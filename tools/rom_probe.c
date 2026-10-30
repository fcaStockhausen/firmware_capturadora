/* Sonda diagnóstica: ¿por dónde habla la MS213x-ROM (534d:2130)?
 * Enumera TODAS las colecciones HID, prueba el protocolo del flasher
 * en cada una con errores verbosos, y si alguna responde, lee flash.
 */
#include <hidapi/hidapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

static void phiderr(hid_device *h, const char *what) {
    const wchar_t *e = hid_error(h);
    if (e) fprintf(stderr, "    hid_error(%s): %ls\n", what, e);
    else fprintf(stderr, "    hid_error(%s): (null)\n", what);
}

static int send_cmd(hid_device *h, const uint8_t *cmd, size_t len) {
    int r = hid_send_feature_report(h, cmd, len);
    if (r < 0) { fprintf(stderr, "    send[%zu] fallo r=%d\n", len, r); phiderr(h, "send"); }
    return r;
}

static int get_rep(hid_device *h, uint8_t *buf, size_t len) {
    int r = hid_get_feature_report(h, buf, len);
    if (r < 0) { fprintf(stderr, "    get[%zu] fallo r=%d\n", len, r); phiderr(h, "get"); }
    return r;
}

static void try_protocol(hid_device *h, const char *tag) {
    uint8_t resp[64];
    int r;

    printf("  [%s] test ms_read_sfr(P3=0xb0): cmd {0xc5,0xb0}\n", tag);
    uint8_t c_sfr[8] = { 0xc5, 0xb0 };
    r = send_cmd(h, c_sfr, sizeof(c_sfr));
    if (r < 0) return;
    memset(resp, 0xAA, sizeof(resp));
    r = get_rep(h, resp, 8);
    if (r < 0) return;
    printf("    OK r=%d resp: %02x %02x %02x %02x %02x %02x %02x %02x\n",
           r, resp[0], resp[1], resp[2], resp[3], resp[4], resp[5], resp[6], resp[7]);

    printf("  [%s] test read_flash_page(0): cmd {0xf7,0x01,0,0,0,0,1}\n", tag);
    uint8_t c_read[8] = { 0xf7, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01 };
    r = send_cmd(h, c_read, sizeof(c_read));
    if (r < 0) return;
    uint8_t c_xfer[8] = { 0xf7, 0x00, 0, 0, 0, 0, 0, 0 };
    r = send_cmd(h, c_xfer, sizeof(c_xfer));
    if (r < 0) return;
    memset(resp, 0xAA, sizeof(resp));
    r = get_rep(h, resp, 8);
    if (r < 0) return;
    printf("    flash[0..7]: %02x %02x %02x %02x %02x %02x %02x %02x  (3c c3 = cabecera firmware)\n",
           resp[0], resp[1], resp[2], resp[3], resp[4], resp[5], resp[6], resp[7]);
    printf("  [%s] LA ROM RESPONDE POR AQUI\n", tag);
}

int main(void) {
    if (hid_init() < 0) { fprintf(stderr, "hid_init fallo\n"); return 1; }

    printf("=== Enumerando 534d:2130 ===\n");
    struct hid_device_info *devs = hid_enumerate(0x534d, 0x2130);
    int n = 0;
    for (struct hid_device_info *d = devs; d; d = d->next, n++) {
        printf("col#%d path=%s\n  if=%d usage_page=%04x usage=%04x prod=%ls serial=%ls\n",
               n, d->path, d->interface_number, d->usage_page, d->usage,
               d->product_string ? d->product_string : L"(null)",
               d->serial_number ? d->serial_number : L"(null)");
    }
    if (!devs) printf("(ninguna coleccion HID enumerada)\n");

    for (struct hid_device_info *d = devs; d; d = d->next) {
        printf("\n=== Abriendo col path=%s ===\n", d->path);
        hid_device *h = hid_open_path(d->path);
        if (!h) { fprintf(stderr, "  hid_open_path fallo\n"); continue; }
        try_protocol(h, d->path);
        hid_close(h);
    }
    hid_free_enumeration(devs);

    printf("\n=== Modo flasher: hid_open(vid,pid) ===\n");
    hid_device *h = hid_open(0x534d, 0x2130, NULL);
    if (h) { try_protocol(h, "hid_open"); hid_close(h); }
    else fprintf(stderr, "hid_open(vid,pid) fallo\n");

    hid_exit();
    return 0;
}
