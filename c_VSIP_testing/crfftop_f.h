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
/* $Id: crfftop_f.h,v 2.2 2009/09/05 18:01:44 judd Exp $ */

#include"VU_vprintm_f.include"
#include"VU_cvprintm_f.include"
static void crfftop_f(void)
{
   printf("*********\nTEST crfftop \n");
   {
      vsip_length MAX_POINTS=24;
      vsip_length np[]={8,16,22,24},npm,n2;
      int i;
      vsip_scalar_f enp,t;
      vsip_cvview_f *x = vsip_cvcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_f *y = vsip_vcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_f  *xr = vsip_vrealview_f(x);
      vsip_vview_f  *xi = vsip_vimagview_f(x);
      vsip_vview_f  *ramp = vsip_vcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_vview_f  *chk = vsip_vcreate_f(MAX_POINTS,VSIP_MEM_NONE);
      vsip_cvview_f *xc = vsip_cvcloneview_f(x);
      vsip_cvview_f *xn = vsip_cvcloneview_f(x);
      vsip_vview_f  *xnr = vsip_vrealview_f(x);
      vsip_vview_f  *xni = vsip_vimagview_f(x);
      vsip_cvputstride_f(xc,-1);
      vsip_vputoffset_f(xnr,1);
      vsip_vputoffset_f(xni,1);
      vsip_cvputoffset_f(xn,1);
      vsip_vramp_f(0,1,ramp);
      
      for(i=0; i<4; i++){
        printf("vsip_fft_f *fft = vsip_crfftop_create_f(np,1.0,0,VSIP_ALG_SPACE)\n");
        printf("np = %4d\n",(int)np[i]);
        enp = np[i]; npm = np[i] / 2 - 1; t = M_PI / enp;
        vsip_cvputlength_f(x,np[i]);
        vsip_vputlength_f(y,np[i]);
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
        vsip_cvputlength_f(x,np[i]/2+1);
        vsip_vputlength_f(ramp,np[i]);
        { /* do fft */
          {
          vsip_fft_f *fft = vsip_crfftop_create_f(np[i],1.0,0,VSIP_ALG_SPACE);
          printf("x = ");VU_cvprintm_f("8.6",x);
          vsip_crfftop_f(fft,x,y);
          printf("vsip_crfftop_f(fft,x,y)\n");
          printf("y = ");VU_vprintm_f("8.6",y);
          vsip_fft_destroy_f(fft); 
          }
        }
        vsip_vputlength_f(chk,np[i]);
        printf("expected\n");VU_vprintm_f("7.4",ramp);
        vsip_vsub_f(y,ramp,chk); vsip_vmag_f(chk,chk);
        vsip_vclip_f(chk,.001,.001,0,1,chk);
        if(vsip_vsumval_f(chk) > .5)
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
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ramp);
     vsip_cvalldestroy_f(x);
     vsip_valldestroy_f(y);
  }
  return;
}
