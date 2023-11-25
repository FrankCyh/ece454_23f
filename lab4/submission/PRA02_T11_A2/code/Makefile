CC = g++
CFLAGS = -pthread -g -std=c++11

all: coarse_or_fine_grained_lock spin_lock

coarse_or_fine_grained_lock: coarse_or_fine_grained_lock.o
	$(CC) $(CFLAGS) coarse_or_fine_grained_lock.o -o coarse_or_fine_grained_lock

coarse_or_fine_grained_lock.o: coarse_or_fine_grained_lock.cpp
	$(CC) $(CFLAGS) -c coarse_or_fine_grained_lock.cpp

spin_lock: spin_lock.o
	$(CC) $(CFLAGS) spin_lock.o -o spin_lock

spin_lock.o: spin_lock.cpp
	$(CC) $(CFLAGS) -c spin_lock.cpp

clean:
	rm -f coarse_or_fine_grained_lock coarse_or_fine_grained_lock.o