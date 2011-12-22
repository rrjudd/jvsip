/* Created RJudd December 13 1997 */
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
/* $Id: vsip_vcmagsq_f.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_vcmagsq_f)(
  const vsip_cvview_f* a,
  const vsip_vview_f* r) {
  { 
    /* register */ vsip_length n = r->length;
    vsip_stride cast = a->block->cstride;
    vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                  *rp  = (vsip_scalar_f*) ((r->block->array) + r->offset * r->block->rstride);
    vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
    /* register */ vsip_stride ast = (cast * a->stride),
                               rst = r->stride * r->block->rstride;
    while(n-- > 0){
       *rp = *apr * *apr + *api * *api;
       apr += ast; api += ast; 
       rp  += rst;
    }
  }
}

