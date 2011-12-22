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
/* $Id: get_put_offset_bl.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_offset_bl(void){
   printf("********\nTEST get_put_offset_bl\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 0;
       vsip_length ivl = 3;
       vsip_offset jvo = 2;

       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;       

       vsip_block_bl *b = vsip_blockcreate_bl(80,VSIP_MEM_NONE);
       vsip_vview_bl *v = vsip_vbind_bl(b,ivo,ivs,ivl);
       vsip_mview_bl *m = vsip_mbind_bl(b,ivo,ics,icl,irs,irl);

       vsip_offset s;
       
       printf("test vgetoffset_bl\n"); fflush(stdout);
       {
          s = vsip_vgetoffset_bl(v);
          (s == ivo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_bl\n"); fflush(stdout);
       {
          vsip_vputoffset_bl(v,jvo);
          s = vsip_vgetoffset_bl(v);
          (s == jvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetoffset_bl\n"); fflush(stdout);
       {
          s = vsip_mgetoffset_bl(m);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputoffset_bl\n"); fflush(stdout);
       {
          vsip_mputoffset_bl(m,jvo);
          s = vsip_mgetoffset_bl(m);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }
       vsip_vdestroy_bl(v);
       vsip_malldestroy_bl(m);
   }
   return;
}
