/* Created RJudd, Retired */
/* https://github.com/rrjudd/jvsip */
/***********************************************************************
 // This code includes no warranty, express or implied, including the  /
 // warranties of merchantability and fitness for a particular purpose./
 // No person or entity assumes any legal liability or responsibility  /
 // for the accuracy, completeness, or usefulness of an information    /
 // apparatus,  product, or process disclosed, or represents that its  /
 // use would not infringe privately owned rights.                     /
 **********************************************************************/
/* jvsip source code may not be defined in the VSIPL specification    */
/* Functions I know are not VSIPL defined I will place in the jvsip   */
/* name space to prevent inadvertent use.                             */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cmviewattributes_f.h>
#include"jvsip.h"

void jvsip_mprod2_d( const vsip_mview_d* a, const vsip_mview_d* b, const vsip_mview_d* r)
{
    /* st_r-> row stride, st_c=>col stride */
    vsip_stride a_st_r = a->row_stride * a->block->rstride,
                a_st_c = a->col_stride * a->block->rstride,
                b_st_r = b->row_stride * b->block->rstride,
                b_st_c = b->col_stride * b->block->rstride,
                r_st_r = r->row_stride * r->block->rstride,
                r_st_c = r->col_stride * r->block->rstride;
    vsip_index j;
    vsip_length r_r_l  = r->row_length;  /* j_size */
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                  *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *b0p = bp;
    vsip_scalar_d *b1p = b0p + b_st_c;
    vsip_scalar_d *r0p = rp;
    vsip_scalar_d *r1p = r0p + r_st_c;
    register vsip_scalar_d a00,a01;
    register vsip_scalar_d a10,a11;
    a00 = *ap;            a01 = *(ap + a_st_r);
    a10 = *(ap + a_st_c); a11 = *(ap + a_st_c + a_st_r);
    for( j=0; j<r_r_l; j++){
       /* copying b_j into local variables allows in place operation */
       register vsip_scalar_d b0 = *b0p, b1 = *b1p;
       *r0p = a00 * b0 + a01 * b1; 
       *r1p = a10 * b0 + a11 * b1;
       b0p += b_st_r; b1p += b_st_r;
       r0p += r_st_r; r1p += r_st_r;
    }
}
void jvsip_mprod2_f( const vsip_mview_f* a, const vsip_mview_f* b, const vsip_mview_f* r)
{
    /* st_r-> row stride, st_c=>col stride */
    vsip_stride a_st_r = a->row_stride * a->block->rstride,
                a_st_c = a->col_stride * a->block->rstride,
                b_st_r = b->row_stride * b->block->rstride,
                b_st_c = b->col_stride * b->block->rstride,
                r_st_r = r->row_stride * r->block->rstride,
                r_st_c = r->col_stride * r->block->rstride;
    vsip_index j;
    vsip_length r_r_l  = r->row_length;  /* j_size */
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                  *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_f *b0p = bp;
    vsip_scalar_f *b1p = b0p + b_st_c;
    vsip_scalar_f *r0p = rp;
    vsip_scalar_f *r1p = r0p + r_st_c;
    register vsip_scalar_f a00,a01;
    register vsip_scalar_f a10,a11;
    a00 = *ap;            a01 = *(ap + a_st_r);
    a10 = *(ap + a_st_c); a11 = *(ap + a_st_c + a_st_r);
    for( j=0; j<r_r_l; j++){
       /* copying b_j into local variables allows in place operation */
       register vsip_scalar_f b0 = *b0p, b1 = *b1p;
       *r0p = a00 * b0 + a01 * b1; 
       *r1p = a10 * b0 + a11 * b1;
       b0p += b_st_r; b1p += b_st_r;
       r0p += r_st_r; r1p += r_st_r;
    }
}

