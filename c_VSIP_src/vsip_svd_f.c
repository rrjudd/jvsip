/*
 *  vsip_svd_f.c
 *  VI_svd
 *
 *  Created by Randall Judd on 12/25/07.
 *
 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#include<vsip.h>
#include <vsip_svdattributes_f.h>
#include <vsip_blockattributes_f.h>
#include <vsip_vviewattributes_f.h>
#include <vsip_vviewattributes_vi.h>
#include"VI_mcolview_f.h"

/* local subroutines */
static void svmul_f(
  vsip_scalar_f alpha,
  const vsip_vview_f *b,
  const vsip_vview_f *r) {
  { 
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride bst = b->stride * b->block->rstride,
                               rst = r->stride * r->block->rstride;
    vsip_scalar_f *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    while(n-- > 0){
       *rp = alpha * *bp;
       bp += bst; rp += rst;
    }
  }
}

static void vsma_f(
                   const vsip_vview_f* a,
                   vsip_scalar_f beta,
                   const vsip_vview_f* c,
                   const vsip_vview_f* r) {
   /* register */ vsip_length n = r->length;
   /* register */ vsip_stride ast = a->stride * a->block->rstride,
   cst = c->stride * c->block->rstride,
   rst = r->stride * r->block->rstride;
   vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
   *cp = (c->block->array) + c->offset * c->block->rstride,
   *rp = (r->block->array) + r->offset * r->block->rstride;
   /* if c == r then this is a saxpy */
   if (cp == rp ){
      while(n-- > 0){ 
         *cp = *ap * beta + *cp;
         ap += ast;
         cp += cst;
      }
   } else {
      while(n-- > 0){
         *rp = (*ap * beta) + *cp;
         ap += ast;
         cp += cst;
         rp += rst;
      }
   }
}

static void vcopy_f_f(
                      const vsip_vview_f* a,
                      const vsip_vview_f* r) {
   vsip_length n   = r->length;
   vsip_stride ast = a->stride * a->block->rstride,
   rst = r->stride * r->block->rstride;
   vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
      *rp = (r->block->array) + r->offset * r->block->rstride;
   /*end define*/
   while(n-- > 0){
      *rp = *ap;
      ap += ast; rp += rst;
   }
}

static void vneg_f(
                   const vsip_vview_f *a,
                   const vsip_vview_f *r) {
   vsip_length n = r->length;
   vsip_stride ast = a->stride * a->block->rstride,
   rst = r->stride * r->block->rstride;
   vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
   *rp = (r->block->array) + r->offset * r->block->rstride;
   while(n-- > 0){
      *rp = - *ap;
      ap += ast; rp += rst;
   }
}

/* Start sort */
#define VRAMP(x) { \
vsip_scalar_vi k; \
vsip_scalar_vi *ind = x->block->array + x->offset; \
vsip_stride str = x->stride; \
for(k=0; k<x->length; k++){ \
*ind = k; \
ind += str;} \
}

/* below adaption of K&R qsort; section 4.10 */

/* return a derefrenced pointer to the i'th element in v */
#define VGET(v,i) (*(v->block->array+(vsip_offset) \
(v->block->rstride * (v->offset + (vsip_stride)i * v->stride))))

/* only float vectors have "rstride" in the current implementation So we need this too*/
#define VGET_VI(v,i) (*(v->block->array+(vsip_offset)  (v->offset + (vsip_stride)i * v->stride)))

#define SWAP(x,i,j) { /* x is float vector view; i,j are indices */ \
vsip_scalar_f tmp = VGET(x,i); \
VGET(x,i) = VGET(x,j); \
VGET(x,j) = tmp; \
}

#define SWAP_VI(x,i,j) { /* x is vector view of type index; i,j are indices */ \
vsip_scalar_vi tmp = VGET_VI(x,i); \
VGET_VI(x,i) = VGET_VI(x,j); \
VGET_VI(x,j) = tmp; \
}

static
void
VI_qsort_f(vsip_vview_f *v, vsip_index left, vsip_index right, vsip_vview_vi *vi){
   vsip_index i,last;
   vsip_index iright;
   if(left >= right){
      return;
   } else {
      iright = (vsip_index)(left+right)/2;
   }
   SWAP(v,left, iright);
   if(vi) SWAP_VI(vi,left,iright);
   last = left;
   for(i=left+1; i<= right; i++){
      if(VGET(v,i) < VGET(v,left)){
         last++;
         SWAP(v,last,i);
         if(vi) SWAP_VI(vi,last,i);
      }
   }
   SWAP(v,left,last);
   if(vi) SWAP_VI(vi,left,last);
   if(last > 0) VI_qsort_f(v,left,last-1,vi);
   VI_qsort_f(v,last+1,right,vi);
   return;
}

