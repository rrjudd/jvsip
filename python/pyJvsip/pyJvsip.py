from vsip import *
from vsipElementwiseElementary import *
from vsipElementwiseManipulation import *
from vsipElementwiseUnary import *
from vsipElementwiseBinary import *
from vsipElementwiseTernary import *
from vsipElementwiseLogical import *
from vsipElementwiseSelection import *
from vsipElementwiseBandB import *
from vsipElementwiseCopy import *
from vsipSignalProcessing import *
from vsipLinearAlgebra import *

import vsiputils as vsip

__version__='0.3.1'

def __isView(a):
    return 'pyJvsip.__View' in repr(a)

def getType(v):
    """
        Returns a tuple with type information.
        Most of the time getType(v)[2] will be the information needed.
        getType(v)[0] is the module (python, vsip, or pyJvsip).
        getType(v)[1] is the class (scalar, View, Block, etc).
        getType(v)[2] is the type which is dependent on the module and class.
    """
    if isinstance(v,int) or isinstance(v,long) or isinstance(v,float) or isinstance(v,complex):
        return ('python','scalar',type(v))
    elif 'Swig' in repr(v) and 'scalar' in repr(v):
        if 'vsip_scalar_mi' in repr(v):
            return ('vsip','scalar','scalar_mi')
        if 'vsip_cscalar_f' in repr(v):
            return ('vsip','scalar','cscalar_f')
        if 'vsip_cscalar_d' in repr(v):
            return ('vsip','scalar','cscalar_d')
    elif 'pyJvsip' in repr(v):
        if 'View' in repr(v):
            return ('pyJvsip','View',v.type)
        elif 'Block' in repr(v):
            return ('pyJvsip','Block',v.type)
        elif 'Rand' in repr(v):
            return ('pyJvsip','Rand',v.type)
        elif 'FFT' in repr(v):
            return ('pyJvsip','FFT',v.type)
        elif 'LU' in repr(v):
            return('pyJvsip','LU',v.type)
        elif 'QR' in repr(v):
            return('pyJvsip','QR',v.type)
        else:
            print('Do not recognize object')
            return (repr(v),None,None)
    else:
        print('Do not recognize object')
        return (repr(v),None,None)

class JVSIP (object):
    init = 0
    def __init__(self):
        if JVSIP.init:
            self.vsipInit=0;
            JVSIP.init +=1;
        else:
            self.vsipInit = vsip.init()
            if self.vsipInit:
                printf('VSIP failed to initialize')
            else:
                JVSIP.init = 1;

    def __del__(self):
        JVSIP.init -= 1
        if JVSIP.init == 0:
            vsip.finalize()

