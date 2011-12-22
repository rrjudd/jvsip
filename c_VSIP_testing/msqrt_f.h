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
/* $Id: msqrt_f.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void msqrt_f(void){
   printf("\n*********\nTEST msqrt_f\n");
   {
     vsip_mview_f *M = vsip_mcreate_f(4,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *m1 = vsip_msubview_f(M,0,0,2,3);
     vsip_mview_f *m2 = vsip_msubview_f(M,2,0,2,3);
     vsip_mview_f *chk = vsip_mcreate_f(2,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_scalar_f data[6];
     vsip_block_f *block = vsip_blockbind_f(data,6,VSIP_MEM_NONE);
     vsip_mview_f *ans = vsip_mbind_f(block,0,1,2,2,3);
     vsip_vview_f *vans = vsip_vbind_f(block,0,1,6);
     vsip_blockadmit_f(block,VSIP_FALSE);
     vsip_vramp_f(1,.5,vans);
     vsip_mcopy_f_f(ans,m1);
     vsip_blockrelease_f(block,VSIP_TRUE);
     data[0] = sqrt(data[0]); data[1] = sqrt(data[1]);
     data[2] = sqrt(data[2]); data[3] = sqrt(data[3]);
     data[4] = sqrt(data[4]); data[5] = sqrt(data[5]);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_msqrt_f(m1,m2);
     printf("msqrt_f(a,b)");
     printf("matrix a\n"); VU_mprintm_f("8.6",m1);
     printf("matrix b\n"); VU_mprintm_f("8.6",m2);
     printf("right answer\n"); VU_mprintm_f("8.4",ans);
     vsip_msub_f(m2,ans,chk); vsip_mclip_f(chk,0.0001,0.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
          printf("error\n");
     else
          printf("correct\n");
 
     printf("in place\n");
     vsip_msqrt_f(m1,m1);
     vsip_msub_f(m1,ans,chk); vsip_mclip_f(chk,0.0001,0.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
          printf("error\n");
     else
          printf("correct\n");
 
     vsip_mdestroy_f(ans); vsip_valldestroy_f(vans);
     vsip_mdestroy_f(m2); vsip_mdestroy_f(m1); vsip_malldestroy_f(M);
     vsip_malldestroy_f(chk);
   }
}
