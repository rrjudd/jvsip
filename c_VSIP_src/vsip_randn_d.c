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
/* $Id: vsip_randn_d.c,v 2.0 2003/02/22 15:19:02 judd Exp $ */
#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_randobject.h"

vsip_scalar_d vsip_randn_d(
     vsip_randstate *state)
{
   vsip_index i;
   vsip_scalar_d rp;
   if(state->type)
   { /* nonportable generator */
      vsip_scalar_ue32 a = state->a,
                      c = state->c,
                      X = state->X;
      rp = 0;
      for(i=0; i<12; i++){
          X    = a * X + c;
          rp  += (vsip_scalar_d)X/4294967296.0;
      }
      state->X = X;
      rp -= 6.0;
   } else { /* portable generator */
      vsip_scalar_ue32 itemp;
      rp = 0;
      for(i=0; i<12; i++){
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         rp  += (vsip_scalar_d)itemp/4294967296.0;
      }
      rp = 6.0 - rp;
   }
   return rp;
}
