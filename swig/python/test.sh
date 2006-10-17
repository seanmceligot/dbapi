#! /bin/sh
rm -vf __db.* *.db
PYTHONPATH=.libs
export PYTHONPATH
PYTHON=python
$PYTHON mktable.py testtable 2 strcol 4 intcol 2> test.log
$PYTHON desc.py testtable 2>>test.log
$PYTHON addrow.py testtable one 1 2>>test.log
$PYTHON addrow.py testtable two 2 2>>test.log
$PYTHON addrow.py testtable three 3 2>>test.log
$PYTHON list.py testtable 2>>test.log

