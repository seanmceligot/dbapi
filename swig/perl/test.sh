#! /bin/sh
rm -vf __db.* *.db
LD_LIBRARY_PATH=.libs:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
perl mktable.pl testtable 2 strcol 4 intcol 2> test.log
perl desc.pl testtable 2>>test.log
perl addrow.pl testtable one 1 2>>test.log
perl addrow.pl testtable two 2 2>>test.log
perl addrow.pl testtable three 3 2>>test.log
perl list.pl testtable 2>>test.log

