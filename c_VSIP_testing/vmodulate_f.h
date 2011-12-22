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
/* $Id: vmodulate_f.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
static void vmodulate_f(void){
   printf("********\nTEST vmodulate_f\n");
   {
      vsip_scalar_f nu = .5;
      vsip_scalar_f phi = M_PI * .25;
      vsip_scalar_f phi1 = 5 + M_PI * .25;
      vsip_scalar_f ans1_r[] ={1.0607, 0.4223,-0.3194,-0.9830,-1.4058,
                            -1.4845,-1.1997,-0.6212,0.1094,0.8132};
      vsip_scalar_f ans1_i[] ={ 1.0607, 1.4393, 1.4656, 1.1330, 0.5231,-0.2150,-0.9004, 
                                 -1.3653,-1.4960, -1.2604 };
                              
      
      vsip_scalar_f ans2_r[] ={1.318, 1.5, 1.3148, 0.8077, 0.1028,
                            -0.6272,-1.2037,-1.4855, -1.4035,-0.9780};
      vsip_scalar_f ans2_i[] ={-0.7162, 0.0033, 0.722, 1.264, 1.4965, 
                             1.3626, 0.895, 0.2084, -0.5293, -1.1374};
      vsip_cblock_f *ans1_block = vsip_cblockbind_f(ans1_r,ans1_i,10,VSIP_MEM_NONE);
      vsip_cblock_f *ans2_block = vsip_cblockbind_f(ans2_r,ans2_i,10,VSIP_MEM_NONE);
      vsip_cvview_f *ans1 = vsip_cvbind_f(ans1_block,0,1,10);
      vsip_cvview_f *ans2 = vsip_cvbind_f(ans2_block,0,1,10);
      vsip_vview_f *a  = vsip_vcreate_f(20,VSIP_MEM_NONE);
      vsip_vview_f *a1 = vsip_vsubview_f(a,0,10);
      vsip_vview_f *a2 = vsip_vsubview_f(a,10,10);
      vsip_cvview_f *r1 = vsip_cvcreate_f(10,VSIP_MEM_NONE);
      vsip_cvview_f *r2 = vsip_cvcreate_f(10,VSIP_MEM_NONE);
      vsip_cvview_f *chk = vsip_cvcreate_f(10,VSIP_MEM_NONE);
      vsip_vview_f *chk_r = vsip_vrealview_f(chk);

      vsip_cblockadmit_f(ans1_block,VSIP_TRUE);
      vsip_cblockadmit_f(ans2_block,VSIP_TRUE);
      vsip_vfill_f(1.5,a);
      printf("phi = vsip_vmodulate_f(a1,nu,phi,r1)\n");
      printf("a1 = ");VU_vprintm_f("8.6",a1);
      printf("nu = %4.2f\n",nu);
      printf("input phi = %6.4f\n",phi);
      phi = vsip_vmodulate_f(a1,nu,phi,r1);
      printf("output phi = %6.4f\n",phi);
      printf("expected output phi = %6.4f\n",phi1);
      if(fabs(phi - phi1) > .0001)
           printf("error\n");
      else
           printf("correct\n");
      printf("r1 = ");VU_cvprintm_f("8.6",r1);
      printf("expected r1 =");VU_cvprintm_f("8.6",ans1);
      vsip_cvsub_f(r1,ans1,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");


      printf("vsip_vmodulate_f(a2,nu,phi,r2)\n");
      vsip_vmodulate_f(a2,nu,phi,r2);
      printf("a2 = ");VU_vprintm_f("8.6",a2);
      printf("r2 = ");VU_cvprintm_f("8.6",r2);
      printf("expected r2 =");VU_cvprintm_f("8.6",ans2);
      vsip_cvsub_f(r2,ans2,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) > .5)
         printf("error\n");
      else
         printf("correct\n");
     
      vsip_vdestroy_f(chk_r);
      vsip_cvalldestroy_f(chk);
      vsip_cvalldestroy_f(ans1);vsip_cvalldestroy_f(ans2);
      vsip_vdestroy_f(a1);vsip_vdestroy_f(a2);
      vsip_valldestroy_f(a);
      vsip_cvalldestroy_f(r1);vsip_cvalldestroy_f(r2);

   }
   return;
}
