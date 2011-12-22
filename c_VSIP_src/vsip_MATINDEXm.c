/* Created RJudd February 17, 1999 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_MATINDEXm.c,v 2.0 2003/02/22 15:18:36 judd Exp $ */

#include<vsip.h>

void (vsip_MATINDEX)(
  vsip_scalar_vi r, 
  vsip_scalar_vi c,
  vsip_scalar_mi *mi) {
  *mi = vsip_matindex(r,c);
}

