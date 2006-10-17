#! /bin/sh
rm -vf __db.* *.db
./mktable people int id string name int age
./desc people
./addrow people 1 John 30
./addrow people 4 Eric 18
./addrow people 2 Bob 42
./addrow people 3 Steve 18
./list people

