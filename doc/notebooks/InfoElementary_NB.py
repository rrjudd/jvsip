# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ## Elementary Math operations using pyJvsip   
# These are examples of operations defined in the C VSIPL spec in the Vector and Elementwise chapter under Elementary Math Functions.

# <codecell>

import pyJvsip as pv
f='%.3f'

# <markdowncell>

# We create a vector and put some date into it. Most elementary operations are done as properties if a method is used. Methods are frequently in-place. Use a function for out of place, or a copy of the input vector.

# <codecell>

try: pi
except: from math import pi
a=pv.create('vview_d',10).ramp(0,2*pi/10.0)

# <markdowncell>

# In-Place using method

# <codecell>

a.mprint(f)
a.sin
a.mprint(f)

# <markdowncell>

# out-of-place using method

# <codecell>

b=a.copy.asin
b.mprint(f)
a.mprint(f)

# <markdowncell>

# out-of-place using function call

# <codecell>

pv.sin(b,a)
b.mprint(f)
a.mprint(f)

# <markdowncell>

# in-place using function call

# <codecell>

pv.sin(b,b)
b.mprint(f)

# <markdowncell>

# All the elementary functions work the same except for atan2 which has three arguments (two input and an output). There is no view method in pyJvsip for atan2, only a function call.

