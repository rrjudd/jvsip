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
/* $Id: cvrealimagview_f.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void cvrealimagview_f(void){
   printf("********\nTEST cvrealimagview_f\n");
   {
      vsip_scalar_f data_r[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_scalar_f data_i[10] = { 0, -1, -2, -3, -4, -5, -7, -8, -9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_cblock_f        *b = vsip_cblockcreate_f(100,VSIP_MEM_NONE);
      vsip_cvview_f        *v = vsip_cvbind_f(b,o,s,n);
      vsip_vview_f       *rv = vsip_vrealview_f(v);
      vsip_vview_f       *iv = vsip_vimagview_f(v);
      vsip_scalar_f chk = 0;
      vsip_cscalar_f a;
      int i;
      for(i=0; i< (int)n; i++){
           a.r = data_r[i]; a.i = data_i[i];
           vsip_cvput_f(v,i,a);
      }
     
      printf("test vrealview_f\n"); fflush(stdout);
      for(i=0; i< (int)n; i++){
          a.r = vsip_vget_f(rv,i);
          a.r -= data_r[i];
          chk +=  a.r * a.r;
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      printf("test vimagview_f\n"); fflush(stdout);
      chk = 0;
      for(i=0; i< (int)n; i++){
          a.i = vsip_vget_f(iv,i);
          a.i -= data_i[i];
          chk +=  a.i * a.i;
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_vdestroy_f(rv);
      vsip_vdestroy_f(iv);
      vsip_cvalldestroy_f(v);
   }
   return;
}