static
void
VI_qsortmag_f(vsip_vview_f *v, vsip_index left, vsip_index right, vsip_vview_vi *vi){
   vsip_index i,last;
   vsip_index iright;
   if(left >= right){
      return;
   } else {
      iright = (vsip_index)(left+right)/2;
   }
   SWAP(v,left, iright);
   if(vi) SWAP_VI(vi,left,iright);
   last = left;
   for(i=left+1; i<= right; i++){
      if(fabs(VGET(v,i)) < fabs(VGET(v,left))){
         last++;
         SWAP(v,last,i);
         if(vi) SWAP_VI(vi,last,i);
      }
   }
   SWAP(v,left,last);
   if(vi) SWAP_VI(vi,left,last);
   if(last > 0) VI_qsortmag_f(v,left,last-1,vi);
   VI_qsortmag_f(v,last+1,right,vi);
   return;
}

static void vsortip_f(const vsip_vview_f *in_out, 
                    vsip_sort_mode mode, 
                    vsip_sort_dir dir, 
                    vsip_bool fill,
                    const vsip_vview_vi *vi0){
   vsip_vview_f in = *in_out;
   vsip_vview_vi viN,*vi;
   vi = &viN;
   if(vi0){ /* mirror sort an index */
      viN = *vi0;
      if(fill) VRAMP(vi);
   } else {
      vi = (vsip_vview_vi*)0;
   }
   if(dir == VSIP_SORT_DESCENDING){ /* need to go through vector backwards */
      in.offset += in.stride * (in.length-1);
      in.stride *= -1;
      if(vi0){
         vi->offset += (vi->length - 1) * vi->stride;
         vi->stride *= -1;
      }
   }
   if(VSIP_SORT_BYMAGNITUDE){
      VI_qsortmag_f(&in,(vsip_index) 0,(vsip_index)(in.length-1),vi);
   } else {
      VI_qsort_f(&in,(vsip_index) 0,(vsip_index)(in.length-1),vi);
   }
   return;
}
/* end sort */

/* begine permute */
static void mpermute_once_f(
                          const vsip_mview_f* in,
                          vsip_major major,
                          const vsip_vview_vi* p,
                          const vsip_mview_f* out){
   vsip_length n_dta; /* length of data row/col to copy */
   vsip_length n_ind; /* length of matrix col/row to index */
   vsip_stride in_dta_strd, out_dta_strd;
   vsip_stride in_ind_strd, out_ind_strd;
   vsip_index i,j;
   if(major == VSIP_ROW){ 
      n_dta = in->row_length;
      n_ind = in->col_length;
      in_dta_strd = in->row_stride * in->block->rstride;
      in_ind_strd = in->col_stride * in->block->rstride;
      out_dta_strd = out->row_stride * out->block->rstride;
      out_ind_strd = out->col_stride * out->block->rstride;
   } else {
      n_dta = in->col_length;
      n_ind = in->row_length;
      in_dta_strd = in->col_stride * in->block->rstride;
      in_ind_strd = in->row_stride * in->block->rstride;
      out_dta_strd = out->col_stride * out->block->rstride;
      out_ind_strd = out->row_stride * out->block->rstride;      
   }
   if(in == out) { /* in-place */
      vsip_scalar_f *ptr = in->block->array + in->offset * in->block->rstride;
      vsip_scalar_vi *b = p->block->array + p->offset;
      for(i=0; i<n_ind; i++){
         vsip_index r_or_c = b[i * p->stride]; /* row or column to copy to */
         register vsip_index from0 = b[i * p->stride] * in_ind_strd;
         register vsip_index to0 = i * in_ind_strd;
         if(from0 != to0) {
            for(j=0; j<n_dta; j++){
               vsip_index to = to0 + j * in_dta_strd;
               vsip_index from = from0 + j * in_dta_strd;
               vsip_scalar_f t = ptr[to];
               ptr[to] = ptr[from];
               ptr[from] = t;
            }
            j=i;
            while(i != b[j * p->stride]){
               j++;
               if(j > n_ind) exit(-1);
            }
            b[j * p->stride] = r_or_c;
         }
      } 
   } else { /* out-of-place */
      vsip_scalar_f *in_ptr = in->block->array + in->offset * in->block->rstride;
      vsip_scalar_f *out_ptr = out->block->array + out->offset * out->block->rstride;
      vsip_scalar_vi *in = p->block->array + p->offset;
      for(i=0; i<n_ind; i++){
         vsip_scalar_f *pin = in_ptr + in[i * p->stride] * in_ind_strd;
         vsip_scalar_f *pout = out_ptr + i * out_ind_strd;
         for(j=0; j < n_dta; j++){
            *pout = *pin;
            pout += out_dta_strd;
            pin += in_dta_strd;
         }
      }
   }
   return;
}
/* end permute */

