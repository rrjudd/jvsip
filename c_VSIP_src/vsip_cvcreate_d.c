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
/* $Id: vsip_cvcreate_d.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */

#include<vsip.h>
#include"VI_cblockcreate_d.h"
#include"VI_cblockdestroy_d.h"

vsip_cvview_d* (vsip_cvcreate_d)(
  vsip_length n, 
  vsip_memory_hint h) {
   vsip_cblock_d* b = VI_cblockcreate_d((size_t)n, h);
   vsip_cvview_d* v = (vsip_cvview_d*)NULL;
   if(b != (vsip_cblock_d*)NULL){
       v = vsip_cvbind_d(b, (vsip_offset)0, (vsip_stride)1, n);
       if(v == (vsip_cvview_d*)NULL) VI_cblockdestroy_d(b);
   }
   return v;
}

