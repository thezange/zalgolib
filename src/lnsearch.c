#include <stdlib.h>

/*
 * This function performs a linear search on a set of sorted data
 * pointed to by base, using cmp; lnsearch assumes that cmp(x1, x2)
 * returns an integer in this manner: positive if x1 > x2,
 * negative if x1 < x2, and zero if x1 == x2.
 *
 * Order O(N)
 */
void *lnsearch(const void *key, const void *base, size_t nmemb,
	       size_t size, int (*cmp)(const void *, const void *))
{
	int i = 0;
	void *start = (char *)base;
	for (i = 0; i < nmemb; i++)
		if (cmp(key, start+size*i) == 0)
			return start+size*i;
	return NULL; 
}
