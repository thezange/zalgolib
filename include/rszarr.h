#ifndef RSZARR__H
#define RSZARR__H
#include <stdlib.h>

typedef struct {
	void **data;
	size_t size;
	size_t cap;
} rszarr_t;

rszarr_t *rszarr_alloc();
void rszarr_free(rszarr_t *ra);
/* rszarr_free_all() ? */
int rszarr_push(rszarr_t *ra, void *d);
void *rszarr_pop(rszarr_t *ra);
/* void *rszarr_replace(rszarr_t *ra, size_t i, void *d); replace a val */
void rszarr_swap(rszarr_t *ra, size_t i, size_t j);
/* resize public or private? */

#endif

