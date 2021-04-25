#include "sensor_functions.h"
double get_pulse_width(struct gpiohandle_request *ireq, struct gpiohandle_request *oreq)
{
	float pulse_width;
	clock_t clock_initial, clock_final;

	gpio_write(oreq, 1);
	usleep(10);
	gpio_write(oreq, 0);
	while (!gpio_read(ireq));
	clock_initial = clock();
	while (gpio_read(ireq));
	clock_final = clock();
	pulse_width = (double)(clock_final - clock_initial) / CLOCKS_PER_SEC * USLEEP_ONE_SECOND;
	return pulse_width;
}
