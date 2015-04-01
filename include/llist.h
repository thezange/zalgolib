#ifndef LLIST__H
#define LLIST__H
#include "lnode.h"

typedef struct {
	lnode *first;
	lnode *last;
	unsigned int count;
	/* function pointer for cmp() */
} llist;

llist *llist_alloc(/* function ptr here */);
void llist_free(llist *ll);
/* FUNCTIONS TO IMPLEMENT:
 * search() - just returns data
 * rsearch() - search from back to front
 * d(r)search() - not sure if i should do this: search and delete
 * insert_front()
 * insert_back()
 * delete_front()
 * delete_rear()
 * isempty()
 */

#endif

