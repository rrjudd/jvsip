/* Created RJudd September 21, 2000 */
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
/* $Id: VI_vdestroy_f.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#ifndef VI_VDESTROY_F_H
#define VI_VDESTROY_F_H

static
vsip_block_f* 
VI_vdestroy_f(
        vsip_vview_f* v){
   vsip_block_f* b = (vsip_block_f*)NULL;
   if(v != (vsip_vview_f*)NULL){
      b = v->block;
      v->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free((void*)v);
   }
   return b;
}
#endif
