/* Created RJudd September 19, 2000 */
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
/* $Id: vsip_cvbind_d.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */

#include<vsip.h>
#include"vsip_cvviewattributes_d.h"

vsip_cvview_d* (vsip_cvbind_d)(
  const vsip_cblock_d* b, 
  vsip_offset o, 
  vsip_stride s, 
  vsip_length n) {
    vsip_cvview_d* v = (vsip_cvview_d*)malloc(sizeof(vsip_cvview_d));
    if(v != (vsip_cvview_d*)NULL){
       v->block  = (vsip_cblock_d*)b;
       v->offset = o;
       v->stride = s;
       v->length = n;
       v->markings = VSIP_VALID_STRUCTURE_OBJECT;
    }
    return v;
}

