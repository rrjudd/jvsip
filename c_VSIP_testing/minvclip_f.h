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
/* $Id: minvclip_f.h,v 2.0 2003/02/22 15:23:25 judd Exp $ */
static void minvclip_f(void){
    printf("\n******\nTEST madd_f\n");
    {
        vsip_scalar_f data1[]= {.1, .2, .3, 4, 5, 6, 7, 8, 9};
        vsip_scalar_f ans[] =  {0.1, 0.2, 0.0, 1, 1, 1, 7.0, 8.0, 9.0}; 
        vsip_mview_f *a = vsip_mbind_f(
                  vsip_blockbind_f(data1,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *b = vsip_mcreate_f(3,3,VSIP_COL,VSIP_MEM_NONE);
        vsip_mview_f *mans = vsip_mbind_f(
                  vsip_blockbind_f(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *chk = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_scalar_f min = .25;
        vsip_scalar_f mid = 1.0;
        vsip_scalar_f max = 6.5;
        vsip_scalar_f minval = 0.0;
        vsip_scalar_f maxval = 1.0;
        vsip_blockadmit_f(vsip_mgetblock_f(a),VSIP_TRUE);
        vsip_blockadmit_f(vsip_mgetblock_f(mans),VSIP_TRUE);
        printf("call vsip_minvclip_f(a,min,mid,max,minval,maxval,b)\n");
        printf("min = %f\n",min);
        printf("mid = %f\n",mid);
        printf("max = %f\n",max);
        printf("min to mid value = %f\n",minval);
        printf("mid to max value = %f\n",maxval);
        printf("a =\n");VU_mprintm_f("8.6",a);
        vsip_minvclip_f(a,min,mid,max,minval,maxval,b);
        printf("b =\n");VU_mprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_mprintm_f("6.4",mans);
        vsip_msub_f(mans,b,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        printf(" a,b inplace\n");
        vsip_minvclip_f(a,min,mid,max,minval,maxval,a);
        printf("a =\n");VU_mprintm_f("8.6",a);
        vsip_msub_f(mans,a,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_f(a); vsip_malldestroy_f(b);
        vsip_malldestroy_f(mans);
        vsip_malldestroy_f(chk);
    }                                                       
      
    return;
}
