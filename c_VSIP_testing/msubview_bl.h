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
/* $Id: msubview_bl.h,v 2.0 2003/02/22 15:23:34 judd Exp $ */
static void msubview_bl(void){
   printf("********\nTEST msubview_bl\n");
   {
      vsip_scalar_bl data[10][4] ={{ 0,  1,  1,  1}, 
                                  {  0,  1,  0,  0},
                                  {  0,  1,  0,  1},
                                  {  0,  1,  0,  0},
                                  {  1,  0,  0,  0},
                                  {  0,  0,  0,  0},
                                  {  0,  1,  1,  1},
                                  {  0,  1,  1,  0},
                                  {  1,  1,  0,  1},
                                  {  0,  1,  1,  0}};
      vsip_offset           o = 4;
      vsip_stride          rs = 2, cs = 8;
      vsip_length           m = 10, n = 4;
      vsip_block_bl         *b = vsip_blockcreate_bl(100,VSIP_MEM_NONE);
      vsip_mview_bl         *v = vsip_mbind_bl(b,o,cs,m,rs,n);
      vsip_index           si = 2, sj = 1;
      vsip_length          sm = 5, sn = 3;
      vsip_mview_bl        *sv = vsip_msubview_bl(v,si,sj,sm,sn);
      vsip_scalar_bl chk = VSIP_FALSE;
      int i,j;
      for(i=0; i< (int)m; i++)
         for(j=0; j< (int)n; j++)
            vsip_mput_bl(v,i,j,data[i][j]);
      for(i=0; i< (int)sm; i++){
         for(j=0; j< (int)sn; j++){
            vsip_scalar_bl d = (data[si+i][sj+j] != 0) ? 
                                          VSIP_TRUE : VSIP_FALSE;
            vsip_scalar_bl a = (vsip_mget_bl(sv,i,j) != VSIP_FALSE) ?
                                          VSIP_TRUE : VSIP_FALSE;
            if(a != d) chk = VSIP_TRUE;
         }
      }
      (chk == VSIP_TRUE) ?    printf("error \n") :
                              printf("correct \n");
      fflush(stdout);
      vsip_mdestroy_bl(sv);
      vsip_malldestroy_bl(v);
   }
   return;
}
