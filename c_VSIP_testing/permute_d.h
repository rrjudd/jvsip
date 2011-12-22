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
/* $Id: permute_d.h,v 1.1 2008/09/20 22:34:50 judd Exp $ */

static void permute_d(void){
   printf("********\nTEST permute for double\n");
   {
      int i,j;
      vsip_vview_vi *v_ind = vsip_vcreate_vi(10,VSIP_MEM_NONE);
      vsip_scalar_vi vi[10]={4, 3, 2, 1, 6, 5, 0, 7, 8, 9}; /* pemute data for p */
      vsip_mview_d *indta = vsip_mcreate_d(10,10,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *outdta = vsip_mcreate_d(10,10,VSIP_COL,VSIP_MEM_NONE);
      vsip_permute* perm;
      vsip_scalar_d ansdta_byrow[100]={\
		4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, \
		3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, \
		2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, \
		1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, \
		6.0, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9, \
		5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, \
		0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, \
		7.0, 7.1, 7.2, 7.3, 7.4, 7.5, 7.6, 7.7, 7.8, 7.9, \
		8.0, 8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9, \
		9.0, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9};
      vsip_scalar_d ansdta_bycol[100]={\
		0.4, 0.3, 0.2, 0.1, 0.6, 0.5, 0.0, 0.7, 0.8, 0.9, \
		1.4, 1.3, 1.2, 1.1, 1.6, 1.5, 1.0, 1.7, 1.8, 1.9, \
		2.4, 2.3, 2.2, 2.1, 2.6, 2.5, 2.0, 2.7, 2.8, 2.9, \
		3.4, 3.3, 3.2, 3.1, 3.6, 3.5, 3.0, 3.7, 3.8, 3.9, \
		4.4, 4.3, 4.2, 4.1, 4.6, 4.5, 4.0, 4.7, 4.8, 4.9, \
		5.4, 5.3, 5.2, 5.1, 5.6, 5.5, 5.0, 5.7, 5.8, 5.9, \
		6.4, 6.3, 6.2, 6.1, 6.6, 6.5, 6.0, 6.7, 6.8, 6.9, \
		7.4, 7.3, 7.2, 7.1, 7.6, 7.5, 7.0, 7.7, 7.8, 7.9, \
		8.4, 8.3, 8.2, 8.1, 8.6, 8.5, 8.0, 8.7, 8.8, 8.9, \
		9.4, 9.3, 9.2, 9.1, 9.6, 9.5, 9.0, 9.7, 9.8, 9.9};
      vsip_mview_d *ans_byrow = vsip_mcreate_d(10,10,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *ans_bycol = vsip_mcreate_d(10,10,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *chk = vsip_mcreate_d(10,10,VSIP_ROW,VSIP_MEM_NONE);
      
      vsip_mcopyfrom_user_d(ansdta_byrow,VSIP_ROW, ans_byrow);
      vsip_mcopyfrom_user_d(ansdta_bycol,VSIP_ROW, ans_bycol);
		/* Example of by row */
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            vsip_mput_d(indta,i,j,(float)j/10.0 + (float)i ); /* create some data to permute */
         }
      }
      vsip_vcopyfrom_user_vi(vi,v_ind);
      perm = vsip_mpermute_create_d(10,10,VSIP_ROW); /* create the permutation object */
      vsip_permute_init(perm,v_ind);        /* initialze the object with p */
      vsip_mpermute_d(indta, perm, outdta); /* permute out of place */
      printf("permute vector p\n");
      for(i=0; i<10; i++){
         printf("%2d,",(int)vi[i]);
      }
      printf("\ninput\n");
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            printf("%3.1f, ",vsip_mget_d(indta,i,j));
         }
         printf("\n");
      }
      printf("\noutput (by row out-of-place)\n");
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            printf("%3.1f, ",vsip_mget_d(outdta,i,j));
         }
         printf("\n");
      }  
      vsip_msub_d(outdta,ans_byrow,chk);
      vsip_mmag_d(chk,chk);
      if(vsip_msumval_d(chk) == 0) printf("correct\n"); else printf("error\n");
      printf("\noutput (by row in-place)\n");
      vsip_mpermute_d(indta, perm, indta);
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            printf("%3.1f, ",vsip_mget_d(indta,i,j));
         }
         printf("\n");
      } 
      vsip_msub_d(indta,ans_byrow,chk);
      vsip_mmag_d(chk,chk);
      if(vsip_msumval_d(chk) == 0) printf("correct\n"); else printf("error\n");
      
      /* re-init input matrix and destroy and create new perm object */
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            vsip_mput_d(indta,i,j,(float)j/10.0 + (float)i ); /* create some data to permute */
         }
      }
      vsip_permute_destroy(perm); /* destroy old permutation object */
      perm = vsip_mpermute_create_d(10,10,VSIP_COL); /* create new permutation object */
      vsip_permute_init(perm,v_ind);        /* initialze the object with p */
      vsip_mpermute_d(indta, perm, outdta); /* permute out of place */
        printf("\noutput (by column out-of-place)\n");
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            printf("%3.1f, ",vsip_mget_d(outdta,i,j));
         }
         printf("\n");
      }  
      vsip_msub_d(outdta,ans_bycol,chk);
      vsip_mmag_d(chk,chk);
      if(vsip_msumval_d(chk) == 0) printf("correct\n"); else printf("error\n");
      
      printf("\noutput (by column in-place)\n");
      vsip_mpermute_d(indta, perm, indta);
      for(i=0; i<10; i++){
         for(j=0; j<10; j++){
            printf("%3.1f, ",vsip_mget_d(indta,i,j));
         }
         printf("\n");
      } 
      vsip_msub_d(indta,ans_bycol,chk);
      vsip_mmag_d(chk,chk);
      if(vsip_msumval_d(chk) == 0) printf("correct\n"); else printf("error\n");
   
      vsip_permute_destroy(perm);
      vsip_valldestroy_vi(v_ind);
      vsip_malldestroy_d(indta);
      vsip_malldestroy_d(outdta);
      vsip_malldestroy_d(ans_bycol);
      vsip_malldestroy_d(ans_byrow);
   }
   return;
}
