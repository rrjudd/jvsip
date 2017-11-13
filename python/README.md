# Python for JVSIP   
This directory contains python related development code for the JVSIP VSIP Library.
The primary content is in the **vsip** and **pyJvsip**  directory.  The **pyJvsip** module needs
the **vsip** module to build.  Everything here is basically a *proof of concept* for C VSIPL with python
but the pyJvsip module has become fairly complete and I don't run into bugs very often.

## Python notebooks
Much of this implementations documentation and examples run in python notebooks.  Since I 
started this notebooks have undergone many changes and some things may be stale. Currently to
start a notebook I do

>    jupyter notebook

then navigate around till I find a notebook I am interested in running.  In the **jvsip** 
root directory you will find the **doc/notebooks** directory.  These are generally more instructive.

## Environment
I run on an Apple environment with an **Xcode** development environment.  I also use 
[Homebrew](https://brew.sh) to install various tools available including *python2* and *python3* and 
 [SWIG](http://www.swig.org) .