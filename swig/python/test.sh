#! /bin/sh
rm -vf __db.* *.db
LD_LIBRARY_PATH=.libs:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

python mktable.py testtable 2 strcol 4 intcol 2> test.log || cat test.log
python desc.py testtable 2>>test.log
python addrow.py testtable one 1 2>>test.log
python addrow.py testtable two 2 2>>test.log
python addrow.py testtable three 3 2>>test.log
python list.py testtable 2>>test.log