/* Macros needed for code */

#define EPS (FLT_EPSILON * .00001 )

#define SQR(_a) ((_a) * (_a))

/* _val (return value); _dta (data ptr); _str (stride); _l (length) */
/* this is dot(val,val) */
#define AUTODOT(_val, _dta, _str, _l) {\
vsip_index _k; _val=0; \
for(_k=1; _k<_l; _k++) _val += (SQR(_dta[_k*_str]));\
}

/* calculate a householder reflector */
#define HOUSE(_v, _beta, _x, _str, _l)  {\
vsip_scalar_f _sigma, _mu; vsip_index _i; \
AUTODOT(_sigma, _x, _str, _l);\
_v[0] = 1; \
for(_i=1; _i<_l; _i++) _v[_i] = _x[_i * _str];\
if( _sigma == 0 ){ _beta = 0.0; } else { \
_mu = sqrt(SQR(_x[0]) + _sigma); \
_v[0] = ((_x[0] <=0) ? (_x[0] - _mu) : (-_sigma/(_x[0] + _mu)));\
_mu = SQR(_v[0]);\
_beta = (2 * _mu) / (_sigma + _mu); \
for(_i=1; _i<_l; _i++) _v[_i] = _v[_i]/_v[0];\
_v[0]=1.0; }\
}

/* scalar matrix vector prod */
#define SMVPROD(_A, _r,_c,_cl,_cs,_rl,_rs,_v,_w,_beta) {\
vsip_index r,c; vsip_scalar_f t; vsip_index ind;\
for(r=_r; r<_cl; r++){ \
t = 0; ind = r * _cs + _c * _rs;\
for(c=_c; c<_rl; c++){\
t += _A[ind] * _v[c-_c];  ind += _rs;\
}\
_w[r-_r] = _beta * t;\
}}

/* scalar vector matrix prod */
#define SVMPROD(_A, _r,_c,_cl,_cs,_rl,_rs,_v,_w,_beta) {\
vsip_index r,c; vsip_scalar_f t; vsip_index ind;\
for(c=_c; c<_rl; c++){ \
t = 0; ind = _r * _cs + c * _rs;\
for(r=_r; r<_cl; r++){\
t += _A[ind] * _v[r-_r];  ind += _cs;\
}\
_w[c-_c] = _beta * t;\
}}


/* Outer Product Update for householder update */
/* (r,c) implies corner element; A the matrix */
/* cl, cs => column length, stride */
/* rl, rs => row length, stride */
/* _w, _v are vectors for outer product */
/* A - w v' */
#define OPU(_A,_r,_c,_cl,_cs,_rl,_rs,_w,_v) {\
vsip_index r,c; \
   for(r=_r; r<_cl; r++){ \
      vsip_scalar_f t = _v[r-_r];\
      vsip_index ind = r * _cs + _c * _rs;\
      for(c=_c; c<_rl; c++){\
         _A[ind] -= t * _w[c-_c];\
         ind += _rs;\
      }\
   }\
}

/* Matrix product of a matrix times a householder rotation */
#define VI_MHMUL_D(_A,_r,_c,_cl,_cs,_rl,_rs,_beta,_v,_w) { \
SMVPROD(_A, _r,_c,_cl,_cs,_rl,_rs,_v,_w,_beta) \
OPU(_A,_r,_c,_cl,_cs,_rl,_rs,_v,_w)}

/* Matrix product of a householder rotation times a matrix */
#define VI_HMMUL_D(_A,_r,_c,_cl,_cs,_rl,_rs,_beta,_v,_w) { \
SVMPROD(_A, _r,_c,_cl,_cs,_rl,_rs,_v,_w,_beta) \
OPU(_A,_r,_c,_cl,_cs,_rl,_rs,_w,_v);}

/* fill matrix mat with an identity matrix */
/* l=>length; cs=>columnStride; rs=>rowStride */
#define EYE(_mat,_l,_cs, _rs) {\
vsip_index _i,_j; \
for(_i=0; _i < _l; _i++) for(_j=0; _j<_l; _j++) \
_mat[_i * _cs + _j * _rs] = ((_i == _j) ? 1 : 0);}

/* Store a vector in a column of A  starting at (r,c) */
#define STOREVCOL(_A,_r,_c,_cs,_rs,_l,_v) { \
vsip_index _i; vsip_scalar_f *_ptr = _A + _r * _cs + _c * _rs; \
for(_i=0; _i<_l; _i++) _ptr[_i * _cs] = _v[_i];}

