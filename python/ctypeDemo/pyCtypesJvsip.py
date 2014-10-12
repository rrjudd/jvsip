import ctypes
lib=ctypes.CDLL("./_vsip.so")

# Memory hints are only supported at the interface for C JVSIP. Here I don't expose them to the user interface.
memory_hint = {
    "VSIP_MEM_NONE":ctypes.c_int(0),
    "VSIP_MEM_RDONLY":ctypes.c_int(1),
    "VSIP_MEM_CONST":ctypes.c_int(2),
    "VSIP_MEM_SHARED":ctypes.c_int(3),
    "VSIP_MEM_SHARED_RDONLY":ctypes.c_int(4),
    "VSIP_MEM_SHARED_CONST":ctypes.c_int(5)}

class vattr(ctypes.Structure):
   _fields_=[
             ('offset',ctypes.c_ulong),
             ('stride',ctypes.c_long),
             ('length',ctypes.c_ulong),
             ('block', ctypes.c_void_p)
             ]
class cmplx(ctypes.Structure):
    _fields_=[('r',ctypes.c_float),('i',ctypes.c_float)]

def vsipInit():
    lib.vsip_init.restype=ctypes.c_int
    return lib.vsip_init(ctypes.c_void_p(0))
def vsipFinalize():
    lib.vsip_finalize.restype=ctypes.c_int
    return lib.vsip_finalize(ctypes.c_void_p(0))
class JVSIP (object):
    jinit = 0
    def __init__(self):
        if JVSIP.jinit:
            self.vsipInit=0;
            JVSIP.jinit +=1;
        else:
            self.vsipInit = vsipInit()
            assert self.vsipInit == 0,'VSIP failed to initialize'
            JVSIP.jinit = 1;

    def __del__(self):
        JVSIP.jinit -= 1
        if JVSIP.jinit == 0:
            vsipFinalize()
def _tType(a):
    if isinstance(a,complex):
        return 'cscalar'
    elif isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        return 'scalar'
    elif 'View' in repr(a):
        return a.type
    else:
        return repr(a)
