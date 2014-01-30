/* Created RJudd January 8, 2013 */
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
#include"VU_svdUtils.h"
vsip_scalar_f
vnormFro_f(vsip_vview_f *v){
    return vsip_sqrt_f(vsip_vsumsqval_f(v));
}
vsip_scalar_f
vnorm2_f(vsip_vview_f *v){
    return vnormFro_f(v);
}
vsip_scalar_f
cvnorm2_f(vsip_cvview_f *v){
    return vsip_sqrt_f(vsip_cvjdot_f(v,v).r);
}
vsip_scalar_d
vnormFro_d(vsip_vview_d *v){
    return vsip_sqrt_d(vsip_vsumsqval_d(v));
}
vsip_scalar_d
vnorm2_d(vsip_vview_d *v){
    return vnormFro_d(v);
}
vsip_scalar_d
cvnorm2_d(vsip_cvview_d *v){
    return vsip_sqrt_d(vsip_cvjdot_d(v,v).r);
}
vsip_scalar_f
mnormFro_f(vsip_mview_f *v){
    return vsip_sqrt_f(vsip_msumsqval_f(v));
}
vsip_scalar_d
mnormFro_d(vsip_mview_d *v){
    return vsip_sqrt_d(vsip_msumsqval_d(v));
}

vsip_scalar_f
cvnormFro_f(vsip_cvview_f *v){
    vsip_vview_f* re=vsip_vrealview_f(v); 
    vsip_vview_f* im=vsip_vimagview_f(v);
    return vsip_sqrt_f(vsip_vsumsqval_f(re)+vsip_vsumsqval_f(im));
    vsip_vdestroy_f(re);vsip_vdestroy_f(im);
}
vsip_scalar_d
cvnormFro_d(vsip_cvview_d *v){
    vsip_vview_d* re=vsip_vrealview_d(v); 
    vsip_vview_d* im=vsip_vimagview_d(v);
    return vsip_sqrt_d(vsip_vsumsqval_d(re)+vsip_vsumsqval_d(im));
    vsip_vdestroy_d(re);vsip_vdestroy_d(im);
}
vsip_scalar_f
cmnormFro_f(vsip_cmview_f *v){
    vsip_mview_f* re=vsip_mrealview_f(v); 
    vsip_mview_f* im=vsip_mimagview_f(v);
    return vsip_sqrt_f(vsip_msumsqval_f(re)+vsip_msumsqval_f(im));
    vsip_mdestroy_f(re);vsip_mdestroy_f(im);
}
vsip_scalar_d
cmnormFro_d(vsip_cmview_d *v){
    vsip_mview_d* re=vsip_mrealview_d(v); 
    vsip_mview_d* im=vsip_mimagview_d(v);
    return vsip_sqrt_d(vsip_msumsqval_d(re)+vsip_msumsqval_d(im));
    vsip_mdestroy_d(re);vsip_mdestroy_d(im);
}

vsip_scalar_f
meig_f(vsip_mview_f *A){
    /* A should be square, symetric, postive definite */
    int i;
    vsip_scalar_f small = mnormFro_f(A)/1E16;
    vsip_length m = vsip_mgetcollength_f(A);
    vsip_scalar_f vk = 0.0,vkn=0.0,n=0.0,chk=0.0;
    vsip_vview_f *xk = vsip_vcreate_f(m,VSIP_MEM_NONE);
    vsip_vview_f *axk = vsip_vcreate_f(m,VSIP_MEM_NONE);
    vsip_vfill_f(0.0,xk);
    vsip_vput_f(xk,0,1.0);
    for(i = 0; i<1000; i++){
       vsip_mvprod_f(A,xk,axk);
       n=vnorm2_f(axk);
       vkn = vsip_vdot_f(xk,axk);
       chk = vkn - vk;
       if (chk < 0)
           chk = -chk;
       if (chk < small)
          return vkn;
       else
          vk=vkn;
       vsip_svmul_f(1.0/n,axk,xk);
    }
    return vkn;
}
vsip_scalar_d
meig_d(vsip_mview_d *A){
    /* A should be square, symetric, postive definite */
    int i;
    vsip_scalar_d small = mnormFro_d(A)/1E16;
    vsip_length m = vsip_mgetcollength_d(A);
    vsip_scalar_d vk = 0.0,vkn=0.0,n=0.0,chk=0.0;
    vsip_vview_d *xk = vsip_vcreate_d(m,VSIP_MEM_NONE);
    vsip_vview_d *axk = vsip_vcreate_d(m,VSIP_MEM_NONE);
    vsip_vfill_d(0.0,xk);
    vsip_vput_d(xk,0,1.0);
    for(i = 0; i<1000; i++){
       vsip_mvprod_d(A,xk,axk);
       n=vnorm2_d(axk);
       vkn = vsip_vdot_d(xk,axk);
       chk = vkn - vk;
       if (chk < 0)
           chk = -chk;
       if (chk < small)
          return vkn;
       else
          vk=vkn;
       vsip_svmul_d(1.0/n,axk,xk);
    }
    return vkn;
}
vsip_scalar_f
cmeig_f(vsip_cmview_f *A){
    /* A should be square, symetric, postive definite */
    int i;
    vsip_scalar_f small = cmnormFro_f(A)/1E16;
    vsip_length m = vsip_cmgetcollength_f(A);
    vsip_scalar_f vk = 0.0,vkn=0.0,n=0.0,chk=0.0;
    vsip_cvview_f *xk = vsip_cvcreate_f(m,VSIP_MEM_NONE);
    vsip_cvview_f *axk = vsip_cvcreate_f(m,VSIP_MEM_NONE);
    vsip_cvfill_f(vsip_cmplx_f(0.0,0.0),xk);
    vsip_cvput_f(xk,0,vsip_cmplx_f(1.0,0.0));
    for(i = 0; i<1000; i++){
       vsip_cmvprod_f(A,xk,axk);
       n=cvnorm2_f(axk);
       vkn = vsip_cvjdot_f(xk,axk).r;
       chk = vkn - vk;
       if (chk < 0)
           chk = -chk;
       if (chk < small)
          return vkn;
       else
          vk=vkn;
       vsip_rscvmul_f(1.0/n,axk,xk);
    }
    return vkn;
}
vsip_scalar_d
cmeig_d(vsip_cmview_d *A){
    /* A should be square, symetric, postive definite */
    int i;
    vsip_scalar_d small = cmnormFro_d(A)/1E16;
    vsip_length m = vsip_cmgetcollength_d(A);
    vsip_scalar_d vk = 0.0,vkn=0.0,n=0.0,chk=0.0;
    vsip_cvview_d *xk = vsip_cvcreate_d(m,VSIP_MEM_NONE);
    vsip_cvview_d *axk = vsip_cvcreate_d(m,VSIP_MEM_NONE);
    vsip_cvfill_d(vsip_cmplx_d(0.0,0.0),xk);
    vsip_cvput_d(xk,0,vsip_cmplx_d(1.0,0.0));
    for(i = 0; i<1000; i++){
       vsip_cmvprod_d(A,xk,axk);
       n=cvnorm2_d(axk);
       vkn = vsip_cvjdot_d(xk,axk).r;
       chk = vkn - vk;
       if (chk < 0)
           chk = -chk;
       if (chk < small)
          return vkn;
       else
          vk=vkn;
       vsip_rscvmul_d(1.0/n,axk,xk);
    }
    return vkn;
}
