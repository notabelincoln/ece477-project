CC = gcc
CFLAGS = -g -O2 -Wall

all:	main gpio_functions.o sensor_functions.o

main:	main.o gpio_functions.o sensor_functions.o
	$(CC) $(LFLAGS) -o project main.o gpio_functions.o sensor_functions.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

gpio_functions.o:	gpio_functions.c gpio_functions.h
	$(CC) $(CFLAGS) -c gpio_functions.c

sensor_functions.o:	sensor_functions.c sensor_functions.h
	$(CC) $(CFLAGS) -c sensor_functions.c

clean:	
	rm -f *~ *.o project
