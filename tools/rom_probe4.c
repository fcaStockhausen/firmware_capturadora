/* Sonda 4: matriz de report IDs x framing para la MS213x-ROM via libusb EP0.
 * Basado en UsbVideoDownloadTool (UltraSemi): probeFeatureReport() prueba
 * sendFeatureReport(reportId, [0xC5, 0xB0, ...]) con IDs [0, 1] (no-S).
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static libusb_device_handle *dh = NULL;

static int set_report(int rid, const uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0x21, 0x09, (3 << 8) | rid, 0,
                                   (uint8_t *)payload, len, 500);
}

static int get_report(int rid, uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (3 << 8) | rid, 0,
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
    printf("abierto 534d:2130\n");

    uint8_t cmd[16], resp[16];
    int ids[] = { 0, 1, 2, 3, 16, 17 };
    int nid = sizeof(ids) / sizeof(ids[0]);

    for (int ii = 0; ii < nid; ii++) {
        int rid = ids[ii];
        /* variante A: 8 bytes de payload {c5,b0,...} */
        memset(cmd, 0, sizeof(cmd)); cmd[0] = 0xc5; cmd[1] = 0xb0;
        int r = set_report(rid, cmd, 8);
        printf("SET rid=%02d payload8 (c5 b0): r=%d %s\n", rid, r, r == LIBUSB_ERROR_PIPE ? "STALL" : "");
        if (r >= 0) {
            memset(resp, 0xAA, sizeof(resp));
            r = get_report(rid, resp, 8);
            printf("  GET rid=%02d: r=%d\n", rid, r);
            if (r > 0) dump("  resp", resp, r);
        }
        /* variante B: 9 bytes de payload {id,c5,b0,...} (id dentro del data stage) */
        memset(cmd, 0, sizeof(cmd)); cmd[0] = (uint8_t)rid; cmd[1] = 0xc5; cmd[2] = 0xb0;
        r = set_report(rid, cmd, 9);
        if (r >= 0) {
            printf("SET rid=%02d payload9 (con id embebido): r=%d OK!\n", rid, r);
            memset(resp, 0xAA, sizeof(resp));
            r = get_report(rid, resp, 9);
            if (r > 0) dump("  resp9", resp, r);
        }
    }

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
