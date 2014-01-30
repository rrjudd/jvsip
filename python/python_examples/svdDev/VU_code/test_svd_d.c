#include"svd_d.h"

static void mprint_d(vsip_mview_d *A){
    vsip_length n=vsip_mgetrowlength_d(A);
    vsip_length m=vsip_mgetcollength_d(A);
    vsip_index i,j;
    printf("[");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            printf("%+.5f ",vsip_mget_d(A,i,j));
        }
        printf(";\n") ;
    }
    printf("]\n");
}
static void vprint_d(vsip_vview_d *v){
    vsip_index i;
    printf("[");
    for(i=0; i<vsip_vgetlength_d(v); i++)
        printf("%+.5f ",vsip_vget_d(v,i));
    printf("]\n");
}
static vsip_scalar_d mnormFro_d(vsip_mview_d *A){
    return vsip_sqrt_d(vsip_msumsqval_d(A));
}
static vsip_scalar_d checkBack_d(vsip_mview_d* A,vsip_mview_d* L, vsip_vview_d* d, vsip_mview_d* R){
    vsip_scalar_d c;
    vsip_mview_d *VH=vsip_mcreate_d(vsip_mgetcollength_d(R),vsip_mgetrowlength_d(R),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *Ac=vsip_mcreate_d(vsip_mgetcollength_d(A),vsip_mgetrowlength_d(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *L0=vsip_msubview_d(L,0,0,vsip_mgetcollength_d(L),vsip_vgetlength_d(d));
    vsip_mcopy_d_d(R,VH);
    vsip_vmmul_d(d,VH,VSIP_COL,VH);
    vsip_mprod_d(L0,VH,Ac);
    vsip_msub_d(A,Ac,Ac);
    c = mnormFro_d(Ac);
    vsip_malldestroy_d(VH);vsip_malldestroy_d(Ac);vsip_mdestroy_d(L0);
    return c;
}

int main(int argc, char* argv[]){
    vsip_length m=6,n=6;
    svdObj_d *s;
    int init=vsip_init((void*)0);
    vsip_mview_d *A = vsip_mcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_d *a = vsip_vbind_d(vsip_mgetblock_d(A),0,1,m*n);
    vsip_randstate *rnd=vsip_randcreate(5,1,1,VSIP_PRNG);
    if(init) exit(0);
    vsip_vrandn_d(rnd,a);
    mprint_d(A); printf("\n");
    s = svd_d(A);
    if(!s){
        printf("svd failed\n");
        exit(0);
    }
    mprint_d(s->L);
    printf("\n");
    vprint_d(s->d);
    printf("\n");
    mprint_d(s->R);
    printf("Check value %f\n",checkBack_d(A,s->L,s->d,s->R));
    vsip_vdestroy_d(a);
    vsip_malldestroy_d(A);
    vsip_randdestroy(rnd);
    svdFinalize_d(s);
    vsip_finalize((void*)0);
    return 1;
}
