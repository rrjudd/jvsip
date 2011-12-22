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
/* $Id: vsip_cvrandu_f.c,v 2.0 2003/02/22 15:18:51 judd Exp $ */
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_randobject.h>

void vsip_cvrandu_f(
     vsip_randstate *state,
     const vsip_cvview_f *r)
{
   if(state->type)
   { /* nonportable generator */
      vsip_scalar_ue32 a = state->a,
                      c = state->c,
                      X = state->X;
      vsip_length n = r->length;
      /* register */ vsip_stride rst = r->stride * r->block->cstride;
      vsip_scalar_f *rpr = (r->block->R->array) + r->offset * r->block->cstride;
      vsip_scalar_f *rpi = (r->block->I->array) + r->offset * r->block->cstride;
      while(n-- > 0){
         X    = a * X + c;
         *rpr  = (vsip_scalar_f)X/(vsip_scalar_f)4294967296.0;
         rpr  += rst;
         X    = a * X + c;
         *rpi  = (vsip_scalar_f)X/(vsip_scalar_f)4294967296.0;
         rpi  += rst;
      }  
      state->X = X;
   } else { /* portable generator */
      vsip_scalar_ue32 itemp;
      vsip_length n = r->length;
      /* register */ vsip_stride rst = r->stride * r->block->cstride;
      vsip_scalar_f *rpr = (r->block->R->array) + r->offset * r->block->cstride;
      vsip_scalar_f *rpi = (r->block->I->array) + r->offset * r->block->cstride;
      while(n-- > 0){
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         itemp = (itemp>>8) | 0x00000001;
         *rpr  = (vsip_scalar_f)itemp/(vsip_scalar_f)16777216.0;
         rpr   += rst;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         } 
         itemp = (itemp>>8) | 0x00000001;
         *rpi  = (vsip_scalar_f)itemp/(vsip_scalar_f)16777216.0;
         rpi  += rst;
      }
   }
   return;
}
