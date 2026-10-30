/* Sonda 6: escaneo de vendor requests (0x40 OUT / 0xC0 IN) en la MS213x-ROM.
 * Busca CUALQUIER request no-STALL con datos. 5 min de exhaustividad.
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    libusb_device_handle *dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("no se pudo abrir\n"); return 1; }
    printf("abierto — escaneando vendor IN (0xC0)...\n");

    uint8_t buf[32];
    int hits = 0;
    for (int req = 0; req <= 0x3F; req++) {
        for (int wvi = 0; wvi < 2; wvi++) {
            int windex = wvi ? 0 : 0; /* probamos wIndex 0 siempre, y wValue variante */
            int wvalue = wvi ? (req << 8) : 0;
            memset(buf, 0xAA, sizeof(buf));
            int r = libusb_control_transfer(dh, 0xC0, req, wvalue, windex, buf, 8, 200);
            if (r > 0) {
                printf("IN  req=%02x wValue=%04x: r=%d:", req, wvalue, r);
                for (int i = 0; i < r && i < 8; i++) printf(" %02x", buf[i]);
                printf("\n");
                hits++;
            }
        }
    }
    printf("vendor IN: %d hits\n", hits);

    /* algunos OUT con payload conocido, mirando si alguno no hace STALL */
    hits = 0;
    uint8_t cmd[8] = { 0xc5, 0xb0, 0, 0, 0, 0, 0, 0 };
    for (int req = 0; req <= 0x3F; req++) {
        int r = libusb_control_transfer(dh, 0x40, req, 0, 0, cmd, 8, 200);
        if (r >= 0) { printf("OUT req=%02x: r=%d NO-STALL!\n", req, r); hits++; }
    }
    printf("vendor OUT: %d hits\n", hits);

    /* bonus: leer el endpoint de interrupcion EP1 IN con claim (puede fallar por HID driver) */
    int rc = libusb_claim_interface(dh, 0);
    printf("claim iface0: %d (%s)\n", rc, rc == 0 ? "OK" : libusb_error_name(rc));
    if (rc == 0) {
        int xfer = libusb_interrupt_transfer(dh, 0x81, buf, 8, &xfer, 300);
        printf("interrupt IN: %d\n", xfer);
        if (xfer == 0) { printf("  data:"); for (int i = 0; i < 8; i++) printf(" %02x", buf[i]); printf("\n"); }
        libusb_release_interface(dh, 0);
    }

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
