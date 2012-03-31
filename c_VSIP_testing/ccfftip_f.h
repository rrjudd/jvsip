/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: ccfftip_f.h,v 2.3 2009/09/05 18:01:44 judd Exp $ */

#include"VU_cvprintm_f.include"
static void ccfftip_f(void)
{  
   printf("******\nTEST ccfftip forward\n");
   {
      vsip_length MAX_POINTS=24;
      vsip_length np[]={8,16,22,24},npm,n2;
      int i;
      vsip_scalar_f enp,t;
      vsip_cvview_f *x = vsip_cvcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_f  *xr = vsip_vrealview_f(x);
      vsip_vview_f  *xi = vsip_vimagview_f(x);
      vsip_cvview_f  *cramp = vsip_cvcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_f  *ramp_r = vsip_vrealview_f(cramp);
      vsip_vview_f  *ramp_i = vsip_vimagview_f(cramp);
      vsip_cvview_f  *chk = vsip_cvcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_f  *chk_r = vsip_vrealview_f(chk);
      vsip_cvview_f *xc = vsip_cvcloneview_f(x);
      vsip_cvview_f *xn = vsip_cvcloneview_f(x);
      vsip_vview_f  *xnr = vsip_vrealview_f(x);
      vsip_vview_f  *xni = vsip_vimagview_f(x);
      vsip_cvattr_f xc_attr;
      vsip_cvattr_f xn_attr;
      vsip_vattr_f  xnir_attr;
      vsip_cvgetattrib_f(xc,&xc_attr);
      vsip_cvgetattrib_f(xn,&xn_attr);
      vsip_vgetattrib_f(xni,&xnir_attr);

      xc_attr.stride = -1;
      xn_attr.offset = 1;
      xnir_attr.offset = 1;
      vsip_vramp_f(0,1,ramp_r);
      vsip_vfill_f(0,ramp_i);
      
      for(i=0; i<4; i++){
        printf("vsip_fft_f *fft = vsip_ccfftip_create_f(np,1.0,VSIP_FFT_FWD,0,VSIP_ALG_SPACE)\n");
        printf("np = %4d\n",(int)np[i]);
        enp = np[i]; npm = np[i] / 2 - 1; t = M_PI / enp;
        vsip_cvputlength_f(x,np[i]);
        xc_attr.length = npm; xc_attr.offset = np[i] -1;
        xn_attr.length = npm; xnir_attr.length = npm;
        vsip_cvputattrib_f(xc, &xc_attr);
        vsip_cvputattrib_f(xn, &xn_attr);
        vsip_vputattrib_f(xni, &xnir_attr); vsip_vputattrib_f(xnr, &xnir_attr);
        vsip_cvput_f(x,0,vsip_cmplx_f((enp -1.0)/2.0,0));
        n2 = np[i] / 2; vsip_cvput_f(x,n2,vsip_cmplx_f(-0.5,0));
        vsip_vramp_f(t,t,xni);
        vsip_vcos_f(xni,xnr);
        vsip_vsin_f(xni,xni);
        vsip_vdiv_f(xnr,xni,xni);
        vsip_svmul_f(-0.5,xni,xni);
        vsip_vfill_f(-0.5,xnr);
        vsip_cvconj_f(xn,xc);
        { /* do fft */
          {
          vsip_fft_f *fft = vsip_ccfftip_create_f(np[i],1.0,VSIP_FFT_FWD,0,VSIP_ALG_SPACE);
          printf("x = ");VU_cvprintm_f("8.6",x);
          vsip_ccfftip_f(fft,x);
          printf("vsip_ccfftip_f(fft,x)\n");
          printf("x = ");VU_cvprintm_f("8.6",x);
          vsip_fft_destroy_f(fft); 
          }
        }
        vsip_cvputlength_f(cramp,np[i]); 
        vsip_cvputlength_f(chk,np[i]);vsip_vputlength_f(chk_r,np[i]);
        printf("expected\n");VU_cvprintm_f("7.4",cramp);
        vsip_cvsub_f(x,cramp,chk); vsip_cvmag_f(chk,chk_r);
        vsip_vclip_f(chk_r,.001,.001,0,1,chk_r);
        if(vsip_vsumval_f(chk_r) > .5)
            printf("error\n");
        else
            printf("correct\n");
     }
     vsip_vdestroy_f(xnr);
     vsip_vdestroy_f(xni);
     vsip_cvdestroy_f(xn);
     vsip_cvdestroy_f(xc);
     vsip_vdestroy_f(xr);
     vsip_vdestroy_f(xi);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
     vsip_vdestroy_f(ramp_r);
     vsip_vdestroy_f(ramp_i);
     vsip_cvalldestroy_f(cramp);
     vsip_cvalldestroy_f(x);
  }
  return;
}
