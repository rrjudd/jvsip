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
/* $Id: get_put_attrib_f.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void get_put_attrib_f(void){
   printf("********\nTEST get_put_attrib_f\n");
   {
       vsip_offset ivo = 3, icvo=10; 
       vsip_stride ivs = 2, icvs=-1;
       vsip_length ivl = 3, icvl=4;
       vsip_offset jvo = 2, jcvo=0; 
       vsip_stride jvs = 3, jcvs=1;
       vsip_length jvl = 5, jcvl=7;

       vsip_stride irs = 1, ics = 3; 
       vsip_length irl = 2, icl = 3;
       vsip_stride jrs = 5, jcs = 2; 
       vsip_length jrl = 5, jcl = 2;
       
       vsip_stride ixs = 2, iys = 4, izs = 14;
       vsip_length ixl = 2, iyl = 3, izl = 4;
       vsip_stride jxs = 4, jys = 14, jzs = 2;
       vsip_length jxl = 3, jyl = 4, jzl = 2;

       vsip_block_f *b = vsip_blockcreate_f(80,VSIP_MEM_NONE);
       vsip_cblock_f *cb = vsip_cblockcreate_f(80,VSIP_MEM_NONE);
       vsip_vview_f *v = vsip_vbind_f(b,ivo,ivs,ivl);
       vsip_mview_f *m = vsip_mbind_f(b,ivo,ics,icl,irs,irl);
       vsip_tview_f *t = vsip_tbind_f(b,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_cvview_f *cv = vsip_cvbind_f(cb,icvo,icvs,icvl);
       vsip_cmview_f *cm = vsip_cmbind_f(cb,ivo,ics,icl,irs,irl);
       vsip_ctview_f *ct = vsip_ctbind_f(cb,ivo,izs,izl,iys,iyl,ixs,ixl);
       vsip_vattr_f  attr;
       vsip_cvattr_f cattr;
       vsip_mattr_f  mattr;
       vsip_cmattr_f cmattr;
       vsip_tattr_f  tattr;
       vsip_ctattr_f ctattr;
       
       printf("test vgetattrib_f\n"); fflush(stdout);
       {
          vsip_vgetattrib_f(v,&attr);
          (attr.offset == ivo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == ivs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == ivl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputattrib_f\n"); fflush(stdout);
       {
          attr.offset = jvo; attr.stride = jvs; attr.length = jvl;
          vsip_vputattrib_f(v,&attr);
          vsip_vgetattrib_f(v,&attr);
          (attr.offset == jvo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == jvs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == jvl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       

       printf("test cvgetattrib_f\n"); fflush(stdout);
       {
          vsip_cvgetattrib_f(cv,&cattr);
          (cattr.offset == icvo) ? printf("offset correct\n") : 
                                   printf("offset error \n");
          (cattr.stride == icvs) ? printf("stride correct\n") :
                                   printf("stride error \n");
          (cattr.length == icvl) ? printf("length correct\n") :
                                   printf("length error \n");
          fflush(stdout);
       }  
       /* the next test requires the previous test to be correct */
       printf("test cvputattrib_f\n"); fflush(stdout);
       {  
          cattr.offset = jcvo; cattr.stride = jcvs; cattr.length = jcvl;
          vsip_cvputattrib_f(cv,&cattr);
          vsip_cvgetattrib_f(cv,&cattr);
          (cattr.offset == jcvo) ? printf("offset correct\n") :
                                   printf("offset error \n"); 
          (cattr.stride == jcvs) ? printf("stride correct\n") :
                                   printf("stride error \n"); 
          (cattr.length == jcvl) ? printf("length correct\n") :
                                   printf("length error \n");
          fflush(stdout);
       }
