#ifndef __UTIL_HH
#define __UTIL_HH

#include <queue>
#include <cstring>

struct eqstr
{
    bool operator()(const char* s1, const char* s2) const { 
      return strcmp(s1, s2) == 0;
    }
};
struct ltstr {
    bool operator()(const char* s1, const char* s2) const {
       return strcmp(s1, s2) < 0;
    }
};

typedef std::queue<char*> StrQueue;

StrQueue* split_words(const char* str);
const char* next_word(const char* str);
#endif
