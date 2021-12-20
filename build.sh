#!/bin/bash
#build
find `pwd` -type f -name "*.c" -exec gcc {} -o {}.o \;
#clean
if [ "$1" = "clean" ]; then
	rm `pwd`/*.o -rf	
fi
