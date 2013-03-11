#include"svd_f.h"

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
static vsip_scalar_f checkBack_f(vsip_mview_f* A,vsip_mview_f* L, vsip_vview_f* d, vsip_mview_f* R){
    vsip_scalar_f c;
    vsip_mview_f *VH=vsip_mcreate_f(vsip_mgetcollength_f(R),vsip_mgetrowlength_f(R),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *Ac=vsip_mcreate_f(vsip_mgetcollength_f(A),vsip_mgetrowlength_f(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *L0=vsip_msubview_f(L,0,0,vsip_mgetcollength_f(L),vsip_vgetlength_f(d));
    vsip_mcopy_f_f(R,VH);
    vsip_vmmul_f(d,VH,VSIP_COL,VH);
    vsip_mprod_f(L0,VH,Ac);
    vsip_msub_f(A,Ac,Ac);
    c = mnormFro_f(Ac);
    vsip_malldestroy_f(VH);vsip_malldestroy_f(Ac);vsip_mdestroy_f(L0);
    return c;
}

int main(int argc, char* argv[]){
    vsip_length m=6,n=6;
    svdObj_f *s;
    int init=vsip_init((void*)0);
    vsip_mview_f *A = vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_f *a = vsip_vbind_f(vsip_mgetblock_f(A),0,1,m*n);
    vsip_randstate *rnd=vsip_randcreate(5,1,1,VSIP_PRNG);
    if(init) exit(0);
    vsip_vrandn_f(rnd,a);
    mprint_f(A); printf("\n");
    s = svd_f(A);
    if(!s){
        printf("svd failed\n");
        exit(0);
    }
    mprint_f(s->L);
    printf("\n");
    vprint_f(s->d);
    printf("\n");
    mprint_f(s->R);
    printf("Check value %f\n",checkBack_f(A,s->L,s->d,s->R));
    vsip_vdestroy_f(a);
    vsip_malldestroy_f(A);
    vsip_randdestroy(rnd);
    svdFinalize_f(s);
    vsip_finalize((void*)0);
    return 1;
}
