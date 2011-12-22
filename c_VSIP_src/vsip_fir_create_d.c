/* Created RJudd December 14, 1998 */
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
/* $Id: vsip_fir_create_d.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_firattributes_d.h>
#include"VI_vcreate_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_vfill_d.h"

vsip_fir_d *vsip_fir_create_d(
              const vsip_vview_d *kernel,
              vsip_symmetry symm,
              vsip_length N,
              vsip_length D,
              vsip_obj_state state,
              unsigned int ntimes,
              vsip_alg_hint hint)
{
    vsip_length klength = 0;
    vsip_fir_d *fir = (vsip_fir_d*)malloc(sizeof(vsip_fir_d));
    if(fir == NULL){ return (vsip_fir_d*) NULL;
    } else {
        switch(symm){
           case 0: klength = kernel->length;
                   break;
           case 1: klength = 2 * kernel->length - 1;
                   break;
           case 2: klength = 2 * kernel->length;
                   break;
        }
        fir->h = VI_vcreate_d(klength,VSIP_MEM_NONE);
        fir->s = VI_vcreate_d(klength-1,VSIP_MEM_NONE);
    }
    if((fir->h == NULL) | (fir->s == NULL)){ 
        vsip_fir_destroy_d(fir);
        return (vsip_fir_d*) NULL;
    } else {
       fir->N = N;
       fir->M = klength;
       fir->D = D;
       fir->p = 0;
       fir->ntimes = ntimes;
       fir->symm = symm;
       fir->hint = hint;
       switch(symm){
           case 0:{
              fir->h->offset = fir->h->length - 1;
              fir->h->stride = -1;
              VI_vcopy_d_d(kernel,fir->h);
           }
           break;
           case 1: {
              fir->h->length = kernel->length;
              VI_vcopy_d_d(kernel,fir->h);
              fir->h->offset = klength - 1;
              fir->h->stride = -1;
              VI_vcopy_d_d(kernel,fir->h);
              fir->h->length = klength;
           }
           break;
           case 2: {
              fir->h->length = kernel->length;
              VI_vcopy_d_d(kernel,fir->h);
              fir->h->offset = klength - 1;
              fir->h->stride = -1;
              VI_vcopy_d_d(kernel,fir->h);
              fir->h->length = klength;
           }
           break;
       }
       fir->state = state;
       fir->h->offset = 0;
       fir->h->stride = 1;
       VI_vfill_d(0,fir->s);
       return fir;
    }
}
