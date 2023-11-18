CC = g++
CFLAGS = -pthread -std=c++11

all: lab4_p1

lab4_p1: lab4_p1.o
	$(CC) $(CFLAGS) lab4_p1.o -o lab4_p1

lab4_p1.o: lab4_p1.cpp
	$(CC) $(CFLAGS) -c lab4_p1.cpp

clean:
	rm -f lab4_p1 lab4_p1.o