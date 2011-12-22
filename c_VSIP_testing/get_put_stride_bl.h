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
/* $Id: get_put_stride_bl.h,v 2.1 2007/04/18 17:05:56 judd Exp $ */
static void get_put_stride_bl(void){
   printf("********\nTEST get_put_stride_bl\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 2;
       vsip_length ivl = 3;
       vsip_stride jvs = 3;

       vsip_stride irs = 1, ics = 3; 
       vsip_length irl = 2, icl = 3;
       vsip_stride jrs = 5, jcs = 2; 
       

       vsip_block_bl *b = vsip_blockcreate_bl(80,VSIP_MEM_NONE);
       vsip_vview_bl *v = vsip_vbind_bl(b,ivo,ivs,ivl);
       vsip_mview_bl *m = vsip_mbind_bl(b,ivo,ics,icl,irs,irl);

       vsip_stride s;
       
       printf("test vgetstride_bl\n"); fflush(stdout);
       {
          s = vsip_vgetstride_bl(v);
          (s == ivs) ? printf("stride correct\n") : 
                       printf("stride error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputstride_bl\n"); fflush(stdout);
       {
          vsip_vputstride_bl(v,jvs);
          s = vsip_vgetstride_bl(v);
          (s == jvs) ? printf("stride correct\n") : 
                               printf("stride error \n");
          fflush(stdout);
       }       
/*************************************************************************/

       printf("test mgetrowstride_bl\n"); fflush(stdout);
       {
          s = vsip_mgetrowstride_bl(m);
          (s == irs) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputrowstride_bl\n"); fflush(stdout);
       {
          vsip_mputrowstride_bl(m,jrs);
          s = vsip_mgetrowstride_bl(m);
          (s == jrs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }

       printf("test mgetcolstride_bl\n"); fflush(stdout);
       {
          s = vsip_mgetcolstride_bl(m);
          (s == ics) ? printf("stride correct\n") :
                       printf("stride error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputcolstride_bl\n"); fflush(stdout);
       {
          vsip_mputcolstride_bl(m,jcs);
          s = vsip_mgetcolstride_bl(m);
          (s == jcs) ? printf("stride correct\n") :
                               printf("stride error \n");
          fflush(stdout);
       }
       vsip_vdestroy_bl(v);
       vsip_malldestroy_bl(m);
   }
   return;
}
