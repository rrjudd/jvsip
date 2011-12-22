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
/* $Id: ctget_put_f.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void ctget_put_f(void){
   printf("********\nTEST ctget_put_f\n");
   {
     vsip_scalar_f datar_a[]   = { 0,  1,  1, 0,   1, 0,  2, 1, -1, -2, 0 ,1};
     vsip_scalar_f datai_a[]   = { 1, -1, -1, 1,  -1, 1, -2, 0,  1,  2, 1,-1};
                                 
     vsip_scalar_f ansr[2][3][2]  = {{{ 0,  1},{  1, 0},{   1, 0}},{{  2, 1},{ -1, -2},{ 0 ,1}}};
     vsip_scalar_f ansi[2][3][2]  = {{{ 1, -1},{ -1, 1},{  -1, 1}},{{ -2, 0},{  1,  2},{ 1,-1}}};
     vsip_cblock_f *block_a    = vsip_cblockbind_f(datar_a,datai_a,12,VSIP_MEM_NONE);
     vsip_ctview_f *a          = vsip_ctbind_f(block_a,0,6,2,2,3,1,2);

     vsip_cblock_f *block_b    = vsip_cblockcreate_f(50,VSIP_MEM_NONE);
     vsip_ctview_f *b          = vsip_ctbind_f(block_b,45,-1,2,-3,3,-10,2);
     vsip_index h,i,j;

     vsip_cblockadmit_f(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(h=0; h<2; h++)
      for(j=0; j<2; j++)
        for(i=0; i<3; i++)
           vsip_ctput_f(b,h,i,j,vsip_ctget_f(a,h,i,j));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(h=0; h<2; h++)
      for(j=0; j<2; j++)
        for(i=0; i<3; i++){
           vsip_cscalar_f chk = vsip_ctget_f(a,h,i,j);
           chk.r = chk.r - ansr[h][i][j]; chk.i = chk.i - ansi[h][i][j];
           chk.r = chk.r * chk.r + chk.i * chk.i;
           (chk.r < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     printf("check general stride view\n");
     for(h=0; h<2; h++)
       for(j=0; j<2; j++)
         for(i=0; i<3; i++){
           vsip_cscalar_f chk = vsip_ctget_f(b,h,i,j);
           chk.r = chk.r - ansr[h][i][j]; chk.i = chk.i - ansi[h][i][j];
           chk.r = chk.r * chk.r + chk.i * chk.i;
           (chk.r < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     vsip_ctalldestroy_f(a);
     vsip_ctalldestroy_f(b);
   }
   return;
}
