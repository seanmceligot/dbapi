#include "greendb/memory.hh"

void
greendb_free (void *ptr)
{
  free (ptr);
}

void *
greendb_malloc (size_t size)
{
  return malloc (size);
}

void *
greendb_realloc (void *ptr, size_t newsize)
{
  return realloc (ptr, newsize);
}
/*
void *
gc_malloc (size_t size)
{
  return GC_malloc (size);
}
*/
