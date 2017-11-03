/* Created RJudd January 27, 1999 */
/* SPAWARSYSCEN D881 */

/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_gemp_d.c,v 2.3 2008/03/03 18:36:36 judd Exp $ */

#include"vsip_mviewattributes_d.h"
#include"vsip_vviewattributes_d.h"
#include"vsip.h"

#define VI_GEMP_jki_D {\
vsip_scalar_d *ap_ik = ap0, *ap_0k = ap0;\
vsip_scalar_d *bp_kj = bp0, *bp_0j = bp0;\
vsip_scalar_d *rp_ij = rp0, *rp_0j = rp0;\
if(b1 != 1.0) vsip_smmul_d(b1,r,r);\
while(r_r_l-- > 0){ /* j */\
rp_ij = rp_0j;\
bp_kj = bp_0j;\
while(a_r_l-- > 0){ /* k */\
b_scalar = a1 * *bp_kj;\
bp_kj += b_st_c;\
ap_ik = ap_0k;\
while(a_c_l-- > 0){ /* i */\
*rp_ij =  *ap_ik * b_scalar + *rp_ij;\
rp_ij += r_st_c;\
ap_ik += a_st_c;\
} a_c_l = a->col_length;\
ap_0k += a_st_r;\
rp_ij = rp_0j;\
} a_r_l = a->row_length;\
rp_0j += r_st_r;\
bp_0j += b_st_r;\
ap_0k = ap0;\
}} 

#define VI_GEMP_ijk_D { \
vsip_scalar_d *ap_ik = ap0, *ap_i0 = ap0;\
vsip_scalar_d *bp_kj = bp0, *bp_0j = bp0;\
vsip_scalar_d *rp_ij = rp0, *rp_i0 = rp0;\
while(a_c_l-- > 0){ /* i */\
rp_ij = rp_i0;\
bp_0j = bp0;\
while(r_r_l-- > 0){ /* j */\
ap_ik = ap_i0;\
temp = 0;\
bp_kj = bp_0j;\
while(a_r_l-- > 0){ /* k */\
temp += *ap_ik * *bp_kj;\
ap_ik += a_st_r;\
bp_kj += b_st_c;\
} a_r_l = a->row_length;\
*rp_ij = b1 * *rp_ij + a1 * temp;\
rp_ij += r_st_r;\
bp_0j += b_st_r;\
} r_r_l = r->row_length;\
rp_i0 += r_st_c;\
ap_i0 += a_st_c;\
}}

#define VI_GEMP_ikj_D {\
vsip_scalar_d *ap_ik = ap0, *ap_i0 = ap0;\
vsip_scalar_d *bp_kj = bp0, *bp_k0 = bp0;\
vsip_scalar_d *rp_ij = rp0, *rp_i0 = rp0;\
if(b1 != 1.0) vsip_smmul_d(b1,r,r);\
while(a_c_l-- > 0){ /* i */\
ap_ik = ap_i0;\
while(a_r_l-- > 0){ /* k */\
a_scalar = a1 * *ap_ik;\
ap_ik += a_st_r;\
bp_kj = bp_k0;\
rp_ij = rp_i0;\
while(r_r_l-- > 0){ /* j */\
*rp_ij = *bp_kj * a_scalar + *rp_ij;\
rp_ij += r_st_r;\
bp_kj += b_st_r;\
} r_r_l = r->row_length;\
bp_k0 += b_st_c;\
}a_r_l = a->row_length;\
bp_k0 = bp0;\
rp_i0 += r_st_c;\
ap_i0 += a_st_c;\
}}

void vsip_gemp_d(vsip_scalar_d alpha,
                   const vsip_mview_d *AA,
                   vsip_mat_op OpA,
                   const vsip_mview_d *BB,
                   vsip_mat_op OpB,
                   vsip_scalar_d beta,
                   const vsip_mview_d *r){
   register vsip_scalar_d a1 = alpha;
   register vsip_scalar_d b1 = beta;
   vsip_mview_d At = *AA,
                Bt = *BB;
   vsip_mview_d *a = &At,
                *b = &Bt;
   if(OpA == VSIP_MAT_TRANS){
        a->row_length = AA->col_length;
        a->col_length = AA->row_length;
        a->row_stride = AA->col_stride;
        a->col_stride = AA->row_stride;
   }
   if(OpB == VSIP_MAT_TRANS){
        b->row_length = BB->col_length;
        b->col_length = BB->row_length;
        b->row_stride = BB->col_stride;
        b->col_stride = BB->row_stride;
   }
   {
       /* c => column major, r => row major */
       /* decide if ccc => 0 ccr=> 1, crc => 2, etc to rrr => 7 */
       unsigned method = (unsigned)(r->row_stride <= r->col_stride) + 
                         (unsigned)(b->row_stride <= b->col_stride) * 2 +
                         (unsigned)(a->row_stride <= a->col_stride) * 4;
       vsip_stride a_st_r = a->row_stride * a->block->rstride,
                  a_st_c = a->col_stride * a->block->rstride,
                  b_st_r = b->row_stride * b->block->rstride,
                  b_st_c = b->col_stride * b->block->rstride,
                  r_st_r = r->row_stride * r->block->rstride,
                  r_st_c = r->col_stride * r->block->rstride;
       vsip_length a_c_l  = a->col_length;  /* i_size */
       vsip_length r_r_l  = r->row_length;  /* j_size */
       vsip_length a_r_l  = a->row_length;  /* k_size */
       register vsip_scalar_d a_scalar, b_scalar, temp;
       vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                     *bp = (b->block->array) + b->offset * b->block->rstride,
                     *rp = (r->block->array) + r->offset * r->block->rstride;
       vsip_scalar_d *ap0 = ap,
                     *bp0 = bp,
                     *rp0 = rp;
       switch(method){
          case 0 : VI_GEMP_jki_D; break; /* ccc */
          case 1 : VI_GEMP_ikj_D; break; /* ccr */ 
          case 2 : VI_GEMP_jki_D; break; /* crc */
          case 3 : VI_GEMP_ikj_D; break; /* crr */            
          case 4 : VI_GEMP_ijk_D; break; /* rcc */
          case 5 : VI_GEMP_ijk_D; break; /* rcr */
          case 6 : VI_GEMP_ikj_D; break; /* rrc */
          case 7 : VI_GEMP_ikj_D;        /* rrr */
      }
   }
}
