/* Abe Jordan
 * ECE 477
 * Project
 * gpio_functions.c
 * Code originally based off ECE 471 homework 4
 * Provides code for configuring GPIOs
 */
#include "gpio_functions.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

// configure GPIO as either read or write with consumer label
int gpio_setup(unsigned int gpio_num, char *consumer_label, char gpio_mode)
{
	/* variables for handling GPIO */
	int fd, rv;
	struct gpiohandle_request req;
	
	/* ensure that no unwanted values are set in the memory for data*/
	memset(&req, 0, sizeof(struct gpiohandle_request));

	fd = open("/dev/gpiochip0",O_RDWR);
	if (fd < 0)
		return errno;

	/* configure basic gpio attributes */
	req.flags = gpio_mode;
	req.lines = 1;
	req.lineoffsets[0] = gpio_num; // wanting to read gpio17
	strcpy(req.consumer_label, consumer_label);

	if (gpio_mode == GPIOHANDLE_REQUEST_OUTPUT)
		req.default_values[0] = 0;

	rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
	if (rv < 0)
		return errno;
}

// read from gpio pin
int gpio_read(struct gpiohandle_request req)
{
	int rv;
	struct gpiohandle_data data;

	/* ensure no unwanted values are set */
	memset(&data, 0, sizeof(data));

	/* read data from gpio pin */
	rv = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
	if (rv < 0) return errno;

	return data.values[0];
}

// write to gpio pin
int gpio_write(struct gpiohandle_request req, int set_value)
{
	int rv;
	struct gpiohandle_data data;

	// write value to gpio pin
	data.values[0] = set_value;
	rv = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
	if (rv < 0) 
		return errno;

	return 0;
}