/* Store a vector is a row of A starting at (r,c) */
#define STOREVROW(_A,_r,_c,_cs,_rs,_l,_v) { \
vsip_index _i; vsip_scalar_f *_ptr = _A + _r * _cs + _c * _rs; \
for(_i=0; _i<_l; _i++) _ptr[_i * _rs] = _v[_i];}

/* Get a vector stored in a column of A starting at (r,c) */
#define GETVCOL(_A,_r,_c,_cs,_rs,_l,_v) { \
vsip_index _i; vsip_scalar_f *_ptr = _A + _r * _cs + _c * _rs; \
for(_i=0; _i<_l; _i++) _v[_i] = _ptr[_i * _cs];}

/* Get a vector stored in a row of A starting at (r,c) */
#define GETVROW(_A,_r,_c,_cs,_rs,_l,_v) { \
vsip_index _i; vsip_scalar_f *_ptr = _A + _r * _cs + _c * _rs; \
for(_i=0; _i<_l; _i++) _v[_i] = _ptr[_i * _rs];}

/* fill a vector v with val */
/* lng=>length; str=>stride */
#define FILLV(_val,_lng,_str,_v) {\
vsip_index _i; for(_i=0; _i<_lng; _i++) _v[_i * _str] = _val;}

/* copy vector "in" into vector "out" */
/* lng=>length; **Strd => stride */
#define COPYV(_in,_inStrd,_out, _outStrd, _lng) {\
vsip_index _i; for(_i=0; _i<_lng; _i++) _out[_i * _outStrd] = _in[_i * _inStrd];}

/* end macros */

/* Bi-diagonalization */
static int bidiag_f(vsip_sv_f *obj){
   int retval = 0;
   vsip_scalar_f *v = obj->v,  *w=obj->w, *betaR=obj->betaR, *betaL=obj->betaL;
   vsip_length cl, rl, U_n, V_n; /* column, row length, size of U and V */
   vsip_stride   rs, cs, U_cs,U_rs,V_cs,V_rs;    /* strides */
   vsip_scalar_f *A = obj->A->block->array + obj->A->offset * obj->A->block->rstride;
   vsip_scalar_f *ptrA;
   vsip_scalar_f *U, *V;
   vsip_stride i,j;
   /* for A = U S V' */
   /* size of U = M; size of V = L; size of diagonal of S = L */
   vsip_length /*N = obj->N, M = obj->M,*/ L = obj->L;
   if(obj->L == obj->N){
      U=obj->U; V = obj->V;
      U_rs = 1; U_cs=obj->M;
      V_rs = 1; V_cs=obj->N;
      U_n = obj->M; V_n = obj->N;
      cl=obj->M; rl = obj->N;
      rs = obj->A->row_stride   * obj->A->block->rstride;
      cs = obj->A->col_stride   * obj->A->block->rstride;
   } else { /* need to switch U and V and transpose A */
      V=obj->U; U = obj->V;
      U_rs = 1; U_cs=obj->N;
      V_rs = 1; V_cs=obj->M;
      U_n = obj->N; V_n = obj->M;
      cl=obj->N; rl = obj->M;
      cs = obj->A->row_stride   * obj->A->block->rstride;
      rs = obj->A->col_stride   * obj->A->block->rstride;
      
   }
   
   EYE(U,U_n,U_cs,U_rs);
   EYE(V,V_n,V_cs,V_rs);
   for(i=0; i<L; i++){
      j=i;
      ptrA = &A[i * cs + j * rs];
      HOUSE(v,(betaL[i]),ptrA,cs,cl-i);
      if(betaL[i] != 0.0)
         VI_HMMUL_D(A,i,j,cl,cs,rl,rs,(betaL[i]),v,w); 
      STOREVCOL(A,(i+1),j,cs,rs,(cl-(i+1)),(&v[1]));
      if(i < L - 2){
         j = i+1;
         ptrA = &A[i * cs + j * rs];
         HOUSE(v,betaR[j],ptrA,rs,rl-j);
         if(betaR[j] != 0.0)
            VI_MHMUL_D(A,i,j,cl,cs,rl,rs,(betaR[j]),v,w);
         STOREVROW(A,i,(j+1),cs,rs,(rl-(j+1)),(&v[1]));
      }
   }
   {  /* retrieve the diagonal and superdiagonal */
      /* store in d and f for use in VI_gk_f */
      /* the golub-kahan iteration */
      vsip_stride A_str = cs + rs, d_str=1;
      COPYV(A,A_str,obj->d,d_str,L);
      ptrA = A + rs;
      COPYV(ptrA,A_str,obj->f,d_str,(L-1));
   }
   v[0]=1;
   for(i=L-1; i>=0; i--){ /* form U */
      j=i+1;
      GETVCOL(A,(j),i,cs,rs,(cl-j),(&v[1]));
      if(betaL[i] != 0.0)
         VI_HMMUL_D(U,i,i,U_n,U_cs,cl,U_rs,(betaL[i]),v,w);
      if(i<L-2){ /* Form V */
         GETVROW(A,i,(j+1),cs,rs,(rl-(j+1)),(&v[1]));
         if(betaR[j] != 0.0)
            VI_HMMUL_D(V,j,j,V_n,V_cs,rl,V_rs,(betaR[j]),v,w);
      }
   }
   return retval;
}
/* End bi-diagonalization */

