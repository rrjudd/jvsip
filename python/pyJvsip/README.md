# Python Jvsip **pyJvsip** module

This directory contains a module which demonstrates a VSIPL inspired, python vector/matrix signal processing library.
The **pyJvsip** module imports the **vsip** module. It must be installed for pyJvsip to work properly.

## Build and Install

Should be able to just do

>    python3 setup.py install --user

or, if you prefer

>    python3 setup.py install


## Notes:

* There seem to be continual changes to python and it's environment which have caused problems.  I have changed the
install to --user which seems to cause fewer problems.  The code works.  Getting it installed may require the use of a python knowledgable person.

* Currently I am using the module **setuptools** for the setup. You must have the module
installed for your python version.

*  I also build and test on a raspberrypi (linux) which seems to be less sensitive to Python problems.  

* The **vsip** module is the raw C VSIPL library as a python module. Encapsulation was done using SWIG.
[SWIG](http://www.swig.org) provides type information in the encapsulation but all the naming and use of VSIPL functions
remains pretty much the same as in C VSIPL.

* The **pyJvsip** module defines true python classes to wrap the C VSIPL objects. For instance
pyJvsip has a block and view class which wrap the C VSIPL block and view objects in a 
python object. No init, finalize, create or destroy is required in the pyJvsip implementation
as all that is handled by the pyJvsip implementation and the python garbage collector.

