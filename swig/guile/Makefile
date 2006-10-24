compile: libguilegreendb.la
include ../../config.mak

BASEDIR=../..
INCLUDES=-I../.. ${GUILE_INCLUDE} ${DB_INCLUDE}
DEFINES=-DSWIG

libguilegreendb.la: greendb_wrap.lo
	${LIBTOOL_LINK} -o $@ $< -rpath ${prefix}/lib -lm -ldb_cxx -lrlog ../../src/libgreendb.la 

install:
	${LIBTOOL_INSTALL} -c libguilegreendb.la ${prefix}/lib/

uninstall:
	${LIBTOOL_UNINSTALL} ${prefix}/lib/libguilegreendb.la 

greendb_wrap.cc: ../greendb.i
	swig -procdoc doc.txt -c++ -guile -o $@ $<

%.lo: %.cc
	$(LIBTOOL_CXX) -c ${INCLUDES} ${DEFINES} $<

clean:
	rm -vrf *.o *_wrap.c *_wrap.cc *.pm *.so *.doc __db.* *.db .libs *.la *.lo *.la *.db *.log 

