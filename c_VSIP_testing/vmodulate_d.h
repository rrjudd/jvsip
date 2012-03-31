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
/* $Id: vmodulate_d.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
#include"VU_vprintm_d.include"
#include"VU_cvprintm_d.include"
static void vmodulate_d(void){
   printf("********\nTEST vmodulate_d\n");
   {
      vsip_scalar_d nu = .5;
      vsip_scalar_d phi = M_PI * .25;
      vsip_scalar_d phi1 = 5 + M_PI * .25;
      vsip_scalar_d ans1_r[] ={1.0607, 0.4223,-0.3194,-0.9830,-1.4058,
                            -1.4845,-1.1997,-0.6212,0.1094,0.8132};
      vsip_scalar_d ans1_i[] ={ 1.0607, 1.4393, 1.4656, 1.1330, 0.5231,-0.2150,-0.9004, 
                                 -1.3653,-1.4960, -1.2604 };
                              
      
      vsip_scalar_d ans2_r[] ={1.318, 1.5, 1.3148, 0.8077, 0.1028,
                            -0.6272,-1.2037,-1.4855, -1.4035,-0.9780};
      vsip_scalar_d ans2_i[] ={-0.7162, 0.0033, 0.722, 1.264, 1.4965, 
                             1.3626, 0.895, 0.2084, -0.5293, -1.1374};
      vsip_cblock_d *ans1_block = vsip_cblockbind_d(ans1_r,ans1_i,10,VSIP_MEM_NONE);
      vsip_cblock_d *ans2_block = vsip_cblockbind_d(ans2_r,ans2_i,10,VSIP_MEM_NONE);
      vsip_cvview_d *ans1 = vsip_cvbind_d(ans1_block,0,1,10);
      vsip_cvview_d *ans2 = vsip_cvbind_d(ans2_block,0,1,10);
      vsip_vview_d *a  = vsip_vcreate_d(20,VSIP_MEM_NONE);
      vsip_vview_d *a1 = vsip_vsubview_d(a,0,10);
      vsip_vview_d *a2 = vsip_vsubview_d(a,10,10);
      vsip_cvview_d *r1 = vsip_cvcreate_d(10,VSIP_MEM_NONE);
      vsip_cvview_d *r2 = vsip_cvcreate_d(10,VSIP_MEM_NONE);
      vsip_cvview_d *chk = vsip_cvcreate_d(10,VSIP_MEM_NONE);
      vsip_vview_d *chk_r = vsip_vrealview_d(chk);

      vsip_cblockadmit_d(ans1_block,VSIP_TRUE);
      vsip_cblockadmit_d(ans2_block,VSIP_TRUE);
      vsip_vfill_d(1.5,a);
      printf("phi = vsip_vmodulate_d(a1,nu,phi,r1)\n");
      printf("a1 = ");VU_vprintm_d("8.6",a1);
      printf("nu = %4.2f\n",nu);
      printf("input phi = %6.4f\n",phi);
      phi = vsip_vmodulate_d(a1,nu,phi,r1);
      printf("output phi = %6.4f\n",phi);
      printf("expected output phi = %6.4f\n",phi1);
      if(fabs(phi - phi1) > .0001)
           printf("error\n");
      else
           printf("correct\n");
      printf("r1 = ");VU_cvprintm_d("8.6",r1);
      printf("expected r1 =");VU_cvprintm_d("8.6",ans1);
      vsip_cvsub_d(r1,ans1,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");


      printf("vsip_vmodulate_d(a2,nu,phi,r2)\n");
      vsip_vmodulate_d(a2,nu,phi,r2);
      printf("a2 = ");VU_vprintm_d("8.6",a2);
      printf("r2 = ");VU_cvprintm_d("8.6",r2);
      printf("expected r2 =");VU_cvprintm_d("8.6",ans2);
      vsip_cvsub_d(r2,ans2,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");
     
      vsip_vdestroy_d(chk_r);
      vsip_cvalldestroy_d(chk);
      vsip_cvalldestroy_d(ans1);vsip_cvalldestroy_d(ans2);
      vsip_vdestroy_d(a1);vsip_vdestroy_d(a2);
      vsip_valldestroy_d(a);
      vsip_cvalldestroy_d(r1);vsip_cvalldestroy_d(r2);

   }
   return;
}
