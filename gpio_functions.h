/* Abe Jordan
 * ECE 477
 * Project
 * gpio_functions.h
 * Provides function declarations for configuring gpios
 */
#ifndef GPIO_FUNCTIONS_H
#define GPIO_FUNCTIONS_H
#include "linux/gpio.h"
#include "sys/ioctl.h"

// configure GPIO as either read or write with consumer label
struct gpiohandle_request gpio_setup(unsigned int gpio_num, char *consumer_label, char gpio_mode);

// read from gpio pin
int gpio_read(struct gpiohandle_request *req);

// write to gpio pin
int gpio_write(struct gpiohandle_request *req, int set_value);
#endif
