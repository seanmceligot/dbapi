#include <cwchar>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "greendb/strdatum.hh"
#include "greendb/debug.hh"

static void datumtest() {
		IntDatum i(1);
		debug <<i.value() <<std::endl;
		assert(i.value() == 1);
		//i.set_value(99);
		i = 99;
		debug <<i.value() <<std::endl;
		assert(i.value() == 99);
	}
void strtest() {
  {
		StrDatum* s= new StrDatum ("abc");
		debug <<s->value() <<std::endl;
		assert(strcmp(s->value(), "abc")==0);
		
		s->set_value ("defg");
		debug <<s->value() <<std::endl;
		assert(strcmp(s->value(), "defg")==0);

		delete s;
	}

  {
		StrDatum s("abc");
		debug <<s.value() <<std::endl;
		assert(strcmp(*s, "abc")==0);

		s = "defg";
		debug <<s.value() <<std::endl;
		assert(strcmp(s.value(), "defg")==0);
	}
	{
		//wchar_t ww[]= { L'a',L'b',L'c',(wchar_t)NULL};
		WStrDatum* ws = new WStrDatum(L"abc");
		debug << "WStr: ";
		std::wcout << ws->value();
		std::cout<<std::endl;
		assert(wcscmp(ws->value(), L"abc")==0);
	}
}
int main (int argc, char **argv)
{
  datumtest();
  strtest();
  return 0;
}