/* zero supper diagonal elements */
/* gk => guluk-kahan step but there is more  here than that */
/******************************************************************/
/* EIG_SELECT code calculates the starting value for an iteration */
/* of Golub-Kahan for SVD */
/* looks like
 (m = n-1 in G&V) (here 0 => m-1)
 
 | * f0  0 |
 | 0 dm fm |
 | 0  0 dn |
 
 */
#define EIG_SELECT(_eig, _dm, _dn, _f0, _fm) {\
register double _a = _dm * _dm + _f0 * _f0;\
register double _b = _dm * _fm;\
register double _c = _dn * _dn + _fm * _fm;\
register double _c_a = (_c + _a)/2.0;\
register double _l1 = sqrt(_c_a * _c_a - _a * _c + _b * _b);\
register double _l2 = _c_a - _l1;\
_l1 += _c_a; \
if(fabs(_c - _l1) > fabs(_c - _l2)) \
_eig = _l2;\
else \
_eig = _l1;\
} 

/******************************************************************/

/* inline code for givens transformation */
/* Alg 5.13 G&V */
#define GIVENS_D(a,b,c,s){ \
vsip_scalar_f _tau; \
if(b == 0.0) { c = 1.0; s = 0.0; } else { \
if(fabs(b) > fabs(a)) { \
_tau = -a/b; s = (vsip_scalar_f)(1.0/sqrt(1 + _tau * _tau)); c = s * _tau; } /* mod */\
else { \
_tau = -b/a; c = (vsip_scalar_f)(1.0/sqrt(1 + _tau * _tau)); s = c * _tau; } \
}}

/* below find (givens) rotation macros used in the SVD */
/* note these rotation work on three elements in a row (left) or column (right) */
/* Special rotations at the ends are on two elements */
/* note that c_ret and s_ret should be declared local */
/* to the routine they will be used */
/* c_ret and s_ret are used to get back from the macro the rotation */
/* information which is used to update the matrix decomposition */

/* givens rotation on the LEFT ie matrix product (GR_L * A) */
/* c_ret and s_ret are defined external to the macro */
/* b13 should be zero on entry */
/* b21 should be zero on exit */
/*
 |c -s | |a11 a12 a13| -> |b11 b12 b13|
 |s  c | |a21 a22 a23| => |b21 b22 b23|
 */
#define GR_L(b11,b12,b13, b21,b22,b23) { \
register vsip_scalar_f _a11 = b11, _a12 = b12,\
_a21 = b21, _a22 = b22, _a23 = b23;\
register vsip_scalar_f _c,_s;      \
GIVENS_D(_a11,_a21,_c,_s);     \
b11 = _c * _a11 - _s * _a21; \
b12 = _c * _a12 - _s * _a22; \
b13 = - _s * _a23; \
b21 = 0; \
b22 = _c * _a22 + _s * _a12; \
b23 = _c * _a23 ; \
c_ret = _c; s_ret = _s; \
}

/* givens rotation on the right; matrix product (A * GR_R) */
/* b31 should be zero on entry */
/* b12 should be zero on exit */
/*
 |a11 a12 | | c  s | -> |b11 b12|
 |a21 a22 | |-s  c | -> |b21 b22|
 |a31 a32 |          -> |b31 b32|
 */
#define GR_R(b11,b12,b21,b22,b31,b32) { \
register vsip_scalar_f _a11 = b11, _a12 = b12, \
_a21 = b21, _a22 = b22, \
_a32 = b32; \
register vsip_scalar_f _c,_s;      \
GIVENS_D(_a11,_a12,_c,_s);     \
b11 = _c * _a11 - _s * _a12; \
b21 = _c * _a21 - _s * _a22; \
b31 = - _s * _a32; \
b12 = 0; \
b22 = _c * _a22 + _s * _a21; \
b32 = _c * _a32; \
c_ret = _c; s_ret = _s; \
}

/* special rotation on the right */
/* for GR_R in general we have 3 x 2 but for this case */
/* we are in the upper left corner and only have 2 x 2 */
/* For this case it is probable no zeros will emerge */
/* For this algorithm b21 is assumed to be zero on entry*/
/* for this case the rotation is calculated using section 8.6.2 of G&V 3rd ed. */
/*
 |a11 a12 | | c  s | -> |b11 b12|
 | 0  a22 | |-s  c | -> |b21 b22|
 | 0   0  |          -> | 0   0 |
 */
