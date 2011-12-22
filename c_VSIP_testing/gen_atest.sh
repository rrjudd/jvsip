#!/bin/sh
echo $@ | sed '/\.h/!d' | sed 's/ /#include"/' | sed 's/ /"/g' >includes
echo $@ | sed '/\.h/!d' | sed 's/\.h/();/' | sed 's/ /    /g' >functions
sed -e '/func\.h/ r includes' <testing.tmplt | sed  -e '/func()/ r functions' >atest.c
rm includes
rm functions
