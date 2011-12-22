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
/* $Id: get_put_offset_mi.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_offset_mi(void){
   printf("********\nTEST get_put_offset_mi\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 0;
       vsip_length ivl = 3;
       vsip_offset jvo = 2;
       
       vsip_block_mi *b = vsip_blockcreate_mi(80,VSIP_MEM_NONE);
       vsip_vview_mi *v = vsip_vbind_mi(b,ivo,ivs,ivl);

       vsip_offset s;
       
       printf("test vgetoffset_mi\n"); fflush(stdout);
       {
          s = vsip_vgetoffset_mi(v);
          (s == ivo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_mi\n"); fflush(stdout);
       {
          vsip_vputoffset_mi(v,jvo);
          s = vsip_vgetoffset_mi(v);
          (s == jvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
       vsip_valldestroy_mi(v);
   }
   return;
}
