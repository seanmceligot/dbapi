compile: _greendb.la
include ../../config.mak

INCLUDES=-I../.. ${PYTHON_INCLUDE}
DEFINES=-DSWIG

_greendb.la: greendb_wrap.lo
	${LIBTOOL_LINK} -module -o $@ $< -rpath ${PYTHON_INSTALL} -lm -ldb_cxx ../../src/libgreendb.la 

install:
	${LIBTOOL_INSTALL} -c _greendb.la *.py ${PYTHON_INSTALL}

uninstall:
	${LIBTOOL_UNINSTALL} ${PYTHON_INSTALL}/_greendb.la 

greendb_wrap.cc: ../greendb.i
	swig -c++ -python -o $@ $<

%.lo: %.cc
	$(LIBTOOL_CXX) -c ${INCLUDES} ${DEFINES} $<

clean:
	$(LIBTOOL_CLEAN) *.o *_wrap.c *_wrap.cc *.pm *.so *.doc __db.* *.db *.so _greendb.a 

