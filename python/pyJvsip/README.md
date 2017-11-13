# Python Jvsip **pyJvsip** module

This directory contains a module which demonstrates a VSIPL inspired, python vector/matrix signal processing library.
The **pyJvsip** module imports the **vsip** module. It must be installed for pyJvsip to work properly.

## Build and Install

Should be able to just do

>    python setup.py install


## Notes:

* The **vsip** module is the raw C VSIPL library as a python module. Encapsulation was done using SWIG.
[SWIG](http://www.swig.org) provides type information in the encapsulation but all the naming and use of VSIPL functions
remains pretty much the same as in C VSIPL.

* The **pyJvsip** module defines true python clases to wrap the C VSIPL objects. For instance
pyJvsip has a block and view class which wrap the C VSIPL block and view objects in a 
python object. No init, finalize, create or destroy is required in the pyJvsip implementation
as all that is handled by the pyJvsip implementation and the python garbage collector.

