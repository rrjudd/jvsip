/* Created RJudd March 16, 2012 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/
#include"vsip.h"
#include"vsip_cvviewattributes_d.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_rcfirattributes_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_cvfill_d.h"

vsip_rcfir_d *vsip_rcfir_create_d(
                                  const vsip_vview_d *kernel,
                                  vsip_symmetry symm,
                                  vsip_length N,
                                  vsip_length D,
                                  vsip_obj_state state,
                                  unsigned int ntimes,
                                  vsip_alg_hint hint)
{
    vsip_length klength = 0;
    vsip_rcfir_d *fir = (vsip_rcfir_d*)malloc(sizeof(vsip_rcfir_d));
    if(fir == NULL){ return (vsip_rcfir_d*) NULL;
    } else {
        switch(symm){
            case 0: klength = kernel->length;
                break;
            case 1: klength = 2 * kernel->length - 1;
                break;
            case 2: klength = 2 * kernel->length;
                break;
        }
        fir->h = vsip_vcreate_d(klength,VSIP_MEM_NONE);
        fir->s = vsip_cvcreate_d(klength-1,VSIP_MEM_NONE);
    }
    if((fir->h == NULL) | (fir->s == NULL)){ 
        vsip_rcfir_destroy_d(fir);
        return (vsip_rcfir_d*) NULL;
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
        VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),fir->s);
        return fir;
    }
}
