#!/bin/bash
#build
find ./ -type f -name "*.c" -exec gcc {} -o {}.o \;
#clean
if [ "$1" = "clean" ]; then
	rm *.o -rf	
fi
