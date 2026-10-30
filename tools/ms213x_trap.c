/*
 * ms213x_trap - trampa de alta frecuencia para cazar al escritor del
 * transitorio 960 en eventos de modo 1080p120 (sin stream).
 *
 * Ventanas de 4 bytes (el protocolo 0xB5 devuelve addr..addr+3 en una
 * transaccion), sweep ~7-15 ms, timestamps en microsegundos, y re-apertura
 * automatica cuando el cambio de modo rebota el USB.
 *
 * Campos vigilados (BE = hi primero):
 *   [1AAD:1AAE] fuente de w2   [1AB1] clase
 *   [1AE2:1AE3] w1 (f604)      [1AE6:1AE7] w2 (f606!!!)
 *   [1AE8:1AE9] h2 (f60e)      [1AEA:1AEB] struct B w (f618)
 *   [F604..F607] scaler        [22BC..22BF] refresh/geo entrada
 */
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <hidapi/hidapi.h>

#define VID 0x345f
#define PID 0x2131

static const uint16_t wins[] = {
	0x22dc, 0x1ae4, 0xf604
};
#define NWINS (sizeof(wins)/sizeof(wins[0]))

static hid_device *h;

static hid_device *open_dev(void)
{
	while (!(h = hid_open(VID, PID, NULL)))
		usleep(30000);
	return h;
}

static int read4(uint16_t addr, uint8_t out[4])
{
	uint8_t cmd[8] = { 0xb5, addr >> 8, addr & 0xff };
	uint8_t resp[8] = { 1 };
	if (hid_send_feature_report(h, cmd, 8) < 0)
		return -1;
	if (hid_get_feature_report(h, resp, 8) < 0)
		return -1;
	out[0] = resp[3]; out[1] = resp[4]; out[2] = resp[5]; out[3] = resp[6];
	return 0;
}

static uint64_t now_us(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000000ull + ts.tv_nsec / 1000;
}

int main(int argc, char **argv)
{
	int sleep_us = argc > 1 ? atoi(argv[1]) : 4000;
	uint8_t cur[NWINS][4], prev[NWINS][4];
	int armed = 0;

	hid_init();
	open_dev();
	fprintf(stderr, "trap armada: %d ventanas, sweep+dormida=%dus\n", (int)NWINS, sleep_us);

	for (;;) {
		int bad = 0;
		for (int w = 0; w < (int)NWINS; w++)
			if (read4(wins[w], cur[w]) < 0) { bad = 1; break; }
		if (bad) {
			hid_close(h); h = NULL;
			open_dev();
			armed = 0;
			printf("[%9llu] --- re-enum, re-armado ---\n",
			       (unsigned long long)now_us());
			fflush(stdout);
			continue;
		}
		if (!armed || memcmp(cur, prev, sizeof(cur)) != 0) {
			printf("[%9llu]", (unsigned long long)now_us());
			for (int w = 0; w < (int)NWINS; w++) {
				if (!armed || memcmp(cur[w], prev[w], 4) != 0)
					printf(" %04x:%02x%02x%02x%02x", wins[w],
					       cur[w][0], cur[w][1], cur[w][2], cur[w][3]);
			}
			printf("\n");
			fflush(stdout);
			memcpy(prev, cur, sizeof(cur));
			armed = 1;
		}
		usleep(sleep_us);
	}
	return 0;
}
