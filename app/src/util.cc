#include "util.hh"

const char* next_word(const char* text) {
  while(*text) {
    if (*text == ' ') {
      while(*text) {
        if (*text != ' ') {
          return text;
        }
        text++;
      }
    }
    text++;
  }
  return text;
}
StrQueue* split_words(const char* str) {
  StrQueue* words = new StrQueue();
  int len;
  for(;;) {
    char* pos;
    pos = strchr(str, ' ');
    if (pos) {
      len = pos-str;
      pos++;
    } else {
      len = strlen(str);
      if (!len) {
        break;
      }
    }
    while( (pos && (*pos == ' '))) {
      pos++;
    }
    char* word = new char[len+1];
    strncpy(word, str, len);
    word[len] = 0;
    words->push(word);
    if (!pos) {
      break;
    }
    str = pos;
  }
  return words;
}

#ifdef NEXT_TEST
#include <iostream>
int main(int argc, char** args) {
  std::cout <<'\"'<<next_word(args[1])<<'\"'<<std::endl;
  return 0;
}
#endif

#ifdef SPLIT_TEST
#include <iostream>
int main(int argc, char** args) {
  StrQueue* words = split_words(args[1]);
  while(!words->empty()) {
    std::cout <<'\"'<<words->front()<<'\"'<<std::endl;
    words->pop();
  }
  return 0;
}
#endif


