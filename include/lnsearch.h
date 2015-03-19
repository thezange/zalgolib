#ifndef LNSEARCH__H 
#define LNSEARCH__H
#include <stdlib.h>

void *lnsearch(const void *, const void *, size_t, size_t,
               int (*)(const void *, const void *));

#endif
