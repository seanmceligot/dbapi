all: _greendb.so
#LIBS=-ldb_cxx -L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o -
#LIBS=-L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o 
#LIBS=-ldb_cxx ../src/*.o greendb_wrap.o 
BASEDIR=../..
INCLUDES=-I${BASEDIR} ${DB_INCLUDE}
LIBS=${BASEDIR}/src/*.o /usr/lib/libdb_cxx-4.2.a
#DEFINES=-Dbool=char -DSWIG
DEFINES=

sclean:
	rm -vf *.so

_greendb.so: greendb_wrap.o
	c++ -shared ${LIBS} -lstdc++ -ldb_cxx $< -o $@

greendb_wrap.cc: ../greendb.i
	swig -c++ -ocaml -o $@ $<

greendb_wrap.c: greendb_wrap.cc
	mv -v $< $@

greendb_wrap.o: greendb_wrap.c
	ocamlc -c -ccopt -xc++ -ccopt -g -g -ccopt ${INCLUDES} ${DEFINES} $<
#g++ -fpic -c $< ${INCLUDES} ${DEFINES}

clean:
	rm -vf greendb.ml __db*  *.o *_wrap.c *_wrap.cc *.pm *.so *.doc

versions:
	set -x
	g++ --version
	c++ --version
	swig -version

