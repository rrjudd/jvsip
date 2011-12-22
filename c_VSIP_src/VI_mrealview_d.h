/* Created RJudd October 6, 2000 */
/* SPAWARSYSCEN D857             */
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
/* $Id: VI_mrealview_d.h,v 2.1 2003/03/09 22:41:17 judd Exp $ */
#ifndef _VI_MREALVIEW_D_H
#define _VI_MREALVIEW_D_H

#include<vsip_cmviewattributes_d.h>
#include<vsip_mviewattributes_d.h>

static
vsip_mview_d* VI_mrealview_d(
          const vsip_cmview_d* X, 
          vsip_mview_d* Y)
{
     Y->block = X->block->R;
     Y->offset = X->offset;
     Y->row_length = X->row_length;
     Y->col_length = X->col_length;
     Y->row_stride = X->row_stride;
     Y->col_stride = X->col_stride;
     Y->markings = VSIP_VALID_STRUCTURE_OBJECT;
     return Y;
}

#endif /* _VI_MREALVIEW_D_H */
