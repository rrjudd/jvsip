/* See Copyright in top level directory */
/*********************************************************************
// This code includes                                                 /
// no warranty, express or implied, including the warranties          /
// of merchantability and fitness for a particular purpose.           /
// No person or entity                                                /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
#ifndef _NUMPYARRAYCOPIES_H
#define _NUMPYARRAYCOPIES_H
#include<vsip.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include"Python.h"
#include"numpy/arrayobject.h"
/* extra functions for python */
void vcopyToNParray_d(vsip_vview_d *, PyObject* );
void vcopyToNParray_f(vsip_vview_f *, PyObject* );
void cvcopyToNParray_d(vsip_cvview_d *, PyObject* );
void cvcopyToNParray_f(vsip_cvview_f *, PyObject* );
void mcopyToNParray_d(vsip_mview_d *, vsip_major, PyObject* );
void mcopyToNParray_f(vsip_mview_f *, vsip_major, PyObject* );
void cmcopyToNParray_d(vsip_cmview_d *, vsip_major, PyObject* );
void cmcopyToNParray_f(vsip_cmview_f *, vsip_major, PyObject* );
void vcopyFromNParray_d(vsip_vview_d *, PyObject* );
void vcopyFromNParray_f(vsip_vview_f *, PyObject* );
void cvcopyFromNParray_d(vsip_cvview_d *, PyObject* );
void cvcopyFromNParray_f(vsip_cvview_f *, PyObject* );
void mcopyFromNParray_d(vsip_mview_d *, vsip_major, PyObject* );
void mcopyFromNParray_f(vsip_mview_f *, vsip_major, PyObject* );
void cmcopyFromNParray_d(vsip_cmview_d *, vsip_major, PyObject* );
void cmcopyFromNParray_f(vsip_cmview_f *, vsip_major, PyObject* );
#endif
