/* Created RJudd March 2, 2013 */
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
#include"svd.h"
/* these functions return a 'bottom corner' of a matrix or vector */
static vsip_mview_f* msv_f(
    vsip_mview_f *B, 
    vsip_mview_f *BS, 
    vsip_index i,vsip_index j)
{
    vsip_mattr_f attr;
    vsip_mgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_f(BS,&attr);
    return BS;
}
static vsip_vview_f *vsv_f(
    vsip_vview_f *v,
    vsip_vview_f *vs,
    vsip_index i)
{
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
}
static vsip_cmview_f* cmsv_f(
    vsip_cmview_f *B, 
    vsip_cmview_f *BS, 
    vsip_index i,vsip_index j)
{
    vsip_cmattr_f attr;
    vsip_cmgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_f(BS,&attr);
    return BS;
}
static vsip_cvview_f *cvsv_f(
    vsip_cvview_f *v,
    vsip_cvview_f *vs,
    vsip_index i)
{
     vsip_cvattr_f attr;
     vsip_cvgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_f(vs,&attr);
     return vs;
}
static vsip_mview_d* msv_d(
    vsip_mview_d *B, 
    vsip_mview_d *BS, 
    vsip_index i,vsip_index j)
{
    vsip_mattr_d attr;
    vsip_mgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_d(BS,&attr);
    return BS;
}
static vsip_vview_d *vsv_d(
    vsip_vview_d *v,
    vsip_vview_d *vs,
    vsip_index i)
{
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
}
static vsip_cmview_d* cmsv_d(vsip_cmview_d *B,vsip_cmview_d *BS, vsip_index i,vsip_index j)
{
    vsip_cmattr_d attr;
    vsip_cmgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_d(BS,&attr);
    return BS;
}
static vsip_cvview_d *cvsv_d(vsip_cvview_d *v,vsip_cvview_d *vs,vsip_index i)
{
     vsip_cvattr_d attr;
     vsip_cvgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_d(vs,&attr);
     return vs;
}

