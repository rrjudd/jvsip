/* Created RJudd September 18, 2000 */
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
/* $Id: vsip_cvcreate_f.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */

#include<vsip.h>
#include"VI_cblockcreate_f.h"
#include"VI_cblockdestroy_f.h"

vsip_cvview_f* (vsip_cvcreate_f)(
  vsip_length n, 
  vsip_memory_hint h) {
   vsip_cblock_f* b = VI_cblockcreate_f((size_t)n, h);
   vsip_cvview_f* v = (vsip_cvview_f*)NULL;
   if(b != (vsip_cblock_f*)NULL){
      v = vsip_cvbind_f(b, (vsip_offset)0, (vsip_stride)1, n);
      if(v == (vsip_cvview_f*)NULL) VI_cblockdestroy_f(b);
   }
   return v;
}
