#! /bin/sh
rm -vf __db.* *.db
./mktable testtable 2 strcol 4 intcol 2> test.log
./desc testtable 2>>test.log
./addrow testtable one 1 2>>test.log
./addrow testtable two 2 2>>test.log
./addrow testtable three 3 2>>test.log
./list testtable 2>>test.log

