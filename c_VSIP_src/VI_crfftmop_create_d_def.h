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
/* $Id: VI_crfftmop_create_d_def.h,v 2.1 2003/04/22 02:19:56 judd Exp $ */
/* real to complex fft */

#include"VI_nuV.h"
#include"VI_jofk.h"
#include"VI_vrealview_d.h"
#include"VI_vimagview_d.h"

#define VI_ft_d_2PI 6.2831853071795864769252866
#define VI_ft_d_PI  3.1415926535897932384626433


vsip_fftm_d* vsip_crfftmop_create_d(vsip_length M,
                       vsip_length N,
                       vsip_scalar_d scale,
                       vsip_major major,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_d wt1,wt2;
    vsip_fftm_d *fft = (vsip_fftm_d*) malloc(sizeof(vsip_fftm_d));
    if(fft == NULL) return (vsip_fftm_d*) NULL;
    fft->N = N;
    fft->M = M;
    fft->MN = (major == VSIP_ROW) ? N/2: M/2;
    fft->mN = (major == VSIP_ROW) ?  M : N;
    fft->major = major;
    fft->scale = scale;
    fft->d = VSIP_FFT_INV;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_d((2 + fft->mN) * (fft->MN + 1),VSIP_MEM_NONE); /* create some work space */
    fft->wt = vsip_cvcreate_d(fft->MN,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(fft->MN * sizeof(vsip_scalar_vi));
    /* check for creation problem */
    if( (fft->pn == NULL) || (fft->p0 == NULL) || 
        (fft->pF == NULL) || (fft->wt == NULL) || 
        (fft->temp == NULL) || (fft->index == NULL)){
          vsip_fftm_destroy_d(fft);
          return (vsip_fftm_d*) NULL;
    }
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_CRFFTOP; 
    /* calculate factors, fft->length is number of factors found */
    fft->length = VI_nuV(fft->MN,
         fft->pn,
         fft->p0,
         fft->pF);

    /* create twiddle table */
    { 
        vsip_vview_d *wtR = VI_vrealview_d(fft->wt,&wt1);
        vsip_vview_d *wtI = VI_vimagview_d(fft->wt,&wt2); 
        vsip_vramp_d((vsip_scalar_d)0., (vsip_scalar_d)VI_ft_d_2PI/fft->MN,wtR);  
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }
    /* create euler for crfftop in fft->temp */
    fft->temp->offset = fft->MN + 1;
    fft->temp->length = fft->MN + 1;
    {
        vsip_vview_d *wtR = VI_vrealview_d(fft->temp,&wt1);
        vsip_vview_d *wtI = VI_vimagview_d(fft->temp,&wt2); 
        vsip_vramp_d((vsip_scalar_d)0, (vsip_scalar_d)VI_ft_d_PI/fft->MN,wtR);
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }
    fft->temp->offset = 0;
    fft->temp->length = fft->MN;
        
    if((fft->p0[0] == 1) && (fft->pF[0] == fft->MN)){
        fft->dft = 1;
    } else {
        fft->dft = 0;
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< fft->MN; i++) fft->index[i] = VI_jofk(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
