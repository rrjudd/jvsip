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
#ifndef _PYVSIP_H
#define _PYVSIP_H

/* extra functions for python */
vsip_index *vindexptr(void);
void vindexfree(vsip_index*);
vsip_index vindexptrToInt(vsip_index*);
vsip_cscalar_f py_rcvjdot_f(const vsip_vview_f*, const vsip_cvview_f*);
vsip_cscalar_f py_crvjdot_f(const vsip_cvview_f* , const vsip_vview_f*);
vsip_cscalar_d py_rcvjdot_d(const vsip_vview_d*, const vsip_cvview_d*);
vsip_cscalar_d py_crvjdot_d(const vsip_cvview_d* , const vsip_vview_d*);
PyObject *cvcopyToList_f(vsip_cvview_f *);
PyObject *cvcopyToList_d(vsip_cvview_d *);
PyObject *vcopyToList_f(vsip_vview_f *);
PyObject *vcopyToList_d(vsip_vview_d *);
PyObject *vcopyToList_i(vsip_vview_i *);
PyObject *vcopyToList_si(vsip_vview_si *);
PyObject *vcopyToList_uc(vsip_vview_uc *);
PyObject *vcopyToList_vi(vsip_vview_vi *);
PyObject *vcopyToList_mi(vsip_vview_mi *);
PyObject *cmcopyToListByRow_f(vsip_cmview_f *);
PyObject *mcopyToListByRow_f(vsip_mview_f *);
PyObject *cmcopyToListByRow_d(vsip_cmview_d *);
PyObject *mcopyToListByRow_d(vsip_mview_d *);
#endif
