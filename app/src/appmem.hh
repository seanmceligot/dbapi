#ifndef __APPMEM_HH
#define __APPMEM_HH

#include <malloc.h>
//#include <gc_cpp.h>

void* greenapp_malloc (size_t size);
void* greenapp_realloc (void *ptr, size_t newsize);
void greenapp_free (void *ptr);
//void* gc_malloc (size_t size);

#endif
