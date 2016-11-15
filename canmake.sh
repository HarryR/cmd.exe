#!/bin/sh
# Check which files can be successfully built
for FILE in *.c
do
    make `echo $FILE | sed -e 's/\.c/\.o/'` &> /dev/null
    if test $? -eq 0
    then
        echo $FILE
    fi
done
