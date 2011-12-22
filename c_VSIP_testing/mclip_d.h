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
/* $Id: mclip_d.h,v 2.1 2004/04/03 14:45:20 judd Exp $ */
static void mclip_d(void){
    printf("\n******\nTEST mclip_d\n");
    {
        vsip_scalar_d data1[]= {.1, .2, .3, 4, 5, 6, 7, 8, 9};
        vsip_scalar_d ans[] =  {0.0, 0.0, 0.3, 4, 5, 6, 1.0, 1.0, 1.0}; 
        vsip_mview_d *a = vsip_mbind_d(
                  vsip_blockbind_d(data1,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *b = vsip_mcreate_d(3,3,VSIP_COL,VSIP_MEM_NONE);
        vsip_mview_d *mans = vsip_mbind_d(
                  vsip_blockbind_d(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *chk = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_scalar_d min = .25;
        vsip_scalar_d max = 6.5;
        vsip_scalar_d minval = 0.0;
        vsip_scalar_d maxval = 1.0;
        vsip_blockadmit_d(vsip_mgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(mans),VSIP_TRUE);
        printf("call vsip_mclip_d(a,min,max,minval,maxval,b)\n");
        printf("min = %f\n",min);
        printf("max = %f\n",max);
        printf("minval = %f\n",minval);
        printf("maxval = %f\n",maxval);
        printf("a =\n");VU_mprintm_d("8.6",a);
        vsip_mclip_d(a,min,max,minval,maxval,b);
        printf("b =\n");VU_mprintm_d("8.6",b);
        printf("\nright answer =\n"); VU_mprintm_d("6.4",mans);
        vsip_msub_d(mans,b,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        printf(" a,b inplace\n");
        vsip_mclip_d(a,min,max,minval,maxval,a);
        vsip_msub_d(mans,a,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_d(a); vsip_malldestroy_d(b);
        vsip_malldestroy_d(mans);
        vsip_malldestroy_d(chk);
    }                                                       
      
    return;
}
