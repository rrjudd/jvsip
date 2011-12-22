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
/* $Id: cmmeanval_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmmeanval_f(void){
   printf("\n*******\nTEST cmmeanval_f\n\n");
   { vsip_scalar_f data_r[] = {M_PI/8.0,  M_PI/4.0,  M_PI/3.0,  M_PI/1.5,  1.25 * M_PI,  1.75 * M_PI};
     vsip_scalar_f data_i[] = { 1,        2,         -3,        -4,         5,           6};
     vsip_cscalar_f ans = vsip_cmplx_f(2.29074,1.16667);
     vsip_cscalar_f val;
     vsip_cblock_f  *block = vsip_cblockbind_f(data_r,data_i,6,VSIP_MEM_NONE);
     vsip_cmview_f  *a = vsip_cmbind_f(block,0,2,3,1,2);
     vsip_cblockadmit_f(block,VSIP_TRUE);
     val = vsip_cmmeanval_f(a);
     printf("val = vsip_cmmeanval_f(a)\n matrix a\n");VU_cmprintm_f("8.6",a);
     printf("val = %f %+fi\n",vsip_real_f(val),vsip_imag_f(val));
     printf("right answer = %f %+fi\n",vsip_real_f(ans),vsip_imag_f(ans));
     if(((vsip_real_f(val)-vsip_real_f(ans)) > .0001) ||
     ((vsip_imag_f(val)-vsip_imag_f(ans)) > .0001))
        printf("error\n");
     else
        printf("correct\n");
     vsip_cmalldestroy_f(a);
   }
   return;
}
