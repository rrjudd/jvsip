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
/* $Id: cvrealimagview_d.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void cvrealimagview_d(void){
   printf("********\nTEST cvrealimagview_d\n");
   {
      vsip_scalar_d data_r[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_scalar_d data_i[10] = { 0, -1, -2, -3, -4, -5, -7, -8, -9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_cblock_d        *b = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
      vsip_cvview_d        *v = vsip_cvbind_d(b,o,s,n);
      vsip_vview_d       *rv = vsip_vrealview_d(v);
      vsip_vview_d       *iv = vsip_vimagview_d(v);
      vsip_scalar_d chk = 0;
      vsip_cscalar_d a;
      int i;
      for(i=0; i< (int)n; i++){
           a.r = data_r[i]; a.i = data_i[i];
           vsip_cvput_d(v,i,a);
      }
     
      printf("test vrealview_d\n"); fflush(stdout);
      for(i=0; i< (int)n; i++){
          a.r = vsip_vget_d(rv,i);
          a.r -= data_r[i];
          chk +=  a.r * a.r;
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      printf("test vimagview_d\n"); fflush(stdout);
      chk = 0;
      for(i=0; i< (int)n; i++){
          a.i = vsip_vget_d(iv,i);
          a.i -= data_i[i];
          chk +=  a.i * a.i;
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_d(rv);
      vsip_vdestroy_d(iv);
      vsip_cvalldestroy_d(v);
   }
   return;
}
