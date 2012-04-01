#!/bin/sh
ATEST=$1
AWORKINGDIR="./"
AVSIPLIB="../lib/libvsip.a"
AVSIPHEADERDIR="../include"
CC=cc 
set `echo $ATEST | sed 's/\// /g'`
AFILE=`eval echo \\\$$#`
AFUNC=`eval echo $AFILE | sed '/\.h/!d' | sed 's/\.h/();/'`
echo "/* atest.c */" >atest.c
echo "/* $AFILE  */" >>atest.c
echo "#include<stdio.h>\n#include<string.h>\n#include<vsip.h>\n" >>atest.c
echo "#include\"$ATEST\"\n" >>atest.c
echo "#define NDPTR_f ((vsip_scalar_f*)NULL)\n#define NDPTR_d ((vsip_scalar_d*)NULL)" >>atest.c
echo "#define NDPTR_i ((vsip_scalar_i*)NULL)\n#define NDPTR_si ((vsip_scalar_si*)NULL)" >>atest.c
echo "int main(){\n\tvsip_init((void*)0);"  >>atest.c
echo "\n/* function to test */\n\t$AFUNC\n" >>atest.c
echo "\tvsip_finalize((void*)0); \n\treturn 0;\n} " >>atest.c
$CC atest.c -o atest -I$AVSIPHEADERDIR $AVSIPLIB
./atest
