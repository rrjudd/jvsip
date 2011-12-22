/* Created RJudd For Core January 10, 1998 */
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
/* $Id: vsip_vcreate_hanning_f.c,v 2.1 2003/04/22 02:19:59 judd Exp $ */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include"vsip_scalars.h"
#include"VI_vcreate_f.h"

#define twoPI 6.2831853071796

vsip_vview_f* (vsip_vcreate_hanning_f)(
  vsip_length N, vsip_memory_hint h) {
  vsip_vview_f *a;
    a  = VI_vcreate_f(N,h);
    if(a == NULL) return (vsip_vview_f*)NULL;
    {
      /*define variables*/
      vsip_length n =  0;
      vsip_scalar_f *ap  = (a->block->array) + a->offset,
                    temp = (vsip_scalar_f)twoPI/(N+1);
      /*end define*/
      /* Note this is always unit stride */
      while(n++ < N ){
         *ap++ = (vsip_scalar_f)0.5 * ((vsip_scalar_f)1. - (vsip_scalar_f)VSIP_COS_F(temp * (vsip_scalar_f) n));
      }
    }
    return a;
}
