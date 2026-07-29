#include"numpyArrayCopies.h"

void vcopyToNParray_d(vsip_vview_d *v, PyObject* array){
    vsip_vcopyto_user_d(v,(vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array));
}
void vcopyToNParray_f(vsip_vview_f *v, PyObject* array){
    vsip_vcopyto_user_f(v,(vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array));
}
void cvcopyToNParray_d(vsip_cvview_d *v, PyObject* array){
    vsip_cvcopyto_user_d(v,(vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array),NULL);
}
void cvcopyToNParray_f(vsip_cvview_f *v, PyObject* array){
    vsip_cvcopyto_user_f(v,(vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array),NULL);
}
void mcopyToNParray_d(vsip_mview_d *v, vsip_major major, PyObject* array){
    vsip_mcopyto_user_d(v,major,(vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array));
}
void mcopyToNParray_f(vsip_mview_f *v, vsip_major major, PyObject* array){
    vsip_mcopyto_user_f(v,major,(vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array));
}
void cmcopyToNParray_d(vsip_cmview_d *v, vsip_major major, PyObject* array){
    vsip_cmcopyto_user_d(v,major,(vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array),NULL);
}
void cmcopyToNParray_f(vsip_cmview_f *v, vsip_major major, PyObject* array){
    vsip_cmcopyto_user_f(v,major,(vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array),NULL);
}

void vcopyFromNParray_d(vsip_vview_d *v, PyObject* array){
    vsip_vcopyfrom_user_d((vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array),v);
}
void vcopyFromNParray_f(vsip_vview_f *v, PyObject* array){
    vsip_vcopyfrom_user_f((vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array),v);
}
void cvcopyFromNParray_d(vsip_cvview_d *v, PyObject* array){
    vsip_cvcopyfrom_user_d((vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array),NULL,v);
}
void cvcopyFromNParray_f(vsip_cvview_f *v, PyObject* array){
    vsip_cvcopyfrom_user_f((vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array),NULL,v);
}
void mcopyFromNParray_d(vsip_mview_d *v, vsip_major major, PyObject* array){
    vsip_mcopyfrom_user_d((vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array),major,v);
}
void mcopyFromNParray_f(vsip_mview_f *v, vsip_major major, PyObject* array){
    vsip_mcopyfrom_user_f((vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array),major,v);
}
void cmcopyFromNParray_d(vsip_cmview_d *v, vsip_major major, PyObject* array){
    vsip_cmcopyfrom_user_d((vsip_scalar_d*)PyArray_DATA((PyArrayObject*)array),NULL,major,v);
}
void cmcopyFromNParray_f(vsip_cmview_f *v, vsip_major major, PyObject* array){
    vsip_cmcopyfrom_user_f((vsip_scalar_f*)PyArray_DATA((PyArrayObject*)array),NULL,major,v);
}
