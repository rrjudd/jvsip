/* Created RJudd March 14, 1998 */
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
/* $Id: vsip_cmvprod_d.c,v 2.2 2006/04/18 17:04:53 judd Exp $ */
/* Modified to vsip_cmvprod_d.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>

void (vsip_cmvprod_d)(
  const vsip_cmview_d* A,
  const vsip_cvview_d* b,
  const vsip_cvview_d* r) {
   if((A->block->cstride == 2) && (b->block->cstride == 2) && (r->block->cstride == 2)){
      vsip_length nx = 0, mx = 0;
      vsip_stride cbst = b->block->cstride, crst = b->block->cstride, cAst = A->block->cstride;
      vsip_scalar_d  *bp_r  = (vsip_scalar_d*)(b->block->R->array + cbst * b->offset),
                     *rp_r  = (vsip_scalar_d*)(r->block->R->array + crst * r->offset),
                     *Axp_r = (vsip_scalar_d*)(A->block->R->array + cAst * A->offset),
                     *Aypr = Axp_r;
       vsip_stride stb = cbst * b->stride, str = crst * r->stride, stA = cAst * A->row_stride;
       vsip_scalar_d dot_r, dot_i;
       while(nx++ < A->col_length){
           mx = 0;
           dot_r = 0; dot_i = 0;
           while(mx++ < A->row_length){
               vsip_scalar_d Ar = *Axp_r, Ai = *(Axp_r + 1);
               vsip_scalar_d br = *bp_r, bi = *(bp_r + 1);
               dot_r += br * Ar - bi * Ai;
               dot_i += br * Ai + bi * Ar;
               bp_r += stb; Axp_r += stA;
           }
           *rp_r = dot_r; *(rp_r + 1) = dot_i;
           bp_r = (vsip_scalar_d*)(b->block->R->array + cbst * b->offset);
           Axp_r = (Aypr += (cAst * A->col_stride));
           rp_r += str;
      }   
   } else { 
      vsip_length nx = 0, mx = 0;
      vsip_stride cbst = b->block->cstride, crst = r->block->cstride, cAst = A->block->cstride;
      vsip_scalar_d  *bp_r  = (vsip_scalar_d*)(b->block->R->array + cbst * b->offset),
                     *bp_i  = (vsip_scalar_d*)(b->block->I->array + cbst * b->offset),
                     *rp_r  = (vsip_scalar_d*)(r->block->R->array + crst * r->offset),
                     *rp_i  = (vsip_scalar_d*)(r->block->I->array + crst * r->offset),
                     *Axp_r = (vsip_scalar_d*)(A->block->R->array + cAst * A->offset),
                     *Axp_i = (vsip_scalar_d*)(A->block->I->array + cAst * A->offset),
                     *Aypr = Axp_r,
                     *Aypi = Axp_i;
       vsip_stride stb = cbst * b->stride, str = crst * r->stride, stA = cAst * A->row_stride;
       vsip_scalar_d dot_r, dot_i;
       while(nx++ < A->col_length){
           dot_r = 0; dot_i = 0;
           mx = 0;
           while(mx++ < A->row_length){
               dot_r += *bp_r * *Axp_r - *bp_i * *Axp_i;
               dot_i += *bp_r * *Axp_i + *bp_i * *Axp_r;
               bp_r += stb; Axp_r += stA;
               bp_i += stb; Axp_i += stA;
           }
           *rp_r = dot_r; *rp_i = dot_i;
           bp_r = (vsip_scalar_d*)(b->block->R->array + cbst * b->offset);
           bp_i = (vsip_scalar_d*)(b->block->I->array + cbst * b->offset);
           Axp_r = (Aypr += (cAst * A->col_stride));
           Axp_i = (Aypi += (cAst * A->col_stride));
           rp_r += str; rp_i += str;
      }   
   }
}

