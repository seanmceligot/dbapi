prefix=/usr/local
GUILE_INCLUDE=-I/usr/lib/guile/5.6.1/CORE 
PERL_INCLUDE=-I/usr/lib/perl/5.8/CORE 

PYTHON_INCLUDE=-I/usr/include/python2.3
PYTHON=/usr/bin/python2.3
PYTHON_INSTALL=/usr/lib/python2.3/site-packages

RUBY_INCLUDE=-I/usr/lib/ruby/1.8/i386-linux
RUBY=/usr/bin/ruby1.8
RUBY_INSTALL=/usr/local/lib/site_ruby/1.8

AR=ar
CXXCOMPILE=${CXX} ${CXXFLAGS}
CXXFLAGS=-ggdb
#CXXFLAGS=-ggdb -Wall
CXX=g++
DEFINES=-DGC_OPERATOR_NEW_ARRAY
EXE=
EXTRA_DIST=debian
LIBS=-ldb_cxx
RANLIB=ranlib

LIBTOOL_CLEAN=libtool --mode=clean rm -vf
LIBTOOL_CXX=libtool --mode=compile ${CXXCOMPILE}
LIBTOOL_INSTALL=libtool --mode=install install
LIBTOOL_LINK=libtool --mode=link ${CXXCOMPILE}
LIBTOOL_UNINSTALL=libtool --mode=uninstall rm -vf
