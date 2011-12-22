/* Created RJudd February 17, 2000 */
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
/* $Id: vsip_mcloneview_bl.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_bl.h>

vsip_mview_bl* vsip_mcloneview_bl(
      const vsip_mview_bl* mview_bl) 
{
   vsip_mview_bl* mcloneview_bl = (vsip_mview_bl*)malloc(sizeof(vsip_mview_bl));
   if(mcloneview_bl != NULL){
       *mcloneview_bl = *mview_bl;
   }
   return mcloneview_bl;
}
