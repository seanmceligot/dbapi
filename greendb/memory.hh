#ifndef __MEMORY_HH
#define __MEMORY_HH

#include <stdlib.h>
//#include <gc_cpp.h>
#include "greendb/debug.hh"

void* greendb_malloc (size_t size);
void* greendb_realloc (void *ptr, size_t newsize);
void greendb_free (void *ptr);
//void* gc_malloc (size_t size);

#endif
