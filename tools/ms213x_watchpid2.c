#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FLASHER "/Users/fcaraneda/projects/utility_projects/firmware_capturadora/tools/ms213x_flash"
#define WRAPPER "/Users/fcaraneda/projects/utility_projects/firmware_capturadora/backup/MS2131_native_wrapper.bin"

static void stamp(const char *fmt, uint16_t vid, uint16_t pid) {
    char tbuf[32];
    time_t t = time(NULL);
    struct tm tmv;
    localtime_r(&t, &tmv);
    strftime(tbuf, sizeof(tbuf), "%H:%M:%S", &tmv);
    char msg[256];
    snprintf(msg, sizeof(msg), fmt, vid, pid);
    fprintf(stderr, "[%s] %s\n", tbuf, msg);
    fflush(stderr);
}

int main(void) {
    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) { perror("libusb_init"); return 1; }
    fprintf(stderr, "[watch2] armado: 345f:* -> flash wrapper | 534d:2130 -> solo log\n");
    fflush(stderr);
    int rom_prev = 0;
    for (;;) {
        libusb_device **list;
        ssize_t n = libusb_get_device_list(ctx, &list);
        int rom = 0, race = 0;
        uint16_t rvid = 0, rpid = 0;
        for (ssize_t i = 0; i < n; i++) {
            struct libusb_device_descriptor d;
            if (libusb_get_device_descriptor(list[i], &d) == 0) {
                if (d.idVendor == 0x345f &&
                    (d.idProduct == 0x2131 || d.idProduct == 0x2130 ||
                     d.idProduct == 0x2132 || d.idProduct == 0x2133 || d.idProduct == 0x0001)) {
                    race = 1; rvid = d.idVendor; rpid = d.idProduct;
                    break;
                }
                if (d.idVendor == 0x534d && d.idProduct == 0x2130) {
                    rom = 1; rvid = d.idVendor; rpid = d.idProduct;
                }
            }
        }
        libusb_free_device_list(list, 1);
        if (race) {
            stamp("CARRERA GANADA %04x:%04x — flasheando wrapper AHORA", rvid, rpid);
            execl(FLASHER, "ms213x_flash", "-w", WRAPPER, "-n", (char *)NULL);
            perror("execl");
            return 1;
        }
        if (rom && !rom_prev) {
            stamp("ROM MODE APARECE %04x:%04x (puente puede seguir puesto: NO flasheo)", rvid, rpid);
        }
        if (!rom && rom_prev) {
            stamp("ROM MODE DESAPARECE %04x:%04x", rvid, rpid);
        }
        rom_prev = rom;
        usleep(20000);
    }
}
