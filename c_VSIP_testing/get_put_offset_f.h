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
/* $Id: get_put_offset_f.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_offset_f(void){
   printf("********\nTEST get_put_offset_f\n");
   {
       vsip_offset ivo = 3, icvo=10; 
       vsip_stride ivs = 0, icvs=0;
       vsip_length ivl = 3, icvl=4;
       vsip_offset jvo = 2, jcvo=0; 

       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;
       
       vsip_stride ixs = 0, iys = 0, izs = 0;
       vsip_length ixl = 2, iyl = 3, izl = 4;

       vsip_block_f *b = vsip_blockcreate_f(80,VSIP_MEM_NONE);
       vsip_cblock_f *cb = vsip_cblockcreate_f(80,VSIP_MEM_NONE);
       vsip_vview_f *v = vsip_vbind_f(b,ivo,ivs,ivl);
       vsip_mview_f *m = vsip_mbind_f(b,ivo,ics,icl,irs,irl);
       vsip_tview_f *t = vsip_tbind_f(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_f *cv = vsip_cvbind_f(cb,icvo,icvs,icvl);
       vsip_cmview_f *cm = vsip_cmbind_f(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_f *ct = vsip_ctbind_f(cb,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_offset s;
       
       printf("test vgetoffset_f\n"); fflush(stdout);
       {
          s = vsip_vgetoffset_f(v);
          (s == ivo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_f\n"); fflush(stdout);
       {
          vsip_vputoffset_f(v,jvo);
          s = vsip_vgetoffset_f(v);
          (s == jvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
       printf("test cvgetoffset_f\n"); fflush(stdout);
       {
          s = vsip_cvgetoffset_f(cv);
          (s == icvo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_f\n"); fflush(stdout);
       {
          vsip_cvputoffset_f(cv,jcvo);
          s = vsip_cvgetoffset_f(cv);
          (s == jcvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetoffset_f\n"); fflush(stdout);
       {
          s = vsip_mgetoffset_f(m);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputoffset_f\n"); fflush(stdout);
       {
          vsip_mputoffset_f(m,jvo);
          s = vsip_mgetoffset_f(m);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }

       printf("test cmgetoffset_f\n"); fflush(stdout);
       {
          s = vsip_cmgetoffset_f(cm);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputoffset_f\n"); fflush(stdout);
       {
          vsip_cmputoffset_f(cm,jvo);
          s = vsip_cmgetoffset_f(cm);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetoffset_f\n"); fflush(stdout);
       {
          s = vsip_tgetoffset_f(t);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputoffset_f\n"); fflush(stdout);
       {
          vsip_tputoffset_f(t,jvo);
          s = vsip_tgetoffset_f(t);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }
       printf("test ctgetoffset_f\n"); fflush(stdout);
       {
          s = vsip_ctgetoffset_f(ct);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputoffset_f\n"); fflush(stdout);
       {
          vsip_ctputoffset_f(ct,jvo);
          s = vsip_ctgetoffset_f(ct);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }
       vsip_vdestroy_f(v);
       vsip_mdestroy_f(m);
       vsip_talldestroy_f(t);
       vsip_cvdestroy_f(cv);
       vsip_cmdestroy_f(cm);
       vsip_ctalldestroy_f(ct);
   }
   return;
}
