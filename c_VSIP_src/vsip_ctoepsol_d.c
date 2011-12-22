/* Created RJudd September 27, 1999 */
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
/* $Id: vsip_ctoepsol_d.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */
/* vsip_ctoepsol_d.c */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

static void VI_cscale_d(
         vsip_cvview_d *a,
         vsip_cvview_d *b)
{
   vsip_length n = a->length;
   vsip_stride ast = a->stride * a->block->cstride,
               bst = b->stride * b->block->cstride;
   vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                 *bp_r = (b->block->R->array) + b->offset * b->block->cstride;
   vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                 *bp_i = (b->block->I->array) + b->offset * b->block->cstride;
   vsip_scalar_d s = *ap_r; /* for this case ap_i == 0 */
   *ap_r  = 1; ap_r += ast;
   *ap_i  = 0; ap_i += ast;
   *bp_r /= s; bp_r += bst; 
   *bp_i /= s; bp_i += bst; 
   n--;
   while(n-- >0){
       *ap_r /= s; *bp_r /= s;
       *ap_i /= s; *bp_i /= s;
       ap_r += ast; bp_r += bst;
       ap_i += ast; bp_i += bst;
   }
   return;
}

static vsip_cscalar_d VI_cvdotr_d(/* vector dot reciprical vector */
     vsip_length k,
     const vsip_cvview_d *a,
     const vsip_cvview_d *b)
{
   /*define variables*/
   vsip_length n = k;
   vsip_stride ast =   a->stride * a->block->cstride,
               bst = - (b->stride * b->block->cstride);
   vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                 *bp_r = (b->block->R->array) + 
                           ((k-1) * b->stride + b->offset) * b->block->cstride;
   vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                 *bp_i = (b->block->I->array) + 
                           ((k-1) * b->stride + b->offset) * b->block->cstride;
   vsip_cscalar_d t;
   t.r  = (*ap_r * *bp_r + *ap_i * *bp_i);
   t.i  = (*ap_r * *bp_i - *ap_i * *bp_r);
  /* do sum */
   while(n-- > 1){
      ap_r += ast; bp_r += bst;
      ap_i += ast; bp_i += bst;
      t.r  += (*ap_r * *bp_r + *ap_i * *bp_i);
      t.i  += (*ap_r * *bp_i - *ap_i * *bp_r);
   }
  /* return dot sum */
   return t;
}

/* scalar vector multiply vector add reciprocal scalar attend */
static void VI_csvmul_vaddr_sattend_d(
       vsip_cscalar_d mu,
       vsip_length k,
       const vsip_cvview_d *a,
       const vsip_cvview_d *b,
       const vsip_cvview_d *c) /* c and b may be the same if a != b */
{
   vsip_length n = k;
   vsip_stride cst = c->stride * c->block->cstride,
               bst = b->stride * b->block->cstride,
               ast = -a->stride * a->block->cstride;
   vsip_scalar_d *ap_r = (a->block->R->array) + 
                          ((k-1) * a->stride + a->offset) * a->block->cstride,
                 *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                 *cp_r = (c->block->R->array) + c->offset * c->block->cstride;
   vsip_scalar_d *ap_i = (a->block->I->array) + 
                          ((k-1) * a->stride + a->offset) * a->block->cstride,
                 *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                 *cp_i = (c->block->I->array) + c->offset * c->block->cstride;
  /* do sum */
   while(n-- > 0){
      *cp_r = mu.r * *ap_r + mu.i * *ap_i + *bp_r;
      *cp_i = mu.i * *ap_r - mu.r * *ap_i + *bp_i;
      ap_r += ast; bp_r += bst; cp_r += cst;
      ap_i += ast; bp_i += bst; cp_i += cst;
   }
   *cp_r = mu.r; /* scalar attend */
   *cp_i = mu.i;
   return;
}

