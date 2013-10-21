/* Created RJudd March 18, 2012 */
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
#include"VI_mrowview_d.h"
#include"VI_mcolview_d.h"
#include"VI_cmrowview_d.h"
#include"VI_cmcolview_d.h"

static void vcmplx_d(const vsip_vview_d* a, const vsip_vview_d* b, const vsip_cvview_d* r) { 
    vsip_length n = r->length;
    vsip_stride crst = r->block->cstride;
    vsip_scalar_d 
    *ap  = (vsip_scalar_d*) (a->block->array)      +  a->offset * a->block->rstride,
    *bp  = (vsip_scalar_d*) (b->block->array)      +  b->offset * b->block->rstride,
    *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset),
    *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
    vsip_scalar_d  temp;
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


void vsip_mcmplx_d(const vsip_mview_d* a, const vsip_mview_d* b, const vsip_cmview_d* r){
    vsip_index i;
    vsip_vview_d av; vsip_vview_d bv; vsip_cvview_d rv;
    if(a->row_stride < a->col_stride){
        for(i=0; i < a->col_length; i++){
            VI_mrowview_d(a,i,&av); VI_mrowview_d(b,i,&bv);VI_cmrowview_d(r,i,&rv);
            vcmplx_d(&av,&bv,&rv);
        }
    } else {
        for(i=0; i < a->col_length; i++){
            VI_mcolview_d(a,i,&av); VI_mcolview_d(b,i,&bv);VI_cmcolview_d(r,i,&rv);
            vcmplx_d(&av,&bv,&rv);
        }
    }
    
}

