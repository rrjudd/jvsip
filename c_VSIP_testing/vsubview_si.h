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
/* $Id: vsubview_si.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vsubview_si(void){
   printf("********\nTEST vsubview_si\n");
   {
      vsip_scalar_si data[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_block_si        *b = vsip_blockcreate_si(100,VSIP_MEM_NONE);
      vsip_vview_si        *v = vsip_vbind_si(b,o,s,n);
      vsip_index          si = 2;
      vsip_length         sn = 5;
      vsip_vview_si       *sv = vsip_vsubview_si(v,si,sn);
      vsip_scalar_si      chk = 0;
      int i;
      for(i=0; i< (int)n; i++)
           vsip_vput_si(v,i,data[i]);
      for(i=0; i< (int)sn; i++)
          chk += abs(vsip_vget_si(sv,i) - data[si+i]);
      (chk != 0) ?    printf("error \n") :
                      printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_si(sv);
      vsip_valldestroy_si(v);
   }
   return;
}
