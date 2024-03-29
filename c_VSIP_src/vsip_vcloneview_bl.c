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
/* $Id: vsip_vcloneview_bl.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_bl.h"

vsip_vview_bl* vsip_vcloneview_bl(
      const vsip_vview_bl* vview_bl)
{
   vsip_vview_bl* vcloneview_bl = (vsip_vview_bl*)malloc(sizeof(vsip_vview_bl));
   if(vcloneview_bl != NULL){
       *vcloneview_bl = *vview_bl;
   }
   return vcloneview_bl;
}
