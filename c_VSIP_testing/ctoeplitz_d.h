/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: ctoeplitz_d.h,v 1.1 2006/05/16 16:45:18 judd Exp $ */

void ctoeplitz_d(void)
{
    vsip_cmview_d *A = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_d *B = vsip_cmcreate_d(4,1,VSIP_ROW,VSIP_MEM_NONE);
    vsip_cvview_d *b = vsip_cmcolview_d(B,0);
   
    vsip_cvview_d *t = vsip_cvcreate_d(4,VSIP_MEM_NONE),
                 *x = vsip_cvcreate_d(4,VSIP_MEM_NONE),
                 *w = vsip_cvcreate_d(4,VSIP_MEM_NONE),
                 *y = vsip_cvcreate_d(4,VSIP_MEM_NONE);

    printf("\ntest ctoeplitz_d\n");
    vsip_cvput_d(t,(vsip_index)0,vsip_cmplx_d(1.0,0));
    vsip_cvput_d(t,(vsip_index)1,vsip_cmplx_d(0.0,.4));
    vsip_cvput_d(t,(vsip_index)2,vsip_cmplx_d(0.0,.2));
    vsip_cvput_d(t,(vsip_index)3,vsip_cmplx_d(0.0,.15)); 

    vsip_cvput_d(y,(vsip_index)0,vsip_cmplx_d(4.0,1));
    vsip_cvput_d(y,(vsip_index)1,vsip_cmplx_d(-1.0,2));
    vsip_cvput_d(y,(vsip_index)2,vsip_cmplx_d(3.0,3));
    vsip_cvput_d(y,(vsip_index)3,vsip_cmplx_d(-2.0,-4));
    
    /* place full (lower diagonal) matrix in A */
    vsip_cmput_d(A,0,0,vsip_cvget_d(t,0));
    vsip_cmput_d(A,1,0,vsip_conj_d(vsip_cvget_d(t,1)));vsip_cmput_d(A,1,1,vsip_cvget_d(t,0));
    vsip_cmput_d(A,2,0,vsip_conj_d(vsip_cvget_d(t,2)));vsip_cmput_d(A,2,1,vsip_conj_d(vsip_cvget_d(t,1)));vsip_cmput_d(A,2,2,vsip_cvget_d(t,0));
    vsip_cmput_d(A,3,0,vsip_conj_d(vsip_cvget_d(t,3)));vsip_cmput_d(A,3,1,vsip_conj_d(vsip_cvget_d(t,2)));vsip_cmput_d(A,3,2,vsip_conj_d(vsip_cvget_d(t,1)));vsip_cmput_d(A,3,3,vsip_cvget_d(t,0));
    
    vsip_cvcopy_d_d(y,b);
    /* solve using cholesky */
    { 
       vsip_cchol_d *chol = vsip_cchold_create_d(VSIP_TR_LOW,4);
       vsip_cchold_d(chol,A);
       vsip_ccholsol_d(chol,B);
       vsip_cchold_destroy_d(chol);
    }
    printf("the solution using cholesky is\n");
    VU_cvprintm_d("7.5",b);

    printf("t=\n");VU_cvprintm_d("6.4",t);
    printf("y=\n");VU_cvprintm_d("6.4",y);
    vsip_ctoepsol_d(t,y,w,x);
    printf("t=\n");VU_cvprintm_d("6.4",t);
    printf("y=\n");VU_cvprintm_d("6.4",y);
    printf("the solution using toeplitz is\n");
    printf("x=\n");VU_cvprintm_d("6.4",x);
    vsip_cvsub_d(x,b,w);
    if(vsip_cmag_d(vsip_cvsumval_d(w)) < .00001)
       printf("\ncorrect\n");
    else
       printf("\nerror\n");
    
    vsip_cvalldestroy_d(t);
    vsip_cvalldestroy_d(x);
    vsip_cvalldestroy_d(w);
    vsip_cvalldestroy_d(y);
    
    vsip_cmalldestroy_d(A);
    vsip_cvdestroy_d(b);
    vsip_cmalldestroy_d(B);
}
