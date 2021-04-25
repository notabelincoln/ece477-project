/* Abe Jordan
 * ECE 477
 * Project
 * main.c
 */
#include "sensor_functions.h"

int main(int argc, char **argv)
{
	struct gpiohandle_request ireq;
	struct gpiohandle_request oreq;
	double pulse_width;
	ireq = gpio_setup(17, "ECE477 Input", GPIOHANDLE_REQUEST_INPUT);
	oreq = gpio_setup(18, "ECE 477 Output", GPIOHANDLE_REQUEST_OUTPUT);

	while(1) {
		pulse_width = get_pulse_width(&ireq, &oreq);
		printf("distance = %04.1lf cm\n", pulse_width / 58);
		usleep(USLEEP_ONE_SECOND - pulse_width);
	}

	return 0;
}


