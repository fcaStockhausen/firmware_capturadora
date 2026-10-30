/* Sonda 7: ¿los vendor OUT aterrizan en el buffer que devuelven los GET?
 * baseline GET -> vendor OUT marcado -> GET -> comparar.
 * Si el eco aparece: canal de comandos funcional.
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static libusb_device_handle *dh = NULL;

static int vout(int req, const uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0x40, req, 0, 0, (uint8_t *)payload, len, 500);
}
static int vin(int req, uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0xC0, req, 0, 0, payload, len, 500);
}
static int getrep(int type, int rid, uint8_t *payload, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (type << 8) | rid, 0, payload, len, 500);
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
    if (!dh) { printf("ROM no visible — reintenta cuando este en pantalla\n"); return 1; }
    printf("ROM abierta\n");

    uint8_t a[16], b[16];

    /* baseline: dos GETs seguidos — deben ser identicos (estabilidad) */
    memset(a, 0, sizeof(a)); getrep(3, 0, a, 8);
    memset(b, 0, sizeof(b)); getrep(3, 0, b, 8);
    dump("baseline GET#1", a, 8);
    dump("baseline GET#2", b, 8);
    int estable = memcmp(a, b, 8) == 0;
    printf("buffer estable: %s\n", estable ? "SI" : "NO");

    /* vendor OUT con marcador inequivoco */
    uint8_t mark[8] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x11, 0x22, 0x33, 0x44 };
    printf("\nvendor OUT req=0x00 marcador DEADBEEF...\n");
    int r = vout(0x00, mark, 8);
    printf("  r=%d\n", r);
    memset(b, 0, sizeof(b)); getrep(3, 0, b, 8);
    dump("GET tras marcador", b, 8);
    if (memcmp(a, b, 8) != 0) printf("  >>> CAMBIO EL BUFFER <<<\n");

    /* variante: wValue con magic en vez de payload */
    r = libusb_control_transfer(dh, 0x40, 0x00, 0xBEEF, 0x2130, mark, 8, 500);
    printf("vendor OUT wValue=BEEF wIndex=2130: r=%d\n", r);
    memset(b, 0, sizeof(b)); getrep(3, 0, b, 8);
    dump("GET tras wValue-magic", b, 8);
    if (memcmp(a, b, 8) != 0) printf("  >>> CAMBIO EL BUFFER <<<\n");

    /* vendor IN tras el OUT — quizas la respuesta va ahi */
    memset(b, 0, sizeof(b)); r = vin(0x00, b, 8);
    if (r > 0) dump("vendor IN tras marcador", b, r);

    /* comando real como vendor OUT: read SFR P3 {c5,b0} */
    uint8_t cmd[8] = { 0xc5, 0xb0, 0, 0, 0, 0, 0, 0 };
    r = vout(0x00, cmd, 8);
    printf("\nvendor OUT cmd {c5 b0}: r=%d\n", r);
    memset(b, 0, sizeof(b)); getrep(3, 0, b, 8);
    dump("GET tras cmd", b, 8);

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
