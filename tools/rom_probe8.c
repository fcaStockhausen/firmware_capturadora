/* Sonda 8: mapa EXHAUSTIVO del dispatcher EP0 de la MS213x-ROM.
 * Escanea todos los bRequest 0x00-0xFF para cada bmRequestType relevante,
 * IN y OUT, con wValue=0 wIndex=0. Clasifica respuestas por contenido.
 * Imprime solo lo DISTINTO (nuevos patrones de respuesta).
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static libusb_device_handle *dh = NULL;

typedef struct { uint8_t bytes[16]; int len; int count; int first_req; } pattern_t;
static pattern_t pats[128];
static int npat = 0;

static void classify(int req, int r, const uint8_t *buf) {
    if (r < 0) return; /* stall/err — la mayoria */
    for (int i = 0; i < npat; i++) {
        if (pats[i].len == r && memcmp(pats[i].bytes, buf, r > 16 ? 16 : r) == 0) {
            pats[i].count++;
            return;
        }
    }
    if (npat < 128) {
        pats[npat].len = r;
        memcpy(pats[npat].bytes, buf, r > 16 ? 16 : r);
        pats[npat].count = 1;
        pats[npat].first_req = req;
        npat++;
        printf("  NUEVO PATRON req=%02x: [%d]", req, r);
        for (int i = 0; i < r && i < 16; i++) printf(" %02x", buf[i]);
        printf("\n");
    }
}

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("ROM no visible\n"); return 1; }
    printf("ROM abierta — escaneo exhaustivo EP0\n\n");

    uint8_t buf[16];
    struct { uint8_t type; const char *name; } ins[] = {
        { 0x80, "std-dev-IN" }, { 0x81, "std-if-IN" }, { 0x88, "std-ep-IN" },
        { 0xA0, "cls-dev-IN" }, { 0xA1, "cls-if-IN" },
        { 0xC0, "vnd-dev-IN" }, { 0xC1, "vnd-if-IN" },
    };
    struct { uint8_t type; const char *name; } outs[] = {
        { 0x00, "std-dev-OUT" }, { 0x01, "std-if-OUT" },
        { 0x20, "cls-dev-OUT" }, { 0x21, "cls-if-OUT" },
        { 0x40, "vnd-dev-OUT" }, { 0x41, "vnd-if-OUT" },
    };
    uint8_t payload[8] = { 0 };

    for (unsigned t = 0; t < sizeof(ins)/sizeof(ins[0]); t++) {
        npat = 0;
        memset(pats, 0, sizeof(pats));
        printf("=== IN  type=%s (0x%02x) ===\n", ins[t].name, ins[t].type);
        int ok = 0;
        for (int req = 0; req <= 0xFF; req++) {
            memset(buf, 0xAA, sizeof(buf));
            int r = libusb_control_transfer(dh, ins[t].type, req, 0, 0, buf, 8, 100);
            if (r >= 0) { ok++; classify(req, r, buf); }
        }
        printf("  aceptados: %d/256\n", ok);
    }

    for (unsigned t = 0; t < sizeof(outs)/sizeof(outs[0]); t++) {
        npat = 0;
        memset(pats, 0, sizeof(pats));
        printf("=== OUT type=%s (0x%02x) ===\n", outs[t].name, outs[t].type);
        int ok = 0;
        for (int req = 0; req <= 0xFF; req++) {
            int r = libusb_control_transfer(dh, outs[t].type, req, 0, 0, payload, 8, 100);
            if (r >= 0) { ok++;
                if (ok <= 3 || (ok % 64) == 0) printf("  req=%02x aceptado r=%d\n", req, r);
            }
        }
        printf("  aceptados: %d/256\n", ok);
    }

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
