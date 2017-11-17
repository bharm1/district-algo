# NEIGHBORING ZIP CODES FINDER

This file takes in a comma separated value (CSV) file containing ZIP codes and their coordinates. Then it will use that informatin to evaluate the neighboring ZIP codes for each ZIP code.

## COMPILING

This code was written for C++11 and therefore, must be run with C++11 enabled.  To enable C++11, you must add -std=c++0x immediately after g++

Example: g++ -std=c++0x back.cpp -o back

NOTE: UMBC gl does not support C++11

This code was developed and tested on GCC version 6.3.0

## CSV FORMAT

In order for the comma separated value (CSV) file to be read in correctly, it must be headerless.
In addition, it must contain 9 columns in the following order:

poname, zip, latitude, pop2001, state, area, longitude, sumblkpop, coords