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

