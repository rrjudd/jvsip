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
/* $Id: get_put_stride_f.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_stride_f(void){
   printf("********\nTEST get_put_stride_f\n");
   {
       vsip_offset ivo = 3, icvo=10; 
       vsip_stride ivs = 2, icvs=-1;
       vsip_length ivl = 3, icvl=4;
       vsip_stride jvs = 3, jcvs=1;

       vsip_stride irs = 1, ics = 3; 
       vsip_length irl = 2, icl = 3;
       vsip_stride jrs = 5, jcs = 2; 
       
       vsip_stride ixs = 2, iys = 4, izs = 14;
       vsip_length ixl = 2, iyl = 3, izl = 4;
       vsip_stride jxs = 4, jys = 14, jzs = 2;

       vsip_block_f *b = vsip_blockcreate_f(80,VSIP_MEM_NONE);
       vsip_cblock_f *cb = vsip_cblockcreate_f(80,VSIP_MEM_NONE);
       vsip_vview_f *v = vsip_vbind_f(b,ivo,ivs,ivl);
       vsip_mview_f *m = vsip_mbind_f(b,ivo,ics,icl,irs,irl);
       vsip_tview_f *t = vsip_tbind_f(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_f *cv = vsip_cvbind_f(cb,icvo,icvs,icvl);
       vsip_cmview_f *cm = vsip_cmbind_f(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_f *ct = vsip_ctbind_f(cb,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_stride s;
       
       printf("test vgetstride_f\n"); fflush(stdout);
       {
          s = vsip_vgetstride_f(v);
          (s == ivs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_f\n"); fflush(stdout);
       {
          vsip_vputstride_f(v,jvs);
          s = vsip_vgetstride_f(v);
          (s == jvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
       printf("test cvgetstride_f\n"); fflush(stdout);
       {
          s = vsip_cvgetstride_f(cv);
          (s == icvs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_f\n"); fflush(stdout);
       {
          vsip_cvputstride_f(cv,jcvs);
          s = vsip_cvgetstride_f(cv);
          (s == jcvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowstride_f\n"); fflush(stdout);
       {
          s = vsip_mgetrowstride_f(m);
          (s == irs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowstride_f\n"); fflush(stdout);
       {
          vsip_mputrowstride_f(m,jrs);
          s = vsip_mgetrowstride_f(m);
          (s == jrs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test mgetcolstride_f\n"); fflush(stdout);
       {
          s = vsip_mgetcolstride_f(m);
          (s == ics) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcolstride_f\n"); fflush(stdout);
       {
          vsip_mputcolstride_f(m,jcs);
          s = vsip_mgetcolstride_f(m);
          (s == jcs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test cmgetrowstride_f\n"); fflush(stdout);
       {
          s = vsip_cmgetrowstride_f(cm);
          (s == irs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputrowstride_f\n"); fflush(stdout);
       {
          vsip_cmputrowstride_f(cm,jrs);
          s = vsip_cmgetrowstride_f(cm);
          (s == jrs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test cmgetcolstride_f\n"); fflush(stdout);
       {
          s = vsip_cmgetcolstride_f(cm);
          (s == ics) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputcolstride_f\n"); fflush(stdout);
       {
          vsip_cmputcolstride_f(cm,jcs);
          s = vsip_cmgetcolstride_f(cm);
          (s == jcs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxstride_f\n"); fflush(stdout);
       {
          s = vsip_tgetxstride_f(t);
          (s == ixs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxstride_f\n"); fflush(stdout);
       {
          vsip_tputxstride_f(t,jxs);
          s = vsip_tgetxstride_f(t);
          (s == jxs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test ctgetxstride_f\n"); fflush(stdout);
       {
          s = vsip_ctgetxstride_f(ct);
          (s == ixs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputxstride_f\n"); fflush(stdout);
       {
          vsip_ctputxstride_f(ct,jxs);
          s = vsip_ctgetxstride_f(ct);
          (s == jxs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }


       printf("test tgetystride_f\n"); fflush(stdout);
       {
          s = vsip_tgetystride_f(t);
          (s == iys) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputystride_f\n"); fflush(stdout);
       {
          vsip_tputystride_f(t,jys);
          s = vsip_tgetystride_f(t);
          (s == jys) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test ctgetystride_f\n"); fflush(stdout);
       {
          s = vsip_ctgetystride_f(ct);
          (s == iys) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputystride_f\n"); fflush(stdout);
       {
          vsip_ctputystride_f(ct,jys);
          s = vsip_ctgetystride_f(ct);
          (s == jys) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test tgetzstride_f\n"); fflush(stdout);
       {
          s = vsip_tgetzstride_f(t);
          (s == izs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzstride_f\n"); fflush(stdout);
       {
          vsip_tputzstride_f(t,jzs);
          s = vsip_tgetzstride_f(t);
          (s == jzs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test ctgetzstride_f\n"); fflush(stdout);
       {
          s = vsip_ctgetzstride_f(ct);
          (s == izs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputzstride_f\n"); fflush(stdout);
       {
          vsip_ctputzstride_f(ct,jzs);
          s = vsip_ctgetzstride_f(ct);
          (s == jzs) ? printf("stride correct\n") :
                               printf("stride error \n");
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
