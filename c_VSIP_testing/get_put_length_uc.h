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
/* $Id: get_put_length_uc.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_uc(void){
   printf("********\nTEST get_put_length_uc\n");
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

       vsip_block_uc *b = vsip_blockcreate_uc(80,VSIP_MEM_NONE);
       vsip_vview_uc *v = vsip_vbind_uc(b,ivo,ivs,ivl);
       vsip_mview_uc *m = vsip_mbind_uc(b,ivo,ics,icl,irs,irl);
       vsip_tview_uc *t = vsip_tbind_uc(b,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_length s;
       
       printf("test vgetlength_uc\n"); fflush(stdout);
       {
          s = vsip_vgetlength_uc(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_uc\n"); fflush(stdout);
       {
          vsip_vputlength_uc(v,jvl);
          s = vsip_vgetlength_uc(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowlength_uc\n"); fflush(stdout);
       {
          s = vsip_mgetrowlength_uc(m);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowlength_uc\n"); fflush(stdout);
       {
          vsip_mputrowlength_uc(m,jrl);
          s = vsip_mgetrowlength_uc(m);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test mgetcollength_uc\n"); fflush(stdout);
       {
          s = vsip_mgetcollength_uc(m);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcollength_uc\n"); fflush(stdout);
       {
          vsip_mputcollength_uc(m,jcl);
          s = vsip_mgetcollength_uc(m);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxlength_uc\n"); fflush(stdout);
       {
          s = vsip_tgetxlength_uc(t);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxlength_uc\n"); fflush(stdout);
       {
          vsip_tputxlength_uc(t,jxl);
          s = vsip_tgetxlength_uc(t);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test tgetylength_uc\n"); fflush(stdout);
       {
          s = vsip_tgetylength_uc(t);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputylength_uc\n"); fflush(stdout);
       {
          vsip_tputylength_uc(t,jyl);
          s = vsip_tgetylength_uc(t);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test tgetzlength_uc\n"); fflush(stdout);
       {
          s = vsip_tgetzlength_uc(t);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzlength_uc\n"); fflush(stdout);
       {
          vsip_tputzlength_uc(t,jzl);
          s = vsip_tgetzlength_uc(t);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       vsip_vdestroy_uc(v);
       vsip_mdestroy_uc(m);
       vsip_talldestroy_uc(t);
   }
   return;
}
