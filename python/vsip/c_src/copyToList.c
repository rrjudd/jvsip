#include<vsip.h>
#include"Python.h"
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
    vsip_length M = vsip_vgetcollength_f(v);
    vsip_length N = vsip_vgetrowlength_f(v);
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
    vsip_length M = vsip_vgetcollength_d(v);
    vsip_length N = vsip_vgetrowlength_d(v);
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

