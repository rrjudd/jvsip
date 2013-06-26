from vsip import *
from vsipElementwiseElementary import *
from vsipElementwiseManipulation import *
from vsipElementwiseUnary import *

import vsiputils as vsip
def getType(v):
    """
        Returns a tuple with type information.
        most of the time getType(v)[2] will be the information needed.
        getType(v)[0] is the module (python, vsip, or pyJvsip)
        getType(v)[1] is the class (scalar, View, Block, etc)
        getType(v)[2] is the type which is dependent on the module and class.
    """
    if isinstance(v,int) or isinstance(v,float) or isinstance(v,complex):
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
        else:
            print('Do not recognize object')
            return
    else:
        print('Do not recognize object')
        return
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
    blockTypes = ['block_f','block_d','cblock_f','cblock_d',
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
    #View Class defined here
    class __View(object):
        viewTypes=['mview_f','mview_d','cmview_f','cmview_d',
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
        def __del__(self):
            del(self.__pyBlock)
            del(self.__jvsip)
            vsip.destroy(self.__vsipView)
        # Support functions
        @property  #scalar is a place to store a value which can be recovered from the view
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
        @classmethod
        def supported(cls):
            return cls.viewTypes
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
            if t in Block.blockTypes and b != 0:
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
        @property # returns deep (view and block) copy of object
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
            attr=self.compactAttrib(0)
            b = self.block.otherBlock(attr[0],attr[1])
            newView = b.bind(attr[2])
            vsip.copy(self.view,newView.view)
            return newView
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
        @property # A way to get a new view and data space of the same size but no copy penalty
        def empty(self):
            """
               creates a new view, on a new block, of the same type and shape as 
               the calling view. No copy or initialization takes place, so new view
               is empty, so-to-speak.
            """
            attr=self.compactAttrib(0)
            b = self.block.otherBlock(attr[0],attr[1])
            newView = b.bind(attr[2])
            return newView
        @property # A way to ge a new in-place view of the object
        def clone(self):
            return self.__clone(self)   
        #data generators
        def ramp(self,start,increment):
            supported = ['vview_f','vview_d','vview_i','vview_si','vview_uc','vview_vi']
            extended = ['cvview_f','cvview_d']
            if self.type in supported:
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
            if self.type in f:
                self.fill(0)
                self.diagview(0).fill(1)
                return self
            else:
                print('View of type <:'+self.type+':> not supported by identity')
                return False
        #support functions
        def gather(self,v,indx):
            if 'vview' not in self.type:
                print('Gather only works with a vector calling view')
                return
            f = {'cmview_d':vsip_cmgather_d, 'cmview_f':vsip_cmgather_f, 
                 'cvview_d':vsip_cvgather_d, 'cvview_f':vsip_cvgather_f,
                 'mview_d':vsip_mgather_d, 'mview_f':vsip_mgather_f,
                 'vview_d':vsip_vgather_d, 'vview_f':vsip_vgather_f,
                 'vview_i':vsip_vgather_i, 'vview_si':vsip_vgather_si,
                 'vview_uc':vsip_vgather_uc,
                 'vview_mi':vsip_vgather_mi, 'vview_vi':vsip_vgather_vi}
            if 'vview_vi' == indx.type and 'vview' in v.type:
                f[v.type](v.view,indx.view,self.view)
                return self
            elif 'vview_mi' == indx.type and 'mview' in v.type:
                f[v.type](v.view,indx.view,self.view)
                return self
            else:
                print('Argument list of types<:'+
                self.type+':>,<:'+v.type+':>,<:'+indx.type+\
                ':> not supported for gather')
                return          
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
        @property
        def real(self):
            return self.realview.copy
        @property
        def imag(self):
            return self.imagview.copy
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
        @classmethod
        def __newView(cls,v,b):
            return cls(v,b)         
        @property
        def realview(self):
            return self.__realview(self)
        @property
        def imagview(self):
            return self.__imagview(self)
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
        @property
        def mrowview(self):
            if 'vview' in self.type:
                return self.block.bind(self.offset,1,1,self.stride,self.length)
            else:
                print('The mrowview method only works with a vview input')
                return
        @property
        def mcolview(self):
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
        @classmethod
        def __clone(cls,V):
            v=vsip.cloneview(V.view)
            b=V.block
            return cls(v,b)
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
                elif isinstance(val,int) or isinstance(val,float) or isinstance(val,complex):
                    return val
                elif 'scalar_mi' in vsip.getType(val)[1]:
                    return {'row_index':val.r,'col_index':val.i}
                else:
                    print('__getitem__ does not recognize<:' +type(val)+ ':>')
                    return False
            if 'vview' in self.type and isinstance(index,int) and index >= 0:
                val=vsip.get(self.view,index)
                return scalarVal(val)
            elif 'vview' in self.type and isinstance(index,slice):
                return self.subview(index)
            elif 'mview' in self.type and (len(index) is 2) and \
                        isinstance(index[0],int) and isinstance(index[1],int) \
                        and (index[0] >=0) and (index[1] >= 0):
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
                if isinstance(i,int):
                    vsip.put(self.view,i,value)
                elif 'vview' in self.type and isinstance(i,slice):
                    copy(value,self.subview(i))
                else:
                    print('Failed to recognize index for vector view')
            elif 'mview' in self.type and isinstance(i,tuple) and len(i) == 2:
                if isinstance(i[0],slice) and isinstance(i[1],slice):
                    copy(value,self.subview(i[0],i[1]))
                elif isinstance(i[0],slice) and isinstance(i[1],int):
                    copy(value,self.subview(i[0],slice(i[1],i[1]+1,1)))
                elif (isinstance(i[0],int) and isinstance(i[1],slice)):
                    copy(value,self.subview(slice(i[0],i[0]+1,1),i[1]))
                elif (isinstance(i[0],int) and isinstance(i[1],int)):
                    vsip.put(self.view,i,value)
                else:
                    print('Failed to recognize index for matrix view')
            else:
                print('Failed to parse argument list for __setitem__') 
        def __len__(self):
            attr=vsip.size(self.__vsipView)
            n = attr[2]
            if len(attr) > 3:
                n *= attr[4]
            return int(n)
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
        # Elementwise add, sub, mul, div
        def __iadd__(self,other):
            if 'scalar' in vsip.getType(other)[1] :
                vsip.add(other,self.view,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.add(self.view,other.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for add')
                return False
        def __add__(self,other):
            retval = self.copy
            retval += other
            return retval
        def __radd__(self,other):
            retval = self.copy
            retval += other
            return retval
        def __isub__(self,other): # -=other
            if 'scalar' in vsip.getType(other)[1] : # v-a
                vsip.add(-other,self.view,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.sub(self.view,other.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for sub')
                return False
        def __sub__(self,other):#self - other
            retval=self.copy
            retval -= other
            return retval
        def __rsub__(self,other): #other - self
            if 'scalar' in vsip.getType(other)[1]:
                retval = self.copy.neg
                vsip.add(other,retval.view,retval.view)
                return retval
            elif 'pyJvsip.__View' in repr(other):
                retval = other.copy
                vsip.sub(retval.view,self.view,retval.view)
                return retval
            else:
                print('Object <:' + repr(other) +  ':> not supported for sub')
                return False
        def __imul__(self,other):# *=other
            if isinstance(other,int):
                x = float(other)
            elif isinstance(other,complex):
                if '_d' in self.type:
                    x = vsip_cmplx_d(other.real,other.imag)
                elif '_f' in self.type:
                    x = vsip_cmplx_f(other.real,other.imag)
            else:
                 x = other
            if 'scalar' in getType(other)[1] :
                vsip.mul(x,self.view,self.view)
                return self
            elif 'pyJvsip.__View' in repr(other):
                vsip.mul(other.view,self.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for mul')
                return False
        def __mul__(self,other):
            retval = self.copy
            retval *= other
            return retval
        def __rmul__(self,other): # other * self
            retval = self.copy
            retval *= other
            return retval
        def __idiv__(self,other):
            if isinstance(other,int):
                x = float(other)
            elif isinstance(other,complex):
                if '_d' in self.type:
                    x = vsip_cmplx_d(other.real,other.imag)
                elif '_f' in self.type:
                    x = vsip_cmplx_f(other.real,other.imag)
            else:
                 x = other
            if 'scalar' in getType(other)[1]:
                vsip.div(self.view,x,self.view)
                return self
            elif 'View' in getType(other)[1]:
                vsip.div(self.view,other.view,self.view)
                return self
            else:
                print('Object <:' + repr(other) +  ':> not supported for div')
                return False                 
        def __div__(self,other):
            retval=self.copy
            retval /= other
            return retval
        def __rdiv__(self,other): # other / self
            if 'scalar' in vsip.getType(other):
                print('Divide scalar by view not supported')
                return False
            else:
                retval=other.copy
                vsip.div(retval.view,self.view,retval.view)
                return retval
        #vector-matrix elementwise multiply by row or col
        def mmul(self,other):
            """
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
            """
            f={'cvview_dcmview_d':vsip_cvmmul_d,
               'cvview_fcmview_f':vsip_cvmmul_f,
               'vview_dcmview_d':vsip_rvcmmul_d,
               'vview_fcmview_f':vsip_rvcmmul_f,
               'vview_dmview_d':vsip_vmmul_d,
               'vview_fmview_f':vsip_vmmul_f}
            t=self.type+other.type
            if f.has_key(t):
                if other.__major is 'COL':
                    f[t](self.view,other.view,VSIP_COL,other.view)
                else:
                    f[t](self.view,other.view,VSIP_ROW,other.view)
                return other
            else:
                print('Type <:' + t + ':> not recognized for method mmul')
        def Mmul(self,other):
            """
            Mmul(A) expects the calling view to be of type float vector and A to be of 
            the same precision and type float matrix. Matrix A is returned as a convenience.
            Note that view A has an a major attribute. If it is set to COL then the calling vector
            is multiplied elementwise by COL, otherwise it is multiplied by ROW
            Note lengths must be conformant.
            If one is unsure of the state of the major attribute it should be set
            For instance
            v.Mmul(A.ROW)
            or
            v.Mmul(A.COL)
            Done out of place. B=v.Mmul(A) returns a new matrix with the result.
            """
            f={'cvview_dcmview_d':vsip_cvmmul_d,
               'cvview_fcmview_f':vsip_cvmmul_f,
               'vview_dcmview_d':vsip_rvcmmul_d,
               'vview_fcmview_f':vsip_rvcmmul_f,
               'vview_dmview_d':vsip_vmmul_d,
               'vview_fmview_f':vsip_vmmul_f}
            t=self.type+other.type
            if f.has_key(t):
                retval=other.empty.fill(0.0)
                if other.__major is 'COL':
                    f[t](self.view,other.view,VSIP_COL,retval.view)
                else:
                    f[t](self.view,other.view,VSIP_ROW,retval.view)
                return retval
            else:
                print('Type <:' + t + ':> not recognized for method Mmul')
        # Elementary math functions
        @property
        def acos(self):
            vsip.acos(self.view,self.view)
            return self
        @property
        def asin(self):
            vsip.asin(self.view,self.view)
            return self
        @property
        def cos(self):
            vsip.cos(self.view,self.view)
            return self
        @property
        def cosh(self):
            vsip.cosh(self.view,self.view)
            return self
        @property
        def exp(self):
            vsip.exp(self.view,self.view)
            return self
        @property
        def exp10(self):
            vsip.exp10(self.view,self.view)
            return self
        @property
        def log(self):
            vsip.log(self.view,self.view)
            return self
        @property
        def log10(self):
            vsip.log10(self.view,self.view)
            return self
        @property
        def sin(self):
            vsip.sin(self.view,self.view)
            return self
        @property
        def sinh(self):
            vsip.sinh(self.view,self.view)
            return self
        @property
        def sqrt(self):
            vsip.sqrt(self.view,self.view)
            return self
        @property
        def tan(self):
            vsip.tan(self.view,self.view)
            return self
        @property
        def tanh(self):
            vsip.tanh(self.view,self.view)
            return self
        # Unary Operations
        @property
        def arg(self):
            """ Cone out of place
                Input vector of type complex
                arg creates and returns a new vector of type real 
            """
            attrs=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            vsip.arg(self.view,out.view)
            return out      
        @property
        def conj(self):
            """
            Done In Place. For out of place use self.copy.conj.
            """
            vsip.conj(self.view,self.view)
            return self
        @property   
        def cumsum(self):
            """
            Done In Place
            """
            vsip.cumsum(self.view,self.view)
            return self
        @property
        def euler(self):
            """ Input vector of type real
                arg creates and returns a new vector of type complex 
            """
            attrs=self.compactAttrib(1)
            out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
            vsip.euler(self.view,out.view)
            return out 
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
            f = {'cmview_d':'vsip_cmmag_d(self.view,out.view)',
                 'cmview_f':'vsip_cmmag_f(self.view,out.view)',
                 'cvview_d':'vsip_cvmag_d(self.view,out.view)',
                 'cvview_f':'vsip_cvmag_f(self.view,out.view)',
                 'mview_d': 'vsip_mmag_d(self.view,out.view)',
                 'mview_f': 'vsip_mmag_f(self.view,out.view)',
                 'vview_d': 'vsip_vmag_d(self.view,out.view)',
                 'vview_f': 'vsip_vmag_f(self.view,out.view)',
                 'vview_i': 'vsip_vmag_i(self.view,out.view)',
                 'vview_si':'vsip_vmag_si(self.view,out.view)'}
            if f.has_key(self.type):
                if 'cmview' in self.type or 'cvview' in self.type:
                    attr=self.compactAttrib(1)
                else:
                    attr=self.compactAttrib(0)
                out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
                eval(f[self.type])
                return out
            else:
                print('Type <:'+self.type+':> not recognized for mag')
                return
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
            f={'cvview_f':'vsip_vcmagsq_f(self.view,out.view)',
               'cvview_d':'vsip_vcmagsq_d(self.view,out.view)',
               'cmview_f':'vsip_mcmagsq_f(self.view,out.view)',
               'cmview_d':'vsip_mcmagsq_d(self.view,out.view)'}
            if f.has_key(self.type):
                attr=self.compactAttrib(1)
                out=self.block.otherBlock(attr[0],attr[1]).bind(attr[2])
                eval(f[self.type])
                return out
            else:
                print('Type <:'+self.type+':> not recognized for magsq')
                return
        def __neg__(self):
            vsip.neg(self.view,self.view)
        @property
        def neg(self):
            """
            Done In place
            Returns a convenience copy.
            For out of place, for view x, do y = x.copy.neg
            """
            f= {'cmview_f':vsip_cmneg_d,'cmview_f':vsip_cmneg_f,'cvview_d':vsip_cvneg_d,
                'cvview_f':vsip_cvneg_f,'mview_d':vsip_mneg_d,'mview_f':vsip_mneg_f,
                'vview_d':vsip_vneg_d,'vview_f':vsip_vneg_f,'vview_i':vsip_vneg_i,'vview_si':vsip_vneg_si}
            assert f.has_key(self.type),'Method neg does not support <:'+self.type +':>.'
            f[self.type](self.view,self.view)
            return self
        @property
        def meansqval(self):
            """ returns scalar value
            """
            return vsip.meansqval(self)
            return self
        @property
        def meanval(self):
            """ returns scalar value
            """
            return vsip.meanval(self.view)
        @property
        def recip(self):
            vsip.recip(self.view,self.view)
            return self
        @property
        def rsqrt(self):
            vsip.rsqrt(self.view,self.view)
            return self
        @property 
        def sq(self):
            vsip.sq(self.view,self.view)
            return self
        @property
        def sumval(self):
            """returns a scalar
            """
            return vsip.sumval(self.view)
        @property
        def sumsqval(self):
            """ returns a scalar
            """
            return vsip.sumsqval(self.view)   
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
        def scatter(self,other,indx):
            """
              Usage:
                  self.scatter(other,indx)
              This function scatters self into other governed by indx
              View other is returned as a convienience
            """
            t=self.type+other.type+indx.type
            f={'cvview_dcmview_dvview_mi': vsip_cmscatter_d, 
               'cvview_fcmview_fvview_mi': vsip_cmscatter_f, 
               'cvview_dcvview_dvview_vi': vsip_cvscatter_d, 
               'cvview_fcvview_fvview_vi': vsip_cvscatter_f, 
               'vview_dmview_dvview_mi':   vsip_mscatter_d, 
               'vview_fmview_fvview_mi':   vsip_mscatter_f, 
               'vview_dvview_dvview_vi':   vsip_vscatter_d, 
               'vview_fvview_fvview_vi':   vsip_vscatter_f, 
               'vview_ivview_ivview_vi':   vsip_vscatter_i, 
               'vview_sivview_sivview_vi': vsip_vscatter_si, 
               'vview_ucvview_ucvview_vi': vsip_vscatter_uc}
            if f.has_key(t):
                f[t](self.view,other.view,indx.view)
                return other
            else:
                print('Input types <:'+t+':> not recognized for scatter')
                return;
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
            assert len(vars) < 2, 'Gather only supports two arguments'
            if len(vars) is 1:
                other = vars[0]
            else:
                other = create(ot[self.type],indx.length)
            t=self.type+indx.type+other.type
            f={'cmview_dvview_micvview_d': vsip_cmgather_d,
               'cmview_fvview_micvview_f': vsip_cmgather_f,
               'cvview_dvview_vicvview_d': vsip_cvgather_d,
               'cvview_fvview_vicvview_f': vsip_cvgather_f,
               'mview_dvview_mivview_d':   vsip_mgather_d,
               'mview_fvview_mivview_f':   vsip_mgather_f,
               'vview_dvview_vivview_d':   vsip_vgather_d,
               'vview_fvview_vivview_f':   vsip_vgather_f,
               'vview_ivview_vivview_i':   vsip_vgather_i,
               'vview_sivview_vivview_si': vsip_vgather_si,
               'vview_ucvview_vivview_uc': vsip_vgather_uc,
               'vview_mivview_vivview_mi': vsip_vgather_mi,
               'vview_vivview_vivview_vi': vsip_vgather_vi}
            if f.has_key(t):
                f[t](self.view,indx.view,other.view)
                return other
            else:
                print('Input types <:'+t+':> not recognized for other')
                return;
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
                    return (idx.r,idx.c)
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=vsip.vindexptrToInt(idx)
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
                    return (idx.r,idx.c)
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=vsip.vindexptrToInt(idx)
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
                    return (idx.r,idx.c)
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=vsip.vindexptrToInt(idx)
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
                    return (idx.r,idx.c)
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=vsip.vindexptrToInt(idx)
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
                    return (idx.r,idx.c)
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=vsip.vindexptrToInt(idx)
                    vsip.vindexfree(idx)
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
                    return (idx.r,idx.c)
                else:
                    idx=vsip.vindexptr()
                    eval(f[self.type])
                    retval=vsip.vindexptrToInt(idx)
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
        #Basic Algorithms
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
                   A.eros(i,j)
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
                  Done in place and the input is used up so use a copy if the input
                  matrix is needed.
            """
            supported = ['mview_f','mview_d']
            if self.type not in supported:
                print('Matrix must be of type mview_f or mview_d')
                return
            n=self.rowlength
            m=self.collength
            if m != n:
                print('Matrix must be square')
                return
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
        @property
        def plu(self):
            """ Calculate an LU decomposition with a row permutation vector
               for square Matrix A of size 'n' and type real, float.
               This operation is done out of place
                A.plu will return (a tuple)
                  an permutation (index) vector of length n (call it p)
                  a lower triangular matrix of size n (call it L)
                  an upper triangular matrix of size n (call it U)
                such that A.permute(p) will be equal to L.prod(U)
            """
            p=Block('block_vi',self.collength).vector.ramp(0,1)
            L=self.empty.identity
            U=self.copy
            supported = ['mview_f','mview_d']
            if U.type not in supported:
                print('Matrix must be of type mview_f or mview_d')
                return
            n=U.rowlength
            m=U.collength
            if m != n:
                print('Matrix must be square')
                return
            for k in range(n-1):
                pk=U.colview(k)[k:n].maxmgvalindx
                if pk != 0:
                    U.eros(k,k+pk)
                    t=p[k]
                    p[k]=p[k+pk]
                    p[k+pk]=t
                pvt=U[k,k]
                if pvt == 0.0:
                    return 0.0 
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
            if 'mview' in xy.type:
                print('Method usolve only works with vector argument')
                return
            if 'vview' in self.type:
                print('Calling view must be a (upper diagonal) matrix')
                return
            if self.rowlength != self.collength or self.rowlength != xy.length:
                print('Calling view must be square with size equal to argument length')
                return
            n=self.rowlength
            xy[0] /= self[0,0]
            for i in range(1,n):
                y0=xy[i]
                xy[i] = (y0 - self.rowview(i)[0:i].dot(xy[0:i]))/self[i,i]
            return xy             
        def usolve(self,xy):
            if 'mview' in xy.type:
                print('Method usolve only works with vector argument')
                return
            if 'vview' in self.type:
                print('Calling view must be a (upper diagonal) matrix')
                return
            if self.rowlength != self.collength or self.rowlength != xy.length:
                print('Calling view must be square with size equal to argument length')
                return
            n=self.rowlength-1
            xy[n] /= self[n,n]
            for i in range(n-1,-1,-1):
                y0=xy[i]
                xy[i] = (y0 - self.rowview(i)[i+1:n+1].dot(xy[i+1:n+1]))/self[i,i]
            return xy 
        @property
        def norm2(self):
            """This method is a property which returns the two norm
            """
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
            vSup=['vview_f','cvview_f','vview_d','cvview_d']
            mSup=['mview_f','cmview_f','mview_d','cmview_d']
            if self.type in vSup:
                return vsip_sqrt_d(self.jdot(self).real)
            if self.type in mSup:
                if self.collength >= self.rowlength:
                    t=self.transview
                    M=t.prodh(t)
                else:
                    M=self.prodh(self)
                return vsip_sqrt_d(eigB(M))
            else:
                print('Type <:'+self.type+':> not supported by norm2');
                return
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
            Done out of place.
            Usage: Given matrix view A
                B = A.herm
                returns new matrix B which is hermitian of A.
            For an in place equivalent one can do A.transview.conj or use the hermitian function call conj(A,A).
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
            f={'mview_f':vsip_mpermute_once_f,'mview_d':vsip_mpermute_once_d}
            if p.type != 'vview_vi':
                print('First input argument must be of type vview_vi')
                return
            pc=p.copy
            if self.type not in ['vview_f','vview_d','mview_d','mview_f']:
                print('permute currently only supported for real, float, views')
                return
            if 'vview' in self.type:
                self.mcolview.permute(p,'ROW')
                return self
            elif len(major) == 1 and major[0] == 'COL':
                if p.length != self.rowlength:
                    print('Length of permutation vector must be equal to row length')
                    return
                f[self.type](self.view,VSIP_COL,pc.view,self.view)
            else: #do by ROW
                if p.length != self.collength:
                    print('Length of permutation vector must be equal to column length')
                    return
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
            retval = self.empty
            f = {'cvview_d':'ccfftop_d',
                 'cvview_f':'ccfftop_f',
                 'cmview_d':'ccfftmop_d',
                 'cmview_f':'ccfftmop_f'}
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
            obj=FFT(f[self.type],arg)
            obj.dft(self,retval)
            return retval
        @property
        def ifftop(self):
            retval = self.empty
            f = {'cvview_d':'ccfftop_d',
                 'cvview_f':'ccfftop_f',
                 'cmview_d':'ccfftmop_d',
                 'cmview_f':'ccfftmop_f'}
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
            if LU.luSel.has_key(self.type) and (self.rowlength == self.collength):
                return LU(LU.luSel[self.type],self.rowlength).decompose(self)
        @property
        def luInv(self):
            if self.type in Block.matrixTypes:
                if LU.luSel.has_key(self.type) and (self.rowlength == self.collength):
                    retval=self.empty.identity
                    LU(LU.luSel[self.type],self.rowlength).decompose(self).solve(0,retval)
                    return retval
                else:
                    print('Type <:'+self.type+':> not supported for lu or not square matrix')
                    return
            else:
                print('Property luInv only works on matrices of type float')
                return
        def luSolve(self,XB):
            """
            Usage:
                X = A.luSolve(X)
                A is a matrix of type float or double; real or complex.
                On input X is a vector or matrix of the same precision as A
            luSolve solve overwrites input data with output data
            """
            sptd=['mview_f','cmview_f','mview_d','cmview_d']
            assert self.type in sptd, "Solve method only works with matrices"
            if 'vview' in XB.type:
                X=XB.block.bind(XB.offset,XB.stride,XB.length,1,1)
            else:
                X = XB
            if self.type in Block.matrixTypes and X.type == self.type:
                if LU.luSel.has_key(self.type) and (self.rowlength == self.collength) and (self.collength == X.collength):
                    LU(LU.luSel[self.type],self.rowlength).decompose(self).solve(0,X)
                    return XB
                else:
                    print('Non-conformant views for luSolve')
                    return
            else:
                print('Non-conformant views for luSolve')
                return
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
               This returns a QR object for a Full Q. (qOpt => VSIP_QRD_SAVEQ)
               NOTE for vector views:
               If the input view is a vector then the vector is converted to a matrix matrix.
               Vectors are treated as a column here.
            """
            if self.type in ['vview_f','vview_d','cvview_f','cvview_d']:
                A=self.block.bind(self.offset,self.stride,self.length,0,1)
            elif self.type in ['mview_f','mview_d','cmview_f','cmview_d']:
                A = self
            else:
                print('Type <:' +self.type+ '<: not supported for QR')
                return
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
            if self.type not in ['vview_d','vview_f','mview_d','mview_f', \
                                 'cvview_d','cvview_f','cmview_d','cmview_f']:
                print('Type <:'+self.type+':> not supported by view qrd method')
                return
            if self.type in ['vview_f','vview_d','cvview_f','cvview_d']:
                A=self.block.bind(self.offset,self.stride,self.length,0,1).copy
            elif self.type in ['mview_f','mview_d','cmview_f','cmview_d']:
                A = self.copy
            else:
                print('Type <:' +self.type+ '<: not supported for qrd')
                return
            if 'vview' in self.type:
                n = self.length
            else:
                n = self.collength
            Q = Block(Block.blkSel[self.type],n*n).bind(0,1,n,n,n).identity
            qr = A.qr
            qr.prodQ(0,0,Q)
            if 'mview' in self.type:
                R = Q.transview.prod(self)
            else:
                R = Q.transview.prod(self.block.bind(self.offset,self.stride,self.length,0,1))
            return(Q,R)
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
            print(self.mstring(fmt))
    #Block specific class below
    def __init__(self,block_type,length):
        other = ['real_f','imag_f','real_d','imag_d']
        self.__jvsip = JVSIP()
        if block_type in Block.blockTypes:
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
        if self.__type in Block.blockTypes:
            vsip.destroy(self.__vsipBlock)
        del(self.__jvsip)
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
        return {'blockTypes':Block.blockTypes,'viewTypes':Block.__View.supported()} 
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
             'vview_f':vsip_vrandn_f}
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
             'vview_f':vsip_vrandu_f}
        if f.has_key(t):
            f[t](self.rng,a.view)
            return a
        else:
            print('Not a supported type for rand')
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
       If VSIPL enumerated types are used one must first import the type from the VSIPL library.
    """
    fftTypes = ['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', 'ccfftip_d', 
                'ccfftop_d', 'rcfftop_d', 'crfftop_d', 'ccfftmip_f', 'ccfftmop_f', 
                'rcfftmop_f', 'crfftmop_f', 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', 
                 'crfftmop_d']
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
                   'rcfftmop_f':'mview_fcmview_f'}
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
    fftFuncDict={'cvview_d':'vsip_ccfftip_d(self.fft,l[0].view)',
                 'cvview_f':'vsip_ccfftip_f(self.fft,l[0].view)',
                 'cvview_dcvview_d':'vsip_ccfftop_d(self.fft,l[0].view,l[1].view)',
                 'cvview_fcvview_f':'vsip_ccfftop_f(self.fft,l[0].view,l[1].view)',
                 'vview_dcvview_d':'vsip_rcfftop_d(self.fft,l[0].view,l[1].view)',
                 'vview_fcvview_f':'vsip_rcfftop_f(self.fft,l[0].view,l[1].view)',
                 'cvview_dvview_d':'vsip_crfftop_d(self.fft,l[0].view,l[1].view)',
                 'cvview_fvview_f':'vsip_crfftop_f(self.fft,l[0].view,l[1].view)',
                 'cmview_d':'vsip_ccfftmip_d(self.fft,l[0].view)',
                 'cmview_f':'vsip_ccfftmip_f(self.fft,l[0].view)',
                 'cmview_dcmview_d':'vsip_ccfftmop_d(self.fft,l[0].view,l[1].view)',
                 'cmview_fcmview_f':'vsip_ccfftmop_f(self.fft,l[0].view,l[1].view)',
                 'mview_dcmview_d':'vsip_rcfftmop_d(self.fft,l[0].view,l[1].view)',
                 'mview_fcmview_f':'vsip_rcfftmop_f(self.fft,l[0].view,l[1].view)',
                 'cmview_dmview_d':'vsip_crfftmop_d(self.fft,l[0].view,l[1].view)',
                 'cmview_fmview_f':'vsip_crfftmop_f(self.fft,l[0].view,l[1].view)'}             
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
        """This method requires a single view or two views enclosed in a tuple.
           Input success depends upon How the FFT object was created.
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
    def fft(self):
        return self.__fft
    @property
    def type(self):
        return self.__type
    @property
    def arg(self):
        return self.__arg
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
    def lud(self):
        return self.__lu
    def decompose(self,m):
        tMatrix={'cmview_d':'clu_d','cmview_f':'clu_f','mview_d':'lu_d','mview_f':'lu_f'}
        luDecompose={'lu_f':vsip_lud_f,
                'lu_d':vsip_lud_d,
                'clu_f':vsip_clud_f,
                'clu_d':vsip_clud_d}
        chk = (m.type in LU.supported) 
        if chk:
            chk = (m.rowlength == m.collength) and (self.size == m.rowlength) \
                   and self.type == tMatrix[m.type]
        if chk:
            luDecompose[self.type](self.lud,m.view)
            self.__m['matrix'] = m
            return self
        else:
            print('Matrix must be square and compliant with calling object')
            return
    def solve(self,opM,XB):
        luSol={'lu_d':vsip_lusol_d,'lu_f':vsip_lusol_f,\
               'clu_d':vsip_clusol_d,'clu_f':vsip_clusol_f}
        if (XB.type in LU.supported) and (XB.collength == self.size):
            if self.__m['matrix'] == 0:
                print('LU object has no matrix associated with it')
                return
            else:
                luSol[self.type](self.lud,opM,XB.view)
                return XB
        else:
            print('Input matrix must be conformant with lu')
            return
class QR(object):
    """ qOpt is VSIP_QRD_NOSAVEQ => 0 (No Q)
                VSIP_QRD_SAVEQ => 1  (Full Q)
                VSIP_QRD_SAQVEQ1 =>2 (skinny Q)
        opR, opQ
                VSIP_MAT_NTRANS => 0,
                VSIP_MAT_TRANS => 1,
                VSIP_MAT_HERM => 2,
        opSide
                VSIP_MAT_LSIDE => 0, 
                VSIP_MAT_RSIDE => 1
        qrProb
                VSIP_COV => 0,
                VSIP_LLS => 1
   """
    tQr=['qr_f','qr_d','cqr_f','cqr_d']
    qrSel={'mview_f':'qr_f','mview_d':'qr_d','cmview_f':'cqr_f','cmview_d':'cqr_d'}
    supported=['cmview_d','cmview_f','mview_d','mview_f']
    def __init__(self,t,m,n,qOpt):
        qrCreate={'cqr_f':vsip_cqrd_create_f,
              'cqr_d':vsip_cqrd_create_d,
              'qr_f':vsip_qrd_create_f,
              'qr_d':vsip_qrd_create_d}
        self.__jvsip = JVSIP()
        if t in QR.tQr:
            self.__type = t
        else:
            print('Type qr not found')
            return
        self.__qOpt = qOpt
        self.__collength = m
        self.__rowlength = n
        self.__m = {'matrix':0}
        if qrCreate.has_key(t) and (m > 0 and isinstance(m,int)) \
                               and (n > 0 and isinstance(n,int)) \
                               and (qOpt >= 0) and (qOpt <= 2) and isinstance(qOpt,int):
            self.__qr = qrCreate[t](m,n,qOpt)
        else:
            print('Type must be one of '+repr(tQr)+' and m,n must be integers greater than 0.')
            print('qOpt must be a valid member of vsip_qrd_qopt.')
            return
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
        return (self.__collength,self.__rowlength,self.__qOpt)
    @property
    def qrd(self):
        return self.__qr
    def decompose(self,m):
        tMatrix={'cmview_d':'cqr_d','cmview_f':'cqr_f','mview_d':'qr_d','mview_f':'qr_f'}
        qrDecompose={'qr_f':vsip_qrd_f,
                'qr_d':vsip_qrd_d,
                'cqr_f':vsip_cqrd_f,
                'cqr_d':vsip_cqrd_d}
        if tMatrix[m.type] in self.type :
            qrDecompose[self.type](self.qrd,m.view)
            self.__m['matrix'] = m
            return self
        else:
            print('View type <:' +m.type+':> not supported by qr object of type <:' \
                   + self.type +':>')
            return
    def prodQ(self,opQ,opSide,X):
        qrProd={'qr_d':vsip_qrdprodq_d,'qr_f':vsip_qrdprodq_f, \
               'cqr_d':vsip_cqrdprodq_d,'cqr_f':vsip_cqrdprodq_f}
        if QR.qrSel[X.type] in self.type:
            qrProd[self.type](self.qrd,opQ,opSide,X.view)
            return X
        else:
            print('QR Type not compatible with input')
            return
    def solveR(self,opR,alpha,XB):
        qrSol={'qr_d':vsip_qrsolr_d,'qr_f':vsip_qrsolr_f,\
               'cqr_d':vsip_cqrsolr_d,'cqr_f':vsip_cqrsolr_f}
        if (QR.qrSel[XB.type] in self.type) and qrSol.has_key(self.type) and \
           (opR >= 0 and opR <= 2) and isinstance(opR,int):
            if self.__m['matrix'] == 0:
                print('QR object has no matrix associated with it')
                return
            else:
                qrSol[self.type](self.qrd,opR,alpha,XB.view)
                return XB
        else:
            print('Input arguments must be conformant with qrsolr')
            return
    def solve(self,qrProb,XB):
        qrSol={'qr_d':vsip_qrsol_d,'qr_f':vsip_qrsol_f,\
               'cqr_d':vsip_cqrsol_d,'cqr_f':vsip_cqrsol_f}
        if (QR.qrSel[XB.type] in self.type) and qrSol.has_key(self.type) and \
           (opR >= 0 and opR <= 2) and isinstance(opR,int):
            if self.__m['matrix'] == 0:
                print('QR object has no matrix associated with it')
                return
            else:
                qrSol[self.type](self.qrd,qrProf,XB.view)
                return XB
        else:
            print('Input arguments must be conformant with qrsol')
            return
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
    For instance if singular values of matrix A are required then you could do
    sv=SV(A.type,A.collength,A.rowlength,'NOS','NOS')
    """
    tSv=['sv_f','sv_d','csv_f','csv_d','mview_d','cmview_d','mview_f','cmview_f']
    svSel={'sv_f':'mview_f','sv_d':'mview_d','csv_f':'cmview_f','csv_d':'cmview_d'}
    svvSel={'sv_f':'vview_f','sv_d':'vview_d','csv_f':'vview_f','csv_d':'vview_d'}
    tSel={'sv_f':'sv_f','mview_f':'sv_f','sv_d':'sv_d','mview_d':'sv_d',
          'csv_f':'csv_f','cmview_f':'csv_f','csv_d':'csv_d','cmview_d':'csv_d'}
    def __init__(self,t,m,n,opU,opV):
        svCreate={'sv_f':vsip_svd_create_f,
              'sv_d':vsip_svd_create_d,
              'csv_f':vsip_csvd_create_f,
              'csv_d':vsip_csvd_create_d}
        op={'NOS':VSIP_SVD_UVNOS,'FULL':VSIP_SVD_UVFULL,'PART':VSIP_SVD_UVPART}
        self.__jvsip = JVSIP()
        if t in SV.tSv:
            self.__type = SV.tSel[t]
        else:
            printf('type <:' + t + ':>not found for SVD')
            return
        self.opU=opU
        self.opV=opV
        self.m=m
        self.n=n
        self.__sv=svCreate[SV.tSel[t]](m,n,op[opU],op[opV])
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
        if 'NOS' in self.opV:
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
        if 'NOS' in self.opU:
            return     
        else:
            svMatU[self.type](self.vsip,low,high,other.view)
            return other
class FIR(object):
    
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
        firDestroy[self.type](self.fir)
        del(self.__jvsip)
    def flt(self,x,y):
        """
        Usage:
             fir = FIR(...)
             fir.flt(x,y)
             x is input view of data to be filtered
             y is output view of filtered data
        """
        filtSptd = {'fir_f':'vview_f','fir_d':'vview_d',
                     'cfir_f':'cvview_f','cfir_d':'cvview_d',
                     'rcfir_f':'cvview_f','rcfir_d':'cvview_d'}
        firflt = {'fir_f':vsip_firflt_f,'fir_d':vsip_firflt_d,
                  'cfir_f':vsip_cfirflt_f,'cfir_d':vsip_cfirflt_d,
                  'rcfir_f':vsip_rcfirflt_f,'rcfir_d':vsip_rcfirflt_d} 
        assert x.type == y.type
        assert filtSptd[self.type] == x.type
        firflt[self.type](self.fir,x.view,y.view)
        return y
    def reset(self):
        fir_reset = {'fir_f':vsip_fir_reset_f,'fir_d':vsip_fir_reset_d,
                  'cfir_f':vsip_cfir_reset_f,'cfir_d':vsip_cfir_reset_d,
                  'rcfir_f':vsip_rcfir_reset_f,'rcfir_d':vsip_rcfir_reset_d} 
        if self.state:
            fir_reset[self.type](self.fir)
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
    def fir(self):
        return self.__fir
    @property
    def length(self):
        return self.__length
    @property
    def decimation(self):
        return self.__decimation
    
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
# Functions
# copy is kind of brain dead. Need more functionality and performance
def copy(input,to):
    """
    Usage:
        for A => list or view and  B=> view
        copy(A,B) will copy the data from A into B
    The copy function allows one to copy data from a list into a VSIP vector or matrix view.
    If the list is 2D the list is copied as row major into a matrix.
    If the list is 1D it is copied into a vector.
    I would not call this function efficient or robust; just handy.
    Note if both input and output are views then a standard VSIP copy takes place.
    The views must be compliant.
    """
    if isinstance(input,list):
        if 'vview' in to.type and (len(input) == to.length):
            for i in range(to.length):
               to[i] = input[i]
        elif 'mview' in to.type and \
                     (len(input) == to.collength) and (len(input[0]) == to.rowlength):
            for i in range(to.collength):
                for j in range(to.rowlength):
                    to[i,j] = input[i][j]
        else: 
            print('Error in copy list to type <:'+to.type+':>.')
            return
    else:
        vsip.copy(input.view,to.view)
    return to
def create(atype,*vals):
    """
       usage:
          anObject=create(aType,...)
       where:
          aType corresponds to a valid type for the object being created and
          ... are a variable argument list associated with each supported create type
    """
    blockTypes = ['cblock_f','cblock_d','block_f','block_d','block_i','block_si','block_uc', \
                  'block_vi','block_mi','block_bl']
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
    fftTypes = ['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', 'ccfftip_d', \
                'ccfftop_d', 'rcfftop_d', 'crfftop_d', 'ccfftmip_f', 'ccfftmop_f', \
                'rcfftmop_f', 'crfftmop_f', 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', \
                'crfftmop_d']
    mfftTypes = ['ccfftmip_f', 'ccfftmop_f', 'rcfftmop_f', 'crfftmop_f', \
                 'ccfftmip_d', 'ccfftmop_d', 'rcfftmop_d', 'crfftmop_d']
    vfftTypes=['ccfftip_f', 'ccfftop_f', 'rcfftop_f', 'crfftop_f', \
               'ccfftip_d', 'ccfftop_d', 'rcfftop_d', 'crfftop_d']
    if atype in blockTypes:
        if isinstance(vals[0],int) and len(vals) == 1:
            return Block(atype,vals[0])
        else:
            print('Input length for <:' + atype + 'must be a single integer value')
            return
    elif atype in vectorTypes:
        if isinstance(vals[0],int) and len(vals) == 1:
            return create(fVector[atype],vals[0]).bind(0,1,vals[0])
        else:
            print('Input length for <:' + atype + ':> must be a single integer value')
            return
    elif atype in matrixTypes:
        if len(vals) >1 and isinstance(vals[0],int) and isinstance(vals[1],int):
            cl=vals[0]
            rl= vals[1]
            l=rl * cl;
            offset=0;
            if (len(vals) == 3 and 'ROW' in vals[2]) or len(vals) == 2:
                row_stride=1
                col_stride=rl
            elif len(vals) == 3 and 'COL' in vals[2]:
                row_stride=cl
                col_stride=1
            else:
                print('Input arguments for <:'+atype+':> must be (integers):')
                print('\tcolumn length, row length,\n and optional major:')
                print("\t'ROW' (default) or 'COL'")
                return
            return create(fMatrix[atype],l).bind(offset,col_stride,cl,row_stride,rl)
        else:
            print('Input arguments for <:'+atype+':> must be 2 (integers) and an optional major:')
            print('\tcolumn length, row length,\n and optional major:')
            print("\t'ROW' (default) or 'COL'")
            return
    elif atype in fftTypes:
        nVals = len(vals)
        hint = 0 # set to VSIP_ALG_TIME
        ntimes = 0 # set to use a lot
        if (atype in vfftTypes and nVals < 1) or (atype in mfftTypes and nVals < 2):
            print('Usage requires a single length for vectors or the column and row length for matrices')
            print('For vectors (matrices) the second (third) argument is a scalar indicating')
            print('a scale. This value defaults to 1.0')
            print('The argument list is searched for the string "INV" and if found the')
            print('object is built for an inverse FFT. The default is a Forward FFT')
            print('If a multiple FFT is specified the argument list is searched for a string')
            print('of "COL". If found the fft is done for each column. The default is by row')
            return
        else:
            if 'INV' in vals:
                dir = 1 #VSIP_FFT_INV
            else:
                dir = -1 #VSIP_FFT_FWD
            if atype in mfftTypes and nVals > 1:
                M = vals[0]
                N = vals[1]
                if nVals > 2 and (isinstance(vals[2,int]) or isinstance(vals[2],float)):
                    scaleFactor = vals[2] 
                else:
                    scaleFactor = 1.0   
                if 'COL' in vals:
                    major = 1 #'VSIP_COL'
                else:
                    major = 0 #'VSIP_ROW'
            elif atype in vfftTypes and nVals > 0:
                N = vals[0]
                if nVals > 1 and (isinstance(vals[1],int) or isinstance(vals[1],float)):
                    scaleFactor = vals[1]
                else:
                    scaleFactor = 1.0
            else:
                print('<:' + atype + ':> not recognized') #should not be able to get here
                return
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
    else:
        print('Input argument <:'+atype+':> not recognzied for create')
