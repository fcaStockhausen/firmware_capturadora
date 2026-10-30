/* Sonda 11: la ROM sirve config de 5 interfaces que macOS no instancio.
 * Disparar el protocolo de fabrica DIRECTO a cada interfaz via EP0:
 * SET_REPORT/GET_REPORT con wIndex = 0..5, framing 9 bytes {00,cmd,...}.
 * Si algun interface hace eco -> setup_spi + lectura de flash -> FLASH.
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static libusb_device_handle *dh = NULL;

static int setrep(int iface, const uint8_t *pay, uint16_t len) {
    return libusb_control_transfer(dh, 0x21, 0x09, (3 << 8), iface, (uint8_t *)pay, len, 300);
}
static int getrep(int iface, uint8_t *pay, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (3 << 8), iface, pay, len, 300);
}
static void dump(const char *tag, const uint8_t *b, int n) {
    printf("%s [%d]:", tag, n);
    for (int i = 0; i < n && i < 16; i++) printf(" %02x", b[i]);
    printf("\n");
}

int main(int argc, char **argv) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("ROM no visible\n"); return 1; }
    printf("ROM abierta — probando protocolo fabrica en interfaces 0..5\n\n");

    int working_iface = -1;

    for (int iface = 0; iface <= 5; iface++) {
        uint8_t cmd[8] = { 0xc5, 0xb0, 0, 0, 0, 0, 0, 0 };  /* read SFR P3 */
        int r = setrep(iface, cmd, 8);
        printf("if#%d SET {c5 b0}: r=%d%s\n", iface, r, r < 0 ? " (STALL)" : "");
        if (r < 0) continue;
        uint8_t resp[8];
        memset(resp, 0xAA, sizeof(resp));
        r = getrep(iface, resp, 8);
        if (r <= 0) { printf("  GET fallo r=%d\n", r); continue; }
        dump("  resp", resp, r);
        if (resp[0] == 0xc5 && resp[1] == 0xb0) {
            printf("  >>> ECO VALIDO en if#%d — LA ROM OYE <<<\n", iface);
            working_iface = iface;
        }
    }

    if (working_iface < 0) { printf("\nninguna interfaz respondio\n"); goto out; }

    int ifc = working_iface;
    printf("\n=== PROTOCOLO VIVO en if#%d — intentando leer la flash ===\n", ifc);

    /* setup_spi: write XDATA f01f=00 (b6) */
    uint8_t s1[8] = { 0xb6, 0xf0, 0x1f, 0x00, 0, 0, 0, 0 };
    printf("setup f01f=00: r=%d\n", setrep(ifc, s1, 8));
    /* SFR P3 (0xb0): |= 0x20, &= ~0x1c -> read then write */
    uint8_t c_sfr[8] = { 0xc5, 0xb0, 0, 0, 0, 0, 0, 0 };
    setrep(ifc, c_sfr, 8);
    uint8_t p3[8]; memset(p3, 0, sizeof(p3));
    getrep(ifc, p3, 8);
    dump("P3 antes", p3, 8);
    uint8_t v = p3[2];  /* SFR read devuelve resp[2] */
    v = (v | 0x20) & ~0x1c;
    uint8_t w3[8] = { 0xc6, 0xb0, v, 0, 0, 0, 0, 0 };
    printf("write P3=%02x: r=%d\n", v, setrep(ifc, w3, 8));
    /* SFR P2 (0xa0): |= 0x1c */
    uint8_t c2[8] = { 0xc5, 0xa0, 0, 0, 0, 0, 0, 0 };
    setrep(ifc, c2, 8);
    uint8_t p2[8]; memset(p2, 0, sizeof(p2));
    getrep(ifc, p2, 8);
    v = p2[2] | 0x1c;
    uint8_t w2[8] = { 0xc6, 0xa0, v, 0, 0, 0, 0, 0 };
    printf("write P2=%02x: r=%d\n", v, setrep(ifc, w2, 8));
    /* XDATA f01f=10 */
    uint8_t s2[8] = { 0xb6, 0xf0, 0x1f, 0x10, 0, 0, 0, 0 };
    printf("setup f01f=10: r=%d\n", setrep(ifc, s2, 8));

    /* read flash page 0: f7 01 addr=0 len=256; luego f7 00 offset 0 -> 8 bytes */
    uint8_t fr[8] = { 0xf7, 0x01, 0, 0, 0, 0x00, 0x01, 0 };
    printf("f7 read setup: r=%d\n", setrep(ifc, fr, 8));
    uint8_t fx[8] = { 0xf7, 0x00, 0, 0, 0, 0, 0, 0 };
    printf("f7 xfer: r=%d\n", setrep(ifc, fx, 8));
    uint8_t fd[8]; memset(fd, 0xAA, sizeof(fd));
    r: ;
    int rr = getrep(ifc, fd, 8);
    if (rr > 0) {
        dump("flash[0..7]", fd, rr);
        if (fd[0] == 0x3c && fd[1] == 0xc3) {
            printf(">>> 3C C3 — CABECERA DE FIRMWARE EN LA FLASH — LECTURA FUNCIONA <<<\n");
        }
    }

out:
    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
