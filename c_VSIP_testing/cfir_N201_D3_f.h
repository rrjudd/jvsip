/* Created by RJudd */
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

/* $Id: cfir_N201_D3_f.h,v 2.2 2009/09/05 18:01:45 judd Exp $ */
#include"VU_cvprintm_f.include"
static void cfir_N201_D3_f(void){
   printf("********\nTEST cfir_N201_D3_f\n");
   {
      vsip_length N = 201;
      vsip_length D = 3;
      vsip_length n = 0;
      vsip_length L = 0;
      vsip_scalar_f k_data_r[]  = {
              1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
      vsip_scalar_f k_data_i[]  = {
              1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
      vsip_scalar_f in_data_r[] = {0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      vsip_scalar_f in_data_i[] = {0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      vsip_scalar_f ans_data_r[] = {0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      vsip_scalar_f ans_data_i[] = {0.0,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2,
              0.1*2, 0.2*2, 0.3*2, 0.4*2, 0.5*2, 0.6*2, 0.7*2, 0.8*2, 0.9*2, 1.0*2,
              0.9*2, 0.8*2, 0.7*2, 0.6*2, 0.5*2, 0.4*2, 0.3*2, 0.2*2, 0.1*2, 0.0*2};
       vsip_cblock_f *k_block = vsip_cblockbind_f(k_data_r,k_data_i,10,VSIP_MEM_NONE);
       vsip_cblock_f *in_block = vsip_cblockbind_f(in_data_r,in_data_i,201,VSIP_MEM_NONE);
       vsip_cblock_f *ans_block = vsip_cblockbind_f(ans_data_r,ans_data_i,201,VSIP_MEM_NONE);
       vsip_cblock_f *out_block = vsip_cblockcreate_f(201,VSIP_MEM_NONE);
       vsip_cvview_f *k = vsip_cvbind_f(k_block,0,1,10);
       vsip_cvview_f *in = vsip_cvbind_f(in_block,0,1,201);
       vsip_cvview_f *ans = vsip_cvbind_f(ans_block,0,1,201);
       vsip_cvview_f *out = vsip_cvbind_f(out_block,0,1,201);
       vsip_cfir_f *fir;
       vsip_cblockadmit_f(k_block,VSIP_TRUE);
       vsip_cblockadmit_f(in_block,VSIP_TRUE);

       vsip_cblockadmit_f(ans_block,VSIP_TRUE);
       { L = N/D;
         if(N%D) L+=1;
         vsip_cvputlength_f(ans,L);
         vsip_cvputlength_f(out,L);
         vsip_cvputstride_f(ans,D);
         vsip_cvputstride_f(out,D);
       }
       fir = vsip_cfir_create_f(
                       k, /* kernel */
             VSIP_NONSYM, /* lets use the whole thing */
                       N, /* length input */
                       D, /* decimation */
         VSIP_STATE_SAVE, /* save state */
                       0,
                       0);
       n = vsip_cfirflt_f(fir,in,out);
       printf("N = %d\nD = %d\n",(int)N,(int)D);
       printf("fir = vsip_cfir_create_f( k,\n VSIP_NONSYM,\n N,\n D,\n VSIP_STATE_SAVE,\n 0,\n 0)\n");
       printf("n = vsip_cfirflt_f(fir,in,out)\n");
       printf("n = %d",(int)n);
       if(n == L)
           printf(" ;correct\n");
       else
           printf(" ;error\n");
       printf("kernel\n");VU_cvprintm_f("3.2",k);
       printf("input\n"); VU_cvprintm_f("3.2",in);
       printf("output\n"); VU_cvprintm_f("3.2",out);
       printf("right output\n"); VU_cvprintm_f("3.2",ans);
       { vsip_cvview_f *chk = vsip_cvcreate_f(vsip_cvgetlength_f(out),VSIP_MEM_NONE);
         vsip_vview_f *chk_r = vsip_vrealview_f(chk);
         vsip_cvsub_f(ans,out,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_vsumval_f(chk_r) > .5)
             printf("error\n");
         else
             printf("correct\n");
         vsip_vdestroy_f(chk_r);
         vsip_cvalldestroy_f(chk);
       }
       vsip_cfir_destroy_f(fir);
       vsip_cvalldestroy_f(k);
       vsip_cvalldestroy_f(in);
       vsip_cvalldestroy_f(out);
       vsip_cvalldestroy_f(ans);
   }
   return;
}
