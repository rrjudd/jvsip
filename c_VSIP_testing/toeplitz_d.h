/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: toeplitz_d.h,v 1.1 2006/05/16 16:45:18 judd Exp $ */

void toeplitz_d(void)
{
    vsip_mview_d *A = vsip_mcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *B = vsip_mcreate_d(4,1,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_d *b = vsip_mcolview_d(B,0);
    vsip_vview_d *t = vsip_vcreate_d(4,VSIP_MEM_NONE),
                 *x = vsip_vcreate_d(4,VSIP_MEM_NONE),
                 *w = vsip_vcreate_d(4,VSIP_MEM_NONE),
                 *y = vsip_vcreate_d(4,VSIP_MEM_NONE);

    printf("********\nTEST toeplitz_d\n");
    printf("\nTest toeplitz_d\n");
    vsip_vput_d(t,(vsip_index)0,(vsip_scalar_d)5.0);
    vsip_vput_d(t,(vsip_index)1,(vsip_scalar_d)0.5);
    vsip_vput_d(t,(vsip_index)2,(vsip_scalar_d)0.2);
    vsip_vput_d(t,(vsip_index)3,(vsip_scalar_d)0.1);
    vsip_vput_d(y,(vsip_index)0,(vsip_scalar_d)4.0);
    vsip_vput_d(y,(vsip_index)1,(vsip_scalar_d)-1.0);
    vsip_vput_d(y,(vsip_index)2,(vsip_scalar_d)3.0);
    vsip_vput_d(y,(vsip_index)3,(vsip_scalar_d)-2.0);

    /* place full matrix in A */
    vsip_mput_d(A,0,0,vsip_vget_d(t,0)); vsip_mput_d(A,0,1,vsip_vget_d(t,1)); vsip_mput_d(A,0,2,vsip_vget_d(t,2)); vsip_mput_d(A,0,3,vsip_vget_d(t,3));
    vsip_mput_d(A,1,0,vsip_vget_d(t,1)); vsip_mput_d(A,1,1,vsip_vget_d(t,0)); vsip_mput_d(A,1,2,vsip_vget_d(t,1)); vsip_mput_d(A,1,3,vsip_vget_d(t,2));
    vsip_mput_d(A,2,0,vsip_vget_d(t,2)); vsip_mput_d(A,2,1,vsip_vget_d(t,1)); vsip_mput_d(A,2,2,vsip_vget_d(t,0)); vsip_mput_d(A,2,3,vsip_vget_d(t,1));
    vsip_mput_d(A,3,0,vsip_vget_d(t,3)); vsip_mput_d(A,3,1,vsip_vget_d(t,2)); vsip_mput_d(A,3,2,vsip_vget_d(t,1)); vsip_mput_d(A,3,3,vsip_vget_d(t,0));
    /* place y in B */
    vsip_vcopy_d_d(y,b);
    /* solve using cholesky */
    { 
        vsip_chol_d *chol = vsip_chold_create_d(VSIP_TR_LOW,4);
        vsip_chold_d(chol,A);
        vsip_cholsol_d(chol,B);
        vsip_chold_destroy_d(chol);
    }
    printf("the solution using cholesky is\n");
    VU_vprintm_d("7.5",b);

    printf("t=\n");VU_vprintm_d("6.4",t);
    printf("y=\n");VU_vprintm_d("6.4",y);
    vsip_toepsol_d(t,y,w,x);
    printf("t=\n");VU_vprintm_d("6.4",t);
    printf("y=\n");VU_vprintm_d("6.4",y);
    printf("w=\n");VU_vprintm_d("6.4",w);
    printf("the solution using toeplitz is\n");
    printf("x=\n");VU_vprintm_d("6.4",x);
    vsip_vsub_d(x,b,b);
    if(fabs(vsip_vsumval_d(b)) < .00001)
       printf("\ncorrect\n");
    else
       printf("\nerror\n");
    vsip_valldestroy_d(t);
    vsip_valldestroy_d(x);
    vsip_valldestroy_d(w);
    vsip_valldestroy_d(y);
    vsip_malldestroy_d(A);
    vsip_vdestroy_d(b);
    vsip_malldestroy_d(B);
}
