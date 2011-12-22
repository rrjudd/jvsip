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
/* $Id: vcloneview_uc.h,v 2.0 2003/02/22 15:23:35 judd Exp $ */
static void vcloneview_uc(void){
   printf("********\nTEST vcloneview_uc\n");
   {
      vsip_scalar_uc data[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_block_uc        *b = vsip_blockcreate_uc(100,VSIP_MEM_NONE);
      vsip_vview_uc        *v = vsip_vbind_uc(b,o,s,n);
      vsip_vview_uc       *sv = vsip_vcloneview_uc(v);
      vsip_scalar_uc chk = 0;
      int i;
      for(i=0; i< (int)n; i++)
           vsip_vput_uc(v,i,data[i]);
      for(i=0; i< (int)n; i++)
          chk += abs(vsip_vget_uc(sv,i) - data[i]);
      (chk != 0) ?    printf("error \n") :
                      printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_uc(sv);
      vsip_valldestroy_uc(v);
   }
   return;
}
