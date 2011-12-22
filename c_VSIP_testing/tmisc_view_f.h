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
/* $Id: tmisc_view_f.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void tmisc_view_f(void){
   printf("********\nTEST tmisc_view_f\n");
   {
      vsip_index k,j,i;
      vsip_scalar_f data_r[4][3][4]  = {{{0.0, 0.01, 0.02, 0.03}, \
                                         {0.1, 0.11, 0.12, 0.13}, \
                                         {0.2, 0.21, 0.22, 0.23}}, \
                                        {{1.0, 1.01, 1.02, 1.03}, \
                                         {1.1, 1.11, 1.12, 1.13}, \
                                         {1.2, 1.21, 1.22, 1.23}}, \
                                        {{2.0, 2.01, 2.02, 2.03}, \
                                         {2.1, 2.11, 2.12, 2.13}, \
                                         {2.2, 2.21, 2.22, 2.23}}, \
                                        {{3.0, 3.01, 3.02, 3.03}, \
                                         {3.1, 3.11, 3.12, 3.13}, \
                                         {3.2, 3.21, 3.22, 3.23}}};
   
/* if a problem with tcreate is suspected check both leading and trailing options here */
       vsip_tview_f *tview_a = vsip_tcreate_f(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
/*     vsip_tview_f *tview_a = vsip_tcreate_f(12,9,12,VSIP_TRAILING,VSIP_MEM_NONE); */
       vsip_block_f *block_a = vsip_tgetblock_f(tview_a);
       vsip_tview_f *tview_b = vsip_tsubview_f(tview_a,1,2,3,4,3,4);
   
       vsip_stride z_a_st = vsip_tgetzstride_f(tview_a);
       vsip_stride y_a_st = vsip_tgetystride_f(tview_a);
       vsip_stride x_a_st = vsip_tgetxstride_f(tview_a);
   
       vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
       vsip_offset b_o_get  = vsip_tgetoffset_f(tview_b);
   
       vsip_tview_f *v = vsip_tbind_f(block_a,b_o_calc,
                                               z_a_st,4,
                                               y_a_st,3,
                                               x_a_st,4);
   
       vsip_mview_f *mview = (vsip_mview_f*)NULL;
       vsip_vview_f *vview = (vsip_vview_f*)NULL;
       vsip_tview_f *tview = (vsip_tview_f*)NULL;
       vsip_scalar_f a;
       vsip_scalar_f chk = 0;
   
       printf("z_a_st %d; y_a_st %d; x_a_st %d\n",(int)z_a_st,(int)y_a_st,(int)x_a_st); fflush(stdout);
       printf("b_o_calc %u; b_o_get %u\n",(unsigned)b_o_calc,(unsigned)b_o_get); fflush(stdout);
       for(k = 0; k < 4; k++){
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = data_r[k][j][i];
                vsip_tput_f(v,k,j,i,a);
             }
          }
       }
   
       printf("test tmatrixview_f\n"); 
       printf("TMZY\n"); fflush(stdout);
       for(i = 0; i < 4; i++){
          mview  = vsip_tmatrixview_f(v,VSIP_TMZY,i);
          for(j = 0; j < 3; j++){
             for(k = 0; k < 4; k++){
                a = vsip_mget_f(mview,k,j);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_f(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMYX\n"); fflush(stdout);
       for(k = 0; k < 4; k++){
          mview  = vsip_tmatrixview_f(v,VSIP_TMYX,k);
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = vsip_mget_f(mview,j,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_f(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMZX\n"); fflush(stdout);
       for(j = 0; j < 3; j++){
          mview  = vsip_tmatrixview_f(v,VSIP_TMZX,j);
          for(k = 0; k < 4; k++){
             for(i = 0; i < 4; i++){
                a = vsip_mget_f(mview,k,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_f(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test tvectview_f\n"); 
       printf("TVX \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             vview = vsip_tvectview_f(v,VSIP_TVX,k,j);
             for(i=0; i<4; i++){
                a = vsip_vget_f(vview,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_vdestroy_f(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test tvectview_f\n"); 
       printf("TVY \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(i=0; i<4; i++){
             vview = vsip_tvectview_f(v,VSIP_TVY,k,i);
             for(j=0; j<3; j++){
                a = vsip_vget_f(vview,j);
                a -= data_r[k][j][i]; 
                chk += a * a ;
             }
          }
          vsip_vdestroy_f(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TVZ \n"); fflush(stdout);
       for(j=0; j<3; j++){
          for(i=0; i<4; i++){
             vview = vsip_tvectview_f(v,VSIP_TVZ,j,i);
             for(k=0; k<4; k++){
                a = vsip_vget_f(vview,k);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_vdestroy_f(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test ttransview_f\n"); fflush(stdout);
       
       printf("NOP\n"); fflush(stdout);
       tview   = vsip_ttransview_f(v,VSIP_TTRANS_NOP);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_f(tview,k,j,i);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_f(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YX\n"); fflush(stdout);
       tview   = vsip_ttransview_f(v,VSIP_TTRANS_YX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_f(tview,k,i,j);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_f(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZY\n"); fflush(stdout);
       tview   = vsip_ttransview_f(v,VSIP_TTRANS_ZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_f(tview,j,k,i);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_f(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZX\n"); fflush(stdout);
       tview   = vsip_ttransview_f(v,VSIP_TTRANS_ZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_f(tview,i,j,k);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_f(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZY\n"); fflush(stdout);
       tview   = vsip_ttransview_f(v,VSIP_TTRANS_YXZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_f(tview,i,k,j);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_f(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZX\n"); fflush(stdout);
       tview   = vsip_ttransview_f(v,VSIP_TTRANS_YXZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_f(tview,j,i,k);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_f(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       vsip_tdestroy_f(v);
       vsip_tdestroy_f(tview_b);
       vsip_talldestroy_f(tview_a);
   }
   return;
}
