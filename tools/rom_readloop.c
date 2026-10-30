/* rom_readloop — test de estabilidad de lectura SPI desde ROM (if#4).
 * Diagnóstico del episodio de no-arranque: si la mask ROM lee el
 * checksum de la flash de forma marginal (alimentación degradada),
 * lecturas repetidas de la MISMA pagina deberian mostrar bit-flips.
 *
 * 1) setup SPI (identico a rom_flash — probado ~6 veces)
 * 2) lectura golden completa de la flash (62715B)
 * 3) N pasadas comparando byte a byte; reporta todo flip
 * 4) lectura de SFRs (P2/P3/SP/ACC/PSW) para registro
 *
 * NO escribe NADA en flash. Solo XDATA f01f + SFR P2/P3 (setup estandar).
 * Uso: rom_readloop [pasadas]
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

#define FLEN 62715L
#define NPAGES ((FLEN + 255) / 256)

int main(int argc, char **argv) {
    int passes = (argc > 1) ? atoi(argv[1]) : 10;

    libusb_context *ctx = NULL;
    if (libusb_init(&ctx) < 0) return 1;
    dh = libusb_open_device_with_vid_pid(NULL, 0x534d, 0x2130);
    if (!dh) { printf("ROM no visible (534d:2130) — no puedo testear\n"); return 1; }
    printf("ROM abierta if#4\n");

    printf("SFRs: P2=%02x P3=%02x SP=%02x ACC=%02x PSW=%02x DPL=%02x DPH=%02x\n",
           sfr_read(0xa0), sfr_read(0xb0), sfr_read(0x81), sfr_read(0xe0),
           sfr_read(0xd0), sfr_read(0x82), sfr_read(0x83));

    if (setup_spi() < 0) { printf("setup_spi fallo\n"); return 1; }
    printf("SPI setup OK\n");

    uint8_t *golden = malloc(NPAGES * 256);
    uint8_t *cur = malloc(NPAGES * 256);
    if (!golden || !cur) { printf("oom\n"); return 1; }

    printf("pasada golden (%ld paginas)...\n", NPAGES);
    for (long p = 0; p < NPAGES; p++) {
        if (read_page((uint32_t)(p * 256), &golden[p * 256]) < 0) {
            printf("fallo lectura pag %ld en golden — aborto\n", p); return 2;
        }
    }
    printf("golden: magic=%02x %02x  fin=%02x %02x\n",
           golden[0], golden[1], golden[FLEN-2], golden[FLEN-1]);

    if (argc > 2) {
        FILE *df = fopen(argv[2], "wb");
        if (df) { fwrite(golden, 1, FLEN, df); fclose(df); printf("golden guardado en %s\n", argv[2]); }
    }

    long total_flips = 0;
    for (int pass = 1; pass <= passes; pass++) {
        long flips = 0, badpages = 0;
        for (long p = 0; p < NPAGES; p++) {
            if (read_page((uint32_t)(p * 256), cur) < 0) {
                printf("pasada %d: FALLO lectura pag %ld — canal cayo\n", pass, p);
                return 3;
            }
            if (memcmp(cur, &golden[p * 256], 256) != 0) {
                badpages++;
                for (int i = 0; i < 256; i++) {
                    if (cur[i] != golden[p*256+i]) {
                        flips++;
                        if (flips <= 20)
                            printf("  FLIP pasada %d: flash 0x%06lX: golden=%02x leido=%02x (xor %02x)\n",
                                   pass, (long)(p*256+i), golden[p*256+i], cur[i],
                                   (uint8_t)(golden[p*256+i]^cur[i]));
                    }
                }
            }
        }
        total_flips += flips;
        printf("pasada %2d/%d: %ld flips en %ld paginas\n", pass, passes, flips, badpages);
        fflush(stdout);
    }

    printf("\nRESULTADO: %ld bit-flips en %d pasadas completas (%ld lecturas por byte)\n",
           total_flips, passes, (long)passes + 1);
    if (total_flips == 0)
        printf("LECTURA SPI ESTABLE — la mask ROM lee la flash sin errores en este estado.\n");
    else
        printf("LECTURA MARGINAL — bit-flips detectados: la ROM puede rechazar el firmware por checksum inestable.\n");

    libusb_close(dh);
    libusb_exit(ctx);
    return 0;
}
