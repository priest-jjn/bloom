CC ?= gcc

CFLAGS = -std=c99 -g3
SRCS = bloom.c
HASHES = lib/murmur3.c lib/fnv.c lib/lookup3.c
OBJS = *.o
ARCHIVE = libbloom.a

all:
	$(CC) $(CFLAGS) -c $(SRCS) $(HASHES)
	ar cr $(ARCHIVE) $(OBJS)
	rm *.o

example:
	$(CC) $(CFLAGS) example.c $(SRCS) $(HASHES)

clean:
	rm -rf *.out *.dSYM *.o *.a
