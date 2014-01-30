/* Created RJudd February 10, 2013 */
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
/* This file includes functions to simplify conversion of python slices
// to VSIPL views. With the exception of Clones which create a new view
// and associated block with a copy of data from input view two views
// are input and one is returned with the subview attributes          */

#include"VU_svdUtils.h"

/* these functions return a 'bottom corner' of a matrix or vector */
vsip_mview_f* msv_f(
    vsip_mview_f *B, 
    vsip_mview_f *BS, 
    vsip_index i,vsip_index j){
    vsip_mattr_f attr;
    vsip_mgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_f(BS,&attr);
    return BS;
}
vsip_vview_f *vsv_f(
    vsip_vview_f *v,
    vsip_vview_f *vs,
    vsip_index i){
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
}
vsip_cmview_f* cmsv_f(
    vsip_cmview_f *B, 
    vsip_cmview_f *BS, 
    vsip_index i,vsip_index j){
    vsip_cmattr_f attr;
    vsip_cmgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_f(BS,&attr);
    return BS;
}
vsip_cvview_f *cvsv_f(
    vsip_cvview_f *v,
    vsip_cvview_f *vs,
    vsip_index i){
     vsip_cvattr_f attr;
     vsip_cvgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_f(vs,&attr);
     return vs;
}
vsip_mview_d* msv_d(
    vsip_mview_d *B, 
    vsip_mview_d *BS, 
    vsip_index i,vsip_index j){
    vsip_mattr_d attr;
    vsip_mgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_d(BS,&attr);
    return BS;
}
vsip_vview_d *vsv_d(
    vsip_vview_d *v,
    vsip_vview_d *vs,
    vsip_index i){
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
}
vsip_cmview_d* cmsv_d(vsip_cmview_d *B,vsip_cmview_d *BS, vsip_index i,vsip_index j){
    vsip_cmattr_d attr;
    vsip_cmgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_d(BS,&attr);
    return BS;
}
vsip_cvview_d *cvsv_d(vsip_cvview_d *v,vsip_cvview_d *vs,vsip_index i){
     vsip_cvattr_d attr;
     vsip_cvgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_d(vs,&attr);
     return vs;
}

/* these functions return a column or row of a matrix */
vsip_cvview_f *ccol_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index col){
    vsip_cmattr_f A; vsip_cvattr_f v;
    vsip_cmgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_f(vv,&v);
    return vv;
}
vsip_cvview_f *crow_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index row){
    vsip_cmattr_f A; vsip_cvattr_f v;
    vsip_cmgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_cvputattrib_f(vv,&v);
    return vv;
}
vsip_vview_f *col_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index col){
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
vsip_vview_f *row_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index row){
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
vsip_vview_d *col_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index col){
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
vsip_vview_d *row_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index row){
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
vsip_cvview_d *ccol_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index col){
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}
vsip_cvview_d *crow_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index row){
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}

