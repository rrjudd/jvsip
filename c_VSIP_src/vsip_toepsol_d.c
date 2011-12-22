/* Created RJudd September 12, 1999 */
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
/* $Id: vsip_toepsol_d.c,v 2.0 2003/02/22 15:19:07 judd Exp $ */
#include<vsip_vviewattributes_d.h>

static void VI_scale_d(
         vsip_vview_d *a,
         vsip_vview_d *b)
{
   vsip_length n = a->length;
   vsip_stride ast = a->stride * a->block->rstride,
               bst = b->stride * b->block->rstride;
   vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                 *bp = (b->block->array) + b->offset * b->block->rstride;
   vsip_scalar_d s = *ap;
   *ap  = 1; ap += ast;
   *bp /= s; bp += bst; 
   n--;
   while(n-- >0){
       *ap /= s; *bp /= s;
       ap += ast; bp += bst;
   }
   return;
}

static vsip_scalar_d VI_vdotr_d(/* vector dot reciprical vector */
     vsip_length k,
     const vsip_vview_d *a,
     const vsip_vview_d *b)
{
   /*define variables*/
   vsip_length n = k;
   vsip_stride ast = a->stride * a->block->rstride,
               bst = - (b->stride * b->block->rstride);
   vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                 *bp = (b->block->array) + 
                        ((k-1) * b->stride + b->offset) * b->block->rstride;
   vsip_scalar_d t = 0;
  /* do sum */
   while(n-- > 0){
      t += (*ap * *bp);
      ap += ast; bp += bst;
   }
  /* return dot sum */
   return t;
}

/* scalar vector multiply vector add reciprocal scalar attend */
static void VI_svmul_vaddr_sattend_d(
       vsip_scalar_d mu,
       vsip_length k,
       const vsip_vview_d *a,
       const vsip_vview_d *b,
       const vsip_vview_d *c) /* c and b may be the same if a != b */
{
   vsip_length n = k;
   vsip_stride cst = c->stride * c->block->rstride,
               bst = b->stride * b->block->rstride,
               ast = -a->stride * a->block->rstride;
   vsip_scalar_d *ap = (a->block->array) + 
                          ((k-1) * a->stride + a->offset) * a->block->rstride,
                 *bp = (b->block->array) + b->offset * b->block->rstride,
                 *cp = (c->block->array) + c->offset * c->block->rstride;
  /* do sum */
   while(n-- > 0){
      *cp = mu * *ap + *bp;
      ap += ast; bp += bst; cp += cst;
   }
   *cp = mu; /* scalar attend */
   return;
}

static void VI_svmul_vaddr_sattendIP_d( 
       vsip_scalar_d mu,
       vsip_length k,
       const vsip_vview_d *a) /* a = a + mu a_invert */
{
   /*define variables*/
   /* register */ vsip_length n = k;
   /* register */ vsip_stride bst = a->stride * a->block->rstride,
                              cst = -a->stride * a->block->rstride;
   vsip_scalar_d *cp = (a->block->array) + 
                          ((k-1) * a->stride + a->offset) * a->block->rstride,
                 *bp = (a->block->array) + a->offset * a->block->rstride;
   vsip_scalar_d t1,t2;
  /* do sum */
   n /=2;
   while(n-- > 0){
      t2 = *cp; t1 = *bp;
      *bp = t1 + mu * t2;
      *cp = t2 + mu * t1;     
      bp += bst; cp += cst;
   }
   if(k%2) *bp = *bp + mu * *bp;
   /* scalar attend */
   *(a->block->array + (k * a->stride + a->offset) * a->block->rstride) = mu;
   return;
}
int vsip_toepsol_d(
     const vsip_vview_d *T,
     const vsip_vview_d *B,
     const vsip_vview_d *Y,
     const vsip_vview_d *X)
{
     int retval = 0;
     vsip_length k,
                 n = T->length;
     vsip_scalar_d beta = 1, alpha, mu; 
     vsip_vview_d bb = *B, yy = *Y, xx = *X;
     vsip_vview_d *b = &bb, *y = &yy, *x = &xx;
     vsip_vview_d rr = *T;
     vsip_vview_d *r = &rr;
     vsip_scalar_d *b_p = b->block->array + b->offset * b->block->rstride,
                   *r_p = r->block->array + r->offset * r->block->rstride;
     vsip_stride bst = b->stride * b->block->rstride,
                 rst = r->stride * r->block->rstride;
     VI_scale_d(r,b);
     r->length--;
     r->offset += r->stride;
     r_p +=rst;
     alpha = - *(r->block->array + r->offset * r->block->rstride);
     *(y->block->array + y->offset * y->block->rstride) = alpha; /* y(0)=r(0) */
     *(x->block->array + x->offset * x->block->rstride) = *b_p; /* x(0)=b(0)*/
     for(k=1; k< n; k++){
         beta *= (1 - alpha * alpha);
         if(beta == 0.0){ 
            retval = 1;
            return retval;
         }
         b_p += bst;
         mu = (*b_p - VI_vdotr_d(k,r,x))/beta;
         VI_svmul_vaddr_sattend_d(mu,k,y,x,x);
         if(k < (n - 1)){
              r_p += rst;
              alpha = -(VI_vdotr_d(k,r,y) + *r_p)/beta; 
              VI_svmul_vaddr_sattendIP_d(alpha,k,y);
         }
      }
      return retval;
}
        
