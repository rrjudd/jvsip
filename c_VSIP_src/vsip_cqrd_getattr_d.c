/* Created RJudd August 29, 1999 */
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
/* $Id: vsip_cqrd_getattr_d.c,v 2.0 2003/02/22 15:18:46 judd Exp $ */

#include<vsip.h>
#include<vsip_cqrdattributes_d.h>

void vsip_cqrd_getattr_d(
         const vsip_cqr_d *qr,
         vsip_cqr_attr_d *attr)
{
      attr->m = qr->M;
      attr->n = qr->N;
      attr->Qopt = qr->qopt;
      return;
}
