/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: ctoeplitz_f.h,v 1.1 2006/05/16 16:45:18 judd Exp $ */

#include"VU_cvprintm_f.include"
static void ctoeplitz_f(void)
{
    vsip_cmview_f *A = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_f *B = vsip_cmcreate_f(4,1,VSIP_ROW,VSIP_MEM_NONE);
    vsip_cvview_f *b = vsip_cmcolview_f(B,0);
   
    vsip_cvview_f *t = vsip_cvcreate_f(4,VSIP_MEM_NONE),
                 *x = vsip_cvcreate_f(4,VSIP_MEM_NONE),
                 *w = vsip_cvcreate_f(4,VSIP_MEM_NONE),
                 *y = vsip_cvcreate_f(4,VSIP_MEM_NONE);

    printf("********\nTEST ctoeplitz_f\n");
    printf("\nTest ctoeplitz_f\n");
    vsip_cvput_f(t,(vsip_index)0,vsip_cmplx_f(1.0,0));
    vsip_cvput_f(t,(vsip_index)1,vsip_cmplx_f(0.0,.4));
    vsip_cvput_f(t,(vsip_index)2,vsip_cmplx_f(0.0,.2));
    vsip_cvput_f(t,(vsip_index)3,vsip_cmplx_f(0.0,.15)); 

    vsip_cvput_f(y,(vsip_index)0,vsip_cmplx_f(4.0,1));
    vsip_cvput_f(y,(vsip_index)1,vsip_cmplx_f(-1.0,2));
    vsip_cvput_f(y,(vsip_index)2,vsip_cmplx_f(3.0,3));
    vsip_cvput_f(y,(vsip_index)3,vsip_cmplx_f(-2.0,-4));
    
    /* place full (lower diagonal) matrix in A */
    vsip_cmput_f(A,0,0,vsip_cvget_f(t,0));
    vsip_cmput_f(A,1,0,vsip_conj_f(vsip_cvget_f(t,1)));vsip_cmput_f(A,1,1,vsip_cvget_f(t,0));
    vsip_cmput_f(A,2,0,vsip_conj_f(vsip_cvget_f(t,2)));vsip_cmput_f(A,2,1,vsip_conj_f(vsip_cvget_f(t,1)));vsip_cmput_f(A,2,2,vsip_cvget_f(t,0));
    vsip_cmput_f(A,3,0,vsip_conj_f(vsip_cvget_f(t,3)));vsip_cmput_f(A,3,1,vsip_conj_f(vsip_cvget_f(t,2)));vsip_cmput_f(A,3,2,vsip_conj_f(vsip_cvget_f(t,1)));vsip_cmput_f(A,3,3,vsip_cvget_f(t,0));
    
    vsip_cvcopy_f_f(y,b);
    /* solve using cholesky */
    { 
       vsip_cchol_f *chol = vsip_cchold_create_f(VSIP_TR_LOW,4);
       vsip_cchold_f(chol,A);
       vsip_ccholsol_f(chol,B);
       vsip_cchold_destroy_f(chol);
    }
    printf("the solution using cholesky is\n");
    VU_cvprintm_f("7.5",b);

    printf("t=\n");VU_cvprintm_f("6.4",t);
    printf("y=\n");VU_cvprintm_f("6.4",y);
    vsip_ctoepsol_f(t,y,w,x);
    printf("t=\n");VU_cvprintm_f("6.4",t);
    printf("y=\n");VU_cvprintm_f("6.4",y);
    printf("the solution using toeplitz is\n");
    printf("x=\n");VU_cvprintm_f("6.4",x);
    vsip_cvsub_f(x,b,w);
    if(vsip_cmag_f(vsip_cvsumval_f(w)) < .00001)
       printf("\ncorrect\n");
    else
       printf("\nerror\n");
    
    vsip_cvalldestroy_f(t);
    vsip_cvalldestroy_f(x);
    vsip_cvalldestroy_f(w);
    vsip_cvalldestroy_f(y);
    
    vsip_cmalldestroy_f(A);
    vsip_cvdestroy_f(b);
    vsip_cmalldestroy_f(B);
}
