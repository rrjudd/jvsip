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
/* $Id: VI_rcfftmop_d_loop.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#ifndef _VI_RCFFTMOP_D_LOOP_H
#define _VI_RCFFTMOP_D_LOOP_H 1

/* Use a loop of vsip_rcfftop_d.h to calculate fftm  */
/* input matrix x, output matrix y, fftm object fftm */

#include"VI_mrowview_d.h"
#include"VI_mcolview_d.h"
#include"VI_cmrowview_d.h"
#include"VI_cmcolview_d.h"

void vsip_rcfftmop_d(
          const vsip_fftm_d   *Offt,
          const vsip_mview_d  *X,
          const vsip_cmview_d *Z)
{
   vsip_fftm_d Nfft  = *Offt; 
   vsip_fftm_d *fftm = &Nfft; 
   vsip_fft_d *fft = (vsip_fft_d*)fftm->ext_fftm_obj;
   vsip_index k = 0;   
   vsip_vview_d vv;
   vsip_cvview_d zz;
   if(fftm->major == VSIP_ROW){
      while(k < X->col_length){
         vsip_rcfftop_d(fft, VI_mrowview_d(X,k,&vv), VI_cmrowview_d(Z,k,&zz));
         k++;
      }
   } else { /* must be column */
      while(k < X->row_length){  
         vsip_rcfftop_d(fft, VI_mcolview_d(X,k,&vv), VI_cmcolview_d(Z,k,&zz));
         k++;
      }    
   }    
}
#endif /* _VI_RCFFTMOP_D_LOOP_H */
