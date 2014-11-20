#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "bloom.h"

static const bsize_t type_size = sizeof(bsize_t) * 8;

static inline void set_bit (bsize_t *filter, bsize_t bit);
static inline bsize_t get_bit (bsize_t *filter, bsize_t bit);

bloom_filter_t bloom_init (bsize_t size) {
  bloom_filter_t filter = { 0, size };
  filter.set = calloc(size, sizeof *filter.set);
  return filter;
}

void bloom_add (bloom_filter_t filter, void *key, bloom_func_t f) {
  assert(filter.set != NULL);
  assert(key != NULL);
  assert(f != NULL);

  set_bit(filter.set, f(key, filter.len));
}

void bloom_add_multiple (bloom_filter_t filter, void *key, int num_hashes, ...) {
  assert(filter.set != NULL);
  assert(key != NULL);
  assert(num_hashes > 0);

  va_list hashes;
  va_start(hashes, num_hashes);

  for (int i = 0; i < num_hashes; i++)
    set_bit(filter.set, va_arg(hashes, bloom_func_t)(key, filter.len));

  va_end(hashes);
}

bloom_result_e bloom_query (bloom_filter_t filter, void *key, bloom_func_t f) {
  assert(filter.set != NULL);
  assert(key != NULL);
  assert(f != NULL);

  return get_bit(filter.set, f(key, filter.len));
}

bloom_result_e bloom_query_multiple (bloom_filter_t filter, void *key, int num_hashes, ...) {
  assert(filter.set != NULL);
  assert(key != NULL);
  assert(num_hashes > 0);

  va_list hashes;
  va_start(hashes, num_hashes);

  bloom_result_e res = BLOOM_MAYBE;

  // TODO: stop as soon as one bit is not set
  for (int i = 0; i < num_hashes; i++)
    res = res && get_bit(filter.set, va_arg(hashes, bloom_func_t)(key, filter.len));

  va_end(hashes);

  return res;
}

void bloom_destroy (bloom_filter_t filter) {
  assert(filter.set != NULL);

  free(filter.set);
}

static inline void set_bit (bsize_t *set, bsize_t bit) {
  assert(set != NULL);
  assert(bit >= 0);

  //printf("bit: %lu\nsize: %lu\n", bit, type_size);
  set[bit / type_size] |= 1 << (bit % type_size);
}

static inline bsize_t get_bit (bsize_t *set, bsize_t bit) {
  assert(set != NULL);
  assert(bit >= 0);


  return (set[bit / type_size] & (1 << (bit % type_size))) != 0;
}
