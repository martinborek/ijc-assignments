# GNU makefile pro IJC-DU1, 20.3.2012
# Autor: Martin Borek (xborek08), FIT

CC=gcc 
CFLAGS= -O2 -std=c99 -Wall -pedantic


all: prvocisla prvocisla-inline steg-decode

prvocisla: prvocisla.o eratosthenes.o error.o
	$(CC) $(CFLAGS) prvocisla.o eratosthenes.o error.o -lm -o prvocisla

prvocisla-inline: prvocisla-inline.o eratosthenes-inline.o error.o
	$(CC) $(CFLAGS) prvocisla-inline.o eratosthenes-inline.o error.o -lm -o prvocisla-inline

steg-decode: steg-decode.o ppm.o eratosthenes.o error.o
	$(CC) $(CFLAGS) steg-decode.o ppm.o eratosthenes.o error.o -lm -o steg-decode


eratosthenes.o: eratosthenes.c eratosthenes.h bit-array.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c

eratosthenes-inline.o: eratosthenes.c eratosthenes.h bit-array.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c -DUSE_INLINE -o eratosthenes-inline.o

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c

steg-decode.o: steg-decode.c bit-array.h ppm.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -c steg-decode.c

prvocisla.o: prvocisla.c bit-array.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -c prvocisla.c

prvocisla-inline.o: prvocisla.c bit-array.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -c prvocisla.c -DUSE_INLINE -o prvocisla-inline.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

clean: 
	rm -f *.o
