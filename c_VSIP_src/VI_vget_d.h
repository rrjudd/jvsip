/* Created RJudd August 8, 2002 */
/* SPAWARSYSCEN */
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
/* $Id: VI_vget_d.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */
#ifndef VI_VGET_D_H
#define VI_VGET_D_H 1

#include<vsip.h>
#include<vsip_blockattributes_d.h>
#include<vsip_vviewattributes_d.h>

#define VI_VGET_D(v,i) (*(v->block->array + (v->offset + (vsip_stride)(i) * v->stride) * v->block->rstride))

#endif /* VI_VGET_D_H */
