/* Created RJudd */
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
/* new version done August 2000 */
/* $Id: vsip_mprod_f.c,v 2.5 2006/11/27 21:39:41 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>

#define VI_MFILL_F( la, lr) { vsip_length n_mj, n_mn; vsip_stride rst_mj, rst_mn; \
    vsip_scalar_f *rpl  = (lr->block->array) + lr->offset * lr->block->rstride; \
    vsip_scalar_f *rpl0 = rpl; \
    if(lr->row_stride < lr->col_stride){ \
           n_mj = lr->row_length; n_mn = lr->col_length; rst_mj = lr->row_stride; rst_mn = lr->col_stride; rst_mj *= lr->block->rstride; rst_mn *= lr->block->rstride; \
    } else { \
           n_mn = lr->row_length; n_mj = lr->col_length; rst_mn = lr->row_stride; rst_mj = lr->col_stride; rst_mn *= lr->block->rstride; rst_mj *= lr->block->rstride; \
    } while(n_mn-- > 0){ \
       vsip_length n = n_mj; while(n-- >0){ *rpl = la; rpl += rst_mj; } rpl0 += rst_mn; rpl = rpl0; \
    } }

#define VI_MPROD_jki_F { \
   vsip_length outer_loop = r_r_l / 3; vsip_length final_loop = r_r_l % 3; \
      for(j=0; j< outer_loop; j++){  \
         vsip_index my_j0 = j * 3; vsip_index my_j1 = my_j0 + 1; vsip_index my_j2 = my_j1 + 1; \
         for(k=0; k< a_r_l; k++){ \
            b0_scalar = bp[k * b_st_c + my_j0 * b_st_r]; \
            b1_scalar = bp[k * b_st_c + my_j1 * b_st_r]; \
            b2_scalar = bp[k * b_st_c + my_j2 * b_st_r]; \
               for(i=0; i<a_c_l; i++){ \
                  a0_scalar = ap[i * a_st_c + k * a_st_r]; \
                  rp[my_j0 * r_st_r + i * r_st_c] +=  a0_scalar * b0_scalar; \
                  rp[my_j1 * r_st_r + i * r_st_c] +=  a0_scalar * b1_scalar; \
                  rp[my_j2 * r_st_r + i * r_st_c] +=  a0_scalar * b2_scalar; \
      } } } if(final_loop){ \
      for(j=r_r_l - final_loop; j<r_r_l; j++){ \
         for(k=0; k<a_r_l; k++){ \
            b0_scalar = bp[k * b_st_c + j * b_st_r]; \
            for(i=0; i<a_c_l; i++) rp[j * r_st_r + i * r_st_c] += ap[i * a_st_c + k * a_st_r] * b0_scalar; \
   }}}}

#define VI_MPROD_ikj_F { \
   vsip_length outer_loop = a_c_l/3; vsip_length final_loop = a_c_l % 3;\
   for(i=0; i< outer_loop; i++){ \
      vsip_index i0 = 3 * i; vsip_index i1 = i0 + 1; vsip_index i2 = i1 + 1;\
      for(k=0; k<a_r_l; k++){ \
         a0_scalar = ap[i0* a_st_c + k * a_st_r];\
         a1_scalar = ap[i1 * a_st_c + k * a_st_r];\
         a2_scalar = ap[i2 * a_st_c + k * a_st_r];\
         for(j=0; j<r_r_l; j++){\
            b0_scalar = bp[k * b_st_c + j * b_st_r];\
            rp[i0 * r_st_c + j * r_st_r] += b0_scalar * a0_scalar;\
            rp[i1 * r_st_c + j * r_st_r] += b0_scalar * a1_scalar;\
            rp[i2 * r_st_c + j * r_st_r] += b0_scalar * a2_scalar;\
      }}} if(final_loop) {\
         for(i=a_c_l - final_loop; i< a_c_l; i++){\
            for(k=0; k<a_r_l; k++){ \
               a0_scalar = ap[i* a_st_c + k * a_st_r];\
               for(j=0; j<r_r_l; j++){ \
                  rp[i * r_st_c + j * r_st_r] +=  bp[k * b_st_c + j * b_st_r] * a0_scalar;\
   }}}}}

#define VI_MPROD_jik_F { \
   vsip_length outer_loop = a_c_l / 3; vsip_length final_loop = a_c_l % 3; \
   for(j=0; j<outer_loop; j++){ \
      vsip_index my_j0 = 3 * j;vsip_index my_j1 = my_j0 + 1;vsip_index my_j2 = my_j1 + 1; \
      for(i=0; i< r_r_l; i++){ \
         temp0 = 0.0;temp1 = 0.0;temp2 = 0.0;\
         for(k=0; k< a_r_l; k++){\
            b0_scalar = bp[i * b_st_r + k * b_st_c];\
            temp0 += ap[my_j0 * a_st_c + k * a_st_r] * b0_scalar;\
            temp1 += ap[my_j1 * a_st_c + k * a_st_r] * b0_scalar;\
            temp2 += ap[my_j2 * a_st_c + k * a_st_r] * b0_scalar;\
         }\
         rp[my_j0 * r_st_c + i * r_st_r] = temp0;\
         rp[my_j1 * r_st_c + i * r_st_r] = temp1;\
         rp[my_j2 * r_st_c + i * r_st_r] = temp2;\
      }} if(final_loop){ \
      for(j=a_c_l - final_loop; j < a_c_l; j++){\
         for(i=0; i<r_r_l; i++){\
            temp0 = 0;\
            for(k=0; k<a_r_l; k++){\
               temp0 += ap[j * a_st_c + k * a_st_r] * bp[i * b_st_r + k * b_st_c];\
            }\
            rp[j * r_st_c + i * r_st_r] = temp0;\
   }}}} 

void (vsip_mprod_f)(
                    const vsip_mview_f* a,
                    const vsip_mview_f* b,
                    const vsip_mview_f* r)
{
   vsip_index i,j,k;
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
   register vsip_scalar_f  a0_scalar,a1_scalar, a2_scalar,
                           b0_scalar, b1_scalar, b2_scalar, 
                           temp0, temp1, temp2;
   vsip_scalar_f  *ap = (a->block->array) + a->offset * a->block->rstride,
                  *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
   VI_MFILL_F(0.0,r);
   switch(method){
      case 0 : VI_MPROD_jki_F; /* printf("here ccc ex3\n"); */ break; /* ccc */
      case 1 : VI_MPROD_ikj_F; /* printf("here ccr ex3\n"); */ break; /* ccr */
      case 2 : VI_MPROD_jki_F; /* printf("here crc ex3\n"); */ break; /* crc */
      case 3 : VI_MPROD_ikj_F; /* printf("here crr ex3\n"); */ break; /* crr */
      case 4 : VI_MPROD_jik_F; /* printf("here rcc ex3\n"); */ break; /* rcc */
      case 5 : VI_MPROD_jik_F; /* printf("here rcr ex3\n"); */ break; /* rcr */
      case 6 : VI_MPROD_ikj_F; /* printf("here rrc ex3\n"); */ break; /* rrc */
      case 7 : VI_MPROD_ikj_F; /* printf("here rrr ex3\n"); */        /* rrr */
   }
}
