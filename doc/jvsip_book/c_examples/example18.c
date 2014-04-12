#include<vsip.h>
#define ripple 100
#define Nlength 101
int main(){vsip_init((void*)0);
{
     void VU_vfprintyg_f(char*,vsip_vview_f*,char*);
     void VU_vfreqswapIP_f(vsip_vview_f*);
     vsip_vview_f* Cw = vsip_vcreate_cheby_f(Nlength,ripple,0);
     vsip_fft_f *fft  = vsip_ccfftip_create_f(Nlength,1.0,VSIP_FFT_FWD,0,0);
     vsip_cvview_f* FCW = vsip_cvcreate_f(Nlength,0);
     /*printf("CW = "); VU_vprintm_f("%6.8f ;\n",Cw); */
     VU_vfprintyg_f("%6.8f\n",Cw,"Cheby_Window");
     vsip_cvfill_f(vsip_cmplx_f(0,0),FCW);
     { vsip_vview_f *rv = vsip_vrealview_f(FCW);
       vsip_vcopy_f_f(Cw,rv);
       vsip_ccfftip_f(fft,FCW);
       vsip_vcmagsq_f(FCW,rv);
       { vsip_index ind;
         vsip_scalar_f max = vsip_vmaxval_f(rv,&ind);
         vsip_scalar_f min = max/(10e12);
         vsip_vclip_f(rv,min,max,min,max,rv);
       } 
       vsip_vlog10_f(rv,rv);
       vsip_svmul_f(10,rv,rv);
       VU_vfreqswapIP_f(rv);
         VU_vfprintyg_f("%6.8f\n",rv,"Cheby_Window_Frequency_Response");
       vsip_vdestroy_f(rv);
     }
     vsip_fft_destroy_f(fft);
     vsip_valldestroy_f(Cw);
     vsip_cvalldestroy_f(FCW);
     } vsip_finalize((void*)0); return 0;
}
void VU_vfreqswapIP_f(vsip_vview_f* b)
{   vsip_length N = vsip_vgetlength_f(b);
    if(N%2){/* odd */
       vsip_vview_f *a1 = vsip_vsubview_f(b,
                 (vsip_index)(N/2)+1,
                 (vsip_length)(N/2));
       vsip_vview_f *a2 = vsip_vsubview_f(b,
                 (vsip_index)0,
                 (vsip_length)(N/2)+1);
       vsip_vview_f *a3 = vsip_vcreate_f((vsip_length)(N/2)+1,
                          VSIP_MEM_NONE);
       vsip_vcopy_f_f(a2,a3);
       vsip_vputlength_f(a2,(vsip_length)(N/2));
       vsip_vcopy_f_f(a1,a2);
       vsip_vputlength_f(a2,(vsip_length)(N/2) + 1);
       vsip_vputoffset_f(a2,(vsip_offset)(N/2));
       vsip_vcopy_f_f(a3,a2);
       vsip_vdestroy_f(a1); vsip_vdestroy_f(a2);
       vsip_valldestroy_f(a3);
    }else{ /* even */
       vsip_vview_f *a1 = vsip_vsubview_f(b,
                 (vsip_index)(N/2),
                 (vsip_length)(N/2));
       vsip_vputlength_f(b,(vsip_length)(N/2));
       vsip_vswap_f(b,a1);
       vsip_vdestroy_f(a1);
       vsip_vputlength_f(b,N);
    }
    return;
}
void VU_vfprintyg_f(char* format, vsip_vview_f* a,char* fname)
{   vsip_length N = vsip_vgetlength_f(a);
    vsip_length i;
    FILE *of = fopen(fname,"w");
    for(i=0; i<N; i++)
           fprintf(of,format, vsip_vget_f(a,i));
    fclose(of);
    return;
}
