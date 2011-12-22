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
/* $Id: cmget_put_f.h,v 2.0 2003/02/22 15:23:32 judd Exp $ */
static void cmget_put_f(void){
   printf("********\nTEST cmget_put_f\n");
   {
     vsip_scalar_f datar_a[]   = { 0,  1,  1, 0,   1, 0};
     vsip_scalar_f datai_a[]   = { 1, -1, -1, 1,  -1, 1};
                                 
     vsip_scalar_f ansr[2][3]      = {{ 0,  1,  1},{ 0,  1, 0}};
     vsip_scalar_f ansi[2][3]      = {{ 1, -1, -1},{ 1, -1, 1}};
     vsip_cblock_f *block_a    = vsip_cblockbind_f(datar_a,datai_a,6,VSIP_MEM_NONE);
     vsip_cmview_f *a          = vsip_cmbind_f(block_a,0,3,2,1,3);

     vsip_cblock_f *block_b    = vsip_cblockcreate_f(50,VSIP_MEM_NONE);
     vsip_cmview_f *b          = vsip_cmbind_f(block_b, 35,-8,2,-2,3);
     vsip_index i,j;

     vsip_cblockadmit_f(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(j=0; j<3; j++)
        for(i=0; i<2; i++)
           vsip_cmput_f(b,i,j,vsip_cmget_f(a,i,j));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(j=0; j<3; j++)
        for(i=0; i<2; i++){
           vsip_cscalar_f chk = vsip_cmget_f(a,i,j);
           chk.r = chk.r - ansr[i][j]; chk.i = chk.i - ansi[i][j];
           chk.r = chk.r * chk.r + chk.i * chk.i;
           (chk.r < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     printf("check general stride view\n");
     for(j=0; j<3; j++)
        for(i=0; i<2; i++){
           vsip_cscalar_f chk = vsip_cmget_f(b,i,j);
           chk.r = chk.r - ansr[i][j]; chk.i = chk.i - ansi[i][j];
           chk.r = chk.r * chk.r + chk.i * chk.i;
           (chk.r < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     vsip_cmalldestroy_f(a);
     vsip_cmalldestroy_f(b);
   }
   return;
}
