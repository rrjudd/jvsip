/* Created RJudd August 30, 2002 */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_cchold_getattr_d.c,v 2.0 2003/02/22 15:18:40 judd Exp $ */
#include<vsip.h>
#include<vsip_ccholdattributes_d.h>

void
vsip_cchold_getattr_d(
          const vsip_cchol_d *chol,
          vsip_cchol_attr_d *attr)
{
   attr->n = chol->N;
   attr->uplo = chol->uplo;
   return;
}
