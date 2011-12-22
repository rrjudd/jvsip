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
/* $Id: vsip_vcloneview_f.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

vsip_vview_f* vsip_vcloneview_f(
      const vsip_vview_f* vview_f)
{
   vsip_vview_f* vcloneview_f = (vsip_vview_f*)malloc(sizeof(vsip_vview_f));
   if(vcloneview_f != NULL){
       *vcloneview_f = *vview_f;
   }
   return vcloneview_f;
}
