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
/* $Id: sort_f.h,v 1.1 2008/09/19 21:01:49 judd Exp $ */

static void sort_f(void){
   printf("********\nTEST sort for float\n");
   {
      vsip_scalar_f dta[30] = { -1, 2, 0,-3, 6, 8, 5, 4,-2, 1, 2, 3, 4, \
      5, 6, 7, 8, 9,10,11, -1,-2,-3,-4,-5, -0,-4,-5,-3,-2}; 
      vsip_scalar_f ans_dta[30] = {-5, -5, -4, -4, -3, -3, -3, -2, -2, -2,\
      -1, -1, -0, 0, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 10, 11};
      vsip_vview_f *s = vsip_vcreate_f(30,VSIP_MEM_NONE);
      vsip_vview_f *sinv = vsip_vcreate_f(30,VSIP_MEM_NONE);
      vsip_vview_f *ans_s = vsip_vcreate_f(30,VSIP_MEM_NONE);
      vsip_vview_vi *vi = vsip_vcreate_vi(30,VSIP_MEM_NONE);
      vsip_vview_bl *chk = vsip_vcreate_bl(30,VSIP_MEM_NONE);
      
      vsip_vcopyfrom_user_f(dta,s);
      vsip_vcopyfrom_user_f(ans_dta,ans_s);
      printf("sort by value; sort ascending\n");
      vsip_vsortip_f(s, VSIP_SORT_BYVALUE, VSIP_SORT_ASCENDING,VSIP_TRUE, vi);
      vsip_vleq_f(s,ans_s,chk);
      if(vsip_valltrue_bl(chk)) printf("correct\n"); else printf("error\n"); 
      vsip_vcopyfrom_user_f(dta,s);
      vsip_vgather_f(s,vi,sinv);
      vsip_vleq_f(sinv,ans_s,chk);
      if(vsip_valltrue_bl(chk)) printf("correct\n"); else printf("error\n");         
      vsip_valldestroy_vi(vi);
      vsip_valldestroy_f(s);
      vsip_valldestroy_f(sinv);
      vsip_valldestroy_f(ans_s);
   }
   return;
}
