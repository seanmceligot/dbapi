prefix=/usr/local
CXX=g++
AR=ar
GUILE_INCLUDE=-I/usr/lib/guile/5.6.1/CORE 
PERL_INCLUDE=-I/usr/lib/perl/5.8/CORE 
PYTHON_INCLUDE=-I/usr/include/python2.1
PYTHON_INSTALL=/usr/lib/python2.1/site-packages
RANLIB=ranlib
EXE=
EXTRA_DIST=debian
#CXXFLAGS=-ggdb -Wall
CXXFLAGS=-ggdb
CXXCOMPILE=${CXX} ${CXXFLAGS}
LIBS=-ldb_cxx
DEFINES=-DGC_OPERATOR_NEW_ARRAY
LIBTOOL_CXX=libtool --mode=compile ${CXXCOMPILE}
LIBTOOL_LINK=libtool --mode=link ${CXXCOMPILE}
LIBTOOL_INSTALL=libtool --mode=install install
LIBTOOL_UNINSTALL=rm -vf
LIBTOOL_CLEAN=rm -vf
