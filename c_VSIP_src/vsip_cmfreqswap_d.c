/* Created RJudd Nov 28, 2011 */
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
#include"vsip.h"
#include"vsip_blockattributes_d.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_mviewattributes_d.h"
#include"vsip_cmviewattributes_d.h"

#define VGET(v,i) (*(v->block->array + (v->offset + (vsip_stride)(i) * v->stride) * v->block->rstride))
#define VPUT(v,i,s) {*(v->block->array + (v->offset + (vsip_stride)(i) * v->stride) * v->block->rstride) = (s);}
#define ROW(a,r,i) {r.block= a->block;r.offset = a->offset + i * a->col_stride; r.stride =a->row_stride; r.length=a->row_length;}
#define COL(a,c,i) {c.block= a->block;c.offset = a->offset + i * a->row_stride; c.stride =a->col_stride; c.length=a->col_length;}

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

static void freqswap(const vsip_vview_d *a){
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

static void mfreqswap(const vsip_mview_d *a){
   vsip_vview_d a_r;
   vsip_vview_d a_c;
   { /* freqswap eo */
      vsip_index i;
      for(i=0; i<a->col_length; i++){
         ROW(a,a_r,i);
         freqswap(&a_r);
      }
      for(i=0; i<a->row_length; i++){
         COL(a,a_c,i);
         freqswap(&a_c);
      }
   } 
}


void vsip_cmfreqswap_d(const vsip_cmview_d *a){
     vsip_mview_d v;
     v.offset = a->offset; 
     v.row_stride=a->row_stride; v.row_length=a->row_length;
     v.col_stride=a->col_stride; v.col_length=a->col_length;
     v.markings=VSIP_VALID_STRUCTURE_OBJECT;
     v.block=a->block->R;
     mfreqswap(&v);
     v.block=a->block->I;
     mfreqswap(&v);
}
