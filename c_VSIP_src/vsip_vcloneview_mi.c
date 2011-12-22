/* Created RJudd March 6, 2000 */
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
/* $Id: vsip_vcloneview_mi.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_mi.h>

vsip_vview_mi* vsip_vcloneview_mi(
      const vsip_vview_mi* vview_mi)
{
   vsip_vview_mi* vcloneview_mi = (vsip_vview_mi*)malloc(sizeof(vsip_vview_mi));
   if(vcloneview_mi != NULL){
       *vcloneview_mi = *vview_mi;
   }
   return vcloneview_mi;
}
