#include"vsip.h"
#include"../../../c_VSIP_testing/svd2_f.h"
#include"../../../c_VSIP_testing/svd2_d.h"
#include"../../../c_VSIP_testing/svd3_f.h"
#include"../../../c_VSIP_testing/svd3_d.h"
#include"../../../c_VSIP_testing/svd4_f.h"
#include"../../../c_VSIP_testing/svd4_d.h"
#include"../../../c_VSIP_testing/svd5_f.h"
#include"../../../c_VSIP_testing/svd5_d.h"
#include"../../../c_VSIP_testing/svd6_f.h"
#include"../../../c_VSIP_testing/svd6_d.h"
#include"../../../c_VSIP_testing/svd7_f.h"
#include"../../../c_VSIP_testing/svd7_d.h"
#include"../../../c_VSIP_testing/svd8_f.h"
#include"../../../c_VSIP_testing/svd1_d.h"
#include"../../../c_VSIP_testing/svd1_f.h"


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

static vsip_scalar_d mnormFro_d(vsip_mview_d *A){
    return vsip_sqrt_d(vsip_msumsqval_d(A));
}
static vsip_scalar_d checkBack_d(vsip_mview_d* A,vsip_mview_d* U, vsip_vview_d* d, vsip_mview_d* V){
    vsip_scalar_d c;
    vsip_mview_d *VH=vsip_mtransview_d(V);
    vsip_mview_d *R=vsip_mcreate_d(vsip_mgetcollength_d(VH),vsip_mgetrowlength_d(VH),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *Ac=vsip_mcreate_d(vsip_mgetcollength_d(A),vsip_mgetrowlength_d(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_vmmul_d(d,VH,VSIP_COL,R);
    vsip_mprod_d(U,R,Ac);
    vsip_msub_d(A,Ac,Ac);
    c = mnormFro_d(Ac);
    vsip_mdestroy_d(VH);vsip_malldestroy_d(Ac);vsip_malldestroy_d(R);
    return c;
}

int main(int argc, char* argv[]){
    int init=vsip_init((void*)0);
    vsip_length in,im;
    printf("check float\n");
    for(im=2; im<200; im+=3){
        for(in=2; in<im; in++){
            vsip_length m=im,n=in;
            vsip_sv_f *s=vsip_svd_create_f(m,n,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
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
            if(vsip_svd_f(s,A,sv)){
                printf("svd failed\n");
                exit(0);
            }
            vsip_svdmatv_f(s,0,(m < n) ? n-1:m-1,V);
            vsip_svdmatu_f(s,0,(m < n) ? m-1:n-1,U);
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
            vsip_svd_destroy_f(s);
        }
    }
    printf("check double\n");
    for(im=2; im<200; im+=5){
        for(in=2; in<im; in++){
            vsip_length m=im,n=in;
            vsip_sv_d *s=vsip_svd_create_d(m,n,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
            vsip_mview_d *A = vsip_mcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_mview_d *V=vsip_mcreate_d(n,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_mview_d *U=vsip_mcreate_d(m,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_vview_d *a = vsip_mdiagview_d(A,0);
            vsip_vview_d *a1 = vsip_mdiagview_d(A, 1);
            //vsip_vview_d *a = vsip_vbind_d(vsip_mgetblock_d(A),0,1,m*n);
            vsip_vview_d *sv = vsip_vcreate_d((m<n)? m:n,VSIP_MEM_NONE);
            vsip_randstate *rnd=vsip_randcreate(7,1,1,VSIP_PRNG);
            vsip_randstate *rnd1=vsip_randcreate(8, 1, 1, VSIP_PRNG);
            printf("----------\nsize %lu %lu\n",m,n);
            if(init) exit(0);
            vsip_mfill_d(0.0,A);
            vsip_vrandn_d(rnd,a);
            vsip_vrandn_d(rnd1,a1);
            vsip_vdestroy_d(a);
            vsip_vdestroy_d(a1);
            if(in == 5 && im == 10){
                a = vsip_vbind_d(vsip_mgetblock_d(A),0,1,m*n);
                vsip_vrandn_d(rnd,a);
                vsip_vdestroy_d(a);
            }
            if(m>2 && n > 2) vsip_mput_d(A, 2, 2, 0.0);
            if(m>4 && n > 4)vsip_mput_d(A, 4, 4, 0.0);
            if(m>4 && n > 4)vsip_mput_d(A, 3, 4, 0.0);
            if(m>2 && n > 2)vsip_mput_d(A, 1, 2, 0.0);
            if(m>2 && n > 2)vsip_mput_d(A,1,2,0.0);
            if(vsip_svd_d(s,A,sv)){
                printf("svd failed\n");
                exit(0);
            }
            vsip_svdmatv_d(s,0,(m < n) ? n-1:m-1,V);
            vsip_svdmatu_d(s,0,(m < n) ? m-1:n-1,U);
            if(in==5 && im == 6){
                printf("A=");mprint_d(A); printf("\n");
                mprint_d(U);
                printf("\n");
                vprint_d(sv);
                printf("\n");
                mprint_d(V);
            }
            if(in==5 && im == 10){
                printf("A=");mprint_d(A); printf("\n");
                mprint_d(U);
                printf("\n");
                vprint_d(sv);
                printf("\n");
                mprint_d(V);
            }
            printf("Check value %f\n",checkBack_d(A,U,sv,V));
            vsip_malldestroy_d(U);vsip_malldestroy_d(V);
            vsip_valldestroy_d(sv);
            vsip_malldestroy_d(A);
            vsip_randdestroy(rnd);
            vsip_randdestroy(rnd1);
            vsip_svd_destroy_d(s);
        }
    }
    svd1_f();
    svd1_d();
    svd2_f();
    svd2_d();
    svd3_f();
    svd3_d();
    svd4_f();
    svd4_d();
    svd5_f();
    svd5_d();
    svd6_f();
    svd6_d();
    svd7_f();
    svd7_d();
    svd8_f();
    vsip_finalize((void*)0);
    return 1;
}
