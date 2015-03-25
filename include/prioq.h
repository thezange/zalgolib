#ifndef PRIOQ__H
#define PRIOQ__H
#include "rszarr.h"

typedef int (*cmp_t)(void *, void *);

typedef struct {
	rszarr_t heap;
	size_t hsiz;
	cmp_t cmp;
} prioq_t;

prioq_t *prioq_alloc(cmp_t cmp);
void prioq_free(prioq_t *pq);
void prioq_insert(prioq_t *pq, void *v);
void *prioq_extract(prioq_t *pq);
void *prioq_peek(prioq_t *pq);

#endif
