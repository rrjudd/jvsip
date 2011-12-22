/* Created by RJudd July 6, 2002 */
/* SPAWARSYSCEN  */
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
/* $Id: VI_rcfftmop_f_def.h,v 2.1 2006/06/08 22:19:26 judd Exp $ */
#ifndef _VI_RCFFTMOP_F_DEF_H
#define _VI_RCFFTMOP_F_DEF_H 1

#include"VI_fftm_building_blocks_f.h"
#include"VI_mrealview_f.h"
#include"VI_mimagview_f.h"
#include"VI_cmrowview_f.h"
#include"VI_cmcolview_f.h"
#include"VI_mcopy_f_f.h"

void vsip_rcfftmop_f(
          const vsip_fftm_f   *Offt,
          const vsip_mview_f  *X,
          const vsip_cmview_f *Z)
{ 
     vsip_fftm_f Nfft = *Offt;
     vsip_fftm_f *fft = &Nfft;
     vsip_length n;
     /* makes */
     vsip_cmview_f ca1 = *Z; vsip_cmview_f *Y = &ca1;
     vsip_mview_f ra1;
     vsip_mview_f *Y_r = VI_mrealview_f(Y,&ra1);
     vsip_mview_f ra2;
     vsip_mview_f *Y_i = VI_mimagview_f(Y,&ra2);
     vsip_mview_f ra3 = *X; vsip_mview_f *X_e = &ra3;
     vsip_mview_f ca2 = *X; vsip_mview_f *X_o = &ca2;
     vsip_cvview_f ca3 = *fft->temp; vsip_cvview_f *t = &ca3;
     vsip_cvview_f ca4 = *fft->temp; vsip_cvview_f *ang = &ca4;
     vsip_cvview_f Z0,*z;
     if(fft->major == VSIP_ROW){
           z = VI_cmrowview_f(Z,0,&Z0);
     }else{
           z = VI_cmcolview_f(Z,0,&Z0);
     }
     /* end makes */
     /* change ang view to to proper portion of temp */
     ang->offset = fft->MN + 1;
     ang->length = fft->MN + 1;
     /* copy even x to imaginary y, odd x to real y: note y is z clone */
     if(fft->major == VSIP_ROW){
         X_e->row_length = fft->MN;
         X_o->row_length = fft->MN;
         X_e->row_stride = 2 * X->row_stride;
         X_o->row_stride = 2 * X->row_stride;
         X_e->offset = X->offset + X->row_stride;
         Y_i->row_length = fft->MN;
         Y_r->row_length = fft->MN;
         VI_mcopy_f_f(X_e,Y_i);
         VI_mcopy_f_f(X_o,Y_r);
         Y->row_length = fft->MN; 
     }else{
         X_e->col_length = fft->MN;
         X_o->col_length = fft->MN;
         X_e->col_stride = 2 * X->col_stride;
         X_o->col_stride = 2 * X->col_stride;    
         X_e->offset = X->offset + X->col_stride;
         Y_i->col_length = fft->MN;
         Y_r->col_length = fft->MN;
         VI_mcopy_f_f(X_e,Y_i);
         VI_mcopy_f_f(X_o,Y_r);
         Y->col_length = fft->MN;
     }
     /* do fft on y */
     VI_ccfftmip_f(fft,Y); /* function resides in ccfftop code */
     
     n = fft->mN;
     while(n-- >0){
        vsip_cvput_f(z,fft->MN,vsip_cvget_f(z,0));
        /* copy z to t in reverse order */
        t->stride = -1;
        t->offset = fft->MN ;
        t->length = fft->MN + 1;
        vsip_cvcopy_f_f(z,t);
        /* reset t to normal */
        t->stride = 1;
        t->offset = 0;
        {   /* this is where the sorting work is done */
            vsip_cvview_f *w = ang; /* these first three steps are just to make*/
            vsip_cvview_f *f = z;   /* it easier to use already developed code */
            vsip_cvview_f *b = t;
            vsip_length n1 = b->length;
            vsip_stride cwst = w->block->cstride;
            vsip_stride cfst = f->block->cstride;
            vsip_stride cbst = b->block->cstride;
            vsip_scalar_f *wpr = (vsip_scalar_f *)((w->block->R->array) + cwst * w->offset),
                          *fpr = (vsip_scalar_f *)((f->block->R->array) + cfst * f->offset),
                          *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset);
            vsip_scalar_f *wpi = (vsip_scalar_f *)((w->block->I->array) + cwst * w->offset),
                          *fpi = (vsip_scalar_f *)((f->block->I->array) + cfst * f->offset),
                          *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset);
            /* register */ vsip_stride wst = cwst * w->stride,
                                       fst = cfst * f->stride,
                                       bst = cbst * b->stride;
            vsip_scalar_f temp;
            while(n1-- > 0){
                temp = (vsip_scalar_f)0.5 * (*bpr + *fpr + *wpr * (*bpi + *fpi) + *wpi * (*fpr - *bpr));
                *fpi = (vsip_scalar_f)0.5 * (*fpi - *bpi + *wpr * (*bpr - *fpr) + *wpi * (*bpi + *fpi));
                *fpr = temp;
                wpr += wst; wpi += wst;
                fpr += fst; fpi += fst;
                bpr += bst; bpi += bst;
            }  
         }   
         z->offset += fft->yst;
     }
     return;
}
#endif /* _VI_RCFFTMOP_F_DEF_H */
