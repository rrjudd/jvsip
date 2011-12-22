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
/* $Id: vsip_mcloneview_f.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>

vsip_mview_f* vsip_mcloneview_f(
      const vsip_mview_f* mview_f)
{
   vsip_mview_f* mcloneview_f = (vsip_mview_f*)malloc(sizeof(vsip_mview_f));
   if(mcloneview_f != NULL){
       *mcloneview_f = *mview_f;
   }
   return mcloneview_f;
}
