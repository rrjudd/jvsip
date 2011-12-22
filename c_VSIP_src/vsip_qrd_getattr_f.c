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
/* $Id: vsip_qrd_getattr_f.c,v 2.0 2003/02/22 15:19:01 judd Exp $ */
#include<vsip.h>
#include<vsip_qrdattributes_f.h>

void vsip_qrd_getattr_f(
         const vsip_qr_f *qr,
         vsip_qr_attr_f *attr)
{
      attr->m = qr->M;
      attr->n = qr->N;
      attr->Qopt = qr->qopt;
      return;
}
