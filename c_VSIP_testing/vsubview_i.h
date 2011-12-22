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
/* $Id: vsubview_i.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vsubview_i(void){
   printf("********\nTEST vsubview_i\n");
   {
      vsip_scalar_i data[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_block_i        *b = vsip_blockcreate_i(100,VSIP_MEM_NONE);
      vsip_vview_i        *v = vsip_vbind_i(b,o,s,n);
      vsip_index          si = 2;
      vsip_length         sn = 5;
      vsip_vview_i       *sv = vsip_vsubview_i(v,si,sn);
      vsip_scalar_i chk = 0;
      int i;
      for(i=0; i< (int)n; i++)
           vsip_vput_i(v,i,data[i]);
      for(i=0; i< (int)sn; i++)
          chk += abs(vsip_vget_i(sv,i) - data[si+i]);
      (chk != 0) ?    printf("error \n") :
                      printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_i(sv);
      vsip_valldestroy_i(v);
   }
   return;
}
