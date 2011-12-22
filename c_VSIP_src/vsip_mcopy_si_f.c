/* Created RJudd  */
/* SPAWARSYSCEN   */
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
/* $Id: vsip_mcopy_si_f.c,v 2.1 2004/04/03 16:03:08 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_si.h>

void (vsip_mcopy_si_f)(
         const vsip_mview_si* a,
         const vsip_mview_f* r) 
{
    vsip_length n_mj, /* major length */
               n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn;
    vsip_scalar_si *ap = (a->block->array) + a->offset;
    vsip_scalar_si *ap0 = ap;
    vsip_index i=0,j=0;
    /* pick direction dependent on input */
    if(a->row_stride < a->col_stride){ /* Row Major */
        n_mj = a->row_length; n_mn = a->col_length;
        ast_mj = a->row_stride; ast_mn = a->col_stride;
        while(n_mn-- > 0){
           vsip_length n = n_mj;
           while(n-- >0){
               vsip_mput_f(r,i,j,(vsip_scalar_f) *ap);
               ap += ast_mj; j++;
           }
           ap0 += ast_mn;
           ap = ap0; i++; j=0;
        }
    } else { /* must be Col Major */
        n_mn = a->row_length; n_mj = a->col_length;
        ast_mn = a->row_stride; ast_mj = a->col_stride;
        while(n_mn-- > 0){
           vsip_length n = n_mj;
           while(n-- >0){
               vsip_mput_f(r,i,j,(vsip_scalar_f) *ap);
               ap += ast_mj; i++;
           }
           ap0 += ast_mn;
           ap = ap0; i=0; j++;
        }
    }
    return;
}
