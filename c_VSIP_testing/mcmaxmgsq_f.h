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
/* $Id: mcmaxmgsq_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
#include"VU_mprintm_f.include"
#include"VU_cmprintm_f.include"
static void mcmaxmgsq_f(void){
    printf("\n******\nTEST mcmaxmgsq_f\n");
    {
        vsip_scalar_f data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_f data2_r[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_f data2_i[]= {-1.1, 2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9};
        vsip_scalar_f ans[] =  { 2.42, 38.72, 118.58, 16.01, 60.50, 154.88, 49.64, 87.12, 196.02};
        vsip_cmview_f *m1 = vsip_cmbind_f(
                  vsip_cblockbind_f(data1,NDPTR_f,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_f *m2 = vsip_cmbind_f(
                  vsip_cblockbind_f(data2_r,data2_i,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_f *ma = vsip_mbind_f(
                  vsip_blockbind_f(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *m3 = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f *chk = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cblockadmit_f(vsip_cmgetblock_f(m1),VSIP_TRUE);
        vsip_cblockadmit_f(vsip_cmgetblock_f(m2),VSIP_TRUE);
        vsip_blockadmit_f(vsip_mgetblock_f(ma),VSIP_TRUE);
        printf("call vsip_mcmaxmgsq_f(a,b,c)\n");
        printf("a =\n");VU_cmprintm_f("8.6",m1);
        printf("b =\n");VU_cmprintm_f("8.6",m2);

        vsip_mcmaxmgsq_f(m1,m2,m3);
        printf("c =\n");VU_mprintm_f("8.6",m3);
        printf("\nright answer =\n"); VU_mprintm_f("6.4",ma);
        vsip_msub_f(ma,m3,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        { vsip_cmview_f *a = vsip_cmcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
          vsip_mview_f  *c= vsip_mrealview_f(a);
          vsip_cmcopy_f_f(m1,a);
          printf(" inplace <c> real view of <a> \n");
          vsip_mcmaxmgsq_f(a,m2,c);
          vsip_msub_f(ma,c,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,2 * .0001,0,1,chk);
          if(fabs(vsip_msumval_f(chk)) > .5)
              printf("error\n");
          else
              printf("correct\n");
          vsip_mdestroy_f(c);
          vsip_cmalldestroy_f(a);
        }

        { vsip_cmview_f *b = vsip_cmcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
          vsip_mview_f  *c= vsip_mimagview_f(b);
          vsip_cmcopy_f_f(m2,b);
          printf(" inplace <c> imag view of <b> \n");
          vsip_mcmaxmgsq_f(m1,b,c);
          vsip_msub_f(ma,c,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,2 * .0001,0,1,chk);
          if(fabs(vsip_msumval_f(chk)) > .5)
              printf("error\n");
          else
              printf("correct\n");
          vsip_mdestroy_f(c);
          vsip_cmalldestroy_f(b);
        }

        vsip_cmalldestroy_f(m1); vsip_cmalldestroy_f(m2);
        vsip_malldestroy_f(m3); vsip_malldestroy_f(ma);
        vsip_malldestroy_f(chk);
    }                                                       
      
    return;
}
