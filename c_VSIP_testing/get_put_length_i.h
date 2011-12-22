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
/* $Id: get_put_length_i.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_i(void){
   printf("********\nTEST get_put_length_i\n");
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

       vsip_block_i *b = vsip_blockcreate_i(80,VSIP_MEM_NONE);
       vsip_vview_i *v = vsip_vbind_i(b,ivo,ivs,ivl);
       vsip_mview_i *m = vsip_mbind_i(b,ivo,ics,icl,irs,irl);
       vsip_tview_i *t = vsip_tbind_i(b,ivo,izs,izl,iys,iyl,ixs,ixl);

       vsip_length s;
       
       printf("test vgetlength_i\n"); fflush(stdout);
       {
          s = vsip_vgetlength_i(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_i\n"); fflush(stdout);
       {
          vsip_vputlength_i(v,jvl);
          s = vsip_vgetlength_i(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowlength_i\n"); fflush(stdout);
       {
          s = vsip_mgetrowlength_i(m);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowlength_i\n"); fflush(stdout);
       {
          vsip_mputrowlength_i(m,jrl);
          s = vsip_mgetrowlength_i(m);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test mgetcollength_i\n"); fflush(stdout);
       {
          s = vsip_mgetcollength_i(m);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcollength_i\n"); fflush(stdout);
       {
          vsip_mputcollength_i(m,jcl);
          s = vsip_mgetcollength_i(m);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

/*************************************************************************/
       printf("test tgetxlength_i\n"); fflush(stdout);
       {
          s = vsip_tgetxlength_i(t);
          (s == ixl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputxlength_i\n"); fflush(stdout);
       {
          vsip_tputxlength_i(t,jxl);
          s = vsip_tgetxlength_i(t);
          (s == jxl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test tgetylength_i\n"); fflush(stdout);
       {
          s = vsip_tgetylength_i(t);
          (s == iyl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputylength_i\n"); fflush(stdout);
       {
          vsip_tputylength_i(t,jyl);
          s = vsip_tgetylength_i(t);
          (s == jyl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       printf("test tgetzlength_i\n"); fflush(stdout);
       {
          s = vsip_tgetzlength_i(t);
          (s == izl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test tputzlength_i\n"); fflush(stdout);
       {
          vsip_tputzlength_i(t,jzl);
          s = vsip_tgetzlength_i(t);
          (s == jzl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       vsip_vdestroy_i(v);
       vsip_mdestroy_i(m);
       vsip_talldestroy_i(t);
   }
   return;
}
