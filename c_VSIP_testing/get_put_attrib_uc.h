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
/* $Id: get_put_attrib_uc.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void get_put_attrib_uc(void){
   printf("********\nTEST get_put_attrib_uc\n");
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
       
       vsip_stride ixs = 2, iys = 4, izs = 14;
       vsip_length ixl = 2, iyl = 3, izl = 4;
       vsip_stride jxs = 4, jys = 14, jzs = 2;
       vsip_length jxl = 3, jyl = 4, jzl = 2;

       vsip_block_uc *b = vsip_blockcreate_uc(80,VSIP_MEM_NONE);
       vsip_vview_uc *v = vsip_vbind_uc(b,ivo,ivs,ivl);
       vsip_mview_uc *m = vsip_mbind_uc(b,ivo,ics,icl,irs,irl);
       vsip_tview_uc *t = vsip_tbind_uc(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_vattr_uc  attr;
       vsip_mattr_uc  mattr;
       vsip_tattr_uc  tattr;
       
       printf("test vgetattrib_uc\n"); fflush(stdout);
       {
          vsip_vgetattrib_uc(v,&attr);
          (attr.offset == ivo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == ivs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == ivl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputattrib_uc\n"); fflush(stdout);
       {
          attr.offset = jvo; attr.stride = jvs; attr.length = jvl;
          vsip_vputattrib_uc(v,&attr);
          vsip_vgetattrib_uc(v,&attr);
          (attr.offset == jvo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == jvs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == jvl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       

/**************************************************************************/
       printf("test mgetattrib_uc\n"); fflush(stdout);
       {
          vsip_mgetattrib_uc(m,&mattr);
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
       printf("test mputattrib_uc\n"); fflush(stdout);
       {
          mattr.offset = jvo; mattr.col_stride = jcs; mattr.col_length = jcl;
                              mattr.row_stride = jrs; mattr.row_length = jrl;
          vsip_mputattrib_uc(m,&mattr);
          vsip_mgetattrib_uc(m,&mattr);
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
/**************************************************************************/
       printf("test tgetattrib_uc\n"); fflush(stdout);
       {
          vsip_tgetattrib_uc(t,&tattr);
          (tattr.offset == ivo) ? printf("offset correct\n") : 
                                  printf("offset error \n");
          (tattr.z_stride == izs) ? printf("z_stride correct\n") : 
                                    printf("z_stride error \n");
          (tattr.z_length == izl) ? printf("z_length correct\n") : 
                                    printf("z_length error \n");
          (tattr.y_stride == iys) ? printf("y_stride correct\n") : 
                                    printf("y_stride error \n");
          (tattr.y_length == iyl) ? printf("y_length correct\n") : 
                                    printf("y_length error \n");
          (tattr.x_stride == ixs) ? printf("x_stride correct\n") : 
                                    printf("x_stride error \n");
          (tattr.x_length == ixl) ? printf("x_length correct\n") : 
                                    printf("x_length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test tputattrib_uc\n"); fflush(stdout);
       {
          tattr.offset = jvo; tattr.z_stride = jzs; tattr.z_length = jzl;
                              tattr.y_stride = jys; tattr.y_length = jyl;
                              tattr.x_stride = jxs; tattr.x_length = jxl;
          vsip_tputattrib_uc(t,&tattr);
          vsip_tgetattrib_uc(t,&tattr);
          (tattr.offset == jvo) ? printf("offset correct\n") : 
                                  printf("offset error \n");
          (tattr.z_stride == jzs) ? printf("z_stride correct\n") :
                                    printf("z_stride error \n");
          (tattr.z_length == jzl) ? printf("z_length correct\n") :
                                    printf("z_length error \n");
          (tattr.y_stride == jys) ? printf("y_stride correct\n") :
                                    printf("y_stride error \n");
          (tattr.y_length == jyl) ? printf("y_length correct\n") :
                                    printf("y_length error \n");
          (tattr.x_stride == jxs) ? printf("x_stride correct\n") :
                                    printf("x_stride error \n");
          (tattr.x_length == jxl) ? printf("x_length correct\n") :
                                    printf("x_length error \n");
          fflush(stdout);
       }       
       vsip_vdestroy_uc(v);
       vsip_mdestroy_uc(m);
       vsip_talldestroy_uc(t);
   }
   return;
}
