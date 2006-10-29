#! /bin/sh
rm -vf __db.* *.db
LD_LIBRARY_PATH=.libs:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
GUILE="libtool --mode=execute guile"

$GUILE -s mktable.scm people int id string name int age
$GUILE -s desc.scm people
$GUILE -s addrow.scm people 1 John 30
$GUILE -s addrow.scm people 4 Eric 18
$GUILE -s addrow.scm people 2 Bob 42
$GUILE -s addrow.scm people 3 Steve 18
$GUILE -s list.scm people
