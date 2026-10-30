/*
 * ms213x_xdata - read/dump/patch XDATA registers of MacroSilicon
 * MS2130/MS2131 HDMI capture sticks via the factory HID interface.
 * Protocol identical to steve-m/ms213x_flash (0xB5 read / 0xB6 write).
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hidapi.h>

#define VID 0x345f
#define PID 0x2131
#define TIMEOUT_MS 300

static hid_device *h = NULL;

static int send_report(const uint8_t *data, size_t len)
{
	return hid_send_feature_report(h, data, len);
}

static int get_report(uint8_t *data, size_t len)
{
	uint8_t buf[64];
	buf[0] = 0x01;
	int r = hid_get_feature_report(h, buf, len);
	if (r < 0)
		return r;
	memcpy(data, buf, len);
	return r;
}

static int read_reg(uint16_t addr, uint8_t *val)
{
	uint8_t cmd[8] = { 0xb5, addr >> 8, addr & 0xff };
	uint8_t resp[8];
	int r = send_report(cmd, sizeof(cmd));
	if (r < 0) return r;
	r = get_report(resp, sizeof(resp));
	if (r < 0) return r;
	*val = resp[3];
	return 0;
}

static int write_reg(uint16_t addr, uint8_t val)
{
	uint8_t cmd[8] = { 0xb6, addr >> 8, addr & 0xff, val };
	return send_report(cmd, sizeof(cmd));
}

static void usage(void)
{
	fprintf(stderr,
		"Usage:\n"
		"  ms213x_xdata read  <hexaddr>          read one register\n"
		"  ms213x_xdata write <hexaddr> <hexval> write one register\n"
		"  ms213x_xdata dump  <hexstart> <hexend> <file>  dump range to file\n"
		"  ms213x_xdata watch <hexstart> <hexend> [interval_ms]  poll & print changes\n");
	exit(1);
}

int main(int argc, char **argv)
{
	if (hid_init())
		return 1;
	h = hid_open(VID, PID, NULL);
	if (!h) {
		fprintf(stderr, "Device not found (VID %04x PID %04x)\n", VID, PID);
		return 1;
	}

	if (argc >= 3 && !strcmp(argv[1], "read")) {
		uint16_t addr = (uint16_t)strtoul(argv[2], NULL, 16);
		uint8_t v;
		if (read_reg(addr, &v) < 0) {
			fprintf(stderr, "read error: %ls\n", hid_error(h));
			return 1;
		}
		printf("0x%04x = 0x%02x\n", addr, v);
		return 0;
	}
	if (argc >= 4 && !strcmp(argv[1], "write")) {
		uint16_t addr = (uint16_t)strtoul(argv[2], NULL, 16);
		uint8_t val = (uint8_t)strtoul(argv[3], NULL, 16);
		if (write_reg(addr, val) < 0) {
			fprintf(stderr, "write error: %ls\n", hid_error(h));
			return 1;
		}
		printf("wrote 0x%04x = 0x%02x\n", addr, val);
		return 0;
	}
	if (argc >= 5 && !strcmp(argv[1], "dump")) {
		uint16_t start = (uint16_t)strtoul(argv[2], NULL, 16);
		uint16_t end = (uint16_t)strtoul(argv[3], NULL, 16);
		FILE *f = fopen(argv[4], "wb");
		if (!f) { perror("fopen"); return 1; }
		for (uint32_t a = start; a <= end; a++) {
			uint8_t v;
			if (read_reg((uint16_t)a, &v) < 0) {
				fprintf(stderr, "read failed at 0x%04x\n", a);
				v = 0;
			}
			fwrite(&v, 1, 1, f);
		}
		fclose(f);
		printf("dumped 0x%04x-0x%04x to %s\n", start, end, argv[4]);
		return 0;
	}
	if (argc >= 4 && !strcmp(argv[1], "watch")) {
		uint16_t start = (uint16_t)strtoul(argv[2], NULL, 16);
		uint16_t end = (uint16_t)strtoul(argv[3], NULL, 16);
		int interval = argc >= 5 ? atoi(argv[4]) : 500;
		size_t n = end - start + 1;
		uint8_t *cur = calloc(n, 1), *prev = calloc(n, 1);
		memset(prev, 0xff, n); /* force first print */
		for (;;) {
			for (size_t i = 0; i < n; i++)
				read_reg((uint16_t)(start + i), &cur[i]);
			int changed = memcmp(cur, prev, n) != 0;
			if (changed) {
				char tstr[32];
				time_t t = time(NULL);
				strftime(tstr, sizeof(tstr), "%H:%M:%S", localtime(&t));
				printf("[%s]", tstr);
				for (size_t i = 0; i < n; i++)
					if (cur[i] != prev[i])
						printf(" %04x:%02x", start + i, cur[i]);
				printf("\n");
				fflush(stdout);
				memcpy(prev, cur, n);
			}
			struct timespec ts = { 0, interval * 1000000L };
			nanosleep(&ts, NULL);
		}
	}
	if (argc >= 3 && !strcmp(argv[1], "guard")) {
		/* watchdog: SOLO si f606/f607 == 960 (estado diezmado de 1080p120)
		 * re-aplica: f600 stop -> anchos 1920 -> f65c=0x10 -> start.
		 * No toca otros anchos (formatos UVC legitimos como 640/720/1280).
		 * Reabre el dispositivo si se desconecta. */
		int interval_ms = argc >= 4 ? atoi(argv[3]) : 200;
		int fails = 0;
		struct timespec ts = { 0, interval_ms * 1000000L };
		for (;;) {
			uint8_t lo, hi;
			if (read_reg(0xf606, &lo) == 0 && read_reg(0xf607, &hi) == 0) {
				fails = 0;
				uint16_t w = lo | (hi << 8);
				if (w == 0x03c0) {
					write_reg(0xf600, 0x00);
					write_reg(0xf606, 0x80); write_reg(0xf607, 0x07);
					write_reg(0xf618, 0x80); write_reg(0xf619, 0x07);
					write_reg(0xf660, 0x80); write_reg(0xf661, 0x07);
					write_reg(0xf65c, 0x10);
					write_reg(0xf600, 0x01);
					fprintf(stderr, "[guard] fix aplicado\n");
				}
			} else if (++fails > 5) {
				/* dispositivo desaparecido: reabrir */
				hid_close(h);
				h = NULL;
				while (!h) {
					struct timespec ts2 = { 2, 0 };
					nanosleep(&ts2, NULL);
					h = hid_open(VID, PID, NULL);
				}
				fails = 0;
			}
			nanosleep(&ts, NULL);
		}
	}
	usage();
	return 0;
}
