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
/* $Id: get_put_stride_si.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_stride_si(void){
   printf("********\nTEST get_put_stride_si\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 2;
       vsip_length ivl = 3;
       vsip_stride jvs = 3;

       vsip_stride irs = 1, ics = 3; 
       vsip_length irl = 2, icl = 3;
       vsip_stride jrs = 5, jcs = 2; 
       
       vsip_stride ixs = 2, iys = 4, izs = 14;
       vsip_length ixl = 2, iyl = 3, izl = 4;
       vsip_stride jxs = 4, jys = 14, jzs = 2;

       vsip_block_si *b = vsip_blockcreate_si(80,VSIP_MEM_NONE);
       vsip_vview_si *v = vsip_vbind_si(b,ivo,ivs,ivl);
       vsip_mview_si *m = vsip_mbind_si(b,ivo,ics,icl,irs,irl);
       vsip_tview_si *t = vsip_tbind_si(b,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_stride s;
       
       printf("test vgetstride_si\n"); fflush(stdout);
       {
          s = vsip_vgetstride_si(v);
          (s == ivs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_si\n"); fflush(stdout);
       {
          vsip_vputstride_si(v,jvs);
          s = vsip_vgetstride_si(v);
          (s == jvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowstride_si\n"); fflush(stdout);
       {
          s = vsip_mgetrowstride_si(m);
          (s == irs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowstride_si\n"); fflush(stdout);
       {
          vsip_mputrowstride_si(m,jrs);
          s = vsip_mgetrowstride_si(m);
          (s == jrs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test mgetcolstride_si\n"); fflush(stdout);
       {
          s = vsip_mgetcolstride_si(m);
          (s == ics) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcolstride_si\n"); fflush(stdout);
       {
          vsip_mputcolstride_si(m,jcs);
          s = vsip_mgetcolstride_si(m);
          (s == jcs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxstride_si\n"); fflush(stdout);
       {
          s = vsip_tgetxstride_si(t);
          (s == ixs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxstride_si\n"); fflush(stdout);
       {
          vsip_tputxstride_si(t,jxs);
          s = vsip_tgetxstride_si(t);
          (s == jxs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test tgetystride_si\n"); fflush(stdout);
       {
          s = vsip_tgetystride_si(t);
          (s == iys) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputystride_si\n"); fflush(stdout);
       {
          vsip_tputystride_si(t,jys);
          s = vsip_tgetystride_si(t);
          (s == jys) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       printf("test tgetzstride_si\n"); fflush(stdout);
       {
          s = vsip_tgetzstride_si(t);
          (s == izs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzstride_si\n"); fflush(stdout);
       {
          vsip_tputzstride_si(t,jzs);
          s = vsip_tgetzstride_si(t);
          (s == jzs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       vsip_vdestroy_si(v);
       vsip_mdestroy_si(m);
       vsip_talldestroy_si(t);
   }
   return;
}
