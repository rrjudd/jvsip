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
/* $Id: mrsqrt_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void mrsqrt_d(void){
   printf("\n*********\nTEST mrsqrt_d\n");
   {
     vsip_mview_d *M = vsip_mcreate_d(4,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *m1 = vsip_msubview_d(M,0,0,2,3);
     vsip_mview_d *m2 = vsip_msubview_d(M,2,0,2,3);
     vsip_mview_d *chk = vsip_mcreate_d(2,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_scalar_d data[6];
     vsip_block_d *block = vsip_blockbind_d(data,6,VSIP_MEM_NONE);
     vsip_mview_d *ans = vsip_mbind_d(block,0,1,2,2,3);
     vsip_vview_d *vans = vsip_vbind_d(block,0,1,6);
     vsip_blockadmit_d(block,VSIP_FALSE);
     vsip_vramp_d(1,.5,vans);
     vsip_mcopy_d_d(ans,m1);
     vsip_blockrelease_d(block,VSIP_TRUE);
     data[0] = (vsip_scalar_d)1.0/sqrt(data[0]); data[1] = (vsip_scalar_d)1.0/sqrt(data[1]);
     data[2] = (vsip_scalar_d)1.0/sqrt(data[2]); data[3] = (vsip_scalar_d)1.0/sqrt(data[3]);
     data[4] = (vsip_scalar_d)1.0/sqrt(data[4]); data[5] = (vsip_scalar_d)1.0/sqrt(data[5]);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_mrsqrt_d(m1,m2);
     printf("mrsqrt_d(a,b)");
     printf("matrix a\n"); VU_mprintm_d("8.6",m1);
     printf("matrix b\n"); VU_mprintm_d("8.6",m2);
     printf("right answer\n"); VU_mprintm_d("8.4",ans);
     vsip_msub_d(m2,ans,chk); vsip_mclip_d(chk,0.0001,0.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
          printf("error\n");
     else
          printf("correct\n");
 
     printf("in place\n");
     vsip_mrsqrt_d(m1,m1);
     vsip_msub_d(m1,ans,chk); vsip_mclip_d(chk,0.0001,0.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
          printf("error\n");
     else
          printf("correct\n");
 
     vsip_mdestroy_d(ans); vsip_valldestroy_d(vans);
     vsip_mdestroy_d(m2); vsip_mdestroy_d(m1); vsip_malldestroy_d(M);
     vsip_malldestroy_d(chk);
   }
}
