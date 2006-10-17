#ifndef __GREENENV_HH
#define __GREENENV_HH

#include <db_cxx.h>
#include <string>

class GreenEnv:protected DbEnv {
  const std::string _home;
public:
  GreenEnv (const char *home);
  void open ();
  void close ();
  const char *home () const {
    return _home.c_str();
  }
	void err(int dberr) { DbEnv::err(dberr, "GreenEnv");};
};

std::ostream & operator << (std::ostream & os, const GreenEnv & db);
std::ostream & operator << (std::ostream & os, const GreenEnv * db);
#endif
