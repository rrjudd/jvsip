/* Created By RJudd July 4, 2002 */
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
/* $Id: VI_ccfftmop_create_f_loop.h,v 2.0 2003/02/22 15:18:30 judd Exp $ */
vsip_fftm_f* vsip_ccfftmop_create_f(vsip_length M,
                       vsip_length N,
                       vsip_scalar_f scale,
                       vsip_fft_dir dir,
                       vsip_major major,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_fftm_f *fftm = (vsip_fftm_f*) malloc(sizeof(vsip_fftm_f));
    vsip_fft_f *fft = (vsip_fft_f*)NULL;

    /* find the length of the fft */
    vsip_length L = (major == VSIP_ROW) ? N:M;

    if(fftm == NULL) return (vsip_fftm_f*) NULL;
    fftm->N = N;
    fftm->M = M;
    fftm->major = major;
    fftm->MN = 0;
    fftm->mN = 0;
    fftm->scale = scale;
    fftm->d = dir;
    fftm->pn = (vsip_scalar_vi*)NULL;
    fftm->p0 = (vsip_scalar_vi*)NULL;
    fftm->pF = (vsip_scalar_vi*)NULL;
    fftm->temp = (vsip_cvview_f*)NULL;
    fftm->wt = (vsip_cvview_f*)NULL;
    fftm->index = (vsip_scalar_vi*)NULL; 
    fftm->hint = hint;
    fftm->ntimes = ntimes; 
    fftm->type = VSIP_CCFFTOP; 
    fft = vsip_ccfftop_create_f(L,scale,dir,ntimes,hint);
    if(fft == NULL){
        free(fftm);
        fftm = (vsip_fftm_f*)NULL;
    } else {
        fftm->ext_fftm_obj = (void*)fft;
    }
    return fftm;
}
