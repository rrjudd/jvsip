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
/* $Id: get_put_stride_d.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_stride_d(void){
   printf("********\nTEST get_put_stride_d\n");
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

       vsip_block_d *b = vsip_blockcreate_d(80,VSIP_MEM_NONE);
       vsip_cblock_d *cb = vsip_cblockcreate_d(80,VSIP_MEM_NONE);
       vsip_vview_d *v = vsip_vbind_d(b,ivo,ivs,ivl);
       vsip_mview_d *m = vsip_mbind_d(b,ivo,ics,icl,irs,irl);
       vsip_tview_d *t = vsip_tbind_d(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_d *cv = vsip_cvbind_d(cb,icvo,icvs,icvl);
       vsip_cmview_d *cm = vsip_cmbind_d(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_d *ct = vsip_ctbind_d(cb,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_stride s;
       
       printf("test vgetstride_d\n"); fflush(stdout);
       {
          s = vsip_vgetstride_d(v);
          (s == ivs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_d\n"); fflush(stdout);
       {
          vsip_vputstride_d(v,jvs);
          s = vsip_vgetstride_d(v);
          (s == jvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
       printf("test cvgetstride_d\n"); fflush(stdout);
       {
          s = vsip_cvgetstride_d(cv);
          (s == icvs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_d\n"); fflush(stdout);
       {
          vsip_cvputstride_d(cv,jcvs);
          s = vsip_cvgetstride_d(cv);
          (s == jcvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowstride_d\n"); fflush(stdout);
       {
          s = vsip_mgetrowstride_d(m);
          (s == irs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowstride_d\n"); fflush(stdout);
       {
          vsip_mputrowstride_d(m,jrs);
          s = vsip_mgetrowstride_d(m);
          (s == jrs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test mgetcolstride_d\n"); fflush(stdout);
       {
          s = vsip_mgetcolstride_d(m);
          (s == ics) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcolstride_d\n"); fflush(stdout);
       {
          vsip_mputcolstride_d(m,jcs);
          s = vsip_mgetcolstride_d(m);
          (s == jcs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test cmgetrowstride_d\n"); fflush(stdout);
       {
          s = vsip_cmgetrowstride_d(cm);
          (s == irs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputrowstride_d\n"); fflush(stdout);
       {
          vsip_cmputrowstride_d(cm,jrs);
          s = vsip_cmgetrowstride_d(cm);
          (s == jrs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test cmgetcolstride_d\n"); fflush(stdout);
       {
          s = vsip_cmgetcolstride_d(cm);
          (s == ics) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test cmputcolstride_d\n"); fflush(stdout);
       {
          vsip_cmputcolstride_d(cm,jcs);
          s = vsip_cmgetcolstride_d(cm);
          (s == jcs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxstride_d\n"); fflush(stdout);
       {
          s = vsip_tgetxstride_d(t);
          (s == ixs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxstride_d\n"); fflush(stdout);
       {
          vsip_tputxstride_d(t,jxs);
          s = vsip_tgetxstride_d(t);
          (s == jxs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test ctgetxstride_d\n"); fflush(stdout);
       {
          s = vsip_ctgetxstride_d(ct);
          (s == ixs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputxstride_d\n"); fflush(stdout);
       {
          vsip_ctputxstride_d(ct,jxs);
          s = vsip_ctgetxstride_d(ct);
          (s == jxs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }


       printf("test tgetystride_d\n"); fflush(stdout);
       {
          s = vsip_tgetystride_d(t);
          (s == iys) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputystride_d\n"); fflush(stdout);
       {
          vsip_tputystride_d(t,jys);
          s = vsip_tgetystride_d(t);
          (s == jys) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test ctgetystride_d\n"); fflush(stdout);
       {
          s = vsip_ctgetystride_d(ct);
          (s == iys) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputystride_d\n"); fflush(stdout);
       {
          vsip_ctputystride_d(ct,jys);
          s = vsip_ctgetystride_d(ct);
          (s == jys) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test tgetzstride_d\n"); fflush(stdout);
       {
          s = vsip_tgetzstride_d(t);
          (s == izs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzstride_d\n"); fflush(stdout);
       {
          vsip_tputzstride_d(t,jzs);
          s = vsip_tgetzstride_d(t);
          (s == jzs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test ctgetzstride_d\n"); fflush(stdout);
       {
          s = vsip_ctgetzstride_d(ct);
          (s == izs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test ctputzstride_d\n"); fflush(stdout);
       {
          vsip_ctputzstride_d(ct,jzs);
          s = vsip_ctgetzstride_d(ct);
          (s == jzs) ? printf("stride correct\n") :
                               printf("stride error \n");
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
