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
/* $Id: get_put_length_vi.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_vi(void){
   printf("********\nTEST get_put_length_vi\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 0;
       vsip_length ivl = 3;
       vsip_length jvl = 5;
       
       vsip_block_vi *b = vsip_blockcreate_vi(80,VSIP_MEM_NONE);
       vsip_vview_vi *v = vsip_vbind_vi(b,ivo,ivs,ivl);

       vsip_length s;
       
       printf("test vgetlength_vi\n"); fflush(stdout);
       {
          s = vsip_vgetlength_vi(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_vi\n"); fflush(stdout);
       {
          vsip_vputlength_vi(v,jvl);
          s = vsip_vgetlength_vi(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
       vsip_valldestroy_vi(v);
   }
   return;
}
