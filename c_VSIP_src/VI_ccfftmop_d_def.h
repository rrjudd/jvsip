/* Created by RJudd July 13, 2002 */
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
/* $Id: VI_ccfftmop_d_def.h,v 2.0 2003/02/22 15:18:30 judd Exp $ */
#ifndef _VI_CCFFTMOP_D_DEF_H
#define _VI_CCFFTMOP_D_DEF_H

#include"VI_fftm_building_blocks_d.h"
#include"VI_cmcopy_d_d.h"

/*========================================================*/
void vsip_ccfftmop_d(
         const vsip_fftm_d *Offt, 
         const vsip_cmview_d *x,
         const vsip_cmview_d *y)
{
   vsip_fftm_d Nfft = *Offt;
   vsip_fftm_d *fftm = &Nfft;
   VI_cmcopy_d_d(x,y);
   fftm->type = VSIP_CCFFTIP;
   VI_ccfftmip_d(fftm,y);
}

#endif /* _VI_CCFFTMOP_D_DEF_H */
