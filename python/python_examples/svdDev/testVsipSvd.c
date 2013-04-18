#include"vsip_svd.h"

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
    for(im=4; im<150; im++){
        for(in=4; in<im; in++){
            vsip_length m=in,n=im;
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
            if(m>2 && n > 2) vsip_mput_f(A, 2, 2, 0.0);
            if(m>4 && n > 4)vsip_mput_f(A, 4, 4, 0.0);
            if(m>4 && n > 4)vsip_mput_f(A, 3, 4, 0.0);
            if(m>2 && n > 2)vsip_mput_f(A, 1, 2, 0.0);
            if(m>2 && n > 2)vsip_mput_f(A,1,2,0.0);
            //printf("A=");mprint_f(A); printf("\n");
            if(jvsip_svd_f(s,A,sv)){
                printf("svd failed\n");
                exit(0);
            }
            jvsip_svdmatv_f(s,0,(m < n) ? n-1:m-1,V);
            jvsip_svdmatu_f(s,0,(m < n) ? m-1:n-1,U);
           /* mprint_f(U);
            printf("\n");
            vprint_f(sv);
            printf("\n");
            mprint_f(V); */
            printf("Check value %f\n",checkBack_f(A,U,sv,V));
            vsip_malldestroy_f(U);vsip_malldestroy_f(V);
            vsip_valldestroy_f(sv);
            vsip_malldestroy_f(A);
            vsip_randdestroy(rnd);
            vsip_randdestroy(rnd1);
            jvsip_svd_destroy_f(s);
        }
    }
    vsip_finalize((void*)0);
    return 1;
}
