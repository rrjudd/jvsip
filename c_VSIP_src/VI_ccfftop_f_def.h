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
/* $Id: VI_ccfftop_f_def.h,v 2.0 2003/02/22 15:18:30 judd Exp $ */
#include"VI_fft_building_blocks_f.h"
#include"VI_ccfftip_f.h"


/*========================================================*/
void vsip_ccfftop_f(const vsip_fft_f *Offt, 
                    const vsip_cvview_f *x,
                    const vsip_cvview_f *y)
{
     vsip_fft_f Nfft = *Offt;
     vsip_fft_f *fft = &Nfft;
     vsip_cvcopy_f_f(x,y);
     fft->type = VSIP_CCFFTIP;
     VI_ccfftip_f(fft,y);
}
