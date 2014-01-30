#include"csvd_d.h"

static void cmprint_d(vsip_cmview_d *A){
    vsip_length n=vsip_cmgetrowlength_d(A);
    vsip_length m=vsip_cmgetcollength_d(A);
    vsip_index i,j;
    printf("[");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            vsip_cscalar_d a=vsip_cmget_d(A,i,j);
            printf("%.5f%+.5fi ",a.r,a.i);
            if(j < n - 1) printf(",");
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
static vsip_scalar_d cmnormFro_d(vsip_cmview_d *v){
    vsip_mview_d* re=vsip_mrealview_d(v);
    vsip_mview_d* im=vsip_mimagview_d(v);
    return vsip_sqrt_d(vsip_msumsqval_d(re)+vsip_msumsqval_d(im));
    vsip_mdestroy_d(re);vsip_mdestroy_d(im);
}
static vsip_scalar_d ccheckBack_d(vsip_cmview_d* A,vsip_cmview_d* L, vsip_vview_d* d, vsip_cmview_d* R){
    vsip_scalar_d c;
    vsip_cmview_d *VH=vsip_cmcreate_d(vsip_cmgetcollength_d(R),vsip_cmgetrowlength_d(R),VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_d *Ac=vsip_cmcreate_d(vsip_cmgetcollength_d(A),vsip_cmgetrowlength_d(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmview_d *L0=vsip_cmsubview_d(L,0,0,vsip_cmgetcollength_d(L),vsip_vgetlength_d(d));
    vsip_cmcopy_d_d(R,VH);
    vsip_rvcmmul_d(d,VH,VSIP_COL,VH);
    vsip_cmprod_d(L0,VH,Ac);
    vsip_cmsub_d(A,Ac,Ac);
    c = cmnormFro_d(Ac);
    vsip_cmalldestroy_d(VH);vsip_cmalldestroy_d(Ac);vsip_cmdestroy_d(L0);
    return c;
}

int main(int argc, char* argv[]){
    vsip_length m=12,n=10;
    int init=vsip_init((void*)0);
    csvdObj_d *s;
    vsip_cmview_d *A = vsip_cmcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *Ar=vsip_mrealview_d(A);
    vsip_mview_d *Ai=vsip_mimagview_d(A);
    vsip_vview_d *ar = vsip_vbind_d(vsip_mgetblock_d(Ar),0,1,m*n);
    vsip_vview_d *ai = vsip_vbind_d(vsip_mgetblock_d(Ai),0,1,m*n);
    vsip_randstate *rnd=vsip_randcreate(5,1,1,VSIP_PRNG);
    if(init) exit(0);
    vsip_vrandn_d(rnd,ar);
    vsip_vrandn_d(rnd,ai);
    s=csvd_d(A);
    cmprint_d(A); printf("\n");
    cmprint_d(s->L);
    printf("\n");
    vprint_d(s->d);
    printf("\n");
    cmprint_d(s->R);
    printf("Check value %f\n",ccheckBack_d(A,s->L,s->d,s->R));
    csvdFinalize_d(s);
    vsip_mdestroy_d(Ar);vsip_mdestroy_d(Ai);
    vsip_vdestroy_d(ar); vsip_vdestroy_d(ai);
    vsip_cmalldestroy_d(A);
    vsip_randdestroy(rnd);
    vsip_finalize((void*)0);
    return 1;
}
