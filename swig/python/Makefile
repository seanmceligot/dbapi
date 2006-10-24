dllprefix=_
compile: ${dllprefix}greendb.la
include ../../config.mak

INCLUDES=-I../.. ${PYTHON_INCLUDE} ${DB_INCLUDE}
DEFINES=-DSWIG 


${dllprefix}greendb.la: greendb_wrap.lo 
	${LIBTOOL_LINK} -module -o $@ $< -rpath ${PYTHON_INSTALL} -lm -ldb_cxx -lrlog ../../src/libgreendb.la 

install: 
	${LIBTOOL_INSTALL} -c ${dllprefix}greendb.la *.py ${PYTHON_INSTALL}

uninstall:
	${LIBTOOL_UNINSTALL} ${PYTHON_INSTALL}/${dllprefix}greendb.la 

greendb_wrap.cc: ../greendb.i
	swig -c++ -python -o $@ $<

%.lo: %.cc
	$(LIBTOOL_CXX) -c ${INCLUDES} ${DEFINES} $<

clean:
	$(LIBTOOL_CLEAN) *.o *_wrap.c *_wrap.cc *.pm *.so *.doc __db.* *.db *.so ${dllprefix}greendb.a  *.pyc *.la *.lo *.log

