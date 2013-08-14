#!/usr/bin/env python
from distutils.core import setup
setup(name='pyJvsip',
      version='0.2.2',
      description='pyJvsip is a vector/matrix signal processing module bassed on the VSIPL C Library',
      author='Randall Judd',
      author_email='rrjudd@me.com',
      license='MIT ( http://opensource.org/licenses/MIT )',
      py_modules=['pyJvsip','vsipElementwiseElementary','vsipElementwiseManipulation',\
            'vsipElementwiseUnary','vsipElementwiseBinary','vsipElementwiseTernary',\
            'vsipElementwiseLogical'],
      )
