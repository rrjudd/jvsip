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

/* $Id: fir_n3_N67_D1_d.h,v 2.2 2009/09/05 18:01:45 judd Exp $ */
#include"VU_vprintm_d.include"
static void fir_n3_N67_D1_d(void){
   printf("********\nTEST fir_n3_N67_D1_d\n");
   {
      vsip_length N = 67;
      vsip_length n = 0;
      vsip_length D = 1;
      vsip_length L=0;
      vsip_length ML=0;
      int p;
      int i;
      int num=3;
      vsip_vattr_d vattr;
      vsip_scalar_d k_data[]  = {
              1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
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
              0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0};
       vsip_block_d *k_block = vsip_blockbind_d(k_data,10,VSIP_MEM_NONE);
       vsip_block_d *in_block = vsip_blockbind_d((vsip_scalar_d*)NULL,201,VSIP_MEM_NONE);
       vsip_block_d *ans_block = vsip_blockbind_d(ans_data,201,VSIP_MEM_NONE);
       vsip_block_d *out_block = vsip_blockcreate_d(201,VSIP_MEM_NONE);
       vsip_vview_d *k = vsip_vbind_d(k_block,0,1,10);
       vsip_vview_d *in = vsip_vbind_d(in_block,0,1,67);
       vsip_vview_d *ans = vsip_vbind_d(ans_block,0,1,201);
       vsip_vview_d *out = vsip_vbind_d(out_block,0,1,201);

       vsip_block_d *block = vsip_blockcreate_d(500,VSIP_MEM_NONE);
       vsip_vview_d *in_V  = vsip_vbind_d(block,490,-3,67);
       vsip_vview_d *out_V = vsip_vbind_d(block,9,2,67);
       vsip_vview_d *k_V   = vsip_vbind_d(block,145,3,10);

       vsip_fir_d *fir;
       vsip_blockadmit_d(k_block,VSIP_TRUE);
       vsip_blockadmit_d(ans_block,VSIP_TRUE);
       vsip_vcopy_d_d(k,k_V);
       fir = vsip_fir_create_d(
                       k_V, /* kernel */
             VSIP_NONSYM, /* lets use the whole thing */
                       N, /* length input */
                       D, /* decimation */
         VSIP_STATE_SAVE, /* save state */
                       0,
                       0);
       
       vsip_vgetattrib_d(out,&vattr);
       printf("N = %d\nD = %d\n",(int)N,(int)D);
       printf("fir = vsip_fir_create_d( k,\n VSIP_NONSYM,\n N,\n D,\n VSIP_STATE_SAVE,\n 0,\n 0)\n");
       printf("kernel\n");VU_vprintm_d("3.2",k_V);
       /* set max length of output vector */
       ML = (N)/D;
       if((N)%D) ML+=1;
       vsip_vputlength_d(out_V,ML);
       /* set length and stride of answer vector */
       L = (num * N)/D;
       if((num * N)%D) L+=1;
       vsip_vputlength_d(ans,L);
       vsip_vputstride_d(ans,D);
       p=0; /* initialize p */
       for(i=0; i< num; i++){
           { L = (N-p)/D;
             if((N-p)%D) L+=1;
             p = (int)(D - 1 - (N-1-p)%D);
           }
           vsip_blockrebind_d(in_block,in_data+i*N);
           vsip_blockadmit_d(in_block,VSIP_TRUE);
           vsip_vcopy_d_d(in,in_V);
           vattr.offset = vattr.offset+n;
           n = vsip_firflt_d(fir,in_V,out_V);
           printf("n = vsip_firflt_d(fir,in,out)\n");
           printf("n= %d",(int)n);
           if(n == L) 
               printf(" ;correct\n");
           else
               printf(" ;error\n");
           printf("input\n"); VU_vprintm_d("3.2",in_V);
           vsip_vputlength_d(out_V,n);
           printf("output\n"); VU_vprintm_d("3.2",out_V);
           vattr.length = n;
           vsip_vputattrib_d(out,&vattr);
           vsip_vcopy_d_d(out_V,out);
           vsip_vputlength_d(out_V,ML);
           vsip_blockrelease_d(in_block,VSIP_FALSE);
       }
       vattr.length = vattr.offset + n;
       vattr.offset = 0;
       vsip_vputattrib_d(out,&vattr);
       printf("total output\n"); VU_vprintm_d("3.2",out);
       printf("right output\n"); VU_vprintm_d("3.2",ans);
       if(vsip_vgetlength_d(ans) != vattr.length){
           printf("error, ans length doesn't match out length\n");
       } else { vsip_vview_d *chk = vsip_vcreate_d(vsip_vgetlength_d(out),VSIP_MEM_NONE);
           vsip_vsub_d(ans,out,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
           if(vsip_vsumval_d(chk) > .5)
               printf("error\n");
           else
               printf("correct\n");
           vsip_valldestroy_d(chk);
       } 
       vsip_vdestroy_d(k_V);
       vsip_vdestroy_d(in_V);
       vsip_valldestroy_d(out_V);
       vsip_fir_destroy_d(fir);
       vsip_valldestroy_d(k);
       vsip_valldestroy_d(in);
       vsip_valldestroy_d(out);
       vsip_valldestroy_d(ans);
   }
   return;
}