static void VI_csvmul_vaddr_sattendIP_d( 
       vsip_cscalar_d alpha,
       vsip_length k,
       const vsip_cvview_d *a) /* a = a + mu conj(a_invert) */
{
   /*define variables*/
   /* register */ vsip_length n = k;
   /* register */ vsip_stride bst =   a->stride * a->block->cstride,
                              cst = - a->stride * a->block->cstride;
   vsip_scalar_d *cp_r = (a->block->R->array) + 
                           ((k-1) * a->stride + a->offset) * a->block->cstride,
                 *bp_r = (a->block->R->array) + a->offset * a->block->cstride;
   vsip_scalar_d *cp_i = (a->block->I->array) + 
                           ((k-1) * a->stride + a->offset) * a->block->cstride,
                 *bp_i = (a->block->I->array) + a->offset * a->block->cstride;
   vsip_cscalar_d t1,t2;
  /* do sum */
   n /=2;
   while(n-- > 0){
      t2.r = *cp_r; t1.r = *bp_r;
      t2.i = *cp_i; t1.i = *bp_i;
      *bp_r = t1.r + alpha.r * t2.r + alpha.i * t2.i;
      *bp_i = t1.i + alpha.i * t2.r - alpha.r * t2.i;
      *cp_r = t2.r + alpha.r * t1.r + alpha.i * t1.i;     
      *cp_i = t2.i + alpha.i * t1.r - alpha.r * t1.i;
      bp_r += bst; cp_r += cst;
      bp_i += bst; cp_i += cst;
   }
   if(k%2){ t1.r = *bp_r; t1.i = *bp_i;
            *bp_r = t1.r + alpha.r * t1.r + alpha.i * t1.i;
            *bp_i = t1.i + alpha.i * t1.r - alpha.r * t1.i;
   }
   /* scalar attend */
   *(a->block->R->array + (k * a->stride + a->offset) * a->block->cstride) = alpha.r;
   *(a->block->I->array + (k * a->stride + a->offset) * a->block->cstride) = alpha.i;
   return;
}
int vsip_ctoepsol_d(
     const vsip_cvview_d *T,
     const vsip_cvview_d *B,
     const vsip_cvview_d *Y,
     const vsip_cvview_d *X)
{
     int retval = 0;
     vsip_length k,
                 n = T->length;
     vsip_scalar_d beta = 1.0;
     vsip_cscalar_d alpha, mu, temp; 
     vsip_cvview_d bb = *B, yy = *Y, xx = *X;
     vsip_cvview_d *b = &bb, *y = &yy, *x = &xx;
     vsip_cvview_d rr = *T;
     vsip_cvview_d *r = &rr;
     vsip_scalar_d *bp_r = b->block->R->array + b->offset * b->block->cstride,
                   *rp_r = r->block->R->array + r->offset * r->block->cstride;
     vsip_scalar_d *bp_i = b->block->I->array + b->offset * b->block->cstride,
                   *rp_i = r->block->I->array + r->offset * r->block->cstride;
     vsip_stride bst = b->stride * b->block->cstride,
                 rst = r->stride * r->block->cstride;
     VI_cscale_d(r,b);
     r->length--;
     r->offset += r->stride;
     rp_r += rst;
     rp_i += rst;
     alpha.r = - *rp_r;
     alpha.i = + *rp_i;
     *(y->block->R->array + y->offset * y->block->cstride) = alpha.r; /* y(0)=r(0) */
     *(y->block->I->array + y->offset * y->block->cstride) = alpha.i; 
     *(x->block->R->array + x->offset * x->block->cstride) = *bp_r; /* x(0)=b(0)*/
     *(x->block->I->array + x->offset * x->block->cstride) = *bp_i; 
     for(k=1; k< n; k++){
         beta *= (1.0 - (alpha.r * alpha.r + alpha.i * alpha.i));
         if(beta == 0.0){ 
            retval = 1;
            return retval;
         } 
         bp_r += bst; bp_i += bst;

         temp = VI_cvdotr_d(k,r,x);
         mu.r = (*bp_r - temp.r)/beta;
         mu.i = (*bp_i - temp.i)/beta;

         VI_csvmul_vaddr_sattend_d(mu,k,y,x,x);

         if(k < (n - 1 )){
              rp_r += rst; rp_i += rst;
              temp = VI_cvdotr_d(k,r,y);
              alpha.r = -(temp.r + *rp_r)/beta; 
              alpha.i = -(temp.i - *rp_i)/beta; 

              VI_csvmul_vaddr_sattendIP_d(alpha,k,y);
         }
      }
      return retval;
}
        
