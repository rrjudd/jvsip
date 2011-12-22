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
/* $Id: tmisc_view_i.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void tmisc_view_i(void){
   printf("********\nTEST tmisc_view_i\n");
   {
      vsip_index k,j,i;
      vsip_scalar_i data_r[4][3][4]  = {{{0, 001, 002, 003}, \
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
       vsip_tview_i *tview_a = vsip_tcreate_i(12,9,12,VSIP_LEADING,VSIP_MEM_NONE);
/*     vsip_tview_i *tview_a = vsip_tcreate_i(12,9,12,VSIP_TRAILING,VSIP_MEM_NONE); */
       vsip_block_i *block_a = vsip_tgetblock_i(tview_a);
       vsip_tview_i *tview_b = vsip_tsubview_i(tview_a,1,2,3,4,3,4);
   
       vsip_stride z_a_st = vsip_tgetzstride_i(tview_a);
       vsip_stride y_a_st = vsip_tgetystride_i(tview_a);
       vsip_stride x_a_st = vsip_tgetxstride_i(tview_a);
   
       vsip_offset b_o_calc = z_a_st + 2 * y_a_st + 3 * x_a_st;
       vsip_offset b_o_get  = vsip_tgetoffset_i(tview_b);
   
       vsip_tview_i *v = vsip_tbind_i(block_a,b_o_calc,
                                               z_a_st,4,
                                               y_a_st,3,
                                               x_a_st,4);
   
       vsip_mview_i *mview = (vsip_mview_i*)NULL;
       vsip_vview_i *vview = (vsip_vview_i*)NULL;
       vsip_tview_i *tview = (vsip_tview_i*)NULL;
       vsip_scalar_i a;
       int chk = 0;
   
       printf("z_a_st %d; y_a_st %d; x_a_st %d\n",(int)z_a_st,(int)y_a_st,(int)x_a_st); fflush(stdout);
       printf("b_o_calc %u; b_o_get %u\n",(unsigned)b_o_calc,(unsigned)b_o_get); fflush(stdout);
       for(k = 0; k < 4; k++){
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = data_r[k][j][i];
                vsip_tput_i(v,k,j,i,a);
             }
          }
       }
   
       printf("test tmatrixview_i\n"); 
       printf("TMZY\n"); fflush(stdout);
       for(i = 0; i < 4; i++){
          mview  = vsip_tmatrixview_i(v,VSIP_TMZY,i);
          for(j = 0; j < 3; j++){
             for(k = 0; k < 4; k++){
                a = vsip_mget_i(mview,k,j);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_i(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMYX\n"); fflush(stdout);
       for(k = 0; k < 4; k++){
          mview  = vsip_tmatrixview_i(v,VSIP_TMYX,k);
          for(j = 0; j < 3; j++){
             for(i = 0; i < 4; i++){
                a = vsip_mget_i(mview,j,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_i(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TMZX\n"); fflush(stdout);
       for(j = 0; j < 3; j++){
          mview  = vsip_tmatrixview_i(v,VSIP_TMZX,j);
          for(k = 0; k < 4; k++){
             for(i = 0; i < 4; i++){
                a = vsip_mget_i(mview,k,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_mdestroy_i(mview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test tvectview_i\n"); 
       printf("TVX \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             vview = vsip_tvectview_i(v,VSIP_TVX,k,j);
             for(i=0; i<4; i++){
                a = vsip_vget_i(vview,i);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_vdestroy_i(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test tvectview_i\n"); 
       printf("TVY \n"); fflush(stdout);
       for(k=0; k<4; k++){
          for(i=0; i<4; i++){
             vview = vsip_tvectview_i(v,VSIP_TVY,k,i);
             for(j=0; j<3; j++){
                a = vsip_vget_i(vview,j);
                a -= data_r[k][j][i]; 
                chk += a * a ;
             }
          }
          vsip_vdestroy_i(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("TVZ \n"); fflush(stdout);
       for(j=0; j<3; j++){
          for(i=0; i<4; i++){
             vview = vsip_tvectview_i(v,VSIP_TVZ,j,i);
             for(k=0; k<4; k++){
                a = vsip_vget_i(vview,k);
                a -= data_r[k][j][i]; 
                chk += a * a;
             }
          }
          vsip_vdestroy_i(vview);
       }
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("test ttransview_i\n"); fflush(stdout);
       
       printf("NOP\n"); fflush(stdout);
       tview   = vsip_ttransview_i(v,VSIP_TTRANS_NOP);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_i(tview,k,j,i);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_i(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YX\n"); fflush(stdout);
       tview   = vsip_ttransview_i(v,VSIP_TTRANS_YX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_i(tview,k,i,j);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_i(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZY\n"); fflush(stdout);
       tview   = vsip_ttransview_i(v,VSIP_TTRANS_ZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_i(tview,j,k,i);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_i(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("ZX\n"); fflush(stdout);
       tview   = vsip_ttransview_i(v,VSIP_TTRANS_ZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_i(tview,i,j,k);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_i(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZY\n"); fflush(stdout);
       tview   = vsip_ttransview_i(v,VSIP_TTRANS_YXZY);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_i(tview,i,k,j);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_i(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       printf("YXZX\n"); fflush(stdout);
       tview   = vsip_ttransview_i(v,VSIP_TTRANS_YXZX);
       for(k=0; k<4; k++){
          for(j=0; j<3; j++){
             for(i=0; i<4; i++){
                a = vsip_tget_i(tview,j,i,k);
                a -= data_r[k][j][i];
                chk += a * a;
             }
          }
       }
       vsip_tdestroy_i(tview);
       (chk > .0001) ? printf("error\n") : printf("correct\n"); fflush(stdout);
        chk = 0;

       vsip_tdestroy_i(v);
       vsip_tdestroy_i(tview_b);
       vsip_talldestroy_i(tview_a);
   }
   return;
}
