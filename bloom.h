#ifndef BLOOM_H
#define BLOOM_H

#include <stdlib.h>

typedef size_t bsize_t;
typedef enum { BLOOM_NO, BLOOM_MAYBE } bloom_result_e;
typedef struct bloom_filter_s {
  bsize_t *set;
  size_t len;
} bloom_filter_t;
typedef bsize_t (*bloom_func_t) (void *key, bsize_t len);

bloom_filter_t bloom_init (bsize_t size);
void bloom_add (bloom_filter_t filter, bloom_func_t f, void *key);
bloom_result_e bloom_contains (bloom_filter_t filter, bloom_func_t f, void *key);
void bloom_destroy (bloom_filter_t filter);

#endif
