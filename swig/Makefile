all: compile

include ../config.mak

subdirs=python ruby

compile:
	for d in ${subdirs};do make -C $$d $@;done

install: 
	for d in ${subdirs};do make -C $$d $@;done
	
uninstall:
	for d in ${subdirs};do make -C $$d $@;done

clean:
	for d in ${subdirs};do make -C $$d $@;done
	rm -vf config.h

