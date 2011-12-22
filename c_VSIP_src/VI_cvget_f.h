/* Created RJudd August 11, 2002 */
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
/* $Id: VI_cvget_f.h,v 2.0 2003/02/22 15:18:31 judd Exp $ */

#ifndef VI_CVGET_F_H
#define VI_CVGET_F_H 1

#include<vsip.h>
#include<vsip_cblockattributes_f.h>
#include<vsip_cvviewattributes_f.h>

/* get and store a value in the internal block scalar storage */
#define VI_CVGETP_F(v, k) { vsip_offset o = (v)->block->cstride * ((v)->offset + (vsip_stride)(k) * (v)->stride); \
                            (v)->block->a_scalar.r = *((v)->block->R->array + o); \
                            (v)->block->a_scalar.i = *((v)->block->I->array + o);} 

/* retrieve the value stored in the internal block scalar storage */
#define VI_CVGET_F(v) ((v)->block->a_scalar)

#endif /* VI_CVGET_F_H */
