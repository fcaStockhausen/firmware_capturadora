/* Sonda 9: ATAQUE LATERAL al stack EP0 de la MS213x-ROM.
 * Vector: el stack responde TODO IN desde un buffer TX de 8 bytes (dangling) y
 * acepta TODO vendor OUT en un buffer RX. Probamos:
 *   A) IN con wIndex/wValue variables (puntero indexado?)
 *   B) vendor OUT con wLength 8..255 (overflow del buffer RX)
 *      -> si el overflow alcanza el TX: nuestros markers aparecen en el IN
 *   C) GET_DESCRIPTOR con wLength oversize (leak mas alla del descriptor)
 *   D) tras cada ataque: GET de control para ver si el estado cambio
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static libusb_device_handle *dh = NULL;

static int vin_w(int req, uint16_t wval, uint16_t widx, uint8_t *buf, uint16_t len) {
    return libusb_control_transfer(dh, 0xC0, req, wval, widx, buf, len, 200);
}
static int getrep(uint8_t *buf, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (3 << 8), 0, buf, len, 200);
}
static void dump(const char *tag, const uint8_t *b, int n) {
    printf("%s [%d]:", tag, n);
    for (int i = 0; i < n && i < 32; i++) printf(" %02x", b[i]);
    printf("\n");
}
static int alive(void) {
    uint8_t b[8];
    return vin_w(0x00, 0, 0, b, 8) >= 0;
}

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("ROM no visible\n"); return 1; }
    printf("ROM abierta\n");

    uint8_t base[8], cur[64];
    memset(base, 0, sizeof(base));
    getrep(base, 8);
    dump("baseline TX", base, 8);

    /* === A) wIndex sweep === */
    printf("\n[A] IN wIndex 0..64:\n");
    for (int i = 0; i <= 64; i++) {
        memset(cur, 0, sizeof(cur));
        int r = vin_w(0x00, 0, i, cur, 8);
        if (r >= 0 && memcmp(cur, base, 8) != 0) {
            printf("  wIndex=%d CAMBIO:", i); dump("", cur, 8);
            memcpy(base, cur, 8);
        }
    }
    /* wValue high-byte sweep */
    printf("[A2] IN wValue high 0..255:\n");
    for (int v = 0; v <= 255; v++) {
        memset(cur, 0, sizeof(cur));
        int r = vin_w(0x00, v << 8, 0, cur, 8);
        if (r >= 0 && memcmp(cur, base, 8) != 0) {
            printf("  wValue=%02x00 CAMBIO:", v); dump("", cur, 8);
            memcpy(base, cur, 8);
        }
    }

    /* === B) overflow del RX === */
    int lens[] = { 8, 16, 24, 32, 48, 64, 96, 128, 192, 255 };
    for (unsigned k = 0; k < sizeof(lens)/sizeof(lens[0]); k++) {
        int len = lens[k];
        uint8_t pay[255];
        for (int i = 0; i < len; i++) pay[i] = (uint8_t)(0xC0 + (i & 0x3F)); /* marcador rastreable */
        pay[0] = 0xB0; pay[1] = (uint8_t)len; pay[2] = 0xCA; pay[3] = 0xFE;
        int r = libusb_control_transfer(dh, 0x40, 0x00, 0, 0, pay, len, 300);
        printf("[B] OUT len=%3d: r=%d", len, r);
        if (r < 0) { printf(" (STALL/err)\n"); break; }
        uint8_t after[8];
        memset(after, 0, sizeof(after));
        int r2 = getrep(after, 8);
        printf(" | TX tras:");
        for (int i = 0; i < 8 && r2 > 0; i++) printf(" %02x", after[i]);
        printf("\n");
        if (r2 > 0 && (after[0] == 0xB0 || after[2] == 0xCA || memchr(after, 0xFE, 4))) {
            printf("  >>> MARKER EN TX — OVERFLOW->TX CONFIRMADO <<<\n");
        }
        if (!alive()) { printf("  dispositivo murio tras overflow len=%d\n", len); break; }
    }

    /* === C) descriptores oversize === */
    printf("\n[C] GET_DESCRIPTOR oversize:\n");
    uint8_t big[255];
    int r = libusb_control_transfer(dh, 0x80, 0x06, (1 << 8), 0, big, 64, 300); /* device, 64B */
    if (r > 0) { printf("  device[%d]:", r); for (int i = 0; i < r; i++) printf(" %02x", big[i]); printf("\n"); }
    r = libusb_control_transfer(dh, 0x80, 0x06, (2 << 8), 0, big, 255, 300); /* config full */
    if (r > 0) { printf("  config[%d] head:", r); for (int i = 0; i < 32 && i < r; i++) printf(" %02x", big[i]); printf("\n"); }
    r = libusb_control_transfer(dh, 0x81, 0x06, (0x22 << 8), 0, big, 255, 300); /* HID report oversize */
    if (r > 0) { printf("  report[%d]:", r); for (int i = 0; i < r && i < 48; i++) printf(" %02x", big[i]); printf("\n"); }
    /* strings */
    for (int s = 0; s <= 4; s++) {
        r = libusb_control_transfer(dh, 0x80, 0x06, (3 << 8) | s, 0x0409, big, 64, 300);
        if (r > 0) { printf("  string%d[%d]:", s, r); for (int i = 0; i < r && i < 20; i++) printf(" %02x", big[i]); printf("\n"); }
    }

    /* === E) comando flash como vendor OUT tras todo lo anterior === */
    uint8_t fcmd[8] = { 0xf7, 0x01, 0, 0, 0, 0, 1, 0 };
    libusb_control_transfer(dh, 0x40, 0x00, 0, 0, fcmd, 8, 200);
    uint8_t fcmd2[8] = { 0xf7, 0x00, 0, 0, 0, 0, 0, 0 };
    libusb_control_transfer(dh, 0x40, 0x00, 0, 0, fcmd2, 8, 200);
    memset(cur, 0, sizeof(cur));
    int r3 = getrep(cur, 8);
    if (r3 > 0) { printf("[E] TX tras cmd flash:"); dump("", cur, 8); }

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
