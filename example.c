#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bloom.h"
#include "lib/fnv.h"

extern uint32_t murmur3_32 (const char *, uint32_t, uint32_t);
extern Fnv32_t fnv_32_str (char *str, Fnv32_t hval);
extern uint32_t hashlittle (const void *, size_t, uint32_t);

static const bsize_t magic_number = 0x777;

void add (bloom_filter_t filter, void *key);
bloom_result_e query (bloom_filter_t filter, void *key);

bsize_t hash1 (void *key, bsize_t len);
bsize_t hash2 (void *key, bsize_t len);
bsize_t hash3 (void *key, bsize_t len);

int main () {
  bloom_filter_t filter = bloom_init(16);
  add(filter, "chris");
  add(filter, "gregg");
  add(filter, "is");
  add(filter, "mayonnaise");

  printf("query chris? %d\n",
	 query(filter, "chris"));

  printf("query gregg? %d\n",
	 query(filter, "gregg"));

  printf("query is? %d\n",
	 query(filter, "is"));

  printf("query mustard? %d\n",
	 query(filter, "mustard"));

  bloom_destroy(filter);
}

void add (bloom_filter_t filter, void *key) {
  bloom_add_multiple(filter, key, 3, hash1, hash2, hash3);
}

bloom_result_e query (bloom_filter_t filter, void *key) {
  return bloom_query_multiple(filter, key, 3, hash1, hash2, hash3);
}

bsize_t hash1 (void *key, bsize_t len) {
  return (bsize_t) murmur3_32((const char *) key,
			      (uint32_t) len,
			      magic_number) % len;
}

bsize_t hash2 (void *key, bsize_t len) {
  return (bsize_t) fnv_32_str((char *) key,
			      (Fnv32_t) len) % len;
}

bsize_t hash3 (void *key, bsize_t len) {
  return (bsize_t) hashlittle((const void *) key,
			      strlen((const char *) key),
			      magic_number) % len;
}
