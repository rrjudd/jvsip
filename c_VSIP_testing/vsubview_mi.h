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
/* $Id: vsubview_mi.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vsubview_mi(void){
   printf("********\nTEST vsubview_mi\n");
   {
      vsip_scalar_vi data_r[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
      vsip_scalar_vi data_c[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_block_mi        *b = vsip_blockcreate_mi(100,VSIP_MEM_NONE);
      vsip_vview_mi        *v = vsip_vbind_mi(b,o,s,n);
      vsip_index          si = 2;
      vsip_length         sn = 5;
      vsip_vview_mi       *sv = vsip_vsubview_mi(v,si,sn);
      int chk = 0;
      int i;
      for(i=0; i< (int)n; i++){
           vsip_scalar_mi a;
           a.r = data_r[i]; a.c = data_c[i];
           vsip_vput_mi(v,i,a);
      }
      for(i=0; i< (int)sn; i++){
           vsip_scalar_mi a = vsip_vget_mi(sv,i);
           int a_r = (int)(a.r - data_r[si+i]);
           int a_c = (int)(a.c - data_c[si+i]);
           chk += a_r * a_r + a_c * a_c;
      }
      (chk != 0) ?    printf("error \n") :
                      printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_mi(sv);
      vsip_valldestroy_mi(v);
   }
   return;
}
