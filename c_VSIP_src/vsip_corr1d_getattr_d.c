/* Created By Randall Judd April 8, 1999 */
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
/* $Id: vsip_corr1d_getattr_d.c,v 2.0 2003/02/22 15:18:45 judd Exp $ */

#include<vsip.h>
#include<vsip_corr1dattributes_d.h>

void vsip_corr1d_getattr_d(
      const vsip_corr1d_d *corr,
      vsip_corr1d_attr *attr)
{
      attr->ref_len  = corr->m;
      attr->data_len = corr->n;
      attr->lag_len  = corr->lag_len;
      attr->support  = corr->support;
      return;
}
