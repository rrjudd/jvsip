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
/* $Id: vsip_vrandu_f.c,v 2.0 2003/02/22 15:19:17 judd Exp $ */
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_randobject.h>

void vsip_vrandu_f(
     vsip_randstate *state,
     const vsip_vview_f *r)
{
   if(state->type)
   { /* nonportable generator */
      vsip_scalar_ue32 a = state->a,
                      c = state->c,
                      X = state->X;
      vsip_length n = r->length;
      /* register */ vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         X    = a * X + c;
         *rp  = (vsip_scalar_f)X/(vsip_scalar_f)4294967296.0;
         rp  += rst;
      }  
      state->X = X;
   } else { /* portable generator */
      vsip_scalar_ue32 itemp;
      vsip_length n = r->length;
      /* register */ vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         itemp = (itemp>>8) | 0x00000001;
         *rp  = (vsip_scalar_f)itemp/(vsip_scalar_f)16777216.0;
         rp   += rst;
      }
   }
}
