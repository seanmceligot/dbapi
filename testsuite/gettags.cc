#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "libcutils/debug.h"

static FILE *in;
static char line[2048];
static int g_verbose_debug = true;

void
close ()
{
  //free (line);
  fclose (in);
}

bool
next_tag (char *func, char *file)
{
  size_t len;
  if (*line == '\0') {
    return false;
  }
  if (!feof_unlocked (in)) {
    ssize_t n = getline ((char **) &line, &len, in);
    if (n > 0) {
      char *ptr = strchr (line, '\t');
      int len = ptr - line;
      strncpy (func, line, len);
      func[len] = 0;
      debugf ("func %s", func);
      ptr++;
      char *ptr2 = strchr (ptr, '\t');
      len = ptr2 - ptr;
      strncpy (file, ptr, len);
      file[len] = 0;
      debugf ("file %s", file);
      return true;
    }
  }
  close ();
  return false;
}

bool
init_tags (const char *fname)
{
  size_t len;
  //line = (char *) malloc (1024);
  in = fopen (fname, "r");
  while (!feof_unlocked (in)) {
    long int start = ftell (in);
    ssize_t n = getline ((char **) &line, &len, in);
    if (n <= 0) {
      break;
    }
    if (*line != '!') {
      fseek (in, start, SEEK_SET);
      return true;
    }
  }
  close ();
  return false;
}

int
main (int argc, char **argv)
{
  FILE *in = fopen ("tags", "r");
  char func[256];
  char file[256];
  init_tags ("tags");
  while (next_tag (func, file)) {
    ;
  }
}
