/* Created By RJudd October 14, 1998 */
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
/* $Id: VI_crfftop_create_f_def.h,v 2.2 2009/05/23 21:59:51 judd Exp $ */
/* real to complex fft */

#include"VI_nuV.h"
#include"VI_jofk.h"
#include"VI_vrealview_f.h"
#include"VI_vimagview_f.h"
#define VI_ft_f_2PI 6.2831853071795864769252866
#define VI_ft_f_PI  3.1415926535897932384626433

vsip_fft_f* vsip_crfftop_create_f(vsip_length N,
                       vsip_scalar_f scale,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_length i;
    vsip_vview_f wt1,wt2;
    vsip_fft_f *fft = (vsip_fft_f*) malloc(sizeof(vsip_fft_f));
    if(fft == NULL) return (vsip_fft_f*) NULL;
    fft->N = N/2;
    fft->scale = scale;
    fft->d = VSIP_FFT_INV;
    fft->pn = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->p0 = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->pF = (vsip_scalar_vi*)malloc(6 * sizeof(vsip_scalar_vi));
    fft->temp = vsip_cvcreate_f(3 * fft->N + 3,VSIP_MEM_NONE); /* create some work space */
    fft->wt = vsip_cvcreate_f(fft->N,VSIP_MEM_NONE);
    fft->index = (vsip_scalar_vi*) malloc(fft->N * sizeof(vsip_scalar_vi));
    /* check for creation problem */
    if( (fft->pn == NULL) || (fft->p0 == NULL) || 
        (fft->pF == NULL) || (fft->wt == NULL) || 
        (fft->temp == NULL) || (fft->index == NULL)){
          vsip_fft_destroy_f(fft);
          return (vsip_fft_f*) NULL;
    }
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_CRFFTOP; 
    /* calculate factors, fft->length is number of factors found */
    fft->length = VI_nuV(fft->N,
         fft->pn,
         fft->p0,
         fft->pF);

    /* create twiddle table */
    { 
        vsip_vview_f *wtR = VI_vrealview_f(fft->wt,&wt1);
        vsip_vview_f *wtI = VI_vimagview_f(fft->wt,&wt2); 
        vsip_vramp_f((vsip_scalar_f)0, (vsip_scalar_f)VI_ft_f_2PI/fft->N,wtR);  
        vsip_vsin_f(wtR,wtI);
        vsip_vcos_f(wtR,wtR);
    }
    /* create euler for rcfftop in fft->temp */
    fft->temp->offset = fft->N + 1;
    fft->temp->length = fft->N + 1;
    {
        vsip_vview_f *wtR = VI_vrealview_f(fft->temp,&wt1);
        vsip_vview_f *wtI = VI_vimagview_f(fft->temp,&wt2); 
        vsip_vramp_f((vsip_scalar_f)0, (vsip_scalar_f)VI_ft_f_PI/fft->N,wtR);
        vsip_vsin_f(wtR,wtI);
        vsip_vcos_f(wtR,wtR);
    }
    fft->temp->offset = 0;
    fft->temp->length = fft->N;
        
    if((fft->p0[0] == 1) && (fft->pF[0] == fft->N)){
        fft->dft = 1;
    } else {
        fft->dft = 0;
    }
    /* calculate unsorting vector */
    {
        vsip_scalar_vi pF = fft->pF[fft->length - 1];
        for(i = 0; i< fft->N; i++) fft->index[i] = VI_jofk(i,fft->pn,fft->p0,pF,fft->length);
    }
    return fft;
}
