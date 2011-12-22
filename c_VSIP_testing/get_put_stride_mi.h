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
/* $Id: get_put_stride_mi.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_stride_mi(void){
   printf("********\nTEST get_put_stride_mi\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 2;
       vsip_length ivl = 3;
       vsip_stride jvs = 3;

       

       vsip_block_mi *b = vsip_blockcreate_mi(80,VSIP_MEM_NONE);
       vsip_vview_mi *v = vsip_vbind_mi(b,ivo,ivs,ivl);

       vsip_stride s;
       
       printf("test vgetstride_mi\n"); fflush(stdout);
       {
          s = vsip_vgetstride_mi(v);
          (s == ivs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_mi\n"); fflush(stdout);
       {
          vsip_vputstride_mi(v,jvs);
          s = vsip_vgetstride_mi(v);
          (s == jvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
       vsip_valldestroy_mi(v);
   }
   return;
}
