#ifndef SENSOR_FUNCTIONS_H
#define SENSOR_FUNCTIONS_H
#include <unistd.h>
#include <time.h>
#include "gpio_functions.h"
double get_pulse_width(struct gpiohandle_request *ireq, struct gpiohandle_request *oreq);
#endif

#ifndef USLEEP_ONE_SECOND
#define USLEEP_ONE_SECOND 1000000
#endif
