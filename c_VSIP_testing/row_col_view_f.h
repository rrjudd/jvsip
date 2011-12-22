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
/* $Id: row_col_view_f.h,v 2.0 2003/02/22 15:23:35 judd Exp $ */
static void row_col_view_f(void){
   printf("********\nTEST row_col_view_f\n");
   {
      vsip_scalar_f data[10][4] = {{0,   1,  2,  3}, 
                                   {10, 11, 12, 13},
                                   {20, 21, 22, 23},
                                   {30, 31, 32, 33},
                                   {40, 41, 42, 43},
                                   {50, 51, 52, 53},
                                   {60, 61, 62, 63},
                                   {70, 71, 72, 73},
                                   {80, 81, 82, 83},
                                   {90, 91, 92, 93}};
      vsip_offset           o = 5;
      vsip_stride          rs = 3, cs = 8;
      vsip_length           m = 10, n = 4;
      vsip_block_f         *b = vsip_blockcreate_f(100,VSIP_MEM_NONE);
      vsip_mview_f         *v = vsip_mbind_f(b,o,cs,m,rs,n);
      vsip_vview_f         *sv;
      vsip_scalar_f chk = 0;
      int i,j;
      for(i=0; i< (int)m; i++)
         for(j=0; j< (int)n; j++)
            vsip_mput_f(v,i,j,data[i][j]);

      printf("test mrowview_f\n"); fflush(stdout);
      for(i=0; i< (int)m; i++){
         sv = vsip_mrowview_f(v,i);
         for(j=0; j< (int)n; j++){
            chk += fabs(vsip_vget_f(sv,j) - data[i][j]);
         }
         vsip_vdestroy_f(sv);
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");

      printf("test mcolview_f\n"); fflush(stdout);
      chk = 0;
      for(j=0; j< (int)n; j++){
         sv = vsip_mcolview_f(v,j);
         for(i=0; i< (int)m; i++){
            chk += fabs(vsip_vget_f(sv,i) - data[i][j]);
         }
         vsip_vdestroy_f(sv);
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");

      fflush(stdout);
      vsip_malldestroy_f(v);
   }
   return;
}
