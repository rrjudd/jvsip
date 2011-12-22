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
/* $Id: vsip_cfir_getattr_f.c,v 2.0 2003/02/22 15:18:40 judd Exp $ */
#include<vsip.h>
#include<vsip_cfirattributes_f.h>

void vsip_cfir_getattr_f(
     const vsip_cfir_f *fir,
     vsip_cfir_attr *attr)
{
    attr->symm = fir->symm;
    attr->kernel_len = fir->M;
    attr->decimation = fir->D;
    attr->in_len = fir->N;
    attr->out_len = fir->N/fir->D + ((fir->N % fir->D) ? 1:0);
    attr->state = fir->state;
    return;
}
