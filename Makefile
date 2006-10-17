all: compile

include config.mak

subdirs=src util

compile:
	for d in ${subdirs};do make -C $$d $@;done

install: 
	for d in ${subdirs};do make -C $$d $@;done
	
uninstall:
	for d in ${subdirs};do make -C $$d $@;done

clean:
	for d in ${subdirs};do make -C $$d $@;done
	rm -vf config.h dbversion${EXE}

config.h: dbversion${EXE}
	./dbversion > config.h

dbversion${EXE}: dbversion.cc
	${CXX} ${DB_INCLUDE} -ldb_cxx -o $@ $<	

