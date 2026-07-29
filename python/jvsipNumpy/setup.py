#!python
"""
Python setup file. Creates JVSIP vsip module.
Requirements:
    C Compiler
    python setuptools module needs to be downloaded
    SWIG program installed (www.swig.org)
    Need to have built the JVSIP vsip library (libvsip.a)
"""
from numpy import get_include
npIncld = get_include()

from setuptools import setup, Extension

jvsipNumpyUtils_module = Extension('_jvsipNumpyUtils',
                        sources=['jvsipNumpyUtils.i',
                                 'numpyArrayCopies.c'],
                        include_dirs=['../../c_VSIP_src','../../include','./',npIncld],
                        library_dirs=['../../lib'],
                        libraries=['vsip']
                       )
setup (name = 'jvsipNumpy',
       version = '0.1',
       author      = "Randall Judd",
       description = """jvsip numpy Extension Module""",
       ext_modules = [jvsipNumpyUtils_module],
       py_modules=['jvsipNumpy','jvsipNumpyUtils'],
    )
