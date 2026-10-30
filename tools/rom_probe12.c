/* Sonda 12: calibrar la lectura de flash via if#4.
 * Leemos offsets conocidos y comparamos con la imagen original:
 *   img[0x00]=3c c3 f4 c7 ff ff ff ff | img[0x08]=80 00 00 00 19 04 09 10
 *   img[0x30]=02 a4 eb 02 d5 95 7f 08 | img[0xFF00]=? (fin)
 * Ademas: verify de SFRs tras escribir (P3/P2), y respuesta del f7-01.
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static libusb_device_handle *dh = NULL;
static const int IFC = 4;

static int setrep(const uint8_t *pay, uint16_t len) {
    return libusb_control_transfer(dh, 0x21, 0x09, (3 << 8), IFC, (uint8_t *)pay, len, 300);
}
static int getrep(uint8_t *pay, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (3 << 8), IFC, pay, len, 300);
}
static void dump(const char *tag, const uint8_t *b, int n) {
    printf("%s [%d]:", tag, n);
    for (int i = 0; i < n && i < 16; i++) printf(" %02x", b[i]);
    printf("\n");
}

static uint8_t sfr_read(uint8_t addr) {
    uint8_t cmd[8] = { 0xc5, addr, 0, 0, 0, 0, 0, 0 };
    setrep(cmd, 8);
    uint8_t r[8]; memset(r, 0, sizeof(r));
    if (getrep(r, 8) > 0) return r[2];
    return 0xEE;
}

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("ROM no visible\n"); return 1; }

    /* setup SPI con verificacion de escritura */
    uint8_t c[8];
    c[0]=0xb6; c[1]=0xf0; c[2]=0x1f; c[3]=0x00; setrep(c,8);
    uint8_t p3 = sfr_read(0xb0);
    printf("P3 leido=%02x\n", p3);
    uint8_t p3n = (p3 | 0x20) & ~0x1c;
    c[0]=0xc6; c[1]=0xb0; c[2]=p3n; setrep(c,8);
    printf("P3 escrito=%02x, releido=%02x %s\n", p3n, sfr_read(0xb0), sfr_read(0xb0)==p3n?"OK":"FAIL");
    uint8_t p2 = sfr_read(0xa0);
    uint8_t p2n = p2 | 0x1c;
    c[0]=0xc6; c[1]=0xa0; c[2]=p2n; setrep(c,8);
    printf("P2 leido=%02x escrito=%02x, releido=%02x %s\n", p2, p2n, sfr_read(0xa0), sfr_read(0xa0)==p2n?"OK":"FAIL");
    c[0]=0xb6; c[1]=0xf0; c[2]=0x1f; c[3]=0x10; setrep(c,8);
    /* verificar XDATA f01f */
    c[0]=0xb5; c[1]=0xf0; c[2]=0x1f; setrep(c,8);
    uint8_t xr[8]; memset(xr,0,sizeof(xr)); getrep(xr,8);
    dump("XDATA f01f tras setup:", xr, 8);

    /* lecturas en offsets de calibracion */
    unsigned offs[] = { 0x0000, 0x0001, 0x0008, 0x0010, 0x0030, 0x0031, 0x0038, 0x8000, 0xFFF8 };
    for (unsigned k = 0; k < sizeof(offs)/sizeof(offs[0]); k++) {
        unsigned addr = offs[k];
        /* f7 01: cargar pagina addr>>8, len 256 */
        uint8_t ld[8] = { 0xf7, 0x01, (addr >> 16) & 0xff, (addr >> 8) & 0xff, 0, 0x01, 0x00, 0 };
        ld[4] = 0; /* addr bajo siempre 0: leemos desde inicio de pagina */
        int r1 = setrep(ld, 8);
        uint8_t ld_resp[8]; memset(ld_resp, 0, sizeof(ld_resp));
        getrep(ld_resp, 8);
        usleep(20000); /* margen para la carga SPI */
        /* f7 00: pedir offset dentro del buffer */
        uint8_t xf[8] = { 0xf7, 0x00, 0, 0, 0, (addr >> 8) & 0xff, addr & 0xff, 0 };
        int r2 = setrep(xf, 8);
        uint8_t data[8]; memset(data, 0xAA, sizeof(data));
        int r3 = getrep(data, 8);
        printf("off %04x: ld=%d xf=%d get=%d |", addr, r1, r2, r3);
        for (int i = 0; i < 8 && r3 > 0; i++) printf(" %02x", data[i]);
        printf(" | ldresp:");
        for (int i = 0; i < 4; i++) printf(" %02x", ld_resp[i]);
        printf("\n");
    }

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
