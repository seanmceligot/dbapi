
compile: desc${EXE} mktable${EXE} addrow${EXE} list${EXE} toxml${EXE}

include ../config.mak

addrow${EXE}: addrow.lo 
	${LIBTOOL_LINK} -o $@ ${LIBS} addrow.o  ../src/libgreendb.la 

list${EXE}: list.lo 
	${LIBTOOL_LINK} -o $@ ${LIBS} list.o  ../src/libgreendb.la 

toxml${EXE}: toxml.lo 
	${LIBTOOL_LINK} -o $@ ${LIBS} toxml.o  ../src/libgreendb.la 

mktable${EXE}: mktable.lo 
	${LIBTOOL_LINK} -o $@ ${LIBS} mktable.o  ../src/libgreendb.la 

desc${EXE}: desc.lo 
	${LIBTOOL_LINK} -o $@ ${LIBS} desc.o  ../src/libgreendb.la 

%.lo: %.cc
	$(LIBTOOL_CXX) ${INCLUDES}  -c $<

DISTCLEANFILES = .deps/*.P
INCLUDES=-I.. -I../greendb

clean:
	rm -vrf .libs *.o *.exe *.log __db.* *.lo *.db

install: desc${EXE} mktable${EXE} addrow${EXE} list${EXE} toxml${EXE}
	${LIBTOOL_INSTALL} -c desc${EXE} ${prefix}/bin/
	${LIBTOOL_INSTALL} -c mktable${EXE} ${prefix}/bin/
	${LIBTOOL_INSTALL} -c addrow${EXE} ${prefix}/bin/
	${LIBTOOL_INSTALL} -c list${EXE} ${prefix}/bin/
	${LIBTOOL_INSTALL} -c toxml${EXE} ${prefix}/bin/

uninstall:
	${LIBTOOL_UNINSTTALL} ${prefix}/bin/desc${EXE}
	${LIBTOOL_UNINSTTALL} ${prefix}/bin/mktable${EXE}
	${LIBTOOL_UNINSTTALL} ${prefix}/bin/addrow${EXE}
	${LIBTOOL_UNINSTTALL} ${prefix}/bin/list${EXE}
	${LIBTOOL_UNINSTTALL} ${prefix}/bin/toxml${EXE}
