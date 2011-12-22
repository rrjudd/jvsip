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
/* $Id: cvcloneview_f.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void cvcloneview_f(void){
   printf("********\nTEST cvcloneview_f\n");
   {
      vsip_scalar_f data_r[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_scalar_f data_i[10] = { 0, 1, 2, 3, 4, 5, 7, 8, 9};
      vsip_offset          o = 40;
      vsip_stride          s = -3;
      vsip_length          n = 10;
      vsip_cblock_f        *b = vsip_cblockcreate_f(100,VSIP_MEM_NONE);
      vsip_cvview_f        *v = vsip_cvbind_f(b,o,s,n);
      vsip_cvview_f       *sv = vsip_cvcloneview_f(v);
      vsip_scalar_f chk = 0;
      int i;
      for(i=0; i< (int)n; i++){
           vsip_cscalar_f a;
           a.r = data_r[i]; a.i = data_i[i];
           vsip_cvput_f(v,i,a);
      }
      for(i=0; i< (int)n; i++){
          vsip_cscalar_f a = vsip_cvget_f(sv,i);
          a.r = a.r - data_r[i]; a.i = a.i - data_i[i];
          chk +=  a.r * a.r + a.i * a.i;
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_cvdestroy_f(sv);
      vsip_cvalldestroy_f(v);
   }
   return;
}
