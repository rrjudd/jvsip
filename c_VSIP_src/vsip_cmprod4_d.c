/* Created R. Judd  */
/* Retired          */
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
/* $Id: vsip_cmprod4_d.c,v 2.1 2006/04/09 19:25:53 judd Exp $ */
/* New disclaimer now I am retired */

#include<vsip.h>
#include<VI.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>

/* note that matrix products may not be done in place */
void (vsip_cmprod4_d)(
  const vsip_cmview_d* a,
  const vsip_cmview_d* b,
  const vsip_cmview_d* c) {

    /* get the stride info */
    /* st_r => stride row; st_c => stride column */
    vsip_stride a_st_r = a->row_stride * a->block->cstride,
                a_st_c = a->col_stride * a->block->cstride,
                b_st_r = b->row_stride * b->block->cstride,
                b_st_c = b->col_stride * b->block->cstride,
                c_st_r = c->row_stride * c->block->cstride,
                c_st_c = c->col_stride * c->block->cstride;

    /* get the length info */
    /* note we know a is 4 by 4 and b is 4 by row length */
    vsip_length c_r_l  = c->row_length;  /* j_size */

    /* get the pointers to the input and output data spaces */
    vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *cp_r = (c->block->R->array) + c->offset * c->block->cstride,
                  *cp_i = (c->block->I->array) + c->offset * c->block->cstride;

    /* some additional pointers to store initial data */
    vsip_scalar_d *ap0_r = ap_r, *ap0_i = ap_i,
                  *bp0_r, *bp0_i,
                  *cp0_r, *cp0_i;
    register vsip_scalar_d a00_r, a01_r, a02_r, a03_r, a00_i, a01_i, a02_i,a03_i;
    register vsip_scalar_d a10_r, a11_r, a12_r, a13_r, a10_i, a11_i, a12_i,a13_i;
    register vsip_scalar_d a20_r, a21_r, a22_r, a23_r, a20_i, a21_i, a22_i,a23_i;
    register vsip_scalar_d a30_r, a31_r, a32_r, a33_r, a30_i, a31_i, a32_i,a33_i;

    /* we need local storage for a column of b */
    register vsip_scalar_d b0_r, b1_r, b2_r, b3_r;
    register vsip_scalar_d b0_i, b1_i, b2_i, b3_i;

    vsip_length i; /* need a counter */

    /* we copy a to local storage */
    a00_r = *ap0_r, a00_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a01_r = *ap0_r, a01_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a02_r = *ap0_r, a02_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a03_r = *ap0_r, a03_i = *ap0_i; ap0_r= ap_r + a_st_c; ap0_i = ap_i + a_st_c;
    a10_r = *ap0_r, a10_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a11_r = *ap0_r, a11_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a12_r = *ap0_r, a12_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a13_r = *ap0_r, a13_i = *ap0_i; ap0_r= ap_r + 2 * a_st_c; ap0_i = ap_i + 2 *  a_st_c;
    a20_r = *ap0_r, a20_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a21_r = *ap0_r, a21_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a22_r = *ap0_r, a22_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a23_r = *ap0_r, a23_i = *ap0_i; ap0_r= ap_r + 3 * a_st_c; ap0_i = ap_i + 3 * a_st_c;
    a30_r = *ap0_r, a30_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a31_r = *ap0_r, a31_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a32_r = *ap0_r, a32_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a33_r = *ap0_r, a33_i = *ap0_i;

    for(i=0; i< c_r_l; i++){
       /* copy i'th column of b into local */
       bp0_r = bp_r + (vsip_stride)i * b_st_r; bp0_i = bp_i +  (vsip_stride)i * b_st_r;
       b0_r = *bp0_r; b0_i = *bp0_i; bp0_r += b_st_c; bp0_i += b_st_c;
       b1_r = *bp0_r; b1_i = *bp0_i; bp0_r += b_st_c; bp0_i += b_st_c;
       b2_r = *bp0_r; b2_i = *bp0_i; bp0_r += b_st_c; bp0_i += b_st_c;
       b3_r = *bp0_r; b3_i = *bp0_i; 
       
       /* get the pointer to the column where output will go */
       cp0_r = cp_r + (vsip_stride)i * c_st_r; cp0_i = cp_i + (vsip_stride)i * c_st_r;

       /* do the math */
       /* the real part */
       *cp0_r = (a00_r * b0_r + a01_r * b1_r + a02_r * b2_r + a03_r * b3_r) -
                (a00_i * b0_i + a01_i * b1_i + a02_i * b2_i + a03_i * b3_i); cp0_r += c_st_c;

       *cp0_r = (a10_r * b0_r + a11_r * b1_r + a12_r * b2_r + a13_r * b3_r) -
                (a10_i * b0_i + a11_i * b1_i + a12_i * b2_i + a13_i * b3_i); cp0_r += c_st_c;

       *cp0_r = (a20_r * b0_r + a21_r * b1_r + a22_r * b2_r + a23_r * b3_r) -
                (a20_i * b0_i + a21_i * b1_i + a22_i * b2_i + a23_i * b3_i); cp0_r += c_st_c;

       *cp0_r = (a30_r * b0_r + a31_r * b1_r + a32_r * b2_r + a33_r * b3_r) -
                (a30_i * b0_i + a31_i * b1_i + a32_i * b2_i + a33_i * b3_i);

       /* the imaginary part */
       *cp0_i = a00_r * b0_i + a01_r * b1_i + a02_r * b2_i + a03_r * b3_i +
                a00_i * b0_r + a01_i * b1_r + a02_i * b2_r + a03_i * b3_r; cp0_i += c_st_c;

       *cp0_i = a10_r * b0_i + a11_r * b1_i + a12_r * b2_i + a13_r * b3_i +
                a10_i * b0_r + a11_i * b1_r + a12_i * b2_r + a13_i * b3_r; cp0_i += c_st_c;

       *cp0_i = a20_r * b0_i + a21_r * b1_i + a22_r * b2_i + a23_r * b3_i +
                a20_i * b0_r + a21_i * b1_r + a22_i * b2_r + a23_i * b3_r; cp0_i += c_st_c;

       *cp0_i = a30_r * b0_i + a31_r * b1_i + a32_r * b2_i + a33_r * b3_i +
                a30_i * b0_r + a31_i * b1_r + a32_i * b2_r + a33_i * b3_r;
    }
}
 
