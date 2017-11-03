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
/* $Id: example18.c,v 1.1 2003/04/22 02:17:53 judd Exp $ */

#include<vsip.h>
#define ripple 100
#define Nlength 101
int main(){vsip_init((void*)0);
{
     void VU_vfprintyg_d(char*,vsip_vview_d*,char*);
     void VU_vfreqswapIP_d(vsip_vview_d*);
     vsip_vview_d* Cw = vsip_vcreate_cheby_d(Nlength,ripple,0);
     vsip_fft_d *fft  = vsip_ccfftip_create_d(Nlength,1.0,VSIP_FFT_FWD,0,0);
     vsip_cvview_d* FCW = vsip_cvcreate_d(Nlength,0);
     /*printf("CW = "); VU_vprintm_d("%6.8f ;\n",Cw); */
     VU_vfprintyg_d("%6.8f\n",Cw,"Cheby_Window");
     vsip_cvfill_d(vsip_cmplx_d(0,0),FCW);
     { vsip_vview_d *rv = vsip_vrealview_d(FCW);
       vsip_vcopy_d_d(Cw,rv);
       vsip_ccfftip_d(fft,FCW);
       vsip_vcmagsq_d(FCW,rv);
       { vsip_index ind;
         vsip_scalar_d max = vsip_vmaxval_d(rv,&ind);
         vsip_scalar_d min = max/(10e12);
         vsip_vclip_d(rv,min,max,min,max,rv);
       } 
       vsip_vlog10_d(rv,rv);
       vsip_svmul_d(10,rv,rv);
       VU_vfreqswapIP_d(rv);
         VU_vfprintyg_d("%6.8f\n",rv,"Cheby_Window_Frequency_Response");
       vsip_vdestroy_d(rv);
     }
     vsip_fft_destroy_d(fft);
     vsip_valldestroy_d(Cw);
     vsip_cvalldestroy_d(FCW);
     } vsip_finalize((void*)0); return 0;
}
void VU_vfreqswapIP_d(vsip_vview_d* b)
{   vsip_length N = vsip_vgetlength_d(b);
    if(N%2){/* odd */
       vsip_vview_d *a1 = vsip_vsubview_d(b,
                 (vsip_index)(N/2)+1,
                 (vsip_length)(N/2));
       vsip_vview_d *a2 = vsip_vsubview_d(b,
                 (vsip_index)0,
                 (vsip_length)(N/2)+1);
       vsip_vview_d *a3 = vsip_vcreate_d((vsip_length)(N/2)+1,
                          VSIP_MEM_NONE);
       vsip_vcopy_d_d(a2,a3);
       vsip_vputlength_d(a2,(vsip_length)(N/2));
       vsip_vcopy_d_d(a1,a2);
       vsip_vputlength_d(a2,(vsip_length)(N/2) + 1);
       vsip_vputoffset_d(a2,(vsip_offset)(N/2));
       vsip_vcopy_d_d(a3,a2);
       vsip_vdestroy_d(a1); vsip_vdestroy_d(a2);
       vsip_valldestroy_d(a3);
    }else{ /* even */
       vsip_vview_d *a1 = vsip_vsubview_d(b,
                 (vsip_index)(N/2),
                 (vsip_length)(N/2));
       vsip_vputlength_d(b,(vsip_length)(N/2));
       vsip_vswap_d(b,a1);
       vsip_vdestroy_d(a1);
       vsip_vputlength_d(b,N);
    }
    return;
}
void VU_vfprintyg_d(char* format, vsip_vview_d* a,char* fname)
{   vsip_length N = vsip_vgetlength_d(a);
    vsip_length i;
    FILE *of = fopen(fname,"w");
    for(i=0; i<N; i++)
           fprintf(of,format, vsip_vget_d(a,i));
    fclose(of);
    return;
}
