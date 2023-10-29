CC = g++
CFLAGS = -pthread -std=c++11

all: lab4

lab4: lab4.o
	$(CC) $(CFLAGS) lab4.o -o lab4

lab4.o: lab4.cpp
	$(CC) $(CFLAGS) -c lab4.cpp

clean:
	rm -f lab4 lab4.o