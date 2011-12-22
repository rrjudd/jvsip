/* Created R Judd March 6, 2000 */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_vindexbool.c,v 2.0 2003/02/22 15:19:14 judd Exp $ */
#include<vsip.h>
#include<vsip_blockattributes_vi.h>
#include<vsip_vviewattributes_vi.h>
#include<vsip_vviewattributes_bl.h>

vsip_length (vsip_vindexbool)(
    const vsip_vview_bl* v, 
    vsip_vview_vi* x) {
    vsip_length retval = 0;
    {
       vsip_stride n = -1;
       vsip_scalar_bl *vp = v->block->array + v->offset;
       vsip_scalar_vi *xp = x->block->array + x->offset;
       vsip_stride vst = v->stride,
                   xst = x->stride;
       while(n++ < (vsip_stride)(v->length - 1)){
          if(*vp != VSIP_FALSE){
              *xp = n;
               xp += xst;
               retval++;
          }
          vp += vst;     
       }
       if(retval > 0 ) x->length = retval;
    }
    return retval;
}
