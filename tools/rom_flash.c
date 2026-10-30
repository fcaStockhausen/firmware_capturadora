/* rom_flash — flasheador definitivo de la MS2131 via ROM if#4 (USB3).
 * 1) setup SPI (SFR P2/P3 + XDATA f01f) — verificado
 * 2) lectura de verificacion: flash[0..15] debe calzar con testB (3c c3 ...)
 * 3) erase chip (fe)
 * 4) escritura pagina a pagina (f8, len CORRECTO 0x0100, chunks de 6 bytes)
 * 5) lectura completa y verify contra la imagen
 * Uso: rom_flash <imagen.bin> [--noverify]
 */
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static libusb_device_handle *dh = NULL;
static const int IFC = 4;

static int setrep(const uint8_t *pay, uint16_t len) {
    return libusb_control_transfer(dh, 0x21, 0x09, (3 << 8), IFC, (uint8_t *)pay, len, 400);
}
static int getrep(uint8_t *pay, uint16_t len) {
    return libusb_control_transfer(dh, 0xA1, 0x01, (3 << 8), IFC, pay, len, 400);
}
static void dump(const char *tag, const uint8_t *b, int n) {
    printf("%s:", tag);
    for (int i = 0; i < n && i < 16; i++) printf(" %02x", b[i]);
    printf("\n");
}
static uint8_t sfr_read(uint8_t addr) {
    uint8_t cmd[8] = { 0xc5, addr, 0, 0, 0, 0, 0, 0 };
    setrep(cmd, 8);
    uint8_t r[8]; memset(r, 0, sizeof(r));
    if (getrep(r, 8) > 0) return r[2];
    return 0xEE;
}
static int setup_spi(void) {
    uint8_t c[8];
    c[0]=0xb6; c[1]=0xf0; c[2]=0x1f; c[3]=0x00;
    if (setrep(c,8) < 0) return -1;
    uint8_t p3 = sfr_read(0xb0);
    uint8_t p3n = (p3 | 0x20) & ~0x1c;
    c[0]=0xc6; c[1]=0xb0; c[2]=p3n;
    if (setrep(c,8) < 0) return -1;
    uint8_t p2 = sfr_read(0xa0);
    c[0]=0xc6; c[1]=0xa0; c[2]=(uint8_t)(p2 | 0x1c);
    if (setrep(c,8) < 0) return -1;
    c[0]=0xb6; c[1]=0xf0; c[2]=0x1f; c[3]=0x10;
    if (setrep(c,8) < 0) return -1;
    return 0;
}
/* lee hasta 256 bytes de la pagina pag al buf (que debe ser >=256) */
static int read_page(uint32_t addr, uint8_t *buf) {
    uint8_t ld[8] = { 0xf7, 0x01, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff, 0x01, 0x00, 0 };
    if (setrep(ld, 8) < 0) return -1;
    usleep(5000);
    for (int off = 0; off < 256; off += 8) {
        uint8_t xf[8] = { 0xf7, 0x00, 0, 0, 0, (off >> 8) & 0xff, off & 0xff, 0 };
        if (setrep(xf, 8) < 0) return -1;
        if (getrep(&buf[off], 8) < 0) return -1;
    }
    return 0;
}
static int write_page(uint32_t addr, const uint8_t *buf) {
    uint8_t ld[8] = { 0xf8, 0x01, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff, 0x01, 0x00, 0 };
    if (setrep(ld, 8) < 0) return -1;
    for (int off = 0; off < 256; off += 6) {
        uint8_t xf[8] = { 0xf8, 0x00 };
        int n = 256 - off; if (n > 6) n = 6;
        memcpy(&xf[2], &buf[off], n);
        if (setrep(xf, 8) < 0) return -1;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) { printf("uso: %s <imagen.bin>\n", argv[0]); return 1; }
    int noverify = (argc > 2 && strcmp(argv[2], "--noverify") == 0);

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("imagen"); return 1; }
    fseek(f, 0, SEEK_END); long flen = ftell(f); fseek(f, 0, SEEK_SET);
    uint8_t *img = malloc(flen + 300);
    memset(img, 0xff, flen + 300);
    if (fread(img, 1, flen, f) != (size_t)flen) { perror("read"); return 1; }
    fclose(f);
    printf("imagen: %s (%ld bytes) magic=%02x %02x\n", argv[1], flen, img[0], img[1]);
    if (img[0] != 0x3c || img[1] != 0xc3) { printf("imagen sin magic 3c c3 — ABORTO\n"); return 1; }

    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("ROM no visible (534d:2130) — reentra al modo ROM y reintenta\n"); return 1; }
    printf("ROM abierta en if#4\n");

    if (setup_spi() < 0) { printf("setup_spi fallo\n"); return 1; }
    printf("SPI setup OK (P3=%02x P2=%02x)\n", sfr_read(0xb0), sfr_read(0xa0));

    uint8_t page[300];
    if (read_page(0, page) < 0) { printf("lectura inicial fallo\n"); return 1; }
    dump("flash[0..15] ACTUAL", page, 16);
    if (page[0] == 0x3c && page[1] == 0xc3) printf("flash contiene imagen 3c c3 (testB) — canal calibrado\n");
    else if (page[0] == 0xff && page[1] == 0xff) printf("flash parece BORRADA (ff ff)\n");
    else printf("contenido inesperado — continuo bajo tu riesgo\n");

    printf("\nERASE chip (fe)... ");
    uint8_t fe[8] = { 0xfe, 0, 0, 0, 0, 0, 0, 0 };
    int r = setrep(fe, 8);
    printf("r=%d, esperando...\n", r);
    sleep(4);
    read_page(0, page);
    dump("flash[0..7] tras erase", page, 8);

    long npages = (flen + 255) / 256;
    printf("\nESCRIBIENDO %ld paginas...\n", npages);
    for (long p = 0; p < npages; p++) {
        uint8_t wbuf[256];
        memset(wbuf, 0xff, sizeof(wbuf));
        long off = p * 256, n = flen - off; if (n > 256) n = 256;
        memcpy(wbuf, &img[off], n);
        if (write_page((uint32_t)off, wbuf) < 0) {
            int alive = libusb_control_transfer(dh, 0xC0, 0, 0, 0, page, 0, 100);
            printf("\nFALLO escribiendo pagina %ld (off 0x%lx) — device %s\n", p, off,
                   alive == 0 ? "vivo" : "desaparecido");
            return 2;
        }
        if ((p % 32) == 0) { printf("%3ld/%ld\r", p, npages); fflush(stdout); }
    }
    printf("escritura completa: %ld paginas\n", npages);

    if (noverify) { printf("(sin verify)\n"); goto done; }
    printf("\nVERIFICANDO...\n");
    long bad = 0;
    for (long p = 0; p < npages; p++) {
        long off = p * 256, n = flen - off; if (n > 256) n = 256;
        if (read_page((uint32_t)off, page) < 0) { printf("\nverify: fallo lectura pag %ld\n", p); bad++; break; }
        if (memcmp(page, &img[off], n) != 0) {
            bad++;
            printf("\nMISMATCH pag %ld (off 0x%lx):\n  img:", p, off);
            for (int i = 0; i < 16; i++) printf(" %02x", img[off+i]);
            printf("\n  flash:");
            for (int i = 0; i < 16; i++) printf(" %02x", page[i]);
            printf("\n");
        }
        if ((p % 32) == 0) { printf("%3ld/%ld\r", p, npages); fflush(stdout); }
    }
    if (bad == 0) printf("\nVERIFY OK — FLASH ESCRITA CORRECTAMENTE\n");
    else printf("\nVERIFY: %ld paginas mal\n", bad);

done:
    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
