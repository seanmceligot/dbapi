#include "greendb/memory.hh"

void
greendb_free (void *ptr)
{
  //debug << "db free:" << ptr << std::endl;
  free (ptr);
}

void *
greendb_malloc (size_t size)
{
  //debug << "db malloc:" << size << std::endl;
  return malloc (size);
}

void *
greendb_realloc (void *ptr, size_t newsize)
{
  //debug << "db realloc:" << ptr << ':' << newsize << std::endl;
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
