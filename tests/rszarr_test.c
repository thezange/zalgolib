#include <stdio.h>
#include "rszarr.h"
typedef struct {
	int data;
} test_struct;

int main(int argc, char *argv[])
{
	int rval;
	int i;
	test_struct *cur;
	test_struct *ptr;
	/* testing allocation */
	rszarr_t *ra = rszarr_alloc();
	if (!ra) {
		fprintf(stderr, "rszarr_alloc() error: function returned "
				"NULL\n");
		rval = -1;
		goto exit;
	}
	printf("rszarr_alloc() success\n");
	for (i = 0; i < 20; i++) {
		cur = calloc(1, sizeof(test_struct));
		cur->data = i * 10;
		rszarr_push(ra, cur);
	}
	/* testing pop() */
	while (ra->size > 0) {
		cur = rszarr_pop(ra);
		if (!cur) {
			fprintf(stderr, "rszarr_pop() error: function "
					"returned NULL\n");
			rval = -1;
			goto exit;
		}
		free(cur);
	}
	printf("rszarr_pop() success\n");
	cur = calloc(1, sizeof(test_struct));
	cur->data = 5;
	rszarr_push(ra, cur);
	cur = calloc(1, sizeof(test_struct));
	cur->data = 12;
	rszarr_push(ra, cur);
	/* testing swap (depends on pop for now) */
	rszarr_swap(ra, 0, 1);
	cur = rszarr_pop(ra);
	ptr = rszarr_pop(ra);
	if (cur->data != 5 || ptr->data != 12) {
		fprintf(stderr, "rszarr_swap() error\n");
		rval = -1;
		goto exit;
	}
	printf("rszarr_swap() success\n");
	rval = 0;
exit:
	rszarr_free(ra);
	return rval;
}

