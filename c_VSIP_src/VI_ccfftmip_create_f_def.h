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
/* $Id: VI_ccfftmip_create_f_def.h,v 2.1 2003/04/22 02:19:56 judd Exp $ */
#include"VI_nuV.h"
#include"VI_jofk.h"
#include"VI_vrealview_f.h"
#include"VI_vimagview_f.h"
#include"vsip_scalars.h"

#define VI_ft_f_2PI 6.2831853071795864769252866
#define VI_ft_f_PI  3.1415926535897932384626433

vsip_fftm_f* vsip_ccfftmip_create_f(vsip_length M,
                       vsip_length N,
                       vsip_scalar_f scale,
                       vsip_fft_dir dir,
                       vsip_major major,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_f wt1,wt2;
    vsip_fftm_f *fft = (vsip_fftm_f*) malloc(sizeof(vsip_fftm_f));
    if(fft == NULL) return (vsip_fftm_f*) NULL;
    fft->N = N;
    fft->M = M;
    fft->major = major;
    fft->MN = (major == VSIP_COL) ? M : N;
    fft->mN = (major == VSIP_COL) ? N : M;
    fft->scale = scale;
    fft->d = dir;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_f(fft->MN,VSIP_MEM_NONE); /* create a space to copy too when unsorting */
    fft->wt = vsip_cvcreate_f(fft->MN,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(fft->MN * sizeof(vsip_scalar_vi));
    if((fft->pn == NULL) || (fft->p0 == NULL) || 
       (fft->pF == NULL) || (fft->wt == NULL) ||
       (fft->temp == NULL) || (fft->index == NULL)){
         vsip_fftm_destroy_f(fft);
         return (vsip_fftm_f*) NULL;
    }
    fft->length = VI_nuV(fft->MN,
         fft->pn,
         fft->p0,
         fft->pF);
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_CCFFTIP; 

    /* create twiddle table */
    { 
        vsip_vview_f *wtR = VI_vrealview_f(fft->wt,&wt1); 
        vsip_vview_f *wtI = VI_vimagview_f(fft->wt,&wt2); 
        if(dir == -1){ 
          vsip_vramp_f((vsip_scalar_f)0.,- (vsip_scalar_f)VI_ft_f_2PI/fft->MN,wtR);  
        }else{ 
          vsip_vramp_f((vsip_scalar_f)0., (vsip_scalar_f)VI_ft_f_2PI/fft->MN,wtR); 
        }   
        vsip_vsin_f(wtR,wtI);
        vsip_vcos_f(wtR,wtR);
    }

    if((fft->p0[0] == 1) && (fft->pF[0] == fft->MN)){
        fft->dft = 1; /* implies no supported factor exists */
    } else {
        fft->dft = 0; /* implies at least one of the supported factors exist */
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< fft->MN; i++) fft->index[i] = VI_jofk(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
