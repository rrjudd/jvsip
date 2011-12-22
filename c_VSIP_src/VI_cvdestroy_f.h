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
/* $Id: VI_cvdestroy_f.h,v 2.0 2003/02/22 15:18:31 judd Exp $ */

#include<vsip.h>
#include"vsip_cvviewattributes_f.h"
#ifndef VI_CVDESTROY_F_H
#define VI_CVDESTROY_F_H

static
vsip_cblock_f* 
VI_cvdestroy_f(
  vsip_cvview_f* v) {
   vsip_cblock_f* b = (vsip_cblock_f*)NULL;
   if(v != (vsip_cvview_f*)NULL){
      b = v->block;
      v->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free((void*)v);
   }
   return b;
}
#endif
