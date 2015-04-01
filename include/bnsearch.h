#ifndef BNSEARCH__H 
#define BNSEARCH__H 
#include <stdlib.h>

void *bnsearch(const void *, const void *, size_t, size_t,
               int (*)(const void *, const void *));

#endif

