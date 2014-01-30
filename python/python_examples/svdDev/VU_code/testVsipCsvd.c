#include<vsip.h>

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
    vsip_scalar_f retval= vsip_sqrt_f(vsip_msumsqval_f(re)+vsip_msumsqval_f(im));
    vsip_mdestroy_f(re);vsip_mdestroy_f(im);
    return retval;
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
    vsip_scalar_d retval= vsip_sqrt_d(vsip_msumsqval_d(re)+vsip_msumsqval_d(im));
    vsip_mdestroy_d(re);vsip_mdestroy_d(im);
    return retval;
}
static vsip_scalar_d ccheckBack_d(vsip_cmview_d* A,vsip_cmview_d* U, vsip_vview_d* d, vsip_cmview_d* V){
    vsip_scalar_d c;
    vsip_cmview_d *R=vsip_cmcreate_d(vsip_cmgetrowlength_d(V),vsip_cmgetcollength_d(V),VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *Rr=vsip_mrealview_d(R);
    vsip_mview_d *Ri=vsip_mimagview_d(R);
    vsip_cmview_d *Ac=vsip_cmcreate_d(vsip_cmgetcollength_d(A),vsip_cmgetrowlength_d(A),VSIP_ROW,VSIP_MEM_NONE);
    vsip_cmherm_d(V,R);
    vsip_vmmul_d(d,Rr,VSIP_COL,Rr);
    vsip_vmmul_d(d,Ri,VSIP_COL,Ri);
    vsip_cmprod_d(U,R,Ac);
    vsip_cmsub_d(A,Ac,Ac);
    c = cmnormFro_d(Ac);
    vsip_mdestroy_d(Rr);vsip_mdestroy_d(Ri);
    vsip_cmalldestroy_d(Ac);vsip_cmalldestroy_d(R);
    return c;
}


int main(int argc, char* argv[]){
    int init=vsip_init((void*)0);
    vsip_length in,im;
    printf("check complex float\n");
    for(in=5; in<50; in++){
        for(im=5; im<in; im++){
            vsip_length n=in,m=im;
            vsip_csv_f *s=vsip_csvd_create_f(m,n,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
            vsip_cmview_f *A0 = vsip_cmcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_cmview_f *A = vsip_cmcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_mview_f *Ar=vsip_mrealview_f(A);
            vsip_mview_f *Ai=vsip_mimagview_f(A);
            vsip_vview_f *ar = vsip_vbind_f(vsip_mgetblock_f(Ar),0,1,m*n);
            vsip_vview_f *ai = vsip_vbind_f(vsip_mgetblock_f(Ai),0,1,m*n);
            //vsip_vview_f *ar = vsip_mdiagview_f(Ar, 0);
            //vsip_vview_f *ai = vsip_mdiagview_f(Ai, 0);
            vsip_cmview_f *V=vsip_cmcreate_f(n,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_cmview_f *U=vsip_cmcreate_f(m,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_vview_f *sv = vsip_vcreate_f((m < n ? m:n),VSIP_MEM_NONE);
            vsip_randstate *rnd=vsip_randcreate(7,1,1,VSIP_PRNG);
            vsip_randstate *rnd1=vsip_randcreate(8, 1, 1, VSIP_PRNG);
            printf("size %lu %lu\n",m,n);
            if(init) exit(0);
            vsip_mfill_f(0.0, Ar);vsip_mfill_f(0.0, Ai);
            vsip_vrandn_f(rnd,ar); vsip_vrandn_f(rnd,ai);
            vsip_vdestroy_f(ar);vsip_vdestroy_f(ai);
            ar = vsip_mdiagview_f(Ar, 1);
            ai = vsip_mdiagview_f(Ai, 1);
            vsip_vrandn_f(rnd1,ar); vsip_vrandn_f(rnd1,ai);
            if (in > 2 && im > 2) vsip_cmput_f(A, 2, 2, vsip_cmplx_f(0.0, 0.0));
            if (in > 4 && im > 4) vsip_cmput_f(A, 4, 4, vsip_cmplx_f(0.0, 0.0));
            if (in > 2 && im > 2) vsip_cmput_f(A,1,2,vsip_cmplx_f(0.0,0.0));
            if (in > 4 && im > 3) vsip_cmput_f(A,3,4,vsip_cmplx_f(0.0,0.0));
            if (in > 1 && im > 2) vsip_cmput_f(A,0,1,vsip_cmplx_f(0.0,0.0));
            vsip_cmcopy_f_f(A,A0);
            if(vsip_csvd_f(s,A0,sv)){
                printf("svd failed\n");
                exit(0);
            }
            vsip_csvdmatv_f(s,0,(m < n) ? n-1:m-1,V);
            vsip_csvdmatu_f(s,0,(m < n) ? m-1:n-1,U);
            if(in==6 && im == 5){
                printf("A = ");cmprint_f(A); printf("\n");
                cmprint_f(U);
                printf("\n");
                vprint_f(sv);
                printf("\n");
                cmprint_f(V);
            }
            printf("Check value %f\n-----------------------------\n",ccheckBack_f(A,U,sv,V));
            vsip_cmalldestroy_f(U);
            vsip_cmalldestroy_f(V);
            vsip_valldestroy_f(sv);
            vsip_vdestroy_f(ai);
            vsip_vdestroy_f(ar);
            vsip_mdestroy_f(Ar);
            vsip_mdestroy_f(Ai);
            vsip_cmalldestroy_f(A);
            vsip_randdestroy(rnd);
            vsip_randdestroy(rnd1);
            vsip_csvd_destroy_f(s);
            
        }
    }
    printf("check complex double\n");
    for(in=5; in<50; in++){
        for(im=5; im<in; im++){
            vsip_length n=in,m=im;
            vsip_csv_d *s=vsip_csvd_create_d(m,n,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
            vsip_cmview_d *A0 = vsip_cmcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_cmview_d *A = vsip_cmcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_mview_d *Ar=vsip_mrealview_d(A);
            vsip_mview_d *Ai=vsip_mimagview_d(A);
            vsip_vview_d *ar = vsip_vbind_d(vsip_mgetblock_d(Ar),0,1,m*n);
            vsip_vview_d *ai = vsip_vbind_d(vsip_mgetblock_d(Ai),0,1,m*n);
            //vsip_vview_d *ar = vsip_mdiagview_d(Ar, 0);
            //vsip_vview_d *ai = vsip_mdiagview_d(Ai, 0);
            vsip_cmview_d *V=vsip_cmcreate_d(n,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_cmview_d *U=vsip_cmcreate_d(m,(m < n) ? m:n,VSIP_ROW,VSIP_MEM_NONE);
            vsip_vview_d *sv = vsip_vcreate_d((m < n ? m:n),VSIP_MEM_NONE);
            vsip_randstate *rnd=vsip_randcreate(7,1,1,VSIP_PRNG);
            vsip_randstate *rnd1=vsip_randcreate(8, 1, 1, VSIP_PRNG);
            printf("size %lu %lu\n",m,n);
            if(init) exit(0);
            vsip_mfill_d(0.0, Ar);vsip_mfill_d(0.0, Ai);
            vsip_vrandn_d(rnd,ar); vsip_vrandn_d(rnd,ai);
            vsip_vdestroy_d(ar);vsip_vdestroy_d(ai);
            ar = vsip_mdiagview_d(Ar, 1);
            ai = vsip_mdiagview_d(Ai, 1);
            vsip_vrandn_d(rnd1,ar); vsip_vrandn_d(rnd1,ai);
            if (in > 2 && im > 2) vsip_cmput_d(A, 2, 2, vsip_cmplx_d(0.0, 0.0));
            if (in > 4 && im > 4) vsip_cmput_d(A, 4, 4, vsip_cmplx_d(0.0, 0.0));
            if (in > 2 && im > 2) vsip_cmput_d(A,1,2,vsip_cmplx_d(0.0,0.0));
            if (in > 4 && im > 3) vsip_cmput_d(A,3,4,vsip_cmplx_d(0.0,0.0));
            if (in > 1 && im > 2) vsip_cmput_d(A,0,1,vsip_cmplx_d(0.0,0.0));
            vsip_cmcopy_d_d(A,A0);
            if(vsip_csvd_d(s,A0,sv)){
                printf("svd failed\n");
                exit(0);
            }
            vsip_csvdmatv_d(s,0,(m < n) ? n-1:m-1,V);
            vsip_csvdmatu_d(s,0,(m < n) ? m-1:n-1,U);
            if(in==6 && im == 5){
                printf("A = ");cmprint_d(A); printf("\n");
                cmprint_d(U);
                printf("\n");
                vprint_d(sv);
                printf("\n");
                cmprint_d(V);
            }
            printf("Check value %f\n-----------------------------\n",ccheckBack_d(A,U,sv,V));
            vsip_cmalldestroy_d(U);
            vsip_cmalldestroy_d(V);
            vsip_valldestroy_d(sv);
            vsip_vdestroy_d(ai);
            vsip_vdestroy_d(ar);
            vsip_mdestroy_d(Ar);
            vsip_mdestroy_d(Ai);
            vsip_cmalldestroy_d(A);
            vsip_cmalldestroy_d(A0);
            vsip_randdestroy(rnd);
            vsip_randdestroy(rnd1);
            vsip_csvd_destroy_d(s);
            
        }
    }
    vsip_finalize((void*)0);
    return 1;
}
