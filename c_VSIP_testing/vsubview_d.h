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
/* $Id: vsubview_d.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vsubview_d(void){
   printf("********\nTEST vsubview_d\n");
   {
      vsip_scalar_d data[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_block_d        *b = vsip_blockcreate_d(100,VSIP_MEM_NONE);
      vsip_vview_d        *v = vsip_vbind_d(b,o,s,n);
      vsip_index          si = 2;
      vsip_length         sn = 5;
      vsip_vview_d       *sv = vsip_vsubview_d(v,si,sn);
      vsip_scalar_d chk = 0;
      int i;
      for(i=0; i< (int)n; i++)
           vsip_vput_d(v,i,data[i]);
      for(i=0; i< (int)sn; i++)
          chk += fabs(vsip_vget_d(sv,i) - data[si+i]);
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_d(sv);
      vsip_valldestroy_d(v);
   }
   return;
}
