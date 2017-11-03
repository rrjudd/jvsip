/*
 //  vsip_cmrandn_f.c
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

#include"VI_cmcolview_f.h"
#include"VI_cmrowview_f.h"
#include"vsip.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_vviewattributes_f.h"
#include"vsip_randobject.h"

static void cvrandu_f(
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
         *rpr  = (vsip_scalar_f)X/4294967296.0;
         rpr  += rst;
         X    = a * X + c;
         *rpi  = (vsip_scalar_f)X/4294967296.0;
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
         *rpr  = (vsip_scalar_f)itemp/4294967296.0;
         rpr   += rst;
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         } 
         *rpi  = (vsip_scalar_f)itemp/4294967296.0;
         rpi  += rst;
      }
   }
   return;
}


void vsip_cmrandu_f(
     vsip_randstate *state,
     const vsip_cmview_f *A)
{
   vsip_index i;
   vsip_cvview_f v;
   vsip_length M=A->col_length, N=A->row_length;
   vsip_stride CS=A->col_stride, RS=A->row_stride;
   if (CS < RS){ /* do by column */
       for (i=0; i<N; i++){
            VI_cmcolview_f(A,i,&v);
            cvrandu_f(state,&v);
       }
   } else { /* do by row */
        for (i=0; i<M; i++){
            VI_cmrowview_f(A,i,&v);
            cvrandu_f(state,&v);
       }
   }
} 
