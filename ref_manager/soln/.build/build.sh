#!/bin/bash
NAME=we3_solution
if ! [ -f $NAME ]
then
    make -s
    rm *.o
fi
chmod +x $NAME
./$NAME
rm -f $NAME
