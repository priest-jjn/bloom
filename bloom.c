#include <stdlib.h>
#include <assert.h>

#include "bloom.h"

static const bsize_t type_size = sizeof(bsize_t) * 8;

static void set_bit (bsize_t *filter, bsize_t bit);
static bsize_t get_bit (bsize_t *filter, bsize_t bit);

bloom_filter_t bloom_init (bsize_t size) {
  bloom_filter_t filter = { 0, size };
  filter.set = calloc(size, sizeof *filter.set);
  return filter;
}

void bloom_add (bloom_filter_t filter, bloom_func_t f, void *key) {
  assert(filter.set != NULL);
  assert(f != NULL);
  assert(key != NULL);

  set_bit(filter.set, f(key, filter.len));
}

bloom_result_e bloom_contains (bloom_filter_t filter, bloom_func_t f, void *key) {
  assert(filter.set != NULL);
  assert(f != NULL);
  assert(key != NULL);

  return get_bit(filter.set, f(key, filter.len));
}

void bloom_destroy (bloom_filter_t filter) {
  assert(filter.set != NULL);

  free(filter.set);
}

static void set_bit (bsize_t *set, bsize_t bit) {
  assert(set != NULL);
  assert(bit >= 0);

  //printf("bit: %lu\nsize: %lu\n", bit, type_size);
  set[bit / type_size] |= 1 << (bit % type_size);
}

static bsize_t get_bit (bsize_t *set, bsize_t bit) {
  assert(set != NULL);
  assert(bit >= 0);


  return (set[bit / type_size] & (1 << (bit % type_size))) != 0;
}
