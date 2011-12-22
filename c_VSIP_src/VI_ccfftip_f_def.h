/* Created by RJudd January 7, 1999 */
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
/* $Id: VI_ccfftip_f_def.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
#include<vsip.h>
#include<vsip_fftattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include"VI_fft_building_blocks_f.h"
#include"VI_ccfftip_f.h"

void vsip_ccfftip_f(const vsip_fft_f *Offt, 
                    const vsip_cvview_f *y)
{
     vsip_fft_f Nfft = *Offt;
     vsip_fft_f *fft = &Nfft;
     VI_ccfftip_f(fft,y);
     return;
}

