/*
 *  vsip_vsortip_d.c
 *
 *  Created by Randall Judd on 10/26/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *  It uses private information and is compatible with the tvcpp 
 *  reference implementation of VSIPL; however the functions are not
 *  yet approved for official inclusion into VSIPL
 *
 */

#include <vsip_blockattributes_d.h>
#include <vsip_vviewattributes_d.h>
#include <vsip_blockattributes_vi.h>
#include <vsip_vviewattributes_vi.h>
#include <vsip.h>

#define VRAMP(x) { \
    vsip_scalar_vi k; \
    vsip_scalar_vi *ind = x->block->array + x->offset; \
    vsip_stride str = x->stride; \
    for(k=0; k<x->length; k++){ \
        *ind = k; \
        ind += str;} \
}

/* below adaption of K&R qsort; section 4.10 */

/* return a derefrenced pointer to the i'th element in v */
#define VGET(v,i) (*(v->block->array+(vsip_offset) \
                     (v->block->rstride * (v->offset + (vsip_stride)i * v->stride))))

/* only float vectors have "rstride" in the current implementation So we need this too*/
#define VGET_VI(v,i) (*(v->block->array+(vsip_offset)  (v->offset + (vsip_stride)i * v->stride)))

#define SWAP(x,i,j) { /* x is float vector view; i,j are indices */ \
   vsip_scalar_d tmp = VGET(x,i); \
   VGET(x,i) = VGET(x,j); \
   VGET(x,j) = tmp; \
}

#define SWAP_VI(x,i,j) { /* x is vector view of type index; i,j are indices */ \
   vsip_scalar_vi tmp = VGET_VI(x,i); \
      VGET_VI(x,i) = VGET_VI(x,j); \
      VGET_VI(x,j) = tmp; \
}

static
void
VI_qsort_d(vsip_vview_d *v, vsip_index left, vsip_index right, vsip_vview_vi *vi){
   vsip_index i,last;
   vsip_index iright;
   if(left >= right){
      return;
   } else {
      iright = (vsip_index)(left+right)/2;
   }
   SWAP(v,left, iright);
   if(vi) SWAP_VI(vi,left,iright);
   last = left;
   for(i=left+1; i<= right; i++){
      if(VGET(v,i) < VGET(v,left)){
         last++;
         SWAP(v,last,i);
         if(vi) SWAP_VI(vi,last,i);
      }
   }
   SWAP(v,left,last);
   if(vi) SWAP_VI(vi,left,last);
   if(last > 0) VI_qsort_d(v,left,last-1,vi);
   VI_qsort_d(v,last+1,right,vi);
   return;
}

static
void
VI_qsortmag_d(vsip_vview_d *v, vsip_index left, vsip_index right, vsip_vview_vi *vi){
   vsip_index i,last;
   vsip_index iright;
   if(left >= right){
      return;
   } else {
      iright = (vsip_index)(left+right)/2;
   }
   SWAP(v,left, iright);
   if(vi) SWAP_VI(vi,left,iright);
   last = left;
   for(i=left+1; i<= right; i++){
      if(fabs(VGET(v,i)) < fabs(VGET(v,left))){
         last++;
         SWAP(v,last,i);
         if(vi) SWAP_VI(vi,last,i);
      }
   }
   SWAP(v,left,last);
   if(vi) SWAP_VI(vi,left,last);
   if(last > 0) VI_qsortmag_d(v,left,last-1,vi);
   VI_qsortmag_d(v,last+1,right,vi);
   return;
}

void vsip_vsortip_d(const vsip_vview_d *in_out, 
                  vsip_sort_mode mode, 
                  vsip_sort_dir dir, 
                  vsip_bool fill,
                  const vsip_vview_vi *vi0){
   vsip_vview_d in = *in_out;
   vsip_vview_vi viN,*vi;
   vi = &viN;
   if(vi0){ /* mirror sort an index */
      viN = *vi0;
      if(fill) VRAMP(vi);
   } else {
      vi = (vsip_vview_vi*)0;
   }
   if(dir == VSIP_SORT_DESCENDING){ /* need to go through vector backwards */
      in.offset += in.stride * (in.length-1);
      in.stride *= -1;
      if(vi0){
         vi->offset += (vi->length - 1) * vi->stride;
         vi->stride *= -1;
      }
   } 
   if(mode == VSIP_SORT_BYMAGNITUDE){
      VI_qsortmag_d(&in,(vsip_index) 0,(vsip_index)(in.length-1),vi);
   } else {
      VI_qsort_d(&in,(vsip_index) 0,(vsip_index)(in.length-1),vi);
   }
   return;
}
