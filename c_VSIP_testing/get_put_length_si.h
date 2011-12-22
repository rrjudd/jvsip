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
/* $Id: get_put_length_si.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_si(void){
   printf("********\nTEST get_put_length_si\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 0;
       vsip_length ivl = 3;
       vsip_length jvl = 5;

       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;
       vsip_length jrl = 5, jcl = 2;
       
       vsip_stride ixs = 0, iys = 0, izs = 0;
       vsip_length ixl = 2, iyl = 3, izl = 4;
       vsip_length jxl = 3, jyl = 4, jzl = 2;

       vsip_block_si *b = vsip_blockcreate_si(80,VSIP_MEM_NONE);
       vsip_vview_si *v = vsip_vbind_si(b,ivo,ivs,ivl);
       vsip_mview_si *m = vsip_mbind_si(b,ivo,ics,icl,irs,irl);
       vsip_tview_si *t = vsip_tbind_si(b,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_length s;
       
       printf("test vgetlength_si\n"); fflush(stdout);
       {
          s = vsip_vgetlength_si(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_si\n"); fflush(stdout);
       {
          vsip_vputlength_si(v,jvl);
          s = vsip_vgetlength_si(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowlength_si\n"); fflush(stdout);
       {
          s = vsip_mgetrowlength_si(m);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowlength_si\n"); fflush(stdout);
       {
          vsip_mputrowlength_si(m,jrl);
          s = vsip_mgetrowlength_si(m);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test mgetcollength_si\n"); fflush(stdout);
       {
          s = vsip_mgetcollength_si(m);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcollength_si\n"); fflush(stdout);
       {
          vsip_mputcollength_si(m,jcl);
          s = vsip_mgetcollength_si(m);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxlength_si\n"); fflush(stdout);
       {
          s = vsip_tgetxlength_si(t);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxlength_si\n"); fflush(stdout);
       {
          vsip_tputxlength_si(t,jxl);
          s = vsip_tgetxlength_si(t);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test tgetylength_si\n"); fflush(stdout);
       {
          s = vsip_tgetylength_si(t);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputylength_si\n"); fflush(stdout);
       {
          vsip_tputylength_si(t,jyl);
          s = vsip_tgetylength_si(t);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test tgetzlength_si\n"); fflush(stdout);
       {
          s = vsip_tgetzlength_si(t);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzlength_si\n"); fflush(stdout);
       {
          vsip_tputzlength_si(t,jzl);
          s = vsip_tgetzlength_si(t);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       vsip_vdestroy_si(v);
       vsip_mdestroy_si(m);
       vsip_talldestroy_si(t);
   }
   return;
}
