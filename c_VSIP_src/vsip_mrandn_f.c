/*
 //  vsip_mrandn_f.c
 //  jvsipF
 //
 //  Created by RANDALL JUDD on 9/14/13.
 //  Copyright (c) 2013 Independent Consultant. All rights reserved.
 */
/*********************************************************************
 // This code includes no warranty, express or implied, including     /
 // the warranties of merchantability and fitness for a particular    /
 // purpose.                                                          /
 // No person or entity assumes any legal liability or responsibility /
 // for the accuracy, completeness, or usefulness of any information, /
 // apparatus, product, or process disclosed, or represents that      /
 // its use would not infringe privately owned rights.                /
 *********************************************************************/
/*********************************************************************
 // The MIT License (see copyright for jvsip in top level directory)
 // http://opensource.org/licenses/MIT
 **********************************************************************/
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_randobject.h>
#include"VI_mcolview_f.h"
#include"VI_mrowview_f.h"

static void vrandn_f(
    vsip_randstate *state,
    const vsip_vview_f *r)
{
   vsip_index i;
   if(state->type)
   { /* nonportable generator */
      vsip_scalar_ue32 a = state->a,
                      c = state->c,
                      X = state->X;
      vsip_length n = r->length;
      vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         *rp = 0.0;
         for(i=0; i<12; i++){
            X    = a * X + c;
            *rp  += (vsip_scalar_f)X/(vsip_scalar_f)4294967296.0;
         }
         *rp -= 6.0;
         rp  += rst;
      }  
      state->X = X;
   } else { /* portable generator */
      vsip_scalar_ue32 itemp;
      vsip_length n = r->length;
      vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         *rp = 0.0;
         for(i=0; i<12; i++){
            state->X  = state->X * state->a + state->c;
            state->X1 = state->X1 * state->a1 + state->c1;
            itemp     = state->X - state->X1;
            if(state->X1 == state->X2){
               state->X1++;
               state->X2++;
            }
            itemp = (itemp>>8) | 0x00000001;
            *rp  += (vsip_scalar_f)itemp/(vsip_scalar_f)16777216.0;
         }
         *rp = (vsip_scalar_f)6.0 - *rp;
         rp   += rst;
      }
   }
}

void vsip_mrandn_f(
     vsip_randstate *state,
     const vsip_mview_f *A)
{
   vsip_index i;
   vsip_vview_f v;
   vsip_length M=A->col_length, N=A->row_length;
   vsip_stride CS=A->col_stride, RS=A->row_stride;
   if (CS < RS){ /* do by column */
       for (i=0; i<N; i++){
            VI_mcolview_f(A,i,&v);
            vrandn_f(state,&v);
       }
   } else { /* do by row */
        for (i=0; i<M; i++){
            VI_mrowview_f(A,i,&v);
            vrandn_f(state,&v);
       }
   }
} 
