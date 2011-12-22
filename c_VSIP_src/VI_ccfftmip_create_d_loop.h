/* Created By RJudd July 4, 2002 */
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
/* $Id: VI_ccfftmip_create_d_loop.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */

#define VI_ft_d_2PI 6.2831853071795864769252866
#define VI_ft_d_PI  3.1415926535897932384626433

vsip_fftm_d* vsip_ccfftmip_create_d(vsip_length M,
                       vsip_length N,
                       vsip_scalar_d scale,
                       vsip_fft_dir dir,
                       vsip_major major,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{   
    vsip_fftm_d *fftm = (vsip_fftm_d*) malloc(sizeof(vsip_fftm_d));
    vsip_fft_d *fft = (vsip_fft_d*)NULL;

    /* find the length of the fft */
    vsip_length L = (major == VSIP_ROW) ? N:M;

    if(fftm == NULL) return (vsip_fftm_d*) NULL;
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
    fftm->temp = (vsip_cvview_d*)NULL;
    fftm->wt = (vsip_cvview_d*)NULL;
    fftm->index = (vsip_scalar_vi*)NULL;
    fftm->hint = hint;
    fftm->ntimes = ntimes; 
    fftm->type = VSIP_CCFFTIP; 
    fft = vsip_ccfftip_create_d(L,scale,dir,ntimes,hint);
    if(fft == NULL){
        free(fftm);
        fftm = (vsip_fftm_d*)NULL;
    } else {
        fftm->ext_fftm_obj = (void*)fft;
    }
    return fftm;
}
