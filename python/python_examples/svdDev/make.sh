#!/bin/sh
rm *.o
swig -python svdUtils.i
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_svdSlices.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_eye.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_sign.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_bidiag.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_norm.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_houseVector.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c VU_svdIteration.c
gcc-4.2 -arch x86_64 -O3 -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/Library/Frameworks/jvsipF.framework/Headers -c svdUtils_wrap.c
gcc-4.2 -bundle -arch x86_64 -isysroot /Developer/SDKs/MacOSX10.6.sdk /Library/Frameworks/jvsipF.framework/jvsipF /Library/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib *.o -o _svdUtils.so
