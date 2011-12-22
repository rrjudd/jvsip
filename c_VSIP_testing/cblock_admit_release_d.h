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
/* $Id: cblock_admit_release_d.h,v 2.0 2003/02/22 15:23:32 judd Exp $ */
static void cblock_admit_release_d(void){
   printf("********\nTEST cblock_admit_release_d\n");
   {
      int i;
      vsip_scalar_d *ptr1,*ptr2;
      vsip_scalar_d *ptr1s,*ptr2s;
      vsip_scalar_d data_r[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
      vsip_scalar_d data_i[10] = { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
      vsip_scalar_d datarb_r[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
      vsip_scalar_d datarb_i[10] = { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
      vsip_scalar_d data_ri[20] = { 0,0, 1,-1, 2,-2, 3,-3, 4,-4, 5,-5, 6,-6, 7,-7, 8,-8, 9,-9};
      vsip_scalar_d datarb_ri[20] = { 0,0, 1,-1, 2,-2, 3,-3, 4,-4, 5,-5, 6,-6, 7,-7, 8,-8, 9,-9};
      vsip_cblock_d       *b_r_i = vsip_cblockbind_d(data_r,data_i,10,VSIP_MEM_NONE);
      vsip_cvview_d       *v_r_i = vsip_cvbind_d(b_r_i,0,1,10);
      vsip_cblock_d       *b_ri = vsip_cblockbind_d(data_ri,(vsip_scalar_d*)NULL,10,VSIP_MEM_NONE);
      vsip_cvview_d       *v_ri = vsip_cvbind_d(b_ri,0,1,10);
      vsip_cscalar_d chk_i= vsip_cmplx_d(0,0);
      vsip_cscalar_d chk_s= vsip_cmplx_d(0,0);
      int chk = 0;

      vsip_cblockadmit_d(b_r_i,VSIP_TRUE);
      vsip_cblockadmit_d(b_ri,VSIP_TRUE);
      vsip_rscvmul_d(2.0,v_r_i,v_r_i);
      vsip_rscvmul_d(2.0,v_ri,v_ri);
/* VU_cvprintm_d("2.0",v_r_i); VU_cvprintm_d("2.0",v_ri); */
      for(i=0; i<10; i++){
         chk_i = vsip_cvget_d(v_ri,(vsip_index)i); 
         chk_s = vsip_cvget_d(v_r_i,(vsip_index)i); 
         if( (chk_i.r != chk_s.r) || (chk_i.i != chk_s.i)) chk++;
      }
      printf("check admit\n");
      if(chk != 0) printf("error\n"); else printf("correct\n");
      fflush(stdout);
      chk = 0;

      vsip_cblockrelease_d(b_r_i,VSIP_TRUE,&ptr1s,&ptr2s);
      vsip_cblockrelease_d(b_ri,VSIP_TRUE,&ptr1,&ptr2);
      printf("check release\n");
      for(i=0; i< 10; i++){
         if((ptr1[2*i] != ptr1s[i]) || (ptr1[2*i+1] != ptr2s[i])) chk++;
/* printf("%2.0f, %2.0f; %2.0f, %2.0f\n",ptr1[2*i],ptr1[2*i+1], ptr1s[i],ptr2s[i]); */
      }
      if(chk != 0) printf("error\n"); else printf("correct\n");
      fflush(stdout);
      chk = 0;
   
      vsip_cblockrebind_d(b_ri,datarb_r,datarb_i,&ptr1,&ptr2);
      vsip_cblockrebind_d(b_r_i,datarb_ri,(vsip_scalar_d*)NULL,&ptr1s,&ptr2s);
      printf("check rebind\n");
      printf("check correct pointer returned\n");
      for(i=0; i< 10; i++){
         if((ptr1[2*i] != ptr1s[i]) || (ptr1[2*i+1] != ptr2s[i])) chk++;
      }
      if(chk != 0) printf("error\n"); else printf("correct\n");
      fflush(stdout);
      chk = 0;
     
      vsip_cblockadmit_d(b_r_i,VSIP_TRUE);
      vsip_cblockadmit_d(b_ri,VSIP_TRUE);
      vsip_rscvmul_d(2.0,v_r_i,v_r_i);
      vsip_rscvmul_d(2.0,v_ri,v_ri);
      for(i=0; i<10; i++){
         chk_i = vsip_cvget_d(v_ri,(vsip_index)i); 
         chk_s = vsip_cvget_d(v_r_i,(vsip_index)i); 
         if( (chk_i.r != chk_s.r) || (chk_i.i != chk_s.i)) chk++;
      }
      printf("check admit\n");
      if(chk != 0) printf("error\n"); else printf("correct\n");
      fflush(stdout);
      chk = 0;
      fflush(stdout);

      vsip_cblockrelease_d(b_ri,VSIP_TRUE,&ptr1s,&ptr2s);
      vsip_cblockrelease_d(b_r_i,VSIP_TRUE,&ptr1,&ptr2);
      printf("check release\n");
      for(i=0; i< 10; i++){
         if((ptr1[2*i] != ptr1s[i]) || (ptr1[2*i+1] != ptr2s[i])) chk++;
      }
      if(chk != 0) printf("error\n"); else printf("correct\n");
      fflush(stdout);

      vsip_cvalldestroy_d(v_r_i);
      vsip_cvalldestroy_d(v_ri);
   }
   return;
}
