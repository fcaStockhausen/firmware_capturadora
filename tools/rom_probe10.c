/* Sonda 10: la ROM en USB3 expone 5 interfaces. Encontrar TODAS las colecciones
 * HID y probar el protocolo de fabrica (c5/b5 setup_spi) en cada una.
 * Si alguna responde: setup_spi + lectura de flash -> CABEZA 3C C3.
 */
#include <libusb-1.0/libusb.h>
#include <hidapi/hidapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

static void dump(const char *tag, const uint8_t *b, int n) {
    printf("%s [%d]:", tag, n);
    for (int i = 0; i < n && i < 16; i++) printf(" %02x", b[i]);
    printf("\n");
}

int main(void) {
    libusb_context *ctx = NULL;
    hid_init();
    if (libusb_init(&ctx) < 0) return 1;

    /* 1) mapa de interfaces via libusb */
    libusb_device **list;
    ssize_t n = libusb_get_device_list(ctx, &list);
    libusb_device *dev = NULL;
    for (ssize_t i = 0; i < n; i++) {
        struct libusb_device_descriptor d;
        if (libusb_get_device_descriptor(list[i], &d) == 0 &&
            d.idVendor == 0x534d && d.idProduct == 0x2130) { dev = list[i]; break; }
    }
    if (!dev) { printf("ROM no visible\n"); return 1; }

    struct libusb_config_descriptor *cfg;
    if (libusb_get_active_config_descriptor(dev, &cfg) == 0) {
        printf("config ACTIVA: ifaces=%d total_len=%d\n", cfg->bNumInterfaces, cfg->wTotalLength);
        for (int i = 0; i < cfg->bNumInterfaces; i++) {
            const struct libusb_interface *ifc = &cfg->interface[i];
            for (int a = 0; a < ifc->num_altsetting; a++) {
                const struct libusb_interface_descriptor *id = &ifc->altsetting[a];
                printf("  if#%d alt%d class=%02x.%02x proto=%d eps=%d\n",
                       i, a, id->bInterfaceClass, id->bInterfaceSubClass, id->bInterfaceProtocol, id->bNumEndpoints);
            }
        }
        libusb_free_config_descriptor(cfg);
    } else {
        printf("get_active_config fallo\n");
    }

    /* 2) colecciones HID via hidapi */
    printf("\n=== colecciones HID ===\n");
    struct hid_device_info *devs = hid_enumerate(0x534d, 0x2130);
    int nc = 0;
    for (struct hid_device_info *d = devs; d; d = d->next, nc++) {
        printf("col#%d if=%d usage=%04x/%04x path=%s\n", nc, d->interface_number, d->usage_page, d->usage, d->path);
    }
    if (!nc) printf("(ninguna)\n");

    /* 3) probar protocolo en cada coleccion, ambos framings */
    for (struct hid_device_info *d = devs; d; d = d->next) {
        hid_device *h = hid_open_path(d->path);
        if (!h) { printf("col if=%d: open fallo\n", d->interface_number); continue; }
        printf("\n--- col if=%d ---\n", d->interface_number);

        uint8_t f9[9] = { 0x00, 0xc5, 0xb0, 0, 0, 0, 0, 0, 0 };   /* ms-tools framing */
        uint8_t f8[8] = { 0xc5, 0xb0, 0, 0, 0, 0, 0, 0 };          /* cmd-como-report-id */

        int r = hid_send_feature_report(h, f9, 9);
        printf("  send9 (00 c5 b0): r=%d\n", r);
        if (r >= 0) {
            uint8_t resp[9];
            memset(resp, 0xAA, sizeof(resp));
            r = hid_get_feature_report(h, resp, 9);
            if (r > 0) { dump("  resp9", resp, r);
                if (resp[1] == 0xc5 && resp[2] == 0xb0) printf("  >>> ECO VALIDO — LA ROM RESPONDE <<<\n");
            } else printf("  get9 fallo r=%d\n", r);
        }
        r = hid_send_feature_report(h, f8, 8);
        printf("  send8 (c5 b0): r=%d\n", r);
        if (r >= 0) {
            uint8_t resp[8];
            memset(resp, 0xAA, sizeof(resp));
            r = hid_get_feature_report(h, resp, 8);
            if (r > 0) { dump("  resp8", resp, r);
                if (resp[0] == 0xc5 && resp[1] == 0xb0) printf("  >>> ECO VALIDO — LA ROM RESPONDE <<<\n");
            } else printf("  get8 fallo r=%d\n", r);
        }
        hid_close(h);
    }
    hid_free_enumeration(devs);

    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    hid_exit();
    return 0;
}
