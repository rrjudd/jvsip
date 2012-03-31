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
/* $Id: cvlog_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_f.include"
static void cvlog_f(void){
   printf("\n********\nTEST cvlog_f\n\n");
   {
      /* create some space */
      vsip_cscalar_f a0,a1,a2,a3,a4,a5;
      vsip_cvview_f *a = vsip_cvcreate_f(12,VSIP_MEM_NONE);
      vsip_cvview_f *ab = vsip_cvsubview_f(a,0,6);
      vsip_cvview_f *ac = vsip_cvsubview_f(a,1,6);
      vsip_cvview_f *ans = vsip_cvcreate_f(6,VSIP_MEM_NONE);
      vsip_cvview_f *chk = vsip_cvcreate_f(6,VSIP_MEM_NONE);
      vsip_vview_f  *chk_r = vsip_vimagview_f(chk);
      vsip_scalar_f data1[12];
      vsip_scalar_f data2[6];
      vsip_scalar_f data3[6];
      vsip_cvview_f *ua = vsip_cvbind_f(
              vsip_cblockbind_f(data1,(vsip_scalar_f*)NULL,6,VSIP_MEM_NONE),
              0,1,6); /* interleaved */
      vsip_cvview_f *ub = vsip_cvbind_f(
              vsip_cblockbind_f(data2,data3,6,VSIP_MEM_NONE),
              0,1,6); /* split */
      vsip_cblockadmit_f(vsip_cvgetblock_f(ua),VSIP_FALSE);
      vsip_cblockadmit_f(vsip_cvgetblock_f(ub),VSIP_FALSE);
      vsip_cvputstride_f(ab,2); vsip_cvputstride_f(ac,2);

      /* put some data in a */
      a0 = vsip_cmplx_f(0,1); a1 = vsip_cmplx_f(1, 0); a2 = vsip_cmplx_f(-1,VSIP_MEM_NONE);
      a3 = vsip_cmplx_f(1,1); a4 = vsip_cmplx_f(1,-1); a5 = vsip_cmplx_f(0,1);
      vsip_cvput_f(ab,0,a0); vsip_cvput_f(ab,1,a1); vsip_cvput_f(ab,2,a2);
      vsip_cvput_f(ab,3,a3); vsip_cvput_f(ab,4,a4); vsip_cvput_f(ab,5,a5);
      a0 = vsip_cmplx_f(0,1.5708); a1 = vsip_cmplx_f(0, 0); a2 = vsip_cmplx_f(0,3.1416);
      a3 = vsip_cmplx_f(.3466,.7854); a4 = vsip_cmplx_f(.3466,-.7854); a5 = vsip_cmplx_f(0.0,1.5708);
      vsip_cvput_f(ans,0,a0); vsip_cvput_f(ans,1,a1); vsip_cvput_f(ans,2,a2);
      vsip_cvput_f(ans,3,a3); vsip_cvput_f(ans,4,a4); vsip_cvput_f(ans,5,a5);
      printf("input vector ab\n"); 
      printf("ab from \"a\" stride 2 offset 0\n");VU_cvprintm_f("8.6",ab);
      vsip_cvlog_f(ab,ac);
      printf("ac from \"a\" stride 2 offset 1\n");
      printf("output of cvlog_f(ab,ac)\n"); VU_cvprintm_f("8.6",ac);
      printf("expected output to four decimal\n"); VU_cvprintm_f("8.4",ans);

      vsip_cvsub_f(ac,ans,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0002,.0002,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) > .5)
         printf(" cvlog_f in error\n");
      else {
         printf("cvlog_f correct to 4 decimal digits for\n");
         printf("input vsipl vector of stride 2, output vsipl vector of stride 2\n");
      }

      printf("\ntest cvlog for \"user data case\"\n");
      printf("with user interleaved data on input\n");
      printf("and user split data on output\n");
      vsip_cvcopy_f_f(ab,ua);
      vsip_cvlog_f(ua,ub);
      vsip_cvsub_f(ub,ans,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0002,.0002,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) > .5)
         printf("cvlog_f in error for user data case \n");
      else {
         printf("cvlog_f correct to 4 decimal digits for ");
         printf("user data case\n");
      
      vsip_cvdestroy_f(ab); vsip_cvdestroy_f(ac);vsip_cvalldestroy_f(a);
      vsip_cvalldestroy_f(ans);
      vsip_vdestroy_f(chk_r); vsip_cvalldestroy_f(chk);
      }
    }
    return;
}

