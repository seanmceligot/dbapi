#! /bin/sh

set -e
name=`basename $0 .sh`
./clean.sh
#DMALLOC_OPTIONS=debug=0xff67d6b,log=$0.log
#DMALLOC_OPTIONS=log-stats,log-non-free,log-bad-space,check-fence,catch-null,log=$name.log
DMALLOC_OPTIONS=log-stats,log-non-free,log-bad-space,check-fence,catch-null
export DMALLOC_OPTIONS

./$name 
#grep "not freed:" $name.log ||true


