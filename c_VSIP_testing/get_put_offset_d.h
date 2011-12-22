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
/* $Id: get_put_offset_d.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_offset_d(void){
   printf("********\nTEST get_put_offset_d\n");
   {
       vsip_offset ivo = 3, icvo=10; 
       vsip_stride ivs = 0, icvs=0;
       vsip_length ivl = 3, icvl=4;
       vsip_offset jvo = 2, jcvo=0; 
       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;
       
       vsip_stride ixs = 0, iys = 0, izs = 0;
       vsip_length ixl = 2, iyl = 3, izl = 4;

       vsip_block_d *b = vsip_blockcreate_d(80,VSIP_MEM_NONE);
       vsip_cblock_d *cb = vsip_cblockcreate_d(80,VSIP_MEM_NONE);
       vsip_vview_d *v = vsip_vbind_d(b,ivo,ivs,ivl);
       vsip_mview_d *m = vsip_mbind_d(b,ivo,ics,icl,irs,irl);
       vsip_tview_d *t = vsip_tbind_d(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_d *cv = vsip_cvbind_d(cb,icvo,icvs,icvl);
       vsip_cmview_d *cm = vsip_cmbind_d(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_d *ct = vsip_ctbind_d(cb,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_offset s;
       
       printf("test vgetoffset_d\n"); fflush(stdout);
       {
          s = vsip_vgetoffset_d(v);
          (s == ivo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_d\n"); fflush(stdout);
       {
          vsip_vputoffset_d(v,jvo);
          s = vsip_vgetoffset_d(v);
          (s == jvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
       printf("test cvgetoffset_d\n"); fflush(stdout);
       {
          s = vsip_cvgetoffset_d(cv);
          (s == icvo) ? printf("offset correct\n") : 
                       printf("offset error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputoffset_d\n"); fflush(stdout);
       {
          vsip_cvputoffset_d(cv,jcvo);
          s = vsip_cvgetoffset_d(cv);
          (s == jcvo) ? printf("offset correct\n") : 
                               printf("offset error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetoffset_d\n"); fflush(stdout);
       {
          s = vsip_mgetoffset_d(m);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputoffset_d\n"); fflush(stdout);
       {
          vsip_mputoffset_d(m,jvo);
          s = vsip_mgetoffset_d(m);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }

       printf("test cmgetoffset_d\n"); fflush(stdout);
       {
          s = vsip_cmgetoffset_d(cm);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputoffset_d\n"); fflush(stdout);
       {
          vsip_cmputoffset_d(cm,jvo);
          s = vsip_cmgetoffset_d(cm);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetoffset_d\n"); fflush(stdout);
       {
          s = vsip_tgetoffset_d(t);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputoffset_d\n"); fflush(stdout);
       {
          vsip_tputoffset_d(t,jvo);
          s = vsip_tgetoffset_d(t);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }
       printf("test ctgetoffset_d\n"); fflush(stdout);
       {
          s = vsip_ctgetoffset_d(ct);
          (s == ivo) ? printf("offset correct\n") :
                       printf("offset error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputoffset_d\n"); fflush(stdout);
       {
          vsip_ctputoffset_d(ct,jvo);
          s = vsip_ctgetoffset_d(ct);
          (s == jvo) ? printf("offset correct\n") :
                               printf("offset error \n");
          fflush(stdout);
       }
       vsip_vdestroy_d(v);
       vsip_mdestroy_d(m);
       vsip_talldestroy_d(t);
       vsip_cvdestroy_d(cv);
       vsip_cmdestroy_d(cm);
       vsip_ctalldestroy_d(ct);
   }
   return;
}
