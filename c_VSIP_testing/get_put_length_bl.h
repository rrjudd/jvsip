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
/* $Id: get_put_length_bl.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_length_bl(void){
   printf("********\nTEST get_put_length_bl\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 0;
       vsip_length ivl = 3;
       vsip_length jvl = 5;

       vsip_stride irs = 0, ics = 0; 
       vsip_length irl = 2, icl = 3;
       vsip_length jrl = 5, jcl = 2;
       

       vsip_block_bl *b = vsip_blockcreate_bl(80,VSIP_MEM_NONE);
       vsip_vview_bl *v = vsip_vbind_bl(b,ivo,ivs,ivl);
       vsip_mview_bl *m = vsip_mbind_bl(b,ivo,ics,icl,irs,irl);

       vsip_length s;
       
       printf("test vgetlength_bl\n"); fflush(stdout);
       {
          s = vsip_vgetlength_bl(v);
          (s == ivl) ? printf("length correct\n") : 
                       printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputlength_bl\n"); fflush(stdout);
       {
          vsip_vputlength_bl(v,jvl);
          s = vsip_vgetlength_bl(v);
          (s == jvl) ? printf("length correct\n") : 
                               printf("length error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowlength_bl\n"); fflush(stdout);
       {
          s = vsip_mgetrowlength_bl(m);
          (s == irl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowlength_bl\n"); fflush(stdout);
       {
          vsip_mputrowlength_bl(m,jrl);
          s = vsip_mgetrowlength_bl(m);
          (s == jrl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }

       printf("test mgetcollength_bl\n"); fflush(stdout);
       {
          s = vsip_mgetcollength_bl(m);
          (s == icl) ? printf("length correct\n") :
                       printf("length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcollength_bl\n"); fflush(stdout);
       {
          vsip_mputcollength_bl(m,jcl);
          s = vsip_mgetcollength_bl(m);
          (s == jcl) ? printf("length correct\n") :
                               printf("length error \n");
          fflush(stdout);
       }
       vsip_vdestroy_bl(v);
       vsip_malldestroy_bl(m);
   }
   return;
}
