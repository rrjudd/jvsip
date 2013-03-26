#include"vsip_svd.h"

static void cmprint_f(vsip_cmview_f *A){
    vsip_length n=vsip_cmgetrowlength_f(A);
    vsip_length m=vsip_cmgetcollength_f(A);
    vsip_index i,j;
    printf("[");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            vsip_cscalar_f a=vsip_cmget_f(A,i,j);
            printf("%.5f%+.5fi ",a.r,a.i);
            if(j < n - 1) printf(",");
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
static vsip_scalar_f cmnormFro_f(vsip_cmview_f *v){
    vsip_mview_f* re=vsip_mrealview_f(v);
    vsip_mview_f* im=vsip_mimagview_f(v);
    return vsip_sqrt_f(vsip_msumsqval_f(re)+vsip_msumsqval_f(im));
    vsip_mdestroy_f(re);vsip_mdestroy_f(im);
}
static vsip_scalar_f ccheckBack_f(vsip_cmview_f* A,vsip_cmview_f* U, vsip_vview_f* d, vsip_cmview_f* V){
    vsip_scalar_f c;
    vsip_cmview_f *R=vsip_cmcreate_f(vsip_cmgetrowlength_f(V),vsip_cmgetcollength_f(V),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *Rr=vsip_mrealview_f(R);
    vsip_mview_f *Ri=vsip_mimagview_f(R);
    vsip_cmview_f *Ac=vsip_cmcreate_f(vsip_cmgetcollength_f(A),vsip_cmgetrowlength_f(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmherm_f(V,R);
    vsip_vmmul_f(d,Rr,VSIP_COL,Rr);
    vsip_vmmul_f(d,Ri,VSIP_COL,Ri);
    vsip_cmprod_f(U,R,Ac);
    vsip_cmsub_f(A,Ac,Ac);
    c = cmnormFro_f(Ac);
    vsip_mdestroy_f(Rr);vsip_mdestroy_f(Ri);
    vsip_cmalldestroy_f(Ac);vsip_cmalldestroy_f(R);
    return c;
}

int main(int argc, char* argv[]){
    vsip_length n=8,m=6;
    int init=vsip_init((void*)0);
    jvsip_csv_f *s=jvsip_csvd_create_f(m,n,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
    vsip_cmview_f *A = vsip_cmcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *Ar=vsip_mrealview_f(A);
    vsip_mview_f *Ai=vsip_mimagview_f(A);
    vsip_vview_f *ar = vsip_vbind_f(vsip_mgetblock_f(Ar),0,1,m*n);
    vsip_vview_f *ai = vsip_vbind_f(vsip_mgetblock_f(Ai),0,1,m*n);
    /*vsip_vview_f *ar = vsip_mdiagview_f(Ar, 0);
    vsip_vview_f *ai = vsip_mdiagview_f(Ai, 0);*/
    vsip_cmview_f *V=vsip_cmcreate_f(n,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_f *U=vsip_cmcreate_f(m,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_f *sv = vsip_vcreate_f((m < n ? m:n),VSIP_MEM_NONE);
    vsip_randstate *rnd=vsip_randcreate(5,1,1,VSIP_PRNG);
    if(init) exit(0);
    vsip_mfill_f(0.0, Ar);vsip_mfill_f(0.0, Ai);
    vsip_vrandn_f(rnd,ar); vsip_vrandn_f(rnd,ai);
    vsip_vdestroy_f(ar);vsip_vdestroy_f(ai);
    ar = vsip_mdiagview_f(Ar, 1); ai = vsip_mdiagview_f(Ai, 1);
    vsip_vrandn_f(rnd,ar); vsip_vrandn_f(rnd,ai);
    vsip_cmput_f(A, 2, 2, vsip_cmplx_f(0.0, 0.0));
    vsip_cmput_f(A, 2, 2, vsip_cmplx_f(0.0, 0.0));
    vsip_cmput_f(A, 5, 5, vsip_cmplx_f(0.0, 0.0));
    vsip_cmput_f(A,1,2,vsip_cmplx_f(0.0,0.0));
    vsip_cmput_f(A,3,4,vsip_cmplx_f(0.0,0.0));
    vsip_cmput_f(A,0,1,vsip_cmplx_f(0.0,0.0));
    printf("A = ");cmprint_f(A); printf("\n");
    if(jvsip_csvd_f(s,A,sv)){
        printf("svd failed\n");
        exit(0);
    }
    jvsip_csvdmatv_f(s,0,(m < n) ? n-1:m-1,V);
    jvsip_csvdmatu_f(s,0,(m < n) ? m-1:n-1,U);
    cmprint_f(U);
    printf("\n");
    vprint_f(sv);
    printf("\n");
    cmprint_f(V);
    printf("Check value %f\n",ccheckBack_f(A,U,sv,V)); 
    vsip_cmalldestroy_f(U);vsip_cmalldestroy_f(V);
    vsip_valldestroy_f(sv);
    vsip_vdestroy_f(ai);vsip_vdestroy_f(ar);
    vsip_mdestroy_f(Ar);vsip_mdestroy_f(Ai);
    vsip_randdestroy(rnd);
    jvsip_csvd_destroy_f(s);
    vsip_finalize((void*)0);
    return 1;
}
