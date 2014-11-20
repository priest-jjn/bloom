#include <stdio.h>
#include <stdint.h>

#include "bloom.h"

extern uint32_t murmur3_32 (const char *, uint32_t, uint32_t);
bsize_t hash1 (void *key, bsize_t len);

int main () {
  bloom_filter_t filter = bloom_init(16);
  bloom_add(filter, hash1, "max");
  printf("contains max? %d\n", bloom_contains(filter, hash1, "max"));
  printf("contains joe? %d\n", bloom_contains(filter, hash1, "joe"));
  bloom_destroy(filter);
}

bsize_t hash1 (void *key, bsize_t len) {
  return (bsize_t) murmur3_32((const char *) key, (uint32_t) len, 0x777) % len;
}
