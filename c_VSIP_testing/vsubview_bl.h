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
/* $Id: vsubview_bl.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vsubview_bl(void){
   printf("********\nTEST vsubview_bl\n");
   {
      vsip_scalar_bl data[10] = { 0, 1, 0, 0, 1, 0, 1, 1, 0};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_block_bl        *b = vsip_blockcreate_bl(100,VSIP_MEM_NONE);
      vsip_vview_bl        *v = vsip_vbind_bl(b,o,s,n);
      vsip_index          si = 2;
      vsip_length         sn = 5;
      vsip_vview_bl       *sv = vsip_vsubview_bl(v,si,sn);
      vsip_scalar_bl chk = VSIP_FALSE;
      int i;
      for(i=0; i< (int)n; i++)
           vsip_vput_bl(v,i,data[i]);
      for(i=0; i< (int)sn; i++){
          vsip_scalar_bl c = data[si+i];
          vsip_scalar_bl a = vsip_vget_bl(sv,i);
          if(c != VSIP_FALSE) c = VSIP_TRUE;
          if(a != VSIP_FALSE) a = VSIP_TRUE;
          if(a != c) chk = VSIP_TRUE; 
      } 
      (chk != VSIP_FALSE) ? printf("error \n") :
                            printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_bl(sv);
      vsip_valldestroy_bl(v);
   }
   return;
}
