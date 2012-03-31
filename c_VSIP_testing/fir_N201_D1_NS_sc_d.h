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

/* $Id: fir_N201_D1_NS_sc_d.h,v 2.2 2009/09/05 18:01:45 judd Exp $ */
#include"VU_vprintm_d.include"
static void fir_N201_D1_NS_sc_d(void){
   printf("********\nTEST fir_N201_D1_NS_sc_d\n");
   {
      vsip_length N = 201;
      vsip_length n = 0;
      vsip_length D = 1;
      vsip_scalar_d k_data[]  = {
              0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
      vsip_scalar_d in_data[] = {0.0,
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
      vsip_scalar_d ans_data[] = {0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0,
              0.0, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
              0.8, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0};
       vsip_block_d *k_block = vsip_blockbind_d(k_data,10,VSIP_MEM_NONE);
       vsip_block_d *in_block = vsip_blockbind_d(in_data,201,VSIP_MEM_NONE);
       vsip_block_d *ans_block = vsip_blockbind_d(ans_data,201,VSIP_MEM_NONE);
       vsip_block_d *out_block = vsip_blockcreate_d(201,VSIP_MEM_NONE);
       vsip_vview_d *k = vsip_vbind_d(k_block,0,1,10);
       vsip_vview_d *in = vsip_vbind_d(in_block,0,1,201);
       vsip_vview_d *ans = vsip_vbind_d(ans_block,0,1,201);
       vsip_vview_d *out = vsip_vbind_d(out_block,0,1,201);
       vsip_fir_d *fir;
       vsip_blockadmit_d(k_block,VSIP_TRUE);
       vsip_blockadmit_d(in_block,VSIP_TRUE);
       vsip_blockadmit_d(ans_block,VSIP_TRUE);
       fir = vsip_fir_create_d(
                       k, /* kernel */
             VSIP_NONSYM, /* lets use the whole thing */
                       N, /* length input */
                       D, /* decimation */
         VSIP_STATE_NO_SAVE, /* save state */
                       0,
                       0);
       n = vsip_firflt_d(fir,in,out);
       printf("N = %d\nD = %d\n",(int)N,(int)D);
       printf("fir = vsip_fir_create_d( k,\n VSIP_NONSYM,\n N,\n D,\n VSIP_STATE_NO_SAVE,\n 0,\n 0)\n");
       printf("n = vsip_firflt_d(fir,in,out)\n");
       printf("n= %d",(int)n);
       if(n == N) 
           printf(" ;correct\n");
       else
           printf(" ;error\n");
       printf("kernel\n");VU_vprintm_d("3.2",k);
       printf("input\n"); VU_vprintm_d("3.2",in);
       printf("output\n"); VU_vprintm_d("3.2",out);
       printf("right output\n"); VU_vprintm_d("3.2",ans);
       { vsip_vview_d *chk = vsip_vcreate_d(vsip_vgetlength_d(out),VSIP_MEM_NONE);
         vsip_vsub_d(ans,out,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
         if(vsip_vsumval_d(chk) > .5)
             printf("error\n");
         else
             printf("correct\n");
         vsip_valldestroy_d(chk);
       } 
       vsip_fir_destroy_d(fir);
       vsip_valldestroy_d(k);
       vsip_valldestroy_d(in);
       vsip_valldestroy_d(out);
       vsip_valldestroy_d(ans);
   }
   return;
}
