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
/* $Id: ctmisc_view_d.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void ctmisc_view_d(void){
   printf("********\nTEST ctmisc_view_d\n");
   {
      vsip_index k,j,i;
/* if a problem with tcreate is suspected check both leading and trailing options here */
   
      vsip_scalar_d data_r[4][3][4]  = 
                           { {{0.0, 0.01, 0.02, 0.03}, \
                             { 0.1, 0.11, 0.12, 0.13}, \
                             { 0.2, 0.21, 0.22, 0.23}},{ \
                             { 1.0, 1.01, 1.02, 1.03}, \
                             { 1.1, 1.11, 1.12, 1.13}, \
                             { 1.2, 1.21, 1.22, 1.23}},{ \
                             { 2.0, 2.01, 2.02, 2.03}, \
                             { 2.1, 2.11, 2.12, 2.13}, \
                             { 2.2, 2.21, 2.22, 2.23}},{ \
                             { 3.0, 3.01, 3.02, 3.03}, \
                             { 3.1, 3.11, 3.12, 3.13}, \
                             { 3.2, 3.21, 3.22, 3.23}}};
   
      vsip_scalar_d data_i[4][3][4]  = 
                            { {{0.0, -0.01, -0.02, -0.03}, \
                              {-0.1, -0.11, -0.12, -0.13}, \
                              {-0.2, -0.21, -0.22, -0.23}},{ \
                              {-1.0, -1.01, -1.02, -1.03}, \
                              {-1.1, -1.11, -1.12, -1.13}, \
                              {-1.2, -1.21, -1.22, -1.23}},{ \
                              {-2.0, -2.01, -2.02, -2.03}, \
                              {-2.1, -2.11, -2.12, -2.13}, \
                              {-2.2, -2.21, -2.22, -2.23}},{ \
                              {-3.0, -3.01, -3.02, -3.03}, \
                              {-3.1, -3.11, -3.12, -3.13}, 
                              {-3.2, -3.21, -3.22, -3.23}}};

       vsip_ctview_d *tview_a = vsip_ctcreate_d(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
/*     vsip_ctview_d *tview_a = vsip_ctcreate_d(12,9,12,VSIP_TRAILING,VSIP_MEM_NONE); */
       vsip_cblock_d *block_a = vsip_ctgetblock_d(tview_a);
       vsip_ctview_d *tview_b = vsip_ctsubview_d(tview_a,1,2,3,4,3,4);
   
       vsip_stride z_a_st = vsip_ctgetzstride_d(tview_a);
       vsip_stride y_a_st = vsip_ctgetystride_d(tview_a);
       vsip_stride x_a_st = vsip_ctgetxstride_d(tview_a);
   
       vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
       vsip_offset b_o_get  = vsip_ctgetoffset_d(tview_b);
   
       vsip_ctview_d *v = vsip_ctbind_d(block_a,b_o_calc,
                                               z_a_st,4,
                                               y_a_st,3,
                                               x_a_st,4);
   
       vsip_cmview_d *mview = (vsip_cmview_d*)NULL;
       vsip_cvview_d *vview = (vsip_cvview_d*)NULL;
       vsip_ctview_d *tview = (vsip_ctview_d*)NULL;
       vsip_cscalar_d a;
       vsip_scalar_d chk = 0;
   
       printf("z_a_st %d; y_a_st %d; x_a_st %d\n",(int)z_a_st,(int)y_a_st,(int)x_a_st); fflush(stdout);
       printf("b_o_calc %u; b_o_get %u\n",(unsigned)b_o_calc,(unsigned)b_o_get); fflush(stdout);
       for(k = 0; k < 4; k++){
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a.r = data_r[k][j][i]; a.i = data_i[k][j][i];
                vsip_ctput_d(v,k,j,i,a);
             }
          }
       }
   
       printf("test ctmatrixview_d\n"); 
       printf("TMZY\n"); fflush(stdout);
       for(i = 0; i < 4; i++){
          mview  = vsip_ctmatrixview_d(v,VSIP_TMZY,i);
          for(j = 0; j < 3; j++){
             for(k = 0; k < 4; k++){
                a = vsip_cmget_d(mview,k,j);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
          vsip_cmdestroy_d(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMYX\n"); fflush(stdout);
       for(k = 0; k < 4; k++){
          mview  = vsip_ctmatrixview_d(v,VSIP_TMYX,k);
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = vsip_cmget_d(mview,j,i);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
          vsip_cmdestroy_d(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMZX\n"); fflush(stdout);
       for(j = 0; j < 3; j++){
          mview  = vsip_ctmatrixview_d(v,VSIP_TMZX,j);
          for(k = 0; k < 4; k++){
             for(i = 0; i < 4; i++){
                a = vsip_cmget_d(mview,k,i);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
          vsip_cmdestroy_d(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test ctvectview_d\n"); 
       printf("TVX \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             vview = vsip_ctvectview_d(v,VSIP_TVX,k,j);
             for(i=0; i<4; i++){
                a = vsip_cvget_d(vview,i);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
          vsip_cvdestroy_d(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test ctvectview_d\n"); 
       printf("TVY \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(i=0; i<4; i++){
             vview = vsip_ctvectview_d(v,VSIP_TVY,k,i);
             for(j=0; j<3; j++){
                a = vsip_cvget_d(vview,j);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
          vsip_cvdestroy_d(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TVZ \n"); fflush(stdout);
       for(j=0; j<3; j++){
          for(i=0; i<4; i++){
             vview = vsip_ctvectview_d(v,VSIP_TVZ,j,i);
             for(k=0; k<4; k++){
                a = vsip_cvget_d(vview,k);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
          vsip_cvdestroy_d(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test cttransview_d\n"); fflush(stdout);
       
       printf("NOP\n"); fflush(stdout);
       tview   = vsip_cttransview_d(v,VSIP_TTRANS_NOP);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_ctget_d(tview,k,j,i);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
       }
       vsip_ctdestroy_d(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YX\n"); fflush(stdout);
       tview   = vsip_cttransview_d(v,VSIP_TTRANS_YX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_ctget_d(tview,k,i,j);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
       }
       vsip_ctdestroy_d(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZY\n"); fflush(stdout);
       tview   = vsip_cttransview_d(v,VSIP_TTRANS_ZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_ctget_d(tview,j,k,i);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
       }
       vsip_ctdestroy_d(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZX\n"); fflush(stdout);
       tview   = vsip_cttransview_d(v,VSIP_TTRANS_ZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_ctget_d(tview,i,j,k);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
       }
       vsip_ctdestroy_d(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZY\n"); fflush(stdout);
       tview   = vsip_cttransview_d(v,VSIP_TTRANS_YXZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_ctget_d(tview,i,k,j);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
       }
       vsip_ctdestroy_d(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZX\n"); fflush(stdout);
       tview   = vsip_cttransview_d(v,VSIP_TTRANS_YXZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_ctget_d(tview,j,i,k);
                a.r -= data_r[k][j][i]; a.i -= data_i[k][j][i];
                chk += a.r * a.r + a.i * a.i;
             }
          }
       }
       vsip_ctdestroy_d(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       vsip_ctdestroy_d(v);
       vsip_ctdestroy_d(tview_b);
       vsip_ctalldestroy_d(tview_a);
   }
   return;
}
