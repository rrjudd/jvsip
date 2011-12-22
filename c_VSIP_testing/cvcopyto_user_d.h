/* Created RJudd */
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
/* $Id: cvcopyto_user_d.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */

static void cvcopyto_user_d(void){
   int i;
   printf("********\nTEST cvcopyto_user_d\n");
   { /* test interleaved */
      vsip_cblock_d *block = vsip_cblockcreate_d(200,VSIP_MEM_NONE);
      vsip_scalar_d output[10];
      vsip_scalar_d ans[10]={0,1,2,3,4,5,6,7,8,9};
      vsip_scalar_d check = 0;
      vsip_cvview_d *view = vsip_cvbind_d(block,100,-2,5);
      vsip_cvview_d *all = vsip_cvbind_d(block,0,1,200);
      vsip_cvfill_d(vsip_cmplx_d(-1,-1),all);
      for(i=0; i<5; i++){
         vsip_cscalar_d t = vsip_cmplx_d((vsip_scalar_d)i*2, (vsip_scalar_d)i*2+1); 
         vsip_cvput_d(view,(vsip_index)i,t);
      }
      printf("interleaved\n");
      VU_cvprintm_d("3.2",view);
      vsip_cvcopyto_user_d(view,output,(vsip_scalar_d*)NULL);
      for(i=0; i<10; i++){
	printf("%f\n",(float)output[i]);
        check += fabs(output[i]-ans[i]);
      }
      if(check < 0.1){ 
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_cvdestroy_d(all);
      vsip_cvdestroy_d(view);
      vsip_cblockdestroy_d(block); 
   }
   { /* test split */
      vsip_cblock_d *block = vsip_cblockcreate_d(200,VSIP_MEM_NONE);
      vsip_scalar_d output_r[5];
      vsip_scalar_d output_i[5];
      vsip_scalar_d ans_r[5]={0,2,4,6,8};
      vsip_scalar_d ans_i[5]={1,3,5,7,9};
      vsip_scalar_d check = 0;
      vsip_cvview_d *view = vsip_cvbind_d(block,100,3,5);
      vsip_cvview_d *all = vsip_cvbind_d(block,0,1,200);
      vsip_cvfill_d(vsip_cmplx_d(-1,-1),all);
      for(i=0; i<5; i++){
         vsip_cscalar_d t = vsip_cmplx_d((vsip_scalar_d)i*2, (vsip_scalar_d)i*2+1);
         vsip_cvput_d(view,(vsip_index)i,t);
      }
      printf("split\n");
      VU_cvprintm_d("3.2",view);
      vsip_cvcopyto_user_d(view,output_r,output_i);
      for(i=0; i<5; i++){
        printf("%f\n",(float)output_r[i]);
        check += fabs(output_r[i]-ans_r[i]);
        printf("%f\n",(float)output_i[i]);
        check += fabs(output_i[i]-ans_i[i]);
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_cvdestroy_d(all);
      vsip_cvdestroy_d(view);
      vsip_cblockdestroy_d(block);
   }
   return;
}
