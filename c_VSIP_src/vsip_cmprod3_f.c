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
/* $Id: vsip_cmprod3_f.c,v 2.4 2006/04/27 01:58:00 judd Exp $ */

#include<vsip.h>
#include<VI.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

/* note that matrix products may not be done in place */
void (vsip_cmprod3_f)(
  const vsip_cmview_f* a,
  const vsip_cmview_f* b,
  const vsip_cmview_f* c) {

    /* get the stride info */
    /* st_r => stride row; st_c => stride column */
    vsip_stride a_st_r = a->row_stride * a->block->cstride,
                a_st_c = a->col_stride * a->block->cstride,
                b_st_r = b->row_stride * b->block->cstride,
                b_st_c = b->col_stride * b->block->cstride,
                c_st_r = c->row_stride * c->block->cstride,
                c_st_c = c->col_stride * c->block->cstride;

    /* get the length info */
    /* note we know a is 3 by 3 and b is 3 by row length */
    vsip_length c_r_l  = c->row_length;  /* j_size */

    /* get the pointers to the input and output data spaces */
    vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *cp_r = (c->block->R->array) + c->offset * c->block->cstride,
                  *cp_i = (c->block->I->array) + c->offset * c->block->cstride;

    /* some additional pointers to store initial data */
    vsip_scalar_f *ap0_r = ap_r, *ap0_i = ap_i,
                  *bp0_r, *bp0_i,
                  *cp0_r, *cp0_i;
    register vsip_scalar_f a00_r, a01_r, a02_r, a00_i, a01_i, a02_i;
    register vsip_scalar_f a10_r, a11_r, a12_r, a10_i, a11_i, a12_i;
    register vsip_scalar_f a20_r, a21_r, a22_r, a20_i, a21_i, a22_i;

    /* we need local storage for a column of b */
    register vsip_scalar_f b0_r, b1_r, b2_r;
    register vsip_scalar_f b0_i, b1_i, b2_i;

    vsip_length i; /* need a counter */

    /* we copy a to local storage */
    a00_r = *ap0_r, a00_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a01_r = *ap0_r, a01_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a02_r = *ap0_r, a02_i = *ap0_i; 

    ap0_r = ap_r + a_st_c; ap0_i = ap_i + a_st_c;
    a10_r = *ap0_r, a10_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a11_r = *ap0_r, a11_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a12_r = *ap0_r, a12_i = *ap0_i;

    ap0_r = ap_r + 2 * a_st_c; ap0_i = ap_i + 2 * a_st_c;
    a20_r = *ap0_r, a20_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a21_r = *ap0_r, a21_i = *ap0_i; ap0_r+=a_st_r; ap0_i += a_st_r;
    a22_r = *ap0_r, a22_i = *ap0_i; 

    for(i=0; i< c_r_l; i++){
       /* copy i'th column of b into local */
       bp0_r = bp_r + (vsip_stride)i * b_st_r; bp0_i = bp_i +  (vsip_stride)i * b_st_r;
       b0_r = *bp0_r; b0_i = *bp0_i; bp0_r += b_st_c; bp0_i += b_st_c;
       b1_r = *bp0_r; b1_i = *bp0_i; bp0_r += b_st_c; bp0_i += b_st_c;
       b2_r = *bp0_r; b2_i = *bp0_i; 
       
       /* get the pointer to the column where output will go */
       cp0_r = cp_r + (vsip_stride)i * c_st_r; cp0_i = cp_i + (vsip_stride)i * c_st_r;

       /* do the math */
       /* the real part */
       *cp0_r = (a00_r * b0_r + a01_r * b1_r + a02_r * b2_r ) -
                (a00_i * b0_i + a01_i * b1_i + a02_i * b2_i ); cp0_r += c_st_c;

       *cp0_r = (a10_r * b0_r + a11_r * b1_r + a12_r * b2_r ) -
                (a10_i * b0_i + a11_i * b1_i + a12_i * b2_i ); cp0_r += c_st_c;

       *cp0_r = (a20_r * b0_r + a21_r * b1_r + a22_r * b2_r ) -
                (a20_i * b0_i + a21_i * b1_i + a22_i * b2_i ); 


       /* the imaginary part */
       *cp0_i = a00_r * b0_i + a01_r * b1_i + a02_r * b2_i +
                a00_i * b0_r + a01_i * b1_r + a02_i * b2_r ; cp0_i += c_st_c;

       *cp0_i = a10_r * b0_i + a11_r * b1_i + a12_r * b2_i +
                a10_i * b0_r + a11_i * b1_r + a12_i * b2_r ; cp0_i += c_st_c;

       *cp0_i = a20_r * b0_i + a21_r * b1_i + a22_r * b2_i +
                a20_i * b0_r + a21_i * b1_r + a22_i * b2_r ; 
    }
}