class Block (object):
    tBlock = ['block_f','block_d','cblock_f','cblock_d',
              'block_vi','block_mi','block_bl',
              'block_si','block_i','block_uc']
    derivedTypes = ['real_f','real_d']
    matrixTypes=['mview_f','mview_d','cmview_f','cmview_d',
                 'mview_si','mview_i','mview_uc','mview_bl']
    vectorTypes=['vview_f','vview_d','cvview_f','cvview_d', 'vview_si','vview_i',\
                 'vview_uc','vview_mi', 'vview_vi','vview_bl']
    complexTypes=['cvview_f','cmview_f','cvview_d','cmview_d','cblock_f','cblock_d']
    blkSel={'vview_f':'block_f','vview_d':'block_d','cvview_f':'cblock_f',\
            'cvview_d':'cblock_d', 'vview_si':'block_si','vview_i':'block_i',\
            'vview_uc':'block_uc', 'vview_mi':'block_mi', 'vview_vi':'block_vi',\
            'vview_bl':'block_bl','mview_f':'block_f','mview_d':'block_d',\
            'cmview_f':'cblock_f','cmview_d':'cblock_d','mview_si':'block_si',\
            'mview_i':'block_i','mview_uc':'block_uc','mview_bl':'block_bl'}
    #Block specific class below
    def __init__(self,block_type,length):
        other = ['real_f','imag_f','real_d','imag_d']
        self.__jvsip = JVSIP()
        if block_type in Block.tBlock:
            self.__vsipBlock = vsip.create(block_type,(length,VSIP_MEM_NONE))
            self.__length = length
            self.__type = block_type
        elif block_type in other:
            self.__vsipBlock = length[0]
            self.__length = length[1]
            self.__type = block_type
        else:
            print('block type <:'+block_type+':> not support by Block class')
    def __del__(self):
        if self.__type in Block.tBlock:
            vsip.destroy(self.__vsipBlock)
        del(self.__jvsip)
    @property
    def vsip(self):
        return self.__vsipBlock
    # major for bind of matrix in attr is 'ROW', or 'COL'
    def bind(self,*args):
        if isinstance(args[0],tuple):
            attr=args[0]
        elif len(args) is 3:
            attr=(args[0],args[1],args[2])
        elif len(args) is 5:
            attr=(args[0],args[1],args[2],args[3],args[4])
        else:
            print('Argument list <:'+repr(args)+':>to bind must be either 3 or 5 integers')
            print('For vector arguments are offset, stride, length')
            print('For matrix arguments are offset, col_stride, col_length, row_stride, row_length')
            return
        view = vsip.bind(self.__vsipBlock,attr)
        retval = self.__View(view,self)
        retval.EW
        return retval
    @property
    def vector(self):
        """
            Since data in blocks is only accessible through a view the vector method
            is a convenience method to return the simplest view wich indexes all data.
            Usage:
               b = Block(aBlockType,length)
               v = b.vector
            v is a unit stride compact one dimensional view reflecting all the data
            in the block.
        """
        return self.bind(0,1,self.length)
    @classmethod
    def supported(cls):
        return {'tBlock':Block.tBlock,'viewTypes':Block.__View.supported()}
    @property
    def copy(self):
        """ This makes a new block object identical to the calling block object.
            Data in the old block object is NOT copied to the  new block object.
        """
        return self.otherBlock(self.type,self.length)
    @classmethod
    def otherBlock(cls,blk,length):
        """
        This method is used internal to the pyJvsip module.
        It is not intended to be used in user code.
        """
        return cls(blk,length)
    @property
    def type(self):
        return self.__type
    @property
    def length(self):
        return self.__length
    def __len__(self):
        return self.length
    #View Class defined here
    # views are required by the specification to be associated with a block.
    # To enforce that in pyJvsip only block objects know how to create views;
    # or at least that is the goal by placing views here. As far as python is
    # concerned I still have much to learn.
    class __View(object):
        tView=['mview_f','mview_d','cmview_f','cmview_d',
                 'mview_si','mview_i','mview_uc','mview_bl',
                 'vview_f','vview_d','cvview_f','cvview_d',
                 'vview_si','vview_i','vview_uc',
                 'vview_mi', 'vview_vi','vview_bl']
        def __init__(self,view,block):
            self.__jvsip = JVSIP()
            self.__vsipView = view
            self.__pyBlock   = block
            self.__type      =vsip.getType(view)[1]
            self.__major     ='EW'
            self.__scalar = 0
            self.__parent = 0
        def __del__(self):
            del(self.__pyBlock)
            del(self.__jvsip)
            vsip.destroy(self.__vsipView)
        @classmethod
        def supported(cls):
            return cls.tView
        @property
        def supported(self):
            self.supported()
        @classmethod
        def __newView(cls,v,b):
            """
            Given a C VSIP view v which is associated with block b.block
            where b is a pyJvsip block create a new pyJvsip view encapsulating v.
            This method is used internally to create pyJvsip equivalents for
            subviews like rowview, colview, diagview, etc.
            """
            return cls(v,b)
        @classmethod
        def __realview(cls,V):
            views={'vview_f':'real_f', 'vview_d':'real_d',
                   'mview_f':'real_f','mview_d':'real_d'}
            v=vsip.realview(V.view)
            t=views[vsip.getType(v)[1]]
            B=V.block
            l=B.length
            b=vsip.getblock(v)
            newB = B.otherBlock(t,(b,l))
            return cls(v,newB)
        @classmethod
        def __imagview(cls,V):
            views={'vview_f':'real_f', 'vview_d':'real_d',
                   'mview_f':'real_f','mview_d':'real_d'}
            v=vsip.imagview(V.view)
            t=views[vsip.getType(v)[1]]
            B=V.block
            l=B.length
            b=vsip.getblock(v)
            newB = B.otherBlock(t,(b,l))
            return cls(v,newB)

        # Elementwise add, sub, mul, div
        def __iadd__(self,other): # self += other
            add(other,self,self)
            return self
        def __add__(self,other): # new = self + other
            return add(other,self,self.empty)
        def __radd__(self,other): # new = other + self
            return add(other,self,self.empty)
        def __isub__(self,other): # -=other
            if 'pyJvsip.__View' in repr(other):
                sub(self,other,self)
            else:
                add(-other,self,self)
            return self
        def __sub__(self,other):#self - other
            retval=self.empty
            if 'pyJvsip.__View' in repr(other):
                return sub(self,other,retval)
            else:
                return add(-other,self,retval)
        def __rsub__(self,other): #other - self
            retval=self.empty
            return sub(other,self,retval)
        def __imul__(self,other):# *=other
            mul(other,self,self)
            return self
        def __mul__(self,other):
            return mul(other,self,self.empty)
        def __rmul__(self,other): # other * self
            return mul(other,self,self.empty)
        def __idiv__(self,other):
            if 'pyJvsip.__View' in repr(other):
                div(self,other,self)
            elif isinstance(other,int) or isinstance(other,float) or isinstance(other,long):
                div(self,other,self)
            elif isinstance(other,complex):
                mul(1.0/other,self,self)
            else:
                print('idiv divisor not recognized')
            return self
        def __div__(self,other):
            if isinstance(other,complex):
                return mul(1.0/other,self,self.empty)
            else:
                return div(self,other,self.empty)
        def __rdiv__(self,other): # other / self
            return div(other,self,self.empty)
        def __neg__(self):
            return neg(self,self)
        @property
        def list(self):
            f = {'cvview_f':'cvcopyToList_f(self.view)',
                 'cvview_d':'cvcopyToList_d(self.view)',
                 'vview_f':'vcopyToList_f(self.view)',
                 'vview_d':'vcopyToList_d(self.view)',
                 'vview_i':'vcopyToList_i(self.view)',
                 'vview_si':'vcopyToList_si(self.view)',
                 'vview_uc':'vcopyTolist_uc(self.view)',
                 'vview_vi':'vcopyToList_vi(self.view)',
                 'vview_mi':'vcopyToList_mi(self.view)'}
            fByRow = {'cmview_f':'cmcopyToListByRow_f(self.view)',
                      'mview_f':'mcopyToListByRow_f(self.view)',
                      'cmview_d':'cmcopyToListByRow_d(self.view)',
                      'mview_d':'mcopyToListByRow_d(self.view)',
                      'mview_i':'mcopyToListByRow_i(self.view)',
                      'mview_si':'mcopyToListByRow_si(self.view)',
                      'mview_uc':'mcopyToListByRow_uc(self.view)'}
            fByCol = {'cmview_f':'cmcopyToListByCol_f(self.view)',
                      'mview_f':'mcopyToListByCol_f(self.view)',
                      'cmview_d':'cmcopyToListByCol_d(self.view)',
                      'mview_d':'mcopyToListByCol_d(self.view)',
                      'mview_i':'mcopyToListByCol_i(self.view)',
                      'mview_si':'mcopyToListByCol_si(self.view)',
                      'mview_uc':'mcopyToListByCol_uc(self.view)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            elif 'ROW' in self.major and fByRow.has_key(self.type):
                return eval(fByRow[self.type])
            elif 'COL' in self.major and fByCol.has_key(self.type):
                return eval(fByCol[self.type])
            elif self.type in Block.vectorTypes:
                return vsip.vList(self.view)
            elif self.type in Block.matrixTypes:
                return vsip.mList(self.view)
            else:
                print('Type not a matrix or vector')
                return False
        def __getitem__(self,index):
            def scalarVal(val):
                if 'cscalar' in vsip.getType(val)[1]:
                    c=complex(val.r,val.i)
                    return c
                elif isinstance(val,int) or isinstance(val,long):
                    return int(val)
                elif isinstance(val,float) or isinstance(val,complex):
                    return val
                elif 'scalar_mi' in vsip.getType(val)[1]:
                    return {'row_index':val.r,'col_index':val.i}
                else:
                    print('__getitem__ does not recognize<:' +type(val)+ ':>')
                    return False
            if 'vview' in self.type and isinstance(index,int) and index >= 0:
                assert index < self.length,'Index out of bounds'
                val=vsip.get(self.view,index)
                return scalarVal(val)
            elif 'vview' in self.type and isinstance(index,slice):
                return self.subview(index)
            elif 'mview' in self.type and (len(index) is 2) and \
                        isinstance(index[0],int) and isinstance(index[1],int) \
                        and (index[0] >=0) and (index[1] >= 0):
                assert index[0] < self.collength and index[1] < self.rowlength,\
                        'Index out of bound'
                i = (index[0],index[1])
                val=vsip.get(self.view,i)
                return(scalarVal(val))
            elif 'mview' in self.type and (len(index) is 2) and \
                        isinstance(index[0],slice) and isinstance(index[1],slice):
                return self.subview(index[0],index[1])
            elif 'mview' in self.type and (len(index) is 2) and \
                        isinstance(index[0],slice) and isinstance(index[1],int):
                return self.subview(index[0],slice(index[1],index[1]+1,1))
            elif 'mview' in self.type and (len(index) is 2) and \
                        isinstance(index[0],int) and isinstance(index[1],slice):
                return self.subview(slice(index[0],index[0]+1,1),index[1])
            else:
                print('Failed to parse index arguments')
                return
        def __setitem__(self,i,value):
            if 'vview' in self.type:
                if isinstance(i,int) or isinstance(i,long):
                    assert i >= 0 and i < self.length,'Index out of bound'
                    if('cvview' in self.type):
                        vsip.put(self.view,i,complex(value.real,value.imag))
                    else:
                        vsip.put(self.view,i,value)
                elif isinstance(i,slice) and (isinstance(value,int)\
                        or isinstance(value,long) or isinstance(value,float)):
                    self.subview(i).fill(value)
                elif isinstance(i,slice):
                    copy(value,self.subview(i))
                else:
                    print('Failed to recognize index for vector view')
            elif 'mview' in self.type and isinstance(i,tuple) and len(i) == 2:
                if isinstance(i[0],slice) and isinstance(i[1],slice):
                    copy(value,self.subview(i[0],i[1]))
                elif isinstance(i[0],slice) and isinstance(i[1],int):
                    assert i[1] >= 0 and i[1] < self.collength,'Row index out of bound'
                    copy(value,self.subview(i[0],slice(i[1],i[1]+1,1)))
                elif (isinstance(i[0],int) and isinstance(i[1],slice)):
                    copy(value,self.subview(slice(i[0],i[0]+1,1),i[1]))
                elif (isinstance(i[0],int) or isinstance(i[0],long)) \
                     and (isinstance(i[1],int) or isinstance(i[1],long)):
                    assert i[0] >= 0 and i[0] < self.collength and i[1] >=0 and i[1] < self.collength,\
                           'Index out of bound'
                    if 'cmview' in self.type:
                        vsip.put(self.view,i,complex(value.real,value.imag))
                    else:
                        vsip.put(self.view,i,value)
                else:
                    print('Failed to recognize index for matrix view')
            else:
                print('Failed to parse argument list for __setitem__')
        def __delitem__(self,key): #drop index key
            assert isinstance(key,int) or isinstance(key,long) or isinstance(key,tuple),\
                 'Key must be an integer index or a tuple pair of index integers'
            if isinstance(key,int) or isinstance(key,long):
                i = key
                if 'vview' in self.type:
                    self[i:self.length-1] = self[i+1:self.length].copy # need new copy since overlap exists
                    self.putlength(self.length-1)
                else:
                    if 'COL' in self.major:
                        self[:,i:self.rowlength-1]=self[:,i+1:self.rowlength].copy
                        self.putrowlength(self.rowlength-1)
                    else:
                        self[i:self.collength-1,:]=self[i+1:self.collength,:].copy
                        self.putcollength(self.collength-1)
            else:
                assert 'mview' in self.type,'A tuple key does not work for a vector view'
                assert len(key) == 2, 'Matrix view delete i,j has exactly two integer arguments'
                i=key[0]
                j=key[1]
                assert isinstance(i,int) or isinstance(i,long) and \
                       isinstance(j,int) or isinstance(j,long), 'Integer indices required'
                del self.ROW[i]
                del self.COL[j]
            return self
        def __len__(self):
            attr=vsip.size(self.__vsipView)
            n = attr[2]
            if len(attr) > 3:
                n *= attr[4]
            return int(n)

        # Support functions
        # scalar is a place for the implementation to store a value which can be recovered from the view
        # not sure we need this. Currently not used.
        @property
        def scalar(self):
            val=self.__scalar
            if 'cscalar' in repr(val):
                return complex(self.__scalar.r,self.__scalar.i)
            elif 'scalar_mi' in repr(val):
                return (self.__scalar.r,self.__scalar_c)
            elif 'scalar_bl' in repr(val):
                if self.__scalar == 0:
                    return False
                else:
                    return True
            else:
                return self.__scalar
        # EW, COL, ROW, MAT are indicators of how the view is to be used
        @property
        def EW(self):
            self.__major = 'EW'
            return self
        @property
        def COL(self):
            self.__major = 'COL'
            return self
        @property
        def ROW(self):
            self.__major = 'ROW'
            return self
        @property
        def MAT(self):
            self.__major = 'MAT'
            return self
        def compactAttrib(self,b):
            """Function used for introspection of view objects. Output useful for creating
               attributes needed for creation of new views based on existing views.
               usage:
                 attr=compactAttrib(b)
                 attr is a tuple with three entries.
                 attr[0] is the block type of self if b is 0 (see below for b is 1).
                 attr[1] is len(self)
                 attr[2] is an attribute (tuple) suitable for entry into bind.
               NOTE:
               if b is 1 (not 0) and self.block.type is real then attr[0] will be complex
               if b is 1 and self.block.type is complex then attr[0] will be real
               if self.block.type is not in Block.complexTypes then b is treated as 0
                 and the actual value passed in is ignored
            """
            tdict={'block_f':'cblock_f','block_d':'cblock_d',
                   'cblock_f':'block_f','cblock_d':'block_d'}
            cdict={'real_d':'block_d','real_f':'block_f',\
                   'imag_d':'block_d','imag_f':'block_f'}
            t = self.block.type
            if t in Block.tBlock and b != 0:
                t=tdict[t]
            elif cdict.has_key(t):
                t=cdict[t]
            length = len(self)
            if self.type in Block.vectorTypes:
                attr=(0,1,length)
            elif self.type in Block.matrixTypes:
                size=vsip.size(self.view)
                if size[1] < size[3]:
                    attr=(0,      1,size[2],size[2],size[4])
                else:
                    attr=(0,size[4],size[2],      1,size[4])
            else:
                print('Type <:' + self.type + ':> not supported for compactAttrib')
                return False
            return (t,length,attr)
        @property
        def empty(self):
            """
            A way to get a new view and data space of the same size.
            creates a new view, on a new block, of the same type and shape as
            the calling view. No copy or initialization takes place, so new view
            is empty, so-to-speak.
            """
            attr=self.compactAttrib(0)
            b = self.block.otherBlock(attr[0],attr[1])
            return b.bind(attr[2])
        @property
        def otherEmpty(self):
            """
            A way to get a new complex view and data space of the same size and precision as a real view.
            creates a new complex view on a new block with the same shape and precision as
            the calling view. No copy or initialization takes place, so new view
            is empty, so-to-speak.
            """
            attr=self.compactAttrib(1)
            b = self.block.otherBlock(attr[0],attr[1])
            return b.bind(attr[2])
        @property # returns deep (new view and new block) copy of object including data
        def copy(self):
            """For vector or matrix A then
               B = A.copy will create a compact view B which is a copy
               of A. Note compact means the view exactly fits in the Block
               with unit stride in the major direction. The block is new
               and not the same block associated with A.
               This is an easy way to create a new data space for out of place
               operations.
               For instance:
                   B = A.copy.sin
               will leave A alone, copy its elements to new view (and block) B
               and then do an in-place sine operation on B.
            """
            return copy(self,self.empty)
        @property
        def copyrm(self):
            """ Same as copy method except if the view is a matrix it is created with
                unit stride along the rows.
            """
            if 'mview' in self.type:
                attr=self.compactAttrib(0)
                b = self.block.otherBlock(attr[0],attr[1])
                cl=self.collength; rl=self.rowlength
                o=0; rs=1;cs=rl
                newView = b.bind(o,cs,cl,rs,rl)
                vsip.copy(self.view,newView.view)
                return newView
            else:
                return self.copy
        @property
        def copycm(self):
            """ Same as copy method except if the view is a matrix it is created with
                unit stride along the Columns.
            """
            if 'mview' in self.type:
                attr=self.compactAttrib(0)
                b = self.block.otherBlock(attr[0],attr[1])
                cl=self.collength; rl=self.rowlength
                o=0; rs=cl;cs=1
                newView = b.bind(o,cs,cl,rs,rl)
                vsip.copy(self.view,newView.view)
                return newView
            else:
                return self.copy
        @property # A way to get a new in-place view of the object
        def clone(self):
            v=vsip.cloneview(self.view)
            b=self.block
            return self.__newView(v,b)

        def subview(self,*vals):
            """usage:
               Using Slice (pyJvsip slice does not support negatives at this time):
               For Vector slice=slice(first element, last element+1, stride)
               For Matrix first slice selects rows, second slice selects columns
               Beginning index of slice is included. Ending index is not (python like)
               slice1=slice(first row, last row + 1, stride through column)
               slice2=slice(first col, last col + 1, stride through row)
               Using Index:
               For vector v (example):
                   vs=v.subview(slice(2,len(v),1)) is the same as
                   vs=v.subview(2) or vs=v.subview(2,len(v)-1) or vs=v.subview(2,len(v),1)
                   and
                   vs=v.subview(slice(2,8,2) is the same ags
                   vs=v.subview(2,7,2)
               For matrix first pair is top left corner (row,col)
               For matrix second pair is bottom right corner (row,col) inclusive
               for matrix third pair is (stride through col, stride through row)
               given view aView then
                  anotherView = aView.subview(vals[0],...)
               where:
                  vals is index or
                          index, end_index or
                          index, end_index, stride
                       for a vector
                  vals is row_index,col_index or
                          row_index,col_index, end_row_index, end_col_index or
                          row_index,col_index, end_row_index, end_col_index, colstride, rowstride
                       for a matrix
               anotherView is a view on the same block and data as aView.
               Offset, strides and lengths are defined on aView, not the block.
               Note that strides are along a dimension not through the block so that
               to select every other element of the parent view one would use a stride
               of two for both row and column. (This is Not how one works when setting
               strides through blocks.)
            """
            def nlength(b,e,s): #begin(start),end(stop),step(step)=>b,e,s
                d=int(e)-int(b)
                chk=d%int(s)
                if chk is 0:
                    return d//int(s)
                else:
                    return (d//int(s)) + 1
            def vAttr(attr,vals):
                o=int(attr.offset); l=int(attr.length); strd=int(attr.stride);
                if len(vals) == 1 and isinstance(vals[0],slice):
                    slc=vals[0] # this is (start index, stop index, step)
                    step=slc.step
                    if step is None:
                        step=1
                    #for VSIP we need start offset into block, new length, new stride
                    start=slc.start
                    if start is None:
                        start=0
                    no=start * strd + o                       #new offset
                    ns=step * strd                            #new stride stride
                    stop = slc.stop
                    if (stop is None) or (stop > l):
                        stop = l
                    nl=int(nlength(start,stop,step))  #new length
                elif len(vals) == 1 and isinstance(vals[0],int):
                    return vAttr(attr,(slice(vals[0],l,1),))
                elif len(vals) == 2 and isinstance(vals[0],int) \
                                    and isinstance(vals[1],int):
                    return vAttr(attr,(slice(vals[0],vals[l]+1,1),))
                elif len(vals) == 3 and isinstance(vals[0],int) \
                                    and isinstance(vals[1],int) \
                                    and isinstance(vals[2],int):
                    return vAttr(attr,(slice(vals[0],vals[1]+1,vals[2]),))
                else:
                    print('Failed to parse subview arguments for vector')
                    return False
                return (no,ns,nl)
            def mAttr(attr,vals):
                o=int(attr.offset)
                cl=int(attr.col_length); cs=int(attr.col_stride)
                rl=int(attr.row_length); rs=int(attr.row_stride);
                if len(vals) == 2 and isinstance(vals[0],slice) and isinstance(vals[1],slice):
                    rslc=vals[1]; cslc=vals[0]
                    cstep=cslc.step;rstep=rslc.step;
                    if cstep is None:
                        cstep=1
                    if rstep is None:
                        rstep=1
                    rstart=rslc.start;cstart=cslc.start
                    if rstart is None:
                        rstart = 0
                    if cstart is None:
                        cstart = 0
                    no=rstart * rs + cstart * cs + o
                    ncs=int(cstep * cs)
                    stop = cslc.stop
                    if (stop > cl) or (stop is None):
                        stop = cl
                    ncl= int(nlength(cstart,stop,cstep))
                    nrs=rstep * rs
                    stop = rslc.stop
                    if (stop > rl) or (stop is None):
                        stop = rl
                    nrl= int(nlength(rstart,stop,rstep))
                elif len(vals) == 2 and isinstance(vals[0],int) and isinstance(vals[1],int):
                    return mAttr(attr,(slice(vals[0],cl,1),slice(vals[1],rl,1)))
                elif len(vals) == 4 and isinstance(vals[0],int) and isinstance(vals[1],int) \
                                    and isinstance(vals[2],int) and isinstance(vals[3],int):
                    return mAttr(attr,(slice(vals[0],vals[2]+1,1),slice(vals[1],vals[3]+1,1)))
                elif len(vals) == 6 and isinstance(vals[0],int) and isinstance(vals[1],int) \
                                    and isinstance(vals[2],int) and isinstance(vals[3],int) \
                                    and isinstance(vals[4],int) and isinstance(vals[5],int):
                    return mAttr(attr,(slice(vals[0],vals[2]+1,vals[4]),slice(vals[1],vals[3]+1,vals[5])))
                else:
                    return False
                return (no,ncs,ncl,nrs,nrl)
            attr = vsip.getattrib(self.view)
            if self.type in Block.vectorTypes:
                return self.block.bind(vAttr(attr,vals))
            elif self.type in Block.matrixTypes:
                return self.block.bind(mAttr(attr,vals))
            else: #should not be able to get here
                print('object not supported for subview')
                return False
        def submatrix(self,rows,cols,*vals):
            """ Ussage for matrix m:
                   s = m.submatrix(rows, cols)
                or
                   s=m.submatrix(rows,cols,'COL')
                The method submatrix will create a new data space and copy the indicated
                submatrix values into the new matrix.
                The default submatrix is row major. If the last argument is a string
                which contains 'COL' then the submatrix will be column major.
                If the index entries (rows,cols) are an integer then the submatrix will
                be the input matrix values minus the row and column crossing at (rows,cols).
                If rows and cols are vectors of type vector index then the submatrix will
                of size (rows.length, cols.length) and will consist of the entries contained
                in the rows and columns indicated by the indices in the index vector.
            """
            if isinstance(rows,int) and isinstance(cols,int):
                m=self.collength-1
                n=self.rowlength-1
                if len(vals) > 0 and 'COL' in vals[0]:
                    retval=Block(self.block.type,m*n).bind(0,1,m,m,n)
                else:
                    retval=Block(self.block.type,m*n).bind(0,n,m,1,n)
                retval[0:rows,0:cols]=self[0:rows,0:cols]
                retval[rows:m,0:cols]=self[rows+1:m+1,0:cols]
                retval[0:rows,cols:n]=self[0:rows,cols+1:n+1]
                retval[rows:m,cols:n]=self[rows+1:m+1,cols+1:n+1]
                return retval
            elif 'vview_vi' == rows.type and 'vview_vi' == cols.type:
                m = rows.length
                n = cols.length
                if len(vals) > 0 and 'COL' in vals[0]:
                    retval=Block(self.block.type,m*n).bind(0,1,m,m,n)
                else:
                    retval=Block(self.block.type,m*n).bind(0,n,m,1,n)
                for i in range(n):
                    v=retval.colview(i)
                    v.gather(self.colview(i),rows)
                return retval

            else:
                print('Submatrix uses vector views of type vector index')
                return
        @property
        def attrib(self):
            attr=vsip.getattrib(self.view)
            if 'vview' in self.type:
                return {'offset':attr.offset,'stride':attr.stride,'length':attr.length}
            elif 'mview' in self.type:
                return {'offset':attr.offset,
                        'colstride':attr.col_stride,'collength':attr.col_length,
                        'rowstride':attr.row_stride,'rowlength':attr.row_length}
            else:
                print('Object type not supported for attrib')
                return False
        def putattrib(self,attrib):
            if 'mview' in self.type:
                if 'collength' in attrib:
                    attr=vsip.getattrib(self.view)
                    attr.offset = attrib['offset']
                    attr.row_length = attrib['rowlength']
                    attr.col_length = attrib['collength']
                    attr.row_stride = attrib['rowstride']
                    attr.col_stride = attrib['rowstride']
                    vsip.putattrib(self.view,attr)
                    return self
                else:
                    print('Input attribute does not appear to be for a matrix')
                    return False
            elif 'vview' in self.type:
                if 'length' in attrib:
                    attr=vsip.getattrib(self.view)
                    attr.offset = attrib['offset']
                    attr.stride = attrib['stride']
                    attr.length = attrib['length']
                    vsip.putattrib(self.view,attr)
                    return self
                else:
                    print('Input attribute does not appear to be for a vector')
                    return False
            else:
                print('Type must be a matrix or vector')
                return False
        @property
        def view(self):
            return self.__vsipView
        @property
        def compact(self):
            if self.type in Block.vectorTypes:
                if self.stride == 1:
                    return True
                else:
                    return False
            elif self.type in Block.matrixTypes:
                attrib=self.attrib
                if attrib['colstride'] == 1 and attrib['rowstride'] == attrib['collength']:
                    return True
                elif attrib['rowstride'] == 1 and attrib['colstride'] == attrib['rowlength']:
                    return True
                else:
                    return False
            else:
                print('Type not a matrix or vector view')
                return False
        @property
        def major(self):
            """ This is an attribute that is used to determine certain functionality.
                The major attribue does NOT necessarily agree with the smallest stride direction.
            """
            return self.__major
        def colview(self,j):
            if self.type in Block.matrixTypes:
                v = vsip.colview(self.view,j)
                return self.__newView(v,self.block)
            else:
                print('view not a matrix type')
                return False
        def rowview(self,i):
            if self.type in Block.matrixTypes:
                v=vsip.rowview(self.view,i)
                return self.__newView(v,self.block)
            else:
                print('view not a matrix type')
                return False
        def diagview(self,i):
            if self.type in Block.matrixTypes:
                v = vsip.diagview(self.view,i)
                return self.__newView(v,self.block)
        @property
        def transview(self):
            if 'mview' in self.type:
                return self.__newView(vsip.transview(self.view),self.block)
            else:
                print('Method transview only works on matrix views')
                return False
        @property
        def realview(self):
            v=self.__realview(self)
            v.__parent=self
            return v
        @property
        def imagview(self):
            v = self.__imagview(self)
            v.__parent=self
            return v
        @property
        def mrowview(self):
            """
            The method mrowview is used to convert a vector into a matrix with row length equal self.length
            and column length equal one.
            No (direct) C VSIPL equivalent
            """
            if 'vview' in self.type:
                return self.block.bind(self.offset,1,1,self.stride,self.length)
            else:
                print('The mrowview method only works with a vview input')
                return
        @property
        def mcolview(self):
            """
            The method mcolview is used to convert a vector into a matrix with column length equal self.length
            and row length equal one.
            No (direct) C VSIPL equivalent
            """
            if 'vview' in self.type:
                return self.block.bind(self.offset,self.stride,self.length,1,1)
            else:
                print('The mcolview method only works with a vview input')
                return
        #view attributes.
        @property
        def offset(self):
            return int(vsip.getoffset(self.view))
        def putoffset(self,o):
            vsip.putoffset(self.view,o)
            return self
        @property
        def length(self):
            if self.type in Block.vectorTypes:
                return int(vsip.getlength(self.view))
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        def putlength(self,length):
            if self.type in Block.vectorTypes:
                vsip.putlength(self.view,length)
                return self
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        @property
        def stride(self):
            if self.type in Block.vectorTypes:
                return int(vsip.getstride(self.view))
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        def putstride(self,stride):
            if self.type in Block.vectorTypes:
                vsip.putstride(self.view,stride)
                return self
            elif self.type in Block.matrixTypes:
                print('View not a vector type')
                return False
            else:
                print('Object not of the proper type')
                return False
        @property
        def rowlength(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return int(vsip.getrowlength(self.view))
            else:
                print('Object not of the proper type')
                return False
        def putrowlength(self,length):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putrowlength(self.view,length)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def collength(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return int(vsip.getcollength(self.view))
            else:
                print('Object not of the proper type')
                return False
        def putcollength(self,length):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putcollength(self.view,length)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def rowstride(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return int(vsip.getrowstride(self.view))
            else:
                print('Object not of the proper type')
                return False
        def putrowstride(self,stride):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putrowstride(self.view,stride)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def colstride(self):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                return int(vsip.getcolstride(self.view))
            else:
                print('Object not of the proper type')
                return False
        def putcolstride(self,stride):
            if self.type in Block.vectorTypes:
                print('View not a matrix type')
                return False
            elif self.type in Block.matrixTypes:
                vsip.putcolstride(self.view,stride)
                return self
            else:
                print('Object not of the proper type')
                return False
        @property
        def block(self):
            return self.__pyBlock
        @property
        def type(self):
            return self.__type
        # window (data taper) functions
        def cheby(self,ripple):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_cheby_f,
               'vview_d':vsip_vcreate_cheby_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),ripple,0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support function cheby')
        def kaiser(self,beta):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_kaiser_f,
               'vview_d':vsip_vcreate_kaiser_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),beta,0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support function kaiser')
        @property
        def blackman(self):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_blackman_f,
               'vview_d':vsip_vcreate_blackman_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support property blackman')
        @property
        def hanning(self):
            t=vsip.getType(self.view)[1]
            f={'vview_f':vsip_vcreate_hanning_f,
               'vview_d':vsip_vcreate_hanning_d}
            if f.has_key(t):
                v=f[t](vsip.getlength(self.view),0)
                vsip.copy(v,self.view)
                vsip.allDestroy(v)
                return self
            else:
                print('View type <:' + t +':> does not support property blackman')

        # ### ### ### Element-wise methods
        # Elementary math functions
        @property
        def acos(self):
            acos(self,self)
            return self
        @property
        def asin(self):
            asin(self,self)
            return self
        def atan(self):
            return atan(self,self)
        # atan2 only supported by function call
        @property
        def cos(self):
            cos(self,self)
            return self
        @property
        def cosh(self):
            cosh(self,self)
            return self
        @property
        def exp(self):
            exp(self,self)
            return self
        @property
        def exp10(self):
            exp10(self,self)
            return self
        @property
        def log(self):
            log(self,self)
            return self
        @property
        def log10(self):
            log10(self,self)
            return self
        @property
        def sin(self):
            sin(self,self)
            return self
        @property
        def sinh(self):
            sinh(self,self)
            return self
        @property
        def sqrt(self):
            sqrt(self,self)
            return self
        @property
        def tan(self):
            tan(self,self)
            return self
        @property
        def tanh(self):
            tanh(self,self)
            return self
        # ### Unary Operations
        @property
        def arg(self):
            """ Done out-of-place
                Input vector is of type complex
                Output vector of type real created by arg method and returned.
            """
            attrs=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            return arg(self,out)
        @property
        def conj(self):
            """
            Done In Place. For out of place use self.copy.conj.
            """
            if self.type in ['vview_d','vview_f','mview_d','mview_f']:
                return self
            else:
                return conj(self,self)
        @property
        def cumsum(self):
            """
            Done In-Place
            If Matrix major flag should be set for direction of cumulative sum.
            If a copy is done to preserve calling view place major after copy
            Ex
               a.COL.cumsum
               b = a.copy.COL.cumsum
            """
            return cumsum(self,self)
        @property
        def euler(self):
            """
            Not done In-Place
            Input vector of type real
            Method euler creates and returns a new output vector of type complex
            """
            attrs=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            return euler(self,out)
        @property
        def mag(self):
            """
              View property mag is an out-of-place operation
              Usage:
                 y=x.mag
              Where:
                 x is a view object
                 y is a view object of type real and precision and size the same as x
              Note:
                 y is created internal to the property. If x is real then y.type
                 is the same as x.type. If x is complex then y is real.
            """
            f = ['cmview_d', 'cmview_f', 'cvview_d', 'cvview_f', 'mview_d',
                 'mview_f', 'vview_d', 'vview_f', 'vview_i', 'vview_si']
            assert self.type in f, 'Type <:%s:> not recognized for magsq'%self.type
            if 'cmview' in self.type or 'cvview' in self.type:
                attr=self.compactAttrib(1)
            else:
                attr=self.compactAttrib(0)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            return mag(self,out)
        @property
        def magsq(self):
            """
              View property magsq is an out-of-place operation
              Usage:
                 y=x.magsq
              Where:
                 x is a complex view object
                 y is a view object of type real and precision and size the same as x
              Note:
                 y is created internal to the property.
            """
            f=['cvview_f','cvview_d','cmview_f','cmview_d']
            assert self.type in f, 'Type <:%s:> not recognized for magsq'%self.type
            attr=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            return magsq(self,out)
        # modulate
        @property
        def neg(self):
            """
            Done In place
            Returns a convenience copy.
            For out of place, for view x, do y = x.copy.neg
            """
            return neg(self,self)
        @property
        def recip(self):
            return recip(self,self)
        @property
        def rsqrt(self):
            return rsqrt(self,self)
        @property
        def sq(self):
            return sq(self,self)
        @property
        def sumval(self):
            """returns a scalar
            """
            f={'cmview_d':vsip_cmsumval_d,'cvview_d':vsip_cvsumval_d,'cmview_f':vsip_cmsumval_f,
               'cvview_f':vsip_cvsumval_f,'mview_d':vsip_msumval_d,'vview_d':vsip_vsumval_d,
               'mview_f':vsip_msumval_f,'vview_f':vsip_vsumval_f,'vview_i':vsip_vsumval_i,
               'vview_si':vsip_vsumval_si,'vview_uc':vsip_vsumval_uc,'mview_bl':vsip_msumval_bl,
               'vview_bl':vsip_vsumval_bl}
            assert f.has_key(self.type), 'Type <:%s:> not recognized for sumval'%self.type
            if 'cmview' in self.type or 'cvview' in self.type:
                x=f[self.type](self.view)
                return complex(x.r,x.i)
            elif '_f' in self.type or '_d' in self.type:
                return f[self.type](self.view)
            else:
                return int(f[self.type](self.view))
        @property
        def sumsqval(self):
            """ returns a scalar
            """
            f={'mview_d':vsip_msumsqval_d, 'vview_d':vsip_vsumsqval_d,
                'mview_f':vsip_msumsqval_f, 'vview_f':vsip_vsumsqval_f}
            assert f.has_key(self.type),'Type <:%s:> not recognized for sumsqval'%self.type
            return f[self.type](self.view)

        # ### Binary
        # add, mull, div, sub incorporated into python built in __add__, __div__, __sub__, etc.
        def mmul(self,other):
         #vector-matrix elementwise multiply by row or col
            """
            Input matrix is overwritten by the operation.
            mmul(A) expects the calling view to be of type float vector and A to be of
            the same precision and type float matrix. Matrix A is returned as a convenience.
            Note that view A has an a major attribute. If it is set to COL then the calling vector
            is multiplied elementwise by COL, otherwise it is multiplied by ROW
            Note lengths must be conformant.
            If one is unsure of the state of the major attribute it should be set
            For instance
            v.mmul(A.ROW)
            or
            v.mmul(A.COL)
            Done in place. v.mmul(A) returns the result in A.
            B = v.mmul(A.copy.COL) returns the result in a new matrix.
            """
            return mmul(self,other,other)
        @property
        def meansqval(self):
            """ returns scalar value
            """
            f={'cmview_d':vsip_cmmeansqval_d,'cvview_d':vsip_cvmeansqval_d,'cmview_f':vsip_cmmeansqval_f,
               'cvview_f':vsip_cvmeansqval_f,'mview_d':vsip_mmeansqval_d,'vview_d':vsip_vmeansqval_d,
               'mview_f':vsip_mmeansqval_f,'vview_f':vsip_vmeansqval_f}
            assert f.has_key(self.type), 'Type <:%s:> not recognized for meansqval'%self.type
            return f[self.type](self.view)
        @property
        def meanval(self):
            """ returns scalar value
            """
            f={'cmview_d':vsip_cmmeanval_d,'cvview_d':vsip_cvmeanval_d,'cmview_f':vsip_cmmeanval_f,
               'cvview_f':vsip_cvmeanval_f,'mview_d':vsip_mmeanval_d,'vview_d':vsip_vmeanval_d,
               'mview_f':vsip_mmeanval_f,'vview_f':vsip_vmeanval_f}
            assert f.has_key(self.type), 'Type <:%s:> not recognized for meanval'%self.type
            return f[self.type](self.view)

        #logical operations
        @property
        def alltrue(self):
            f={'mview_bl':vsip_malltrue_bl,
               'vview_bl':vsip_valltrue_bl}
            t=self.type
            if f.has_key(t):
                return 1 == f[t](self.view)
            else:
                print('Type ' + t + ' not a defined type for alltrue')
        @property
        def anytrue(self):
            f={'mview_bl':vsip_manytrue_bl,
               'vview_bl':vsip_vanytrue_bl}
            t=self.type
            if f.has_key(t):
                return 1 == f[t](self.view)
            else:
                print('View type must be boolean for alltrue')
        def leq(self,other):
            """
            Logical Equal
            Usage:
               b=x.leq(y)
               y may be of type x.type or a scalar.
               b is a boolean. if x[i] == y[i] the b[i]=1 (true) else 0 (false)
               if y is a scalar if x[i] == y then b[i] = 1
            Note this works for a matrix also. The index changes to (i,j)
            """
            if isinstance(other,complex) or 'cscalar' in repr(other):
                print('complex scalars not supported at this time for leq')
                return
            t0=getType(other)
            if 'scalar' in t0[1]:
                t = self.type+t0[1]
            else:
                t=self.type+other.type
            if 'mview' in self.type:
                m=self.collength
                n=self.rowlength
                out=create('mview_bl',m,n)
            else: #must be vector
                out=create('vview_bl',self.length)
            f={'mview_dmview_d':vsip_mleq_d,
               'mview_fmview_f':vsip_mleq_f,
               'vview_dvview_d':vsip_vleq_d,
               'vview_fvview_f':vsip_vleq_f,
               'vview_ivview_i':vsip_vleq_i,
               'vview_sivview_si':vsip_vleq_si,
               'vview_ucvview_uc':vsip_vleq_uc
               }
            fs={'vview_fscalar':vsip_svleq_f,
                'vview_dscalar':vsip_svleq_d}
            if f.has_key(t):
                f[t](self.view,other.view,out.view)
                return out
            elif fs.has_key(t):
                fs[t](other,self.view,out.view)
                return out
            else:
                print('Argument type <:'+t+':> not recognized for leq')
                return
        def lge(self,input):
            """
            Logical Greater Than or Equal
            Usage:
               b=x.lge(y)
               y may be of type x.type or a scalar.
               b is a boolean. if x[i] >= y[i] the b[i]=1 (true) else 0 (false)
               if y is a scalar if x[i] >= y then b[i] = 1
            Note this works for a matrix also. The index changes to (i,j)
            Note this is not equivalent to a C VSIP vsip_svlge_p for the scalar case as the
            scalar is on the wrong side of the test.
            """
            t0=getType(input)
            if 'mview' in self.type:
                m=self.collength
                n=self.rowlength
                out=create('mview_bl',m,n)
            else: #must be vector
                out=create('vview_bl',self.length)
            if 'scalar' in t0[1]:
                if 'mview' in self.type:
                    other = create(self.type,1,1).fill(input)
                    attr=self.attrib
                    attr['offset']=0
                    attr['rowstride']=0; attr['colstride']=0
                    other.putattrib(attr)
                else:
                    attr=self.attrib
                    other = create(self.type,1).fill(input)
                    attr['offset']=0;attr['stride']=0;other.putattrib(attr)
            else:
                other=input
            t=self.type+other.type
            f={'mview_dmview_d':vsip_mlge_d,
               'mview_fmview_f':vsip_mlge_f,
               'vview_dvview_d':vsip_vlge_d,
               'vview_fvview_f':vsip_vlge_f,
               'vview_ivview_i':vsip_vlge_i,
               'vview_sivview_si':vsip_vlge_si,
               'vview_ucvview_uc':vsip_vlge_uc}
            if f.has_key(t):
                f[t](self.view,other.view,out.view)
                return out
            else:
                print('Argument type <:'+t+':> not recognized for lge')
                return
        def lgt(self,input):
            """
            Logical Greater Than
            Usage:
               b=x.lgt(y)
               y may be of type x.type or a scalar.
               b is a boolean. if x[i] > y[i] the b[i]=1 (true) else 0 (false)
               if y is a scalar if x[i] > y then b[i] = 1
            Note this works for a matrix also. The index changes to (i,j)
            Note this is not equivalent to a C VSIP vsip_svlgt_p for the scalar case as the
            scalar is on the wrong side of the test.
            """
            t0=getType(input)
            if 'mview' in self.type:
                m=self.collength
                n=self.rowlength
                out=create('mview_bl',m,n)
            else: #must be vector
                out=create('vview_bl',self.length)
            if 'scalar' in t0[1]:
                if 'mview' in self.type:
                    other = create(self.type,1,1).fill(input)
                    attr=self.attrib
                    attr['offset']=0
                    attr['rowstride']=0; attr['colstride']=0
                    other.putattrib(attr)
                else:
                    attr=self.attrib
                    other = create(self.type,1).fill(input)
                    attr['offset']=0;attr['stride']=0;other.putattrib(attr)
            else:
                other=input
            t=self.type+other.type
            f={'mview_dmview_d':vsip_mlgt_d,
               'mview_fmview_f':vsip_mlgt_f,
               'vview_dvview_d':vsip_vlgt_d,
               'vview_fvview_f':vsip_vlgt_f,
               'vview_ivview_i':vsip_vlgt_i,
               'vview_sivview_si':vsip_vlgt_si,
               'vview_ucvview_uc':vsip_vlgt_uc}
            if f.has_key(t):
                f[t](self.view,other.view,out.view)
                return out
            else:
                print('Argument type <:'+t+':> not recognized for lgt')
                return
        def lle(self,input):
            """
            Logical less than or equal
            Usage:
               b=x.lle(y)
               y may be of type x.type or a scalar.
               b is a boolean. If x[i] <= y[i] then b[i]=1 (true) else 0 (false)
               If y is a scalar if x[i] <= y then b[i] = 1
            Note this works for a matrix also. The index changes to (i,j)
            Note this is not equivalent to a C VSIP vsip_svlle_p for the scalar case as the
            scalar is on the wrong side of the test.
            """
            t0=getType(input)
            if 'mview' in self.type:
                m=self.collength
                n=self.rowlength
                out=create('mview_bl',m,n)
            else: #must be vector
                out=create('vview_bl',self.length)
            if 'scalar' in t0[1]:
                if 'mview' in self.type:
                    other = create(self.type,1,1).fill(input)
                    attr=self.attrib
                    attr['offset']=0
                    attr['rowstride']=0; attr['colstride']=0
                    other.putattrib(attr)
                else:
                    attr=self.attrib
                    other = create(self.type,1).fill(input)
                    attr['offset']=0;attr['stride']=0;other.putattrib(attr)
            else:
                other=input
            f={'mview_dmview_d':vsip_mlle_d,
               'mview_fmview_f':vsip_mlle_f,
               'vview_dvview_d':vsip_vlle_d,
               'vview_fvview_f':vsip_vlle_f,
               'vview_ivview_i':vsip_vlle_i,
               'vview_sivview_si':vsip_vlle_si,
               'vview_ucvview_uc':vsip_vlle_uc}
            t=self.type+other.type
            if f.has_key(t):
                f[t](self.view,other.view,out.view)
                return out
            else:
                print('Argument type <:'+t+':> not recognized for lle')
                return
        def llt(self,input):
            """
            Logical less than
            Usage:
               b=x.llt(y)
               y may be of type x.type or a scalar.
               b is a boolean. If x[i] < y[i] then b[i]=1 (true) else 0 (false)
               If y is a scalar if x[i] < y then b[i] = 1
            Note this works for a matrix also. The index changes to (i,j)
            Note this is not equivalent to a C VSIP vsip_svllt_p for the scalar case as the
            scalar is on the wrong side of the test.
            """
            t0=getType(input)
            if 'mview' in self.type:
                m=self.collength
                n=self.rowlength
                out=create('mview_bl',m,n)
            else: #must be vector
                out=create('vview_bl',self.length)
            if 'scalar' in t0[1]:
                if 'mview' in self.type:
                    other = create(self.type,1,1).fill(input)
                    attr=self.attrib
                    attr['offset']=0
                    attr['rowstride']=0; attr['colstride']=0
                    other.putattrib(attr)
                else:
                    attr=self.attrib
                    other = create(self.type,1).fill(input)
                    attr['offset']=0;attr['stride']=0;other.putattrib(attr)
            else:
                other=input
            t=self.type+other.type
            f={'mview_dmview_d':vsip_mllt_d,
               'mview_fmview_f':vsip_mllt_f,
               'vview_dvview_d':vsip_vllt_d,
               'vview_fvview_f':vsip_vllt_f,
               'vview_ivview_i':vsip_vllt_i,
               'vview_sivview_si':vsip_vllt_si,
               'vview_ucvview_uc':vsip_vllt_uc}
            if f.has_key(t):
                f[t](self.view,other.view,out.view)
                return out
            else:
                print('Argument type <:'+t+':> not recognized for llt')
                return
        def lne(self,other):
            """
            Logical Not Equal
            Usage:
               b=x.lne(y)
               y may be of type x.type or a scalar.
               b is a boolean. if x[i] != y[i] the b[i]=1 (true) else 0 (false)
               if y is a scalar if x[i] != y then b[i] = 1
            Note this works for a matrix also. The index changes to (i,j)
            """
            if 'mview' in self.type:
                m=self.collength
                n=self.rowlength
                out=create('mview_bl',m,n)
            else: #must be vector
                out=create('vview_bl',self.length)
            f={'mview_dmview_d':vsip_mlne_d,
               'mview_fmview_f':vsip_mlne_f,
               'vview_dvview_d':vsip_vlne_d,
               'vview_fvview_f':vsip_vlne_f,
               'vview_ivview_i':vsip_vlne_i,
               'vview_sivview_si':vsip_vlne_si,
               'vview_ucvview_uc':vsip_vlne_uc}
            t=self.type+other.type
            if f.has_key(t):
                f[t](self.view,other.view,out.view)
                return out
            else:
                print('Argument type <:'+t+':> not recognized for lne')
            return

        # Selection Operations
        @property
        def indexbool(self):
            if 'mview_bl' in self.type:
                out = create('vview_mi',self.rowlength*self.collength)
            elif 'vview_bl' in self.type:
                out = create('vview_vi',self.length)
            else:
                print('Method indexbool is only defined for views of type mview_bl or vview_bl')
                return
            if self.anytrue:
                f={'mview_bl':vsip_mindexbool,'vview_bl':vsip_vindexbool}
                f[self.type](self.view,out.view)
                return out
            else:
                print('Method indexbool should only be called if there is at least one true entry')
                return
        def indxFill(self,indx,alpha):
            if 'mview' in self.type:
                lnth = self.rowlength * self.collength
                x=create(self.type,1,1)
                x[0,0]=alpha
                x.putrowlength(self.rowlength); x.putcollength(self.collength)
                x.putrowstride(0);x.putcolstride(0)
            else:
                lnth = self.length
                x=create(self.type,1)
                x[0]=alpha
                x.putlength(self.length)
                x.putstride(0)
            x.scatter(self,indx)
            return self
        @property
        def maxvalindx(self):
            """
            This method returns the index of the first maximum value found.
            """
            f={'mview_d':'vsip_mmaxval_d(self.view,idx)',
              'vview_d':'vsip_vmaxval_d(self.view,idx)',
              'mview_f':'vsip_mmaxval_f(self.view,idx)',
              'vview_f':'vsip_vmaxval_f(self.view,idx)',
              'mview_i':'vsip_mmaxval_i(self.view,idx)',
              'vview_i':'vsip_vmaxval_i(self.view,idx)',
              'mview_si':'vsip_mmaxval_si(self.view,idx)',
              'vview_si':'vsip_vmaxval_si(self.view,idx)',
              'vview_vi':'vsip_vmaxval_vi(self.view.idx)'}
            if f.has_key(self.type):
                if 'mview' in self.type:
                    idx=vsip_scalar_mi()
                    eval(f[self.type])
                    return (int(idx.r),int(idx.c))
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=int(vsip.vindexptrToInt(idx))
                    vsip.vindexfree(idx)
                    return retval
            else:
                print('Type <:'+self.type+':> not supported by maxval')
                return
        @property
        def maxval(self):
            """
            This method returns the maximum value found.
            """
            f={'mview_d':'vsip_mmaxval_d(self.view,None)',
              'vview_d':'vsip_vmaxval_d(self.view,None)',
              'mview_f':'vsip_mmaxval_f(self.view,None)',
              'vview_f':'vsip_vmaxval_f(self.view,None)',
              'mview_i':'vsip_mmaxval_i(self.view,None)',
              'vview_i':'vsip_vmaxval_i(self.view,None)',
              'mview_si':'vsip_mmaxval_si(self.view,None)',
              'vview_si':'vsip_vmaxval_si(self.view,None)',
              'vview_vi':'vsip_vmaxval_vi(self.view,None)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not supported by maxval')
                return
        @property
        def maxmgvalindx(self):
            """
            This method returns the index of the first maximum value found.
            """
            f={'mview_d':'vsip_mmaxmgval_d(self.view,idx)',
               'vview_d':'vsip_vmaxmgval_d(self.view,idx)',
               'mview_f':'vsip_mmaxmgval_f(self.view,idx)',
               'vview_f':'vsip_vmaxmgval_f(self.view,idx)'}
            if f.has_key(self.type):
                if 'mview' in self.type:
                    idx=vsip_scalar_mi()
                    eval(f[self.type])
                    return (int(idx.r),int(idx.c))
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=int(vsip.vindexptrToInt(idx))
                    vsip.vindexfree(idx)
                    return retval
            else:
                print('Type <:'+self.type+':> not supported by maxmgvalindx')
                return
        @property
        def maxmgval(self):
            """
            This method returns the first maximum value found.
            """
            f={'mview_d':'vsip_mmaxmgval_d(self.view,None)',
               'vview_d':'vsip_vmaxmgval_d(self.view,None)',
               'mview_f':'vsip_mmaxmgval_f(self.view,None)',
               'vview_f':'vsip_vmaxmgval_f(self.view,None)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not supported by maxmgval')
                return
        @property
        def maxmgsqvalindx(self):
            """
            This method returns the index of the first maximum complex magnitude squared
            value found.
            """
            f={'cmview_d':'vsip_mcmaxmgsqval_d(self.view,idx)',
               'cvview_d':'vsip_vcmaxmgsqval_d(self.view,idx)',
               'cmview_f':'vsip_mcmaxmgsqval_f(self.view,idx)',
               'cvview_f':'vsip_vcmaxmgsqval_f(self.view,idx)'}
            if f.has_key(self.type):
                if 'mview' in self.type:
                    idx=vsip_scalar_mi()
                    eval(f[self.type])
                    return (int(idx.r),int(idx.c))
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=int(vsip.vindexptrToInt(idx))
                    vsip.vindexfree(idx)
                    return retval
            else:
                print('Type <:'+self.type+':> not supported by maxmgsqvalindx')
                return
        @property
        def maxmgsqval(self):
            """
            This method returns the  maximum complex magnitude squared
            value found..
            """
            f={'cmview_d':'vsip_mcmaxmgsqval_d(self.view,None)',
               'cvview_d':'vsip_vcmaxmgsqval_d(self.view,None)',
               'cmview_f':'vsip_mcmaxmgsqval_f(self.view,None)',
               'cvview_f':'vsip_vcmaxmgsqval_f(self.view,None)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not supported by maxmgsqval')
                return
        @property
        def minvalindx(self):
            """
            This method returns the index of the first minimum value found.
            """
            f={'mview_d':'vsip_mminval_d(self.view,idx)',
              'vview_d':'vsip_vminval_d(self.view,idx)',
              'mview_f':'vsip_mminval_f(self.view,idx)',
              'vview_f':'vsip_vminval_f(self.view,idx)',
              'mview_i':'vsip_mminval_i(self.view,idx)',
              'vview_i':'vsip_vminval_i(self.view,idx)',
              'mview_si':'vsip_mminval_si(self.view,idx)',
              'vview_si':'vsip_vminval_si(self.view,idx)',
              'vview_vi':'vsip_vminval_vi(self.view,idx)'}
            if f.has_key(self.type):
                if 'mview' in self.type:
                    idx=vsip_scalar_mi()
                    eval(f[self.type])
                    return (int(idx.r),int(idx.c))
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=int(vsip.vindexptrToInt(idx))
                    vsip.vindexfree(idx)
                    return retval
            else:
                print('Type <:'+self.type+':> not supported by minval')
                return
        @property
        def minval(self):
            """
            This method returns the minimum value found.
            """
            f={'mview_d':'vsip_mminval_d(self.view,None)',
              'vview_d':'vsip_vminval_d(self.view,None)',
              'mview_f':'vsip_mminval_f(self.view,None)',
              'vview_f':'vsip_vminval_f(self.view,None)',
              'mview_i':'vsip_mminval_i(self.view,None)',
              'vview_i':'vsip_vminval_i(self.view,None)',
              'mview_si':'vsip_mminval_si(self.view,None)',
              'vview_si':'vsip_vminval_si(self.view,None)',
              'vview_vi':'vsip_vminval_vi(self.view,None)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not supported by minval')
                return
        @property
        def minmgvalindx(self):
            """
            This method returns the index of the first minimum value found.
            """
            f={'mview_d':'vsip_mminmgval_d(self.view,idx)',
               'vview_d':'vsip_vminmgval_d(self.view,idx)',
               'mview_f':'vsip_mminmgval_f(self.view,idx)',
               'vview_f':'vsip_vminmgval_f(self.view,idx)'}
            if f.has_key(self.type):
                if 'mview' in self.type:
                    idx=vsip_scalar_mi()
                    eval(f[self.type])
                    return (int(idx.r),int(idx.c))
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=int(vsip.vindexptrToInt(idx))
                    int(vsip.vindexfree(idx))
                    return retval
            else:
                print('Type <:'+self.type+':> not supported by minmgvalindx')
                return
        @property
        def minmgval(self):
            """
            This method returns the first minimum value found.
            """
            f={'mview_d':'vsip_mminmgval_d(self.view,None)',
               'vview_d':'vsip_vminmgval_d(self.view,None)',
               'mview_f':'vsip_mminmgval_f(self.view,None)',
               'vview_f':'vsip_vminmgval_f(self.view,None)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not supported by minmgval')
                return
        @property
        def minmgsqvalindx(self):
            """
            This method returns the index of the first minimum complex magnitude squared
            value found.
            """
            f={'cmview_d':'vsip_mcminmgsqval_d(self.view,idx)',
               'cvview_d':'vsip_vcminmgsqval_d(self.view,idx)',
               'cmview_f':'vsip_mcminmgsqval_f(self.view,idx)',
               'cvview_f':'vsip_vcminmgsqval_f(self.view,idx)'}
            if f.has_key(self.type):
                if 'mview' in self.type:
                    idx=vsip_scalar_mi()
                    eval(f[self.type])
                    return (int(idx.r),int(idx.c))
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=int(vsip.vindexptrToInt(idx))
                    vsip.vindexfree(idx)
                    return retval
            else:
                print('Type <:'+self.type+':> not supported by minmgsqvalindx')
                return
        @property
        def minmgsqval(self):
            """
            This method returns the  minimum complex magnitude squared
            value found..
            """
            f={'cmview_d':'vsip_mcminmgsqval_d(self.view,None)',
               'cvview_d':'vsip_vcminmgsqval_d(self.view,None)',
               'cmview_f':'vsip_mcminmgsqval_f(self.view,None)',
               'cvview_f':'vsip_vcminmgsqval_f(self.view,None)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not supported by minmgsqval')
                return
        #Bitwise and Boolean Logical Operators
        #use bb at fron to avoid conflicts
        def bband(self,other):
            """
            bitwise/boolean and
            """
            f={'mview_i':vsip_mand_i, 'mview_si':vsip_mand_si, 'vview_bl':vsip_vand_bl,
               'vview_i':vsip_vand_i, 'vview_si':vsip_vand_si, 'vview_uc':vsip_vand_uc}
            sptd=['mview_i','mview_si','vview_bl','vview_i','vview_si','vview_uc']
            assert self.length is other.length
            assert self.type in other.type
            assert self.type in sptd
            out=self.empty
            f[self.type](self.view,other.view,out.view)
            return out
        def bbnot(self,other):
            """
            bitwise/boolean and
            """
            f={'mview_i':vsip_mnot_i, 'mview_si':vsip_mnot_si, 'vview_bl':vsip_vnot_bl,
               'vview_i':vsip_vnot_i, 'vview_si':vsip_vnot_si, 'vview_uc':vsip_vnot_uc}
            sptd=['vview_bl','vview_i','vview_si','vview_uc']
            assert self.length is other.length
            assert self.type in other.type
            assert self.type in sptd
            out=self.empty
            f[self.type](self.view,other.view,out.view)
            return out
        def bbor(self,other):
            """
            bitwise/boolean and
            """
            f={'mview_i':vsip_mor_i, 'mview_si':vsip_mor_si, 'vview_bl':vsip_vor_bl,
               'vview_i':vsip_vor_i, 'vview_si':vsip_vor_si, 'vview_uc':vsip_vor_uc}
            sptd=['vview_bl','vview_i','vview_si','vview_uc']
            assert self.length is other.length
            assert self.type in other.type
            assert self.type in sptd
            out=self.empty
            f[self.type](self.view,other.view,out.view)
            return out
        def bbxor(self,other):
            """
            bitwise/boolean and
            """
            f={'mview_i':vsip_mxor_i, 'mview_si':vsip_mxor_si, 'vview_bl':vsip_vxor_bl,
               'vview_i':vsip_vxor_i, 'vview_si':vsip_vxor_si, 'vview_uc':vsip_vxor_uc}
            sptd=['vview_bl','vview_i','vview_si','vview_uc']
            assert self.length is other.length
            assert self.type in other.type
            assert self.type in sptd
            out=self.empty
            f[self.type](self.view,other.view,out.view)
            return out

        # data generators
        def ramp(self,start,increment):
            supportedViews = ['vview_f','vview_d','vview_i','vview_si','vview_uc','vview_vi']
            extended = ['cvview_f','cvview_d']
            if self.type in supportedViews:
                vsip.ramp(start,increment,self.view)
                return self
            elif self.type in extended:
                self.fill(0)
                tmp=self.realview
                tmp.ramp(start,increment)
                return self
            else:
                print('Type <:'+self.type+':> not supported for ramp')
                return False
        def fill(self,aScalar):
            if self.type in Block.complexTypes:
                if '_d' in self.type:
                    if type(aScalar) is complex:
                        vsip.fill(vsip_cmplx_d(aScalar.real,aScalar.imag),self.view)
                    else:
                        vsip.fill(vsip_cmplx_d(aScalar,0.0),self.view)
                else:
                    if type(aScalar) is complex:
                        vsip.fill(vsip_cmplx_f(aScalar.real,aScalar.imag),self.view)
                    else:
                        vsip.fill(vsip_cmplx_f(aScalar,0.0),self.view)
            elif type(aScalar) != complex:
                vsip.fill(aScalar,self.view)
            else:
                print('aScalar must be a type which agrees with vector view')
            return self
        def randn(self,seed):
            gen=Rand('PRNG',seed)
            gen.randn(self)
            return self
        def randu(self,seed):
            gen=Rand('PRNG',seed)
            gen.randu(self)
            return self
        @property
        def identity(self):
            f=['cmview_d','cmview_f','mview_d','mview_f','mview_i','mview_si']
            assert self.type in f,'View of type <:'+self.type+':> not supported by identity'
            self.fill(0)
            self.diagview(0).fill(1)
            return self

        # Manipulation
        # Not supported by view method
        # vsip_scmplx_p
        # vsip_srect_p
        # vsip_spolar_p
        # vsip_dswap_p
        # ### ###
        # supported by view method
        # vsip_dsgather_p
        def gather(self,indx,*vars):
            """
              Usage:
                  self.gather(indx,other)
              or
                  self.gather(indx)
              This function gathers self into other governed by indx.
              If other is not provided the function creates one.
              View other is returned as a convienience
            """
            ot={'cmview_f':'cvview_f','cmview_d':'cvview_d','mview_f':'vview_f',
               'mview_d':'vview_d','cvview_f':'cvview_f','cvview_d':'cvview_d',
               'vview_f':'vview_f','vview_d':'vview_d','vview_i':'vview_i',
               'vview_si':'vview_si','vview_uc':'vview_uc','vview_mi':'vview_mi',
               'vview_vi':'vview_vi'}
            assert len(vars) < 2, 'Gather only supports an index view, or an index view and an output view'
            if len(vars) is 1:
                other = vars[0]
            else:
                other = create(ot[self.type],indx.length)
            gather(self,indx,other)
            return other
        # vsip_simag_p
        @property
        def imag(self):
            """
            A method to get a deep copy of the imaginary part of a complex view.
            """
            return imag(self,self.otherEmpty)
        # vsip_sreal_p
        @property
        def real(self):
            """
            A method to get a deep copy of the real part of a complex view.
            """
            return real(self,self.otherEmpty)
        # vsip_dsscatter_p
        def scatter(self,other,indx):
            """
              Usage:
                  self.scatter(other,indx)
              This function scatters self into other governed by indx
              View other is returned as a convienience
            """
            scatter(self,other,indx)
            return other

        # Basic Algorithms
        # These algorithms are specific to pyJvsip for convenience. No C VSIPL functions are in the C Library.
        def axpy(self,a,x):
            """
               This is commonly called a saxpy (daxpy) for single (double) precision
                      y = a * x + y
               or (algorithmically)
                      y += a * x
               where self and x are vectors of the same type and a is a scalar.
               This is an in-place operation
               For C VSIPL this is implemented using functionality vsip_vsma_p
                  vector-scalar-multiply-(vector)-add
            """
            if 'cvview_d' in self.type:
                t = self.type + 'cscalar_d' + x.type
                if type(a) is complex:
                    alpha=vsip_cmplx_d(a.real, a.imag)
                else:
                    alpha = vsip_cmplx_d(a,0)
            elif 'cvview_f' in self.type:
                t = self.type + 'cscalar_f' + x.type
                if type(a) is complex:
                    alpha=vsip_cmplx_f(a.real, a.imag)
                else:
                    alpha = vsip_cmplx_f(a,0)
            elif type(a) is float or type(a) is int:
                t = self.type + 'scalar' + x.type
                alpha = float(a)
            else:
                print('Type combination for axpy not recognized.')
                print('Should be (scalar,vector view)')
                return False
            f = {'cvview_dcscalar_dcvview_d':vsip_cvsma_d,
                 'cvview_fcscalar_fcvview_f':vsip_cvsma_f,
                 'vview_dscalarvview_d':vsip_vsma_d,
                 'vview_fscalarvview_f':vsip_vsma_f}
            if f.has_key(t):
                f[t](x.view,alpha,self.view,self.view)
                return self
            else:
                print('Type <:'+ t + ':> not a supported type string')
                return False
        def gaxpy(self,A,x):
            """
            Generalized axpy:
                y += Ax
                        where y is vector in R(n), x is vector in R(m),
                        A is matrix R(m,n); Views are float of same precision
            For more general case use gemp
            Note:
              Regular matrix multiply may be faster but gaxpy is an in-place operation.
              If instead you use y=Ax+y then Ax will create a new vector; add it to y into
              another new vector; and then replace the y reference with the new reference.
            """
            if ('vview' in self.type) and ('vview' in x.type) and ('mview' in A.type) \
                         and A.rowlength == x.length and A.collength is self.length:
                attr_A=vsip.getattrib(A.view)
                rs=attr_A.row_stride; cs=attr_A.col_stride
                if rs < cs: #do by ROW
                    t=A.rowview(0)
                    s=A.colstride
                    o=A.offset
                    for i in range(attr_A.col_length):
                        t.putoffset(s*i + o)
                        self[i] += t.dot(x)
                else: #do by col
                    t=A.colview(0)
                    s=A.rowstride
                    o=A.offset
                    for i in range(attr_A.row_length):
                        t.putoffset(s*i + o)
                        self.axpy(x[i],t)
                return self
            else:
                print('Argument list for gaxpy does not appear to be compliant')
                return False
        def opu(self,x,y):
            """
               Outer Product Update:
                 A += x.outer(y)
                 where:
                    A in R(m,n); x in R(m), y in R(n)
               Note:
                 Doing a regular outer product such as
                 A = A + x.outer(y)
                 will create a new matrix for the outer product; create a new matrix
                 for the addition results and then return this matrix into the reference
                 for A. Using A.opu(x,y) will do an in-place operation in A.
            """
            if 'mview' not in self.type:
                print('Calling view must be a matrix for opu')
                return
            # we select a method with the += on the major stride.
            # This may not necessarily be the fastest method if calling matrix
            # has row length >> col length or vice versa
            if self.rowstride < self.colstride: #do by ROW
                t=self.rowview(0)
                s=self.colstride
                o=t.offset
                for i in range(self.collength):
                    t.putoffset(i*s+o)
                    t.axpy(x[i],y)
            else: #do by COL
                t=self.colview(0)
                s=self.rowstride
                o=t.offset
                for i in range(self.rowlength):
                    t.putoffset(i*s+o)
                    t.axpy(y[i],x)
            return self
        def nopu(self,x,y):
            """
               Outer Product Update where you want a minus instead of a :
                 A -= x.outer(y)
                 where:
                    A in R(m,n); x in R(m), y in R(n)
               Note:
                 Doing a regular outer product such as
                 A = A - x.outer(y)
                 will create a new matrix for the outer product; create a new matrix
                 for the addition results and then return this matrix into the reference
                 for A. Using A.opu(x,y) will do an in-place operation in A.
            """
            if 'mview' not in self.type:
                print('Calling view must be a matrix for opu')
                return
            # we select a method with the -= on the major stride.
            # This may not necessarily be the fastest method if calling matrix
            # has row length >> col length or vice versa
            if self.rowstride < self.colstride: #do by ROW
                t=self.rowview(0)
                s=self.colstride
                o=t.offset
                for i in range(self.collength):
                    t.putoffset(i*s+o)
                    t.axpy(-x[i],y)
            else: #do by COL
                t=self.colview(0)
                s=self.rowstride
                o=t.offset
                for i in range(self.rowlength):
                    t.putoffset(i*s+o)
                    t.axpy(-y[i],x)
            return self
        def eroa(self,rFrom,rTo):
            """Elementary Row Operation Add (rows)
               For Matrix A
               A.eroa(i,j)
               will add row 'i' to row 'j' and replace row 'j' with the result
            """
            if 'mview' not in self.type:
                print('Elementary row operations only work with matrix views')
                return
            a1 = self.rowview(rTo)
            a1 += self.rowview(rFrom)
            return ('eroa',(rFrom,rTo))
        def eros(self,r0,r1):
            """Elementary Row Operations Switch (rows)
               For Matrix A
                   A.eros(i,j)
                   will switch row 'i' and row'j' in-place
            """
            if 'mview' not in self.type:
                print('Elementary row operations only work with matrix views')
                return
            a0=self.rowview(r0)
            a1=self.rowview(r1)
            swap(a0,a1)
            return ('eros',(r0,r1))
        def ecos(self,r0,r1):
            """Elementary Column Operations Switch (columns)
               For Matrix A
                   A.ecos(i,j)
                   will switch column 'i' and column 'j' in-place
            """
            if 'mview' not in self.type:
                print('Elementary row operations only work with matrix views')
                return
            a0=self.colview(r0)
            a1=self.colview(r1)
            swap(a0,a1)
            return ('ecos',(r0,r1))
        def erom(self,alpha,r):
            """Elementary Row Operation (scalar) Multiply
               For Matrix A
               A.erom(aScalar,aRowIndex)
               will multiply aScalar times the row of A indexed by aRowIndex in-place
            """
            if 'mview' not in self.type:
                print('Elementary row operations only work with matrix views')
                return
            a=self.rowview(r)
            a *= alpha
            return('erom',(alpha,r))
        @property
        def det(self):
            """ Calculate the determinant of a real matrix.
                Uses elementary row operations and axpy to produce an upper diagonal
                matrix. Done in place.
                The determinant is the product of the diagonal entries.
                Note:
                  Done in place and the input is used up so use a copy method if the input
                  matrix is needed.
            """
            supportedViews = ['mview_f','mview_d']
            assert self.type in supportedViews, 'Determinant only calculated for real matrices of type float or double'
            n=self.rowlength
            m=self.collength
            assert m==n,'For determinant input matrix must be square'
            retval=1.0
            for i in range(n):
                T=self[i:n,i:n]
                k=T.colview(0).maxmgvalindx
                if k != 0:
                    retval = -retval
                    T.eros(0,k)
                pvt=T[0,0]
                if pvt == 0.0:
                    return 0.0
                else:
                    retval *= pvt
                vp=T.rowview(0)
                for j in range(1,T.rowlength):
                    scl=-T[j,0]/pvt
                    T.rowview(j).axpy(scl,vp)
            return retval

        ### plu operations are a demonstration. Should use LU class; or lu, luInv, luSolve.
        @property
        def plu(self):
            """ Calculate an LU decomposition with a row permutation vector
               for square Matrix A of size 'n' and type real, float.
               This operation is done out-of-place
                A.plu will return (a tuple)
                  an permutation (index) vector of length n (call it p)
                  a lower triangular matrix of size n (call it L)
                  an upper triangular matrix of size n (call it U)
                such that A.permute(p) will be equal to L.prod(U)
            """
            p=Block('block_vi',self.collength).vector.ramp(0,1)
            L=self.empty.identity
            U=self.copy
            supportedViews = ['mview_f','mview_d']
            assert U.type in supportedViews,'Matrix must be of type mview_f or mview_d'
            n=U.rowlength
            m=U.collength
            assert m == n, 'Matrix must be square'
            for k in range(n-1):
                pk=U.colview(k)[k:n].maxmgvalindx
                if pk != 0:
                    U.eros(k,k+pk)
                    t=p[k]
                    p[k]=p[k+pk]
                    p[k+pk]=t
                pvt=U[k,k]
                assert pvt != 0.0, 'Matrix is singular'
                U[k+1:n,k] /= pvt
                uc=U.colview(k)[k+1:n];ur=U.rowview(k)[k+1:n]
                # to do in place use nopu else use product.
                U[k+1:n,k+1:n].nopu(uc,ur)
                # U[k+1:n,k+1:n] -= U[k+1:n,k].prod(U[k,k+1:n])
            for i in range(1,n):
                for j in range(i):
                    L[i,j]=U[i,j]
                    U[i,j]=0
            return (p,L,U)
        def lsolve(self,xy):
            assert 'vview' in xy.type, 'Method lsolve only works with vector argument'
            assert 'mview' in self.type, 'Method lsolve only defined for (upper diagonal) matrices'
            assert self.rowlength == self.collength and self.rowlength == xy.length,\
                          'Calling view must be square with size equal to argument length'
            n=self.rowlength
            xy[0] /= self[0,0]
            for i in range(1,n):
                y0=xy[i]
                xy[i] = (y0 - self.rowview(i)[0:i].dot(xy[0:i]))/self[i,i]
            return xy
        def usolve(self,xy):
            assert 'vview' in xy.type, 'Method usolve only works with vector argument'
            assert 'mview' in self.type, 'Method usolve only defined for (upper diagonal) matrices'
            assert self.rowlength == self.collength and self.rowlength == xy.length,\
                          'Calling view must be square with size equal to argument length'
            n=self.rowlength-1
            xy[n] /= self[n,n]
            for i in range(n-1,-1,-1):
                y0=xy[i]
                xy[i] = (y0 - self.rowview(i)[i+1:n+1].dot(xy[i+1:n+1]))/self[i,i]
            return xy
        ### end plu operations

        @property
        def norm2(self):
            """This method is a property which returns the two norm
            """
            vSup=['vview_f','cvview_f','vview_d','cvview_d']
            mSup=['mview_f','cmview_f','mview_d','cmview_d']
            def eigB(A): #find Biggest eigenvalue
                small=A.normFro/1e16
                vk=0;
                xk=A.colview(0).empty.fill(0.0)
                xk[0]=1
                for i in range(1000):
                    axk=A.prod(xk)
                    n=axk.norm2
                    vkn=xk.jdot(axk).real
                    chk=vkn-vk
                    if chk < 0:
                        chk = -chk
                    if chk < small:
                        return vkn
                    else:
                        vk = vkn
                    xk=axk / n
                return vkn
            assert self.type in vSup or self.type in mSup, 'Type <:'+self.type+':> not supported by norm2'
            if self.type in vSup:
                return vsip_sqrt_d(self.jdot(self).real)
            else:
                if self.collength >= self.rowlength:
                    t=self.transview
                    M=t.prodh(t)
                else:
                    M=self.prodh(self)
                return vsip_sqrt_d(eigB(M))
        @property
        def normFro(self):
            """This method is a property which returns the Frobenius norm
            """
            f={'vview_f': 'vsip_sqrt_d(self.sumsqval)',
               'vview_d': 'vsip_sqrt_d(self.sumsqval)',
               'mview_f': 'vsip_sqrt_d(self.sumsqval)',
               'mview_d': 'vsip_sqrt_d(self.sumsqval)',
               'cvview_f':'vsip_sqrt_d(self.realview.sumsqval + self.imagview.sumsqval)',
               'cvview_d':'vsip_sqrt_d(self.realview.sumsqval + self.imagview.sumsqval)',
               'cmview_f':'vsip_sqrt_d(self.realview.sumsqval + self.imagview.sumsqval)',
               'cmview_d':'vsip_sqrt_d(self.realview.sumsqval + self.imagview.sumsqval)'}
            if f.has_key(self.type):
                return eval(f[self.type])
            else:
                print('Type <:'+self.type+':> not recognized for frobenius')
                return
        @property
        def norm1(self):
            """This method is a property which returns the one norm
            """
            vSup=['vview_f','cvview_f','vview_d','cvview_d']
            mSup=['mview_f','cmview_f','mview_d','cmview_d']
            if self.type in vSup:
                return self.mag.sumval
            elif self.type in mSup:
                mx=0
                for i in range(self.rowlength):
                    t=self.colview(i).norm1
                    if t > mx:
                        mx=t
                return mx
            else:
                print('Type <:'+self.type+':> not supported by norm1')
                return
        @property
        def normInf(self):
            """This method is a property which returns the Infinity norm
            """
            vSup=['vview_f','cvview_f','vview_d','cvview_d']
            mSup=['mview_f','cmview_f','mview_d','cmview_d']
            if self.type in vSup:
                return self.magval
            elif self.type in mSup:
                mx=0
                for j in range(self.collength):
                    t=self.rowview(j).norm1
                    if t > mx:
                        mx=t
                return mx
            else:
                print('Type <:'+self.type+':> not supported by norm1')
                return
        #linear algebra
        def gemp(self,alpha,A,opA,B,opB,beta):
            """
            self=alpha* opA(A)*obB(B) + beta * self
            op is one of 'NTRANS', 'TRANS','HERM','CONJ'
            alpha and beta are scalars
            A and B are float matrices (_d or _f) of type mview or cmview
            """
            op = {'NTRANS':0,'TRANS':1,'HERM':2,'CONJ':3}
            if A.type == B.type and A.type == self.type and 'mview' in self.type:
                chk = vsip.gemp(alpha,op[opA],A.view,op[opB],beta,self.view)
                if chk == False:
                    return chk
                else:
                    return self
            else:
                print('Views must be matrices of the same type')
                return False
        def gems(self,alpha,A,opA,beta):
            """
               self = alpha * op[opA](A) + beta*self
            """
            op = {'NTRANS':0,'TRANS':1,'HERM':2,'CONJ':3}
            if A.type == self.type and 'mview' in self.type:
                vsip.gems(alpha,A.view,op[opA],beta,self.view)
                return self
            else:
                print('Views must ba matrices of the same type')
                return False
        def outer(self,*args):
            f={'cvview_f':'vsip_cvouter_f(vsip_cmplx_f(a.real,a.imag),\
                           self.view,other.view, retval.view)',
               'cvview_d':'vsip_cvouter_d(vsip_cmplx_d(a.real,a.imag),\
                           self.view,other.view, retval.view)',
               'vview_f':'vsip_vouter_f(a,self.view,other.view,retval.view)',
               'vview_d':'vsip_vouter_d(a,self.view,other.view,retval.view)'}
            if len(args) == 1:
                a = 1.0
                other = args[0]
            elif len(args) == 2:
                a = args[0]
                other = args[1]
            else:
                print('To many arguments to outer')
                print('Method for outer takes either a scalar and a vector, or a vector')
                return False
            if (self.type == other.type) and \
                  ('vview' in self.type) and \
                    f.has_key(self.type):
                cl=self.length; rl=other.length
                retval=self.block.otherBlock(self.block.type,rl*cl).bind(0,rl,cl,1,rl)
                eval(f[self.type])
                return retval
            else:
                print('Input views must be vectors')
                return False
        def prod(self,other):
            if 'vview' in self.type and 'mview' in other.type:
                l=other.rowlength
                retval = self.block.otherBlock(self.block.type,l).bind((0,1,l))
                vsip.prod(self.view,other.view,retval.view)
                return retval
            elif 'mview' in self.type and 'mview' in other.type:
                n=other.rowlength
                m=self.collength
                retval = self.block.otherBlock(self.block.type,m*n).bind((0,n,m,1,n))
                if m == 3 and self.rowlength == 3:
                    vsip.prod3(self.view,other.view,retval.view)
                elif m == 4 and self.rowlength == 4:
                    vsip.prod4(self.view,other.view,retval.view)
                else:
                    vsip.prod(self.view,other.view,retval.view)
                return retval
            elif 'mview' in self.type and 'vview' in other.type:
                l=self.collength
                retval = self.block.otherBlock(self.block.type,l).bind((0,1,l))
                if l == 3 and self.rowlength == 3:
                    vsip.prod3(self.view,other.view,retval.view)
                elif l == 4 and self.rowlength == 4:
                    vsip.prod4(self.view,other.view,retval.view)
                else:
                    vsip.prod(self.view,other.view,retval.view)
                return retval
            else:
                print('Input views <:' + self.type + ':> and <:' + other.type +
                      ':> do not appear to be supported by function prod')
                return False
        def prodh(self,other):
            cSup=['cmview_f','cmview_d']
            rSup=['mview_f','mview_d']
            if (self.type in cSup) and (other.type in cSup):
                n=other.collength
                m=self.collength
                retval = self.block.otherBlock(self.block.type,m*n).bind((0,n,m,1,n))
                vsip.prodh(self.view,other.view,retval.view)
                return retval
            elif (self.type in rSup) and (other.type in rSup):
                return self.prodt(other)
            else:
                print('Views must be both complex, or both real matrices')
                return False
        def prodj(self,other):
            if 'cmview' in self.type and 'cmview' in other.type:
                m=self.collength
                n=other.rowlength
                retval = self.block.otherBlock(self.block.type,m*n).bind((0,n,m,1,n))
                vsip.prodj(self.view,other.view,retval.view)
                return retval
            else:
                print('Views must be complex matrices')
                return False
        def prodt(self,other):
            if 'mview' in self.type and 'mview' in other.type:
                n=other.collength
                m=self.collength
                retval = self.block.otherBlock(self.block.type,m*n).bind((0,n,m,1,n))
                vsip.prodt(self.view,other.view,retval.view)
                return retval
            else:
                print('Views must be matrices')
                return False
        @property
        def trans(self):
            """
            Done out of place.
            A new block and view and view are created and the transpose
            of the calling view is copied into it. See transview for a transpose view on
            the same block.
            Usage:
                B=A.trans
            """
            if 'mview' in self.type:
                m=self.rowlength
                n=self.collength
                retval=self.block.otherBlock(self.block.type,m*n).bind((0,n,m,1,n))
                vsip.trans(self.view,retval.view)
                return retval
            else:
                print('View must be a matrix')
                return False
        @property
        def herm(self):
            """
            Done out of place. For square matrices in-place is possible using the herm function.
            Usage: Given matrix view A
                B = A.herm
                returns new matrix B which is hermitian of A.
            For an in place equivalent one can do A.transview.conj.
            """
            if 'cmview' in self.type:
                m=self.rowlength
                n=self.collength
                retval=self.block.otherBlock(self.block.type,m*n).bind((0,n,m,1,n))
                vsip.herm(self.view,retval.view)
                return retval
            elif 'mview' in self.type:
                return self.trans
            else:
                print('View must be a matrix')
                return False
        def dot(self,other):
            if 'vview' in self.type and 'vview' in other.type:
                retval=vsip.dot(self.view,other.view)
                if 'cscalar' in repr(retval):
                    return complex(retval.r,retval.i)
                else:
                    return retval
            else:
                print('Input views must be vectors')
                return False
        def jdot(self,other):
            reTypes=['vview_f','vview_d']
            imTypes=['cvview_f','cvview_d']
            if ('vview_d' in other.type) and ('vview_f' in self.type) or \
               ('vview_f' in other.type) and ('vview_d' in self.type):
                print('Precision of views must agree')
                return
            if 'cvview' in self.type and 'cvview' in other.type:
                retval = vsip.jdot(self.view,other.view)
                if 'cscalar' in repr(retval):
                    return complex(retval.r,retval.i)
                else:
                    return retval
            elif (self.type in reTypes) and (other.type in reTypes):
                return self.dot(other)
            elif (self.type in imTypes) and (other.type in reTypes):
                return complex(self.realview.dot(other),self.imagview.dot(other))
            elif (self.type in reTypes) and (other.type in imTypes):
                return complex(self.dot(other.realview),-self.dot(other.imagview))
            else:
                print('Input views must be float vectors of the same precision')
                return False
        def permute(self,p,*major):
            """
            The permute method will permute a matrix by row or by column given an index vector.
            """
            f={'cmview_f':vsip_cmpermute_once_f,'cmview_d':vsip_cmpermute_once_d,'mview_f':vsip_mpermute_once_f,'mview_d':vsip_mpermute_once_d}
            assert p.type in 'vview_vi','The index vector for method permute must be of type "vview_vi".'
            pc=p.copy
            assert self.type in ['cmview_f','cmview_d','mview_f','mview_d','vview_f','vview_d'],\
                              'For method permute type <:%s:> not supported'%self.type
            if 'vview' in self.type:
                self.mcolview.permute(p,'ROW')
            elif len(major) == 1 and major[0] == 'COL':
                assert p.length == self.rowlength,'In permute method index vector is not sized properly'
                f[self.type](self.view,VSIP_COL,pc.view,self.view)
            else: #do by ROW
                assert p.length == self.collength,'In permute method index vector is not sized properly'
                f[self.type](self.view,VSIP_ROW,pc.view,self.view)
            return self
        @property
        def permuteTranspose(self):
            """Return a permutation vector which is the equivalent of a transpose
               of the permutation matrix represented by the calling view.
               Done out-of-place. Input vector not modified.
               Input and output vectors both of type vview_vi
            """
            if self.type != 'vview_vi':
                print('permuteTranspose method only works for vectors of type vview_vi')
                return
            p=self.empty
            for i in range(p.length):
                p[self[i]]=i
            return p
        def sort(self,*vals):
            """
              Usage:
                indx=self.sort(mode,dir,fill,indx)
              Default:
                indx=self.sort() -is the same as-  indx = self.sort('BYVALUE','ASCENDING')
                indx=self.sort(mode) -is the same as- index = self.sort(mode,'ASCENDING')
              Where:
                self is a vector
                mode is a string 'BYVALUE' or 'BYMAGNITUDE'
                dir is a string 'ASCENDING' or 'DESCENDING'
                fill is a bool True or False
                indx is an index vector the same length as self
              All arguments are optional but must be entered in order; for instance if
              dir is included then mode must be included.
              The bool fill indicates whether the indx vector is initialized or not.
              If no indx vector is included and fill is False then no indx vector is returned.
              If no indx vector is included and fill is True (or not included) then an indx vector
              is created and initialized and returned (with the sorted indices).
              If an indx vector is included then it is initialized (or not depending on fill), and the
              indices are sorted. If an index is included, indx is returned as a convenience.
            """
            sptd=['vview_f','vview_d','vview_i','vview_vi']
            t=self.type
            assert t in sptd,'Type <:' + t + ':> not supported by sort'
            f={'vview_f':vsip_vsortip_f,'vview_d':vsip_vsortip_d,
               'vview_i':vsip_vsortip_i,'vview_vi':vsip_vsortip_vi}
            m={'BYVALUE':0,'BYMAGNITUDE':1}
            d={'DESCENDING':1,'ASCENDING':0}
            nvals=len(vals)
            if nvals > 4:
                print('Maximum number of arguments for sort is 4');
                return
            if nvals > 0:
                mode=m[vals[0]]
            else:
                mode=m['BYVALUE']
            if nvals > 1:
                dir=d[vals[1]]
            else:
                dir=d['ASCENDING']
            if nvals > 2:
                if vals[2]:
                    fill=1
                else:
                    fill=0
            else:
                fill = 1
            if nvals == 4:
                if vals[3].type == 'vview_vi':
                    idx = vals[3]
                    if fill:
                        idx.ramp(0,1)
                else:
                    print('index vector for sort must be of type vview_vi')
                    return
            elif fill:
                idx = create('vview_vi',self.length)
            else:
                idx = None
            if f.has_key(t):
                f[t](self.view,mode,dir,fill,idx.view)
                return idx
            else:
                print('Type <:' + t + ':> not supported by sort')
                return
        # Signal Processing
        @property
        def fftip(self):
            fCreate = {'cvview_d':'ccfftip_d',
                       'cvview_f':'ccfftip_f',
                       'cmview_d':'ccfftmip_d',
                       'cmview_f':'ccfftmip_f'}
            if self.type in ['cvview_d','cvview_f']:
                arg = (self.length,1.0,-1,0,0)
            elif self.type in ['cmview_d','cmview_f']:
                if 'COL' in self.major:
                    major = 1
                else:
                    major = 0
                arg = (self.collength,self.rowlength,1.0,-1,major,0,0)
            else:
                print('Type <:' +self.type+':> not supported for method fftip')
                return
            obj=FFT(fCreate[self.type],arg)
            obj.dft(self)
            return self
        @property
        def ifftip(self):
            fCreate = {'cvview_d':'ccfftip_d',
                       'cvview_f':'ccfftip_f',
                       'cmview_d':'ccfftmip_d',
                       'cmview_f':'ccfftmip_f'}
            if self.type in ['cvview_d','cvview_f']:
                arg = (self.length,1.0,1,0,0)
            elif self.type in ['cmview_d','cmview_f']:
                if 'COL' in self.major:
                    major = 1
                else:
                    major = 0
                arg = (self.collength,self.rowlength,1.0,-1,major,0,0)
            else:
                print('Type <:' +self.type+':> not supported for method fftip')
                return
            obj=FFT(fCreate[self.type],arg)
            obj.dft(self)
            return self
        @property
        def fftop(self):
            """
            The method fftop (FFT Out Of Place) is a property on real and float vectors and matrices.
            For matrices use the major attribute of the view to set the direction of the FFT.
            fftop will create and return view of the proper type for the output.
            If the input is real then fftop assumes the complex portion is zero.
            """
            selV={'vview_f':'cvview_f','vview_d':'cvview_d'}
            selM={'mview_f':'cmview_f','mview_d':'cmview_d'}
            if selV.has_key(self.type):
                y=create(selV[self.type],self.length).fill(0.0)
                copy(self,y.realview)
                return y.fftip
            elif selM.has_key(self.type):
                y=create(selM[self.type],self.collength,self.rowlength).fill(0.0)
                copy(self,y.realview)
                if 'COL' in self.major:
                    return y.COL.fftip
                else:
                    return y.ROW.fftip
            else:
                f = {'cvview_d':'ccfftop_d',
                     'cvview_f':'ccfftop_f',
                     'cmview_d':'ccfftmop_d',
                     'cmview_f':'ccfftmop_f'}
                assert f.has_key(self.type), 'Type <:'+self.type+':> not supported by method fftop'
                retval = self.empty
                if self.type in ['cvview_d','cvview_f']:
                    arg = (self.length,1.0,-1,0,0)
                else:
                    if 'COL' in self.major:
                        major = 1
                    else:
                        major = 0
                    arg = (self.collength,self.rowlength,1.0,-1,major,0,0)
                obj=FFT(f[self.type],arg)
                obj.dft(self,retval)
                return retval
        @property
        def ifftop(self):
            """
            The method ifftop (Inverse FFT Out Of Place) is a property on real and float vectors and matrices.
            For matrices use the major attribute of the view to set the direction of the FFT.
            fftop will create and return view of the proper type for the output.
            If the input is real then ifftop assumes the complex portion is zero.
            """
            selV={'vview_f':'cvview_f','vview_d':'cvview_d'}
            selM={'mview_f':'cmview_f','mview_d':'cmview_d'}
            if selV.has_key(self.type):
                y=create(selV[self.type],self.length).fill(0.0)
                copy(self,y.realview)
                return y.ifftip
            elif selM.has_key(self.type):
                y=create(selM[self.type],self.collength,self.rowlength).fill(0.0)
                copy(self,y.realview)
                if 'COL' in self.major:
                    return y.COL.ifftip
                else:
                    return y.ROW.ifftip
            else:
                f = {'cvview_d':'ccfftop_d',
                     'cvview_f':'ccfftop_f',
                     'cmview_d':'ccfftmop_d',
                     'cmview_f':'ccfftmop_f'}
                assert f.has_key(self.type), 'Type <:'+self.type+':> not supported by method ifftop'
                retval = self.empty
                if self.type in ['cvview_d','cvview_f']:
                    arg = (self.length,1.0,1,0,0)
                else:
                    if 'COL' in self.major:
                        major = 1
                    else:
                        major = 0
                    arg = (self.collength,self.rowlength,1.0,-1,major,0,0)
                obj=FFT(f[self.type],arg)
                obj.dft(self,retval)
                return retval
        @property
        def rcfft(self):
            fCreate = {'vview_d':'rcfftop_d', 'vview_f':'rcfftop_f',
                       'mview_d':'rcfftmop_d', 'mview_f':'rcfftmop_f'}
            t={'vview_f':'cblock_f','vview_d':'cblock_d',
                   'mview_f':'cblock_f','mview_d':'cblock_d'}
            if self.type in ['vview_d','vview_f']:
                length = self.length
            elif self.type in ['mview_d','mview_f']:
                if 'COL' in self.major:
                    length = self.collength
                else:
                    length = self.rowlength
            else:
                print('Type <:' + self.type + ':> is not supported for rcfft')
                return
            if (length % 2):
                print('rcfft only supported for even length along fft direction ')
                return
            if t.has_key(self.type):
                if self.type in ['vview_f','vview_d']:
                    n=int(length/2)+1
                    retval=Block(t[self.type],n).bind(0,1,n)
                    arg = (length,1.0,1,0)
                else:
                    if 'COL' in self.major:
                        m = int(length/2) + 1
                        n = self.rowlength
                        retval = Block(t[self.type],n * m).bind(0,1,m,m,n)
                        arg=(length,n,1.0,1,1,0)
                    else:
                        m=self.collength
                        n=int(length/2) + 1
                        retval = Block(t[self.type],m*n).bind(0,n,m,1,n)
                        arg=(m,length,1.0,0,1,0)
                FFT(fCreate[self.type],arg).dft(self,retval)
                return retval
            else:
                print('Type <:'+self.type+':> not supported for rcfft')
                return
        @property
        def crfft(self):
            fCreate = {'cvview_d':'crfftop_d', 'cvview_f':'crfftop_f',
                       'cmview_d':'crfftmop_d', 'cmview_f':'crfftmop_f'}
            t={'cvview_f':'block_f','cvview_d':'block_d',
               'cmview_f':'block_f','cmview_d':'block_d'}
            if self.type in ['cvview_d','cvview_f']:
                length = self.length
            elif self.type in ['cmview_d','cmview_f']:
                if 'COL' in self.major:
                    length = self.collength
                else:
                    length = self.rowlength
            else:
                print('Type <:' + self.type + ':> is not supported for rcfft')
                return
            if t.has_key(self.type):
                if self.type in ['cvview_f','cvview_d']:
                    n=2 * (length -1)
                    retval=Block(t[self.type],n).bind(0,1,n)
                    arg = (n,1.0,1,0)
                else:
                    if 'COL' in self.major:
                        m = 2 * (length -1)
                        n = self.rowlength
                        retval = Block(t[self.type],n * m).bind(0,1,m,m,n)
                        arg=(m,n,1.0,1,1,0)
                    else:
                        m=self.collength
                        n==2 * (length -1)
                        retval = Block(t[self.type],m*n).bind(0,n,m,1,n)
                        arg=(m,n,1.0,0,1,0)
                FFT(fCreate[self.type],arg).dft(self,retval)
                return retval
            else:
                print('Type <:'+self.type+':> not supported for crfft')
                return
        #
        # General Square Solver
        @property
        def lu(self):
            """
               Create LU Object and Decomposition of calling view.
               Calling view must be square and float
               return lu object
            """
            assert LU.luSel.has_key(self.type), "LU for %s not supported"%self.type
            assert self.rowlength == self.collength,"LU only supports square matrices"
            return LU(LU.luSel[self.type],self.rowlength).decompose(self)
        @property
        def luInv(self):
            """
            The method luInv creates a new matrix and uses the LU decomposition place the inverse of the
            calling matrix into it. Note that LU decomposition overwrites the input matrix so if "A" is the input matrix
            then
            Y=A.luInv
            will overwrite A. To keep A use copy as in
            Y=A.copy.luInv.
            """
            assert LU.luSel.has_key(self.type), 'Type <:'+ self.type + ':> not supported for luInv'
            assert self.rowlength == self.collength, 'Method luInv only works for square matrices'
            retval=self.empty.identity
            LU(LU.luSel[self.type],self.rowlength).decompose(self).solve(0,retval)
            return retval
        def luSolve(self,XB):
            """
            Usage:
                X = A.luSolve(X)
                A is a matrix of type float or double; real or complex.
                On input X is a vector or matrix of the same precision as A
            luSolve solve overwrites input data with output data.
            To keep the input use
                Y = A.luSolve(X.copy)
            LU will overwrite the Calling matrix. To keep everything use
                Y = A.copy.luSolve(X.copy)
            """
            assert LU.luSel.has_key(self.type), 'Type <:'+ self.type + ':> not supported for luSolve'
            assert self.rowlength == self.collength, 'Method luSolve only works for square matrices'
            if 'vview' in XB.type:
                X=XB.block.bind(XB.offset,XB.stride,XB.length,1,1)
            else:
                X = XB
            assert X.type == self.type, 'Calling view and input/output view must be the same type and precision'
            assert self.collength == X.collength, 'Input/Output view not sized properly for calling view'
            obj=LU(LU.luSel[self.type],self.rowlength).decompose(self)
            assert obj.singular,'The calling matrix is singular'
            obj.solve('NTRANS',X)
            return XB
        #
        #QR Decomposition; Over-Determined Linear System Solver
        @property
        def qr(self):
            """
               Usage:
                  qr = view.qr
               where view is of type float; real or complex
               Return QR object and decomposition for calling view.
               Input view is used by QR object is so use a copy if original is needed.
               This returns a QR object for a Full Q. (qSave => VSIP_QRD_SAVEQ)
               NOTE for vector views:
               If the input view is a vector then the vector is converted to a matrix matrix.
               Vectors are treated as a column here.
            """
            if self.type in ['vview_f','vview_d','cvview_f','cvview_d']:
                A=self.block.bind(self.offset,self.stride,self.length,1,1)
            elif self.type in ['mview_f','mview_d','cmview_f','cmview_d']:
                A = self
            else:
                print('Type <:' +self.type+ '<: not supported for QR')
                return
            assert A.collength >= A.rowlength,"QR requires column length less than row length"
            retval=QR(QR.qrSel[self.type],A.collength,A.rowlength,VSIP_QRD_SAVEQ)
            retval.decompose(A)
            return retval
        @property
        def qrd(self):
            """
               Usage:
                  Q,R=view.qrd
               where view is of type float; real or complex
               For this function self is not overwritten
               Q.prod(R) should return (a matrix) equivalent to the input
            """
            assert self.type in ['vview_d','vview_f','mview_d','mview_f', \
                                 'cvview_d','cvview_f','cmview_d','cmview_f'],\
                   'Type <:'+self.type+':> not supported by view qrd method'
            if self.type in ['vview_f','vview_d','cvview_f','cvview_d']:
                A=self.block.bind(self.offset,self.stride,self.length,0,1).copy
            else:
                A = self.copy
            m = A.collength;n=A.rowlength;
            Q = Block(Block.blkSel[self.type],m*m).bind(0,1,m,m,m).identity
            qr = A.copy.qr
            qr.prodQ('NTRANS','RSIDE',Q)
            if 'cmview' in A.type:
                qr.prodQ('HERM','LSIDE',A)
            else:
                qr.prodQ('TRANS','LSIDE',A)
            return(Q,A)
        #SVD Decomposition
        @property
        def sv(self):
            """
            For a matrix view 'A' of type float or double, real or complex,
            s = A.sv will return a vector of singular values for matrix A
            Note Matrix A is overwritten by the decomposition. To retain A use
            s = A.copy.sv
            """
            svtSel={'mview_d':'sv_d','mview_f':'sv_f','cmview_d':'csv_d','cmview_f':'csv_f'}
            vtSel={'mview_d':'vview_d','mview_f':'vview_f','cmview_d':'vview_d','cmview_f':'vview_f'}
            n=self.rowlength
            m=self.collength
            svObj=SV(svtSel[self.type],m,n,'NOS','NOS')
            if n < m:
                s=create(vtSel[self.type],n)
            else:
                s=create(vtSel[self.type],m)
            return svObj.svd(self,s)
        @property
        def svd(self):
            """
            This method is a full svd decompostion.
            For SVD decomposition where
                A = U s V^H
            For matrix A:
                D=A.svd
            Matrix A is overwritten by the SVD. To retain A use
                D = A.copy.svd
            returns a tuple into D.
            D[0] will be matrix U, D[1] will be (real) vector s of singular values, and
            D[2] will be matrix V
            Note that this method returns the full U and V matrix including any NULL space.
            """
            svtSel={'mview_d':'sv_d','mview_f':'sv_f','cmview_d':'csv_d','cmview_f':'csv_f'}
            vtSel={'mview_d':'vview_d','mview_f':'vview_f','cmview_d':'vview_d','cmview_f':'vview_f'}
            n=self.rowlength
            m=self.collength
            svObj=SV(svtSel[self.type],m,n,'FULL','FULL')
            if n < m:
                s=create(vtSel[self.type],n)
            else:
                s=create(vtSel[self.type],m)
            svObj.svd(self,s)
            U=create(self.type,m,m)
            V=create(self.type,n,n)
            svObj.matv(0,n,V)
            svObj.matu(0,m,U)
            return (U,s,V)
        @property
        def svdP(self):
            """
            This method returns the partial svd decomposition.
            For SVD decomposition where
                A = U s V^H
            For matrix A:
                D=A.svd
            Matrix A is overwritten by the SVD. To retain A use
                D = A.copy.svd
            returns a tuple into D.
            D[0] will be matrix U, D[1] will be (real) vector s of singular values, and
            D[2] will be matrix V
            Note that this method returns the partial U and V matrix without the NULL space.
            """
            svtSel={'mview_d':'sv_d','mview_f':'sv_f','cmview_d':'csv_d','cmview_f':'csv_f'}
            vtSel={'mview_d':'vview_d','mview_f':'vview_f','cmview_d':'vview_d','cmview_f':'vview_f'}
            n=self.rowlength
            m=self.collength
            svObj=SV(svtSel[self.type],m,n,'PART','PART')
            if n < m:
                s=create(vtSel[self.type],n)
                rl=n
            else:
                s=create(vtSel[self.type],m)
                rl=m
            svObj.svd(self,s)
            U=create(self.type,m,rl)
            V=create(self.type,n,rl)
            svObj.matv(0,rl,V)
            svObj.matu(0,rl,U)
            return (U,s,V)
        @property
        def svdU(self):
            """
            For SVD decomposition where
                A = U s V^H
            For matrix A:
                D=A.svd
            Matrix A is overwritten by the SVD. To retain A use
                D = A.copy.svd
            returns a tuple into D.
            D[0] will be matrix U, D[1] will be (real) vector s of singular values
            This method returns the Full matrix U.
            """
            svtSel={'mview_d':'sv_d','mview_f':'sv_f','cmview_d':'csv_d','cmview_f':'csv_f'}
            vtSel={'mview_d':'vview_d','mview_f':'vview_f','cmview_d':'vview_d','cmview_f':'vview_f'}
            n=self.rowlength
            m=self.collength
            svObj=SV(svtSel[self.type],m,n,'FULL','NOS')
            if n < m:
                s=create(vtSel[self.type],n)
            else:
                s=create(vtSel[self.type],m)
            svObj.svd(self,s)
            U=create(self.type,m,m)
            svObj.matu(0,m,U)
            return (U,s)
        @property
        def svdV(self):
            """
            For SVD decomposition where
                A = U s V^H
            For matrix A:
                D=A.svd
            Matrix A is overwritten by the SVD. To retain A use
                D = A.copy.svd
            returns a tuple into D.
            D[0] will be (real) vector s of singular values, and D[1] will be matrix V
            Matrix V is the Full V matrix.
            """
            svtSel={'mview_d':'sv_d','mview_f':'sv_f','cmview_d':'csv_d','cmview_f':'csv_f'}
            vtSel={'mview_d':'vview_d','mview_f':'vview_f','cmview_d':'vview_d','cmview_f':'vview_f'}
            n=self.rowlength
            m=self.collength
            svObj=SV(svtSel[self.type],m,n,'NOS','FULL')
            if n < m:
                s=create(vtSel[self.type],n)
            else:
                s=create(vtSel[self.type],m)
            svObj.svd(self,s)
            V=create(self.type,n,n)
            svObj.matv(0,n,V)
            return (s,V)
        #utility functions
        def mstring(self,fmt):
            """
            This method returns a string suitable for printing the values as a vector or matrix.
            usage:
              mstring(<vsip matrix/vector>, fmt)
            fmt is a string corresponding to a simple fmt statement.
            For instance '%6.5f' prints as 6 characters wide with 5 decimal digits.
            Note format converts this statement to '% 6.5f' or '%+6.5f' so keep
            the input simple.
            """
            assert isinstance(fmt,str), 'Format must be a string'
            def _fmt1(c):
                if c != '%':
                    return c
                else:
                    return '% '
            def _fmt2(c):
                if c != '%':
                    return c
                else:
                    return '%+'
            def _fmtfunc(fmt1,fmt2,y):
                if type(y) is complex:
                    s = fmt1 % y.real
                    s += fmt2 % y.imag
                    s += "i"
                    return s
                else:
                    return fmt1 % y
            tm=['mview_d','mview_f','cmview_d','cmview_f','mview_i','mview_uc',
                 'mview_si','mview_bl']
            tv=['vview_d','vview_f','cvview_d','cvview_f','vview_i','vview_uc',
                 'vview_si','vview_bl','vview_vi','vview_mi']
            t=self.type
            tfmt=[_fmt1(c) for c in fmt]
            fmt1 = "".join(tfmt)
            tfmt=[_fmt2(c) for c in fmt]
            fmt2 = "".join(tfmt)
            if t in tm:
                cl=self.collength
                rl=self.rowlength
                s=str()
                for i in range(cl):
                    M=[]
                    for j in range(rl):
                        M.append(_fmtfunc(fmt1,fmt2,self[i,j]))
                    if i == 0 and cl==1:
                        s += "["+" ".join(M) + "]\n"
                    elif i== 0:
                        s += "["+" ".join(M) + ";\n"
                    elif i < cl-1:
                        s += " "+" ".join(M) + ";\n"
                    else:
                        s += " "+" ".join(M) + "]\n"
                return s
            elif t in tv:
                l=self.length
                V=[_fmtfunc(fmt1,fmt2,self[i]) for i in range(l)]
                return "[" + " ".join(V) + "]\n"
            else:
                print('Object not VSIP vector or matrix')
        def mprint(self,fmt):
            assert isinstance(fmt,str), 'Format for mprint is a string'
            print(self.mstring(fmt))

class Rand(object):
    """
       Usage
            randObj=Rand(aType,aSeed)
            where aType is one of 'PRNG' or 'NPRNG'
            and aSeed is an integer number
      'PRNG' signifies the portable VSIP version and 'NPRNG' signifies the non-portable
       version.
            randObj.randn(a)
            randObj.randu(a)
       fills view object a with the VSIPL normal or uniform (respectivly) random data.
    """
    tRand = ['PRNG','NPRNG']
    supported = ['vview_f','vview_d','cvview_f','cvview_d','mview_f','mview_d','cmview_f','cmview_d']
    def __init__(self,t,seed):
        self.__jvsip = JVSIP()
        self.__type = t
        self.__seed = seed
        f={'PRNG':'vsip_randcreate(seed,1,1,0)',
           'NPRNG':'vsip_randcreate(seed,1,1,1)'}
        if f.has_key(t):
            self.__rng=eval(f[t])
        else:
            print("type must be either 'PRNG' or 'NPRNG'")

    def __del__(self):
        vsip.destroy(self.__rng)
        del(self.__jvsip)
    @property
    def type(self):
        return self.__type;
    @property
    def seed(self):
        return(self.__seed)
    @property
    def nextu(self):
        return vsip_randu_d(self.__rng)
    @property
    def nextn(self):
        return vsip_randn_d(self.__rng)
    @property
    def rng(self):
        return self.__rng
    def randn(self,a):
        t=vsip.getType(a.view)[1]
        f = {'cvview_d':vsip_cvrandn_d,
             'cvview_f':vsip_cvrandn_f,
             'vview_d':vsip_vrandn_d,
             'vview_f':vsip_vrandn_f,
             'cmview_d':vsip_cmrandn_d,
             'cmview_f':vsip_cmrandn_f,
             'mview_d':vsip_mrandn_d,
             'mview_f':vsip_mrandn_f}
        if f.has_key(t):
            f[t](self.rng,a.view)
            return a
        else:
            print('Not a supported type for rand')
    def randu(self,a):
        t=vsip.getType(a.view)[1]
        f = {'cvview_d':vsip_cvrandu_d,
             'cvview_f':vsip_cvrandu_f,
             'vview_d':vsip_vrandu_d,
             'vview_f':vsip_vrandu_f,
             'cmview_d':vsip_cmrandu_d,
             'cmview_f':vsip_cmrandu_f,
             'mview_d':vsip_mrandu_d,
             'mview_f':vsip_mrandu_f}
        if f.has_key(t):
            f[t](self.rng,a.view)
            return a
        else:
            print('Not a supported type for rand')

# Signal Processing Classes
# Not Implemented
# vsip_fft_setwindow_f
# vsip_dfft2dx_create_f
# vsip_ccfft2dx_f
# vsip_crfft2dop_f
# vsip_rcfft2dop_f
# vsip_conv2d_create_f
# vsip_conv2d_destroy_f
# vsip_conv2d_getattr_f
# vsip_convolve2d_f
# vsip_dcorr2d_create_f
# vsip_dcorr2d_destroy_f
# vsip_dcorr2d_getattr_f
# vsip_dcorrelate2d_f

# FFT Class for 1 d and FFTM
# vsip_ccfftx_f
# vsip_crfftop_f
# vsip_rcfftop_f
# vsip_dfftx_create_f
# vsip_ccfftmx_f
# vsip_crfftmop_f
# vsip_rcfftmop_f
# vsip_dfftmx_create_f
# vsip_fftm_setwindow_f
# vsip_fftn_destroy_f
# vsip_fftn_getattr_f
class FFT (object):
    """
       Usage:
            fftObj=FFT(t,arg) where
            t is one of
                ['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', 'ccfftip_d',
                'ccfftop_d', 'rcfftop_d', 'crfftop_d', 'ccfftmip_f', 'ccfftmop_f',
                'rcfftmop_f', 'crfftmop_f', 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d',
                 'crfftmop_d']
            arg is a tuple corresponding to one of the VSIPL arguments list for the associated t value.
       If VSIPL enumerated types are available as part of the pyJvsip import.
    """
    tFft = ['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', 'ccfftip_d', \
            'ccfftop_d', 'rcfftop_d', 'crfftop_d', 'ccfftmip_f', 'ccfftmop_f', \
            'rcfftmop_f', 'crfftmop_f', 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', 'crfftmop_d']
    fftViewDict = {'ccfftip_d':'cvview_d',
                   'ccfftip_f':'cvview_f',
                   'ccfftop_d':'cvview_dcvview_d',
                   'ccfftop_f':'cvview_fcvview_f',
                   'rcfftop_d':'vview_dcvview_d',
                   'rcfftop_f':'vview_fcvview_f',
                   'crfftop_d':'cvview_dvview_d',
                   'crfftop_f':'cvview_dvview_f',
                   'ccfftmip_d':'cmview_d',
                   'ccfftmip_f':'cmview_f',
                   'ccfftmop_d':'cmview_dcmview_d',
                   'ccfftmop_f':'cmview_fcmview_f',
                   'crfftmop_d':'cmview_dmview_d',
                   'crfftmop_f':'cmview_fmview_f',
                   'rcfftmop_d':'mview_dcmview_d',
                   'rcfftmop_f':'mview_fcmview_f'} #given fft type what type of views works
    fftCreateDict={'ccfftip_f':'vsip_ccfftip_create_f(l[0],l[1],l[2],l[3],l[4])',
                     'ccfftop_f':'vsip_ccfftop_create_f(l[0],l[1],l[2],l[3],l[4])',
                     'rcfftop_f':'vsip_rcfftop_create_f(l[0],l[1],l[2],l[3])',
                     'crfftop_f':'vsip_crfftop_create_f(l[0],l[1],l[2],l[3])',
                     'ccfftip_d':'vsip_ccfftip_create_d(l[0],l[1],l[2],l[3],l[4])',
                     'ccfftop_d':'vsip_ccfftop_create_d(l[0],l[1],l[2],l[3],l[4])',
                     'rcfftop_d':'vsip_rcfftop_create_d(l[0],l[1],l[2],l[3])',
                     'crfftop_d':'vsip_crfftop_create_d(l[0],l[1],l[2],l[3])',
                     'ccfftmip_f':'vsip_ccfftmip_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'ccfftmop_f':'vsip_ccfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'rcfftmop_f':'vsip_rcfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5])',
                     'crfftmop_f':'vsip_crfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5])',
                     'ccfftmip_d':'vsip_ccfftmip_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'ccfftmop_d':'vsip_ccfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
                     'rcfftmop_d':'vsip_rcfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5])',
                     'crfftmop_d':'vsip_crfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5])'}
    fftFuncDict={'cvview_d':'vsip_ccfftip_d(self.vsip,l[0].view)',
                 'cvview_f':'vsip_ccfftip_f(self.vsip,l[0].view)',
                 'cvview_dcvview_d':'vsip_ccfftop_d(self.vsip,l[0].view,l[1].view)',
                 'cvview_fcvview_f':'vsip_ccfftop_f(self.vsip,l[0].view,l[1].view)',
                 'vview_dcvview_d':'vsip_rcfftop_d(self.vsip,l[0].view,l[1].view)',
                 'vview_fcvview_f':'vsip_rcfftop_f(self.vsip,l[0].view,l[1].view)',
                 'cvview_dvview_d':'vsip_crfftop_d(self.vsip,l[0].view,l[1].view)',
                 'cvview_fvview_f':'vsip_crfftop_f(self.vsip,l[0].view,l[1].view)',
                 'cmview_d':'vsip_ccfftmip_d(self.vsip,l[0].view)',
                 'cmview_f':'vsip_ccfftmip_f(self.vsip,l[0].view)',
                 'cmview_dcmview_d':'vsip_ccfftmop_d(self.vsip,l[0].view,l[1].view)',
                 'cmview_fcmview_f':'vsip_ccfftmop_f(self.vsip,l[0].view,l[1].view)',
                 'mview_dcmview_d':'vsip_rcfftmop_d(self.vsip,l[0].view,l[1].view)',
                 'mview_fcmview_f':'vsip_rcfftmop_f(self.vsip,l[0].view,l[1].view)',
                 'cmview_dmview_d':'vsip_crfftmop_d(self.vsip,l[0].view,l[1].view)',
                 'cmview_fmview_f':'vsip_crfftmop_f(self.vsip,l[0].view,l[1].view)'}
    def __init__(self,t,arg):
        if FFT.fftCreateDict.has_key(t):
            self.__jvsip = JVSIP()
            self.__arg = arg
            self.__type = t
            l = arg
            self.__fft = eval(FFT.fftCreateDict[t])
        else:
            print("Type <:" + t + ":> not a recognized type for FFT")
    def __del__(self):
        del (self.__jvsip)
        vsip.destroy(self.__fft)

    def dft(self,*vars):
        """This method requires one view for in-place dft calculation or two views for out-of-place.
           The dft type may be retrieved using the type property of the FFT object.
           See the VSIPL specification for various view requirements which depend on the FFT method being used.
           Some error checking is done but it is not all inclusive.
        """
        if isinstance(vars[0],tuple):
            l = vars[0]
        elif len(vars) == 1:
            l=(vars[0],)
        elif len(vars) == 2:
            l=(vars[0],vars[1])
        else:
            print('To many arguments to dft method')
            return
        chk = '__View' in repr(l[0])
        if chk:
            t = l[0].type
        if len(l) == 2:
            chk = chk and '__View' in repr(l[1])
            if chk:
                t = t + l[1].type
        if not chk:
            print('Argument must one or two views or a tuple of one or two views.')
            return False
        if FFT.fftFuncDict.has_key(t):
            eval(FFT.fftFuncDict[t])
            if len(l) == 2:
                return l[1]
            else:
                return l[0]
        else:
            print('Type <:' + t + ':> not a supported type for FFT')
            return False
    @property
    def vsip(self):
        return self.__fft
    @property
    def type(self):
        return self.__type
    @property
    def arg(self):
        return self.__arg

# Convolution/Correlation Classes
# vsip_dconv1d_create_f
# vsip_dconv1d_destroy_f
# vsip_dconv1d_getattr_f
# vsip_dconvolve1d_f
#VSIP_NONSYM = 0, VSIP_SYM_EVEN_LEN_ODD = 1, VSIP_SYM_EVEN_LEN_EVEN = 2
class CONV(object):
    """
    See VSIPL specification for more information on convolution.
    """
    tConv=['conv1d_f','conv1d_d']
    convSel={'vview_f':'conv1d_f','vview_d':'conv1d_d'}
    supported=['vview_f','vview_d']
    supportRegion = {0:VSIP_SUPPORT_FULL,1:VSIP_SUPPORT_SAME,2:VSIP_SUPPORT_MIN,
              'FULL':VSIP_SUPPORT_FULL,'SAME':VSIP_SUPPORT_SAME,'MIN':VSIP_SUPPORT_MIN}
    symmetry = {0:VSIP_NONSYM,1:VSIP_SYM_EVEN_LEN_ODD, 2:VSIP_SYM_EVEN_LEN_EVEN,
        'NON':VSIP_NONSYM,'ODD':VSIP_SYM_EVEN_LEN_ODD,'EVEN':VSIP_SYM_EVEN_LEN_EVEN}
    algHint={0:VSIP_ALG_TIME, 1:VSIP_ALG_SPACE, 2:VSIP_ALG_NOISE,
             'TIME':VSIP_ALG_TIME,'SPACE':VSIP_ALG_SPACE,'NOISE':VSIP_ALG_NOISE}
    supportStrings={0:'FULL',1:'SAME',2:'MIN'}
    symmStrings={0:'NON',1:'ODD',2:'EVEN'}
    algStrings={0:'TIME',1:'SPACE',2:'NOISE'}
    def __init__(self,t,h,symm,dtaLength,dec,sup,ntimes,hint):
        f={'conv1d_d':vsip_conv1d_create_d,'conv1d_f':vsip_conv1d_create_f}
        assert isinstance(t,str),'Type argument must be a string for function conv'
        assert f.has_key(t), 'Type <:'+t+':> not recognized by function conv'
        assert CONV.algHint.has_key(hint), 'Argument hint not recognized by function conv'
        assert CONV.supportRegion.has_key(sup), 'Argument for support region not recognized by function conv'
        assert isinstance(dec,int) and isinstance(dtaLength,int) and isinstance(ntimes,int),\
               'Arguments decimation and data size must be integers, and ntimes is an integer'
        assert dec > 0, 'Decimation must be an integer greater than zero '
        assert 'pyJvsip.__View' in repr(h), 'The kernel must be a pyJvsip view'
        assert CONV.convSel.has_key(h.type) and t == CONV.convSel[h.type],\
              'Kernel type <:' + h.type + ':> not recognized for convolution.'
        assert CONV.symmetry.has_key(symm), 'Symmetry flag not recognized'
        mySym=CONV.symmStrings[CONV.symmetry[symm]]
        # calculate kernel length
        if mySym == 'NON':
            M=h.length
        elif mySym == 'EVEN':
            M=h.length * 2
        else:
            M=h.length * 2 - 1
        assert M <= dtaLength, 'The kernel length is to long for the data length'
        self.__jvsip = JVSIP()
        self.__type = t
        self.__conv = f[t](h.view,CONV.symmetry[symm],dtaLength,dec,CONV.supportRegion[sup],ntimes,CONV.algHint[hint])
        self.__kernel_len = int(M)
        self.__dtaLength = int(dtaLength)
        self.__decimation = int(dec)
        if CONV.supportRegion[sup]==VSIP_SUPPORT_FULL:
            self.__outLen = (self.__dtaLength + self.__kernel_len - 2) // self.__decimation + 1
        elif CONV.supportRegion[sup]==VSIP_SUPPORT_SAME:
            self.__outLen = (self.__dtaLength -1 ) // self.__decimation + 1
        else: # must be MIN
            self.__outLen = (self.__dtaLength - 1) // self.__decimation - (self.__kernel_len - 1) // self.__decimation + 1
        self.__symm = CONV.symmetry[symm]
        self.__support = CONV.supportStrings[CONV.supportRegion[sup]]
    def __del__(self):
        f={'conv1d_d':vsip_conv1d_destroy_d,'conv1d_f':vsip_conv1d_destroy_f}
        f[self.type](self.vsip)
        del(self.__jvsip)
    @property
    def vsip(self):
        return self.__conv
    @property
    def type(self):
        return self.__type
    @property
    def kernel_len(self):
        return self.__kernel_len
    @property
    def symm(self):
        return CONV.symmStrings[self.__symm]
    @property
    def support(self):
        return self.__support
    @property
    def data_len(self):
        return self.__dtaLength
    @property
    def out_len(self):
        return self.__outLen
    @property
    def decimation(self):
        return self.__decimation
    def convolve(self,x,y):
        f={'conv1d_dvview_dvview_d':vsip_convolve1d_d, 'conv1d_fvview_fvview_f':vsip_convolve1d_f}
        assert 'pyJvsip.__View' in repr(x) and 'pyJvsip.__View' in repr(y),'Arguments to convolve must be pyJvsip views'
        t=self.type+x.type+y.type
        assert f.has_key(t),'Type <:' + t + ':> not recognized by convolve method'
        assert y.length == self.out_len, 'Output vector length not equal to calculated output length'
        f[t](self.vsip,x.view,y.view)
        return y

# vsip_dcorr1d_create_f
# vsip_dcorr1d_destroy_f
# vsip_dcorr1d_getattr_f
# vsip_dcorrelate1d_f
class CORR(object):
    """
    See VSIPL specification for more information on correlation.
    """
    tCorr=['corr1d_f','corr1d_d','ccorr1d_f','ccorr1d_d']
    corrSel={'mview_f':'corr1d_f','mview_d':'corr1d_d','cmview_f':'ccorr1d_f','cmview_d':'ccorr1d_d'}
    supported=['cmview_d','cmview_f','mview_d','mview_f']
    supReg = {0:VSIP_SUPPORT_FULL,1:VSIP_SUPPORT_SAME,2:VSIP_SUPPORT_MIN,
              'FULL':VSIP_SUPPORT_FULL,'SAME':VSIP_SUPPORT_SAME,'MIN':VSIP_SUPPORT_MIN}
    supportStrings={0:'FULL',1:'SAME',2:'MIN'}
    algHint={0:VSIP_ALG_TIME, 1:VSIP_ALG_SPACE, 2:VSIP_ALG_NOISE,
             'TIME':VSIP_ALG_TIME,'SPACE':VSIP_ALG_SPACE,'NOISE':VSIP_ALG_NOISE}
    def __init__(self,t,repSize,dtaSize,region,ntimes,hint):
        f={'ccorr1d_d':vsip_ccorr1d_create_d,'ccorr1d_f':vsip_ccorr1d_create_f,
           'corr1d_d':vsip_corr1d_create_d,'corr1d_f':vsip_corr1d_create_f}
        assert isinstance(t,str),'Type argument must be a string for function corr'
        assert f.has_key(t), 'Type <:'+t+':> not recognized by function corr'
        assert CORR.algHint.has_key(hint), 'Argument hint not recognized by function corr'
        assert CORR.supReg.has_key(region), 'Argument for support region not recognized by function corr'
        assert isinstance(repSize,int) and isinstance(dtaSize,int) and isinstance(ntimes,int),\
               'Arguments two, three and five must be integers'
        assert repSize > 0 and repSize <= dtaSize, \
          'The replica vector length must be > 0 and <= to the length of the data vector'
        self.__jvsip = JVSIP()
        self.__type = t
        self.__corr = f[t](repSize,dtaSize,CORR.supReg[region],ntimes,CORR.algHint[hint])
        self.__repLength = repSize
        self.__dtaLength = dtaSize
        if CORR.supReg[region]==VSIP_SUPPORT_FULL:
            self.__lagLength = dtaSize + repSize - 1
        elif CORR.supReg[region]==VSIP_SUPPORT_MIN:
            self.__lagLength = dtaSize - repSize + 1
        else:
            self.__lagLength = dtaSize
        self.__support = CORR.supportStrings[CORR.supReg[region]]
    def __del__(self):
        f={'ccor1d_d':vsip_ccorr1d_destroy_f, 'ccor1d_f':vsip_ccorr1d_destroy_f,
           'corr1d_d': vsip_corr1d_destroy_d, 'corr1d_f': vsip_corr1d_destroy_f}
        f[self.type](self.vsip)
        del(self.__jvsip)
    @property
    def type(self):
        return self.__type
    @property
    def vsip(self):
        return self.__corr
    @property
    def support(self):
        """ Support attribute
        """
        return self.__support
    @property
    def lag_len(self):
        return self.__lagLength
    @property
    def ref_len(self):
        """ Reference vector length attribute
        """
        return self.__repLength
    @property
    def data_len(self):
        """ Data Length attribute
        """
        return self.__dtaLength
    def correlate(self,bias,ref,x,y):
        """
        See VSIP specification document for more Information.
        Usage:
            correlate(bias, ref, x, y)
        Where:
            bias 'BIASED' or 'UNBIASED' to select correlation normalization.
            ref  reference vector
            x    input view
            y    output view
        """
        biasSelect={0:VSIP_BIASED,1:VSIP_UNBIASED, 'BIASED':VSIP_BIASED,
              'UNBIASED':VSIP_UNBIASED}
        f={'ccorr1d_dcvview_dcvview_dcvview_d':vsip_ccorrelate1d_d,
           'ccorr1d_fcvview_fcvview_fcvview_f':vsip_ccorrelate1d_f,
           'corr1d_dvview_dvview_dvview_d':vsip_correlate1d_d,
           'corr1d_fvview_fvview_fvview_f':vsip_correlate1d_f}
        assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
           and 'pyJvsip.__View' in repr(c),\
           'The last three arguments of method correlate must be pyJvsip views'
        t = self.type+ref.type+x.type+y.type
        assert f.has_key(t),'Type<:'+t+' not recognized for correlate object'
        assert biasSelect(bias).has_key(bias), \
                'Bias key not recogonized for correlate method'
        assert ref.length == self.ref_len, \
            'Reference vector length not in correlate object'
        assert x.length == self.data_len, \
            'data vector length not in correlate object'
        f[t](self.vsip,biasSelect[bias],ref.view,x.view,y.view)
        return y

# filter Class
class FIR(object):
    tFir=['fir_f','fir_d','cfir_f','cfir_d','rcfir_f','rcfir_d']
    def __init__(self,t,filt,sym,N,D,state):
        """
        Usage:
           firObj = FIR(t,filt,sym,N,D,state,ntimes,hint)
        t is a type string; one of:
              'rcfir_f','cfir_f','fir_f','rcfir_d','cfir_d','fir_d'
        filt is a vector view of filter coefficients
        sym is a string; one of 'NONE','ODD','EVEN'
        state (save state) is 'NO' or 'YES'
        """
        filtSptd = {'fir_f':'vview_f',
                     'fir_d':'vview_d',
                     'cfir_f':'cvview_f',
                     'cfir_d':'cvview_d',
                     'rcfir_f':'vview_f',
                     'rcfir_d':'vview_d'}
        firCreate = {'fir_f':vsip_fir_create_f,
                     'fir_d':vsip_fir_create_d,
                     'cfir_f':vsip_cfir_create_f,
                     'cfir_d':vsip_cfir_create_d,
                     'rcfir_f':vsip_rcfir_create_f,
                     'rcfir_d':vsip_rcfir_create_d}
        symType={'NONE':0,'ODD':1,'EVEN':2}
        stateType={'NO':1,'YES':2}
        assert filt.type == filtSptd[t],\
                  'Filter Coefficients in wrong view type for filter of type ' + t
        assert firCreate.has_key(t), 'Filter type not recognized'
        assert sym in ['NONE','ODD','EVEN'],'Sym flag not recognized'
        assert state in ['NO','YES'],'State flag not recognized'
        self.__jvsip = JVSIP()
        self.__type = t
        self.__fir = firCreate[t](filt.view,symType[sym],N,D,stateType[state],0,0)
        self.__length = N
        self.__decimation=D
        self.__state = state

    def __del__(self):
        firDestroy = {'fir_f':vsip_fir_destroy_f,
                     'fir_d':vsip_fir_destroy_d,
                     'cfir_f':vsip_cfir_destroy_f,
                     'cfir_d':vsip_cfir_destroy_d,
                     'rcfir_f':vsip_rcfir_destroy_f,
                     'rcfir_d':vsip_rcfir_destroy_d}
        firDestroy[self.type](self.vsip)
        del(self.__jvsip)
    def flt(self,x,y):
        """
        Usage:
             fir = FIR(...)
             fir.flt(x,y)
             x is input view of data to be filtered
             y is output view of filtered data
        """
        filtSptd = {'fir_f':'vview_f','fir_d':'vview_d',\
                     'cfir_f':'cvview_f','cfir_d':'cvview_d',\
                     'rcfir_f':'cvview_f','rcfir_d':'cvview_d'}
        firflt = {'fir_f':vsip_firflt_f,'fir_d':vsip_firflt_d,\
                  'cfir_f':vsip_cfirflt_f,'cfir_d':vsip_cfirflt_d,\
                  'rcfir_f':vsip_rcfirflt_f,'rcfir_d':vsip_rcfirflt_d}
        assert x.type == y.type
        assert filtSptd[self.type] == x.type
        firflt[self.type](self.vsip,x.view,y.view)
        return y
    def reset(self):
        fir_reset = {'fir_f':vsip_fir_reset_f,'fir_d':vsip_fir_reset_d,
                  'cfir_f':vsip_cfir_reset_f,'cfir_d':vsip_cfir_reset_d,
                  'rcfir_f':vsip_rcfir_reset_f,'rcfir_d':vsip_rcfir_reset_d}
        if self.state:
            fir_reset[self.type](self.vsip)
        return self
    @property
    def state(self):
        if self.__state == 'YES':
            return True
        else:
            return False
    @property
    def type(self):
        return self.__type
    @property
    def vsip(self):
        return self.__fir
    @property
    def length(self):
        return self.__length
    @property
    def decimation(self):
        return self.__decimation

# Linear Algebra Classes
# vsip_dlud_p
# vsip_dlud_create_p
# vsip_dlud_destroy_p
# vsip_dlud_getattr_p
# vsip_dlusol_p
class LU(object):
    tLu=['lu_f','lu_d','clu_f','clu_d']
    luSel={'mview_f':'lu_f','mview_d':'lu_d','cmview_f':'clu_f','cmview_d':'clu_d'}
    supported=['cmview_d','cmview_f','mview_d','mview_f']
    def __init__(self,t,luSize):
        luCreate={'clu_f':vsip_clud_create_f,
              'clu_d':vsip_clud_create_d,
              'lu_f':vsip_lud_create_f,
              'lu_d':vsip_lud_create_d}
        self.__jvsip = JVSIP()
        self.__type = t
        self.__size = luSize
        self.__m = {'matrix':0}
        self.__singular=1
        if luCreate.has_key(t) and luSize > 0 and isinstance(luSize,int):
            self.__lu = luCreate[t](luSize)
        else:
            print('Type must be one of '+repr(tLu)+ \
                  ' and size must be an integer greater than 0.')
            return
    def __del__(self):
        del(self.__jvsip)
        vsip.destroy(self.__lu)
    @property
    def type(self):
        return self.__type
    @property
    def size(self):
        return self.__size
    @property
    def singular(self):
        if self.__singular == 0:
            return True
        else:
            return False
    @property
    def vsip(self):
        return self.__lu
    def decompose(self,m):
        """
        Usage:
            luObj.decompose(A)
            A is a square matrix of type real or complex float or double
        decompose method for LU object atta
        """
        tMatrix={'cmview_d':'clu_d','cmview_f':'clu_f','mview_d':'lu_d','mview_f':'lu_f'}
        luDecompose={'lu_f':vsip_lud_f,
                'lu_d':vsip_lud_d,
                'clu_f':vsip_clud_f,
                'clu_d':vsip_clud_d}
        assert 'pyJvsip.__View' in repr(m),'Input must be a pyJvsip view in LU Decompose'
        assert m.rowlength == m.collength,'Matrix must be square for LU'
        assert m.type in LU.supported, 'Matrix not supported by LU'
        assert self.size == m.rowlength,\
                     'LU object of size %d but matrix of size %d'%(self.size,m.rowlength)
        self.__singular=luDecompose[self.type](self.vsip,m.view)
        self.__m['matrix'] = m
        return self
    def solve(self,opIn,inOut):
        """
           sv.solve(opA,XB)
           opA should be a string equal to 'NTRANS', 'TRANS', or 'HERM'
        or
           opA should be a C VSIPL Flag
           XB is a matrix. Solve is done in place.
           For pyJvsip if a vector is passed in for XB it will work as a matrix with a
           single column.
        I have tried to make this generic but it is probably possible to pass in arguments
        which will cause a failure when calling the underlying VSIPL functions.
        """
        op = {'NTRANS':VSIP_MAT_NTRANS,'TRANS':VSIP_MAT_TRANS,'HERM':VSIP_MAT_HERM}
        if 'vview' in inOut.type:
            XB=inOut.block.bind(inOut.offset,inOut.stride,inOut.length,1,1)
        else:
            XB=inOut
        luSol={'lu_d':vsip_lusol_d,'lu_f':vsip_lusol_f,\
               'clu_d':vsip_clusol_d,'clu_f':vsip_clusol_f}
        assert (type(opIn) is str) or (type(opIn) is int), "LU solve: Matrix Operator must be string or int."
        if type(opIn) is str:
            assert ('TRANS' in opIn) or ('HERM' in opIn), "LU solve: Flag type %s not recognized."%opIn
            if 'NTRANS' in opIn:
                opM=op['NTRANS']
            elif 'HERM' in opIn:
                if 'clu' in self.type:
                    opM=opn['HERM']
                else:
                    opM=np['TRANS']
            else:
                opM=op['TRANS']
        else:
            assert (opIn >= 0) and (opIn < 3), "LU solve: Flag %d not recognized"%opIn
            opM = opIn
            if 'clu' not in self.type and opM == 2:
                opM = 1
        if (XB.type in LU.supported) and (XB.collength == self.size):
            if self.__m['matrix'] == 0:
                print('LU object has no matrix associated with it')
                return
            else:
                luSol[self.type](self.vsip,opM,XB.view)
                return inOut
        else:
            print('Input matrix must be conformant with lu')
            return

# vsip_dchold_p
# vsip_dchold_create_p
# vsip_dchold_destroy_p
# vsip_dchold_getattr_p
# vsip_dcholsol_p
class CHOL(object):
    """
    Cholesky Decompossition
    """
    tChol=['chol_f','chol_d','cchol_f','cchol_d']
    cholSel={'mview_f':'chol_f','mview_d':'chol_d','cmview_f':'cchol_f','cmview_d':'cchol_d'}
    uplowSel={0:VSIP_TR_LOW,1:VSIP_TR_UPP,'UPP':VSIP_TR_UPP,'LOW':VSIP_TR_LOW}
    supported=['cmview_d','cmview_f','mview_d','mview_f']
    def __init__(self,t,uplow,cholSize):
        """
        See C VSIP specification for more info.
        Usage:
          chol=CHOL(t,upOrLow,N)
        Where:
          t is the cholesky type ('cchol_f','cchol_d','chol_f','chol_d'
          upOrLow is a string 'UPP' to indicate the upper triangular portion of the matrix
                 is to be used or 'LOW' if the lower triangular portion.
          N is the size of the square matrix.

        """
        cholCreate={'cchol_f':vsip_cchold_create_f,
                    'cchol_d':vsip_cchold_create_d,
                    'chol_f':vsip_chold_create_f,
                    'chol_d':vsip_chold_create_d}
        self.__jvsip = JVSIP()
        self.__type = t
        self.__size = cholSize
        self.__m = {'matrix':0}
        assert cholCreate.has_key(t) and cholSize > 0 and isinstance(cholSize,int), \
               'CHOL create error. Check type, and size. Size must be an int greater than 0.'
        assert CHOL.uplowSel.has_key(uplow),'Flag for upper or lower matrix not recognized'
        self.__chol = cholCreate[t](CHOL.uplowSel[uplow],cholSize)
    def __del__(self):
        cholDestroy={'cchol_f':vsip_cchold_destroy_f,
                    'cchol_d':vsip_cchold_destroy_d,
                    'chol_f':vsip_chold_destroy_f,
                    'chol_d':vsip_chold_destroy_d}
        del(self.__jvsip)
        cholDestroy[self.__type](self.__chol)
    @property
    def type(self):
        return self.__type
    @property
    def size(self):
        return self.__size
    @property
    def vsip(self):
        return self.__chol
    def decompose(self,m):
        """
        Decompose method for CHOL object
        Usage for cholesky object chold:
            chold.decompose(A)
        Where:
            A is a square matrix of type real or complex float or double
        """
        tMatrix={'cmview_d':'cchol_d','cmview_f':'cchol_f',
                 'mview_d':'chol_d','mview_f':'chol_f'}
        cholDecompose={'chol_f':vsip_chold_f,
                'chol_d':vsip_chold_d,
                'cchol_f':vsip_cchold_f,
                'cchol_d':vsip_cchold_d}
        assert 'pyJvsip.__View' in repr(m), \
              'Input for CHOL decompose method must be a pyJvsip view'
        assert tMatrix[m.type] == self.type, 'Type <:'+m.type+':> not supported by CHOL object'
        assert m.rowlength == m.collength and m.rowlength == self.size,\
            'For chold object (decomposition) matrix must be square and of size '+repr(self.size)
        cholDecompose[self.type](self.vsip,m.view)
        self.__m['matrix'] = m
        return self
    def solve(self,inOut):
        """
        Usage for cholesky object chold:
           chold.solve(XB)
           XB is a matrix. Solve is done in place.
           For pyJvsip if a vector is passed in for XB it will work as a matrix with a
           single column.
        I have tried to make this generic but it is probably possible to pass in arguments
        which will cause a failure when calling the underlying VSIPL functions.
        """
        cholSol={'chol_d':vsip_cholsol_d,'chol_f':vsip_cholsol_f,\
               'cchol_d':vsip_ccholsol_d,'cchol_f':vsip_ccholsol_f}
        tMatrix={'cmview_d':'cchol_d','cmview_f':'cchol_f',
                 'mview_d':'chol_d','mview_f':'chol_f'}
        assert 'pyJvsip.__View' in repr(inOut), \
              'Input for CHOL decompose method must be a pyJvsip view'
        if 'vview' in inOut.type:
            a=inOut.block.bind(inOut.offset,inOut.stride,inOut.length,1,1)
        else:
            a=inOut
        assert a.collength == self.size,'Size error in CHOL solve'
        assert tMatrix.has_key(a.type), 'Type <:'+inOut.type+':> not supported by CHOL solve'
        assert tMatrix[a.type] == self.type, 'Cholesky object does not match input view'
        assert self.__m['matrix'] != 0, 'Cholesky object not associated with a matrix'
        cholSol[self.type](a.view)
        return inOut

class QR(object):
    """ qSave is VSIP_QRD_NOSAVEQ => 0 (No Q)
                VSIP_QRD_SAVEQ => 1  (Full Q)
                VSIP_QRD_SAQVEQ1 =>2 (skinny Q)
        qOp
                VSIP_MAT_NTRANS => 0,
                VSIP_MAT_TRANS => 1,
                VSIP_MAT_HERM => 2,
        qSide
                VSIP_MAT_LSIDE => 0,
                VSIP_MAT_RSIDE => 1
        qProb
                VSIP_COV => 0,
                VSIP_LLS => 1
   """
    tQr=['qr_f','qr_d','cqr_f','cqr_d']
    qrSel={'mview_f':'qr_f','mview_d':'qr_d','cmview_f':'cqr_f','cmview_d':'cqr_d'}
    supported=['cmview_d','cmview_f','mview_d','mview_f']
    qSave=['NOSAVEQ','SAVEQ','SAVEQ1', VSIP_QRD_NOSAVEQ, VSIP_QRD_SAVEQ, VSIP_QRD_SAVEQ1]
    selQsave = {'NOSAVEQ':0,'SAVEQ':1,'SAVEQ1':2, 0:VSIP_QRD_NOSAVEQ, 1:VSIP_QRD_SAVEQ, 2:VSIP_QRD_SAVEQ1}
    qSide = {'LSIDE':VSIP_MAT_LSIDE,'RSIDE':VSIP_MAT_RSIDE,0:VSIP_MAT_LSIDE,1:VSIP_MAT_RSIDE}
    qOp = {'NTRANS':VSIP_MAT_NTRANS,'TRANS':VSIP_MAT_TRANS,'HERM':VSIP_MAT_HERM,
            0:VSIP_MAT_NTRANS,1:VSIP_MAT_TRANS,2:VSIP_MAT_HERM}
    qProb={'COV':VSIP_COV,'LLS':VSIP_LLS,0:VSIP_COV,1:VSIP_LLS}
    probSel={0:'COV',1:'LLS'}
    def __init__(self,t,m,n,qSave):
        qrCreate={'cqr_f':vsip_cqrd_create_f,
              'cqr_d':vsip_cqrd_create_d,
              'qr_f':vsip_qrd_create_f,
              'qr_d':vsip_qrd_create_d}
        assert qrCreate.has_key(t), 'Type <:%s:> not recognized for QR'%repr(t)
        assert type(m) is int and type(n) is int,"Row and column sizes must be integers"
        assert m >= n and n > 0, "For QR lengths are greater than zero and column length is >= row length"
        assert QR.selQsave.has_key(qSave), 'Flag for save Q is %s. Flag not recognized for QR'%repr(qSave)
        self.__jvsip = JVSIP()
        if t in QR.tQr:
            self.__type = t
        else:
            print('Type qr not found')
            return
        self.__qSave = QR.selQsave[qSave]
        self.__collength = m
        self.__rowlength = n
        self.__m = {'matrix':0}
        self.__qr = qrCreate[t](m,n,QR.selQsave[qSave])
    def __del__(self):
        del(self.__jvsip)
        vsip.destroy(self.__qr)
    @property
    def type(self):
        return self.__type
    @property
    def size(self):
        return {'ColumnLength':self.__collength,'RowLength':self.__rowlength}
    @property
    def args(self):
        return (self.__collength,self.__rowlength,self.__qSave)
    @property
    def qSize(self):
        attr=self.args
        m=attr[0];n=attr[1];op=attr[2]
        if op == 0:
            return (0,0)
        elif op == 1:
            return(m,m)
        else:
            return(m,n)
    @property
    def vsip(self):
        return self.__qr
    def decompose(self,m):
        tMatrix={'cmview_d':'cqr_d','cmview_f':'cqr_f','mview_d':'qr_d','mview_f':'qr_f'}
        qrDecompose={'qr_f':vsip_qrd_f,
                'qr_d':vsip_qrd_d,
                'cqr_f':vsip_cqrd_f,
                'cqr_d':vsip_cqrd_d}
        assert 'pyJvsip.__View' in repr(m),'Input to decompose must be a pyJvsip view'
        assert tMatrix.has_key(m.type),'Type <:%s:> not supported for QR'%m.type
        assert self.type == tMatrix[m.type],\
                 'View of type <:%s:> not compliant with QR object of type <:%s:>'%(m.type,self.type)
        assert self.__collength==m.collength and self.__rowlength==m.rowlength, \
                 'Matrix to decompose and QR object are not the same size.'
        qrDecompose[self.type](self.vsip,m.view)
        self.__m['matrix'] = m
        return self
    def prodQ(self,op,side,X):
        qrProd={'qr_d':vsip_qrdprodq_d,'qr_f':vsip_qrdprodq_f, \
               'cqr_d':vsip_cqrdprodq_d,'cqr_f':vsip_cqrdprodq_f}
        assert 'pyJvsip.__View' in repr(self.__m['matrix']), 'No matrix associated with QR object.'
        assert QR.qSide.has_key(side),\
         "Flag for Q side not recognized; should be 'LSIDE' or 'RSIDE'"
        assert QR.qOp.has_key(op),\
         "Flag for Q option not recognized; should be 'NTRANS', 'TRANS' or 'HERM' "
        assert self.args[2] != 0,'QR object told not to save Q. No matrix product available'
        assert 'pyJvsip.__View' in repr(X),'The last argument to prodQ must be a pyJvsip view.'
        assert QR.qrSel.has_key(X.type),'The input view to prodQ is not supported by QR object'
        assert QR.qrSel[X.type] == self.type,\
                 'The input view to prodQ not the type the QR object was created for'
        m,n=self.qSize
        XM=X.collength
        if QR.qSide[side] == VSIP_MAT_LSIDE:
            if QR.qOp[op] == VSIP_MAT_TRANS or QR.qOp[op] == VSIP_MAT_HERM:
                assert m == XM, 'Matrix product size error  in prodQ'
            else: #must be NTRANS
                assert n == XM,'Matrix product Size Error in prodQ'
        else: #must be RSIDE
            if QR.qOp[op] == VSIP_MAT_TRANS or QR.qOp[op] == VSIP_MAT_HERM:
                assert n == XM,'Matrix product Size Error in prodQ'
            else: #must be NTRANS
                assert m == XM, 'Matrix product Size Error in prodQ'
        qrProd[self.type](self.vsip,QR.qOp[op],QR.qSide[side],X.view)
        return X
    def solveR(self,op,alpha,XB):
        qrSol={'qr_d':vsip_qrsolr_d,'qr_f':vsip_qrsolr_f,\
               'cqr_d':vsip_cqrsolr_d,'cqr_f':vsip_cqrsolr_f}
        assert 'pyJvsip.__View' in repr(self.__m['matrix']), 'No matrix associated with QR object.'
        assert isinstance(alpha,int) or isinstance(alpha,float) or isinstance(alpha,complex),\
            'Second argument must be a number compatible with input/output view'
        assert QR.qOp.has_key(op),'Flag for matrix operation not found.'
        assert 'pyJvsip.__View' in repr(XB),'Last argument must be a pyJvsip View'
        assert QR.qrSel.has_key(XB.type)
        if 'cmview_d' in XB.type:
            sclr=vsip_cmplx_d(alpha.real,alpha,imag)
        elif 'cmview_f' in XB.type:
            sclr= vsip_cmplx_f(alpha.real,alpha.imag)
        else:
            sclr=alpha
        assert self.__rowlength == XB.rowlength,'Size error for solveR.'
        assert self.type == qrSel[XB.type], 'The input view does not comply with QR object type'
        qrSol[self.type](self.vsip,QR.qOp[op],sclr,XB.view)
        return XB
    def solve(self,prob,XB):
        qrSol={'qr_d':vsip_qrsol_d,'qr_f':vsip_qrsol_f,\
               'cqr_d':vsip_cqrsol_d,'cqr_f':vsip_cqrsol_f}
        assert 'pyJvsip.__View' in repr(self.__m['matrix']),'No matrix associated with QR object'
        assert QR.qProb.has_key(prob),"QR problem type should be 'COV' or 'LLS'. "
        assert 'pyJvsip.__View' in repr(XB),'The second argument to solve must be a pyJvsip view'
        assert QR.qrSel.has_key(XB.type),'The second argument is not supported by QR'
        assert QR.qrSel[XB.type] == self.type,\
        'The QR object of type <:%s:> was not defined for an input/output view of type <:%s:>'%(self.type,XB.type)
        if 'COV' == QR.probSel[QR.qProb[prob]]:
            assert XB.collength == self.__rowlength, 'Size error for solve covariance problem'
        else: # must be LLS
            assert XB.collength == self.__collength, 'Size error for solve least square problem'
        qrSol[self.type](self.vsip,QR.qProb[prob],XB.view)
        return XB

class SV(object):
    """
    Usage:
       svObj=SV(type, colLength,rowLength,opU,opV)
    Where:
       type is a string; one of 'sv_f', 'sv_d', 'csv_f', csf_d'
       colLength and rowLength are the sizes of the expected matrix,
       opU and opV are strings; one of 'NOS', 'FULL', 'PART' indicating
       what part of the U and S matrices are to be retained.
    Note you may also use the string coresponding to the target matrix for type.
    For instance if only singular values of matrix A are required then you could do
    sv=SV(A.type,A.collength,A.rowlength,'NOS','NOS')
    """
    tSv=['sv_f','sv_d','csv_f','csv_d']
    supported=['mview_d','cmview_d','mview_f','cmview_f']
    svSel={'sv_f':'mview_f','sv_d':'mview_d','csv_f':'cmview_f','csv_d':'cmview_d'}
    svvSel={'sv_f':'vview_f','sv_d':'vview_d','csv_f':'vview_f','csv_d':'vview_d'}
    tSel={'sv_f':'sv_f','mview_f':'sv_f','sv_d':'sv_d','mview_d':'sv_d',
          'csv_f':'csv_f','cmview_f':'csv_f','csv_d':'csv_d','cmview_d':'csv_d'}
    opSel={'NOS':VSIP_SVD_UVNOS,'FULL':VSIP_SVD_UVFULL,\
            'PART':VSIP_SVD_UVPART,0:VSIP_SVD_UVNOS,1:VSIP_SVD_UVFULL,2:VSIP_SVD_UVPART}
    def __init__(self,t,m,n,opU,opV):
        svCreate={'sv_f':vsip_svd_create_f,
              'sv_d':vsip_svd_create_d,
              'csv_f':vsip_csvd_create_f,
              'csv_d':vsip_csvd_create_d}
        assert SV.tSel.has_key(t),'Type <:%s:> not recognized for SV'%repr(t)
        assert isinstance(m,int) and isinstance(n,int),'Length arguments must be integers for SV'
        assert SV.opSel.has_key(opU) and SV.opSel.has_key(opV), 'Singular Value flags not recognized'
        self.__jvsip = JVSIP()
        self.__type = SV.tSel[t]
        self.opU=SV.opSel[opU]
        self.opV=SV.opSel[opV]
        self.m=m
        self.n=n
        self.__sv=svCreate[SV.tSel[t]](m,n,SV.opSel[opU],SV.opSel[opV])
        self.View=0.0
    def __del__(self):
        svDestroy={'sv_f':vsip_svd_destroy_f,
              'sv_d':vsip_svd_destroy_d,
              'csv_f':vsip_csvd_destroy_f,
              'csv_d':vsip_csvd_destroy_d}
        svDestroy[self.type](self.vsip)
        del(self.__jvsip)
    @property
    def type(self):
        """
        SV property returning type string.
        """
        return self.__type
    @property
    def vsip(self):
        """
        SV property returning VSIPL svd object.
        Must retain reference to containing SV object to use.
        """
        return self.__sv
    def svd(self,other,s):
        """
        Usage:
            given matrix view A of type real or complex, float or double
            and real vector view s of equivalent precision to A (float or double)
            and s of length min(A.collength, A.rowlength)
            and SV Object sv then
            sv.svd(A,s) will calculate the singular values of A and place them in s.
        Note that the matrix A is overwritten by the singular value calculation. To keep
        A use sv.svd(A.copy,s).
        """
        svdD={'sv_f':vsip_svd_f,
              'sv_d':vsip_svd_d,
              'csv_f':vsip_csvd_f,
              'csv_d':vsip_csvd_d}
        self.View=other
        if SV.svSel[self.type] in other.type and SV.svvSel[self.type] in s.type:
            svdD[self.type](self.vsip,other.view,s.view)
            return s
        else:
            print('svd does not understand argument list\n')
            return
    def matv(self,low,high,other):
        """
        valid arguments are (low,high,outView)
        """
        svMatV={'sv_f':vsip_svdmatv_f,
              'sv_d':vsip_svdmatv_d,
              'csv_f':vsip_csvdmatv_f,
              'csv_d':vsip_csvdmatv_d}
        if SV.opSel['NOS'] == self.opV:
            return
        else:
            svMatV[self.type](self.vsip,low,high,other.view)
            return other
    def matu(self,low,high,other):
        """
        valid arguments are (low,high,outView)
        """
        svMatU={'sv_f':vsip_svdmatu_f,
              'sv_d':vsip_svdmatu_d,
              'csv_f':vsip_csvdmatu_f,
              'csv_d':vsip_csvdmatu_d}
        if SV.opSel['NOS'] == self.opU:
            return
        else:
            svMatU[self.type](self.vsip,low,high,other.view)
            return other
    def prodv(self):
        return
    def produ(self):
        return

# pyJvsip Functions
def create(atype,*vals):
    """
       usage:
          anObject=create(aType,...)
       where:
          aType corresponds to a valid type for the object being created and
          ... are a variable argument list associated with each supported create type
        The create function has default values for most creates. For instance the matrix create will be row major
        by default, and no memory hints are used since the jvsip distribution does not support
        (underneath the covers) the vsip_memory_hint.
        QR creates are by default for the full Q, SV creates are by default for the full matrix.
    """
    blockTypes = Block.tBlock
    vectorTypes=['cvview_f','cvview_d','vview_f','vview_d','vview_i','vview_si','vview_uc',\
                 'vview_vi','vview_mi','vview_bl']
    fVector = {'vview_f':'block_f','vview_d':'block_d','cvview_f':'cblock_f', \
               'cvview_d':'cblock_d','vview_i':'block_i','vview_si':'block_si', \
               'vview_uc':'block_uc','vview_bl':'block_bl','vview_vi':'block_vi', \
               'vview_mi':'block_mi'}
    matrixTypes=['cmview_f','cmview_d','mview_f','mview_d','mview_i','mview_si','mview_uc', \
                 'mview_bl']
    fMatrix = {'mview_f':'block_f','mview_d':'block_d','cmview_f':'cblock_f',\
               'cmview_d':'cblock_d','mview_i':'block_i','mview_si':'block_si',\
               'mview_uc':'block_uc','mview_bl':'block_bl'}
    fftTypes = FFT.tFft
    mfftTypes = ['ccfftmip_f', 'ccfftmop_f', 'rcfftmop_f', 'crfftmop_f', \
                 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', 'crfftmop_d']
    vfftTypes=['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', \
               'ccfftip_d', 'ccfftop_d', 'rcfftop_d', 'crfftop_d']
    luTypes = LU.tLu
    svTypes = SV.tSv
    qrTypes = QR.tQr
    cholTypes=CHOL.tChol
    convTypes=CONV.tConv
    corrTypes=CORR.tCorr
    randType = Rand.tRand
    majorType=['ROW','COL',VSIP_ROW,VSIP_COL]
    mat_uploFlag=['UPP','LOW',VSIP_TR_LOW,VSIP_TR_UPP]
    assert isinstance(atype,str),'Types used in the create function must be a string'
    if atype in blockTypes:
        assert len(vals) == 1, 'Create for %s has a single length argument'%atype
        assert isinstance(vals[0],int) or isinstance(vals[0],long), 'Length for %s must be an integer'%atype
        return Block(atype,vals[0])
    elif atype in vectorTypes:
        assert len(vals) == 1, 'Create for %s has a single length argument'%atype
        assert isinstance(vals[0],int) or isinstance(vals[0],long), 'Length for %s must be an integer'%atype
        return create(fVector[atype],vals[0]).bind(0,1,vals[0])
    elif atype in matrixTypes:
        assert len(vals) > 1 and len(vals) < 4, \
                'Create for %s has two length arguments and an optional major argument'%atype
        assert (isinstance(vals[0],int) and isinstance(vals[1],int)) or \
               (isinstance(vals[0],long) and isinstance(vals[1],long)), 'Lengths for %s must be integers'%atype
        cl=vals[0]
        rl= vals[1]
        l=rl * cl
        offset=0
        row_stride=1
        col_stride=rl
        if len(vals) == 3:
            assert vals[2] in majorType, 'Flag %s not recognized as a vsip_major type'%repr(vals[2])
            if vals[2] == VSIP_COL or vals[2] == 'COL':
                row_stride=cl
                col_stride=1
        return create(fMatrix[atype],l).bind(offset,col_stride,cl,row_stride,rl)
    elif atype in fftTypes:
        nVals = len(vals)
        hint = 0 # set to VSIP_ALG_TIME
        ntimes = 0 # set to use a lot
        assert (atype in vfftTypes and nVals > 0) or (atype in mfftTypes and nVals > 1), \
            """
            Usage requires a single length for vectors or the column and row length for matrices.
            For vectors (matrices) the second (third) argument is a scalar indicating a scale (defaults to 1.0).
            The argument list is searched for the string "INV" and if found the object is built for an inverse FFT.
            The default is a Forward FFT If a multiple FFT is specified the argument list is searched for a string
            of "COL". If found the fft is done for each column. The default is by row."""
        if 'INV' in vals:
            dir = 1 #VSIP_FFT_INV
        else:
            dir = -1 #VSIP_FFT_FWD
        if atype in mfftTypes:
            major = 0 # default fft by row
            assert (isinstance(vals[0],int) and isinstance(vals[1],int)) or \
                   (isinstance(vals[0],long) and isinstance(vals[1],long)), \
                    'Length arguments for %s must be integers'%atype
            M = vals[0]; N = vals[1]
            if nVals > 2 and (isinstance(vals[2,int]) or isinstance(vals[2],float)):
                scaleFactor = float(vals[2])
            else:
                scaleFactor = 1.0
            if 'COL' in vals:
                major = 1 # 'VSIP_COL'
        else:
            assert isinstance(vals[0],int) or isinstance(vals[0],long),'Length argument for %s must be an integer'%atype
            N = vals[0]
            if nVals > 1 and (isinstance(vals[1],int) or isinstance(vals[1],float)):
                scaleFactor = float(vals[1])
            else:
                scaleFactor = 1.0
        if ('ccfftip' in atype) or ('ccfftop' in atype):
            arg = (N,scaleFactor,dir,ntimes,hint)
        elif ('crfftop' in atype) or ('rcfftop' in atype):
            arg = (N,scaleFactor,ntimes,hint)
        elif ('ccfftmip' in atype) or ('ccfftmop' in atype):
            arg = (M,N,scaleFactor,dir,major,ntimes,hint)
        elif ('crfftmop' in atype) or ('rcfftmop' in atype):
            arg = (M,N,scaleFactor,major,ntimes,hint)
        else:
            print('<:' + atype + ':> not recognized') #should not be able to get here
            return
        return FFT(atype,arg)
    elif atype in randType:
        assert len(vals) == 2, 'Type <:%s:> takes a type argument and an intger seed'%atype
        assert isinstance(vals[1],int), 'Argument two for random number generator is an integer'
        return Rand(atype,vals[1])
    elif atype in luTypes:
        assert len(vals) == 1, 'Type <:%s:> takes a type argument and an intger length'%atype
        assert isinstance(vals[0],int), 'Argument two for LU is an integer'
        return LU(atype,vals[0])
    elif atype in qrTypes:
        assert len(vals) > 1, \
            'Too few arguments.  Type <::%s:> takes a type, two length arguments, and an optional Q save argument'%atype
        assert len(vals) < 4, \
            'Too many arguments.  Type <::%s:> takes a type, two length arguments, and an optional Q save argument'%atype
        op='SAVEQ' #default
        if len(vals) == 3:
            assert QR.selQsave.has_key(vals[2]), 'Flag %s not recognized for QR create'%repr(vals[2])
            op=vals[2]
        return QR(atype,vals[0],vals[1],op)
    elif atype in svTypes:
        assert len(vals) > 1,\
        'Too few arguments.  Type <::%s:> takes a type, two length arguments, and two optional vsip_svd_uv save argumenta'%atype
        assert len(vals) < 5, \
            'Too many arguments.  Type <::%s:> takes a type, two length arguments, and an optional Q save argument'%atype
        opVsave='FULL';opUsave='FULL'
        if len(vals) == 3:
            assert SV.opSel.has_key(vals[2]),'Save argument not recognized for singular value'
            opVsave=SV.opSel[vals[2]]
            opUsave=opVsave
        if len(vals) == 4:
            assert SV.opSel.has_key(vals[2]) and SV.opSel.has_key(vals[3]),'Save Arguments not recognized for singular value'
            opVsave=SV.opSel[vals[3]]
            opUsave=SV.opSel[vals[2]]
        return SV(atype,vals[0],vals[1],opUsave,opVsave)
    elif atype in cholTypes:
        assert len(vals) < 3, 'Cholesky create takes either a vsip_mat_uplo flag and a length, or just a length'
        assert len(vals) > 0, 'Cholesky must have at least one integer size value'
        if len(vals) == 2:
            assert vals[0] in mat_uploFlag, "Second argument to create for type %s is 'UPP' or 'LOW' "%atype
            assert isinstance[vals[1],int], 'Third argument to create for type %s is an integer size'%atype
            matFlag=vals[0]
            sz=vals[1]
        else:
            matFlag='UPP'
            assert isinstance[vals[0],int], \
                    'Argument to create for type %s is an integer size. If not included default vsip_mat_uplo is "UPP" '%atype
            sz=vals[0]
        return CHOL(atype,matFlag,sz)
    elif atype in convTypes:
        """
        Usage Cases Convolution:
         create(atype,h,dtaLength) => symm = 'NON', dec=1, support='FULL',ntimes=0,hint='TIME'
         create(atype,h,dtaLength, dec) => symm = 'NON', support='FULL',ntimes=0,hint='TIME'
         create(atype,h,symm, dtaLength, dec) => support='FULL',ntimes=0,hint='TIME'
         create(atype,h,symm, dtaLength, dec, support) => ntimes=0,hint='TIME'
        """
        ntimes=0; hint='TIME'; symm='NON'; dec=1; support='FULL'
        nvals=len(vals)
        msg = 'For create convolution the number of arguments after type is five or less.'
        msg += '\nNote ntimes hint is always 0 and the alg hint is always "TIME" for this function.'
        msg += 'These are default values and not part of the argument list'
        msg1 = 'The first argument after the type must be a vector view conformant with the convolution type\n'
        msg1+= 'The second argument after the data type must be an integer length.'
        assert nvals > 1, 'As a minimum convolution create requires a filter view and a data length'
        h=vals[0]
        if nvals < 4:
            dtaSize = vals[1]
        else:
            dtaSize = vals[2]
            symm = vals[1]
            assert symmetry.has_key(symm),'Symmetry flag not recognized for create of %s'%atype
        assert nvals < 6, msg
        assert 'pyJvsip.__View' in repr(h) and isinstance(dtaSize,int) and CONV.convSel.has_key(h.type), msg1
        assert atype == CONV.convSel[h.type],'Type %s not conformant with %s.'%(h.type,atype)
        if nvals > 3:
            dec = vals[3]
            assert isinstance(dec,int),'Decimation value for create of %s must be an integer'%atype
        if nvals > 4:
            sup = vals[4]
            assert supportRegion.has_key(sup), 'Support region flag not recognized for create of %s'%atype
        return CONV(atype,h,symm,dtaLength,dec,sup,ntimes,hint)
    elif atype in corrTypes:
        """
        Usage:
           If region is 'FULL' use
           corr=create(atype,repSize,dtaSize)
        or:
           corr=create(atype,repSize,dtaSize,region)
           where region is one of 'FULL', 'SAVE', or 'MIN'
        ntimes and hint always default to 0 and 'TIME' respectively.
        """
        ntimes=0; hint='TIME'; region='FULL'
        region = 'FULL'
        nvals = len(vals)
        assert nvals > 1, 'As a minimum create of %s requires a reference vector length and a data vector length'%atype
        assert nvals < 4, \
           'Too many argumentsfor create of %s; has at most a type, two lengths, and a support region flag'%atype
        repSize = vals[0];dtaSize=vals[1]
        if nvals > 2:
           region = vals[2]
        assert supportRegion.has_key(region), 'Support region flag not recognized for create of %s'%atype
        assert isinstance(repSize,int), 'Reference vector length must be an for create of %s'%atype
        assert isinstance(dtaSize,int), 'Data vector length must be an integer for create of %s'%atype
        return CORR(atype,repSize,dtaSize,region,ntimes,hint)
    else:
        print('Input type <:%s:> not recognzied for create'%atype)
def svdCompose(d,indx):
    """
    Usage:
       import pyJvsip as pv
       # get pyJvsip matrix A from some process
       d=A.svd
       # create an index vector (indx) of singular values of interest.
       C=svdCompose(d,indx)
    Returns a matrix reconstituted from selected singular values.
    Note:
     d above is a tuble. See svd method info.
    Note:
     the indices in indx should be less than the length of d[1]
    Note:
     you can create a new tuple, say g=(d[0],s,d[2]) if you want
    to create a new matrix but not use the original singular values.
    Note:
      C=svdCompose(d,pv.create('vview_vi),d[0].length).ramp(0,1))
    will return (an estimate of) the original matrix A.
    """
    assert 'vview_vi' in getType(indx)[2]
    assert type(d) is tuple
    assert 'mview' in getType(d[0])[2]
    assert 'vview' in getType(d[1])[2]
    assert 'mview' in getType(d[2])[2]
    r=create(d[0].type,d[0].collength,d[2].collength).fill(0.0)
    for i in range(indx.length):
        j=indx[i]
        r += d[0].colview(j).outer(d[1][j],d[2].colview(j))
    return r
def listToJv(t,a):
    """
       listToJv will attempt to create a pyJvsip view of type t and copy the list a
       into it. Lists are very general. It is easy to create a list that listToJv can not
       handle. Lists must agree with the data type t. Currently only vectors of type
       float and double are supported.
    """
    assert t in ['vview_d','vview_f','cvview_d','cvview_d'], 'Requested type not supported'
    assert isinstance(a,list),'Input must be a list'
    n=len(a)
    v=create(t,n)
    if 'cvview_d' in t:
        for i in range(n):
            s=a[i]
            v[i]=vsip_cmplx_d(s.real,s.imag)
    elif 'cvview_f' in t:
        for i in range(n):
            s=a[i]
            v[i]=vsip_cmplx_f(s.real,s.imag)
    else:
        for i in range(n):
            v[i] = a[i]
    return v
