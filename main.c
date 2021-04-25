/* Abe Jordan
 * ECE 477
 * Project
 * main.c
 */
#include "gpio_functions.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void pulse(struct gpiohandle_request req, unsigned int frequency, unsigned int duty_cycle);

int main(int argc, char **argv)
{
	int gpiov;
	struct gpiohandle_request ireq;
	struct gpiohandle_request oreq;
	clock_t clock_initial, clock_final;
	double pulse_width;
	ireq = gpio_setup(17, "ECE477 Input", GPIOHANDLE_REQUEST_INPUT);
	oreq = gpio_setup(18, "ECE 477 Output", GPIOHANDLE_REQUEST_OUTPUT);

	while(1) {
		gpio_write(&oreq, 1);
		usleep(10);
		gpio_write(&oreq, 0);
		while (!gpio_read(&ireq));
		clock_initial = clock();
		while (gpio_read(&ireq));
		clock_final = clock();
		pulse_width = (double)(clock_final - clock_initial)/CLOCKS_PER_SEC*1000000;
		printf("distance = %lf cm, clock_initial = %lu, clock_final = %lu\n",
				pulse_width / 58,
				(long unsigned int)clock_initial,
				(long unsigned int)clock_final);
		usleep(1000000 - pulse_width);
	}

	return 0;
}


