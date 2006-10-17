#ifndef __DEBUG_HH
#define __DEBUG_HH
// ## rlog
#include <rlog/rlog.h>
#include <rlog/rloglocation.h>
#include <rlog/RLogChannel.h>
#include <rlog/RLogTime.h>
#include <rlog/StdioNode.h>

#include <iostream>

using namespace rlog;
using namespace std;

void initLogging(int argc, char** argv);
#endif
