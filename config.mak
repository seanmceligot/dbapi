prefix=/usr/local
GUILE_INCLUDE=-I/usr/lib/guile/5.6.1/CORE 
PERL_INCLUDE=-I/usr/lib/perl/5.8/CORE 

PYTHON_INCLUDE=-I/usr/include/python2.4
PYTHON=/usr/bin/python2.4
PYTHON_INSTALL=/usr/lib/python2.4/site-packages

RUBY_INCLUDE=-I/usr/lib/ruby/1.8/i686-linux
RUBY=/usr/bin/ruby1.8
RUBY_INSTALL=/usr/local/lib/site_ruby/1.8
RUBY_LIB=ruby18

DB_INCLUDE=-I/usr/include/db4.3
GLIB_INCLUDE=-I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include/

ALL_INCLUDES=${DB_INCLUDE} ${GLIB_INCLUDE}

AR=ar
CXXCOMPILE=${CXX} ${CXXFLAGS}
CXXFLAGS=-ggdb ${DEFINES}
#CXXFLAGS=-ggdb -Wall
CXX=g++
DEFINES=-DGC_OPERATOR_NEW_ARRAY -DRLOG_COMPONENT=greendb
EXE=
EXTRA_DIST=debian
LIBS=-ldb_cxx -lrlog -lglib-2.0 -lm -lsupc++  -ldl -lcrypt -lpthread  -lc
RANLIB=ranlib

LIBTOOL_CLEAN=libtool --mode=clean rm -vf
LIBTOOL_CXX=libtool --mode=compile ${CXXCOMPILE}
LIBTOOL_INSTALL=libtool --mode=install install
LIBTOOL_LINK=libtool --mode=link ${CXXCOMPILE}
LIBTOOL_UNINSTALL=libtool --mode=uninstall rm -vf

dbclean:
	rm -vrf tables.db __db.*
