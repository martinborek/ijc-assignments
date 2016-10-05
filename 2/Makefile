#
# Makefile 
# IJC-DU2, 24.4.20012
# Autor: Martin Borek (xborek08), FIT
#

CFLAGS=-std=c99 -Wall -pedantic -g
CXXFLAGS=-std=c++98 -Wall -pedantic
CC=gcc

LIBFILES=hash_function.o htable_clear.o htable_foreach.o htable_free.o htable_init.o htable_lookup.o htable_remove.o

all: tail tail2 wordcount
	
dynamic: wordcount-dynamic


tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail

tail2: tail2.o
	g++ $(CXXFLAGS) tail2.o -o tail2

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c

tail2.o: tail2.cc
	g++ $(CXXFLAGS) -c tail2.cc


wordcount: wordcount.o io.o libhtable.a
	$(CC) $(CFLAGS) -o wordcount -static io.o wordcount.o libhtable.a

wordcount-dynamic: wordcount.o io.o libhtable.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o libhtable.so
	

libhtable.a: $(LIBFILES)
	ar crs libhtable.a $(LIBFILES)
	
libhtable.so: $(LIBFILES)
	$(CC) $(CFLAGS) -shared -o libhtable.so $(LIBFILES)


LIBFILES=hash_function.o htable_clear.o htable_foreach.o htable_free.o htable_init.o htable_lookup.o htable_remove.o

hash_function.o: hash_function.c
	$(CC) $(CFLAGS) -c -fPIC hash_function.c
htable_clear.o: htable_clear.c
	$(CC) $(CFLAGS) -c -fPIC htable_clear.c
htable_foreach.o: htable_foreach.c
	$(CC) $(CFLAGS) -c -fPIC htable_foreach.c
htable_free.o: htable_free.c
	$(CC) $(CFLAGS) -c -fPIC htable_free.c
htable_init.o: htable_init.c
	$(CC) $(CFLAGS) -c -fPIC htable_init.c
htable_lookup.o: htable_lookup.c
	$(CC) $(CFLAGS) -c -fPIC htable_lookup.c
htable_remove.o: htable_remove.c
	$(CC) $(CFLAGS) -c -fPIC htable_remove.c


##########################################################

clean: 
	rm -f *.o
