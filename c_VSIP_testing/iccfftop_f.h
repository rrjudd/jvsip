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
/* $Id: iccfftop_f.h,v 2.2 2009/09/05 18:01:44 judd Exp $ */

#include"VU_cvprintm_f.include"
static void iccfftop_f(void)
{  
   printf("********\nTEST ccfftop inverse\n");
   {
      vsip_length MAX_POINTS=24;
      vsip_length np[]={8,16,22,24},npm,n2;
      int i;
      vsip_scalar_f enp,t;
      vsip_cvview_f *x = vsip_cvcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_cvview_f *y = vsip_cvcreate_f(MAX_POINTS,VSIP_MEM_NONE);
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
      vsip_cvputstride_f(xc,-1);
      vsip_vputoffset_f(xnr,1);
      vsip_vputoffset_f(xni,1);
      vsip_cvputoffset_f(xn,1);
      vsip_vramp_f(0,1,ramp_r);
      vsip_vfill_f(0,ramp_i);
      
      for(i=0; i<4; i++){
        printf("vsip_fft_f *fft = vsip_ccfftop_create_f(np,1.0,VSIP_FFT_INV,0,VSIP_ALG_SPACE)\n");
        printf("np = %4d\n",(int)np[i]);
        enp = np[i]; npm = np[i] / 2 - 1; t = M_PI / enp;
        vsip_cvputlength_f(x,np[i]);
        vsip_cvputlength_f(y,np[i]);
        vsip_cvputlength_f(xc,npm); vsip_cvputoffset_f(xc,np[i]-1);
        vsip_cvputlength_f(xn,npm);
        vsip_vputlength_f(xnr,npm);
        vsip_vputlength_f(xni,npm);
        vsip_cvput_f(x,0,vsip_cmplx_f((enp -1.0)/2.0,0));
        n2 = np[i] / 2; vsip_cvput_f(x,n2,vsip_cmplx_f(-0.5,0));
        vsip_vramp_f(t,t,xni);
        vsip_vcos_f(xni,xnr);
        vsip_vsin_f(xni,xni);
        vsip_vdiv_f(xnr,xni,xni);
        vsip_svmul_f(-0.5,xni,xni);
        vsip_vfill_f(-0.5,xnr);
        vsip_cvconj_f(xn,xc);
        vsip_cvconj_f(x,x);
        { /* do fft */
          {
          vsip_fft_f *fft = vsip_ccfftop_create_f(np[i],1.0,VSIP_FFT_INV,0,VSIP_ALG_SPACE);
          printf("x = ");VU_cvprintm_f("8.6",x);
          vsip_ccfftop_f(fft,x,y);
          printf("vsip_ccfftop_f(fft,x,y)\n");
          printf("y = ");VU_cvprintm_f("8.6",y);
          vsip_fft_destroy_f(fft); 
          }
        }
        vsip_cvputlength_f(cramp,np[i]);
        vsip_cvputlength_f(chk,np[i]); vsip_vputlength_f(chk_r,np[i]);
        printf("expected\n");VU_cvprintm_f("7.4",cramp);
        vsip_cvsub_f(y,cramp,chk); vsip_cvmag_f(chk,chk_r);
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
     vsip_cvalldestroy_f(y);
   }
   return;
}
