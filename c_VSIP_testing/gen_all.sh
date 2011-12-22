#!/bin/sh
ls | sed '/\.h/!d' | sed 's/^/#include"/' | sed 's/$/"/' >includes
ls | sed '/\.h/!d' | sed 's/\.h/();/' | sed 's/^/    /' >functions
sed -e '/func\.h/ r includes' <testing.tmplt | sed  -e '/func()/ r functions' >test_all.c
rm includes
rm functions
cc -o test_all test_all.c -O3 -Wall -std=c89 -pedantic -I../include ../lib/libvsip.a
