all: _greendb.so
#LIBS=-ldb_cxx -L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o -
#LIBS=-L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o 
#LIBS=-ldb_cxx ../src/*.o greendb_wrap.o 
BASEDIR=../..
INCLUDES=-I ${BASEDIR}  -I /usr/include/python2.1
PYTHON=python2.1
LIBS=${BASEDIR}/src/*.o /usr/lib/libdb_cxx-4.0.a
#DEFINES=-Dbool=char -DSWIG
DEFINES=

sclean:
	rm -vf *.so

_greendb.so: greendb_wrap.o
	c++ -shared ${LIBS} -lstdc++ -ldb_cxx $< -o $@

greendb_wrap.cc: ../greendb.i
	swig -c++ -python -o $@ $<

greendb_wrap.o: greendb_wrap.cc
	g++ -fpic -c $< ${INCLUDES} ${DEFINES}

clean:
	rm -vf greendb.py __db*  *.o *_wrap.c *_wrap.cc *.pm *.so *.doc

test:
	rm -f __db* *.db
	$(PYTHON) mktable.py testtable 2 strcolumn 4 intcolumn 2>mktable.log
	$(PYTHON) desc.py testtable 2>desc.log
	$(PYTHON) addrow.py testtable one 1 2>addrow.log
	$(PYTHON) addrow.py testtable two 2 2>addrow.log
	$(PYTHON) addrow.py testtable three 3 2>addrow.log
	$(PYTHON) list.py testtable 2>list.log

strace:
	strace -o t.strace python test.py

versions:
	set -x
	g++ --version
	c++ --version
	swig -version

