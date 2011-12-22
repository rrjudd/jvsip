/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: toeplitz_f.h,v 1.1 2006/05/16 16:45:18 judd Exp $ */

void toeplitz_f(void)
{
    vsip_mview_f *A = vsip_mcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *B = vsip_mcreate_f(4,1,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_f *b = vsip_mcolview_f(B,0);
    vsip_vview_f *t = vsip_vcreate_f(4,VSIP_MEM_NONE),
                 *x = vsip_vcreate_f(4,VSIP_MEM_NONE),
                 *w = vsip_vcreate_f(4,VSIP_MEM_NONE),
                 *y = vsip_vcreate_f(4,VSIP_MEM_NONE);

    printf("********\nTEST toeplitz_f\n");
    printf("\nTest toeplitz_f\n");
    vsip_vput_f(t,(vsip_index)0,(vsip_scalar_f)5.0);
    vsip_vput_f(t,(vsip_index)1,(vsip_scalar_f)0.5);
    vsip_vput_f(t,(vsip_index)2,(vsip_scalar_f)0.2);
    vsip_vput_f(t,(vsip_index)3,(vsip_scalar_f)0.1);
    vsip_vput_f(y,(vsip_index)0,(vsip_scalar_f)4.0);
    vsip_vput_f(y,(vsip_index)1,(vsip_scalar_f)-1.0);
    vsip_vput_f(y,(vsip_index)2,(vsip_scalar_f)3.0);
    vsip_vput_f(y,(vsip_index)3,(vsip_scalar_f)-2.0);

    /* place full (lower diagonal part) matrix in A */
    vsip_mput_f(A,0,0,vsip_vget_f(t,0));
    vsip_mput_f(A,1,0,vsip_vget_f(t,1)); vsip_mput_f(A,1,1,vsip_vget_f(t,0)); 
    vsip_mput_f(A,2,0,vsip_vget_f(t,2)); vsip_mput_f(A,2,1,vsip_vget_f(t,1)); vsip_mput_f(A,2,2,vsip_vget_f(t,0)); 
    vsip_mput_f(A,3,0,vsip_vget_f(t,3)); vsip_mput_f(A,3,1,vsip_vget_f(t,2)); vsip_mput_f(A,3,2,vsip_vget_f(t,1)); vsip_mput_f(A,3,3,vsip_vget_f(t,0));

    /* place y in B */
    vsip_vcopy_f_f(y,b);
    /* solve using cholesky */
    { 
        vsip_chol_f *chol = vsip_chold_create_f(VSIP_TR_LOW,4);
        vsip_chold_f(chol,A);
        vsip_cholsol_f(chol,B);
        vsip_chold_destroy_f(chol);
    }
    printf("the solution using cholesky is\n");
    VU_vprintm_f("7.5",b);

    printf("t=\n");VU_vprintm_f("6.4",t);
    printf("y=\n");VU_vprintm_f("6.4",y);
    vsip_toepsol_f(t,y,w,x);
    printf("t=\n");VU_vprintm_f("6.4",t);
    printf("y=\n");VU_vprintm_f("6.4",y);
    printf("w=\n");VU_vprintm_f("6.4",w);
    printf("the solution using toeplitz is\n");
    printf("x=\n");VU_vprintm_f("6.4",x);
    vsip_vsub_f(x,b,b);
    if(fabs(vsip_vsumval_f(b)) < .00001)
       printf("\ncorrect\n");
    else
       printf("\nerror\n");
    vsip_valldestroy_f(t);
    vsip_valldestroy_f(x);
    vsip_valldestroy_f(w);
    vsip_valldestroy_f(y);
    vsip_malldestroy_f(A);
    vsip_vdestroy_f(b);
    vsip_malldestroy_f(B);
}
