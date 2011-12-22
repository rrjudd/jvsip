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
/* $Id: VI_ccfftip_d_def.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
#include<vsip.h>
#include<vsip_fftattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"VI_fft_building_blocks_d.h"
#include"VI_ccfftip_d.h"

void vsip_ccfftip_d(const vsip_fft_d *Offt, 
                    const vsip_cvview_d *y)
{
     vsip_fft_d Nfft = *Offt;
     vsip_fft_d *fft = &Nfft;
     VI_ccfftip_d(fft,y);
     return;
}

