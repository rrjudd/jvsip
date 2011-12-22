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
/* $Id: vsip_mprod3_d.c,v 2.2 2006/04/27 01:58:00 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>

void (vsip_mprod3_d)(
    const vsip_mview_d* a,
    const vsip_mview_d* b,
    const vsip_mview_d* r)
{
    /* st_r-> row stride, st_c=>col stride */
    vsip_index j;
    vsip_stride a_st_r = a->row_stride * a->block->rstride,
                a_st_c = a->col_stride * a->block->rstride,
                b_st_r = b->row_stride * b->block->rstride,
                b_st_c = b->col_stride * b->block->rstride,
                r_st_r = r->row_stride * r->block->rstride,
                r_st_c = r->col_stride * r->block->rstride;

    vsip_length r_r_l  = r->row_length;  /* j_size */

    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                  *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *ap0 = ap;

    vsip_scalar_d *b0p = bp;
    vsip_scalar_d *b1p = b0p + b_st_c;
    vsip_scalar_d *b2p = b1p + b_st_c;

    vsip_scalar_d *r0p = rp;
    vsip_scalar_d *r1p = r0p + r_st_c;
    vsip_scalar_d *r2p = r1p + r_st_c;

    register vsip_scalar_d a00,a01,a02;
    register vsip_scalar_d a10,a11,a12;
    register vsip_scalar_d a20,a21,a22;
    {  vsip_stride chk_c = (a_st_c > 0) ? a_st_c : -a_st_c;
       vsip_stride chk_r = (a_st_r > 0) ? a_st_r : -a_st_r;
       if(chk_c < chk_r){
          a00 = *ap0; ap0+=a_st_c; a10 = *ap0; ap0+=a_st_c; a20 = *ap0; 
          ap0 = ap + a_st_r;
          a01 = *ap0; ap0+=a_st_c; a11 = *ap0; ap0+=a_st_c; a21 = *ap0;
          ap0 = ap + 2 * a_st_r;
          a02 = *ap0; ap0+=a_st_c; a12 = *ap0; ap0+=a_st_c; a22 = *ap0; 
       } else {
          a00 = *ap0; ap0+=a_st_r; a01 = *ap0; ap0+=a_st_r; a02 = *ap0; 
          ap0 = ap + a_st_c;
          a10 = *ap0; ap0+=a_st_r; a11 = *ap0; ap0+=a_st_r; a12 = *ap0; 
          ap0 = ap + 2 * a_st_c;
          a20 = *ap0; ap0+=a_st_r; a21 = *ap0; ap0+=a_st_r; a22 = *ap0; 
       }
    }
    for( j=0; j<r_r_l; j++){
       register vsip_scalar_d b0 = *b0p, b1 = *b1p, b2 = *b2p;
       *r0p = a00 * b0 + a01 * b1 + a02 * b2;
       *r1p = a10 * b0 + a11 * b1 + a12 * b2;
       *r2p = a20 * b0 + a21 * b1 + a22 * b2;
       b0p += b_st_r; b1p += b_st_r; b2p += b_st_r; 
       r0p += r_st_r; r1p += r_st_r; r2p += r_st_r; 
    }
}
