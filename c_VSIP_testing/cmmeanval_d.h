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
/* $Id: cmmeanval_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
#include"VU_cmprintm_d.include"
static void cmmeanval_d(void){
   printf("\n*******\nTEST cmmeanval_d\n\n");
   { vsip_scalar_d data_r[] = {M_PI/8.0,  M_PI/4.0,  M_PI/3.0,  M_PI/1.5,  1.25 * M_PI,  1.75 * M_PI};
     vsip_scalar_d data_i[] = { 1,        2,         -3,        -4,         5,           6};
     vsip_cscalar_d ans = vsip_cmplx_d(2.29074,1.16667);
     vsip_cscalar_d val;
     vsip_cblock_d  *block = vsip_cblockbind_d(data_r,data_i,6,VSIP_MEM_NONE);
     vsip_cmview_d  *a = vsip_cmbind_d(block,0,2,3,1,2);
     vsip_cblockadmit_d(block,VSIP_TRUE);
     val = vsip_cmmeanval_d(a);
     printf("val = vsip_cmmeanval_d(a)\n matrix a\n");VU_cmprintm_d("8.6",a);
     printf("val = %f %+fi\n",vsip_real_d(val),vsip_imag_d(val));
     printf("right answer = %f %+fi\n",vsip_real_d(ans),vsip_imag_d(ans));
     if(((vsip_real_d(val)-vsip_real_d(ans)) > .0001) ||
     ((vsip_imag_d(val)-vsip_imag_d(ans)) > .0001))
        printf("error\n");
     else
        printf("correct\n");
     vsip_cmalldestroy_d(a);
   }
   return;
}