/* these functions return a column or row of a matrix */
static vsip_cvview_f *ccol_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index col)
{
    vsip_cmattr_f A; vsip_cvattr_f v;
    vsip_cmgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_f(vv,&v);
    return vv;
}
static vsip_cvview_f *crow_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index row)
{
    vsip_cmattr_f A; vsip_cvattr_f v;
    vsip_cmgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_cvputattrib_f(vv,&v);
    return vv;
}
static vsip_vview_f *col_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index col)
{
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
static vsip_vview_f *row_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index row)
{
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
static vsip_vview_d *col_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index col)
{
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
static vsip_vview_d *row_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index row)
{
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
static vsip_cvview_d *ccol_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index col)
{
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}
static vsip_cvview_d *crow_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index row)
{
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
static vsip_mview_f* imsv_f( vsip_mview_f *B, vsip_mview_f *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
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
static vsip_vview_f *ivsv_f( vsip_vview_f *v, vsip_vview_f *vs, vsip_index i,vsip_index j)
{
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
}
static vsip_cmview_f* cimsv_f( vsip_cmview_f *B, vsip_cmview_f *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
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
static vsip_mview_d* imsv_d( vsip_mview_d *B, vsip_mview_d *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
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
static vsip_vview_d *ivsv_d( vsip_vview_d *v, vsip_vview_d *vs, vsip_index i, vsip_index j)
{
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
}
static vsip_cmview_d* cimsv_d( vsip_cmview_d *B, vsip_cmview_d *BS, vsip_index i1,vsip_index j1, vsip_index i2, vsip_index j2)
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

/* these functions create a new data space and copy the input into it */
static vsip_cmview_d* cmclone_d(vsip_cmview_d*A){
    vsip_cmview_d *B = vsip_cmcreate_d(
                      vsip_cmgetcollength_d(A),
                      vsip_cmgetrowlength_d(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_cmcopy_d_d(A,B);
    return B;
}
static vsip_cvview_d* cvclone_d(vsip_cvview_d*x){
    vsip_cvview_d *v = vsip_cvcreate_d(
                      vsip_cvgetlength_d(x),
                      VSIP_MEM_NONE);
    if(v) vsip_cvcopy_d_d(x,v);
    return v;
}
static vsip_mview_d* mclone_d(vsip_mview_d*A){
    vsip_mview_d *B = vsip_mcreate_d(
                      vsip_mgetcollength_d(A),
                      vsip_mgetrowlength_d(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_mcopy_d_d(A,B);
    return B;
}
static vsip_vview_d* vclone_d(vsip_vview_d*x){
    vsip_vview_d *v = vsip_vcreate_d(
                      vsip_vgetlength_d(x),
                      VSIP_MEM_NONE);
    if(v) vsip_vcopy_d_d(x,v);
    return v;
}
static vsip_cmview_f* cmclone_f(vsip_cmview_f*A){
    vsip_cmview_f *B = vsip_cmcreate_f(
                      vsip_cmgetcollength_f(A),
                      vsip_cmgetrowlength_f(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_cmcopy_f_f(A,B);
    return B;
}
static vsip_cvview_f* cvclone_f(vsip_cvview_f*x){
    vsip_cvview_f *v = vsip_cvcreate_f(
                      vsip_cvgetlength_f(x),
                      VSIP_MEM_NONE);
    if(v) vsip_cvcopy_f_f(x,v);
    return v;
}
static vsip_mview_f* mclone_f(vsip_mview_f*A){
    vsip_mview_f *B = vsip_mcreate_f(
                      vsip_mgetcollength_f(A),
                      vsip_mgetrowlength_f(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_mcopy_f_f(A,B);
    return B;
}
static vsip_vview_f* vclone_f(vsip_vview_f*x){
    vsip_vview_f *v = vsip_vcreate_f(
                      vsip_vgetlength_f(x),
                      VSIP_MEM_NONE);
    if(v) vsip_vcopy_f_f(x,v);
    return v;
}

/* convenienc functions for creating identity matrices */
static vsip_mview_f* meye_f(vsip_length n){
    vsip_vview_f *d = (vsip_vview_f*) NULL;
    vsip_mview_f *retval = (vsip_mview_f*)NULL;
    retval = vsip_mcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_mdiagview_f(retval,0);
    if(d){
        vsip_mfill_f(0.0,retval);
        vsip_vfill_f(1.0,d);
        vsip_vdestroy_f(d);
    } else {
        vsip_malldestroy_f(retval);
        retval = (vsip_mview_f*) NULL;
    }
    return retval;
}
static vsip_cmview_f* cmeye_f(vsip_length n){
    vsip_cvview_f *d = (vsip_cvview_f*) NULL;
    vsip_cmview_f *retval = (vsip_cmview_f*)NULL;
    retval = vsip_cmcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_cmdiagview_f(retval,0);
    if(d){
        vsip_cmfill_f(vsip_cmplx_f(0.0,0.0),retval);
        vsip_cvfill_f(vsip_cmplx_f(1.0,0.0),d);
        vsip_cvdestroy_f(d);
    } else {
        vsip_cmalldestroy_f(retval);
        retval = (vsip_cmview_f*) NULL;
    }
    return retval;
}
static vsip_mview_d* meye_d(vsip_length n){
    vsip_vview_d *d = (vsip_vview_d*) NULL;
    vsip_mview_d *retval = (vsip_mview_d*)NULL;
    retval = vsip_mcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_mdiagview_d(retval,0);
    if(d){
        vsip_mfill_d(0.0,retval);
        vsip_vfill_d(1.0,d);
        vsip_vdestroy_d(d);
    } else {
        vsip_malldestroy_d(retval);
        retval = (vsip_mview_d*) NULL;
    }
    return retval;
}
static vsip_cmview_d* cmeye_d(vsip_length n){
    vsip_cvview_d *d = (vsip_cvview_d*) NULL;
    vsip_cmview_d *retval = (vsip_cmview_d*)NULL;
    retval = vsip_cmcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_cmdiagview_d(retval,0);
    if(d){
        vsip_cmfill_d(vsip_cmplx_d(0.0,0.0),retval);
        vsip_cvfill_d(vsip_cmplx_d(1.0,0.0),d);
        vsip_cvdestroy_d(d);
    } else {
        vsip_cmalldestroy_d(retval);
        retval = (vsip_cmview_d*) NULL;
    }
    return retval;
}

/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_f sign_f(vsip_scalar_f a_in){
    if(a_in < 0.0)
       return -1.0;
    else 
       return 1.0;
}
static vsip_cscalar_f csign_f(vsip_cscalar_f a_in){
    vsip_scalar_f re = a_in.r;
    vsip_scalar_f im = a_in.i;
    vsip_scalar_f t=vsip_hypot_f(re,im);
    vsip_cscalar_f retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0) {
        retval.r = sign_f(re);
        return retval;
    } else {
        retval.r = re/t;
        retval.i = im/t;
        return retval;
    }
}
static vsip_scalar_d sign_d(vsip_scalar_d a_in){
    if(a_in < 0.0)
        return -1.0;
    else 
        return 1.0; 
}
static vsip_cscalar_d csign_d(vsip_cscalar_d a_in){
    vsip_scalar_d re = a_in.r;
    vsip_scalar_d im = a_in.i;
    vsip_scalar_d t=vsip_hypot_d(re,im);
    vsip_cscalar_d retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0){
        retval.r = sign_d(re);
        return retval;
    } else {
        retval.r = re/t;
        retval.i = im/t;
        return retval;
    }
}

static vsip_scalar_f vnormFro_f(vsip_vview_f *v){
    return vsip_sqrt_f(vsip_vsumsqval_f(v));
}
static vsip_scalar_f vnorm2_f(vsip_vview_f *v){
    return vnormFro_f(v);
}
static vsip_scalar_f cvnorm2_f(vsip_cvview_f *v){
    return vsip_sqrt_f(vsip_cvjdot_f(v,v).r);
}
static vsip_scalar_d vnormFro_d(vsip_vview_d *v){
    return vsip_sqrt_d(vsip_vsumsqval_d(v));
}
static vsip_scalar_d vnorm2_d(vsip_vview_d *v){
    return vnormFro_d(v);
}
static vsip_scalar_d cvnorm2_d(vsip_cvview_d *v){
    return vsip_sqrt_d(vsip_cvjdot_d(v,v).r);
}
static vsip_scalar_f mnormFro_f(vsip_mview_f *v){
    return vsip_sqrt_f(vsip_msumsqval_f(v));
}
static vsip_scalar_d mnormFro_d(vsip_mview_d *v){
    return vsip_sqrt_d(vsip_msumsqval_d(v));
}
static vsip_scalar_f cmnormFro_f(vsip_cmview_f *v){
    vsip_mview_f* re=vsip_mrealview_f(v); 
    vsip_mview_f* im=vsip_mimagview_f(v);
    return vsip_sqrt_f(vsip_msumsqval_f(re)+vsip_msumsqval_f(im));
    vsip_mdestroy_f(re);vsip_mdestroy_f(im);
}
static vsip_scalar_d cmnormFro_d(vsip_cmview_d *v){
    vsip_mview_d* re=vsip_mrealview_d(v); 
    vsip_mview_d* im=vsip_mimagview_d(v);
    return vsip_sqrt_d(vsip_msumsqval_d(re)+vsip_msumsqval_d(im));
    vsip_mdestroy_d(re);vsip_mdestroy_d(im);
}

static void gtProd_f(vsip_index i, vsip_index j, vsip_scalar_f c,vsip_scalar_f s, vsip_mview_f* R)
{
    vsip_vview_f *a1= vsip_mrowview_f(R,i);
    vsip_vview_f *a2= vsip_mrowview_f(R,j);
    vsip_vview_f *a1c=vclone_f(a1);
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1);
    vsip_svmul_f(-s,a1c,a1c); vsip_vsma_f(a2,c,a1c,a2); 
    vsip_vdestroy_f(a1);vsip_vdestroy_f(a2);
    vsip_valldestroy_f(a1c);
}
static void gtProd_d(vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s,vsip_mview_d*R)
{
    vsip_vview_d *a1= vsip_mrowview_d(R,i);
    vsip_vview_d *a2= vsip_mrowview_d(R,j);
    vsip_vview_d *a1c=vclone_d(a1);
    vsip_vview_d *a2c=vclone_d(a2);
    vsip_svmul_d(c,a1c,a1); vsip_vsma_d(a2c,s,a1,a1); 
    vsip_svmul_d(c,a2c,a2); vsip_vsma_d(a1c,-s,a2,a2);
    vsip_vdestroy_d(a1);vsip_vdestroy_d(a2);
    vsip_valldestroy_d(a1c); vsip_valldestroy_d(a2c);
}
static void cgtProd_f(vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s,vsip_cmview_f*R)
{
    vsip_cvview_f *a1= vsip_cmrowview_f(R,i);
    vsip_cvview_f *a2= vsip_cmrowview_f(R,j);
    vsip_cvview_f *a1c=cvclone_f(a1);
    vsip_cvview_f *a2c=cvclone_f(a2);
    vsip_rscvmul_f(c,a1c,a1);  vsip_rscvmul_f(c,a2c,a2);
    vsip_rscvmul_f(s,a2c,a2c); vsip_rscvmul_f(-s,a1c,a1c);
    vsip_cvadd_f(a1,a2c,a1); vsip_cvadd_f(a2,a1c,a2);
    vsip_cvdestroy_f(a1);vsip_cvdestroy_f(a2);
    vsip_cvalldestroy_f(a1c); vsip_cvalldestroy_f(a2c);
}
static void cgtProd_d(vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s,vsip_cmview_d*R)
{
    vsip_cvview_d *a1= vsip_cmrowview_d(R,i);
    vsip_cvview_d *a2= vsip_cmrowview_d(R,j);
    vsip_cvview_d *a1c=cvclone_d(a1);
    vsip_cvview_d *a2c=cvclone_d(a2);
    vsip_rscvmul_d(c,a1c,a1);  vsip_rscvmul_d(c,a2c,a2);
    vsip_rscvmul_d(s,a2c,a2c); vsip_rscvmul_d(-s,a1c,a1c);
    vsip_cvadd_d(a1,a2c,a1); vsip_cvadd_d(a2,a1c,a2);
    vsip_cvdestroy_d(a1);vsip_cvdestroy_d(a2);
    vsip_cvalldestroy_d(a1c); vsip_cvalldestroy_d(a2c);
}

static void prodG_f(vsip_mview_f* L,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_vview_f *a1= vsip_mcolview_f(L,i);
    vsip_vview_f *a2= vsip_mcolview_f(L,j);
    vsip_vview_f *a1c=vclone_f(a1);
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1);
    vsip_svmul_f(-s,a1c,a1c);vsip_vsma_f(a2,c,a1c,a2);
    vsip_vdestroy_f(a1);vsip_vdestroy_f(a2);
    vsip_valldestroy_f(a1c);
}
static void prodG_d(vsip_mview_d* L,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_vview_d *a1= vsip_mcolview_d(L,i);
    vsip_vview_d *a2= vsip_mcolview_d(L,j);
    vsip_vview_d *a1c=vclone_d(a1);
    vsip_vview_d *a2c=vclone_d(a2);
    vsip_svmul_d(c,a1c,a1); vsip_vsma_d(a2,s,a1,a1);
    vsip_svmul_d(c,a2c,a2); vsip_vsma_d(a1c,-s,a2,a2);
    vsip_vdestroy_d(a1);vsip_vdestroy_d(a2);
    vsip_valldestroy_d(a1c); vsip_valldestroy_d(a2c);
}
static void cprodG_f(vsip_cmview_f* L,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_cvview_f *a1= vsip_cmcolview_f(L,i);
    vsip_cvview_f *a2= vsip_cmcolview_f(L,j);
    vsip_cvview_f *a1c=cvclone_f(a1);
    vsip_cvview_f *a2c=cvclone_f(a2);
    vsip_rscvmul_f(c,a1c,a1); vsip_rscvmul_f(-s,a1c,a1c);
    vsip_rscvmul_f(c,a2c,a2); vsip_rscvmul_f(s,a2c,a2c);
    vsip_cvadd_f(a1,a2c,a1); vsip_cvadd_f(a2,a1c,a2);
    vsip_cvdestroy_f(a1);vsip_cvdestroy_f(a2);
    vsip_cvalldestroy_f(a1c); vsip_cvalldestroy_f(a2c);
}
static void cprodG_d(vsip_cmview_d* L,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_cvview_d *a1= vsip_cmcolview_d(L,i);
    vsip_cvview_d *a2= vsip_cmcolview_d(L,j);
    vsip_cvview_d *a1c=cvclone_d(a1);
    vsip_cvview_d *a2c=cvclone_d(a2);
    vsip_rscvmul_d(c,a1c,a1); vsip_rscvmul_d(-s,a1c,a1c);
    vsip_rscvmul_d(c,a2c,a2); vsip_rscvmul_d(s,a2c,a2c);
    vsip_cvadd_d(a1,a2c,a1); vsip_cvadd_d(a2,a1c,a2);
    vsip_cvdestroy_d(a1);vsip_cvdestroy_d(a2);
    vsip_cvalldestroy_d(a1c); vsip_cvalldestroy_d(a2c);
}

static vsip_vview_f *houseVector_f(vsip_vview_f* x){
    vsip_scalar_f nrm=vnorm2_f(x);
    vsip_scalar_f t = vsip_vget_f(x,0);
    vsip_scalar_f s = t +  sign_f(t) * nrm;
    vsip_vput_f(x,0,s); 
    nrm = vnorm2_f(x);
    if (nrm == 0.0)
        vsip_vput_f(x,0,1.0); 
    else
        vsip_svmul_f(1.0/nrm,x,x);
    return x;
}
void prodHouse_f(vsip_mview_f *A, vsip_vview_f *v){
    vsip_mattr_f a_atr; 
    vsip_vview_f *w;
    vsip_mview_f *B;
    vsip_mgetattrib_f(A,&a_atr);
    B=vsip_mcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_f(a_atr.col_length,VSIP_MEM_NONE);
    vsip_scalar_f beta = 2.0/vsip_vdot_f(v,v);
    vsip_mvprod_f(A,v,w);
    vsip_vouter_f(beta,w,v,B);
    vsip_msub_f(A,B,A);
    vsip_valldestroy_f(w);
    vsip_malldestroy_f(B);
}
void houseProd_f(vsip_vview_f *v, vsip_mview_f *A){
    vsip_mattr_f a_atr; 
    vsip_vview_f *w;
    vsip_mview_f *B;
    vsip_mgetattrib_f(A,&a_atr);
    B=vsip_mcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_f(a_atr.row_length,VSIP_MEM_NONE);
    vsip_scalar_f beta = 2.0/vsip_vdot_f(v,v);
    vsip_vmprod_f(v,A,w);
    vsip_vouter_f(beta,v,w,B);
    vsip_msub_f(A,B,A);
    vsip_valldestroy_f(w);
    vsip_malldestroy_f(B);
}

static vsip_cvview_f *chouseVector_f(vsip_cvview_f* x){
    vsip_cscalar_f t = vsip_cvget_f(x,0); /*x[0]*/
    vsip_scalar_f nrm=cvnorm2_f(x); /* x.norm2 */
    vsip_cscalar_f s = vsip_cadd_f(t, vsip_cmul_f(csign_f(t), vsip_cmplx_f(nrm, 0.0)));
    vsip_cvput_f(x,0,s);
    nrm = cvnorm2_f(x);
    if (nrm == 0.0)
        vsip_cvput_f(x,0,vsip_cmplx_f(1.0,0.0));
    else
        vsip_rscvmul_f(1.0/nrm,x,x);
    return x;
}
void chouseProd_f(vsip_cvview_f *v, vsip_cmview_f *A){
    vsip_cmattr_f a_atr; 
    vsip_cvview_f *w;
    vsip_cmview_f *B;
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_cmgetattrib_f(A,&a_atr);
    B=vsip_cmcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_f(a_atr.row_length,VSIP_MEM_NONE);
    vsip_cvconj_f(v,v);
    vsip_cvmprod_f(v,A,w);vsip_cvconj_f(w,w);
    vsip_cvconj_f(v,v);
    vsip_cvouter_f(vsip_cmplx_f(beta,0.0),v,w,B);
    vsip_cmsub_f(A,B,A);
    vsip_cvalldestroy_f(w);
    vsip_cmalldestroy_f(B);
}
void cprodHouse_f(vsip_cmview_f *A, vsip_cvview_f *v){
    vsip_cmattr_f a_atr; 
    vsip_cvview_f *w;
    vsip_cmview_f *B;
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_cmgetattrib_f(A,&a_atr);
    B=vsip_cmcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_f(a_atr.col_length,VSIP_MEM_NONE);
    vsip_cmvprod_f(A,v,w);
    vsip_cvouter_f(vsip_cmplx_f(beta,0.0),w,v,B);
    vsip_cmsub_f(A,B,A);
    vsip_cvalldestroy_f(w);
    vsip_cmalldestroy_f(B);
}

static vsip_vview_d *houseVector_d(vsip_vview_d* x){
    vsip_scalar_d nrm=vnorm2_d(x);
    vsip_scalar_d t = vsip_vget_d(x,0);
    vsip_scalar_d s = t +  sign_d(t) * nrm;
    vsip_vput_d(x,0,s); 
    nrm = vnorm2_d(x);
    if (nrm == 0.0)
        vsip_vput_d(x,0,1.0); 
    else
        vsip_svmul_d(1.0/nrm,x,x);
    return x;
}
void houseProd_d(vsip_vview_d *v, vsip_mview_d *A){
    vsip_mattr_d a_atr; 
    vsip_vview_d *w;
    vsip_mview_d *B;
    vsip_mgetattrib_d(A,&a_atr);
    B=vsip_mcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_d(a_atr.row_length,VSIP_MEM_NONE);
    vsip_scalar_d beta = 2.0/vsip_vdot_d(v,v);
    vsip_vmprod_d(v,A,w);
    vsip_vouter_d(beta,v,w,B);
    vsip_msub_d(A,B,A);
    vsip_valldestroy_d(w);
    vsip_malldestroy_d(B);
}
void prodHouse_d(vsip_mview_d *A, vsip_vview_d *v){
    vsip_mattr_d a_atr; 
    vsip_vview_d *w;
    vsip_mview_d *B;
    vsip_mgetattrib_d(A,&a_atr);
    B=vsip_mcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_d(a_atr.col_length,VSIP_MEM_NONE);
    vsip_scalar_d beta = 2.0/vsip_vdot_d(v,v);
    vsip_mvprod_d(A,v,w);
    vsip_vouter_d(beta,w,v,B);
    vsip_msub_d(A,B,A);
    vsip_valldestroy_d(w);
    vsip_malldestroy_d(B);
}

static vsip_cvview_d* chouseVector_d(vsip_cvview_d* x){
    vsip_cscalar_d t = vsip_cvget_d(x,0); /*x[0]*/
    vsip_scalar_d nrm=cvnorm2_d(x); /* x.norm2 */
    vsip_cscalar_d s = vsip_cadd_d(t, vsip_cmul_d(csign_d(t), vsip_cmplx_d(nrm, 0.0)));
    vsip_cvput_d(x,0,s);
    nrm = cvnorm2_d(x);
    if (nrm == 0.0)
        vsip_cvput_d(x,0,vsip_cmplx_d(1.0,0.0));
    else
        vsip_rscvmul_d(1.0/nrm,x,x);
    return x;
}
void chouseProd_d(vsip_cvview_d *v, vsip_cmview_d *A){
    vsip_cmattr_d a_atr; 
    vsip_cvview_d *w;
    vsip_cmview_d *B;
    vsip_scalar_d beta = 2.0/vsip_cvjdot_d(v,v).r;
    vsip_cmgetattrib_d(A,&a_atr);
    B=vsip_cmcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_d(a_atr.row_length,VSIP_MEM_NONE);
    vsip_cvconj_d(v,v);
    vsip_cvmprod_d(v,A,w);vsip_cvconj_d(w,w);
    vsip_cvconj_d(v,v);
    vsip_cvouter_d(vsip_cmplx_d(beta,0.0),v,w,B);
    vsip_cmsub_d(A,B,A);
    vsip_cvalldestroy_d(w);
    vsip_cmalldestroy_d(B);
}
void cprodHouse_d(vsip_cmview_d *A, vsip_cvview_d *v){
    vsip_cmattr_d a_atr; 
    vsip_cvview_d *w;
    vsip_cmview_d *B;
    vsip_scalar_d beta = 2.0/vsip_cvjdot_d(v,v).r;
    vsip_cmgetattrib_d(A,&a_atr);
    B=vsip_cmcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_d(a_atr.col_length,VSIP_MEM_NONE);
    vsip_cmvprod_d(A,v,w);
    vsip_cvouter_d(vsip_cmplx_d(beta,0.0),w,v,B);
    vsip_cmsub_d(A,B,A);
    vsip_cvalldestroy_d(w);
    vsip_cmalldestroy_d(B);
}

static vsip_mview_f *bidiag_f(
    vsip_mview_f *A){
    vsip_length m = vsip_mgetcollength_f(A);
    vsip_length n = vsip_mgetrowlength_f(A);
    vsip_mview_f *B = mclone_f(A);
    vsip_mview_f *Bs= vsip_mcloneview_f(B);
    vsip_vview_f *x=vsip_mcolview_f(B,0);
    vsip_vview_f *v=vclone_f(x);
    vsip_vview_f *vs = vsip_vcloneview_f(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
    /* x=B[i:,i:].colview(0); v=houseVector(x); v/=v[0]*/
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
    /* houseProd(v,B[i:,i:]) */
        houseProd_f(v,Bs);
    /* x[1:]=v[1:] */
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_vputlength_f(v,n-j);
            vsip_vcopy_f_f(row_sv_f(msv_f(B,Bs,i,j),x,0),v);
            houseVector_f(v);
            vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
            prodHouse_f(Bs,v);
            vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
        houseProd_f(v,Bs);
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
    }
    vsip_vdestroy_f(vs); vsip_valldestroy_f(v);
    vsip_vdestroy_f(x); vsip_mdestroy_f(Bs);
    return B;
}
static vsip_cmview_f *cbidiag_f(
    vsip_cmview_f *A){
    vsip_length m = vsip_cmgetcollength_f(A);
    vsip_length n = vsip_cmgetrowlength_f(A);
    vsip_cmview_f *B = cmclone_f(A);
    vsip_cmview_f *Bs= vsip_cmcloneview_f(B);
    vsip_cvview_f *x=vsip_cmcolview_f(B,0);
    vsip_cvview_f *v=cvclone_f(x);
    vsip_cvview_f *vs = vsip_cvcloneview_f(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_f(v,n-j);
            vsip_cvcopy_f_f(crow_sv_f(cmsv_f(B,Bs,i,j),x,0),v);
            chouseVector_f(v);vsip_cvconj_f(v,v);
            vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
            cprodHouse_f(Bs,v);
            vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
    }
    vsip_cvdestroy_f(vs); vsip_cvalldestroy_f(v);
    vsip_cvdestroy_f(x); vsip_cmdestroy_f(Bs);
    return B;
}
static vsip_mview_d *bidiag_d(vsip_mview_d *A){
    vsip_length m = vsip_mgetcollength_d(A);
    vsip_length n = vsip_mgetrowlength_d(A);
    vsip_mview_d *B = mclone_d(A);
    vsip_mview_d *Bs= vsip_mcloneview_d(B);
    vsip_vview_d *x=vsip_mcolview_d(B,0);
    vsip_vview_d *v=vclone_d(x);
    vsip_vview_d *vs = vsip_vcloneview_d(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
        houseProd_d(v,Bs);
        vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_vputlength_d(v,n-j);
            vsip_vcopy_d_d(row_sv_d(msv_d(B,Bs,i,j),x,0),v);
            houseVector_d(v);
            vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
            prodHouse_d(Bs,v);
            vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
        houseProd_d(v,Bs);
        vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
    }
    vsip_vdestroy_d(vs); vsip_valldestroy_d(v);
    vsip_vdestroy_d(x); vsip_mdestroy_d(Bs);
    return B;
}
static vsip_cmview_d *cbidiag_d(
    vsip_cmview_d *A){
    vsip_length m = vsip_cmgetcollength_d(A);
    vsip_length n = vsip_cmgetrowlength_d(A);
    vsip_cmview_d *B = cmclone_d(A);
    vsip_cmview_d *Bs= vsip_cmcloneview_d(B);
    vsip_cvview_d *x=vsip_cmcolview_d(B,0);
    vsip_cvview_d *v=cvclone_d(x);
    vsip_cvview_d *vs = vsip_cvcloneview_d(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
        chouseProd_d(v,Bs);
        vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_d(v,n-j);
            vsip_cvcopy_d_d(crow_sv_d(cmsv_d(B,Bs,i,j),x,0),v);
            chouseVector_d(v);vsip_cvconj_d(v,v);
            vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
            cprodHouse_d(Bs,v);
            vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
        chouseProd_d(v,Bs);
        vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
    }
    vsip_cvdestroy_d(vs); vsip_cvalldestroy_d(v);
    vsip_cvdestroy_d(x); vsip_cmdestroy_d(Bs);
    return B;
}
static vsip_mview_f *UmatExtract_f(vsip_mview_f*B){
    vsip_stride i;
    vsip_length m = vsip_mgetcollength_f(B);
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *U=meye_f(m);
    vsip_mview_f *Bs, *Us;
    vsip_vview_f *v;
    vsip_scalar_f t;
    v = vsip_mcolview_f(B,0);
    Bs=vsip_mcloneview_f(B);
    Us=vsip_mcloneview_f(U);
    if (m > n){
        i=n-1;
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    } 
    return U;
}
static vsip_cmview_f *cUmatExtract_f(vsip_cmview_f*B){
    vsip_stride i;
    vsip_length m = vsip_cmgetcollength_f(B);
    vsip_length n = vsip_cmgetrowlength_f(B);
    vsip_cmview_f *U=cmeye_f(m);
    vsip_cmview_f *Bs, *Us;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    v = vsip_cmcolview_f(B,0);
    Bs=vsip_cmcloneview_f(B);
    Us=vsip_cmcloneview_f(U);
    if (m > n){
        i=n-1;
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
        chouseProd_f(v,cmsv_f(U,Us,i,i));
        vsip_cvput_f(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
        chouseProd_f(v,cmsv_f(U,Us,i,i));
        vsip_cvput_f(v,0,t);
    } 
    return U;
}
static vsip_mview_f *VHmatExtract_f(vsip_mview_f*B){
    vsip_stride i;
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *Bs; 
    vsip_mview_f *V=meye_f(n);
    vsip_mview_f *Vs;
    vsip_vview_f *v;
    vsip_scalar_f t;
    if(n < 3)
        return V;
    v = vsip_mrowview_f(B,0);
    Vs=vsip_mcloneview_f(V);
    Bs=vsip_mcloneview_f(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        row_sv_f(msv_f(B,Bs,i,j),v,0);
        t=vsip_vget_f(v,0);vsip_vput_f(v,0,1.0);
        prodHouse_f(msv_f(V,Vs,j,j),v);
        vsip_vput_f(v,0,t);
    }      
    vsip_vdestroy_f(v);
    vsip_mdestroy_f(Vs);
    vsip_mdestroy_f(Bs);
    return V;
}
static vsip_cmview_f *cVHmatExtract_f(vsip_cmview_f*B){
    vsip_stride i;
    vsip_length n = vsip_cmgetrowlength_f(B);
    vsip_cmview_f *Bs; 
    vsip_cmview_f *V=cmeye_f(n);
    vsip_cmview_f *Vs;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    if(n < 3)
        return V;
    v = vsip_cmrowview_f(B,0);
    Vs=vsip_cmcloneview_f(V);
    Bs=vsip_cmcloneview_f(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        crow_sv_f(cmsv_f(B,Bs,i,j),v,0);
        t=vsip_cvget_f(v,0);vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
        cprodHouse_f(cmsv_f(V,Vs,j,j),v);
        vsip_cvput_f(v,0,t);
    }      
    vsip_cvdestroy_f(v);
    vsip_cmdestroy_f(Vs);
    vsip_cmdestroy_f(Bs);
    return V;
}
static vsip_mview_d *UmatExtract_d(vsip_mview_d*B){
    vsip_stride i;
    vsip_length m = vsip_mgetcollength_d(B);
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_mview_d *U=meye_d(m);
    vsip_mview_d *Bs, *Us;
    vsip_vview_d *v;
    vsip_scalar_d t;
    v = vsip_mcolview_d(B,0);
    Bs=vsip_mcloneview_d(B);
    Us=vsip_mcloneview_d(U);
    if (m > n){
        i=n-1;
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
        houseProd_d(v,msv_d(U,Us,i,i));
        vsip_vput_d(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
        houseProd_d(v,msv_d(U,Us,i,i));
        vsip_vput_d(v,0,t);
    } 
    return U;
}
static vsip_cmview_d *cUmatExtract_d(vsip_cmview_d*B){
    vsip_stride i;
    vsip_length m = vsip_cmgetcollength_d(B);
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cmview_d *U=cmeye_d(m);
    vsip_cmview_d *Bs, *Us;
    vsip_cvview_d *v;
    vsip_cscalar_d t;
    v = vsip_cmcolview_d(B,0);
    Bs=vsip_cmcloneview_d(B);
    Us=vsip_cmcloneview_d(U);
    if (m > n){
        i=n-1;
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        chouseProd_d(v,cmsv_d(U,Us,i,i));
        vsip_cvput_d(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        chouseProd_d(v,cmsv_d(U,Us,i,i));
        vsip_cvput_d(v,0,t);
    } 
    return U;
}
static vsip_mview_d *VHmatExtract_d(vsip_mview_d*B){
    vsip_stride i;
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_mview_d *Bs; 
    vsip_mview_d *V=meye_d(n);
    vsip_mview_d *Vs;
    vsip_vview_d *v;
    vsip_scalar_d t;
    if(n < 3)
        return V;
    v = vsip_mrowview_d(B,0);
    Vs=vsip_mcloneview_d(V);
    Bs=vsip_mcloneview_d(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        row_sv_d(msv_d(B,Bs,i,j),v,0);
        t=vsip_vget_d(v,0);vsip_vput_d(v,0,1.0);
        prodHouse_d(msv_d(V,Vs,j,j),v);
        vsip_vput_d(v,0,t);
    }      
    vsip_vdestroy_d(v);
    vsip_mdestroy_d(Vs);
    vsip_mdestroy_d(Bs);
    return V;
}
static vsip_cmview_d *cVHmatExtract_d(vsip_cmview_d*B){
    vsip_stride i;
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cmview_d *Bs; 
    vsip_cmview_d *V=cmeye_d(n);
    vsip_cmview_d *Vs;
    vsip_cvview_d *v;
    vsip_cscalar_d t;
    if(n < 3)
        return V;
    v = vsip_cmrowview_d(B,0);
    Vs=vsip_cmcloneview_d(V);
    Bs=vsip_cmcloneview_d(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        crow_sv_d(cmsv_d(B,Bs,i,j),v,0);
        t=vsip_cvget_d(v,0);vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        cprodHouse_d(cmsv_d(V,Vs,j,j),v);
        vsip_cvput_d(v,0,t);
    }      
    vsip_cvdestroy_d(v);
    vsip_cmdestroy_d(Vs);
    vsip_cmdestroy_d(Bs);
    return V;
}

static void csvdZeroCheckAndSet_f(vsip_scalar_f e, vsip_cvview_f *b0, vsip_cvview_f *b1){
    vsip_index i;
    vsip_length n = vsip_cvgetlength_f(b1);
    vsip_cscalar_f z = vsip_cmplx_f(0.0,0.0);
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_cmag_f(vsip_cvget_f(b1,i));
        vsip_scalar_f a = e*(vsip_cmag_f(vsip_cvget_f(b0,i))
                        +    vsip_cmag_f(vsip_cvget_f(b0,i+1)));
        if( b < a ) vsip_cvput_f(b1,i,z);
    }
}
static void svdZeroCheckAndSet_f(vsip_scalar_f e, vsip_vview_f *b0, vsip_vview_f *b1){
    vsip_index i;
    vsip_length n = vsip_vgetlength_f(b1);
    vsip_scalar_f z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_mag_f(vsip_vget_f(b1,i));
        vsip_scalar_f a = e*(vsip_mag_f(vsip_vget_f(b0,i))
                        +    vsip_mag_f(vsip_vget_f(b0,i+1)));
        if( b < a ) vsip_vput_f(b1,i,z);
    }
}
static void csvdZeroCheckAndSet_d(vsip_scalar_d e, vsip_cvview_d *b0, vsip_cvview_d *b1){
    vsip_index i;
    vsip_length n = vsip_cvgetlength_d(b1);
    vsip_cscalar_d z = vsip_cmplx_d(0.0,0.0);
    for(i=0; i<n; i++){
        vsip_scalar_d b = vsip_cmag_d(vsip_cvget_d(b1,i));
        vsip_scalar_d a = e*(vsip_cmag_d(vsip_cvget_d(b0,i))
                        +    vsip_cmag_d(vsip_cvget_d(b0,i+1)));
        if( b < a ) vsip_cvput_d(b1,i,z);
    }
}
static void svdZeroCheckAndSet_d(vsip_scalar_d e, vsip_vview_d *b0, vsip_vview_d *b1){
    vsip_index i;
    vsip_length n = vsip_vgetlength_d(b1);
    vsip_scalar_d z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_d b = vsip_mag_d(vsip_vget_d(b1,i));
        vsip_scalar_d a = e*(vsip_mag_d(vsip_vget_d(b0,i))
                        +    vsip_mag_d(vsip_vget_d(b0,i+1)));
        if( b < a ) vsip_vput_d(b1,i,z);
    }
}
static void biDiagPhaseToZero_f(
      vsip_mview_f *L,
      vsip_vview_f *d,
      vsip_vview_f *f,
      vsip_mview_f *R,
      vsip_scalar_f eps0)
{
   vsip_length n_d=vsip_vgetlength_f(d);
   vsip_length n_f=vsip_vgetlength_f(f);
   vsip_index i,j;
   vsip_scalar_f ps;
   vsip_scalar_f m;
   vsip_vview_f *l = vsip_mcolview_f(L,0);
   vsip_vview_f *r = vsip_mrowview_f(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_vget_f(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            col_sv_f(L,l,i);vsip_svmul_f(ps,l,l);
            vsip_vput_f(d,i,m);
            if (i < n_f)
                vsip_vput_f(f,i,ps*vsip_vget_f(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_vget_f(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        col_sv_f(L, l, j);vsip_svmul_f(ps,l,l);
        row_sv_f(R,r,j);vsip_svmul_f(ps,r,r);
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * vsip_vget_f(f,j));
    }
    j=n_f;
    i=j-1;
    ps=vsip_vget_f(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    col_sv_f(L, l, j);vsip_svmul_f(ps,l,l);
    row_sv_f(R,r,j);vsip_svmul_f(ps,r,r);
    vsip_vdestroy_f(l);
    vsip_vdestroy_f(r);
}
static void cbiDiagPhaseToZero_f(
      vsip_cmview_f *L,
      vsip_cvview_f *d,
      vsip_cvview_f *f,
      vsip_cmview_f *R,
      vsip_scalar_f eps0)
{
   vsip_length n_d=vsip_cvgetlength_f(d);
   vsip_length n_f=vsip_cvgetlength_f(f);
   vsip_index i,j;
   vsip_cscalar_f ps;
   vsip_scalar_f m;
   vsip_cvview_f *l = vsip_cmcolview_f(L,0);
   vsip_cvview_f *r = vsip_cmrowview_f(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_cvget_f(d,i);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_f(-1.0,0.0);
            else
                ps= vsip_cmplx_f(1.0,0.0);
            m = vsip_mag_f(m); 
        } else {
            m=vsip_cmag_f(ps);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_csvmul_f(ps,l,l);
            vsip_cvput_f(d,i,vsip_cmplx_f(m,0));
            if (i < n_f)
                vsip_cvput_f(f,i,vsip_cjmul_f(vsip_cvget_f(f,i),ps));
        }else{
            vsip_cvput_f(d,i,vsip_cmplx_f(0.0,0.0));
        }
    }
    csvdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_cvget_f(f,i);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_f(-1.0,0.0);
            else
                ps= vsip_cmplx_f(1.0,0.0);
            m = vsip_mag_f(m);
        }else{
            m=vsip_cmag_f(ps);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
        crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
        vsip_cvput_f(f,i,vsip_cmplx_f(m,0));
        vsip_cvput_f(f,j,vsip_cmul_f(vsip_cvget_f(f,j),ps));
    }
    j=n_f;
    i=j-1;
    ps=vsip_cvget_f(f,i);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps=vsip_cmplx_f(-1.0,0.0);
        else
            ps= vsip_cmplx_f(1.0,0.0);
        m = vsip_mag_f(m);
    }else{
        m=vsip_cmag_f(ps);
        ps.r /= m; ps.i/=m;
    }
    vsip_cvput_f(f,i,vsip_cmplx_f(m,0.0));
    ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
    crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
    vsip_cvdestroy_f(l);
    vsip_cvdestroy_f(r);
}
static void biDiagPhaseToZero_d(
      vsip_mview_d *L,
      vsip_vview_d *d,
      vsip_vview_d *f,
      vsip_mview_d *R,
      vsip_scalar_d eps0)
{
   vsip_length n_d=vsip_vgetlength_d(d);
   vsip_length n_f=vsip_vgetlength_d(f);
   vsip_index i,j;
   vsip_scalar_d ps;
   vsip_scalar_d m;
   vsip_vview_d *l = vsip_mcolview_d(L,0);
   vsip_vview_d *r = vsip_mrowview_d(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_vget_d(d,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        if(m > eps0){
            col_sv_d(L,l,i);vsip_svmul_d(ps,l,l);
            vsip_vput_d(d,i,m);
            if (i < n_d)
                vsip_vput_d(f,i,ps*vsip_vget_d(f,i));
        } else {
            vsip_vput_d(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_vget_d(f,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        col_sv_d(L, l, j);vsip_svmul_d(ps,l,l);
        row_sv_d(R,r,j);vsip_svmul_d(ps,r,r);
        vsip_vput_d(f,i,m);
        vsip_vput_d(f,j,ps * vsip_vget_d(f,j));
    }
    j=n_f;
    i=j-1;
    ps=vsip_vget_d(f,i);
    m=vsip_mag_d(ps);
    ps=sign_d(ps);
    vsip_vput_d(f,i,m);
    col_sv_d(L, l, j);vsip_svmul_d(ps,l,l);
    row_sv_d(R,r,j);vsip_svmul_d(ps,r,r);
    vsip_vdestroy_d(l);
    vsip_vdestroy_d(r);
}
static void cbiDiagPhaseToZero_d(
      vsip_cmview_d *L,
      vsip_cvview_d *d,
      vsip_cvview_d *f,
      vsip_cmview_d *R,
      vsip_scalar_d eps0)
{
   vsip_length n_d=vsip_cvgetlength_d(d);
   vsip_length n_f=vsip_cvgetlength_d(f);
   vsip_index i,j;
   vsip_cscalar_d ps;
   vsip_scalar_d m;
   vsip_cvview_d *l = vsip_cmcolview_d(L,0);
   vsip_cvview_d *r = vsip_cmrowview_d(R,0);
   for(i=0; i<n_d; i++){
        ps=vsip_cvget_d(d,i);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_d(-1.0,0.0);
            else
                ps= vsip_cmplx_d(1.0,0.0);
            m = vsip_mag_d(m); 
        } else {
            m=vsip_cmag_d(ps);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_d(L,l,i);vsip_csvmul_d(ps,l,l);
            vsip_cvput_d(d,i,vsip_cmplx_d(m,0));
            if (i < n_f)
                vsip_cvput_d(f,i,vsip_cjmul_d(vsip_cvget_d(f,i),ps));
        }else{
            vsip_cvput_d(d,i,vsip_cmplx_d(0.0,0.0));
        }
    }
    csvdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_cvget_d(f,i);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_d(-1.0,0.0);
            else
                ps= vsip_cmplx_d(1.0,0.0);
            m = vsip_mag_d(m);
        }else{
            m=vsip_cmag_d(ps);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_d(L, l, j);vsip_csvmul_d(vsip_conj_d(ps),l,l);
        crow_sv_d(R,r,j);vsip_csvmul_d(ps,r,r);
        vsip_cvput_d(f,i,vsip_cmplx_d(m,0));
        vsip_cvput_d(f,j,vsip_cmul_d(vsip_cvget_d(f,j),ps));
    }
    j=n_f;
    i=j-1;
    ps=vsip_cvget_d(f,i);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps=vsip_cmplx_d(-1.0,0.0);
        else
            ps= vsip_cmplx_d(1.0,0.0);
        m = vsip_mag_d(m);
    }else{
        m=vsip_cmag_d(ps);
        ps.r /= m; ps.i/=m;
    }
    vsip_cvput_d(f,i,vsip_cmplx_d(m,0.0));
    ccol_sv_d(L, l, j);vsip_csvmul_d(vsip_conj_d(ps),l,l);
    crow_sv_d(R,r,j);vsip_csvmul_d(ps,r,r);
    vsip_cvdestroy_d(l);
    vsip_cvdestroy_d(r);
}

static svdObj_f svdBidiag_f(vsip_mview_f* A)
{
    svdObj_f retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_f sv = mnormFro_f(A)/(vsip_scalar_f)vsip_mgetrowlength_f(A);
    vsip_mview_f *B=bidiag_f(A); 
    vsip_vview_f *d0=NULL,*f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) d0=vsip_mdiagview_f(B,0); if(!d0) retval.init++;
    if(B) f0=vsip_mdiagview_f(B,1); if(!f0) retval.init++;
    retval.d=vclone_f(d0); if(!retval.d) retval.init++;
    retval.f=vclone_f(f0); if(!retval.f) retval.init++;
    if(B) retval.L=UmatExtract_f(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=VHmatExtract_f(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-10;
    vsip_vdestroy_f(d0);
    vsip_vdestroy_f(f0);
    vsip_malldestroy_f(B);
    biDiagPhaseToZero_f(retval.L,retval.d,retval.f,retval.R,retval.eps0);
    return retval;
}
static csvdObj_f csvdBidiag_f(vsip_cmview_f* A)
{
    csvdObj_f retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_f sv = cmnormFro_f(A)/(vsip_scalar_f)vsip_cmgetrowlength_f(A);
    vsip_cmview_f *B=cbidiag_f(A);
    vsip_cvview_f *dc=NULL,*fc=NULL;
    vsip_vview_f *d0=NULL, *f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) dc=vsip_cmdiagview_f(B,0); if(!dc) retval.init++;
    if(dc) d0=vsip_vrealview_f(dc); if(!d0) retval.init++;
    if(B) fc=vsip_cmdiagview_f(B,1); if(!fc) retval.init++;
    if(fc) f0 = vsip_vrealview_f(fc); if(!f0) retval.init++;
    if(B) retval.L=cUmatExtract_f(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=cVHmatExtract_f(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-10;
    cbiDiagPhaseToZero_f(retval.L,dc,fc,retval.R,retval.eps0);
    retval.d=vclone_f(d0); if(!retval.d) retval.init++;
    retval.f=vclone_f(f0); if(!retval.f) retval.init++;
    vsip_vdestroy_f(d0);
    vsip_vdestroy_f(f0);
    vsip_cvdestroy_f(dc);
    vsip_cvdestroy_f(fc);
    vsip_cmalldestroy_f(B);
    return retval;
}
static svdObj_d svdBidiag_d(vsip_mview_d* A)
{
    svdObj_d retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_d sv = mnormFro_d(A)/(vsip_scalar_d)vsip_mgetrowlength_d(A);
    vsip_mview_d *B=bidiag_d(A); 
    vsip_vview_d *d0=NULL,*f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) d0=vsip_mdiagview_d(B,0); if(!d0) retval.init++;
    if(B) f0=vsip_mdiagview_d(B,1); if(!f0) retval.init++;
    retval.d=vclone_d(d0); if(!retval.d) retval.init++;
    retval.f=vclone_d(f0); if(!retval.f) retval.init++;
    if(B) retval.L=UmatExtract_d(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=VHmatExtract_d(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-10;
    vsip_vdestroy_d(d0);
    vsip_vdestroy_d(f0);
    vsip_malldestroy_d(B);
    biDiagPhaseToZero_d(retval.L,retval.d,retval.f,retval.R,retval.eps0);
    return retval;
}
static csvdObj_d csvdBidiag_d(vsip_cmview_d* A)
{
    csvdObj_d retval;
    /* sv is a number < maximum singular value */
    vsip_scalar_d sv = cmnormFro_d(A)/(vsip_scalar_d)vsip_cmgetrowlength_d(A);
    vsip_cmview_d *B=cbidiag_d(A);
    vsip_cvview_d *dc=NULL,*fc=NULL;
    vsip_vview_d *d0=NULL, *f0=NULL;
    retval.init=0;
    if(!B) retval.init++;
    if(B) dc=vsip_cmdiagview_d(B,0); if(!dc) retval.init++;
    if(dc) d0=vsip_vrealview_d(dc); if(!d0) retval.init++;
    if(B) fc=vsip_cmdiagview_d(B,1); if(!fc) retval.init++;
    if(fc) f0 = vsip_vrealview_d(fc); if(!f0) retval.init++;
    if(B) retval.L=cUmatExtract_d(B); else retval.L=NULL; if(!retval.L) retval.init++;
    if(B) retval.R=cVHmatExtract_d(B); else retval.R=NULL; if(!retval.R) retval.init++;
    /* eps0 is a number << maximum singular value */
    retval.eps0=sv*1E-10;
    cbiDiagPhaseToZero_d(retval.L,dc,fc,retval.R,retval.eps0);
    retval.d=vclone_d(d0); if(!retval.d) retval.init++;
    retval.f=vclone_d(f0); if(!retval.f) retval.init++;
    vsip_vdestroy_d(d0);
    vsip_vdestroy_d(f0);
    vsip_cvdestroy_d(dc);
    vsip_cvdestroy_d(fc);
    vsip_cmalldestroy_d(B);
    return retval;
}
/* for SVD Givens Coefficients are only calculated for real numbers */
static givensObj_f givensCoef_f(vsip_scalar_f x1, vsip_scalar_f x2)
{
    givensObj_f retval;
    vsip_scalar_f t = vsip_hypot_f(x1,x2);
    if (x2 == 0.0){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0) {
        retval.c=0.0;retval.s=sign_f(x2);retval.r=t;
    }else{
        vsip_scalar_f sn = sign_f(x1);
        retval.c=vsip_mag_f(x1)/t;retval.s=sn*x2/t; retval.r=sn*t;
    }
    return retval;
}
static givensObj_d givensCoef_d(vsip_scalar_d x1, vsip_scalar_d x2)
{
    givensObj_d retval;
    vsip_scalar_d t = vsip_hypot_d(x1,x2);
    if (x2 == 0.0){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0) {
        retval.c=0.0;retval.s=sign_d(x2);retval.r=t;
    }else{
        vsip_scalar_d sn = sign_d(x1);
        retval.c=vsip_mag_d(x1)/t;retval.s=sn * x2/t; retval.r=sn*t;
    }
    return retval;
}
static svdCorner svdCorners_f(vsip_vview_f* f)
{
    svdCorner crnr;
    vsip_index j=vsip_vgetlength_f(f)-1;
    vsip_index i;
    while((j > 0) && (vsip_vget_f(f,j) == 0.0))
        j-=1;
    if(j == 0 && vsip_vget_f(f,0) == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        j += 1;
        while((i > 0) && (vsip_vget_f(f,i) != 0.0))
            i -= 1;
        if((i == 0) && (vsip_vget_f(f,0)== 0.0)){
            crnr.i=1;
            crnr.j=j+1;
        } else if (i==0){
            crnr.i=0;
            crnr.j=j+1;
        } else {
            crnr.i=i+1;
            crnr.j=j+1;
        }
    }
    return crnr;
}
static svdCorner svdCorners_d(vsip_vview_d* f)
{
    svdCorner crnr;
    vsip_index j=vsip_vgetlength_d(f)-1;
    vsip_index i;
    while((j > 0) && (vsip_vget_d(f,j) == 0.0))
        j-=1;
    if(j == 0 && vsip_vget_d(f,0) == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        j += 1;
        while((i > 0) && (vsip_vget_d(f,i) != 0.0))
            i -= 1;
        if((i == 0) && (vsip_vget_d(f,0)== 0.0)){
            crnr.i=1;
            crnr.j=j+1;
        } else if (i==0){
            crnr.i=0;
            crnr.j=j+1;
        } else {
            crnr.i=i+1;
            crnr.j=j+1;
        }
    }
    return crnr;
}
static void phaseCheck_f(vsip_mview_f* L,vsip_vview_f* d,vsip_vview_f* f,vsip_mview_f* R,vsip_scalar_f eps0)
{
    biDiagPhaseToZero_f(L,d,f,R,eps0);
}
static void cphaseCheck_f(vsip_cmview_f* L, vsip_vview_f* d, vsip_vview_f* f,vsip_cmview_f* R, vsip_scalar_f eps0)
{
   vsip_length nf=vsip_vgetlength_f(f);
   vsip_index i,j;
   vsip_scalar_f ps;
   vsip_scalar_f m;
   vsip_cvview_f *l = vsip_cmcolview_f(L,0);
   vsip_cvview_f *r = vsip_cmrowview_f(R,0);
   for(i=0; i<vsip_vgetlength_f(d); i++){
        ps=vsip_vget_f(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_rscvmul_f(ps,l,l);
            vsip_vput_f(d,i,m);
            if (i < nf)
                vsip_vput_f(f,i,ps*vsip_vget_f(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps = vsip_vget_f(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        ccol_sv_f(L, l, j);vsip_rscvmul_f(ps,l,l);
        crow_sv_f(R,r,j);vsip_rscvmul_f(ps,r,r);
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * vsip_vget_f(f,j));
    }
    j=nf;
    i=j-1;
    ps=vsip_vget_f(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    ccol_sv_f(L, l, j);vsip_rscvmul_f(ps,l,l);
    crow_sv_f(R,r,j);vsip_rscvmul_f(ps,r,r);
}
static void phaseCheck_d(vsip_mview_d* L,vsip_vview_d* d,vsip_vview_d* f,vsip_mview_d* R,vsip_scalar_d eps0)
{
    biDiagPhaseToZero_d(L,d,f,R,eps0);
}
static void cphaseCheck_d(vsip_cmview_d* L, vsip_vview_d* d, vsip_vview_d* f,vsip_cmview_d* R, vsip_scalar_d eps0)
{
   vsip_length nf=vsip_vgetlength_d(f);
   vsip_index i,j;
   vsip_scalar_d ps;
   vsip_scalar_d m;
   vsip_cvview_d *l = vsip_cmcolview_d(L,0);
   vsip_cvview_d *r = vsip_cmrowview_d(R,0);
   for(i=0; i<vsip_vgetlength_d(d); i++){
        ps=vsip_vget_d(d,i);
        m = vsip_mag_f(ps);
        ps=sign_d(ps);
        if(m > eps0){
            ccol_sv_d(L,l,i);vsip_rscvmul_d(ps,l,l);
            vsip_vput_d(d,i,m);
            if (i < nf)
                vsip_vput_d(f,i,ps*vsip_vget_d(f,i));
        } else {
            vsip_vput_d(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps = vsip_vget_d(f,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        ccol_sv_d(L, l, j);vsip_rscvmul_d(ps,l,l);
        crow_sv_d(R,r,j);vsip_rscvmul_d(ps,r,r);
        vsip_vput_d(f,i,m);
        vsip_vput_d(f,j,ps * vsip_vget_d(f,j));
    }
    j=nf;
    i=j-1;
    ps=vsip_vget_d(f,i);
    m=vsip_mag_d(ps);
    ps=sign_d(ps);
    vsip_vput_d(f,i,m);
    ccol_sv_d(L, l, j);vsip_rscvmul_d(ps,l,l);
    crow_sv_d(R,r,j);vsip_rscvmul_d(ps,r,r);
}
static vsip_index zeroFind_f(vsip_vview_f* d, vsip_scalar_f eps0){
    vsip_index j = vsip_vgetlength_f(d);
    vsip_scalar_f xd=vsip_vget_f(d,j-1);
    while(xd > eps0){
        if (j > 1){ 
            j -= 1;
            xd=vsip_vget_f(d,j-1);
        }else{
            break;
        }
    }
    if(xd <= eps0)
        vsip_vput_f(d,j-1,0.0);
    if (j == 1)
        j=0;
    return j;
}

static vsip_index zeroFind_d(vsip_vview_d* d, vsip_scalar_d eps0){
    vsip_index j = vsip_vgetlength_d(d);
    vsip_scalar_d xd=vsip_vget_d(d,j-1);
    while(xd > eps0){
        if (j > 1){ 
            j -= 1;
            xd=vsip_vget_d(d,j-1);
        }else{
            break;
        }
    }
    if(xd <= eps0)
        vsip_vput_d(d,j-1,0.0);
    if (j == 1)
        j=0;
    return j;
}

static void zeroRow_f(vsip_mview_f* L,vsip_vview_f *d,vsip_vview_f *f)
{
    vsip_length n = vsip_vgetlength_f(d);
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i;
    xd=vsip_vget_f(d,0);
    xf=vsip_vget_f(f,0);
    g=givensCoef_f(xd,xf);
    if (n == 1){
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
    }else{
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
        xf=vsip_vget_f(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,1,xf);
        prodG_f(L,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            prodG_f(L,i+1,0,g.c,g.s);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_f(f,i+1,xf);
        }
        xd=vsip_vget_f(d,n-1);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,n-1,g.r);
        prodG_f(L,n,0,g.c,g.s);
    }
}
static void zeroCol_f(vsip_vview_f *d,vsip_vview_f *f, vsip_mview_f* R)
{
    vsip_length n = vsip_vgetlength_f(f);
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=vsip_vget_f(d,0);
        xf=vsip_vget_f(f,0);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,0,g.r);
        vsip_vput_f(f,0,0.0);
        gtProd_f(0,1,g.c,g.s,R);
    }else if (n == 2){
        xd=vsip_vget_f(d,1);
        xf=vsip_vget_f(f,1);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,1,g.r);
        vsip_vput_f(f,1,0.0);
        xf=vsip_vget_f(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,0,xf);
        gtProd_f(1,2,g.c,g.s,R);
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,2,g.c,g.s,R);
    }else{
        i=n-1; j=i-1; k=i;
        xd=vsip_vget_f(d,i);
        xf=vsip_vget_f(f,i);
        g=givensCoef_f(xd,xf);
        xf=vsip_vget_f(f,j);
        vsip_vput_f(f,i,0.0);
        vsip_vput_f(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_f(f,j,xf);
        gtProd_f(i,k+1,g.c,g.s,R);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_f(f,j,xf);
            gtProd_f(i,k+1,g.c,g.s,R);
        }
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,k+1,g.c,g.s,R);
    }
}
static void zeroRow_d(vsip_mview_d* L,vsip_vview_d *d,vsip_vview_d *f)
{
    vsip_length n = vsip_vgetlength_d(d);
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=vsip_vget_d(d,0);
    xf=vsip_vget_d(f,0);
    g=givensCoef_d(xd,xf);
    if (n == 1){
        vsip_vput_d(f,0,0.0);
        vsip_vput_d(d,0,g.r);
    }else{
        vsip_vput_d(f,0,0.0);
        vsip_vput_d(d,0,g.r);
        xf=vsip_vget_d(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,1,xf);
        prodG_d(L,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            prodG_d(L,i+1,0,g.c,g.s);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_d(f,i+1,xf);
        }
        xd=vsip_vget_d(d,n-1);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,n-1,g.r);
        prodG_d(L,n,0,g.c,g.s);
    }
}
static void zeroCol_d(vsip_vview_d *d,vsip_vview_d *f, vsip_mview_d* R)
{
    vsip_length n = vsip_vgetlength_d(f);
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=vsip_vget_d(d,0);
        xf=vsip_vget_d(f,0);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,0,g.r);
        vsip_vput_d(f,0,0.0);
        gtProd_d(0,1,g.c,g.s,R);
    }else if (n == 2){
        xd=vsip_vget_d(d,1);
        xf=vsip_vget_d(f,1);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,1,g.r);
        vsip_vput_d(f,1,0.0);
        xf=vsip_vget_d(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,0,xf);
        gtProd_d(1,2,g.c,g.s,R);
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        gtProd_d(0,2,g.c,g.s,R);
    }else{
        i=n-1; j=i-1; k=i;
        xd=vsip_vget_d(d,i);
        xf=vsip_vget_d(f,i);
        g=givensCoef_d(xd,xf);
        xf=vsip_vget_d(f,j);
        vsip_vput_d(f,i,0.0);
        vsip_vput_d(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_d(f,j,xf);
        gtProd_d(i,k+1,g.c,g.s,R);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_d(f,j,xf);
            gtProd_d(i,k+1,g.c,g.s,R);
        }
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        gtProd_d(0,k+1,g.c,g.s,R);
    }
}
static void czeroRow_f(vsip_cmview_f* L,vsip_vview_f *d,vsip_vview_f *f)
{
    vsip_length n = vsip_vgetlength_f(d);
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i;
    xd=vsip_vget_f(d,0);
    xf=vsip_vget_f(f,0);
    g=givensCoef_f(xd,xf);
    if (n == 1){
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
    }else{
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
        xf=vsip_vget_f(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,1,xf);
        cprodG_f(L,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            cprodG_f(L,i+1,0,g.c,g.s);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_f(f,i+1,xf);
        }
        xd=vsip_vget_f(d,n-1);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,n-1,g.r);
        cprodG_f(L,n,0,g.c,g.s);
    }
}
static void czeroCol_f(vsip_vview_f *d,vsip_vview_f *f, vsip_cmview_f* R)
{
    vsip_length n = vsip_vgetlength_f(f);
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=vsip_vget_f(d,0);
        xf=vsip_vget_f(f,0);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,0,g.r);
        vsip_vput_f(f,0,0.0);
        cgtProd_f(0,1,g.c,g.s,R);
    }else if (n == 2){
        xd=vsip_vget_f(d,1);
        xf=vsip_vget_f(f,1);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,1,g.r);
        vsip_vput_f(f,1,0.0);
        xf=vsip_vget_f(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,0,xf);
        cgtProd_f(1,2,g.c,g.s,R);
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        cgtProd_f(0,2,g.c,g.s,R);
    }else{
        i=n-1; j=i-1; k=i;
        xd=vsip_vget_f(d,i);
        xf=vsip_vget_f(f,i);
        g=givensCoef_f(xd,xf);
        xf=vsip_vget_f(f,j);
        vsip_vput_f(f,i,0.0);
        vsip_vput_f(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_f(f,j,xf);
        cgtProd_f(i,k+1,g.c,g.s,R);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_f(f,j,xf);
            cgtProd_f(i,k+1,g.c,g.s,R);
        }
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        cgtProd_f(0,k+1,g.c,g.s,R);
    }
}
static void czeroRow_d(vsip_cmview_d* L,vsip_vview_d *d,vsip_vview_d *f)
{
    vsip_length n = vsip_vgetlength_d(d);
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=vsip_vget_d(d,0);
    xf=vsip_vget_d(f,0);
    g=givensCoef_d(xd,xf);
    if (n == 1){
        vsip_vput_d(f,0,0.0);
        vsip_vput_d(d,0,g.r);
    }else{
        vsip_vput_d(f,0,0.0);
        vsip_vput_d(d,0,g.r);
        xf=vsip_vget_d(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,1,xf);
        cprodG_d(L,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            cprodG_d(L,i+1,0,g.c,g.s);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_d(f,i+1,xf);
        }
        xd=vsip_vget_d(d,n-1);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,n-1,g.r);
        cprodG_d(L,n,0,g.c,g.s);
    }
}
static void czeroCol_d(vsip_vview_d *d,vsip_vview_d *f, vsip_cmview_d* R)
{
    vsip_length n = vsip_vgetlength_d(f);
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=vsip_vget_d(d,0);
        xf=vsip_vget_d(f,0);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,0,g.r);
        vsip_vput_d(f,0,0.0);
        cgtProd_d(0,1,g.c,g.s,R);
    }else if (n == 2){
        xd=vsip_vget_d(d,1);
        xf=vsip_vget_d(f,1);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,1,g.r);
        vsip_vput_d(f,1,0.0);
        xf=vsip_vget_d(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,0,xf);
        cgtProd_d(1,2,g.c,g.s,R);
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        cgtProd_d(0,2,g.c,g.s,R);
    }else{
        i=n-1; j=i-1; k=i;
        xd=vsip_vget_d(d,i);
        xf=vsip_vget_d(f,i);
        g=givensCoef_d(xd,xf);
        xf=vsip_vget_d(f,j);
        vsip_vput_d(f,i,0.0);
        vsip_vput_d(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_d(f,j,xf);
        cgtProd_d(i,k+1,g.c,g.s,R);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_d(f,j,xf);
            cgtProd_d(i,k+1,g.c,g.s,R);
        }
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        cgtProd_d(0,k+1,g.c,g.s,R);
    }

}
static vsip_scalar_f svdMu_f(vsip_scalar_f d2,vsip_scalar_f f1,vsip_scalar_f d3,vsip_scalar_f f2)
{
    vsip_scalar_f mu;
    vsip_scalar_f cu=d2 * d2 + f1 * f1;
    vsip_scalar_f cl=d3 * d3 + f2 * f2;
    vsip_scalar_f cd = d2 * f2;
    vsip_scalar_f D = (cu * cl - cd * cd);
    vsip_scalar_f T = (cu + cl);
    vsip_scalar_f root = vsip_sqrt_f(T*T - 4 * D);
    vsip_scalar_f lambda1 = (T + root)/(2.); 
    vsip_scalar_f lambda2 = (T - root)/(2.);
    if(vsip_mag_f(lambda1 - cl) < vsip_mag_f(lambda2 - cl))
        mu = lambda1;
    else
        mu = lambda2;
    return mu;
}
static vsip_scalar_d svdMu_d(vsip_scalar_d d2,vsip_scalar_d f1,vsip_scalar_d d3,vsip_scalar_d f2)
{
    vsip_scalar_d mu;
    vsip_scalar_d cu=d2 * d2 + f1 * f1;
    vsip_scalar_d cl=d3 * d3 + f2 * f2;
    vsip_scalar_d cd = d2 * f2;
    vsip_scalar_d D = (cu * cl - cd * cd);
    vsip_scalar_d T = (cu + cl);
    vsip_scalar_d root = vsip_sqrt_d(T*T - 4 * D);
    vsip_scalar_d lambda1 = (T + root)/(2.); 
    vsip_scalar_d lambda2 = (T - root)/(2.);
    if(vsip_mag_d(lambda1 - cl) < vsip_mag_d(lambda2 - cl))
        mu = lambda1;
    else
        mu = lambda2;
    return mu;
}


static void svdStep_f(vsip_mview_f* L, vsip_vview_f* d, vsip_vview_f* f, vsip_mview_f *R)
{
    givensObj_f g;
    vsip_length n = vsip_vgetlength_f(d);
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_f(d,n-2);f1= vsip_vget_f(f,n-3);d3 = vsip_vget_f(d,n-1);f2= vsip_vget_f(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_f(d,0);f1= 0.0;d3 = vsip_vget_f(d,1);f2= vsip_vget_f(f,0);
    } else {
        d2=vsip_vget_f(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_f(d2,f1,d3,f2);
    x1=vsip_vget_f(d,0);
    x2 = x1 * vsip_vget_f(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_f(x1,x2);
    x1=vsip_vget_f(d,0);x2=vsip_vget_f(f,0);
    vsip_vput_f(f,0,g.c * x2 - g.s * x1);
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_f(d,1); vsip_vput_f(d,1,t*g.c);
    t*=g.s;
    gtProd_f(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(vsip_vget_f(d,i),t);
        vsip_vput_f(d,i,g.r);      
        x1=vsip_vget_f(d,j)*g.c; 
        x2=vsip_vget_f(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_f(f,i) * g.c;
        x2=vsip_vget_f(d,j) * g.s ;      
        vsip_vput_f(f,i,x1+x2);
        vsip_vput_f(d,j,t);       
        x1=vsip_vget_f(f,j);
        t=g.s * x1; 
        vsip_vput_f(f,j, x1*g.c);
        prodG_f(L,i, j, g.c, g.s);
        g=givensCoef_f(vsip_vget_f(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=vsip_vget_f(d,j); x2=vsip_vget_f(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_f(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        gtProd_f(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(vsip_vget_f(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=vsip_vget_f(d,j)*g.c; x2=vsip_vget_f(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_f(f,i) * g.c; x2=vsip_vget_f(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
    prodG_f(L,i, j, g.c, g.s);
}
static void csvdStep_f(vsip_cmview_f* L, vsip_vview_f* d, vsip_vview_f* f, vsip_cmview_f *R)
{
    givensObj_f g;
    vsip_length n = vsip_vgetlength_f(d);
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_f(d,n-2);f1= vsip_vget_f(f,n-3);d3 = vsip_vget_f(d,n-1);f2= vsip_vget_f(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_f(d,0);f1= 0.0;d3 = vsip_vget_f(d,1);f2= vsip_vget_f(f,0);
    } else {
        d2=vsip_vget_f(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_f(d2,f1,d3,f2);
    x1=vsip_vget_f(d,0);
    x2 = x1 * vsip_vget_f(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_f(x1,x2);
    x1=vsip_vget_f(d,0);x2=vsip_vget_f(f,0);
    vsip_vput_f(f,0,g.c * x2 - g.s * x1);
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_f(d,1); vsip_vput_f(d,1,t*g.c);
    t*=g.s;
    cgtProd_f(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(vsip_vget_f(d,i),t);
        vsip_vput_f(d,i,g.r);      
        x1=vsip_vget_f(d,j)*g.c; 
        x2=vsip_vget_f(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_f(f,i) * g.c;
        x2=vsip_vget_f(d,j) * g.s ;      
        vsip_vput_f(f,i,x1+x2);
        vsip_vput_f(d,j,t);       
        x1=vsip_vget_f(f,j);
        t=g.s * x1; 
        vsip_vput_f(f,j, x1*g.c);
        cprodG_f(L,i, j, g.c, g.s);
        g=givensCoef_f(vsip_vget_f(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=vsip_vget_f(d,j); x2=vsip_vget_f(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_f(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        cgtProd_f(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(vsip_vget_f(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=vsip_vget_f(d,j)*g.c; x2=vsip_vget_f(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_f(f,i) * g.c; x2=vsip_vget_f(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
    cprodG_f(L,i, j, g.c, g.s);
}
static void svdStep_d(vsip_mview_d* L, vsip_vview_d* d, vsip_vview_d* f, vsip_mview_d *R)
{
    givensObj_d g;
    vsip_length n = vsip_vgetlength_d(d);
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_d(d,n-2);f1= vsip_vget_d(f,n-3);d3 = vsip_vget_d(d,n-1);f2= vsip_vget_d(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_d(d,0);f1= 0.0;d3 = vsip_vget_d(d,1);f2= vsip_vget_d(f,0);
    } else {
        d2=vsip_vget_d(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_d(d2,f1,d3,f2);
    x1=vsip_vget_d(d,0);
    x2 = x1 * vsip_vget_d(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_d(x1,x2);
    x1=vsip_vget_d(d,0);x2=vsip_vget_d(f,0);
    vsip_vput_d(f,0,g.c * x2 - g.s * x1);
    vsip_vput_d(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_d(d,1); vsip_vput_d(d,1,t*g.c);
    t*=g.s;
    gtProd_d(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(vsip_vget_d(d,i),t);
        vsip_vput_d(d,i,g.r);      
        x1=vsip_vget_d(d,j)*g.c; 
        x2=vsip_vget_d(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_d(f,i) * g.c;
        x2=vsip_vget_d(d,j) * g.s ;      
        vsip_vput_d(f,i,x1+x2);
        vsip_vput_d(d,j,t);       
        x1=vsip_vget_d(f,j);
        t=g.s * x1; 
        vsip_vput_d(f,j, x1*g.c);
        prodG_d(L,i, j, g.c, g.s);
        g=givensCoef_d(vsip_vget_d(f,i),t);
        vsip_vput_d(f,i,g.r);
        x1=vsip_vget_d(d,j); x2=vsip_vget_d(f,j);
        vsip_vput_d(d,j,g.c * x1 + g.s * x2); vsip_vput_d(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_d(d,k);
        t=g.s * x1; vsip_vput_d(d,k,x1*g.c);
        gtProd_d(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(vsip_vget_d(d,i),t);
    vsip_vput_d(d,i,g.r);
    x1=vsip_vget_d(d,j)*g.c; x2=vsip_vget_d(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_d(f,i) * g.c; x2=vsip_vget_d(d,j) * g.s;
    vsip_vput_d(f,i,x1+x2);
    vsip_vput_d(d,j,t);
    prodG_d(L,i, j, g.c, g.s);
}
static void csvdStep_d(vsip_cmview_d* L, vsip_vview_d* d, vsip_vview_d* f, vsip_cmview_d *R)
{
    givensObj_d g;
    vsip_length n = vsip_vgetlength_d(d);
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_d(d,n-2);f1= vsip_vget_d(f,n-3);d3 = vsip_vget_d(d,n-1);f2= vsip_vget_d(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_d(d,0);f1= 0.0;d3 = vsip_vget_d(d,1);f2= vsip_vget_d(f,0);
    } else {
        d2=vsip_vget_d(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_d(d2,f1,d3,f2);
    x1=vsip_vget_d(d,0);
    x2 = x1 * vsip_vget_d(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_d(x1,x2);
    x1=vsip_vget_d(d,0);x2=vsip_vget_d(f,0);
    vsip_vput_d(f,0,g.c * x2 - g.s * x1);
    vsip_vput_d(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_d(d,1); vsip_vput_d(d,1,t*g.c);
    t*=g.s;
    cgtProd_d(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(vsip_vget_d(d,i),t);
        vsip_vput_d(d,i,g.r);      
        x1=vsip_vget_d(d,j)*g.c; 
        x2=vsip_vget_d(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_d(f,i) * g.c;
        x2=vsip_vget_d(d,j) * g.s ;      
        vsip_vput_d(f,i,x1+x2);
        vsip_vput_d(d,j,t);       
        x1=vsip_vget_d(f,j);
        t=g.s * x1; 
        vsip_vput_d(f,j, x1*g.c);
        cprodG_d(L,i, j, g.c, g.s);
        g=givensCoef_d(vsip_vget_d(f,i),t);
        vsip_vput_d(f,i,g.r);
        x1=vsip_vget_d(d,j); x2=vsip_vget_d(f,j);
        vsip_vput_d(d,j,g.c * x1 + g.s * x2); vsip_vput_d(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_d(d,k);
        t=g.s * x1; vsip_vput_d(d,k,x1*g.c);
        cgtProd_d(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(vsip_vget_d(d,i),t);
    vsip_vput_d(d,i,g.r);
    x1=vsip_vget_d(d,j)*g.c; x2=vsip_vget_d(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_d(f,i) * g.c; x2=vsip_vget_d(d,j) * g.s;
    vsip_vput_d(f,i,x1+x2);
    vsip_vput_d(d,j,t);
    cprodG_d(L,i, j, g.c, g.s);
}

static void svdIteration_f(vsip_mview_f* L0, vsip_vview_f* d0, vsip_vview_f* f0, vsip_mview_f* R0, vsip_scalar_f eps0)
{
    vsip_vview_f *d=vsip_vcloneview_f(d0);
    vsip_vview_f *f=vsip_vcloneview_f(f0);
    vsip_mview_f *L=vsip_mcloneview_f(L0);
    vsip_mview_f *R=vsip_mcloneview_f(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_f(d0);
    while (cntr++ < maxcntr){
        phaseCheck_f(L0,d0,f0,R0,eps0);
        cnr=svdCorners_f(f0);
        if (cnr.j == 0)
            break;
        ivsv_f(d0,d,cnr.i,cnr.j);
        ivsv_f(f0,f,cnr.i,cnr.j-1);
        imsv_f(L0,L,0,0,cnr.i,cnr.j);
        imsv_f(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_f(f);
        k=zeroFind_f(d,eps0);
        if (k > 0){
            if(vsip_vget_f(d,n) == 0.0){
                zeroCol_f(d,f,R);
            }else{
                imsv_f(L,L,0,0,k-1,0);
                ivsv_f(d0,d,k,0);
                ivsv_f(f0,f,k-1,0);
                zeroRow_f(L,d,f);
            }
        }else{
            svdStep_f(L,d,f,R);
        }
    }
    vsip_vdestroy_f(d);
    vsip_vdestroy_f(f);
    vsip_mdestroy_f(L);
    vsip_mdestroy_f(R);
}
static void svdIteration_d(vsip_mview_d* L0, vsip_vview_d* d0, vsip_vview_d* f0, vsip_mview_d* R0, vsip_scalar_d eps0)
{
    vsip_vview_d *d=vsip_vcloneview_d(d0);
    vsip_vview_d *f=vsip_vcloneview_d(f0);
    vsip_mview_d *L=vsip_mcloneview_d(L0);
    vsip_mview_d *R=vsip_mcloneview_d(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_d(d0);
    while (cntr++ < maxcntr){
        phaseCheck_d(L0,d0,f0,R0,eps0);
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        imsv_d(L0,L,0,0,cnr.i,cnr.j);
        imsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_d(f);
        k=zeroFind_d(d,eps0);
        if (k > 0){
            if(vsip_vget_d(d,n) == 0.0){
                zeroCol_d(d,f,R);
            }else{
                imsv_d(L,L,0,0,k-1,0);
                ivsv_d(d0,d,k,0);
                ivsv_d(f0,f,k-1,0);
                zeroRow_d(L,d,f);
            }
        }else{
            svdStep_d(L,d,f,R);
        }
    }
    vsip_vdestroy_d(d);
    vsip_vdestroy_d(f);
    vsip_mdestroy_d(L);
    vsip_mdestroy_d(R);
}
static void csvdIteration_f(vsip_cmview_f* L0, vsip_vview_f* d0, vsip_vview_f* f0, vsip_cmview_f* R0, vsip_scalar_f eps0)
{
    vsip_vview_f *d=vsip_vcloneview_f(d0);
    vsip_vview_f *f=vsip_vcloneview_f(f0);
    vsip_cmview_f *L=vsip_cmcloneview_f(L0);
    vsip_cmview_f *R=vsip_cmcloneview_f(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_f(d0);
    while (cntr++ < maxcntr){
        cphaseCheck_f(L0,d0,f0,R0,eps0);
        cnr=svdCorners_f(f0);
        if (cnr.j == 0)
            break;
        ivsv_f(d0,d,cnr.i,cnr.j);
        ivsv_f(f0,f,cnr.i,cnr.j-1);
        cimsv_f(L0,L,0,0,cnr.i,cnr.j);
        cimsv_f(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_f(f);
        k=zeroFind_f(d,eps0);
        if (k > 0){
            if(vsip_vget_f(d,n) == 0.0){
                czeroCol_f(d,f,R);
            }else{
                cimsv_f(L,L,0,0,k-1,0);
                ivsv_f(d0,d,k,0);
                ivsv_f(f0,f,k-1,0);
                czeroRow_f(L,d,f);
            }
        }else{
            csvdStep_f(L,d,f,R);
        }
    }
    vsip_vdestroy_f(d);
    vsip_vdestroy_f(f);
    vsip_cmdestroy_f(L);
    vsip_cmdestroy_f(R);
}
static void csvdIteration_d(vsip_cmview_d* L0, vsip_vview_d* d0, vsip_vview_d* f0, vsip_cmview_d* R0, vsip_scalar_d eps0)
{
    vsip_vview_d *d=vsip_vcloneview_d(d0);
    vsip_vview_d *f=vsip_vcloneview_d(f0);
    vsip_cmview_d *L=vsip_cmcloneview_d(L0);
    vsip_cmview_d *R=vsip_cmcloneview_d(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_d(d0);
    while (cntr++ < maxcntr){
        cphaseCheck_d(L0,d0,f0,R0,eps0);
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        cimsv_d(L0,L,0,0,cnr.i,cnr.j);
        cimsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_d(f);
        k=zeroFind_d(d,eps0);
        if (k > 0){
            if(vsip_vget_d(d,n) == 0.0){
                czeroCol_d(d,f,R);
            }else{
                cimsv_d(L,L,0,0,k-1,0);
                ivsv_d(d0,d,k,0);
                ivsv_d(f0,f,k-1,0);
                czeroRow_d(L,d,f);
            }
        }else{
            csvdStep_d(L,d,f,R);
        }
    }
    vsip_vdestroy_d(d);
    vsip_vdestroy_d(f);
    vsip_cmdestroy_d(L);
    vsip_cmdestroy_d(R);
}

static void svdSort_f(vsip_mview_f* L0,vsip_vview_f* d,vsip_mview_f* R0){
    vsip_length n=vsip_vgetlength_f(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_mview_f *L=vsip_mcloneview_f(L0);
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_f( L0, L, 0,0, 0, n);
    vsip_mpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_f(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_mdestroy_f(L);   
}
static void csvdSort_f(vsip_cmview_f* L0,vsip_vview_f* d,vsip_cmview_f* R0){
    vsip_length n=vsip_vgetlength_f(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_cmview_f *L=vsip_cmcloneview_f(L0);
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    cimsv_f( L0, L, 0,0, 0, n);
    vsip_cmpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_cmpermute_once_f(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_cmdestroy_f(L);
}
static void svdSort_d(vsip_mview_d* L0,vsip_vview_d* d,vsip_mview_d* R0){
    vsip_length n=vsip_vgetlength_d(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_mview_d *L=vsip_mcloneview_d(L0);
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_d( L0, L, 0,0, 0, n);
    vsip_mpermute_once_d(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_d(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_mdestroy_d(L);
}
static void csvdSort_d(vsip_cmview_d* L0,vsip_vview_d* d,vsip_cmview_d* R0){
    vsip_length n=vsip_vgetlength_d(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_cmview_d *L=vsip_cmcloneview_d(L0);
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    cimsv_d( L0, L, 0,0, 0, n);
    vsip_cmpermute_once_d(L,VSIP_COL,indx_L,L);
    vsip_cmpermute_once_d(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_cmdestroy_d(L);
}

svdObj_f svd_f(vsip_mview_f *A){
    svdObj_f svd = svdBidiag_f(A);
    svdIteration_f(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    svdSort_f(svd.L,svd.d,svd.R);
    return svd;
}
csvdObj_f csvd_f(vsip_cmview_f *A){
    csvdObj_f svd = csvdBidiag_f(A);
    csvdIteration_f(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    csvdSort_f(svd.L,svd.d,svd.R);
    return svd;
}
svdObj_d svd_d(vsip_mview_d *A){
    svdObj_d svd = svdBidiag_d(A);
    svdIteration_d(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    svdSort_d(svd.L,svd.d,svd.R);
    return svd;
}
csvdObj_d csvd_d(vsip_cmview_d *A){
    csvdObj_d svd = csvdBidiag_d(A);
    csvdIteration_d(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    csvdSort_d(svd.L,svd.d,svd.R);
    return svd;
}
