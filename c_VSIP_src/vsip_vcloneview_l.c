/* Created RJudd March 6, 2000 */
/* to vsip_scalar_l version */
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
/* $Id: vsip_vcloneview_l.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_l.h>

vsip_vview_l* vsip_vcloneview_l(
      const vsip_vview_l* vview_l)
{
   vsip_vview_l* vcloneview_l = (vsip_vview_l*)malloc(sizeof(vsip_vview_l));
   if(vcloneview_l != NULL){
       *vcloneview_l = *vview_l;
   }
   return vcloneview_l;
}
