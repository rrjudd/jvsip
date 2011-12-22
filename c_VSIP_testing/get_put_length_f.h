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
/* $Id: get_put_length_f.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_f(void){
   printf("********\nTEST get_put_length_f\n");
   {
       vsip_offset ivo = 3, icvo=10; 
       vsip_stride ivs = 0, icvs=0;
       vsip_length ivl = 3, icvl=4;
       vsip_length jvl = 5, jcvl=7;

       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;
       vsip_length jrl = 5, jcl = 2;
       
       vsip_stride ixs = 0, iys = 0, izs = 0;
       vsip_length ixl = 2, iyl = 3, izl = 4;
       vsip_length jxl = 3, jyl = 4, jzl = 2;

       vsip_block_f *b = vsip_blockcreate_f(80,VSIP_MEM_NONE);
       vsip_cblock_f *cb = vsip_cblockcreate_f(80,VSIP_MEM_NONE);
       vsip_vview_f *v = vsip_vbind_f(b,ivo,ivs,ivl);
       vsip_mview_f *m = vsip_mbind_f(b,ivo,ics,icl,irs,irl);
       vsip_tview_f *t = vsip_tbind_f(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_f *cv = vsip_cvbind_f(cb,icvo,icvs,icvl);
       vsip_cmview_f *cm = vsip_cmbind_f(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_f *ct = vsip_ctbind_f(cb,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_length s;
       
       printf("test vgetlength_f\n"); fflush(stdout);
       {
          s = vsip_vgetlength_f(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_f\n"); fflush(stdout);
       {
          vsip_vputlength_f(v,jvl);
          s = vsip_vgetlength_f(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
       printf("test cvgetlength_f\n"); fflush(stdout);
       {
          s = vsip_cvgetlength_f(cv);
          (s == icvl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_f\n"); fflush(stdout);
       {
          vsip_cvputlength_f(cv,jcvl);
          s = vsip_cvgetlength_f(cv);
          (s == jcvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowlength_f\n"); fflush(stdout);
       {
          s = vsip_mgetrowlength_f(m);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowlength_f\n"); fflush(stdout);
       {
          vsip_mputrowlength_f(m,jrl);
          s = vsip_mgetrowlength_f(m);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test mgetcollength_f\n"); fflush(stdout);
       {
          s = vsip_mgetcollength_f(m);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcollength_f\n"); fflush(stdout);
       {
          vsip_mputcollength_f(m,jcl);
          s = vsip_mgetcollength_f(m);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test cmgetrowlength_f\n"); fflush(stdout);
       {
          s = vsip_cmgetrowlength_f(cm);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputrowlength_f\n"); fflush(stdout);
       {
          vsip_cmputrowlength_f(cm,jrl);
          s = vsip_cmgetrowlength_f(cm);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test cmgetcollength_f\n"); fflush(stdout);
       {
          s = vsip_cmgetcollength_f(cm);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputcollength_f\n"); fflush(stdout);
       {
          vsip_cmputcollength_f(cm,jcl);
          s = vsip_cmgetcollength_f(cm);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxlength_f\n"); fflush(stdout);
       {
          s = vsip_tgetxlength_f(t);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxlength_f\n"); fflush(stdout);
       {
          vsip_tputxlength_f(t,jxl);
          s = vsip_tgetxlength_f(t);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test ctgetxlength_f\n"); fflush(stdout);
       {
          s = vsip_ctgetxlength_f(ct);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputxlength_f\n"); fflush(stdout);
       {
          vsip_ctputxlength_f(ct,jxl);
          s = vsip_ctgetxlength_f(ct);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }


       printf("test tgetylength_f\n"); fflush(stdout);
       {
          s = vsip_tgetylength_f(t);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputylength_f\n"); fflush(stdout);
       {
          vsip_tputylength_f(t,jyl);
          s = vsip_tgetylength_f(t);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test ctgetylength_f\n"); fflush(stdout);
       {
          s = vsip_ctgetylength_f(ct);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputylength_f\n"); fflush(stdout);
       {
          vsip_ctputylength_f(ct,jyl);
          s = vsip_ctgetylength_f(ct);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test tgetzlength_f\n"); fflush(stdout);
       {
          s = vsip_tgetzlength_f(t);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzlength_f\n"); fflush(stdout);
       {
          vsip_tputzlength_f(t,jzl);
          s = vsip_tgetzlength_f(t);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test ctgetzlength_f\n"); fflush(stdout);
       {
          s = vsip_ctgetzlength_f(ct);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputzlength_f\n"); fflush(stdout);
       {
          vsip_ctputzlength_f(ct,jzl);
          s = vsip_ctgetzlength_f(ct);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
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
