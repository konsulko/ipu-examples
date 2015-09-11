#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/mxcfb.h>

int main (int argc, char *argv[])
{
	struct mxcfb_gbl_alpha g_alpha;
	struct timeval begin, end;

	int sec, usec, run_time;
	int fd;
	int ret, i = 0;
	int offset = 1;
 
	// Clear &g_alpha
	memset(&g_alpha, 0, sizeof(g_alpha));
 
	g_alpha.alpha = 128;
	g_alpha.enable = 1;

	// Open fb device
	fd = open("/dev/fb0", O_RDWR, 0);
	if (fd < 0) {
		printf("open fbdev fail\n");
		ret = -1;
		goto done;
	}

	while (1) {
		g_alpha.alpha = i;

		// Adjust global alpha
		ret = ioctl(fd, MXCFB_SET_GBL_ALPHA, &g_alpha);
		if (ret < 0) {
			printf("Set global alpha failed: %x\n", ret);
			goto done;
		}
	 
		usleep(25000);

		/* If at end of range start decrementing, else if we
		   are at the beginning of range start incrementing */
		if (i == 255) {
			printf("Max alpha, decreasing\n");
			offset = -1;
		} else if (i == 0) {
			printf("Min alpha, increasing\n");
			offset = 1;
		}

		i += offset;
	}
 
done:
	if (fd)
		close(fd);

	return ret;
}

