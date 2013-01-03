# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ## Decomposition Utilities Introduction
# ### Notation and Simple Relations to pyJvsip   
# #### Vector   
# A vector is designated $\vec{x}$ and generally uses a lower case. For math purposes a vector should be considered equivalent to a single column of a matrix; although for program puposes there are differeces between vector and matrice views. 
# #### Vector Norm and View Methods   
# Vector and Matrix norms are not supported in C VSIPL but have been included with the pyJvsip implementation. For mathematical definitions of norms the reader should consult a linear algebra text or search the internet. The norms supported in pyJvsip are the one norm (norm1), the two norm (norm2), the infinity norm (normInf) and the Frobenius norm (normFro).
# A vector norm is designated as $\parallel \vec{x} \parallel $. A two norm as ${\parallel \vec{x} \parallel }_{\:2} $
# #### Unit Vectors   
# A unit vector is designated as in $\hat{x}$. To produce a unit vector $\hat{x} = {\vec{x} \over {{\parallel \vec{x} \parallel }_{2}}}$
# #### dot, jdot and outer   
# Note that `dot`, `jdot`, and `outer` are only defined for views of type vector. 
# A math indicator like $ \vec{x} {\;} \vec{y}^H $ in done using an outer product and produces a view of type matrix. An indicator like $\vec{x}^H {\;} \vec{y} $ is done using `jdot` and produces a scalar. An indicator like $\vec{x}^T {\;} \vec{y} $ is done using `dot` and produces a scalar.   
# #### Identity Matrix    
# The identity matrix is square with ones on the diagonal and zero elsewhere. We designate it as $I$ and when the size is of interest we indicate it as a subscript as in $I_m$ or $I_n$. The function `eye(type,size)` is defined for creating a data space with an identity matrix in it. This is a convenience since we sometimes need a matrix for matrix product accumulations and the identity matrix is a convenient starting place.

# <codecell>

import pyJvsip as pv

# <markdowncell>

# #### Identity Matrix
# The function eye(t,n) where t is a pyJvsip matrix type and n is an integer creates and returns an identity matrix of size n and type t. This is a convenience function.

# <codecell>

def eye(t,n): # create and return an identity matrix of size n and type t
    return pv.create(t,n,n).identity

# <markdowncell>

# #### Sign Function
# The sign function is used for Householder and Givens calculations. It is defined in several texts although the text I am using here is the LAPACK Working Notes document #148. 

# <codecell>

def sign(a_in): # see  LAPACK Working Notes 148 for definition of sign
    if type(a_in) is int:
        a=float(a_in)
    else:
        a=a_in
    if type(a) is float or type(a) is complex:
        t=pv.vsip_hypot_d(a.real,a.imag)
        if t == 0.0:
            return 1.0
        elif a.imag==0.0:
            if a.real < 0.0:
                return -1.0
            else:
                return 1.0
        else:
            return a/t
    else:
        print('sign function only works on scalars')
        return