#define SR_R(c, s, b11,b12,b21,b22) { \
register vsip_scalar_f _a11 = b11, _a12 = b12, _a22 = b22;\
b11 = c * _a11 - s * _a12; \
b12 = c * _a12 + s * _a11; \
b21 = - s * _a22; \
b22 = c * _a22 ; \
}

/* Special rotation on the left */
/* This is a corner case (special rotation) */
/* we can't assume any zeros on entry */
/* on exit b21 must be zero */
/*
 |c -s | |a11 a12| -> |b11 b12|
 |s  c | |a21 a22| => | 0  b22|
 */
#define SR_L(b11,b12,b21,b22) { \
register vsip_scalar_f _a11 = b11, _a21 = b21, _a12 = b12, _a22 = b22;\
register vsip_scalar_f _c,_s;      \
GIVENS_D(_a11,_a21,_c,_s);     \
b11 = _c * _a11 - _s * _a21; \
b12 = _c * _a12 - _s * _a22; \
b21 = 0.0;  \
b22 = _c * _a22 + _s * _a12; \
c_ret = _c; s_ret = _s; \
}

/*
 Zero a superdiagonal entry of a bidiagonal matrix if the diagonal 
 entry in the previous row is zero.
 for instance in matlab or octave <givens(a22,a21)' * A([1,2],:)>
 See G&V page 454 
 |c  -s | |0 a21  0  | -> |0  0  b12 |
 |s   c | |0 a22 a23 | -> |0 b21 b22 |
 */
static vsip_length row_zero_f(vsip_scalar_f *d,
                vsip_scalar_f *f,
                vsip_scalar_f *c_l,
                vsip_scalar_f *s_l,                
                vsip_length n){ 
   vsip_length retval=0;
   vsip_index j;
   vsip_scalar_f c_ret,s_ret,t;
   t = f[0];
   f[0] = 0;
   for(j=0; j<n-1; j++){
      if(t == 0.0) break; /* happens if we run into zero supper diagonal element */
      GIVENS_D(d[j],t,c_ret,s_ret);
      d[j] = c_ret * d[j] - s_ret * t;
      t = s_ret * f[j+1];
      f[j+1] = c_ret * f[j+1];
      c_l[j] = c_ret; s_l[j] = s_ret;
      retval++;
   }
   if(t != 0.0) {
      GIVENS_D(d[(n-1)],t,c_ret,s_ret);
      d[j] = d[j] * c_ret - s_ret * t;
      retval++;
   }
   return retval;
}

/* return the 1 norm for an upper bidiagonal matrix of size n by n-1 */
/* d is the diagonal; f is the supperdiagonal */
static vsip_scalar_f norm1(vsip_scalar_f *d,
                    vsip_scalar_f *f,
                    vsip_length n){
   vsip_index i;
   vsip_scalar_f retval,t=0;
   retval = fabs(d[0]);
   for(i=1; i<n; i++){
      t = fabs(d[i]) + fabs(f[i-1]);
      if(retval < t) retval = t;
   }
   return retval;
}

/* return the frobenius norm for an upper bidiagonal matrix of size n  */
/* d is the diagonal; f is the supperdiagonal */
/* static vsip_scalar_f norm_fro(vsip_scalar_f *d,
                              vsip_scalar_f *f,
                              vsip_length n){
   vsip_index i;
   vsip_scalar_f retval;
   retval = d[0] * d[0];
   for(i=1; i<n; i++){
      retval += d[i] * d[i] + f[i-1] * f[i-1];
   }
   return sqrt(retval);
} */


/* a condition for relative smallness or check for zero */
/* See G&V page 455 */
/* Return true if small */
static vsip_bool f_small( vsip_scalar_f d0,
                  vsip_scalar_f d1,
                  vsip_scalar_f f0,
                  vsip_scalar_f sn){
   vsip_bool ans;
   if (fabs(f0) <= sn * (fabs(d0) + fabs(d1)))
      ans = VSIP_TRUE;
   else
      ans = VSIP_FALSE;
   return ans;
}


/* apply a givens rotation */
/* _c=>cos; _s=>sin; (i,j) => (top,botom) rows affected */
/* _cs=>column stride; _rs=> _row stride; _l implies length of row */
/* note here this is always multiplied on the right and affects rows */
/* this macro is currently not used in the algorithm. I do it long hand */
/* See for instance update functions.  It may come back in the future */
#define MPROD_GIVENS_D(_c, _s, _i, _j, _mat, _cs, _rs, _l) { \
   vsip_scalar_f *_a1, *_a2, _t; vsip_stride _k;\
   _a1 = _mat + _i * _rs; _a2 = _mat + _j * _rs;\
   for(_k=0; _k<_l; _k++){ \
      vsip_index _ind=_k * _cs; \
       _t = _c * _a1[_ind] -_s * _a2[_ind]; \
      _a2[_ind] = _s * _a1[_ind] +  _c * _a2[_ind];\
      _a1[_ind] = _t; \
}}

