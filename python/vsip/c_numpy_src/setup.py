#!/usr/bin/env python3
"""
setup.py file for numpy jvsip utilities module
"""
from setuptools import setup, Extension
import numpy as np
incld = np.get_include()

setup (name = 'jvsipNumpy',
       version = '0.1',
       author  = "Randall Judd",
       description = """Numpy Utilities for Use in pyJvsip""",
       ext_modules = [Extension('_jvsipNumpyUtils',
                                    sources=['./numpyArrayCopies.c',
                                             './jvsipNumpyUtils_wrap.c'],
                                    include_dirs=['./','../../../c_VSIP_src',incld]),
                    ],
       py_modules = ["jvsipNumpyUtils","jvsipNumpy"],
    )
