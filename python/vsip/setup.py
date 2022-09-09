#!/usr/bin/env python
# Designed to work for JVSIP with libraries in the standard locations as built with the
# makefile in the JVSIP home directory. Extension parmaeters listing should be self
# explanatory for library and include directory expected locations.
# to build use from the command line
#   python setup.py build_ext
# to build and install use from the command line
#   python setup.py build_ext install
# Note 
#   To use another vsip implementation you need to edit vsip.i to include the proper vsip.h
#   and to list the functionality available (or desired) with the other implementation.
#   Edit Extension and setup calls as needed
"""
Python setup file for distutils. Creates JVSIP vsip module.
Requirements:
    C Compiler
    Python installation and distribution utilities module
    SWIG program installed (www.swig.org)
    Need to have built the JVSIP vsip library (libvsip.a)
"""
from distutils.core import setup, Extension

vsip_module = Extension('_vsip',
                        sources=['vsip.i',
                                  './c_src/copyToList.c',
                                  './c_src/indexptr.c',
                                  './c_src/py_jdot.c',
                                  './c_src/vsipScalarFunctions.c',
                                  './c_src/jvsip_mprod.c'],
                        include_dirs=['../../c_VSIP_src','./c_src'],
                        library_dirs=['../../lib'],
                        libraries=['vsip']
                       )
setup (name = 'vsip',
       version = '0.6',
       author      = "Randall Judd",
       description = """VSIP Extension Module""",
       ext_modules = [vsip_module],
       py_modules=['vsip'],
    )
