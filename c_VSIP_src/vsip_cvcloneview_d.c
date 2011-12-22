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
/* $Id: vsip_cvcloneview_d.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

vsip_cvview_d* vsip_cvcloneview_d(
      const vsip_cvview_d* cvview_d)
{
   vsip_cvview_d* cvcloneview_d = (vsip_cvview_d*)malloc(sizeof(vsip_cvview_d));
   if(cvcloneview_d != NULL){
       *cvcloneview_d = *cvview_d;
   }
   return cvcloneview_d;
}
