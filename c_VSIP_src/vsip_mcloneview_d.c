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
/* $Id: vsip_mcloneview_d.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>

vsip_mview_d* vsip_mcloneview_d(
      const vsip_mview_d* mview_d)
{
   vsip_mview_d* mcloneview_d = (vsip_mview_d*)malloc(sizeof(vsip_mview_d));
   if(mcloneview_d != NULL){
       *mcloneview_d = *mview_d;
   }
   return mcloneview_d;
}
