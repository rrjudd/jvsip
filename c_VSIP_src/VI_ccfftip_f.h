/* Created by RJudd August 2, 2002 */
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
/* $Id: VI_ccfftip_f.h,v 2.2 2007/04/16 16:23:59 judd Exp $ */
#ifndef VI_CCFFTIP_F_H
#define VI_CCFFTIP_F_H 1

/******************************************************************/
/* init fft to x */
static
void  
init_fft_f(void *tx,void* tfft){
  vsip_cvview_f *x = (vsip_cvview_f*) tx;
  vsip_fft_f* fft = (vsip_fft_f*) tfft;
  fft->x = x;
  fft->stage =0;
  return;
}

/* VI_sort_copy_f.c */
/*========================================================*/
static
void 
VI_sort_copy_f(void* tfft){
  vsip_fft_f* fft = (vsip_fft_f*)tfft;
  vsip_scalar_vi *x = fft->index;
  vsip_cvview_f *a = fft->x;
  vsip_cvview_f *r = fft->temp;
  vsip_length n =  fft->N;
  vsip_stride cast = a->block->cstride;
  vsip_stride ast =  cast * a->stride;
  vsip_stride rst = r->block->cstride;
  vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                *rpr = (vsip_scalar_f*) r->block->R->array ;
  vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset),
                *rpi = (vsip_scalar_f*) r->block->I->array;
  vsip_scalar_f *apr2 = apr,
                *rpr2 = rpr;
  vsip_scalar_f *api2 = api,
                *rpi2 = rpi;
  vsip_stride xinc = 0;
  while(n-- >0){
     xinc = *x * ast;
     *rpr = *(apr + xinc);
     *rpi = *(api + xinc);
      rpr += rst; rpi += rst; 
      x++;
  }
  n = fft->N;
  while(n-- >0){
     *apr2 = *rpr2;
     *api2 = *rpi2;
     apr2 += ast; api2 += ast;
     rpr2 += rst; rpi2 += rst;
  }
  return;
}

static
void 
VI_ccfftip_f(const vsip_fft_f* fft, const vsip_cvview_f *x) {
  void* fft_v = (void*) fft;
  void* x_v = (void*) x;
  init_fft_f(x_v,fft_v);
  if(fft->dft == 1){
     VI_dft_f(fft_v);
  }else{
     VI_p0pF_f(fft_v);
     VI_sort_copy_f(fft_v);
  }
  if (fft->scale != 1) vsip_rscvmul_f(fft->scale,x,x);
  return;
}
#endif
