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
/* $Id: VI_ccfftop_d_def.h,v 2.1 2009/12/26 19:19:48 judd Exp $ */
#include<vsip_fftattributes_d.h>
#include"VI_fft_building_blocks_d.h"
#include"VI_ccfftip_d.h"

/*========================================================*/
void vsip_ccfftop_d(const vsip_fft_d *Offt, 
                    const vsip_cvview_d *x,
                    const vsip_cvview_d *y)
{
     vsip_fft_d Nfft = *Offt;
     vsip_fft_d *fft = &Nfft;
     vsip_cvcopy_d_d(x,y);
     fft->type = VSIP_CCFFTIP;
     VI_ccfftip_d(fft,y);
}
