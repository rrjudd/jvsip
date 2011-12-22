/* Created Randall Judd */
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
/* $Id: vsip_clud_getattr_d.c,v 2.0 2003/02/22 15:18:41 judd Exp $ */
/* modified RJudd attr->N to attr->n */
#include<vsip.h>
#include<vsip_cludattributes_d.h>

void vsip_clud_getattr_d(
          const vsip_clu_d *lud,
          vsip_clu_attr_d *attr)
{
   attr->n = lud->N;
   return;
}
