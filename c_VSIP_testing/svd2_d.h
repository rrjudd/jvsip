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
/* $Id: svd2_d.h,v 1.5 2008/09/21 17:17:49 judd Exp $ */
static void svd2_d(void){
   printf("********\nTEST svd2 for double\n");
   {
      vsip_index i;
      vsip_length M=7, N=7;
      vsip_scalar_d data[49] = {1, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 1, 1,
      0, 0, 0, 0, 0, 0, 1};
      vsip_vview_d *s = vsip_vcreate_d(((M > N) ? N : M),VSIP_MEM_NONE);
      vsip_sv_d *svd = vsip_svd_create_d(M,N,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
      
      vsip_block_d *block = vsip_blockbind_d(data,(M * N),VSIP_MEM_NONE);
      vsip_mview_d *A0 = vsip_mbind_d(block,0,N,M,1,N);
      vsip_block_d *vblk = vsip_blockcreate_d(300,VSIP_MEM_NONE);
      vsip_mview_d *A = vsip_mbind_d(vblk,3,3 * N, M,2 , N);
      vsip_mview_d *U = vsip_mcreate_d(M,M,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *V = vsip_mcreate_d(N,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *B = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_blockadmit_d(block,VSIP_TRUE);
      vsip_mcopy_d_d(A0,A);
      printf("in = ");VU_mprintm_d("6.3",A);
      if(vsip_svd_d(svd,A,s)){
         printf("svd error\n");
         return;
      }
      /* create the singular value matrix */
      vsip_mfill_d(0.0,B);
      for(i=0; i<vsip_vgetlength_d(s); i++) vsip_mput_d(B,i,i,vsip_vget_d(s,i));
      vsip_svdmatu_d(svd, 0, M-1, U);
      vsip_svdmatv_d(svd, 0, N-1, V);
      printf("U = ");VU_mprintm_d("12.10",U);
      printf("B = ");VU_mprintm_d("12.10",B);
      printf("V = ");VU_mprintm_d("12.10",V);
      VU_vprintm_d("12.10",s);
      {  /* check that A0 = U * B * V' */
         vsip_scalar_mi mi;
         vsip_scalar_d chk = 1.0;
         vsip_scalar_d lim = 5 * DBL_EPSILON * fabs(vsip_mmaxmgval_d(A0,&mi));
         vsip_mview_d *dif=vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_d *out = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_d *Vt = vsip_mtransview_d(V);
         vsip_mprod_d(U,B,dif);
         vsip_mprod_d(dif,Vt,out);
         vsip_msub_d(out,A0,dif);
         vsip_mmag_d(dif, dif);
         chk = vsip_msumval_d(dif)/(2 * M * N);
         printf("%20.18e - %20.18e = %e\n",lim,chk, (lim - chk));
         if(chk > lim){
            printf("error\n");
         } else {
            printf("correct\n");
         }
         vsip_malldestroy_d(dif);
         vsip_malldestroy_d(out);
         vsip_mdestroy_d(Vt);
      }
      vsip_svd_destroy_d(svd);
      vsip_malldestroy_d(A0);
      vsip_malldestroy_d(A);
      vsip_valldestroy_d(s);
      vsip_malldestroy_d(U);
      vsip_malldestroy_d(B);
      vsip_malldestroy_d(V);
   }
   return;
}
