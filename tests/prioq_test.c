#include <stdio.h>
#include "prioq.h"
typedef struct {
	int data;
} test_struct;

int test_cmp(void *t1, void *t2)
{
	test_struct *ts1 = (test_struct *)t1;
	test_struct *ts2 = (test_struct *)t2;
	if (ts1->data < ts2->data)
		return -1;
	if (ts1->data == ts2->data)
		return 0;
	else
		return 1;
}

int main(int argc, char *argv[])
{
	int rval;
	int i;
	int n;
	test_struct *cur = NULL;
	prioq_t *pq = NULL;
	int nums[] = {79, 55, 43, 37, 21, 12, 8, 3, 1};
	n = sizeof(nums) / sizeof(int);
	/* testing allocation */
	pq = prioq_alloc(test_cmp);
	if (!pq) {
		fprintf(stderr, "prioq_alloc() error: function returned "
				"NULL\n");
		rval = -1;
		goto exit;
	}
	printf("prioq_alloc() success\n");
	for (i = 0; i < n; i++) {
		cur = calloc(1, sizeof(test_struct));
		cur->data = nums[i];
		prioq_insert(pq, cur);
	}
	printf("prioq_insert() success\n");
	/* testing extract() */
	i = n - 1;
	while (pq->hsiz > 0) {
		cur = prioq_extract(pq);
		if (!cur) {
			fprintf(stderr, "prioq_extract() error: function "
					"returned NULL\n");
			rval = -1;
			goto exit;
		}
		if (cur->data != nums[i]) {
			fprintf(stderr, "prioq_extract() error: function "
					"returned values in wrong order\n");
		}
		i--;
		free(cur);
	}
	printf("prioq_extract() success\n");
	rval = 0;
exit:
	return rval;
}
