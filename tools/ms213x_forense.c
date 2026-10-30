/*
 * ms213x_forense - espera el switch a 120Hz y vuelca el estado completo
 * de las variables de trabajo del residuo en cuanto detecta f606=960.
 */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <hidapi/hidapi.h>

#define VID 0x345f
#define PID 0x2131

static hid_device *h;

static int read_reg(uint16_t addr, uint8_t *val)
{
	uint8_t cmd[8] = { 0xb5, addr >> 8, addr & 0xff };
	uint8_t resp[8] = { 1 };
	if (hid_send_feature_report(h, cmd, 8) < 0) return -1;
	if (hid_get_feature_report(h, resp, 8) < 0) return -1;
	*val = resp[3];
	return 0;
}

static void dump_range(const char *name, uint16_t start, uint16_t end)
{
	printf("%s [%04X-%04X]:", name, start, end);
	for (uint16_t a = start; a <= end; a++) {
		uint8_t v = 0;
		if (read_reg(a, &v) < 0) { printf(" ERR"); break; }
		printf(" %02x", v);
	}
	printf("\n");
}

int main(void)
{
	hid_init();
	h = hid_open(VID, PID, NULL);
	if (!h) { fprintf(stderr, "no dev\n"); return 1; }
	fprintf(stderr, "esperando latch f606=960 (switch a 120 cuando quieras)...\n");
	for (;;) {
		uint8_t lo = 0, hi = 0, rbe = 0;
		if (read_reg(0xf606, &lo) < 0 || read_reg(0xf607, &hi) < 0) {
			hid_close(h); h = NULL;
			while (!h) { usleep(50000); h = hid_open(VID, PID, NULL); }
			continue;
		}
		if (lo == 0xc0 && hi == 0x03) {
			printf("=== RESIDUO DETECTADO ===\n");
			dump_range("1AF8 (work div2)",  0x1af8, 0x1afc);
			dump_range("1AAD (pclk/width)", 0x1aad, 0x1ab2);
			dump_range("1AE0 (struct A+B)", 0x1ae0, 0x1aeb);
			dump_range("22DC (formato)",    0x22dc, 0x22e1);
			dump_range("22B8 (entrada)",    0x22b8, 0x22bf);
			dump_range("00E4 (clase)",      0x00e4, 0x00e7);
			fflush(stdout);
			return 0;
		}
		read_reg(0x22be, &rbe);
		usleep(30000);
	}
	return 0;
}
