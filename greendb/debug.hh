#ifndef __DEBUG_HH
#define __DEBUG_HH
#include <fstream>

extern std::ofstream<char> debugf;

#ifndef NDEBUG
#include <iostream>
//#define debug debugf<<__FILE__<<' '<<__LINE__<<':'
//#define error debugf<<__FILE__<<' '<<__LINE__<<':'
//#define fatal debugf<<__FILE__<<' '<<__LINE__<<':'
#define debug std::cerr<<__FILE__<<' '<<__LINE__<<':'
#define error std::cerr<<__FILE__<<' '<<__LINE__<<':'
#define fatal std::cerr<<__FILE__<<' '<<__LINE__<<':'
#else
// unfinished
#define Debug::debug (void*)0
#define Debug::error (void*)0
#define Debug::fatal (void*)0
#endif

#endif
