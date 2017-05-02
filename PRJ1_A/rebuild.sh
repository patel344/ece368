#!/bin/bash

CC=color-gcc.pl
FILES="answer11.c main.c"
BUILDNO=0

build()
{
    BUILDNO=$(expr $BUILDNO + 1)
    clear
    $CC gcc -Wall -Wshadow -g -Wno-unused-variable $FILES -o pa11 && valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./pa11 && cat memcheck.log | tail -n 1 &&\
	echo "Build #$BUILDNO successful"
}

checksum()
{
    cat $FILES | md5sum | awk '{ print $1 }'
}

MD5=
while (( 1 > 0 )) ; do
    SUM=$(checksum)
    [ "$MD5" != "$SUM" ] && MD5=$SUM && build
    sleep 0.25
done

