/* Created RJudd September 15, 2000 */
/* SPAWARSYSCEN D857                */
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
/* $Id: VI_blockdestroy_f.h,v 2.0 2003/02/22 15:18:27 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_f.h>

#ifndef VI_BLOCKDESTROY_F_H
#define VI_BLOCKDESTROY_F_H

static
void 
VI_blockdestroy_f(
  vsip_block_f* b) {
  if (NULL != b) {     /* destroying NULL is harmless */
     if(b->kind != 2){ /* derived destroyed when parent destroyed */
        b->markings = VSIP_FREED_STRUCTURE_OBJECT;
        if (b->kind == VSIP_VSIPL_BLOCK) free((void*)b->array);
        free((void*)b);
     }
  }
  return;
}
#endif
