#include "greendb/debug.hh"
#include <stdio.h>


//std::ofstream<char> debugf("greendb.log");
void initLogging(int argc, char** argv) {
	//RLogInit( argc, argv );
//  StdioNode stdLog(2,1|2|4|8 );
//:w
//stdLog.subscribeTo( GetGlobalChannel("") );

    //stdLog.subscribeTo( RLOG_CHANNEL("debug") );
    //stdLog.subscribeTo( GetGlobalChannel("warning") );
    //stdLog.subscribeTo( RLOG_CHANNEL("error") );
    //stdLog.subscribeTo( GetGlobalChannel("test") );
    // subscribe to various things individually
  //stdLog.subscribeTo( GetGlobalChannel("debug") );
  //stdLog.subscribeTo( GetGlobalChannel("error") );
  //stdLog.subscribeTo( GetGlobalChannel("info") );
  //stdLog.subscribeTo( GetGlobalChannel("warn") );
	//stdLog.subscribeTo( RLOG_CHANNEL("") );
	//rDebug("initLogging");
}
