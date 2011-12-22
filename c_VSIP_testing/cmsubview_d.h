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
/* $Id: cmsubview_d.h,v 2.0 2003/02/22 15:23:32 judd Exp $ */
static void cmsubview_d(void){
   printf("********\nTEST cmsubview_d\n");
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
      vsip_index           si = 2, sj = 1;
      vsip_length          sm = 5, sn = 3;
      vsip_cmview_d       *sv = vsip_cmsubview_d(v,si,sj,sm,sn);
      vsip_scalar_d chk = 0;
      int i,j;
      vsip_cscalar_d a;
      for(i=0; i< (int)m; i++){
         for(j=0; j< (int)n; j++){
            a.r = data_r[i][j]; a.i = data_i[i][j];
            vsip_cmput_d(v,i,j,a);
         }
      }
      for(i=0; i< (int)sm; i++){
         for(j=0; j< (int)sn; j++){
            a = vsip_cmget_d(sv,i,j);
            a.r -= data_r[si+i][sj+j]; a.i -= data_i[si+i][sj+j];
            chk += a.r * a.r +a.i * a.i;
         }
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_cmdestroy_d(sv);
      vsip_cmalldestroy_d(v);
   }
   return;
}