def _nlength(b,e,s): #begin(start),end(stop),step(step)=>b,e,s; Slice Length
    d=int(e)-int(b)
    chk=d%int(s)
    if chk is 0:
        return d//int(s)
    else:
        return (d//int(s)) + 1
def _blockcreate(t,l):
    assert isinstance(l,int),'Length parameter to blockcreate is an integer'
    assert isinstance(t,str),'Type parameter to blockcreate ia a string'
    f={'block_f':lib.vsip_blockcreate_f,'cblock_f':lib.vsip_cblockcreate_f,
       'block_i':lib.vsip_blockcreate_i,'block_vi':lib.vsip_blockcreate_vi}
    assert f.has_key(t),'Block type string <:%s:> not recognized'%t
    f[t].restype=ctypes.c_void_p
    return f[t](ctypes.c_ulong(l),memory_hint["VSIP_MEM_NONE"])
def _blockdestroy(t,aVsipBlock):
    assert isinstance(t,str),'Type parameter to blockdestroy is a string'
    f={'block_f':lib.vsip_blockdestroy_f,'cblock_f':lib.vsip_cblockdestroy_f,
       'block_i':lib.vsip_blockdestroy_i,'block_vi':lib.vsip_blockdestroy_vi}
    assert f.has_key(t),'Block type string <:%s:> not recognized'%t
    f[t](ctypes.c_void_p(aVsipBlock))
def _bind(t,block,offset,stride,length):
    def vbind_f(block,offset,stride,length):
        lib.vsip_vbind_f.restype=ctypes.c_void_p
        return lib.vsip_vbind_f(ctypes.c_void_p(block),ctypes.c_ulong(offset),ctypes.c_long(stride),ctypes.c_ulong(length))
    def cvbind_f(block,offset,stride,length):
        lib.vsip_vbind_f.restype=ctypes.c_void_p
        return lib.vsip_vbind_f(ctypes.c_void_p(block),ctypes.c_ulong(offset),ctypes.c_long(stride),ctypes.c_ulong(length))
    def vbind_i(block,offset,stride,length):
        lib.vsip_vbind_f.restype=ctypes.c_void_p
        return lib.vsip_vbind_f(ctypes.c_void_p(block),ctypes.c_ulong(offset),ctypes.c_long(stride),ctypes.c_ulong(length))
    def vbind_vi(block,offset,stride,length):
        lib.vsip_vbind_f.restype=ctypes.c_void_p
        return lib.vsip_vbind_f(ctypes.c_void_p(block),ctypes.c_ulong(offset),ctypes.c_long(stride),ctypes.c_ulong(length))
    f={'vview_f':vbind_f,'cvview_f':cvbind_f,'vview_i':vbind_i,'vview_vi':vbind_vi}
    assert f.has_key(t),'Type <:%s:> not found for bind.'%t
    return f[t](block,offset,stride,length)
def _viewDestroy(t,aVSipView):
    assert isinstance(t,str),'Type parameter to viewDestroy must be a string'
    f={'vview_f':lib.vsip_vdestroy_f,'cvview_f':lib.vsip_cvdestroy_f,
       'vview_i':lib.vsip_vdestroy_i,'vview_vi':lib.vsip_vdestroy_vi}
    assert f.has_key(t),'Type paramter <:%s:> not recognized for viewDestroy.'%t
    f[t].restype = ctypes.c_void_p
    f[t](ctypes.c_void_p(aVSipView))
def _getattrib(view):
    f={'vview_f':lib.vsip_vgetattrib_f,'cvview_f':lib.vsip_cvgetattrib_f,\
         'vview_i':lib.vsip_vgetattrib_i,'vview_vi':lib.vsip_vgetattrib_vi}
    attr=vattr(0,0,0,0)
    f[view.type](ctypes.c_void_p(view.vsip),ctypes.pointer(attr))
    return attr
def _putattrib(view,attr):
    f={'vview_f':lib.vsip_vputattrib_f,'cvview_f':lib.vsip_cvputattrib_f,
       'vview_i':lib.vsip_vputattrib_i,'vview_vi':lib.vsip_vputattrib_vi}
    f[view.type](ctypes.c_void_p(view.vsip),ctypes.pointer(attr))
def _get(view,index):
    def vget_f(view,index):
        lib.vsip_vget_f.restype = ctypes.c_float
        return lib.vsip_vget_f(ctypes.c_void_p(view.vsip),ctypes.c_ulong(index))
    def cvget_f(view,index):
        r = view.realview.get(index)
        i = view.imagview.get(index)
        return complex(r,i)
    def vget_i(view,index):
        lib.vsip_vget_i.restype = ctypes.c_int
        return lib.vsip_vget_i(ctypes.c_void_p(view.vsip),ctypes.c_ulong(index))
    def vget_vi(view,index):
        lib.vsip_vget_vi.restype = ctypes.c_ulong
        return lib.vsip_vget_vi(ctypes.c_void_p(view.vsip),ctypes.c_ulong(index))
    f={'vview_f':vget_f,'cvview_f':cvget_f,'vview_i':vget_i,'vview_vi':vget_vi}
    return f[view.type](view,index)
def _put(view,index,val):
    def vput_f(view,index,val):
        lib.vsip_vput_f(ctypes.c_void_p(view.vsip),ctypes.c_ulong(index),ctypes.c_float(val))
    def cvput_f(view,index,val):
        view.realview.put(index,val.real)
        view.imagview.put(index,val.imag)
    def vput_i(view,index,val):
        lib.vsip_vput_i(ctypes.c_void_p(view.vsip),ctypes.c_ulong(index),ctypes.c_int(val))
    def vput_vi(view,index,val):
        lib.vsip_vput_vi(ctypes.c_void_p(view.vsip),ctypes.c_ulong(index),ctypes.c_ulong(val))
    f={'vview_f':vput_f,'cvview_f':cvput_f,'vview_i':vput_i,'vview_vi':vput_vi}
    f[view.type](view,index,val)
def _realview(view):
    lib.vsip_vrealview_f.restype=ctypes.c_void_p
    return lib.vsip_vrealview_f(ctypes.c_void_p(view))
def _imagview(view):
    lib.vsip_vimagview_f.restype=ctypes.c_void_p
    return lib.vsip_vimagview_f(ctypes.c_void_p(view))
def _fill(view,val):
    def vfill_f(alpha,view):
        lib.vsip_vfill_f(ctypes.c_float(alpha),ctypes.c_void_p(view))
    def vfill_i(alpha,view):
        lib.vsip_vfill_i(ctypes.c_int(alpha),ctypes.c_void_p(view))
    def vfill_vi(alpha,view):
        lib.vsip_vfill_vi(ctypes.c_ulong(alpha),ctypes.c_void(view))
    f={'vview_f':vfill_f,'vview_i':vfill_i,'vview_vi':vfill_vi}
    f[view.type](val,view.vsip)
def _add(a,b,c):
    """
    The add function includes view+view adds and scalar+view adds.
    """
    def vadd_f(a,b,c):
        lib.vsip_vadd_f(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def svadd_f(a,b,c):
        lib.vsip_svadd_f(ctypes.c_float(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def vadd_i(a,b,c):
        lib.vsip_vadd_i(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def svadd_i(a,b,c):
        lib.vsip_svadd_i(ctypes.c_int(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def vadd_vi(a,b,c):
        lib.vsip_vadd_vi(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def svadd_vi(a,b,c):
        lib.vsip_svadd_vi(ctypes.c_ulong(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def cvadd_f(a,b,c):
        lib.vsip_cvadd_f(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def rscvadd_f(a,b,c):
        svadd_f(a,b.realview,c.realview)
    def csvadd_f(a,b,c):
        svadd_f(a.real,b.realview,c.realview)
        svadd_f(a.imag,b.imagview,c.imagview) 
    f={'vview_fvview_fvview_f':vadd_f,'vview_ivview_ivview_i':vadd_i,
       'vview_vivview_vivview_vi':vadd_vi, 'scalarvview_fvview_f':svadd_f,
       'scalarvview_ivview_i':svadd_i, 'scalarcvview_fcvview_f':rscvadd_f, 
       'scalarvview_vivview_vi':svadd_vi,'cscalarcvview_fcvview_f':csvadd_f}
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t='scalar'+b.type+c.type
    elif isinstance(a,complex):
        t='cscalar'+b.type+c.type
    else:
        t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:%s:> not recognized for add'%t
    f[t](a,b,c)
    return c
def _sub(a,b,c):
    f={ 'cvview_fvview_fcvview_f':lib.vsip_crvsub_f,
        'cscalarcvview_fcvview_f':lib.vsip_csvsub_f,
        'cvview_fcvview_fcvview_f':lib.vsip_cvsub_f,
        'vview_fcvview_fcvview_f':lib.vsip_rcvsub_f,
        'scalarcvview_fcvview_f':lib.vsip_rscvsub_f,
        'scalarvview_fvview_f':lib.vsip_svsub_f,
        'vview_fvview_fvview_f':lib.vsip_vsub_f, 
        'scalarvview_ivview_i':lib.vsip_svsub_i,
        'vview_ivview_ivview_i':lib.vsip_vsub_i,
        'scalarvview_vivview_vi':lib.vsip_svsub_vi}
    t=_tType(a)+_tType(b)+_tType(c)
    assert f.has_key(t), 'Type <:%s:> not recognized for sub'%t
    if 'cscalar' in t:
        _sub(a.real,b.realview,c.realview)
        _sub(a.imag,b.imagview,c.imagview)
    elif 'scalar' in t:
        if '_f' in t:
            f[t](ctypes.c_float(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
        else:
            f[t](ctypes.c_int(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    else:
        f[t](ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    return c
def _mul(a,b,c):
    """
    The mul function includes view+view muls and scalar+view muls.
    """
    def csvmul_f(a,b,c):
        t=c.empty
        rscvmul_f(a.r,b,t)
        svmul_f( a.i,b.realview,c.imagview)
        svmul_f(-a.i,b.imagview,c.realview)
        c+=t
    def cvmul_f(a,b,c):
        lib.vsip_cvmul_f(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def rcvmul_f(a,b,c):
        lib.vsip_rcvmul_f(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def rscvmul_f(a,b,c):
        lib.vsip_rscvmul_f(ctypes.float(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def svmul_f(a,b,c):
        lib.vsip_svmul_f(ctypes.c_float(a),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def vmul_f(a,b,c):
        lib.vsip_vmul_f(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    def vmul_i(a,b,c):
        lib.vsip_vmul_i(ctypes.c_void_p(a.vsip),ctypes.c_void_p(b.vsip),ctypes.c_void_p(c.vsip))
    f={ 'cscalarcvview_fcvview_f':csvmul_f,'cvview_fcvview_fcvview_f':cvmul_f,
        'vview_fcvview_fcvview_f':rcvmul_f,'scalarcvview_fcvview_f':rscvmul_f,
        'scalarvview_fvview_f':svmul_f,'vview_fvview_fvview_f':vmul_f, 'vview_ivview_ivview_i':vmul_i}
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t='scalar'+b.type+c.type
    elif isinstance(a,complex):
        t='cscalar'+b.type+c.type
    else:
        t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:%s:> not recognized for mul'%t
    f[t](a,b,c)
    return c
class Block (object):
    tBlock = ['block_f','cblock_f','block_vi','block_i']
    derivedTypes = ['real_f','imag_f']
    vectorTypes=['vview_f','cvview_f','vview_i','vview_vi']
    windowTypes=['blackman_f','cheby_f','kaiser_f','hanning_f']
    complexTypes=['cvview_f']
    blkSel={'vview_f':'block_f','vview_d':'block_d','cvview_f':'cblock_f',\
            'cvview_d':'cblock_d', 'vview_si':'block_si','vview_i':'block_i',\
            'vview_uc':'block_uc', 'vview_mi':'block_mi', 'vview_vi':'block_vi',\
            'vview_bl':'block_bl','mview_f':'block_f','mview_d':'block_d',\
            'cmview_f':'cblock_f','cmview_d':'cblock_d','mview_si':'block_si',\
            'mview_i':'block_i','mview_uc':'block_uc','mview_bl':'block_bl'}
    #Block specific class below
    def __init__(self,block_type,*args):
        other = Block.derivedTypes
        assert isinstance(block_type,str),'The type argument should be a string'
        keyError='Block type <:%s:> not support by Block class'%block_type
        assert block_type in Block.tBlock or block_type in other or block_type in Block.windowTypes,'Block type not recognized'
        self.__jvsip = JVSIP()
        if block_type in Block.tBlock: #Regular block constructor
            self.__vsipBlock = _blockcreate(block_type,int(args[0]))
            self.__length = int(args[0])
            self.__type = block_type
        elif block_type in other: #Derived block constructor for real, imag views
            self.__vsipBlock = args[0]
            self.__length = int(args[1])
            self.__type = block_type
        else: #must be window
            assert block_type in Block.windowTypes,'Should not be here. Block type not a window type'
            # window functions selector
            f={'blackman_d':'vsip_vcreate_blackman_d(args[0],0)',\
               'blackman_f':'vsip_vcreate_blackman_f(args[0],0)',\
               'cheby_d':'vsip_vcreate_cheby_d(args[0],args[1],0)',\
               'cheby_f':'vsip_vcreate_cheby_f(args[0],args[1],0)',\
                'kaiser_d':'vsip_vcreate_kaiser_d(args[0],args[1],0)',\
                'kaiser_f':'vsip_vcreate_kaiser_f(args[0],args[1],0)',\
                'hanning_d':'vsip_vcreate_hanning_d(args[0],0)',\
                'hanning_f':'vsip_vcreate_hanning_f(args[0],0)'}
            # block type selector
            bt={'blackman_d':'block_d','blackman_f':'block_f','cheby_d':'block_d',\
               'cheby_f':'block_f','kaiser_d':'block_d','kaiser_f':'block_f',\
                'hanning_d':'block_d','hanning_f':'block_f'}
            # get block selector
            gb={'block_d':vsip_vgetblock_d,'block_f':vsip_vgetblock_f}
            v=eval(f[block_type]) # create vsip window vector
            b=bt[block_type] # get block type for window created
            blk = gb[b](v) # get pointer to vectors C VSIPL block
            # construct pyJvsip block
            self.__vsipBlock=blk
            self.__type=b
            self.__length=args[0]
            self.w = self.__View(v,self) #create a pyJvsip view object with window in it.
    def __del__(self):
        t = self.__type
        if t in Block.tBlock:
            _blockdestroy(t,self.vsip)
        del(self.__jvsip)
    @classmethod
    def otherBlock(cls,blk,arg):
        """
        This method is used internal to the pyCtypesJvsip module.
        It is not intended to be used in user code.
        otherBlock creates a new block of type blk (or the proper type if blk is derived).
        """
        #bSel is a block selector to select the proper type block if the input type is derived
        bSel={'imag_f':'block_f','real_f':'block_f'}
        if isinstance(arg,tuple):#create derived block
            return cls(blk,arg[0],arg[1])
        elif bSel.has_key(blk):#create new block starting with derived block
            return cls(bSel[blk],arg)
        else:#create new block
            return cls(blk,arg)
    @property
    def vsip(self):
        return self.__vsipBlock
    @property
    def type(self):
        return self.__type
    @property
    def length(self):
        return self.__length
    def __len__(self):
        return self.length
    @property
    def vector(self):
        return self.bind(0,1,self.length)
    def bind(self,*args): # big rewrite to support matrix
        f={ 'block_fvector':'vview_f',
            'cblock_fvector':'cvview_f',
            'block_ivector':'vview_i',
            'block_vivector':'vview_vi'}
        assert len(args) == 3,'Only vector views are supported for pyCtypesJvsip demo'
        t = self.type+'vector'
        assert f.has_key(t),'Block bind method has no type <:%s:>.'%t
        viewType=f[t]
        offset = int(args[0]);stride=int(args[1]);length=int(args[2])
        assert self.length > offset + stride*(length-1),'View exceeds block size'
        vsipView = _bind(viewType,self.vsip,offset,stride,length)
        return self.__View(viewType,vsipView,self)
    class __View(object):
        tView=['vview_f','cvview_f','vview_i','vview_vi']
        def __init__(self,viewType,vsipView,block):
            self.__jvsip = JVSIP()
            self.__vsipView = vsipView
            self.__pyBlock  = block
            self.__type     = viewType
            self.__parent = 0
        def __del__(self):
            t=self.type
            _viewDestroy(t,self.vsip)
            del(self.__jvsip)
        @classmethod
        def __realview(cls,V):
            db={'cvview_f':'real_f'}
            rv={'cvview_f': _realview}
            assert db.has_key(V.type),'View of type <:%s:> not supported for realview.'%V.type
            t=db[V.type] #type of derived block
            v=rv[V.type](V.vsip) #get real vsip view
            attr=vattr(0,0,0,0)
            lib.vsip_vgetattrib_f(ctypes.c_void_p(v),ctypes.pointer(attr))
            b=attr.block
            B=V.block
            l=B.length
            newB = B.otherBlock(t,(b,l))# create new pyJvsip derived block
            return cls('vview_f',v,newB)#create new pyJvsip real view with associated derived block
        @classmethod
        def __imagview(cls,V):
            db={'cvview_f':'imag_f'}
            rv={'cvview_f': _imagview}
            assert db.has_key(V.type),'View of type <:%s:> not supported for imagview.'%V.type
            t=db[V.type] #type of derived block
            v=rv[V.type](V.vsip) #get real vsip view
            attr=vattr(0,0,0,0)
            lib.vsip_vgetattrib_f(ctypes.c_void_p(v),ctypes.pointer(attr))
            b=attr.block
            B=V.block
            l=B.length
            newB = B.otherBlock(t,(b,l))# create new pyJvsip derived block
            return cls('vview_f',v,newB)#create new pyJvsip real view with associated derived block
        @classmethod
        def __newView(cls,t,v,b):
            return cls(t,v,b)
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
        def block(self): return self.__pyBlock
        @property
        def type(self): return self.__type
        @property
        def vsip(self): return self.__vsipView
        @property
        def length(self):
            return self.attrib.length
        def __len__(self):
            return self.length
        @property
        def offset(self):
            return self.attrib.offset
        @property
        def stride(self):
            return self.attrib.stride
        def putlength(self,length):
            attr=self.attrib
            attr.length = length
            self.putattrib(self,attr)
        def putoffset(self,offset):
            attr=self.attrib
            attr.length = length
            self.putattrib(self,attr)
        def putstride(self,stride):
            attr=self.attrib
            attr.stride = stride
            self.putattrib(self,attr)
        @property
        def attrib(self):
            return _getattrib(self)
        def putattrib(self,attr):
            _putattrib(self,attr)
            return self
        def get(self,indx):
            return _get(self,indx)
        def put(self,indx,val):
            _put(self,indx,val)
            return self
        def fill(self,val):
            if 'cvview_f' in self.type:
                r=self.realview;i=self.imagview
                _fill(self.realview,val.real)
                _fill(self.imagview,val.imag)
            else:
                _fill(self,val)
            return self
        @property
        def empty(self):            
            tSel= {'block_f':'block_f','cblock_f':'cblock_f','block_i':'block_i',\
                   'block_vi':'block_vi','imag_f':'block_f','real_f':'block_f'}
            return Block(tSel[self.block.type],self.length).vector
        def ramp(self,start,increment):
            def vramp_f(start,step,view):
                lib.vsip_vramp_f(ctypes.c_float(start),ctypes.c_float(step),ctypes.c_void_p(view.vsip))
            def cvramp_f(start,step,view):
                view.imagview.fill(0.0)
                view.realview.ramp(start,step)
            def vramp_i(start,step,view):
                lib.vsip_vramp_i(ctypes.c_int(start),ctypes.c_int(step),ctypes.c_void_p(view.vsip))
            def vramp_vi(start,step,view):
                lib.vsip_vramp_vi(ctypes.c_ulong(start),ctypes.c_ulong(step),ctypes.c_void_p(view.vsip))
            f={'vview_f':vramp_f,
               'cvview_f':cvramp_f,
               'vview_i':vramp_i,
               'vview_vi':vramp_vi}
            assert f.has_key(self.type)
            extended = ['cvview_f']
            t=self.type
            assert f.has_key(t),'Type <:%s:> not support for ramp'%self.type
            f[t](start,increment,self)
            return self
        @property
        def cloneview(self):
            f={'vview_f':lib.vsip_vcloneview_f,
               'cvview_f':lib.vsip_cvcloneview_f,
               'vview_i':lib.vsip_vcloneview_i,
               'vview_vi':lib.vsip_vcloneview_vi}
            f[self.type].restype=ctypes.c_void_p
            v = f[self.type](ctypes.c_void_p(self.vsip))
            b=self.block
            return self.__newView(self.type,v,b)
        def __getitem__(self,index):
            assert isinstance(index,int) or isinstance(index,long) or isinstance(index,slice),\
                'Parameter must be a slice or an integer index for __getitem__'
            if isinstance(index,slice):
                v=self.cloneview
                attr=v.attrib
                b=index.start
                e=index.stop
                s=index.step
                if e > attr.length: e = attr.length
                if b == None: b=0
                if e == None: e=attr.length
                if s == None: s=1
                assert b >=0 and e >= 0 and s >= 0 and e >= b,'Only positive slice values are supported for pyCtypesJvsip __getitem__'
                attr.length = _nlength(b,e,s)
                attr.offset += b * attr.stride
                attr.stride *= s
                assert (attr.length -1) * attr.stride + attr.offset < self.block.length, 'Implementation Error. View exceeds Block. Should not be here'
                v.putattrib(attr)
                return v
            else:
                return self.get(index)
        def __setitem__(self,index,val):
            assert isinstance(index,int) or isinstance(index,long),'Put item is only supported for single index at this time'
            self.put(index,val)
            return self
        def __iadd__(self,other): # self += other
            return _add(other,self,self)
        def __add__(self,other): # new = self + other
            return _add(other,self,self.empty)
        def __radd__(self,other): # new = other + self
            return _add(other,self,self.empty)
        def __imul__(self,other):# *=other
            _mul(other,self,self)
            return self
        def __mul__(self,other):
            return _mul(other,self,self.empty)
        def __rmul__(self,other): # other * self
            return _mul(other,self,self.empty)
        def __isub__(self,other): # -=other
            if '__View' in repr(other):
                _sub(self,other,self)
            else:
                _add(-other,self,self)
            return self
        def __sub__(self,other):#self - other
            retval=self.empty
            if '__View' in repr(other):
                return _sub(self,other,retval)
            else:
                return _add(-other,self,retval)
        def __rsub__(self,other): #other - self
            retval=self.empty
            return _sub(other,self,retval)
