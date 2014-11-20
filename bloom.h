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
void bloom_add (bloom_filter_t filter, void *key, bloom_func_t f);
void bloom_add_multiple (bloom_filter_t filter, void *key, int num_hashes, ...);
bloom_result_e bloom_query (bloom_filter_t filter, void *key, bloom_func_t f);
bloom_result_e bloom_query_multiple (bloom_filter_t filter, void *key, int num_hashes, ...);
void bloom_destroy (bloom_filter_t filter);

#endif
