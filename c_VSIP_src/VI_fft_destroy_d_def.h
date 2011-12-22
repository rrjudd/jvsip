/* Created By RJudd August 27, 1998 */
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
/* $Id: VI_fft_destroy_d_def.h,v 2.0 2003/02/22 15:18:32 judd Exp $ */
/* destroy vsip vectors created in vsip_xxfftxx_create_d */
#include"VI_cvalldestroy_d.h"

int vsip_fft_destroy_d(vsip_fft_d *fft)
{
    if(fft != NULL){
       VI_cvalldestroy_d(fft->wt);
       VI_cvalldestroy_d(fft->temp);
       free(fft->pn);
       free(fft->p0);
       free(fft->pF);
       free(fft->index);
       free(fft);
    }
    return 0;
}
