#ifndef LNODE__H
#define LNODE__H

typedef struct lnode lnode;
typedef struct {
	lnode *next;
	lnode *prev;
	void *data;
} lnode;

#endif

