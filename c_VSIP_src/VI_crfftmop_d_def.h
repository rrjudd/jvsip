/* Created by RJudd July 10, 2002 */
/* SPAWARSYSCEN */
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
/* $Id */
#ifndef _VI_CRFFTMOP_D_DEF_H
#define _VI_CRFFTMOP_D_DEF_H 1

#include"VI_fftm_building_blocks_d.h"
#include"VI_mrealview_d.h"
#include"VI_mimagview_d.h"
#include"VI_cmrowview_d.h"
#include"VI_cmcolview_d.h"
#include"VI_mcopy_d_d.h"
#include"VI_cvcopy_d_d.h"

void vsip_crfftmop_d(
           const vsip_fftm_d   *Offt,
           const vsip_cmview_d *Z,
           const vsip_mview_d  *X)
{
   vsip_fftm_d Nfft = *Offt;
   vsip_fftm_d *fft = &Nfft;
   vsip_length m = fft->mN;
   /* makes */
   vsip_mview_d xx_e = *X; vsip_mview_d *X_e = &xx_e;
   vsip_mview_d xx_o = *X; vsip_mview_d *X_o = &xx_o;
   vsip_cvview_d yy = *fft->temp; vsip_cvview_d *y = &yy; /*y*/
   vsip_mview_d YY_r; vsip_mview_d *Y_r;
   vsip_mview_d YY_i; vsip_mview_d *Y_i;
   vsip_cmview_d YY; vsip_cmview_d *Y = &YY;
   vsip_cvview_d ANG = *fft->temp; vsip_cvview_d *ang  = &ANG; /*ang correction*/
   vsip_cvview_d Z0,*z;
   vsip_stride zst,yst = fft->MN + 1;
   vsip_offset ysto = fft->MN;
   vsip_major major = fft->major;
   if(major == VSIP_ROW){
         z = VI_cmrowview_d(Z,0,&Z0);
         *X_e = *X; X_e->row_stride = 2 * X->row_stride; X_e->row_length = ysto;
         *X_o = *X; X_o->row_stride = 2 * X->row_stride; X_o->row_length = ysto;
         X_e->offset += X->row_stride;
         zst = Z->col_stride;
   }else{
         z = VI_cmcolview_d(Z,0,&Z0);
         *X_e = *X; X_e->col_stride = 2 * X->col_stride; X_e->col_length = ysto;
         *X_o = *X; X_o->col_stride = 2 * X->col_stride; X_o->col_length = ysto;
         X_e->offset += X->col_stride;
         zst = Z->row_stride;
   }  
   /* make complex matrix from temp vector row major */
   {
        Y->block = y->block;
        Y->row_length = fft->MN + 1;
        Y->col_length = fft->mN;
        Y->row_stride = 1;
        Y->col_stride = fft->MN +1;
        Y->offset = 2 * (fft->MN + 1);
        Y->markings = vsip_valid_structure_object;
   }
   /* end makes */
   /* change ang view to to proper portion of temp */
   ang->offset = fft->MN + 1;
   ang->length = fft->MN + 1;
   y = VI_cmrowview_d(Y,0,y);
   while(m-- > 0){
      y->stride = -1;
      y->offset += ysto;
      /* copy z to y in reverse order */
      VI_cvcopy_d_d(z,y);
      /* reset y to normal */
      y->stride = 1;
      y->offset -= ysto;
      {   /* this is where the sorting work is done */
         vsip_cvview_d *w = ang; /* these first three steps are just to make*/
         vsip_cvview_d *f = z;   /* it easier to use already developed code */
         vsip_cvview_d *b = y;
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
             temp = /*(0.5) */ (*fpr + *bpr + *wpi * (*bpr - *fpr) - *wpr * (*fpi + *bpi));
             *bpi = /*(0.5) */ (*fpi - *bpi - *wpi * (*fpi + *bpi) + *wpr * (*fpr - *bpr));
             *bpr = temp;
             wpr += wst; wpi += wst;
             fpr += fst; fpi += fst;
             bpr += bst; bpi += bst;
         }  
      }   
      y->offset += yst;
      z->offset += zst;
   }
   { void* tfft = (void*)fft; ((vsip_fftm_d*)tfft)->major = VSIP_ROW;} 
   Y->row_length = ysto;
   VI_ccfftmip_d(fft,Y); /* function resides in ccfftmop code */
   { void* tfft = (void*)fft; ((vsip_fftm_d*)tfft)->major = major;} 
   if( major == VSIP_COL) {
      Y->col_length = Y->row_length;
      Y->row_length = fft->mN;
      Y->row_stride = Y->col_stride;
      Y->col_stride = 1;
   }
   Y_r = VI_mrealview_d(Y,&YY_r);
   Y_i = VI_mimagview_d(Y,&YY_i);
   VI_mcopy_d_d(Y_r,X_o);
   VI_mcopy_d_d(Y_i,X_e);
   return;
}
#endif /* _VI_CRFFTMOP_D_DEF_H */
