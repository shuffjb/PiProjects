#
#
# Author: John Shufflebarger
#
# email: shuffjb@gmail.com
#
#

CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -Wformat-nonliteral -Wformat-security -Wtype-limits -O2
objects = PiTimeServer.o rs232.o

PiTimeServer :	$(objects)
	$(CC) $(CFLAGS) $(objects) -o PiTimeServer	

PiTimeServer.o :	PiTimeServer.h PiTimeServer.cpp rs232.h rs232.c
	$(CC) $(CFLAGS) -c PiTimeServer.cpp -o PiTimeServer.o

rs232.o : rs232.h rs232.c
	$(CC) $(CFLAGS) -c rs232.c -o rs232.o

clean :
	$(RM) test_rx test_tx $(objects) demo_rx.o demo_tx.o rs232.o

#
#
#
#





