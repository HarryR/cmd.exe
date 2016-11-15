#!/bin/sh
# Try to build all files... separately
for FILE in *.c; do make `echo $FILE | sed -e 's/\.c/\.o/'`; done
