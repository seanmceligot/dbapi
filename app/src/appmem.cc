#include "appmem.hh"

void
greenapp_free (void *ptr)
{
  //debug << "db free:" << ptr << std::endl;
  //GC_free (ptr);
  free(ptr);
}

void *
greenapp_malloc (size_t size)
{
  //debug << "db malloc:" << size << std::endl;
  //return GC_malloc (size);
  return malloc(size);
}

void *
greenapp_realloc (void *ptr, size_t newsize)
{
  //debug << "db realloc:" << ptr << ':' << newsize << std::endl;
  //return GC_realloc (ptr, newsize);
  return realloc (ptr, newsize);
}
/*
void *
gc_malloc (size_t size)
{
  debug << "gc malloc:" << size << std::endl;
  return GC_malloc (size);
}
*/
