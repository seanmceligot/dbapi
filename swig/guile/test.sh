#! /bin/sh
rm -vf __db.* *.db
LD_LIBRARY_PATH=.libs:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
guile -s mktable.scm testtable 2 strcol 4 intcol 2> test.log
guile -s desc.scm testtable 2>>test.log
guile -s addrow.scm testtable one 1 2>>test.log
guile -s addrow.scm testtable two 2 2>>test.log
guile -s addrow.scm testtable three 3 2>>test.log
guile -s list.scm testtable 2>>test.log

