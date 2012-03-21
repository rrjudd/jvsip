/* Created RJudd March 18, 2018 */
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
#include<vsip.h>
#include"VI_mrowview_f.h"
#include"VI_mcolview_f.h"
#include"VI_cmrowview_f.h"
#include"VI_cmcolview_f.h"

static void vcmplx_f(const vsip_vview_f* a, const vsip_vview_f* b, const vsip_cvview_f* r) { 
    vsip_length n = r->length;
    vsip_stride crst = r->block->cstride;
    vsip_scalar_f 
    *ap  = (vsip_scalar_f*) (a->block->array)      +  a->offset * a->block->rstride,
    *bp  = (vsip_scalar_f*) (b->block->array)      +  b->offset * b->block->rstride,
    *rpr = (vsip_scalar_f*) ((r->block->R->array) + crst * r->offset),
    *rpi = (vsip_scalar_f*) ((r->block->I->array) + crst * r->offset);
    vsip_scalar_f  temp;
    vsip_stride ast = a->stride * a->block->rstride,
    bst = b->stride * b->block->rstride,
    rst = crst * r->stride;
    while(n-- > 0){
        temp = *ap;
        *rpi = *bp;
        *rpr = temp;
        ap += ast;
        bp += bst;
        rpr += rst; rpi += rst;
    }
}


void vsip_mcmplx_f(const vsip_mview_f* a, const vsip_mview_f* b, const vsip_cmview_f* r){
    vsip_index i;
    vsip_vview_f av; vsip_vview_f bv; vsip_cvview_f rv;
    if(a->row_stride < a->col_stride){
        for(i=0; i < a->col_length; i++){
            VI_mrowview_f(a,i,&av); VI_mrowview_f(b,i,&bv);VI_cmrowview_f(r,i,&rv);
            vcmplx_f(&av,&bv,&rv);
        }
    } else {
        for(i=0; i < a->col_length; i++){
            VI_mcolview_f(a,i,&av); VI_mcolview_f(b,i,&bv);VI_cmcolview_f(r,i,&rv);
            vcmplx_f(&av,&bv,&rv);
        }
    }
    
}