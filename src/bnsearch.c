#include <stdlib.h>

/*
 * This function performs a binary search on a set of sorted data
 * pointed to by base, using cmp; bnsearch assumes that cmp(x1, x2)
 * returns an integer in this manner: positive if x1 > x2,
 * negative if x1 < x2, and zero if x1 == x2.
 *
 * Order O(lg N)
 */
void *bnsearch(const void *key, const void *base, size_t nmemb,
	       size_t size, int (*cmp)(const void *, const void *))
{
	unsigned int i = 0;
	unsigned int k = nmemb - 1;
	unsigned int j = (i + k) / 2;
	int cmpr;
	void *start = (char *)base;
	while (k >= i) {
		j = (i + k) / 2;
		if ((cmpr = cmp(key, start+size*j)) == 0)
			return start+size*j;
		else if (cmpr > 0)
			i = j + 1;
		else
			k = j - 1;
	}
	return NULL; 
}
