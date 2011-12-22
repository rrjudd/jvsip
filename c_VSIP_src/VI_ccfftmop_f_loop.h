/* Created by RJudd July 4, 2002 */
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
/* $Id: VI_ccfftmop_f_loop.h,v 2.0 2003/02/22 15:18:30 judd Exp $ */
#ifndef _VI_CCFFTMOP_F_LOOP_H
#define _VI_CCFFTMOP_F_LOOP_H

/* Use a loop of vsip_ccfftop_f.h to calculate fftm  */
/* input matrix x, output matrix y, fftm object fftm */
#include"VI_cmrowview_f.h"
#include"VI_cmcolview_f.h"

void vsip_ccfftmop_f(const vsip_fftm_f *Offt,
                    const vsip_cmview_f *x,
                    const vsip_cmview_f *y)
{
   vsip_fftm_f Nfft = *Offt;
   vsip_fftm_f *fftm = &Nfft;
   vsip_fft_f *fft = (vsip_fft_f*)fftm->ext_fftm_obj;
   vsip_index k = 0;
   vsip_cvview_f vv,zz;
   if(fftm->major == VSIP_ROW){
      while(k < x->col_length){
         vsip_ccfftop_f(fft, VI_cmrowview_f(x,k,&vv), VI_cmrowview_f(y,k,&zz));
         k++;
      }
   } else { /* must be column */
      while(k < x->row_length){
         vsip_ccfftop_f(fft, VI_cmcolview_f(x,k,&vv), VI_cmcolview_f(y,k,&zz));
         k++;
      }
   }
}

#endif /* _VI_CCFFTMOP_F_LOOP_H */
