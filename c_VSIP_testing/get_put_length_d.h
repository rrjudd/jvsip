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
/* $Id: get_put_length_d.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_d(void){
   printf("********\nTEST get_put_length_d\n");
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

       vsip_block_d *b = vsip_blockcreate_d(80,VSIP_MEM_NONE);
       vsip_cblock_d *cb = vsip_cblockcreate_d(80,VSIP_MEM_NONE);
       vsip_vview_d *v = vsip_vbind_d(b,ivo,ivs,ivl);
       vsip_mview_d *m = vsip_mbind_d(b,ivo,ics,icl,irs,irl);
       vsip_tview_d *t = vsip_tbind_d(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_d *cv = vsip_cvbind_d(cb,icvo,icvs,icvl);
       vsip_cmview_d *cm = vsip_cmbind_d(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_d *ct = vsip_ctbind_d(cb,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_length s;
       
       printf("test vgetlength_d\n"); fflush(stdout);
       {
          s = vsip_vgetlength_d(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_d\n"); fflush(stdout);
       {
          vsip_vputlength_d(v,jvl);
          s = vsip_vgetlength_d(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
       printf("test cvgetlength_d\n"); fflush(stdout);
       {
          s = vsip_cvgetlength_d(cv);
          (s == icvl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_d\n"); fflush(stdout);
       {
          vsip_cvputlength_d(cv,jcvl);
          s = vsip_cvgetlength_d(cv);
          (s == jcvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowlength_d\n"); fflush(stdout);
       {
          s = vsip_mgetrowlength_d(m);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowlength_d\n"); fflush(stdout);
       {
          vsip_mputrowlength_d(m,jrl);
          s = vsip_mgetrowlength_d(m);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test mgetcollength_d\n"); fflush(stdout);
       {
          s = vsip_mgetcollength_d(m);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcollength_d\n"); fflush(stdout);
       {
          vsip_mputcollength_d(m,jcl);
          s = vsip_mgetcollength_d(m);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test cmgetrowlength_d\n"); fflush(stdout);
       {
          s = vsip_cmgetrowlength_d(cm);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputrowlength_d\n"); fflush(stdout);
       {
          vsip_cmputrowlength_d(cm,jrl);
          s = vsip_cmgetrowlength_d(cm);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test cmgetcollength_d\n"); fflush(stdout);
       {
          s = vsip_cmgetcollength_d(cm);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputcollength_d\n"); fflush(stdout);
       {
          vsip_cmputcollength_d(cm,jcl);
          s = vsip_cmgetcollength_d(cm);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxlength_d\n"); fflush(stdout);
       {
          s = vsip_tgetxlength_d(t);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxlength_d\n"); fflush(stdout);
       {
          vsip_tputxlength_d(t,jxl);
          s = vsip_tgetxlength_d(t);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test ctgetxlength_d\n"); fflush(stdout);
       {
          s = vsip_ctgetxlength_d(ct);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputxlength_d\n"); fflush(stdout);
       {
          vsip_ctputxlength_d(ct,jxl);
          s = vsip_ctgetxlength_d(ct);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }


       printf("test tgetylength_d\n"); fflush(stdout);
       {
          s = vsip_tgetylength_d(t);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputylength_d\n"); fflush(stdout);
       {
          vsip_tputylength_d(t,jyl);
          s = vsip_tgetylength_d(t);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test ctgetylength_d\n"); fflush(stdout);
       {
          s = vsip_ctgetylength_d(ct);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputylength_d\n"); fflush(stdout);
       {
          vsip_ctputylength_d(ct,jyl);
          s = vsip_ctgetylength_d(ct);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test tgetzlength_d\n"); fflush(stdout);
       {
          s = vsip_tgetzlength_d(t);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzlength_d\n"); fflush(stdout);
       {
          vsip_tputzlength_d(t,jzl);
          s = vsip_tgetzlength_d(t);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test ctgetzlength_d\n"); fflush(stdout);
       {
          s = vsip_ctgetzlength_d(ct);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputzlength_d\n"); fflush(stdout);
       {
          vsip_ctputzlength_d(ct,jzl);
          s = vsip_ctgetzlength_d(ct);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
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