static void update(vsip_vview_f *buf, vsip_mview_f *U,vsip_scalar_f *c,vsip_scalar_f *s, vsip_index p,vsip_length n){
   vsip_index i;
   vsip_vview_f t = *buf;
   vsip_vview_f x1,x2;
   t.length = U->col_length;
   for(i=p; i<(p+n)-1; i++){
      VI_mcolview_f(U,i,&x1);
      VI_mcolview_f(U,(i+1),&x2);
      svmul_f(c[i-p], &x1 , &t);
      vsma_f(&x2, -s[i-p], &t, &t);
      svmul_f(s[i-p],&x1,&x1);
      vsma_f(&x2, c[i-p], &x1, &x2);
      vcopy_f_f(&t,&x1);
   }
   return;
}

/* update the U matrix for row zero */
/* No V update needed here */
static void zupdate(vsip_vview_f *buf, vsip_mview_f *U,vsip_scalar_f *c,vsip_scalar_f *s, vsip_index p,vsip_length n){
   vsip_index i;
   vsip_index q = p + (vsip_index) n;
   vsip_vview_f t = *buf;
   vsip_vview_f x1,x2;
   t.length = U->col_length;
   VI_mcolview_f(U, p, &x1);
   for(i=p; i<q; i++){
      VI_mcolview_f(U, (i+1), &x2);
      svmul_f(c[i-p], &x1 , &t);
      vsma_f(&x2, s[i-p], &t, &t);
      svmul_f(-s[i-p],&x1,&x1);
      vsma_f(&x2, c[i-p], &x1, &x2);
      vcopy_f_f(&t,&x1);
   }
   return;
}

/* Do one iteration of the Golub-Kahan SVD step */
/* see Alg 8.6.1 of G&V */
static int gk_once_f(vsip_scalar_f *d,
              vsip_scalar_f *f, 
              vsip_scalar_f *c_l,
              vsip_scalar_f *s_l,
              vsip_scalar_f *c_r,
              vsip_scalar_f *s_r,
              vsip_length n){
   int retval=0;
   vsip_index j;
   vsip_scalar_f t1,t2,dm,dn,f0,fm;
   vsip_scalar_f c_ret, s_ret; /* these need to be saved for update of U and V (for later) */
   /* G&V page 452 bottom */
   if(n > 2){
      dn = d[n-1]; dm=d[n-2]; fm = f[n-2]; f0=f[n-3];
      EIG_SELECT(t1,dm,dn,f0,fm);
   } else if(n==2) {
      dn = d[n-1]; dm=d[n-2]; fm = f[n-2]; f0=0;
      EIG_SELECT(t1,dm,dn,f0,fm);
   } else {
      return retval;
   }
   dm = d[0];
   fm = f[0] * dm;
   dm *= dm;
   dm -= t1;
   GIVENS_D(dm,fm,c_ret,s_ret);
   c_r[0] = c_ret; s_r[0] = s_ret;
   SR_R(c_ret,s_ret,d[0],f[0],t1,d[(1)]);
   /* walk down the diagonal */
   for(j=0; j<n-2; j++){
      GR_L((d[j]),(f[j]),t2,t1,(d[(j+1)]),(f[(j+1)]));
      c_l[j] = c_ret; s_l[j] = s_ret;
      GR_R((f[j]),t2, (d[(j+1)]),(f[(j+1)]),t1,(d[(j+2)]));
      c_r[j+1] = c_ret; s_r[j+1] = s_ret;
   } 
   SR_L((d[j]),(f[j]),t1,(d[(j+1)]));
   c_l[j] = c_ret; s_l[j] = s_ret;
   return retval;
}


