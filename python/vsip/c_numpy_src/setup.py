#!/usr/bin/env python
"""
setup.py file for numpy jvsip utilities module
"""
from distutils.core import setup, Extension

setup (name = 'jvsipNumpy',
       version = '0.1',
       author  = "Randall Judd",
       description = """Numpy Utilities for Use in pyJvsip""",
       ext_modules = [Extension('_jvsipNumpyUtils',
                                    sources=['./numpyArrayCopies.c',
                                             './jvsipNumpyUtils_wrap.c'],
                                    include_dirs=['./','../../../c_VSIP_src']),
                    ],
       py_modules = ["jvsipNumpyUtils","jvsipNumpy"],
    )
