/* Created By RJudd July 9, 2002 */
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
/* $Id: VI_rcfftmop_create_f_loop.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
/* real to complex fft */

#ifndef _VI_RCFFTMOP_CREATE_F_LOOP_H
#define _VI_RCFFTMOP_CREATE_F_LOOP_H

vsip_fftm_f* vsip_rcfftmop_create_f(
          vsip_length M,
          vsip_length N,      
          vsip_scalar_f scale,
          vsip_major major,  
          unsigned int ntimes,
          vsip_alg_hint hint)
{
    vsip_fftm_f *fftm = (vsip_fftm_f*)malloc(sizeof(vsip_fftm_f));
    vsip_fft_f *fft = (vsip_fft_f*)NULL;

    /* find the length of the fft */
    vsip_length L = (major == VSIP_ROW) ? N:M;

    if(fftm == NULL) return (vsip_fftm_f*)NULL;
    fftm->N = N;
    fftm->M = M;
    fftm->MN = (major == VSIP_ROW) ? N/2: M/2;
    fftm->mN = (major == VSIP_ROW) ?  M : N;
    fftm->major = major;
    fftm->scale = scale;
    fftm->d = VSIP_FFT_FWD;
    fftm->pn = (vsip_scalar_vi*)NULL;
    fftm->p0 = (vsip_scalar_vi*)NULL;
    fftm->pF = (vsip_scalar_vi*)NULL;
    fftm->temp = (vsip_cvview_f*)NULL;
    fftm->wt = (vsip_cvview_f*)NULL;
    fftm->index = (vsip_scalar_vi*)NULL; 
    fftm->hint = hint;
    fftm->ntimes = ntimes; 
    fftm->type = VSIP_RCFFTOP; 
    fft = vsip_rcfftop_create_f(L,scale,ntimes,hint);

    if(fft == NULL){
        free(fftm);
        fftm = (vsip_fftm_f*)NULL;
    } else {
        fftm->ext_fftm_obj = (void*)fft;
    }
    return fftm;
}

#endif /* _VI_RCFFTMOP_CREATE_F_LOOP_H */
