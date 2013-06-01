#include"pyVsip.h"

PyObject *cvcopyToList_f(vsip_cvview_f *v){
    PyObject *cval;
    vsip_length N = vsip_cvgetlength_f(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       vsip_cscalar_f x = vsip_cvget_f(v,i);
       double re = (double)x.r;
       double im = (double)x.i;
       cval = PyComplex_FromDoubles(re,im);
       PyList_SetItem(retval,i,cval);
    }
    return retval;
}
PyObject *cvcopyToList_d(vsip_cvview_d *v){
    PyObject *cval;
    vsip_length N = vsip_cvgetlength_d(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       vsip_cscalar_d x = vsip_cvget_d(v,i);
       double re = (double)x.r;
       double im = (double)x.i;
       cval = PyComplex_FromDoubles(re,im);
       PyList_SetItem(retval,i,cval);
    }
    return retval;
}
PyObject *vcopyToList_f(vsip_vview_f *v){
    vsip_length N = vsip_vgetlength_f(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       double x = (double)vsip_vget_f(v,i); 
       PyList_SetItem(retval,i,PyFloat_FromDouble(x));
    }
    return retval;
}
   
PyObject *vcopyToList_d(vsip_vview_d *v){
    vsip_length N = vsip_vgetlength_d(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       double x = (double)vsip_vget_d(v,i);
       PyList_SetItem(retval,i,PyFloat_FromDouble(x));
    }
    return retval;
}
PyObject *vcopyToList_i(vsip_vview_i *v){
    vsip_length N = vsip_vgetlength_i(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       long int x = (long int)vsip_vget_i(v,i);
       PyList_SetItem(retval,i,PyInt_FromLong(x));
    }
    return retval;
}
PyObject *vcopyToList_si(vsip_vview_si *v){
    vsip_length N = vsip_vgetlength_si(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       long int x = (long int)vsip_vget_si(v,i);
       PyList_SetItem(retval,i,PyInt_FromLong(x));
    }
    return retval;
}
PyObject *vcopyToList_vi(vsip_vview_vi *v){
    vsip_length N = vsip_vgetlength_vi(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       long int x = (long int)vsip_vget_vi(v,i);
       PyList_SetItem(retval,i,PyInt_FromLong(x));
    }
    return retval;
}
PyObject *vcopyToList_uc(vsip_vview_uc *v){
    vsip_length N = vsip_vgetlength_uc(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       long int x = (long int)vsip_vget_uc(v,i);
       PyList_SetItem(retval,i,PyInt_FromLong(x));
    }
    return retval;
}
PyObject *vcopyToList_mi(vsip_vview_mi *v){
    PyObject *miVal;
    vsip_length N = vsip_vgetlength_mi(v);
    PyObject *retval = PyList_New(N);
    vsip_index i;
    for(i=0; i<N; i++){
       vsip_scalar_mi x = vsip_vget_mi(v,i);
       miVal = Py_BuildValue("(ii)",x.r,x.c);
       PyList_SetItem(retval,i,miVal);
    }
    return retval;
}
/* matrix copy by row */
PyObject *cmcopyToListByRow_f(vsip_cmview_f *v){
    PyObject *cval;
    vsip_length M = vsip_cmgetcollength_f(v);
    vsip_length N = vsip_cmgetrowlength_f(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           vsip_cscalar_f x = vsip_cmget_f(v,i,j);
           double re = (double)x.r;
           double im = (double)x.i;
           cval = PyComplex_FromDoubles(re,im);
           PyList_SetItem(row,j,cval);
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}
PyObject *mcopyToListByRow_f(vsip_mview_f *v){
    vsip_length M = vsip_mgetcollength_f(v);
    vsip_length N = vsip_mgetrowlength_f(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           double x = (double)vsip_mget_f(v,i,j);
           PyList_SetItem(row,j,PyFloat_FromDouble(x));
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}
PyObject *cmcopyToListByRow_d(vsip_cmview_d *v){
    PyObject *cval;
    vsip_length M = vsip_cmgetcollength_d(v);
    vsip_length N = vsip_cmgetrowlength_d(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           vsip_cscalar_d x = vsip_cmget_d(v,i,j);
           double re = (double)x.r;
           double im = (double)x.i;
           cval = PyComplex_FromDoubles(re,im);
           PyList_SetItem(row,j,cval);
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}

PyObject *mcopyToListByRow_d(vsip_mview_d *v){
    vsip_length M = vsip_mgetcollength_d(v);
    vsip_length N = vsip_mgetrowlength_d(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           double x = (double)vsip_mget_d(v,i,j);
           PyList_SetItem(row,j,PyFloat_FromDouble(x));
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}

PyObject *mcopyToListByRow_i(vsip_mview_i *v){
    vsip_length M = vsip_mgetcollength_i(v);
    vsip_length N = vsip_mgetrowlength_i(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           long int x = (long int)vsip_mget_i(v,i,j);
           PyList_SetItem(row,j,PyInt_FromLong(x));
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}

PyObject *mcopyToListByRow_si(vsip_mview_si *v){
    vsip_length M = vsip_mgetcollength_si(v);
    vsip_length N = vsip_mgetrowlength_si(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           long int x = (long int)vsip_mget_si(v,i,j);
           PyList_SetItem(row,j,PyInt_FromLong(x));
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}

PyObject *mcopyToListByRow_uc(vsip_mview_uc *v){
    vsip_length M = vsip_mgetcollength_uc(v);
    vsip_length N = vsip_mgetrowlength_uc(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(i=0; i<M; i++){
        PyObject *row = PyList_New(N);
        for(j=0; j<N; j++){
           long int x = (long int)vsip_mget_uc(v,i,j);
           PyList_SetItem(row,j,PyInt_FromLong(x));
        }
        PyList_SetItem(retval,i,row);
    }
    return retval;
}

/* matrix copy by col */
PyObject *cmcopyToListByCol_f(vsip_cmview_f *v){
    PyObject *cval;
    vsip_length M = vsip_cmgetcollength_f(v);
    vsip_length N = vsip_cmgetrowlength_f(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           vsip_cscalar_f x = vsip_cmget_f(v,i,j);
           double re = (double)x.r;
           double im = (double)x.i;
           cval = PyComplex_FromDoubles(re,im);
           PyList_SetItem(col,i,cval);
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}
PyObject *mcopyToListByCol_f(vsip_mview_f *v){
    vsip_length M = vsip_mgetcollength_f(v);
    vsip_length N = vsip_mgetrowlength_f(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           double x = (double)vsip_mget_f(v,i,j);
           PyList_SetItem(col,i,PyFloat_FromDouble(x));
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}
PyObject *cmcopyToListByCol_d(vsip_cmview_d *v){
    PyObject *cval;
    vsip_length M = vsip_cmgetcollength_d(v);
    vsip_length N = vsip_cmgetrowlength_d(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           vsip_cscalar_d x = vsip_cmget_d(v,i,j);
           double re = (double)x.r;
           double im = (double)x.i;
           cval = PyComplex_FromDoubles(re,im);
           PyList_SetItem(col,i,cval);
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}

PyObject *mcopyToListByCol_d(vsip_mview_d *v){
    vsip_length M = vsip_mgetcollength_d(v);
    vsip_length N = vsip_mgetrowlength_d(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           double x = (double)vsip_mget_d(v,i,j);
           PyList_SetItem(col,i,PyFloat_FromDouble(x));
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}

PyObject *mcopyToListByCol_i(vsip_mview_i *v){
    vsip_length M = vsip_mgetcollength_i(v);
    vsip_length N = vsip_mgetrowlength_i(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           long int x = (long int)vsip_mget_i(v,i,j);
           PyList_SetItem(col,i,PyInt_FromLong(x));
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}

PyObject *mcopyToListByCol_si(vsip_mview_si *v){
    vsip_length M = vsip_mgetcollength_si(v);
    vsip_length N = vsip_mgetrowlength_si(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           long int x = (long int)vsip_mget_si(v,i,j);
           PyList_SetItem(col,i,PyInt_FromLong(x));
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}

PyObject *mcopyToListByCol_uc(vsip_mview_uc *v){
    vsip_length M = vsip_mgetcollength_uc(v);
    vsip_length N = vsip_mgetrowlength_uc(v);
    PyObject *retval = PyList_New(M);
    vsip_index i,j;
    for(j=0; j<N; j++){
        PyObject *col = PyList_New(M);
        for(i=0; i<M; i++){
           long int x = (long int)vsip_mget_uc(v,i,j);
           PyList_SetItem(col,i,PyInt_FromLong(x));
        }
        PyList_SetItem(retval,j,col);
    }
    return retval;
}
