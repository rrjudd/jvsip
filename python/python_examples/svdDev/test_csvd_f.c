#include"csvd_f.h"

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
static vsip_scalar_f ccheckBack_f(vsip_cmview_f* A,vsip_cmview_f* L, vsip_vview_f* d, vsip_cmview_f* R){
    vsip_scalar_f c;
    vsip_cmview_f *VH=vsip_cmcreate_f(vsip_cmgetcollength_f(R),vsip_cmgetrowlength_f(R),VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_f *Ac=vsip_cmcreate_f(vsip_cmgetcollength_f(A),vsip_cmgetrowlength_f(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_f *L0=vsip_cmsubview_f(L,0,0,vsip_cmgetcollength_f(L),vsip_vgetlength_f(d));
    vsip_cmcopy_f_f(R,VH);
    vsip_rvcmmul_f(d,VH,VSIP_COL,VH);
    vsip_cmprod_f(L0,VH,Ac);
    vsip_cmsub_f(A,Ac,Ac);
    c = cmnormFro_f(Ac);
    vsip_cmalldestroy_f(VH);vsip_cmalldestroy_f(Ac);vsip_cmdestroy_f(L0);
    return c;
}

int main(int argc, char* argv[]){
    vsip_length m=12,n=10;
    int init=vsip_init((void*)0);
    csvdObj_f *s;
    vsip_cmview_f *A = vsip_cmcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_f *Ar=vsip_mrealview_f(A);
    vsip_mview_f *Ai=vsip_mimagview_f(A);
    vsip_vview_f *ar = vsip_vbind_f(vsip_mgetblock_f(Ar),0,1,m*n);
    vsip_vview_f *ai = vsip_vbind_f(vsip_mgetblock_f(Ai),0,1,m*n);
    vsip_randstate *rnd=vsip_randcreate(5,1,1,VSIP_PRNG);
    if(init) exit(0);
    vsip_vrandn_f(rnd,ar);
    vsip_vrandn_f(rnd,ai);
    s=csvd_f(A);
    cmprint_f(A); printf("\n");
    cmprint_f(s->L);
    printf("\n");
    vprint_f(s->d);
    printf("\n");
    cmprint_f(s->R);
    printf("Check value %f\n",ccheckBack_f(A,s->L,s->d,s->R));
    csvdFinalize_f(s);
    vsip_mdestroy_f(Ar);vsip_mdestroy_f(Ai);
    vsip_vdestroy_f(ar); vsip_vdestroy_f(ai);
    vsip_cmalldestroy_f(A);
    vsip_randdestroy(rnd);
    vsip_finalize((void*)0);
    return 1;
}
