/* Sonda 5: tipos de report OUTPUT (2) vs FEATURE (3) para la MS213x-ROM.
 * SET_REPORT: 0x21, 0x09, wValue = (tipo<<8)|id
 * GET_REPORT: 0xA1, 0x01, wValue = (tipo<<8)|id   tipo: 1=input 2=output 3=feature
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static libusb_device_handle *dh = NULL;

static int set_report(int type, int rid, const uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0x21, 0x09, (type << 8) | rid, 0,
                                   (uint8_t *)payload, len, 500);
}

static int get_report(int type, int rid, uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (type << 8) | rid, 0,
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

    uint8_t cmd[16], resp[16];
    int types[] = { 2, 3 };       /* output, feature */
    int ids[] = { 0, 1 };
    const char *tn[] = { "?", "input", "output", "feature" };

    for (int ti = 0; ti < 2; ti++) {
        for (int ii = 0; ii < 2; ii++) {
            int t = types[ti], rid = ids[ii];
            memset(cmd, 0, sizeof(cmd)); cmd[0] = 0xc5; cmd[1] = 0xb0;
            int r = set_report(t, rid, cmd, 8);
            printf("SET type=%s rid=%d: r=%d%s\n", tn[t], rid, r, r == LIBUSB_ERROR_PIPE ? " STALL" : "");
            if (r >= 0) {
                printf("  >>> SET ACEPTADO (type=%s rid=%d) <<<\n", tn[t], rid);
                memset(resp, 0xAA, sizeof(resp));
                r = get_report(t, rid, resp, 8);
                printf("  GET same: r=%d\n", r);
                if (r > 0) dump("  resp", resp, r);
            }
        }
    }

    /* GETs solos de todos los tipos por si hay datos esperando */
    for (int t = 1; t <= 3; t++) {
        for (int rid = 0; rid <= 1; rid++) {
            memset(resp, 0xAA, sizeof(resp));
            int r = get_report(t, rid, resp, 8);
            if (r > 0) { printf("GET type=%s rid=%d: r=%d ", tn[t], rid, r); dump("resp", resp, r); }
            else printf("GET type=%s rid=%d: r=%d%s\n", tn[t], rid, r, r == LIBUSB_ERROR_PIPE ? " STALL" : "");
        }
    }

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
