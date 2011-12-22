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
/* $Id: get_put_attrib_bl.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void get_put_attrib_bl(void){
   printf("********\nTEST get_put_attrib_bl\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 2;
       vsip_length ivl = 3;
       vsip_offset jvo = 2;
       vsip_stride jvs = 3;
       vsip_length jvl = 5;
       vsip_stride irs = 1, ics = 3;
       vsip_length irl = 2, icl = 3;
       vsip_stride jrs = 5, jcs = 2;
       vsip_length jrl = 5, jcl = 2;

       vsip_block_bl *b = vsip_blockcreate_bl(80,VSIP_MEM_NONE);
       vsip_vview_bl *v = vsip_vbind_bl(b,ivo,ivs,ivl);
       vsip_mview_bl *m = vsip_mbind_bl(b,ivo,ics,icl,irs,irl);
       vsip_vattr_bl  attr;
       vsip_mattr_bl mattr;
       
       printf("test vgetattrib_bl\n"); fflush(stdout);
       {
          vsip_vgetattrib_bl(v,&attr);
          (attr.offset == ivo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == ivs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == ivl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputattrib_bl\n"); fflush(stdout);
       {
          attr.offset = jvo; attr.stride = jvs; attr.length = jvl;
          vsip_vputattrib_bl(v,&attr);
          vsip_vgetattrib_bl(v,&attr);
          (attr.offset == jvo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == jvs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == jvl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       

       printf("test mgetattrib_bl\n"); fflush(stdout);
       {
          vsip_mgetattrib_bl(m,&mattr);
          (mattr.offset == ivo) ?     printf("offset correct\n") :
                                     printf("offset error \n");
          (mattr.col_stride == ics) ? printf("col_stride correct\n") :
                                     printf("col_stride error \n");
          (mattr.row_stride == irs) ? printf("row_stride correct\n") :
                                     printf("row_stride error \n");
          (mattr.col_length == icl) ? printf("col_length correct\n") :
                                     printf("col_length error \n");
          (mattr.row_length == irl) ? printf("row_length correct\n") :
                                     printf("row_length error \n");
          fflush(stdout);
       }
       /* the next test requires the previous test to be correct */
       printf("test mputattrib_bl\n"); fflush(stdout);
       {
          mattr.offset = jvo; mattr.col_stride = jcs; mattr.col_length = jcl;
                              mattr.row_stride = jrs; mattr.row_length = jrl;
          vsip_mputattrib_bl(m,&mattr);
          vsip_mgetattrib_bl(m,&mattr);
          (mattr.offset == jvo) ? printf("offset correct\n") :
                                 printf("offset error \n");
          (mattr.col_stride == jcs) ? printf("col_stride correct\n") :
                                     printf("col_stride error \n");
          (mattr.col_length == jcl) ? printf("col_length correct\n") :
                                     printf("col_length error \n");
          (mattr.row_stride == jrs) ? printf("row_stride correct\n") :
                                     printf("row_stride error \n");
          (mattr.row_length == jrl) ? printf("row_length correct\n") :
                                     printf("row_length error \n");
          fflush(stdout);
       }
       vsip_vdestroy_bl(v);
       vsip_malldestroy_bl(m);
   }
   return;
}
