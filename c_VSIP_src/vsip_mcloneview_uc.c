/* Created RJudd */
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
/* $Id: vsip_mcloneview_uc.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_uc.h>

vsip_mview_uc* vsip_mcloneview_uc(
      const vsip_mview_uc* mview_uc) 
{
   vsip_mview_uc* mcloneview_uc = (vsip_mview_uc*)malloc(sizeof(vsip_mview_uc));
   if(mcloneview_uc != NULL){
       *mcloneview_uc = *mview_uc;
   }
   return mcloneview_uc;
}