/* these functions return an interior subview of a matrix or vector */
/* note the first index is a corner and the second index is a length (the same as a slice) */
/* for example imsv_f(B,BS,i1,j1,i2,j2) returns a view equivalent to B[i1:j1,i2:j2]; */
/* a view equivalent to B[:,i2:j2] is imsv_f(B,BS,0,0,i2,j2) */
/* a view equivalent to B[i1:j1,:] is imsv_f(B,BS,i1,j1,0,0) */
/* a view equivalent to B[i1:j1,i2:] is imsv_f(B,BS,i1,j1,i2,0) */
vsip_mview_f* imsv_f( vsip_mview_f *B, vsip_mview_f *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
{
    vsip_mattr_f attr;
    vsip_mgetattrib_f(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_mputattrib_f(BS,&attr);
    return BS;
}
vsip_vview_f *ivsv_f( vsip_vview_f *v, vsip_vview_f *vs, vsip_index i,vsip_index j)
{
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
}
vsip_cmview_f* cimsv_f( vsip_cmview_f *B, vsip_cmview_f *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
{
    vsip_cmattr_f attr;
    vsip_cmgetattrib_f(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_cmputattrib_f(BS,&attr);
    return BS;
}
vsip_cvview_f *civsv_f( vsip_cvview_f *v, vsip_cvview_f *vs, vsip_index i, vsip_index j)
{
     vsip_cvattr_f attr;
     vsip_cvgetattrib_f(v,&attr);
     if(j==0) j=attr.length;     
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_cvputattrib_f(vs,&attr);
     return vs;
}
vsip_mview_d* imsv_d( vsip_mview_d *B, vsip_mview_d *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
{
    vsip_mattr_d attr;
    vsip_mgetattrib_d(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_mputattrib_d(BS,&attr);
    return BS;
}
vsip_vview_d *ivsv_d( vsip_vview_d *v, vsip_vview_d *vs, vsip_index i, vsip_index j)
{
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
}
vsip_cmview_d* cimsv_d( vsip_cmview_d *B, vsip_cmview_d *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
{
    vsip_cmattr_d attr;
    vsip_cmgetattrib_d(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_cmputattrib_d(BS,&attr);
    return BS;
}
vsip_cvview_d *civsv_d(vsip_cvview_d *v,vsip_cvview_d *vs,vsip_index i,vsip_index j)
{
     vsip_cvattr_d attr;
     vsip_cvgetattrib_d(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_cvputattrib_d(vs,&attr);
     return vs;
}

/* these functions create a new data space and copy the input into it */
vsip_cmview_d* cmclone_d(vsip_cmview_d*A){
    vsip_cmview_d *B = vsip_cmcreate_d(
                      vsip_cmgetcollength_d(A),
                      vsip_cmgetrowlength_d(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_cmcopy_d_d(A,B);
    return B;
}
vsip_cvview_d* cvclone_d(vsip_cvview_d*x){
    vsip_cvview_d *v = vsip_cvcreate_d(
                      vsip_cvgetlength_d(x),
                      VSIP_MEM_NONE);
    if(v) vsip_cvcopy_d_d(x,v);
    return v;
}
vsip_mview_d* mclone_d(vsip_mview_d*A){
    vsip_mview_d *B = vsip_mcreate_d(
                      vsip_mgetcollength_d(A),
                      vsip_mgetrowlength_d(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_mcopy_d_d(A,B);
    return B;
}
vsip_vview_d* vclone_d(vsip_vview_d*x){
    vsip_vview_d *v = vsip_vcreate_d(
                      vsip_vgetlength_d(x),
                      VSIP_MEM_NONE);
    if(v) vsip_vcopy_d_d(x,v);
    return v;
}
vsip_cmview_f* cmclone_f(vsip_cmview_f*A){
    vsip_cmview_f *B = vsip_cmcreate_f(
                      vsip_cmgetcollength_f(A),
                      vsip_cmgetrowlength_f(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_cmcopy_f_f(A,B);
    return B;
}
vsip_cvview_f* cvclone_f(vsip_cvview_f*x){
    vsip_cvview_f *v = vsip_cvcreate_f(
                      vsip_cvgetlength_f(x),
                      VSIP_MEM_NONE);
    if(v) vsip_cvcopy_f_f(x,v);
    return v;
}
vsip_mview_f* mclone_f(vsip_mview_f*A){
    vsip_mview_f *B = vsip_mcreate_f(
                      vsip_mgetcollength_f(A),
                      vsip_mgetrowlength_f(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_mcopy_f_f(A,B);
    return B;
}
vsip_vview_f* vclone_f(vsip_vview_f*x){
    vsip_vview_f *v = vsip_vcreate_f(
                      vsip_vgetlength_f(x),
                      VSIP_MEM_NONE);
    if(v) vsip_vcopy_f_f(x,v);
    return v;
}