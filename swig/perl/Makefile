compile: libperlgreendb.la
include ../../config.mak

INCLUDES=-I../.. ${PERL_INCLUDE}
DEFINES=-DSWIG

libperlgreendb.la: greendb_wrap.lo
	${LIBTOOL_LINK} -o $@ $< -rpath ${prefix}/lib -lm -ldb_cxx ../../src/libgreendb.la 

install:
	${LIBTOOL_INSTALL} -c libperlgreendb.la ${prefix}/lib/

uninstall:
	${LIBTOOL_UNINSTALL} ${prefix}/lib/libperlgreendb.la 

greendb_wrap.cc: ../greendb.i
	swig -c++ -perl5 -o $@ $<

%.lo: %.cc
	$(LIBTOOL_CXX) -c ${INCLUDES} ${DEFINES} $<

clean:
	rm -vrf *.o *_wrap.c *_wrap.cc *.pm *.so *.doc __db.* *.db .libs
############################################################################
##all: greendb.so
###LIBS=-ldb_cxx -L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o -
###LIBS=-L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o 
###LIBS=-ldb_cxx ../src/*.o greendb_wrap.o 
##BASEDIR=../..
##INCLUDES=${BASEDIR}
##LIBS=${BASEDIR}/src/*.o /usr/lib/libdb_cxx-4.0.a
###DEFINES=-Dbool=char -DSWIG
##DEFINES=-DSWIG
##
##sclean:
##	rm -vf *.so
##
##greendb.so: greendb_wrap.o
##	c++ -shared ${LIBS} -lstdc++ -ldb_cxx $< -o $@
##
##greendb_wrap.cc: ../greendb.i
##	swig -c++ -perl5 -o $@ $<
##
##greendb_wrap.o: greendb_wrap.cc
##	g++ -c $< -I/usr/lib/perl/5.8.0/CORE -I ${INCLUDES} ${DEFINES}
##
##clean:
##	rm -vf *.o *_wrap.c *_wrap.cc *.pm *.so *.doc
##
##test:
##	perl test.pl
##
##strace:
##	strace -o t.strace perl test.pl
