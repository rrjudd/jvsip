/* Created RJudd March 6, 2000 */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_vcloneview_d.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

vsip_vview_d* vsip_vcloneview_d(
      const vsip_vview_d* vview_d)
{
   vsip_vview_d* vcloneview_d = (vsip_vview_d*)malloc(sizeof(vsip_vview_d));
   if(vcloneview_d != NULL){
       *vcloneview_d = *vview_d;
   }
   return vcloneview_d;
}
