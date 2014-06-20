#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_i.h>
#include<vsip_vviewattributes_i.h>
#include<math.h>
#include"vsip_scalars.h"
void vsip_mfloor_d_d(const vsip_mview_d* a, const vsip_mview_d* r)
{
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_d *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride;
    vsip_scalar_d *rp0 = rp;
    vsip_scalar_d  *ap0 = ap;
    if(r->row_stride < r->col_stride){
           n_mj   = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         *rp = VSIP_FLOOR_D(*ap);
         ap += ast_mj;  rp += rst_mj;
       }
       ap0 += ast_mn; rp0 += rst_mn;
       ap = ap0; rp = rp0;
    }
    return;
}
void vsip_mfloor_d_i(const vsip_mview_d* a, const vsip_mview_i* r)
{
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_i *rp = (r->block->array) + r->offset;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride;
    vsip_scalar_i *rp0 = rp;
    vsip_scalar_d  *ap0 = ap;
    if(r->row_stride < r->col_stride){
           n_mj   = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         vsip_scalar_d t = VSIP_FLOOR_D(*ap);
         *rp = (vsip_scalar_i)(t+DBL_EPSILON);
         ap += ast_mj;  rp += rst_mj;
       }
       ap0 += ast_mn; rp0 += rst_mn;
       ap = ap0; rp = rp0;
    }
    return;
}
void vsip_mfloor_f_f(const vsip_mview_f* a, const vsip_mview_f* r)
{
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
    vsip_scalar_f *rp0 = rp;
    vsip_scalar_f  *ap0 = ap;
    if(r->row_stride < r->col_stride){
           n_mj   = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           rst_mj *= r->block->rstride; rst_mn *= r->block->rstride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           rst_mn *= r->block->rstride; rst_mj *= r->block->rstride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         *rp = VSIP_FLOOR_F(*ap);
         ap += ast_mj;  rp += rst_mj;
       }
       ap0 += ast_mn; rp0 += rst_mn;
       ap = ap0; rp = rp0;
    }
    return;
}
void vsip_mfloor_f_i(const vsip_mview_f* a, const vsip_mview_i* r)
{

    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_i *rp = (r->block->array) + r->offset;
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
    vsip_scalar_i *rp0 = rp;
    vsip_scalar_f  *ap0 = ap;
    if(r->row_stride < r->col_stride){
           n_mj   = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         vsip_scalar_f t = VSIP_FLOOR_F(*ap);
         *rp = (vsip_scalar_i)(t+FLT_EPSILON);
         ap += ast_mj;  rp += rst_mj;
       }
       ap0 += ast_mn; rp0 += rst_mn;
       ap = ap0; rp = rp0;
    }
    return;
}
void vsip_vfloor_d_d(const vsip_vview_d* a, const vsip_vview_d* r)
{
      vsip_length n   = r->length;
      vsip_stride ast = a->stride * a->block->rstride,
                  rst = r->stride * r->block->rstride;
      vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_d *rp = (r->block->array) + r->offset * r->block->rstride;
      while(n-- > 0){
         *rp = VSIP_FLOOR_D(*ap);
         ap += ast; rp += rst;
      }
}
void vsip_vfloor_d_i(const vsip_vview_d* a, const vsip_vview_i* r)
{
      vsip_length n   = r->length; 
      vsip_stride ast = a->stride * a->block->rstride, 
                  rst = r->stride;
      vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_i *rp = (r->block->array) + r->offset;
      while(n-- > 0){
         vsip_scalar_d t = VSIP_FLOOR_D(*ap);
         *rp = (vsip_scalar_i)(t+DBL_EPSILON);
         ap += ast; rp += rst;
      }
}
void vsip_vfloor_f_f(const vsip_vview_f* a, const vsip_vview_f* r)
{
      vsip_length n   = r->length; 
      vsip_stride ast = a->stride * a->block->rstride, 
                  rst = r->stride * r->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
      while(n-- > 0){
         *rp = VSIP_FLOOR_F(*ap);
         ap += ast; rp += rst;
      }
}
void vsip_vfloor_f_i(const vsip_vview_f* a, const vsip_vview_i* r)
{
      vsip_length n   = r->length; 
      vsip_stride ast = a->stride * a->block->rstride, 
                  rst = r->stride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_i *rp = (r->block->array) + r->offset;
      while(n-- > 0){
         vsip_scalar_f t = VSIP_FLOOR_F(*ap);
         *rp = (vsip_scalar_i)(t+FLT_EPSILON);
         ap += ast; rp += rst;
      }
}
