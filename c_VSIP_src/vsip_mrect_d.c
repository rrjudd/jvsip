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
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"vsip_scalars.h"
#include"VI_mrowview_d.h"
#include"VI_mcolview_d.h"
#include"VI_cmrowview_d.h"
#include"VI_cmcolview_d.h"

static void vrect_d(vsip_vview_d* r, vsip_vview_d* t, vsip_cvview_d* a) {
   vsip_length n = r->length;
   vsip_stride cast = a->block->cstride, rrst = r->block->rstride, trst = r->block->rstride;
   vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
   *rp  = (vsip_scalar_d*) ((r->block->array) + rrst * r->offset),
   *tp  = (vsip_scalar_d*) ((t->block->array) + trst * t->offset);
   vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset);
   vsip_scalar_d  temp = 0;
   vsip_stride ast = cast * a->stride, rst = rrst * r->stride, tst = trst * t->stride;
   while(n-- > 0){ temp = *rp * VSIP_SIN_D(*tp); *apr = *rp * VSIP_COS_D(*tp); 
      *api = temp; apr += ast; api += ast; rp += rst; tp += tst; }
}

void vsip_mrect_d( const vsip_mview_d* r, const vsip_mview_d *t, const vsip_cmview_d* a){
   vsip_index i;
   vsip_vview_d rv; vsip_vview_d tv; vsip_cvview_d av;
   if(a->row_stride < a->col_stride){
      for(i=0; i < a->col_length; i++){
         VI_mrowview_d(r,i,&rv); VI_mrowview_d(t,i,&tv);VI_cmrowview_d(a,i,&av);
         vrect_d(&rv,&tv,&av);
      }
   } else {
      for(i=0; i < a->col_length; i++){
         VI_mcolview_d(r,i,&rv); VI_mcolview_d(t,i,&tv);VI_cmcolview_d(a,i,&av);
         vrect_d(&rv,&tv,&av);
      }
   }
}

