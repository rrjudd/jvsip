/* Created RJudd Nov 27, 2011 */
/*********************************************************************
// This code includes                                                 /
// no warranty, express or implied, including the warranties          /
// of merchantability and fitness for a particular purpose.           /
// No person or entity                                                /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
#include<vsip.h>
#include<vsip_blockattributes_d.h>
#include<vsip_vviewattributes_d.h>

#define VGET(v,i) (*(v->block->array + (v->offset + (vsip_stride)(i) * v->stride) * v->block->rstride))
#define VPUT(v,i,s) {*(v->block->array + (v->offset + (vsip_stride)(i) * v->stride) * v->block->rstride) = (s);}

static void swapEven(const vsip_vview_d *a, vsip_index i, vsip_index j){
   vsip_scalar_d t = VGET(a,i);
   VPUT(a,i,VGET(a,j));
   VPUT(a,j,t);
}

static void swapOdd(const vsip_vview_d *a, vsip_index i, vsip_index j){
   vsip_scalar_d t = VGET(a,i);
   VPUT(a,i,VGET(a,j));
   VPUT(a,j+1,t);
}
void vsip_vfreqswap_d(const vsip_vview_d *a){
   vsip_length N=a->length;
   vsip_length n;
   vsip_index i;
   if(N > 1){
      if(N & 1){ /* odd */
         vsip_scalar_d t = VGET(a,N-1);
         n = N/2 - 1;
         for(i=0; i<=n; i++)
            swapOdd(a,n-i,N-i-2);
         VPUT(a,N/2,t);
      } else { /* even */
         n=N/2;
         for(i=0; i<N/2; i++)
            swapEven(a,i,i+n);      
      }
   }
}
