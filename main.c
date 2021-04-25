// Abe Jordan
// ECE 477
// Project
// main.c
// Code initially taken from ECE 471 homework 4
#include <stdio.h>
#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>
#include <errno.h>
#include "linux/gpio.h"
#include "sys/ioctl.h"

int main(int argc, char **argv) {
	/* variables for handling GPIO */
	int fd, rv;
	struct gpiohandle_request req;
	struct gpiohandle_data data;
	
	fd = open("/dev/gpiochip0",O_RDWR);
	if (fd < 0) printf("Error opening %s\n", strerror(errno));

	/* ensure that no unwanted values are set in the memory for data*/
	memset(&req, 0, sizeof(struct gpiohandle_request));
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	req.lines = 1;
	req.lineoffsets[0] = 18; // access GPIO18
	req.default_values[0] = 0; // make gpio18 low by default
	strcpy(req.consumer_label, "ECE471");
	rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
	if (rv < 0) printf("Error ioctl %s\n", strerror(errno));

	/* toggle LED every 0.5 seconds at rate of 1 hz */
	while(1) {
		data.values[0]=0;
		rv = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (rv < 0) printf("Error setting value %s\n", strerror(errno));
		usleep(500000);


		data.values[0] = 1;
		rv=ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (rv < 0) printf("Error settting value %s\n", strerror(errno));
		usleep(500000);
	}
	return 0;
}

