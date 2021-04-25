CC = gcc
CFLAGS = -g -O2 -Wall

all:	main gpio_functions

main:	main.o gpio_functions.o
	$(CC) $(LFLAGS) -o project main.o gpio_functions.o

main.o:	main.c
	$(CC) $(CFLAGS) -c main.c

gpio_functions.o:	gpio_functions.c
	$(CC) $(CFLAGS) -c gpio_functions.c

clean:	
	rm -f *~ *.o main
