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
/* $Id: tmisc_view_si.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void tmisc_view_si(void){
   printf("********\nTEST tmisc_view_si\n");
   {
      vsip_index k,j,i;
      vsip_scalar_si data_r[4][3][4]  = {{{00, 001, 002, 003}, \
                                          {01, 011, 012, 013}, \
                                          {02, 021, 022, 023}}, \
                                         {{10, 101, 102, 103}, \
                                          {11, 111, 112, 113}, \
                                          {12, 121, 122, 123}}, \
                                         {{20, 201, 202, 203}, \
                                          {21, 211, 212, 213}, \
                                          {22, 221, 222, 223}}, \
                                         {{30, 301, 302, 303}, \
                                          {31, 311, 312, 313}, \
                                          {32, 321, 322, 323}}};
   
/* if a problem with tcreate is suspected check both leading and trailing options here */
       vsip_tview_si *tview_a = vsip_tcreate_si(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
/*     vsip_tview_si *tview_a = vsip_tcreate_si(12,9,12,VSIP_TRAILING,VSIP_MEM_NONE); */
       vsip_block_si *block_a = vsip_tgetblock_si(tview_a);
       vsip_tview_si *tview_b = vsip_tsubview_si(tview_a,1,2,3,4,3,4);
   
       vsip_stride z_a_st = vsip_tgetzstride_si(tview_a);
       vsip_stride y_a_st = vsip_tgetystride_si(tview_a);
       vsip_stride x_a_st = vsip_tgetxstride_si(tview_a);
   
       vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
       vsip_offset b_o_get  = vsip_tgetoffset_si(tview_b);
   
       vsip_tview_si *v = vsip_tbind_si(block_a,b_o_calc,
                                               z_a_st,4,
                                               y_a_st,3,
                                               x_a_st,4);
   
       vsip_mview_si *mview = (vsip_mview_si*)NULL;
       vsip_vview_si *vview = (vsip_vview_si*)NULL;
       vsip_tview_si *tview = (vsip_tview_si*)NULL;
       vsip_scalar_si a;
       int chk = 0;
   
       printf("z_a_st %d; y_a_st %d; x_a_st %d\n",(int)z_a_st,(int)y_a_st,(int)x_a_st); fflush(stdout);
       printf("b_o_calc %ul; b_o_get %ul\n",(unsigned)b_o_calc,(unsigned)b_o_get); fflush(stdout);
       for(k = 0; k < 4; k++){
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = data_r[k][j][i];
                vsip_tput_si(v,k,j,i,a);
             }
          }
       }
   
       printf("test tmatrixview_si\n"); 
       printf("TMZY\n"); fflush(stdout);
       for(i = 0; i < 4; i++){
          mview  = vsip_tmatrixview_si(v,VSIP_TMZY,i);
          for(j = 0; j < 3; j++){
             for(k = 0; k < 4; k++){
                a = vsip_mget_si(mview,k,j);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_si(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMYX\n"); fflush(stdout);
       for(k = 0; k < 4; k++){
          mview  = vsip_tmatrixview_si(v,VSIP_TMYX,k);
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = vsip_mget_si(mview,j,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_si(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMZX\n"); fflush(stdout);
       for(j = 0; j < 3; j++){
          mview  = vsip_tmatrixview_si(v,VSIP_TMZX,j);
          for(k = 0; k < 4; k++){
             for(i = 0; i < 4; i++){
                a = vsip_mget_si(mview,k,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_si(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test tvectview_si\n"); 
       printf("TVX \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             vview = vsip_tvectview_si(v,VSIP_TVX,k,j);
             for(i=0; i<4; i++){
                a = vsip_vget_si(vview,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_vdestroy_si(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test tvectview_si\n"); 
       printf("TVY \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(i=0; i<4; i++){
             vview = vsip_tvectview_si(v,VSIP_TVY,k,i);
             for(j=0; j<3; j++){
                a = vsip_vget_si(vview,j);
                a -= data_r[k][j][i]; 
                chk += a * a ;
             }
          }
          vsip_vdestroy_si(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TVZ \n"); fflush(stdout);
       for(j=0; j<3; j++){
          for(i=0; i<4; i++){
             vview = vsip_tvectview_si(v,VSIP_TVZ,j,i);
             for(k=0; k<4; k++){
                a = vsip_vget_si(vview,k);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_vdestroy_si(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test ttransview_si\n"); fflush(stdout);
       
       printf("NOP\n"); fflush(stdout);
       tview   = vsip_ttransview_si(v,VSIP_TTRANS_NOP);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_si(tview,k,j,i);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_si(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YX\n"); fflush(stdout);
       tview   = vsip_ttransview_si(v,VSIP_TTRANS_YX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_si(tview,k,i,j);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_si(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZY\n"); fflush(stdout);
       tview   = vsip_ttransview_si(v,VSIP_TTRANS_ZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_si(tview,j,k,i);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_si(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZX\n"); fflush(stdout);
       tview   = vsip_ttransview_si(v,VSIP_TTRANS_ZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_si(tview,i,j,k);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_si(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZY\n"); fflush(stdout);
       tview   = vsip_ttransview_si(v,VSIP_TTRANS_YXZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_si(tview,i,k,j);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_si(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZX\n"); fflush(stdout);
       tview   = vsip_ttransview_si(v,VSIP_TTRANS_YXZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_si(tview,j,i,k);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_si(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       vsip_tdestroy_si(v);
       vsip_tdestroy_si(tview_b);
       vsip_talldestroy_si(tview_a);
   }
   return;
}
