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
/* $Id: tcloneview_d.h,v 2.0 2003/02/22 15:23:35 judd Exp $ */
static void tcloneview_d(void){
   printf("********\nTEST tcloneview_d\n");
   {
      vsip_scalar_d data[4][5][4] = {{{  0,   1,   2,   3},{   10,  11,  12,  13},
                                      { 20,  21,  22,  23},{   30,  31,  32,  33},
                                      { 40,  41,  42, 43}},
                                     {{ 100, 101 ,102 ,103},{   110, 111 ,112 ,113},
                                      {120, 121 ,122 ,123},{   130, 131 ,132 ,133},
                                      {140, 141, 142, 143}},
                                     {{ 200, 201 ,202 ,203},{   210, 211 ,212 ,213},
                                      {220, 221 ,222 ,223},{   230, 231 ,232 ,233},
                                      {240, 241, 242, 243}},
                                     {{ 300, 301 ,302 ,303},{   310, 311 ,312 ,313},
                                      {320, 321 ,322 ,323},{   330, 331 ,332 ,333},
                                      {340, 341, 342, 343}}};
      vsip_offset           o = 7;
      vsip_stride          zs = 1, ys = 8, xs = 42;
      vsip_length          zl = 4, yl = 5, xl = 4;
      vsip_block_d         *b = vsip_blockcreate_d(200,VSIP_MEM_NONE);
      vsip_tview_d         *v = vsip_tbind_d(b,o,zs,zl,ys,yl,xs,xl);
      vsip_tview_d        *sv = vsip_tcloneview_d(v);
      vsip_scalar_d chk = 0;
      int i,j,k;
      for(i=0; i< (int)zl; i++)
         for(j=0; j< (int)yl; j++)
           for(k=0; k< (int)xl; k++)
             vsip_tput_d(v,i,j,k,data[i][j][k]);
      for(i=0; i< (int)zl; i++)
         for(j=0; j< (int)yl; j++)
            for(k=0; k< (int)xl; k++)
               chk += fabs(vsip_tget_d(sv,i,j,k) - data[i][j][k]);
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_tdestroy_d(sv);
      vsip_talldestroy_d(v);
   }
   return;
}
