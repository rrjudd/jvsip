/* Created R. Judd March 11, 1998 */
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
/* $Id: vsip_cmprod_d.c,v 2.2 2006/05/07 15:56:02 judd Exp $ */
/* Remove Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<VI.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"VI_cmfill_d.h"

/* note that matrix products may not be done in place */
void (vsip_cmprod_d)(
  const vsip_cmview_d* a,
  const vsip_cmview_d* b,
  const vsip_cmview_d* c) {
    /* Note that c => column major, r => row major */
 
    /* Below decide input matrix majors ccc => 0 ccr=> 1, crc => 2, etc to rrr => 7 */
    /* the resulting method is used to calculate */
    unsigned method = (unsigned)(c->row_stride <= c->col_stride) + 
                      (unsigned)(b->row_stride <= b->col_stride) * 2 +
                      (unsigned)(a->row_stride <= a->col_stride) * 4;

    /* get the stride info */
    vsip_stride a_st_r = a->row_stride * a->block->cstride,
                a_st_c = a->col_stride * a->block->cstride,
                b_st_r = b->row_stride * b->block->cstride,
                b_st_c = b->col_stride * b->block->cstride,
                c_st_r = c->row_stride * c->block->cstride,
                c_st_c = c->col_stride * c->block->cstride;

    /* get the length info */
    vsip_length a_c_l  = a->col_length,  /* i_size */
                c_r_l  = c->row_length,  /* j_size */
                a_r_l  = a->row_length;  /* k_size */

    /* define some scalars used in the calculations below */
    vsip_cscalar_d a_scalar, b_scalar, temp = vsip_cmplx_d(0.0f,0.0f);

    /* get the pointers to the input and output data spaces */
    vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *cp_r = (c->block->R->array) + c->offset * c->block->cstride,
                  *cp_i = (c->block->I->array) + c->offset * c->block->cstride;

    /* some additional pointers to store initial data */
    vsip_scalar_d *ap0_r = ap_r, *ap0_i = ap_i,
                  *bp0_r = bp_r, *bp0_i = bp_i,
                  *cp0_r = cp_r, *cp0_i = cp_i;

    vsip_scalar_d *bp1_r = bp_r, *bp1_i = bp_i;

    /* initialize output matrix to zero */
    VI_cmfill_d(temp,c); /* initilize output matrix to zero */

    /* select multiply routine bassed on majors of input matrices */
    switch(method){
       case 0 : { /* ccc */
           vsip_scalar_d *ap_ik_r, *ap_0k_r = ap0_r, *ap_ik_i, *ap_0k_i = ap0_i;
           vsip_scalar_d *bp_kj_r, *bp_0j_r = bp0_r, *bp_kj_i, *bp_0j_i = bp0_i; 
           vsip_scalar_d *cp_ij_r, *cp_0j_r = cp0_r, *cp_ij_i, *cp_0j_i = cp0_i;
           while(c_r_l-- > 0){ /* j */
              cp_ij_r = cp_0j_r; cp_ij_i = cp_0j_i;
              bp_kj_r = bp_0j_r; bp_kj_i = bp_0j_i;
              while(a_r_l-- > 0){ /* k */
                 b_scalar.r = *bp_kj_r; b_scalar.i = *bp_kj_i;
                 bp_kj_r += b_st_c; bp_kj_i += b_st_c;
                 ap_ik_r = ap_0k_r; ap_ik_i = ap_0k_i;
                 while(a_c_l-- > 0){ /* i */
                    *cp_ij_r =  *ap_ik_r * b_scalar.r - *ap_ik_i * b_scalar.i + *cp_ij_r;
                    *cp_ij_i =  *ap_ik_r * b_scalar.i + *ap_ik_i * b_scalar.r + *cp_ij_i;
                     cp_ij_r += c_st_c; cp_ij_i += c_st_c;
                     ap_ik_r += a_st_c; ap_ik_i += a_st_c;
                 } a_c_l = a->col_length;
                 ap_0k_r += a_st_r; ap_0k_i += a_st_r;
                 cp_ij_r = cp_0j_r; cp_ij_i = cp_0j_i;
              } a_r_l = a->row_length;
              cp_0j_r += c_st_r; cp_0j_i += c_st_r;
              bp_0j_r += b_st_r; bp_0j_i += b_st_r;
              ap_0k_r = ap0_r; ap_0k_i = ap0_i;
           }
       } break;
       case 1 : { /* ccr */
           vsip_scalar_d *ap_ik_r, *ap_i0_r = ap0_r, *ap_ik_i, *ap_i0_i = ap0_i;
           vsip_scalar_d *bp_kj_r, *bp_0j_r, *bp_kj_i, *bp_0j_i;
           vsip_scalar_d *cp_ij_r, *cp_i0_r = cp0_r, *cp_ij_i, *cp_i0_i = cp0_i;
           while(a_c_l-- > 0){ /* i */
              cp_ij_r = cp_i0_r; cp_ij_i = cp_i0_i;
              bp_0j_r = bp0_r; bp_0j_i = bp0_i;
              while(c_r_l-- > 0){ /* j */
                 ap_ik_r = ap_i0_r;
                 ap_ik_i = ap_i0_i;
                 temp = vsip_cmplx_d(0.0f,0.0f);
                 bp_kj_r = bp_0j_r; bp_kj_i = bp_0j_i;
                 while(a_r_l-- > 0){ /* k */
                    temp.r += *ap_ik_r * *bp_kj_r - *ap_ik_i * *bp_kj_i;
                    temp.i += *ap_ik_r * *bp_kj_i + *ap_ik_i * *bp_kj_r;
                    ap_ik_r += a_st_r; ap_ik_i += a_st_r;
                    bp_kj_r += b_st_c; bp_kj_i += b_st_c;
                 } a_r_l = a->row_length;
                 *cp_ij_r = temp.r; *cp_ij_i = temp.i;
                  cp_ij_r += c_st_r; cp_ij_i += c_st_r;
                  bp_0j_r += b_st_r; bp_0j_i += b_st_r;
              } c_r_l = c->row_length;
              cp_i0_r += c_st_c; cp_i0_i += c_st_c;
              ap_i0_r += a_st_c; ap_i0_i += a_st_c;
           }
       } break;
       case 2 : { /* crc */
          vsip_scalar_d *ap_ik_r, *ap_0k_r = ap0_r, *ap_ik_i, *ap_0k_i = ap0_i;
          vsip_scalar_d *bp_kj_r, *bp_0j_r = bp0_r, *bp_kj_i, *bp_0j_i = bp0_i; 
          vsip_scalar_d *cp_ij_r, *cp_0j_r = cp0_r, *cp_ij_i, *cp_0j_i = cp0_i;
          while(c_r_l-- > 0){ /* j */
             bp_kj_r = bp_0j_r; bp_kj_i = bp_0j_i;
             while(a_r_l-- > 0){ /* k */
                b_scalar.r = *bp_kj_r; b_scalar.i = *bp_kj_i;
                ap_ik_r = ap_0k_r; ap_ik_i = ap_0k_i;
                cp_ij_r = cp_0j_r; cp_ij_i = cp_0j_i;
                while(a_c_l-- > 0){ /* i */
                   *cp_ij_r +=  *ap_ik_r * b_scalar.r - *ap_ik_i * b_scalar.i;
                   *cp_ij_i +=  *ap_ik_i * b_scalar.r + *ap_ik_r * b_scalar.i;
                    cp_ij_r += c_st_c; cp_ij_i += c_st_c;
                    ap_ik_r += a_st_c; ap_ik_i += a_st_c;
                } a_c_l = a->col_length;
                ap_0k_r += a_st_r; ap_0k_i += a_st_r;
                bp_kj_r += b_st_c; bp_kj_i += b_st_c;
             } a_r_l = a->row_length;
             cp_0j_r += c_st_r; cp_0j_i += c_st_r;
             bp_0j_r += b_st_r; bp_0j_i += b_st_r;
             ap_0k_r = ap0_r; ap_0k_i = ap0_i;
          }
       } break;
       case 3 : { /* crr */
           vsip_scalar_d *ap_ik_r, *ap_i0_r = ap0_r, *ap_ik_i, *ap_i0_i = ap0_i;
           vsip_scalar_d *bp_kj_r, *bp_k0_r = bp0_r, *bp_kj_i, *bp_k0_i = bp0_i;
           vsip_scalar_d *cp_ij_r, *cp_i0_r = cp0_r, *cp_ij_i, *cp_i0_i = cp0_i;
           while(a_c_l-- > 0){ /* i */
              ap_ik_r = ap_i0_r;
              ap_ik_i = ap_i0_i;
              while(a_r_l-- > 0){ /* k */
                 a_scalar.r = *ap_ik_r; a_scalar.i = *ap_ik_i;
                 ap_ik_r += a_st_r; ap_ik_i += a_st_r;
                 bp_kj_r = bp_k0_r; bp_kj_i = bp_k0_i;
                 cp_ij_r = cp_i0_r; cp_ij_i = cp_i0_i;
                 while(c_r_l-- > 0){ /* j */
                     *cp_ij_r = *bp_kj_r * a_scalar.r - *bp_kj_i * a_scalar.i + *cp_ij_r;
                     *cp_ij_i = *bp_kj_i * a_scalar.r + *bp_kj_r * a_scalar.i + *cp_ij_i;
                      cp_ij_r += c_st_r; cp_ij_i += c_st_r;
                      bp_kj_r += b_st_r; bp_kj_i += b_st_r;
                 } c_r_l = c->row_length;
                 bp_k0_r += b_st_c; bp_k0_i += b_st_c;
              }a_r_l = a->row_length;
              bp_k0_r = bp0_r; bp_k0_i = bp0_i;
              cp_i0_r += c_st_c; cp_i0_i += c_st_c;
              ap_i0_r += a_st_c; ap_i0_i += a_st_c;
           }
       } break;
       case 4 : { /* rcc */
          while(a_c_l-- > 0){
             while(c_r_l-- > 0){
                temp = vsip_cmplx_d(0.0f,0.0f);
                while(a_r_l-- > 0){
                   temp.r += *ap_r * *bp_r - *ap_i * *bp_i;
                   temp.i += *ap_r * *bp_i + *ap_i * *bp_r;
                   ap_r += a_st_r; ap_i += a_st_r; 
                   bp_r += b_st_c; bp_i += b_st_c;
                }
                *cp_r = temp.r; *cp_i = temp.i;
                cp_r += c_st_r; cp_i += c_st_r;
                ap_r = ap0_r; ap_i = ap0_i;
                bp0_r += b_st_r; bp0_i += b_st_r;
                bp_r = bp0_r; bp_i = bp0_i;
                a_r_l = a->row_length;
             }
              ap0_r += a_st_c; ap0_i += a_st_c; 
              ap_r = ap0_r; ap_i = ap0_i;
              bp0_r = bp1_r; bp0_i = bp1_i; 
              bp_r = bp0_r;  bp_i = bp0_i;
              cp0_r += c_st_c; cp0_i += c_st_c; 
              cp_r = cp0_r; cp_i = cp0_i;
              c_r_l = c->row_length;
           }
       } break;
          case 5 : { /* rcr */
          while(a_c_l-- > 0){
             while(c_r_l-- > 0){
                temp = vsip_cmplx_d(0.0f,0.0f);
                while(a_r_l-- > 0){
                   temp.r += *ap_r * *bp_r - *ap_i * *bp_i;
                   temp.i += *ap_r * *bp_i + *ap_i * *bp_r;
                   ap_r += a_st_r; ap_i += a_st_r; 
                   bp_r += b_st_c; bp_i += b_st_c;
                }
                *cp_r = temp.r;
                *cp_i = temp.i;
                cp_r += c_st_r; cp_i += c_st_r;
                ap_r = ap0_r; ap_i = ap0_i;
                bp0_r += b_st_r; bp_r = bp0_r; 
                bp0_i += b_st_r; bp_i = bp0_i;
                a_r_l = a->row_length;
             }
             ap0_r += a_st_c; ap_r = ap0_r;
             ap0_i += a_st_c; ap_i = ap0_i;
             bp0_r = bp1_r; bp_r = bp0_r;
             bp0_i = bp1_i; bp_i = bp0_i;
             cp0_r += c_st_c; cp_r = cp0_r;
             cp0_i += c_st_c; cp_i = cp0_i;
             c_r_l = c->row_length;
          }
       } break;
       case 6 : { /* rrc */
           vsip_scalar_d *ap_ik_r, *ap_i0_r, *ap_ik_i, *ap_i0_i;
           vsip_scalar_d *bp_kj_r, *bp_0j_r = bp0_r, *bp_kj_i, *bp_0j_i = bp0_i;
           vsip_scalar_d *cp_ij_r, *cp_0j_r = cp0_r, *cp_ij_i, *cp_0j_i = cp0_i;
           /* jik */
           while(c_r_l-- > 0){ /* j */
              cp_ij_r = cp_0j_r; cp_ij_i = cp_0j_i;
              ap_i0_r = ap0_r; ap_i0_i = ap0_i;
              while(a_c_l-- > 0){ /* i */
                 temp = vsip_cmplx_d(0.0f, 0.0f);
                 ap_ik_r = ap_i0_r; ap_ik_i = ap_i0_i;
                 bp_kj_r = bp_0j_r; bp_kj_i = bp_0j_i;
                 while(a_r_l-- > 0){ /* k */
                    temp.r += *ap_ik_r * *bp_kj_r - *ap_ik_i * *bp_kj_i;;
                    temp.i += *ap_ik_r * *bp_kj_i + *ap_ik_i * *bp_kj_r;
                    ap_ik_r += a_st_r; ap_ik_i += a_st_r;
                    bp_kj_r += b_st_c; bp_kj_i += b_st_c;
                 } a_r_l = a->row_length;
                 *cp_ij_r = temp.r; *cp_ij_i = temp.i;
                  cp_ij_r +=c_st_c; cp_ij_i +=c_st_c;
                  ap_i0_r += a_st_c; ap_i0_i += a_st_c;
              } a_c_l = a->col_length;
              cp_0j_r += c_st_r; cp_0j_i += c_st_r;
              bp_0j_r += b_st_r; bp_0j_i += b_st_r;
           }
       } break;
       case 7 : { /* rrr */
           vsip_scalar_d *ap_ik_r, *ap_i0_r = ap0_r, *ap_ik_i, *ap_i0_i = ap0_i;
           vsip_scalar_d *bp_kj_r, *bp_k0_r = bp0_r, *bp_kj_i, *bp_k0_i = bp0_i;
           vsip_scalar_d *cp_ij_r, *cp_i0_r = cp0_r, *cp_ij_i, *cp_i0_i = cp0_i;
           while(a_c_l-- > 0){ /* i */
              ap_ik_r = ap_i0_r; ap_ik_i = ap_i0_i;
              while(a_r_l-- > 0){ /* k */
                 a_scalar.r = *ap_ik_r; a_scalar.i = *ap_ik_i;
                 ap_ik_r += a_st_r; ap_ik_i += a_st_r;
                 bp_kj_r = bp_k0_r; bp_kj_i = bp_k0_i;
                 cp_ij_r = cp_i0_r; cp_ij_i = cp_i0_i;
                 while(c_r_l-- > 0){ /* j */
                     *cp_ij_r = *bp_kj_r * a_scalar.r - *bp_kj_i * a_scalar.i + *cp_ij_r;
                     *cp_ij_i = *bp_kj_r * a_scalar.i + *bp_kj_i * a_scalar.r + *cp_ij_i;
                      cp_ij_r += c_st_r; cp_ij_i += c_st_r;
                      bp_kj_r += b_st_r; bp_kj_i += b_st_r;
                 } c_r_l = c->row_length;
                 bp_k0_r += b_st_c; bp_k0_i += b_st_c;
              }a_r_l = a->row_length;
              bp_k0_r  = bp0_r;  bp_k0_i  = bp0_i;
              cp_i0_r += c_st_c; cp_i0_i += c_st_c;
              ap_i0_r += a_st_c; ap_i0_i += a_st_c;
           }
       }
   }
}
