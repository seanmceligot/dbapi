all: greendb.so
#LIBS=-ldb_cxx -L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o -
#LIBS=-L../src -lgreendb -lgcc -lstdc++ greendb_wrap.o 
#LIBS=-ldb_cxx ../src/*.o greendb_wrap.o 
BASEDIR=../..
INCLUDES=${BASEDIR}
LIBS=${BASEDIR}/src/*.o /usr/lib/libdb_cxx-4.0.a
#DEFINES=-Dbool=char -DSWIG
DEFINES=-DSWIG

sclean:
	rm -vf *.so

greendb.so: greendb_wrap.o
	c++ -shared ${LIBS} -lstdc++ -ldb_cxx $< -o $@

greendb_wrap.cc: ../greendb.i
	swig -c++ -java -o $@ $<

greendb_wrap.o: greendb_wrap.cc
	g++ -c $< -I/usr/lib/java/5.6.1/CORE -I ${INCLUDES} ${DEFINES}

clean:
	rm -vf *.o *_wrap.c *_wrap.cc *.java *.so *.doc

test:
	java test.pl

strace:
	strace -o t.strace java test.pl
