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
/* $Id: mcminmgsq_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void mcminmgsq_d(void){
    printf("\n******\nTEST mcminmgsq_d\n");
    {
        vsip_scalar_d data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_d data2_r[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_d data2_i[]= {-1.1, 2.2, -3.3, 4.4, -5.5, 6.6, -7.7, 8.8, -9.9};
        vsip_scalar_d ans[] =  { 1.01, 4.04, 9.09, 9.68, 25.09, 36.16, 21.78, 64.81, 82.00};
        vsip_cmview_d *m1 = vsip_cmbind_d(
                  vsip_cblockbind_d(data1,NDPTR_d,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *m2 = vsip_cmbind_d(
                  vsip_cblockbind_d(data2_r,data2_i,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_d *ma = vsip_mbind_d(
                  vsip_blockbind_d(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *m3 = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *chk = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m1),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m2),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(ma),VSIP_TRUE);
        printf("call vsip_mcminmgsq_d(a,b,c)\n");
        printf("a =\n");VU_cmprintm_d("8.6",m1);
        printf("b =\n");VU_cmprintm_d("8.6",m2);

        vsip_mcminmgsq_d(m1,m2,m3);
        printf("c =\n");VU_mprintm_d("8.6",m3);
        printf("\nright answer =\n"); VU_mprintm_d("6.4",ma);
        vsip_msub_d(ma,m3,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        { vsip_cmview_d *a = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
          vsip_mview_d  *c= vsip_mrealview_d(a);
          vsip_cmcopy_d_d(m1,a);
          printf(" inplace <c> real view of <a> \n");
          vsip_mcminmgsq_d(a,m2,c);
          vsip_msub_d(ma,c,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,2 * .0001,0,1,chk);
          if(fabs(vsip_msumval_d(chk)) > .5)
              printf("error\n");
          else
              printf("correct\n");
          vsip_mdestroy_d(c);
          vsip_cmalldestroy_d(a);
        }

        { vsip_cmview_d *b = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
          vsip_mview_d  *c= vsip_mimagview_d(b);
          vsip_cmcopy_d_d(m2,b);
          printf(" inplace <c> imag view of <b> \n");
          vsip_mcminmgsq_d(m1,b,c);
          vsip_msub_d(ma,c,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,2 * .0001,0,1,chk);
          if(fabs(vsip_msumval_d(chk)) > .5)
              printf("error\n");
          else
              printf("correct\n");
          vsip_mdestroy_d(c);
          vsip_cmalldestroy_d(b);
        }

        vsip_cmalldestroy_d(m1); vsip_cmalldestroy_d(m2);
        vsip_malldestroy_d(m3); vsip_malldestroy_d(ma);
        vsip_malldestroy_d(chk);
    }                                                       
      
    return;
}
