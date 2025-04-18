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
/* $Id: cmrealimagview_d.h,v 2.0 2003/02/22 15:23:32 judd Exp $ */
static void cmrealimagview_d(void){
   printf("********\nTEST cmrealimagview_d double\n");
   {
      vsip_scalar_d data_r[10][4] ={{ 0,  1,  2,  3}, 
                                   { 10, 11, 12, 13},
                                   { 20, 21, 22, 23},
                                   { 30, 31, 32, 33},
                                   { 40, 41, 42, 43},
                                   { 50, 51, 52, 53},
                                   { 60, 61, 62, 63},
                                   { 70, 71, 72, 73},
                                   { 80, 81, 82, 83},
                                   { 90, 91, 92, 93}};
      vsip_scalar_d data_i[10][4] ={{ 0,  -1,  -2,  -3}, 
                                   {-10, -11, -12, -13},
                                   {-20, -21, -22, -23},
                                   {-30, -31, -32, -33},
                                   {-40, -41, -42, -43},
                                   {-50, -51, -52, -53},
                                   {-60, -61, -62, -63},
                                   {-70, -71, -72, -73},
                                   {-80, -81, -82, -83},
                                   {-90, -91, -92, -93}};
      vsip_offset           o = 4;
      vsip_stride          rs = 2, cs = 8;
      vsip_length           m = 10, n = 4;
      vsip_cblock_d         *b = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
      vsip_cmview_d        *v = vsip_cmbind_d(b,o,cs,m,rs,n);
      vsip_mview_d        *rv = vsip_mrealview_d(v);
      vsip_mview_d        *iv = vsip_mimagview_d(v);
      vsip_scalar_d chk = 0;
      int i,j;
      vsip_cscalar_d a;
      for(i=0; i< (int)m; i++){
         for(j=0; j< (int)n; j++){
            a.r = data_r[i][j]; a.i = data_i[i][j];
            vsip_cmput_d(v,i,j,a);
         }
      }
      printf("check mrealview_d \n"); fflush(stdout);
      for(i=0; i< (int)m; i++){
         for(j=0; j< (int)n; j++){
            a.r = vsip_mget_d(rv,i,j);
            a.r -= data_r[i][j]; 
            chk += a.r * a.r;
         }
      }
            
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      printf("check mimagview_d \n"); fflush(stdout);
      chk = 0;
      for(i=0; i< (int)m; i++){
         for(j=0; j< (int)n; j++){
            a.i = vsip_mget_d(iv,i,j);
            a.i -= data_i[i][j]; 
            chk += a.i * a.i;
         }
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_mdestroy_d(rv);
      vsip_mdestroy_d(iv);
      vsip_cmalldestroy_d(v);
   }
   return;
}
