#include <set>
#include "util.hh"
#include "appmem.hh"

class Completions {
  typedef std::set < const char *, ltstr >StringSet;
  StringSet* _completions;
  static Completions* _instance;
public:
  Completions();
  const char* complete(const char* text)  const;
  static StringSet* make_vector(const char* ss[]);
  static Completions* get_instance();
};