/**************************************************************************/
       printf("test mgetattrib_f\n"); fflush(stdout);
       {
          vsip_mgetattrib_f(m,&mattr);
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
       printf("test mputattrib_f\n"); fflush(stdout);
       {
          mattr.offset = jvo; mattr.col_stride = jcs; mattr.col_length = jcl;
                              mattr.row_stride = jrs; mattr.row_length = jrl;
          vsip_mputattrib_f(m,&mattr);
          vsip_mgetattrib_f(m,&mattr);
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

       printf("test cmgetattrib_f\n"); fflush(stdout);
       {
          vsip_cmgetattrib_f(cm,&cmattr);
          (cmattr.offset == ivo) ? printf("offset correct\n") : 
                                   printf("offset error \n");
          (cmattr.col_stride == ics) ? printf("col_stride correct\n") :
                                      printf("col_stride error \n");
          (cmattr.col_length == icl) ? printf("col_length correct\n") :
                                      printf("col_length error \n");
          (cmattr.row_stride == irs) ? printf("row_stride correct\n") :
                                      printf("row_stride error \n");
          (cmattr.row_length == irl) ? printf("row_length correct\n") :
                                      printf("row_length error \n");
          fflush(stdout);
       }  
       /* the next test requires the previous test to be correct */
       printf("test cmputattrib_f\n"); fflush(stdout);
       {  
          cmattr.offset = jvo; cmattr.col_stride = jcs; cmattr.col_length = jcl;
                               cmattr.row_stride = jrs; cmattr.row_length = jrl;
          vsip_cmputattrib_f(cm,&cmattr);
          vsip_cmgetattrib_f(cm,&cmattr);
          (cmattr.offset == jvo) ? printf("offset correct\n") :
                                   printf("offset error \n");
          (cmattr.col_stride == jcs) ? printf("col_stride correct\n") :
                                      printf("col_stride error \n");
          (cmattr.col_length == jcl) ? printf("col_length correct\n") :
                                      printf("col_length error \n");
          (cmattr.row_stride == jrs) ? printf("row_stride correct\n") :
                                      printf("row_stride error \n");
          (cmattr.row_length == jrl) ? printf("row_length correct\n") :
                                      printf("row_length error \n");
          fflush(stdout);
       }
/**************************************************************************/
       printf("test tgetattrib_f\n"); fflush(stdout);
       {
          vsip_tgetattrib_f(t,&tattr);
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
       printf("test tputattrib_f\n"); fflush(stdout);
       {
          tattr.offset = jvo; tattr.z_stride = jzs; tattr.z_length = jzl;
                              tattr.y_stride = jys; tattr.y_length = jyl;
                              tattr.x_stride = jxs; tattr.x_length = jxl;
          vsip_tputattrib_f(t,&tattr);
          vsip_tgetattrib_f(t,&tattr);
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

       printf("test ctgetattrib_f\n"); fflush(stdout);
       {
          vsip_ctgetattrib_f(ct,&ctattr);
          (ctattr.offset == ivo) ? printf("offset correct\n") :
                                  printf("offset error \n");
          (ctattr.z_stride == izs) ? printf("z_stride correct\n") :
                                    printf("z_stride error \n");
          (ctattr.z_length == izl) ? printf("z_length correct\n") :
                                    printf("z_length error \n");
          (ctattr.y_stride == iys) ? printf("y_stride correct\n") :
                                    printf("y_stride error \n");
          (ctattr.y_length == iyl) ? printf("y_length correct\n") :
                                    printf("y_length error \n");
          (ctattr.x_stride == ixs) ? printf("x_stride correct\n") :
                                    printf("x_stride error \n");
          (ctattr.x_length == ixl) ? printf("x_length correct\n") :
                                    printf("x_length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test ctputattrib_f\n"); fflush(stdout);
       {
          ctattr.offset = jvo; ctattr.z_stride = jzs; ctattr.z_length = jzl;
                               ctattr.y_stride = jys; ctattr.y_length = jyl;
                               ctattr.x_stride = jxs; ctattr.x_length = jxl;
          vsip_ctputattrib_f(ct,&ctattr);
          vsip_ctgetattrib_f(ct,&ctattr);
          (ctattr.offset == jvo) ? printf("offset correct\n") :
                                  printf("offset error \n");
          (ctattr.z_stride == jzs) ? printf("z_stride correct\n") :
                                    printf("z_stride error \n");
          (ctattr.z_length == jzl) ? printf("z_length correct\n") :
                                    printf("z_length error \n");
          (ctattr.y_stride == jys) ? printf("y_stride correct\n") :
                                    printf("y_stride error \n");
          (ctattr.y_length == jyl) ? printf("y_length correct\n") :
                                    printf("y_length error \n");
          (ctattr.x_stride == jxs) ? printf("x_stride correct\n") :
                                    printf("x_stride error \n");
          (ctattr.x_length == jxl) ? printf("x_length correct\n") :
                                    printf("x_length error \n");
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