void jvsip_cmprod2_d( const vsip_cmview_d* a, const vsip_cmview_d* b, const vsip_cmview_d* c)
{
    /* st_r => stride row; st_c => stride column */
    vsip_stride a_st_r = a->row_stride * a->block->cstride,
                a_st_c = a->col_stride * a->block->cstride,
                b_st_r = b->row_stride * b->block->cstride,
                b_st_c = b->col_stride * b->block->cstride,
                c_st_r = c->row_stride * c->block->cstride,
                c_st_c = c->col_stride * c->block->cstride;
    vsip_length c_r_l  = c->row_length;  /* j_size */
    vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *cp_r = (c->block->R->array) + c->offset * c->block->cstride,
                  *cp_i = (c->block->I->array) + c->offset * c->block->cstride;

    /* some additional pointers to store initial data */
    vsip_scalar_d *ap0_r = ap_r, *ap0_i = ap_i, *bp0_r, *bp0_i, *cp0_r, *cp0_i;
    register vsip_scalar_d a00_r, a01_r, a02_r, a00_i, a01_i, a02_i;
    register vsip_scalar_d a10_r, a11_r, a12_r, a10_i, a11_i, a12_i;
    register vsip_scalar_d a20_r, a21_r, a22_r, a20_i, a21_i, a22_i;

    /* we need local storage for a column of b */
    register vsip_scalar_d b0_r, b1_r;
    register vsip_scalar_d b0_i, b1_i;

    vsip_length i; /* need a counter */

    /* we copy matrix a to local storage */
    a00_r = *ap0_r, a00_i = *ap0_i; 
         ap0_r+=a_st_r; ap0_i += a_st_r;
    a01_r = *ap0_r, a01_i = *ap0_i; 
         ap0_r = ap_r + a_st_c; ap0_i = ap_i + a_st_c;
    a10_r = *ap0_r, a10_i = *ap0_i; 
         ap0_r+=a_st_r; ap0_i += a_st_r;
    a11_r = *ap0_r, a11_i = *ap0_i; 

    for(i=0; i< c_r_l; i++){
       /* copy i'th column of b into local */
          bp0_r = bp_r + (vsip_stride)i * b_st_r; 
          bp0_i = bp_i + (vsip_stride)i * b_st_r;
       b0_r = *bp0_r; b0_i = *bp0_i; 
          bp0_r += b_st_c; bp0_i += b_st_c;
       b1_r = *bp0_r; b1_i = *bp0_i;
       /* get the pointer to the column where output will go */
       cp0_r = cp_r + (vsip_stride)i * c_st_r; cp0_i = cp_i + (vsip_stride)i * c_st_r;
       /* do the math */
          /* the real part */
       *cp0_r = (a00_r * b0_r + a01_r * b1_r) - (a00_i * b0_i + a01_i * b1_i ); cp0_r += c_st_c;
       *cp0_r = (a10_r * b0_r + a11_r * b1_r) - (a10_i * b0_i + a11_i * b1_i ); 
          /* the imaginary part */
       *cp0_i = a00_r * b0_i + a01_r * b1_i + a00_i * b0_r + a01_i * b1_r  ; cp0_i += c_st_c;
       *cp0_i = a10_r * b0_i + a11_r * b1_i + a10_i * b0_r + a11_i * b1_r  ;
    }
}
void jvsip_cmprod2_f( const vsip_cmview_f* a, const vsip_cmview_f* b, const vsip_cmview_f* c)
{
    /* st_r => stride row; st_c => stride column */
    vsip_stride a_st_r = a->row_stride * a->block->cstride,
                a_st_c = a->col_stride * a->block->cstride,
                b_st_r = b->row_stride * b->block->cstride,
                b_st_c = b->col_stride * b->block->cstride,
                c_st_r = c->row_stride * c->block->cstride,
                c_st_c = c->col_stride * c->block->cstride;
    vsip_length c_r_l  = c->row_length;  /* j_size */
    vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *cp_r = (c->block->R->array) + c->offset * c->block->cstride,
                  *cp_i = (c->block->I->array) + c->offset * c->block->cstride;

    /* some additional pointers to store initial data */
    vsip_scalar_f *ap0_r = ap_r, *ap0_i = ap_i, *bp0_r, *bp0_i, *cp0_r, *cp0_i;
    register vsip_scalar_f a00_r, a01_r, a02_r, a00_i, a01_i, a02_i;
    register vsip_scalar_f a10_r, a11_r, a12_r, a10_i, a11_i, a12_i;
    register vsip_scalar_f a20_r, a21_r, a22_r, a20_i, a21_i, a22_i;

    /* we need local storage for a column of b */
    register vsip_scalar_f b0_r, b1_r;
    register vsip_scalar_f b0_i, b1_i;

    vsip_length i; /* need a counter */

    /* we copy matrix a to local storage */
    a00_r = *ap0_r, a00_i = *ap0_i; 
         ap0_r+=a_st_r; ap0_i += a_st_r;
    a01_r = *ap0_r, a01_i = *ap0_i; 
         ap0_r = ap_r + a_st_c; ap0_i = ap_i + a_st_c;
    a10_r = *ap0_r, a10_i = *ap0_i; 
         ap0_r+=a_st_r; ap0_i += a_st_r;
    a11_r = *ap0_r, a11_i = *ap0_i; 

    for(i=0; i< c_r_l; i++){
       /* copy i'th column of b into local */
          bp0_r = bp_r + (vsip_stride)i * b_st_r; 
          bp0_i = bp_i + (vsip_stride)i * b_st_r;
       b0_r = *bp0_r; b0_i = *bp0_i; 
          bp0_r += b_st_c; bp0_i += b_st_c;
       b1_r = *bp0_r; b1_i = *bp0_i;
       /* get the pointer to the column where output will go */
       cp0_r = cp_r + (vsip_stride)i * c_st_r; cp0_i = cp_i + (vsip_stride)i * c_st_r;
       /* do the math */
          /* the real part */
       *cp0_r = (a00_r * b0_r + a01_r * b1_r) - (a00_i * b0_i + a01_i * b1_i ); cp0_r += c_st_c;
       *cp0_r = (a10_r * b0_r + a11_r * b1_r) - (a10_i * b0_i + a11_i * b1_i ); 
          /* the imaginary part */
       *cp0_i = a00_r * b0_i + a01_r * b1_i + a00_i * b0_r + a01_i * b1_r  ; cp0_i += c_st_c;
       *cp0_i = a10_r * b0_i + a11_r * b1_i + a10_i * b0_r + a11_i * b1_r  ;
    }
}
