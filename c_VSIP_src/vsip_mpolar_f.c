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
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include"vsip_scalars.h"
#include"VI_mrowview_f.h"
#include"VI_mcolview_f.h"
#include"VI_cmrowview_f.h"
#include"VI_cmcolview_f.h"

static void vpolar_f(const vsip_cvview_f* a, const vsip_vview_f* r, const vsip_vview_f* t) {
   vsip_length n = r->length;
   vsip_stride cast = a->block->cstride,
   rrst = r->block->rstride,
   trst = t->block->rstride;
   vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
   *rp  = (vsip_scalar_f*) ((r->block->array) + rrst * r->offset),
   *tp  = (vsip_scalar_f*) ((t->block->array) + trst * t->offset);
   vsip_scalar_f *api =  (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
   vsip_scalar_f  tmp;
   vsip_stride ast = (cast * a->stride),
   rst = rrst * r->stride,
   tst = trst * t->stride;
   while(n-- > 0){
      tmp = (vsip_scalar_f)atan2(*api,*apr);
      *rp = (vsip_scalar_f)sqrt(*apr * *apr + *api * *api);
      *tp = tmp;
      apr += ast; api += ast;
      rp += rst; tp += tst;
   }
}


void vsip_mpolar_f(const vsip_cmview_f* a, const vsip_mview_f* r, const vsip_mview_f* t){
   vsip_index i;
   vsip_vview_f rv; vsip_vview_f tv; vsip_cvview_f av;
   if(a->row_stride < a->col_stride){
      for(i=0; i < a->col_length; i++){
         VI_mrowview_f(r,i,&rv); VI_mrowview_f(t,i,&tv);VI_cmrowview_f(a,i,&av);
         vpolar_f(&av,&rv,&tv);
      }
   } else {
      for(i=0; i < a->col_length; i++){
         VI_mcolview_f(r,i,&rv); VI_mcolview_f(t,i,&tv);VI_cmcolview_f(a,i,&av);
         vpolar_f(&av,&rv,&tv);
      }
   }
}

