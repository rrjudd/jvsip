/* Created By Randall Judd */
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
/* $Id: vsip_fir_getattr_d.c,v 2.0 2003/02/22 15:18:53 judd Exp $ */

#include<vsip.h>
#include<vsip_firattributes_d.h>

void vsip_fir_getattr_d(
     const vsip_fir_d *fir,
     vsip_fir_attr *attr)
{
    attr->symm = fir->symm;
    attr->kernel_len = fir->M;
    attr->decimation = fir->D;
    attr->in_len = fir->N;
    attr->out_len = fir->N/fir->D + ((fir->N % fir->D) ? 1:0);
    attr->state = fir->state;
    return;
}
