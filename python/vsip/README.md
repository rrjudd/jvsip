# Python vsip module

This directory lets one build a python compatible vsip module from the C
VSIP library.

## Quick Start
From command line

>    python setup.py build_ext install --user

## Additional information

Designed to build for JVSIP with libraries in the standard locations as
built with the makefile in the JVSIP home directory. Extension
parmaeters listing should be self explanatory for library and include
directory expected locations.

To build use from the command line

>    python setup.py build_ext

to build and install use from the command line

>    python setup.py build_ext install --user

### Installation
 There seem to be continual changes to python and it's environment which
 have caused problems.  I have changed the install so the module goes to
 a user folder which seems to cause fewer problems.

 Distutils seems to be deprecated but still around and how to replace it
 is not clear. I removed the line "language=['c']" from setup.py because
 it was causing an error in the build process. It still builds OK
 without that line. I have more trouble on my apple devices. I also
 build and test on a raspberry pi which seems to be less sensitive.

 The code works.  Getting it installed may require the use of a python
 knowledgable person.


### Note 
   To use another vsip implementation you need to edit **vsip.i** to
   include the proper **vsip.h** and to list the functionality available
   (or desired) with the other implementation. Edit Extension and setup
   calls as needed

### Requirements
* C Compiler * Python installation and distribution utilities module *
[SWIG](http://www.swig.org) program installed * Need to have built the
JVSIP vsip library (libvsip.a)

### Hints   
* I use an Apple platform; for linux or microsoft there may be problems
I am not aware of. * I use [Homebrew](https://brew.sh) to install and
keep up-to-date various packages including SWIG and Python. * On my
current configuration I get the Apple installed python if I type
**python** or the brew installed python if I type **python2** or
**python3**. When calling python be aware of which one you are using
when installing.
  * I still use Homebrew but Apple seems to be installing the latest
Python3. To avoid conflicts I use Apples version. Python knowledgable
people may want to go some other way.

