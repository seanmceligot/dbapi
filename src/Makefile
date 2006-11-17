
compile: libgreendb.la

include ../config.mak

INCLUDES=-I.. -I../greendb ${DB_INCLUDE} ${ALL_INCLUDES}

OBJECTS=debug.lo typemap.lo datum.lo greenenv.lo greendb.lo cursor.lo row.lo table.lo schema.lo memory.lo xml.lo resultset.lo

libgreendb.la: $(OBJECTS)
	${LIBTOOL_LINK} -o $@ ${OBJECTS} -rpath ${prefix}/lib ${LIBS}
#	-rm -f libgreendb.a
#	$(AR) cru libgreendb.a $(libgreendb_a_OBJECTS)
#	$(RANLIB) libgreendb.a

clean:
	rm -rvf *.o *.lo *.a .libs *.la

%.lo: %.cc
	$(LIBTOOL_CXX) ${INCLUDES}  -c $<

install:
	${LIBTOOL_INSTALL} -c libgreendb.la ${prefix}/lib/

uninstall:
	${LIBTOOL_UNINSTALL} ${prefix}/lib/libgreendb.la 

