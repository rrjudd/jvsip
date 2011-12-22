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
/* $Id: vsip_conv1d_getattr_d.c,v 2.0 2003/02/22 15:18:45 judd Exp $ */

#include<vsip.h>
#include<vsip_conv1dattributes_d.h>
void vsip_conv1d_getattr_d(
      const vsip_conv1d_d *conv,
      vsip_conv1d_attr *attr)
{
      attr->kernel_len = conv->nh;
      attr->symm       = conv->symm;
      attr->data_len   = conv->nx;
      attr->support    = conv->support;
      attr->out_len    = conv->Noutput;
      attr->decimation = conv->D;
      return;
}
