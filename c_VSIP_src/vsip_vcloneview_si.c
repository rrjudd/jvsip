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
/* $Id: vsip_vcloneview_si.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_si.h"

vsip_vview_si* vsip_vcloneview_si(
      const vsip_vview_si* vview_si)
{
   vsip_vview_si* vcloneview_si = (vsip_vview_si*)malloc(sizeof(vsip_vview_si));
   if(vcloneview_si != NULL){
       *vcloneview_si = *vview_si;
   }
   return vcloneview_si;
}
