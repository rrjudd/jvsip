/* Created By RJudd June 16, 2002 */
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
/* $Id: VI_fftw_obj.h,v 2.0 2003/02/22 15:18:32 judd Exp $ */

/* object to encapsulate fftwone function for fft's */

#ifndef _VI_FFTW_OBJ_H
#define _VI_FFTW_OBJ_H
#include<fftw.h>
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cvviewattributes_d.h>
#include<VU.h>

typedef struct {
   fftw_complex *in;
   fftw_complex *out;
   fftw_plan p;
} vsipl_fftw_obj;

#ifdef __VSIPL_FFTWOBJ_INIT
static
vsipl_fftw_obj *vsipl_fftwobj_create(){
    return (vsipl_fftw_obj*) malloc(sizeof(vsipl_fftw_obj));
}

static
int 
vsipl_fftwobj_init(
          vsipl_fftw_obj* *obj,
          fftw_direction dir,    /* direction of fft */
          int n,                 /* length of fft    */
          int flags){
   int retval = 0;
   *obj = vsipl_fftwobj_create();
   if(obj != NULL){
      #if defined(VSIP_ASSUME_COMPLEX_IS_INTERLEAVED)
         (*obj)->in = NULL;
         (*obj)->out = NULL;
      #else
         (*obj)->in  = (fftw_complex*)malloc(n * sizeof(fftw_complex));
         if((*obj)->in == NULL) retval++;
         (*obj)->out = (fftw_complex*)malloc(n * sizeof(fftw_complex));
         if((*obj)->out == NULL) retval++;
      #endif
      (*obj)->p   = fftw_create_plan(n,dir,flags);
      if((*obj)->p == NULL) retval++;
   } else {
     retval++;
   }
   return retval;
}
#endif

#ifdef __VSIPL_FFTWOBJ_FIN
static
void
vsipl_fftwobj_fin(
          vsipl_fftw_obj *obj) {
   if(obj != NULL){
      if(obj->in != NULL) free(obj->in);
      if(obj->out != NULL) free(obj->out);
      if(obj->p != NULL) fftw_destroy_plan(obj->p);
      free(obj);
    }
    return;
}
#endif

#ifdef __VSIPL_CVCOPY_TO_FFTW_F
static
void
vsipl_cvcopy_to_fftw_f(
          const vsip_cvview_f *v,
          vsipl_fftw_obj *obj){
   vsip_length n = v->length;
   fftw_complex *ptr = obj->in;
   vsip_offset offset = v->offset * v->block->R->rstride;
   vsip_scalar_f *ptr_r = v->block->R->array + offset;
   vsip_scalar_f *ptr_i = v->block->I->array + offset;
   vsip_stride str = v->block->R->rstride * v->stride; 
   while(n-- > 0){
     (*ptr).re = (fftw_real)*ptr_r; (*ptr).im = (fftw_real)*ptr_i;
      ptr++; ptr_r += str; ptr_i += str;
   } 
}
#endif
      
#ifdef __VSIPL_CVCOPY_FROM_FFTW_F
static
void
vsipl_cvcopy_from_fftw_f(
          vsipl_fftw_obj *obj,
          const vsip_cvview_f *v){
   vsip_length n = v->length;
   fftw_complex *ptr = obj->out;
   vsip_offset offset = v->offset * v->block->R->rstride;
   vsip_scalar_f *ptr_r = v->block->R->array + offset;
   vsip_scalar_f *ptr_i = v->block->I->array + offset;
   vsip_stride str = v->block->R->rstride * v->stride; 
   while(n-- > 0){
     *ptr_r = (vsip_scalar_f)((*ptr).re); *ptr_i = (vsip_scalar_f)((*ptr).im);
      ptr++; ptr_r += str; ptr_i += str;
   } 
}
#endif
    
#ifdef __VSIPL_CVCOPY_TO_FFTW_D
static
void
vsipl_cvcopy_to_fftw_d(
          const vsip_cvview_d *v,
          vsipl_fftw_obj *obj){
   vsip_length n = v->length;
   fftw_complex *ptr = obj->in;
   vsip_offset offset = v->offset * v->block->R->rstride;
   vsip_scalar_d *ptr_r = v->block->R->array + offset;
   vsip_scalar_d *ptr_i = v->block->I->array + offset;
   vsip_stride str = v->block->R->rstride * v->stride; 
   while(n-- > 0){
     (*ptr).re = (fftw_real)*ptr_r; (*ptr).im = (fftw_real)*ptr_i;
      ptr++; ptr_r += str; ptr_i += str;
   } 
}
#endif
      
#ifdef __VSIPL_CVCOPY_FROM_FFTW_D
static
void
vsipl_cvcopy_from_fftw_d(
          vsipl_fftw_obj *obj,
          const vsip_cvview_d *v){
   vsip_length n = v->length;
   fftw_complex *ptr = obj->out;
   vsip_offset offset = v->offset * v->block->R->rstride;
   vsip_scalar_d *ptr_r = v->block->R->array + offset;
   vsip_scalar_d *ptr_i = v->block->I->array + offset;
   vsip_stride str = v->block->R->rstride * v->stride; 
   while(n-- > 0){
     *ptr_r = (vsip_scalar_d)((*ptr).re); *ptr_i = (vsip_scalar_d)((*ptr).im);
      ptr++; ptr_r += str; ptr_i += str;
   } 
}
#endif
    
#endif /* _VI_FFTW_OBJ_H */
