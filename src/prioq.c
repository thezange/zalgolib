#include "prioq.h"
#include <stdio.h>

static void prioq_swim(prioq_t *pq, size_t k);
static void prioq_sink(prioq_t *pq, size_t k);

prioq_t *prioq_alloc(cmp_t cmp)
{
	prioq_t *new = NULL;
	rszarr_t *ra = NULL;
	if (!cmp)
		goto exit;
	new = calloc(1, sizeof(prioq_t));
	if (!new)
		goto exit;
	ra = rszarr_alloc();
	if (!ra)
		goto free;
	new->heap = *ra;
	free(ra);
	rszarr_push((rszarr_t *)new, NULL);
	new->cmp = cmp;
	new->hsiz = 0;
exit:
	return new;
free:
	free(new);
	return NULL;
}

void prioq_free(prioq_t *pq)
{
	rszarr_free((rszarr_t *)pq);
}

void prioq_insert(prioq_t *pq, void *v)
{
	size_t pos;
	if (!pq || !v)
		return;
	pos = pq->heap.size;
	if (rszarr_push((rszarr_t *)pq, v) < 0)
		return;
	prioq_swim(pq, pos);
	pq->hsiz++;
}

void *prioq_extract(prioq_t *pq)
{
	void *rval = NULL;
	if (!pq->hsiz)
		goto exit;
	rszarr_swap((rszarr_t *)pq, 1, pq->hsiz);
	rval = rszarr_pop((rszarr_t *)pq);
	pq->hsiz--;
	prioq_sink(pq, 1);
exit:
	return rval;
}

void *prioq_peek(prioq_t *pq)
{
	void *rval = NULL;
	if (!pq->hsiz)
		goto exit;
	rval = *((char **)pq->heap.data + 1);
exit:
	return rval;
}

/* static f(x)'s */
static void prioq_swim(prioq_t *pq, size_t k)
{
	char **pos = (char **)pq->heap.data;
	while (k > 1 && pq->cmp((void *)pos[k],
				(void *)pos[k / 2]) < 0) {
		rszarr_swap((rszarr_t *)pq, k, k / 2);
		k = k / 2;
	}
}

static void prioq_sink(prioq_t *pq, size_t k)
{
	int j;
	char **pos = (char **)pq->heap.data;
	while (2 * k <= pq->hsiz) {
		j = 2 * k;
		if (j < pq->hsiz && pq->cmp((void *)pos[j + 1],
					    (void *)pos[j]) < 0)
			j++;
		if (pq->cmp((void *)pos[k], (void *)pos[j]) <= 0)
			break;
		rszarr_swap((rszarr_t *)pq, k, j);
		k = j;
	}
}

