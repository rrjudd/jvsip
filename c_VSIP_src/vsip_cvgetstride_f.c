/* Created RJudd September 30, 2000 */
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
/* $Id: vsip_cvgetstride_f.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */

#include"vsip.h"
#include"vsip_cvviewattributes_f.h"

vsip_stride (vsip_cvgetstride_f)(
  const vsip_cvview_f* v) {
    return v->stride;
}