static int gk_f(vsip_sv_f *svd){
   int retval=0;
   vsip_length n = svd->L;
   vsip_index p=0,q=0;
   vsip_scalar_f *d = svd->d;
   vsip_scalar_f *f = svd->f;
   vsip_scalar_f *c_l=svd->c_l, 
                 *s_l=svd->s_l, 
                 *c_r=svd->c_r, 
                 *s_r=svd->s_r;
   vsip_scalar_f chk0;
   vsip_mview_f mU,mV;
   chk0 = EPS * norm1(d,f,n);
   if(svd->L == svd->N){
      mU = *(svd->mU);
      mV = *(svd->mV);
   } else { /* need to switch things */
      mU = *(svd->mV);           
      mV = *(svd->mU);            
   }
   for(;;){
      vsip_stride k,i;
      vsip_bool gkstep = VSIP_TRUE;
      
      /* search (test) for zeros in f */
      for(k=0; k<n-1; k++){
         if(f[k] != 0.0){
            if(f_small(d[k],d[k+1],f[k],EPS)) f[k]=0.0;
         }
      }
      
      /* search for index of first non-zero in f */
      k = n-2;
      while(k > 0){
         if(f[k] != 0.0) break;
         k--;
      }
      
      /* if all f are zero enter endgame */
      if((k == 0) && (f[0] == 0.0)){
         for(i=0; i<n; i++){
            if(d[i] < 0){
                d[i] = -d[i];
               /* neg col i of V */
               {
                  vsip_vview_f rV; 
                  VI_mcolview_f(&mV, i, &rV);
                  vneg_f(&rV, &rV);
               }
            }
         }
         
         /* sort d and permute U columns V rows */
         /* U -> U * P'; S -> P * S * P'; V' -> P * V' -> V * P' */
         {
            vsip_vview_vi vi_U = *(svd->ui);
            vsip_vview_vi vi = *(svd->vi);
            vi_U.length = mU.row_length;
            vi.length = vsip_vgetlength_f(svd->vd);
            vsortip_f(svd->vd,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,&vi);
            VRAMP((&vi_U));
            /*vsip_vramp_vi(0,1,&vi_U);*/
            vi_U.length = mV.row_length;
            vsip_vcopy_vi_vi(&vi,&vi_U);
            vi_U.length = mU.row_length;
            mpermute_once_f(&mU, VSIP_COL, &vi_U, &mU);
            mpermute_once_f(&mV, VSIP_COL, &vi, &mV);
         }
         break; /* done */
      }
      
      q = k+1; /* q index into d of bottom corner  */
      
      /* search for top of submatrix */
      while(k > 0){
         if(f[k] == 0.0) break;
         k--;
      }
      
      if(k == 0){/* p index into d of top corner */
         if(f[0] != 0.0) 
            p=0;
         else
            p=k+1;
      } else {
         p = k+1;
      }
      
      /* search for zeros on diagonal in submatrix deliniated by index p (top) and q (bottom) */
      for(i=p; i<=q; i++){
         if(fabs(d[i]) < chk0){
            vsip_length l= 0;
            d[i] = 0.0;
            l = row_zero_f(&d[i+1],&f[i],c_l,s_l,(n - i));
            /* apply givens rotations to U */
            if(l != 0) zupdate(svd->buf,&mU,c_l,s_l,i,l);
            gkstep = VSIP_FALSE;
         }
         if((p == 0) && (d[0] != 0) && (q <= 1) && (f[0] != 0)) {
            gk_once_f(d,f,c_l,s_l,c_r,s_r,2);
            update(svd->buf,&mU,c_l,s_l,0,2);
            update(svd->buf,&mV,c_r,s_r,0,2);
            gkstep = VSIP_FALSE;
         }
      }
      if(gkstep) { /* if no zeros were found do gkstep on submatrix */
         gk_once_f(&d[p], &f[p],c_l,s_l,c_r,s_r,(q - p + 1));
         /* apply givens rotations to U and V */
         update(svd->buf,&mU,c_l,s_l,p,(q-p+1));
         update(svd->buf,&mV,c_r,s_r,p,(q-p+1));
      } else { /* if zeros were found do GK step on valid submatrices */
         while(p < q){
            vsip_index p_f = p;
            while((p < q) & (p_f < q)){
               if(d[p] == 0.0){
                  p++;
                  p_f++;
               }else if(d[p_f] != 0.0){
                  p_f++;
               }
               if(d[p_f] == 0.0) break;
            }
            gk_once_f(&d[p], &f[p],c_l,s_l,c_r,s_r,(p_f - p + 1));
            /* apply givens rotations to U and V */
            update(svd->buf,&mU,c_l,s_l,p,(q-p+1));
            update(svd->buf,&mV,c_r,s_r,p,(q-p+1));
            p = p_f;
         }
      }
         
   }
   return retval;
}

int vsip_svd_f(
               vsip_sv_f *obj,
               const vsip_mview_f *A,
               vsip_vview_f *sv){
   int retval = 0;
   vsip_scalar_f *sv_ptr = sv->block->array;
   vsip_stride sv_str = sv->stride * sv->block->rstride;
   obj->Aval = *A;
   retval += bidiag_f(obj);
   /* if(!retval) */
   retval += gk_f(obj);
   COPYV(obj->d, 1, sv_ptr,sv_str,obj->L)
   return retval;
}

