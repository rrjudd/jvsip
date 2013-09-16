# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ## Introduction   
# In this notebook we introduce the basics of blocks and views.  The reader should first be familiar with the C VSIPL specification introduction chapter so they are familiar with how blocks and views work. Under the covers pyJvsip blocks and views are based on C VSIPL blocks and views.

# <codecell>

import pyJvsip as pv
f='%.2f'

# <markdowncell>

# ### Block  
# Creating a block requires a block type and the number of elements in the block. The memory flag is not used in pyJvsip. The pyJvsip Block object has a method to return the number of elements in the block. This method is not supported by the C VSIPL block object.   
# 
# Memory flag defaults to VSIP_MEM_NONE. Note that C VSIPL does not support hints like memory flag or algorithm except the API is supported, so pyJvsip will frequently default these to some value.

# <codecell>

aFloatBlock=pv.Block('block_f',100)
aDoubleBlock=pv.Block('block_d',100)
aComplexDoubleBlock=pv.Block('block_d',100)
aIntBlock=pv.Block('block_i',100)

# <codecell>

aFloatBlock.length

# <markdowncell>

# ### View
# A pyJvsip view is always associated with a block. All views are created with a block bind method.    
#    
# The number of arguments to bind are used to determine if a matrix or vector view are created.    
# A vector view is bind(offset,stride, length)   
# A matrix view is bind(offset, columnStride, columnLength, rowStride, rowLength)

# <codecell>

aFloatVectorView=aFloatBlock.bind(0,2,10)
aFloatVectorView.ramp(1,1)
aFloatVectorView.mprint(f)

# <codecell>

aDoubleMatrixView=aDoubleBlock.bind(0,5,6,1,5)

# <codecell>

for i in range(aDoubleMatrixView.collength):
    aDoubleMatrixView.rowview(i).ramp(i,1)
aDoubleMatrixView.mprint(f)

# <markdowncell>

# A vector view has a block property so the block a view is associated with can always be recovered and used to make another view on the same block.

# <codecell>

aNewVector = aFloatVectorView.block.bind(0,1,10)
aNewVector.mprint(f)

# <markdowncell>

# Above note we created the block and placed a view on it with stride two and then put a ramp in the view. Here we have created a new view on the same data space with stride one. But we did not initialize this vector so it has coresponding values from the first vector pluss mystery values from our uninitialized block.
# 
# Sometimes you want a vector on an entire block; perhaps to initialize the block values. For convenience pyJvsip supplies a block method to do this for you.

# <codecell>

aFloatVectorView.block.vector.fill(0.0)
aFloatVectorView.ramp(1,1)
aFloatVectorView.mprint(f)
aNewVector.mprint(f)

# <markdowncell>

# Note above we didn't care about the vector on the whole block so we didn't create a reference to it. pyJvsip uses python's garbage collection methods to destroy pyJvsip objects which have no reference.  We can see now the block has been initialized so our second vector has a zero in every other spot. 

# <markdowncell>

# ## Create Function   
# 
# The pyJvsip module has a create function which may be used to create pyJvsip objects including blocks and views. Most of the time you will use this function. When a view is created with this function it creates the needed block under the covers for you.

# <codecell>

aVector=pv.create('vview_d',10)
aVector.ramp(1,1)
aVector.mprint(f)

# <markdowncell>

# Be default when creating a matrix view the view is created as row major.

# <codecell>

aMatrix = pv.create('cmview_d',4,5)
aMatrix.block.vector.ramp(1,1)
aMatrix.imagview.block.vector.ramp(-1,-1)
aMatrix.mprint('%.1f')

# <markdowncell>

# We can also add a major argument if we want a column major matrix

# <codecell>

aMatrix = pv.create('cmview_d',4,5,'COL')
aMatrix.block.vector.ramp(1,1)
aMatrix.imagview.block.vector.ramp(-1,-1)
aMatrix.mprint('%.1f')

# <markdowncell>

# There are other ways to create views using subviews. Note a subview is a first class view and there is no material difference between a subview and it's parent. See the VSIPL spec for more information on the relationship of a parent complex view and it's child real and imag views. A few examples. Of course you can always recover the block and do a blockbind if you want a view of the same depth.  To get a real or imaginary view of complex aparent you must always use the realview and imagview method. 

# <codecell>

aMatrix.diagview(0).mprint(f)
aMatrix.realview.mprint(f)
aMatrix.rowview(2).mprint(f)
aMatrix.colview(1)[1:].mprint(f)
aMatrix[1:,2:].mprint(f)

# <markdowncell>

# The last two methods demonstrate slicing. Currently pyJvsip matrix and vector views support some slicing methods but only for positive index values. 

# <codecell>

aVector=pv.create('vview_i',100).ramp(1,1)

# <codecell>

aVector.mprint('%d')

# <codecell>

aVector[10:20:2].mprint('%d')
aNewVector=aVector[4:30:3].copy
aNewVector.mprint('%d')

# <markdowncell>

# Note the copy method above creates a new block and vector on the block.   
# You can also use a slice to copy data between vectors.

# <codecell>

aNewVector[:]=aVector[:aNewVector.length]
aNewVector.mprint('%d')
aNewVector[::2]=aVector[aNewVector.length:2 * aNewVector.length:2]
aNewVector.mprint('%d')

# <codecell>


