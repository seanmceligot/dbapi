all: compile

include config.mak

compile: config.h
	make -C src $@
	make -C util $@

install: 
	make -C src $@
	make -C util $@
	
uninstall:
	make -C src $@
	make -C util $@

clean:
	make -C src $@
	make -C util $@
	rm -vf config.h

config.h: dbversion${EXE}
	./dbversion > config.h

dbversion${EXE}: dbversion.cc
	${CXX} -ldb_cxx -o $@ $<	

