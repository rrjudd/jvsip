#include<vsip.h>
#include"VU_mprintm_f.include"
#include"VU_vprintm_f.include"
static void svd1_f(void){
   printf("********\nTEST svd1 for float\n");
   {
      vsip_index i;
      vsip_length M=5, N=6;
      vsip_scalar_f data[30] = { -1, 2, 0,-3, 6, \
                                  8, 5, 4,-2, 1, \
                                  2, 3, 4, 5, 6, \
                                  7, 8, 9,10,11, \
                                 -1,-2,-3,-4,-5, \
                                 -0,-4,-5,-3,-2};
      vsip_vview_f *s = vsip_vcreate_f(((M > N) ? N : M),VSIP_MEM_NONE);
      jvsip_sv_f *svd = jvsip_svd_create_f(M,N,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);

      vsip_block_f *block = vsip_blockbind_f(data,(M * N),VSIP_MEM_NONE);
      vsip_mview_f *A0 = vsip_mbind_f(block,0,N,M,1,N);
      vsip_block_f *vblk = vsip_blockcreate_f(300,VSIP_MEM_NONE);
      vsip_mview_f *A = vsip_mbind_f(vblk,3,3 * N, M,2 , N);
      vsip_mview_f *U = vsip_mcreate_f(M,M,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_f *V = vsip_mcreate_f(N,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_f *B = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_blockadmit_f(block,VSIP_TRUE);
      vsip_mcopy_f_f(A0,A);
      printf("in = ");VU_mprintm_f("6.3",A);
      if(jvsip_svd_f(svd,A,s)){
           printf("svd error\n");
           return;
      }
      /* create the singular value matrix */
      vsip_mfill_f(0.0,B);
      for(i=0; i<vsip_vgetlength_f(s); i++) vsip_mput_f(B,i,i,vsip_vget_f(s,i));
      jvsip_svdmatu_f(svd, 0, M-1, U);
      jvsip_svdmatv_f(svd, 0, N-1, V);
      printf("U = ");VU_mprintm_f("12.10",U);
      printf("B = ");VU_mprintm_f("12.10",B);
      printf("V = ");VU_mprintm_f("12.10",V);
      VU_vprintm_f("12.10",s);
      {  /* check that A0 = U * B * V' */
         vsip_scalar_mi mi;
         vsip_scalar_f chk = 1.0;
         vsip_scalar_f lim = 5 * FLT_EPSILON * fabs(vsip_mmaxmgval_f(A0,&mi));
         vsip_mview_f *dif=vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_f *out = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_f *Vt = vsip_mtransview_f(V);
         vsip_mprod_f(U,B,dif);
         vsip_mprod_f(dif,Vt,out);
         vsip_msub_f(out,A0,dif);
         vsip_mmag_f(dif, dif);
         chk = vsip_msumval_f(dif)/(2 * M * N);
         printf("%20.18e - %20.18e = %e\n",lim,chk, (lim - chk));
         if(chk > lim){
            printf("error\n");
         } else {
            printf("correct\n");
         }
         vsip_malldestroy_f(dif);
         vsip_malldestroy_f(out);
         vsip_mdestroy_f(Vt);
      }
      jvsip_svd_destroy_f(svd);
      vsip_malldestroy_f(A0);
      vsip_malldestroy_f(A);
      vsip_valldestroy_f(s);
      vsip_malldestroy_f(U);
      vsip_malldestroy_f(B);
      vsip_malldestroy_f(V);
   }
   return;
}


static void mprint_f(vsip_mview_f *A){
    vsip_length n=vsip_mgetrowlength_f(A);
    vsip_length m=vsip_mgetcollength_f(A);
    vsip_index i,j;
    printf("[");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            printf("%+.5f ",vsip_mget_f(A,i,j));
        }
        printf(";\n") ;
    }
    printf("]\n");
}
static void vprint_f(vsip_vview_f *v){
    vsip_index i;
    printf("[");
    for(i=0; i<vsip_vgetlength_f(v); i++)
        printf("%+.5f ",vsip_vget_f(v,i));
    printf("]\n");
}
static vsip_scalar_f mnormFro_f(vsip_mview_f *A){
    return vsip_sqrt_f(vsip_msumsqval_f(A));
}
static vsip_scalar_f checkBack_f(vsip_mview_f* A,vsip_mview_f* U, vsip_vview_f* d, vsip_mview_f* V){
    vsip_scalar_f c;
    vsip_mview_f *VH=vsip_mtransview_f(V);
    vsip_mview_f *R=vsip_mcreate_f(vsip_mgetcollength_f(VH),vsip_mgetrowlength_f(VH),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *Ac=vsip_mcreate_f(vsip_mgetcollength_f(A),vsip_mgetrowlength_f(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_vmmul_f(d,VH,VSIP_COL,R);
    vsip_mprod_f(U,R,Ac);
    vsip_msub_f(A,Ac,Ac);
    c = mnormFro_f(Ac);
    vsip_mdestroy_f(VH);vsip_malldestroy_f(Ac);vsip_malldestroy_f(R);
    return c;
}

int main(int argc, char* argv[]){
    int init=vsip_init((void*)0);
    vsip_length in,im;
    for(im=2; im<99; im++){
        for(in=2; in<im; in++){
            vsip_length m=im,n=in;
            jvsip_sv_f *s=jvsip_svd_create_f(m,n,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
            vsip_mview_f *A = vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_mview_f *V=vsip_mcreate_f(n,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_mview_f *U=vsip_mcreate_f(m,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_vview_f *a = vsip_mdiagview_f(A,0);
            vsip_vview_f *a1 = vsip_mdiagview_f(A, 1);
            //vsip_vview_f *a = vsip_vbind_f(vsip_mgetblock_f(A),0,1,m*n);
            vsip_vview_f *sv = vsip_vcreate_f((m<n)? m:n,VSIP_MEM_NONE);
            vsip_randstate *rnd=vsip_randcreate(7,1,1,VSIP_PRNG);
            vsip_randstate *rnd1=vsip_randcreate(8, 1, 1, VSIP_PRNG);
            printf("----------\nsize %lu %lu\n",m,n);
            if(init) exit(0);
            vsip_mfill_f(0.0,A);
            vsip_vrandn_f(rnd,a);
            vsip_vrandn_f(rnd1,a1);
            vsip_vdestroy_f(a);
            vsip_vdestroy_f(a1);
            if(in == 5 && im == 10){
                a = vsip_vbind_f(vsip_mgetblock_f(A),0,1,m*n);
                vsip_vrandn_f(rnd,a);
                vsip_vdestroy_f(a);
            }
            if(m>2 && n > 2) vsip_mput_f(A, 2, 2, 0.0);
            if(m>4 && n > 4)vsip_mput_f(A, 4, 4, 0.0);
            if(m>4 && n > 4)vsip_mput_f(A, 3, 4, 0.0);
            if(m>2 && n > 2)vsip_mput_f(A, 1, 2, 0.0);
            if(m>2 && n > 2)vsip_mput_f(A,1,2,0.0);
            if(jvsip_svd_f(s,A,sv)){
                printf("svd failed\n");
                exit(0);
            }
            jvsip_svdmatv_f(s,0,(m < n) ? n-1:m-1,V);
            jvsip_svdmatu_f(s,0,(m < n) ? m-1:n-1,U);
            if(in==5 && im == 6){
                printf("A=");mprint_f(A); printf("\n");
                mprint_f(U);
                printf("\n");
                vprint_f(sv);
                printf("\n");
                mprint_f(V);
            }
            if(in==5 && im == 10){
                printf("A=");mprint_f(A); printf("\n");
                mprint_f(U);
                printf("\n");
                vprint_f(sv);
                printf("\n");
                mprint_f(V);
            }
            printf("Check value %f\n",checkBack_f(A,U,sv,V));
            vsip_malldestroy_f(U);vsip_malldestroy_f(V);
            vsip_valldestroy_f(sv);
            vsip_malldestroy_f(A);
            vsip_randdestroy(rnd);
            vsip_randdestroy(rnd1);
            jvsip_svd_destroy_f(s);
        }
    }
    svd1_f();
    vsip_finalize((void*)0);
    return 1;
}
