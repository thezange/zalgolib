#include "prioq.h"
#define HEAP_MIN 16

prioq_t *prioq_alloc()
{
	prioq_t *new = calloc(1, sizeof(prioq_t));
	new->heap = calloc(HEAP_MIN, sizeof(void *));
	new->capacity = HEAP_MIN;
	new->size = 1;

	return new;
}

void prioq_free(prioq_t *pq)
{
	if (pq)
		free(pq->heap);
	free(pq);
}

void prioq_insert(prioq_t *pq, void *v)
{
	if (!pq || !v)
		return;
	if (pq->size >= pq->capacity){}
		//prioq_resize(pq);
	pq->heap[pq->size] = v;
}

