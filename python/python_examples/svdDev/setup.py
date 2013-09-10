#!/usr/bin/env python
"""
setup.py file for svdDev module
"""
from distutils.core import setup, Extension

setup (name = 'svdUtils',
       version = '0.1',
       author  = "Randall Judd",
       description = """Example of c extension used for svd developement""",
       ext_modules = [Extension('_svdUtils',
                      sources=[ 'VU_svdSlices.c',
                                'VU_eye.c', 
                                'VU_sign.c', 
                                'VU_bidiag.c', 
                                'VU_norm.c', 
                                'VU_houseVector.c', 
                                'VU_svdIteration.c',
                                'svdUtils_wrap.c',],
                       include_dirs=['./','../../../include']),
                    ],
       py_modules = [],
    )
