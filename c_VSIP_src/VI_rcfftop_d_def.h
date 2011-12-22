/* Created by RJudd September 9, 1998 */
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
/* $Id: VI_rcfftop_d_def.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#ifndef _VI_RCFFTOP_D_DEF_H
#define _VI_RCFFTOP_D_DEF_H

#include"VI_fft_building_blocks_d.h"
#include"VI_ccfftip_d.h"
#include"VI_vrealview_d.h"
#include"VI_vimagview_d.h"

void vsip_rcfftop_d(
           const vsip_fft_d    *Offt, 
           const vsip_vview_d  *x,
           const vsip_cvview_d *z)
{
     vsip_fft_d Nfft = *Offt;
     vsip_fft_d *fft = &Nfft;
     /* makes */
     vsip_cvview_d ca1 = *z;
     vsip_cvview_d *y  = &ca1; /*y*/
     vsip_vview_d ra1;
     vsip_vview_d *y_r = VI_vrealview_d(y,&ra1);
     vsip_vview_d ra2;
     vsip_vview_d *y_i = VI_vimagview_d(y,&ra2);
     vsip_vview_d ra3 = *x;
     vsip_vview_d *x_e = &ra3; /*x*/
     vsip_vview_d ca2 = *x;
     vsip_vview_d *x_o = &ca2;
     vsip_cvview_d ca3 = *(fft->temp);
     vsip_cvview_d *t  = &ca3; /*t*/
     vsip_cvview_d ca4 = *(fft->temp);
     vsip_cvview_d *ang  = &ca4; /*ang create*/
     /* end makes */
     /* change ang view to to proper portion of temp */
     ang->offset = fft->N + 1;
     ang->length = fft->N + 1;
     
     /* copy even x to imaginary y, odd x to real y: note y is z clone */
     x_e->length = fft->N;
     x_o->length = fft->N;
     x_e->stride = 2 * x->stride;
     x_o->stride = 2 * x->stride;
     x_e->offset = x->offset + x->stride;
     y_i->length = fft->N;
     y_r->length = fft->N;
     vsip_vcopy_d_d(x_e,y_i);
     vsip_vcopy_d_d(x_o,y_r);
     /* do fft on y */
     y->length = fft->N;
     VI_ccfftip_d(fft,y); /* function resides in ccfftop code */
     y->length = fft->N + 1;
     vsip_cvput_d(y,fft->N,vsip_cvget_d(y,0));
     /* copy z to t in reverse order */
     t->stride = -1;
     t->offset = fft->N ;
     t->length = fft->N + 1;
     y->length = fft->N + 1;
     vsip_cvcopy_d_d(y,t);
     /* reset t to normal */
     t->stride = 1;
     t->offset = 0;
     {   /* this is where the sorting work is done */
         vsip_cvview_d *w = ang; /* these first three steps are just to make*/
         vsip_cvview_d *f = y;   /* it easier to use already developed code */
         vsip_cvview_d *b = t;
         /* register */ vsip_length n = b->length;
         vsip_stride cwst = w->block->cstride;
         vsip_stride cfst = f->block->cstride;
         vsip_stride cbst = b->block->cstride;
         vsip_scalar_d *wpr = (vsip_scalar_d *)((w->block->R->array) + cwst * w->offset),
                       *fpr = (vsip_scalar_d *)((f->block->R->array) + cfst * f->offset),
                       *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset);
         vsip_scalar_d *wpi = (vsip_scalar_d *)((w->block->I->array) + cwst * w->offset),
                       *fpi = (vsip_scalar_d *)((f->block->I->array) + cfst * f->offset),
                       *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset);
         /* register */ vsip_stride wst = cwst * w->stride,
                                    fst = cfst * f->stride,
                                    bst = cbst * b->stride;
         vsip_scalar_d temp;
         while(n-- > 0){
             temp = (vsip_scalar_d)0.5 * (*bpr + *fpr + *wpr * (*bpi + *fpi) + *wpi * (*fpr - *bpr));
             *fpi = (vsip_scalar_d)0.5 * (*fpi - *bpi + *wpr * (*bpr - *fpr) + *wpi * (*bpi + *fpi));
             *fpr = temp;
             wpr += wst; wpi += wst;
             fpr += fst; fpi += fst;
             bpr += bst; bpi += bst;
         }  
      }   
     return;
}

#endif /* _VI_RCFFTOP_D_DEF_H */
