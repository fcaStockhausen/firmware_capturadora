/* Sonda 2: framing correcto para la MS213x-ROM en macOS.
 * 1) Brute-force de longitud con report ID 0x01 (y 0x00) via hidapi
 * 2) Dump del descriptor HID REPORT por EP0 (libusb) para ver IDs/tamaños reales
 */
#include <hidapi/hidapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <libusb-1.0/libusb.h>

static hid_device *open_rom(void) {
    hid_device *h = hid_open(0x534d, 0x2130, NULL);
    if (!h) fprintf(stderr, "hid_open fallo\n");
    return h;
}

int main(void) {
    hid_init();

    hid_device *h = open_rom();
    if (h) {
        uint8_t buf[128];
        printf("=== SET brute-force: report ID 0x01, payload {0xc5,0xb0,...}, len total 2..66 ===\n");
        for (int len = 2; len <= 66; len++) {
            memset(buf, 0, sizeof(buf));
            buf[0] = 0x01; buf[1] = 0xc5; buf[2] = 0xb0;
            int r = hid_send_feature_report(h, buf, len);
            if (r >= 0) printf("  len=%2d -> r=%d OK!\n", len, r);
        }
        printf("=== SET brute-force: sin report ID (0x00), payload {0xc5,0xb0,...} ===\n");
        for (int len = 2; len <= 66; len++) {
            memset(buf, 0, sizeof(buf));
            buf[0] = 0x00; buf[1] = 0xc5; buf[2] = 0xb0;
            int r = hid_send_feature_report(h, buf, len);
            if (r >= 0) printf("  len=%2d -> r=%d OK!\n", len, r);
        }
        hid_close(h);
    }

    printf("\n=== Descriptor HID REPORT via libusb EP0 ===\n");
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) { fprintf(stderr, "libusb_init fallo\n"); return 1; }
    libusb_device **list;
    ssize_t n = libusb_get_device_list(ctx, &list);
    for (ssize_t i = 0; i < n; i++) {
        struct libusb_device_descriptor d;
        if (libusb_get_device_descriptor(list[i], &d) != 0) continue;
        if (d.idVendor != 0x534d || d.idProduct != 0x2130) continue;

        printf("encontrado 534d:2130, configs=%d\n", d.bNumConfigurations);
        struct libusb_config_descriptor *cfg;
        for (int c = 0; c < d.bNumConfigurations; c++) {
            if (libusb_get_config_descriptor(list[i], c, &cfg) != 0) continue;
            printf(" config %d: ifaces=%d\n", c, cfg->bNumInterfaces);
            for (int ifn = 0; ifn < cfg->bNumInterfaces; ifn++) {
                const struct libusb_interface *iface = &cfg->interface[ifn];
                for (int alt = 0; alt < iface->num_altsetting; alt++) {
                    const struct libusb_interface_descriptor *id = &iface->altsetting[alt];
                    printf("  if#%d alt%d class=%02x.%02x eps=%d", ifn, alt, id->bInterfaceClass, id->bInterfaceSubClass, id->bNumEndpoints);
                    if (id->bInterfaceClass == 3) printf("  <-- HID");
                    printf("\n");
                }
            }
            libusb_free_config_descriptor(cfg);
        }

        libusb_device_handle *dh;
        if (libusb_open(list[i], &dh) == 0) {
            for (int ifn = 0; ifn < 4; ifn++) {
                uint8_t rpt[512];
                int r = libusb_control_transfer(dh,
                    LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_INTERFACE,
                    LIBUSB_REQUEST_GET_DESCRIPTOR, (LIBUSB_DT_REPORT << 8), ifn,
                    rpt, sizeof(rpt), 1000);
                if (r > 0) {
                    printf(" REPORT descriptor if#%d (%d bytes):\n", ifn, r);
                    for (int k = 0; k < r; k++) printf("%s%02x", (k % 16) ? " " : "\n   ", rpt[k]);
                    printf("\n");
                }
            }
            libusb_close(dh);
        } else printf(" libusb_open fallo\n");
    }
    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    hid_exit();
    return 0;
}
