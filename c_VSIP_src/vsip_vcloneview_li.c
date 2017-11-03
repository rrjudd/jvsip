/* Created RJudd March 6, 2000 */
/* to vsip_scalar_li version */
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
/* $Id: vsip_vcloneview_li.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_li.h"

vsip_vview_li* vsip_vcloneview_li(
      const vsip_vview_li* vview_li)
{
   vsip_vview_li* vcloneview_li = (vsip_vview_li*)malloc(sizeof(vsip_vview_li));
   if(vcloneview_li != NULL){
       *vcloneview_li = *vview_li;
   }
   return vcloneview_li;
}
