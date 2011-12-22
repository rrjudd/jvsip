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

/* $Id: fir_N200_D1_f.h,v 2.2 2009/09/05 18:01:45 judd Exp $ */
static void fir_N200_D1_f(void){
   printf("********\nTEST fir_N200_D1_f\n");
   {
      vsip_length N = 200;
      vsip_length n = 0;
      vsip_length D = 1;
      vsip_scalar_f k_data[]  = {
              1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
      vsip_scalar_f in_data[] = {0.0,
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
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, };
      vsip_scalar_f ans_data[] = {0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, };
       vsip_block_f *k_block = vsip_blockbind_f(k_data,10,VSIP_MEM_NONE);
       vsip_block_f *in_block = vsip_blockbind_f(in_data,N,VSIP_MEM_NONE);
       vsip_block_f *ans_block = vsip_blockbind_f(ans_data,N,VSIP_MEM_NONE);
       vsip_block_f *out_block = vsip_blockcreate_f(N,VSIP_MEM_NONE);
       vsip_vview_f *k = vsip_vbind_f(k_block,0,1,10);
       vsip_vview_f *in = vsip_vbind_f(in_block,0,1,N);
       vsip_vview_f *ans = vsip_vbind_f(ans_block,0,1,N);
       vsip_vview_f *out = vsip_vbind_f(out_block,0,1,N);
       vsip_fir_f *fir;
       vsip_blockadmit_f(k_block,VSIP_TRUE);
       vsip_blockadmit_f(in_block,VSIP_TRUE);
       vsip_blockadmit_f(ans_block,VSIP_TRUE);
       fir = vsip_fir_create_f(
                       k, /* kernel */
             VSIP_NONSYM, /* lets use the whole thing */
                       N, /* length input */
                       D, /* decimation */
         VSIP_STATE_SAVE, /* save state */
                       0,
                       0);
       n = vsip_firflt_f(fir,in,out);
       printf("N = %d\nD = %d\n",(int)N,(int)D);
       printf("fir = vsip_fir_create_f( k,\n VSIP_NONSYM,\n N,\n D,\n VSIP_STATE_SAVE,\n 0,\n 0)\n");
       printf("n = vsip_firflt_f(fir,in,out)\n");
       printf("n= %d",(int)n);
       if(n == N) 
           printf(" ;correct\n");
       else
           printf(" ;error\n");
       printf("kernel\n");VU_vprintm_f("3.2",k);
       printf("input\n"); VU_vprintm_f("3.2",in);
       printf("output\n"); VU_vprintm_f("3.2",out);
       printf("right output\n"); VU_vprintm_f("3.2",ans);
       { vsip_vview_f *chk = vsip_vcreate_f(vsip_vgetlength_f(out),VSIP_MEM_NONE);
         vsip_vsub_f(ans,out,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
         if(vsip_vsumval_f(chk) > .5)
             printf("error\n");
         else
             printf("correct\n");
         vsip_valldestroy_f(chk);
       } 
       vsip_fir_destroy_f(fir);
       vsip_valldestroy_f(k);
       vsip_valldestroy_f(in);
       vsip_valldestroy_f(out);
       vsip_valldestroy_f(ans);
   }
   return;
}
