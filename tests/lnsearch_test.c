#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "lnsearch.h"

int intcmp(const void *key, const void *array)
{
	int k = *(int *)key;
	int a = *(int *)array;
	if (k > a)
		return 1;
	else if (k < a)
		return -1;
	else
		return 0;
}

int main()
{
	size_t arraysize = 1000000;
	int key = 545000;
	int i = 0;
	int *vpos = NULL;
	int rval;
	/* create array that we will search through */
	int *incrnums = calloc(arraysize, sizeof(int));
	if (!incrnums) {
		fprintf(stderr, "calloc() error: %s\n", strerror(errno));
		rval = -1;
		goto exit;
	}
	for (i = 0; i < arraysize; i++)
		incrnums[i] = i;
	/* perform linear search */
	vpos = lnsearch(&key, incrnums, arraysize, sizeof(int), intcmp);
	if (vpos == NULL) {
		fprintf(stderr, "lnsearch() error: function returned "
				"NULL\n");
		rval = -1;
		goto exit;
	} else {
		printf("lnsearch() success: value is: %d\n", *vpos);
	}
	rval = 0;
exit:
	free(incrnums);
	return rval;
}

