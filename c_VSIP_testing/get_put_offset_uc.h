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
/* $Id: get_put_offset_uc.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_offset_uc(void){
   printf("********\nTEST get_put_offset_uc\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 0;
       vsip_length ivl = 3;
       vsip_offset jvo = 2;

       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;
       
       vsip_stride ixs = 0, iys = 0, izs = 0;
       vsip_length ixl = 2, iyl = 3, izl = 4;

       vsip_block_uc *b = vsip_blockcreate_uc(80,VSIP_MEM_NONE);
       vsip_vview_uc *v = vsip_vbind_uc(b,ivo,ivs,ivl);
       vsip_mview_uc *m = vsip_mbind_uc(b,ivo,ics,icl,irs,irl);
       vsip_tview_uc *t = vsip_tbind_uc(b,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_offset s;
       
       printf("test vgetoffset_uc\n"); fflush(stdout);
       {
          s = vsip_vgetoffset_uc(v);
          (s == ivo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_uc\n"); fflush(stdout);
       {
          vsip_vputoffset_uc(v,jvo);
          s = vsip_vgetoffset_uc(v);
          (s == jvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetoffset_uc\n"); fflush(stdout);
       {
          s = vsip_mgetoffset_uc(m);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputoffset_uc\n"); fflush(stdout);
       {
          vsip_mputoffset_uc(m,jvo);
          s = vsip_mgetoffset_uc(m);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetoffset_uc\n"); fflush(stdout);
       {
          s = vsip_tgetoffset_uc(t);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputoffset_uc\n"); fflush(stdout);
       {
          vsip_tputoffset_uc(t,jvo);
          s = vsip_tgetoffset_uc(t);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }
       vsip_vdestroy_uc(v);
       vsip_mdestroy_uc(m);
       vsip_talldestroy_uc(t);
   }
   return;
}
