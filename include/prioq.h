#ifndef PRIOQ__H
#define PRIOQ__H
#include <stdlib.h>

typedef struct {
	void **heap;
	size_t size;
	size_t capacity;
	/* cmp f(x) */
} prioq_t;

prioq_t *prioq_alloc(/* cmp */);
void prioq_free(prioq_t *pq);
void prioq_insert(prioq_t *pq, void *v);

#endif
