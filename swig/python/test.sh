#! /bin/sh
rm -vf __db.* *.db
PYTHONPATH=.libs
export PYTHONPATH
PYTHON="libtool --mode=execute python"
$PYTHON mktable.py people int id string name int age
$PYTHON desc.py people
$PYTHON addrow.py people 1 John 30
$PYTHON addrow.py people 4 Eric 18
$PYTHON addrow.py people 2 Bob 42
$PYTHON addrow.py people 3 Steve 18
$PYTHON list.py people

