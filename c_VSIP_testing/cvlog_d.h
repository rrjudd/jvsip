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
/* $Id: cvlog_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_d.include"
static void cvlog_d(void){
   printf("\n********\nTEST cvlog_d\n\n");
   {
      /* create some space */
      vsip_cscalar_d a0,a1,a2,a3,a4,a5;
      vsip_cvview_d *a = vsip_cvcreate_d(12,VSIP_MEM_NONE);
      vsip_cvview_d *ab = vsip_cvsubview_d(a,0,6);
      vsip_cvview_d *ac = vsip_cvsubview_d(a,1,6);
      vsip_cvview_d *ans = vsip_cvcreate_d(6,VSIP_MEM_NONE);
      vsip_cvview_d *chk = vsip_cvcreate_d(6,VSIP_MEM_NONE);
      vsip_vview_d  *chk_r = vsip_vimagview_d(chk);
      vsip_scalar_d data1[12];
      vsip_scalar_d data2[6];
      vsip_scalar_d data3[6];
      vsip_cvview_d *ua = vsip_cvbind_d(
              vsip_cblockbind_d(data1,(vsip_scalar_d*)NULL,6,VSIP_MEM_NONE),
              0,1,6); /* interleaved */
      vsip_cvview_d *ub = vsip_cvbind_d(
              vsip_cblockbind_d(data2,data3,6,VSIP_MEM_NONE),
              0,1,6); /* split */
      vsip_cblockadmit_d(vsip_cvgetblock_d(ua),VSIP_FALSE);
      vsip_cblockadmit_d(vsip_cvgetblock_d(ub),VSIP_FALSE);
      vsip_cvputstride_d(ab,2); vsip_cvputstride_d(ac,2);

      /* put some data in a */
      a0 = vsip_cmplx_d(0,1); a1 = vsip_cmplx_d(1, 0); a2 = vsip_cmplx_d(-1,VSIP_MEM_NONE);
      a3 = vsip_cmplx_d(1,1); a4 = vsip_cmplx_d(1,-1); a5 = vsip_cmplx_d(0,1);
      vsip_cvput_d(ab,0,a0); vsip_cvput_d(ab,1,a1); vsip_cvput_d(ab,2,a2);
      vsip_cvput_d(ab,3,a3); vsip_cvput_d(ab,4,a4); vsip_cvput_d(ab,5,a5);
      a0 = vsip_cmplx_d(0,1.5708); a1 = vsip_cmplx_d(0, 0); a2 = vsip_cmplx_d(0,3.1416);
      a3 = vsip_cmplx_d(.3466,.7854); a4 = vsip_cmplx_d(.3466,-.7854); a5 = vsip_cmplx_d(0.0,1.5708);
      vsip_cvput_d(ans,0,a0); vsip_cvput_d(ans,1,a1); vsip_cvput_d(ans,2,a2);
      vsip_cvput_d(ans,3,a3); vsip_cvput_d(ans,4,a4); vsip_cvput_d(ans,5,a5);
      printf("input vector ab\n"); 
      printf("ab from \"a\" stride 2 offset 0\n");VU_cvprintm_d("8.6",ab);
      vsip_cvlog_d(ab,ac);
      printf("ac from \"a\" stride 2 offset 1\n");
      printf("output of cvlog_d(ab,ac)\n"); VU_cvprintm_d("8.6",ac);
      printf("expected output to four decimal\n"); VU_cvprintm_d("8.4",ans);

      vsip_cvsub_d(ac,ans,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0002,.0002,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) > .5)
         printf(" cvlog_d in error\n");
      else {
         printf("cvlog_d correct to 4 decimal digits for\n");
         printf("input vsipl vector of stride 2, output vsipl vector of stride 2\n");
      }

      printf("\ntest cvlog for \"user data case\"\n");
      printf("with user interleaved data on input\n");
      printf("and user split data on output\n");
      vsip_cvcopy_d_d(ab,ua);
      vsip_cvlog_d(ua,ub);
      vsip_cvsub_d(ub,ans,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0002,.0002,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) > .5)
         printf("cvlog_d in error for user data case \n");
      else {
         printf("cvlog_d correct to 4 decimal digits for ");
         printf("user data case\n");
      
      vsip_cvdestroy_d(ab); vsip_cvdestroy_d(ac);vsip_cvalldestroy_d(a);
      vsip_cvalldestroy_d(ans);
      vsip_vdestroy_d(chk_r); vsip_cvalldestroy_d(chk);
      }
    }
    return;
}

