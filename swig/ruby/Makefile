compile: greendb.la
include ../../config.mak

INCLUDES=-I../.. ${RUBY_INCLUDE} ${ALL_INCLUDES}
DEFINES=-DSWIG

greendb.la: greendb_wrap.lo
	${LIBTOOL_LINK} -module -o $@ $< -rpath ${RUBY_INSTALL} -l${RUBY_LIB} ${LIBS} ../../src/libgreendb.la 

install:
	${LIBTOOL_INSTALL} -c greendb.la ${RUBY_INSTALL}

uninstall:
	${LIBTOOL_UNINSTALL} ${RUBY_INSTALL}/greendb.la 

greendb_wrap.cc: ../greendb.i
	swig -c++ -ruby -o $@ $<

%.lo: %.cc
	$(LIBTOOL_CXX) -c ${INCLUDES} ${DEFINES} $<

clean:
	$(LIBTOOL_CLEAN) *.o *_wrap.c *_wrap.cc *.so __db.* *.db *.so  *.lo *.la *.loT

test:
	sh test.sh

debug:
				libtool --mode=execute gdb --args ruby -I .libs test.rb

wipe:
	rm -vrf tables.db __db.*
