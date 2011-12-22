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
/* $Id: ctrealimagview_f.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void ctrealimagview_f(void){
   printf("********\nTEST ctrealimagview_f\n");
   {
      vsip_scalar_f data_r[4][5][4] = 
          {{ { 0,   1,   2,   3},  {10,  11,  12,  13},
          {   20,  21,  22,  23},  {30,  31,  32,  33},
          {   40,  41,  42,  43}}, 
          {{ 100, 101 ,102 ,103},  {110, 111 ,112 ,113},
          {  120, 121 ,122 ,123},  {130, 131 ,132 ,133},
          {  140, 141, 142, 143}}, 
          {{ 200, 201 ,202 ,203},  {210, 211 ,212 ,213},
          {  220, 221 ,222 ,223},  {230, 231 ,232 ,233},
          {  240, 241, 242, 243}}, 
          {{ 300, 301 ,302 ,303},  {310, 311 ,312 ,313},
          {  320, 321 ,322 ,323},  {330, 331 ,332 ,333},
          {  340, 341, 342, 343}}};
      vsip_scalar_f data_i[4][5][4] = 
           {{{ 0,   -1,   -2,   -3},  { -10,  -11,  -12,  -13},
           { -20,  -21,  -22,  -23},  { -30,  -31,  -32,  -33},
           { -40,  -41,  -42,  -43}}, 
          {{-100, -101, -102, -103},  {-110, -111, -112, -113},
          { -120, -121, -122, -123},  {-130, -131, -132, -133},
          { -140,  141, -142, -143}}, 
          {{-200, -201, -202, -203},  {-210, -211, -212, -213},
          { -220, -221, -222, -223},  {-230, -231, -232, -233},
          { -240, -241, -242, -243}}, 
          {{-300, -301, -302, -303},  {-310, -311, -312, -313},
           {-320, -321, -322, -323},  {-330, -331, -332, -333},
            {-340, -341, -342, -343}}};
      vsip_offset           o = 7;
      vsip_stride          zs = 1, ys = 8, xs = 42;
      vsip_length          zl = 4, yl = 5, xl = 4;
      vsip_cblock_f         *b = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_ctview_f         *v = vsip_ctbind_f(b,o,zs,zl,ys,yl,xs,xl);
      vsip_tview_f        *rv = vsip_trealview_f(v);
      vsip_tview_f        *iv = vsip_timagview_f(v);
      vsip_scalar_f chk = 0;
      vsip_cscalar_f a;
      int i,j,k;
      for(i=0; i< (int)zl; i++){
         for(j=0; j< (int)yl; j++){
           for(k=0; k< (int)xl; k++){
              a.r = data_r[i][j][k]; a.i = data_i[i][j][k]; 
              vsip_ctput_f(v,i,j,k,a);
           }
         }
      }

      printf("check trealview_f\n"); fflush(stdout);
      for(i=0; i< (int)zl; i++){
         for(j=0; j< (int)yl; j++){
            for(k=0; k< (int)xl; k++){
               a.r = vsip_tget_f(rv,i,j,k);
               a.r -= data_r[i][j][k];
               chk +=  a.r * a.r;
           }
         }
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");

      printf("check timagview_f\n"); fflush(stdout);
      chk = 0;
      for(i=0; i< (int)zl; i++){
         for(j=0; j< (int)yl; j++){
            for(k=0; k< (int)xl; k++){
               a.i = vsip_tget_f(iv,i,j,k);
               a.i -= data_i[i][j][k];
               chk +=  a.i * a.i;
           }
         }
      }
      (chk > .0001) ?    printf("error \n") :
                         printf("correct \n");
      fflush(stdout);
      vsip_tdestroy_f(rv);
      vsip_tdestroy_f(iv);
      vsip_ctalldestroy_f(v);
   }
   return;
}
