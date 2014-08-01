#ifndef __DEBUG_HH
#define __DEBUG_HH

#include <iostream>
#include <glog/logging.h>

using namespace std;

#define debug VLOG(1)

void initLogging(int argc, char** argv);
#endif
