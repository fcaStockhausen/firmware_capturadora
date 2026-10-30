/* Sonda 3: hablar con la MS213x-ROM por control transfers DIRECTOS (libusb),
 * replicando el formato de cable de Linux hidraw/ms-tools:
 *   SET_REPORT: 0x21, bRequest 0x09, wValue (3<<8)|reportID, wIndex=iface, data
 *   GET_REPORT: 0xA1, bRequest 0x01, wValue (3<<8)|reportID, wIndex=iface, data
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static libusb_device_handle *dh = NULL;

static int set_report(uint16_t rid, const uint8_t *payload, uint16_t len, int iface) {
    return libusb_control_transfer(dh, 0x21, 0x09, (3 << 8) | rid, iface,
                                   (uint8_t *)payload, len, 500);
}

static int get_report(uint16_t rid, uint8_t *payload, uint16_t len, int iface) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (3 << 8) | rid, iface,
                                   payload, len, 500);
}

static void dump(const char *tag, const uint8_t *b, int n) {
    printf("%s [%d]:", tag, n);
    for (int i = 0; i < n && i < 16; i++) printf(" %02x", b[i]);
    printf("\n");
}

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("no se pudo abrir 534d:2130\n"); return 1; }
    printf("abierto\n");

    uint8_t cmd[8], resp[8];

    /* test 1: ms_read_sfr(P3=0xb0) estilo ms-tools: report ID 0, payload {c5,b0} */
    memset(cmd, 0, sizeof(cmd)); cmd[0] = 0xc5; cmd[1] = 0xb0;
    int r = set_report(0x00, cmd, 8, 0);
    printf("SET_REPORT rid=00 (c5 b0): r=%d\n", r);
    if (r < 0) { libusb_error_name(r); goto more; }
    memset(resp, 0xAA, sizeof(resp));
    r = get_report(0x00, resp, 8, 0);
    printf("GET_REPORT rid=00: r=%d\n", r);
    if (r > 0) dump("resp", resp, r);

more:
    /* test 2: mismo comando pero con report ID 0xb5 (estilo steve-m upstream) */
    memset(cmd, 0, sizeof(cmd)); cmd[0] = 0xb0;  /* addr como payload */
    {
        uint8_t c2[8] = { 0x00 };  /* placeholder */
        memset(c2, 0, sizeof(c2));
        c2[0] = 0xc5 - 0x10; /* no usamos esto, prueba real abajo */
    }
    memset(cmd, 0, sizeof(cmd)); cmd[0] = 0xb0;
    r = set_report(0xc5, cmd, 8, 0);
    printf("SET_REPORT rid=c5: r=%d\n", r);

    /* test 3: exchange completo estilo ms213x ROM con report id 0 */
    /* write XDATA 0xf01f = 0x00 (pin mux off->on luego), primero leamos RAM */
    memset(cmd, 0, sizeof(cmd));
    cmd[0] = 0xb5; cmd[1] = 0xf0; cmd[2] = 0x1f;   /* read XDATA f01f */
    r = set_report(0x00, cmd, 8, 0);
    printf("SET (b5 f0 1f): r=%d\n", r);
    if (r >= 0) {
        memset(resp, 0xAA, sizeof(resp));
        r = get_report(0x00, resp, 8, 0);
        printf("GET: r=%d\n", r);
        if (r > 0) dump("resp", resp, r);
    }

    /* test 4: GET_REPORT sin SET previo (a ver si suelta algo) */
    memset(resp, 0xAA, sizeof(resp));
    r = get_report(0x00, resp, 8, 0);
    printf("GET solo: r=%d\n", r);
    if (r > 0) dump("resp", resp, r);

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
