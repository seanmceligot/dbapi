#include <cstddef>
#include <iostream>
#include "complete.hh"
#include "widgets.hh"

const char* top_completions[] = { "load-table", "add-row", "create-table", "schema-add-column", NULL};
Completions* Completions::_instance = NULL;

Completions::Completions() {
  _completions = make_vector(top_completions);
}

Completions::StringSet* Completions::make_vector(const char* ss[]) {
  StringSet* list = new StringSet();
  while(*ss!= NULL) {
    list->insert(*ss);
    ss++;
  }
  return list;
}

const char* Completions::complete(const char* text) const {
   std::cout <<"complete: "<<text<<std::endl;
  char* word_ptr = strchr(text, ' ');
  size_t text_len;
  if (word_ptr) {
    text_len = word_ptr - text;
  } else {
    text_len = strlen(text);
  }
  int matches = 0;
  char* match = NULL;
  for(StringSet::iterator it = _completions->begin(); it != _completions->end(); it++) {
    const char* item = *it;
    std::cout <<"test: "<<item<<std::endl;
    size_t item_len = strlen(item);
    if (text_len < item_len) {
      if (strncmp(item, text, text_len) == 0) {
        if (!matches) {
          match = (char*)item;
        }
        matches++;
        if (matches == 2) {
          break;
        }
      }
    }
  }
  std::cout<<matches<<" matches"<<std::endl;
  if (matches == 1) {
    return match;
  }
  return NULL;
}
Completions* Completions::get_instance() {
  if (_instance == NULL) {
    _instance = new Completions();
  }
  return _instance;
}
