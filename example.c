#include <stdio.h>
#include <stdint.h>

#include "lib/fnv.h"
#include "bloom.h"

extern uint32_t murmur3_32 (const char *, uint32_t, uint32_t);
extern Fnv32_t fnv_32_str (char *str, Fnv32_t hval);

bsize_t hash1 (void *key, bsize_t len);
bsize_t hash2 (void *key, bsize_t len);

int main () {
  bloom_filter_t filter = bloom_init(16);
  bloom_add_multiple(filter, "max", 2, hash1, hash2);

  printf("query max? %d\n",
	 bloom_query_multiple(filter, "max", 2, hash1, hash2));

  printf("query joe? %d\n",
	 bloom_query_multiple(filter, "joe", 2, hash1, hash2));

  bloom_destroy(filter);
}

bsize_t hash1 (void *key, bsize_t len) {
  return (bsize_t) murmur3_32((const char *) key, (uint32_t) len, 0x777) % len;
}

bsize_t hash2 (void *key, bsize_t len) {
  return (bsize_t) fnv_32_str((char *) key, (Fnv32_t) len) % len;
}
