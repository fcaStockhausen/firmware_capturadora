#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <unistd.h>

#define FLASHER "/Users/fcaraneda/projects/utility_projects/firmware_capturadora/tools/ms213x_flash"
#define WRAPPER "/Users/fcaraneda/projects/utility_projects/firmware_capturadora/backup/MS2131_native_wrapper.bin"

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) { perror("libusb_init"); return 1; }
    for (;;) {
        libusb_device **list;
        ssize_t n = libusb_get_device_list(ctx, &list);
        int hit = 0;
        for (ssize_t i = 0; i < n; i++) {
            struct libusb_device_descriptor d;
            if (libusb_get_device_descriptor(list[i], &d) == 0) {
                if ((d.idVendor == 0x345f && (d.idProduct == 0x2131 || d.idProduct == 0x2130 || d.idProduct == 0x2132 || d.idProduct == 0x2133 || d.idProduct == 0x0001)) ||
                    (d.idVendor == 0x534d && d.idProduct == 0x2130)) {
                    fprintf(stderr, "DETECTADO vid=%04x pid=%04x — flasheando wrapper\n", d.idVendor, d.idProduct);
                    fflush(stderr);
                    hit = 1;
                    break;
                }
            }
        }
        libusb_free_device_list(list, 1);
        if (hit) {
            execl(FLASHER, "ms213x_flash", "-w", WRAPPER, "-n", (char *)NULL);
            perror("execl");
            return 1;
        }
        usleep(20000);
    }
}
