/* Created RJudd March 6, 2000 */
/* to vsip_scalar_i version */
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
/* $Id: vsip_vcloneview_i.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_i.h>

vsip_vview_i* vsip_vcloneview_i(
      const vsip_vview_i* vview_i)
{
   vsip_vview_i* vcloneview_i = (vsip_vview_i*)malloc(sizeof(vsip_vview_i));
   if(vcloneview_i != NULL){
       *vcloneview_i = *vview_i;
   }
   return vcloneview_i;
}
