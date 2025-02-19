#!/usr/bin/env python
from setuptools import setup
setup(name='pyJvsip',
      version='0.3.1',
      description='pyJvsip is a vector/matrix signal processing module bassed on the VSIPL C Library',
      author='Randall Judd',
      author_email='rrjudd@me.com',
      license='MIT ( http://opensource.org/licenses/MIT )',
      py_modules=['pyJvsip','vsipElementwiseElementary','vsipElementwiseManipulation',\
            'vsipElementwiseUnary','vsipElementwiseBinary','vsipElementwiseTernary',\
            'vsipElementwiseLogical','vsipElementwiseSelection','vsipElementwiseBandB',
            'vsipElementwiseCopy','vsipSignalProcessing','vsipLinearAlgebra','vsipAddendum'],
      )
