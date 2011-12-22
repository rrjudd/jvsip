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
/* $Id: vsip_malldestroy_bl.c,v 2.0 2003/02/22 15:18:53 judd Exp $ */

#include<vsip.h>

void (vsip_malldestroy_bl)(
  vsip_mview_bl* mview_bl) {
  if(mview_bl != NULL){
  vsip_blockdestroy_bl(vsip_mdestroy_bl(mview_bl));
  }
  return;
  }
