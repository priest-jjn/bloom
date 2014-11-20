all:
	gcc -std=c99 -g3 example.c bloom.c lib/murmur3.c lib/fnv.c
