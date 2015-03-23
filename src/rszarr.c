#include <string.h>
#include "rszarr.h"
#define RSZARR_MIN_SIZ 8

static int rszarr_resize(rszarr_t *ra, size_t cap);

rszarr_t *rszarr_alloc()
{
	rszarr_t *new = calloc(1, sizeof(rszarr_t));
	if (!new)
		goto exit;
	new->data = calloc(RSZARR_MIN_SIZ, sizeof(void *));
	if (!new->data)
		goto free;
	new->size = 0;
	new->cap = RSZARR_MIN_SIZ;
exit:
	return new;
free:
	free(new->data);
	free(new);
	return NULL;
}

void rszarr_free(rszarr_t *ra)
{
	if (!ra)
		return;
	free(ra->data);
	free(ra);
}

void rszarr_push(rszarr_t *ra, void *d)
{
	if (!ra)
		return;
	if (ra->size >= ra->cap)
		rszarr_resize(ra, ra->cap * 2);
	void **pos = (void **)((char **)ra->data + ra->size);
	*pos = d;
	ra->size++;
}

void *rszarr_pop(rszarr_t *ra)
{
	if (!ra->size)
		return NULL;
	void *rval = *((char **)ra->data + ra->size - 1);
	ra->size--;
	if (ra->size <= ra->cap / 4)
		rszarr_resize(ra, ra->cap / 2);
	return rval;
}

void rszarr_swap(rszarr_t *ra, size_t i, size_t j)
{
	if (!ra)
		return;
	if (i >= ra->size || j >= ra->size)
		return;
	void **iptr = (void **)((char **)ra->data + i);
	void **jptr = (void **)((char **)ra->data + j);
	/* swap */
	void *tmp = *iptr;
	*iptr = *jptr;
	*jptr = tmp;
}

/* static f(x)'s */

/* first try realloc(), if it doesnt work do calloc() and memcpy() */
static int rszarr_resize(rszarr_t *ra, size_t cap)
{
	int rval;
	if (!ra) {
		rval = -1;
		goto error;
	}
	if (cap <= RSZARR_MIN_SIZ) {
		rval = -1;
		goto error;
	}
	void **tmp;
	tmp = realloc(ra->data, cap * sizeof(void *));
	if (tmp) {
		rval = 0;
		goto exit;
	}
	tmp = calloc(cap, sizeof(void *));
	if (!tmp) {
		rval = -1;
		goto error;
	}
	memcpy(tmp, ra->data, cap); 
	free(ra->data);
	rval = 0;
exit:
	ra->data = tmp;
	ra->cap = cap;
error:
	return rval;
}

