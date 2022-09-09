# Python Jvsip **pyJvsip** module

This directory contains a module which demonstrates a VSIPL inspired, python vector/matrix signal processing library.
The **pyJvsip** module imports the **vsip** module. It must be installed for pyJvsip to work properly.

## Build and Install

Should be able to just do

>    python setup.py install --user


## Notes:

* There seem to be continual changes to python and it's environment which have caused problems.  I have changed the
intall to --user which seems to cause fewer problems.  Distutils seems to be deprecated but still around and how to
replace it is not clear.  I have more trouble on my apple devices.  I also build and test on a raspberry pi which seems
to be less sensitive.  The code works.  Getting it installed may require the use of a python knowledgable person.

* The **vsip** module is the raw C VSIPL library as a python module. Encapsulation was done using SWIG.
[SWIG](http://www.swig.org) provides type information in the encapsulation but all the naming and use of VSIPL functions
remains pretty much the same as in C VSIPL.

* The **pyJvsip** module defines true python clases to wrap the C VSIPL objects. For instance
pyJvsip has a block and view class which wrap the C VSIPL block and view objects in a 
python object. No init, finalize, create or destroy is required in the pyJvsip implementation
as all that is handled by the pyJvsip implementation and the python garbage collector.

