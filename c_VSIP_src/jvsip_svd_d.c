/*
 //  jvsip_svd_d.c
 //  jvsipF
 //
 //  Created by RANDALL JUDD on 4/21/13.
 //  Copyright (c) 2013 Independent Consultant. All rights reserved.
 */
/*********************************************************************
 // This code includes no warranty, express or implied, including     /
 // the warranties of merchantability and fitness for a particular    /
 // purpose.                                                          /
 // No person or entity assumes any legal liability or responsibility /
 // for the accuracy, completeness, or usefulness of any information, /
 // apparatus, product, or process disclosed, or represents that      /
 // its use would not infringe privately owned rights.                /
 *********************************************************************/
/*********************************************************************
 // The MIT License (see copyright for jvsip in top level directory)
 // http://opensource.org/licenses/MIT
 **********************************************************************/
#include"vsip.h"
#include"vsip_svdattributes_d.h"
#include"VI.h"
#include"vsip_blockattributes_d.h"
#include"vsip_cblockattributes_d.h"
#include"vsip_blockattributes_vi.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_mviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"
#include"vsip_cmviewattributes_d.h"
#include"vsip_vviewattributes_vi.h"

#define EPS DBL_EPSILON
#define VI_VGET_F(v,i) (*(v->block->array + (v->offset + (vsip_stride)(i) * v->stride) * v->block->rstride))

#define scaleV(v) { \
vsip_index k;vsip_scalar_d *p = v->block->array + v->offset * v->block->rstride;\
vsip_stride std = v->stride * v->block->rstride;vsip_length n = v->length * std;\
vsip_scalar_d scl = p[0];p[0]=1.0;for(k=std; k<n; k+=std) p[k] /= scl; \
}

#define CMAG_F(re,im) ((re == 0.0) ? im:(im< re) ? re * (vsip_scalar_d)sqrt(1.0 + (im/re) * (im/re)): \
im * (vsip_scalar_d)sqrt(1.0 + (re/im) * (re/im)))

/* coded for this routine. Only done in place */
#define csvmul_d(alpha, b) {\
vsip_length _n = b->length; vsip_stride cbst = b->block->cstride;\
vsip_scalar_d *bpr = b->block->R->array + cbst * b->offset,*bpi = b->block->I->array + cbst * b->offset;\
register vsip_scalar_d temp; vsip_stride bst = cbst * b->stride;\
while(_n-- > 0){temp = alpha.r * *bpr - *bpi * alpha.i;*bpi = alpha.r * *bpi + alpha.i * *bpr;*bpr = temp;\
bpr += bst; bpi += bst;}}

#define cvcopy_d(a, r) {\
vsip_length _n =  (r)->length;vsip_stride cast = (a)->block->cstride,crst = (r)->block->cstride;\
vsip_scalar_d *apr = (a)->block->R->array + cast * (a)->offset,*rpr = (r)->block->R->array + crst * (r)->offset;\
vsip_scalar_d *api = (a)->block->I->array + cast * (a)->offset,*rpi = (r)->block->I->array + crst * (r)->offset;\
vsip_stride ast = (cast * (a)->stride),rst = (crst * (r)->stride);\
while(_n-- > 0){*rpr = *apr;*rpi = *api;apr += ast; api += ast;rpr += rst; rpi += rst;}}

#define vcopy_d(a,r) {vsip_length _n   = (r)->length;\
vsip_stride ast = (a)->stride * (a)->block->rstride,rst = (r)->stride * (r)->block->rstride;\
vsip_scalar_d *ap = (a)->block->array + (a)->offset * (a)->block->rstride,*rp = (r)->block->array+(r)->offset * (r)->block->rstride;\
while(_n-- > 0){*rp = *ap;ap += ast; rp += rst;}}

#define vcopy_vi(a,r) {vsip_length _n   = (r)->length;\
vsip_stride ast = (a)->stride,rst = (r)->stride;\
vsip_scalar_vi *ap = (a)->block->array + (a)->offset,*rp = (r)->block->array+(r)->offset;\
while(_n-- > 0){*rp = *ap;ap += ast; rp += rst;}}

#define mcopy_d(a,r) {vsip_length n_mj,n_mn;vsip_stride ast_mj, ast_mn,rst_mj, rst_mn;\
vsip_scalar_d *rp = ((r)->block->array) + (r)->offset * (r)->block->rstride,\
*ap = ((a)->block->array) + (a)->offset * (a)->block->rstride;vsip_scalar_d *rp0 = rp,*ap0 = ap;\
if((r)->row_stride < (r)->col_stride){n_mj   = (r)->row_length; n_mn = (r)->col_length;\
rst_mj = (r)->row_stride; rst_mn = (r)->col_stride;ast_mj = (a)->row_stride; ast_mn = (a)->col_stride;\
rst_mj *= (r)->block->rstride; rst_mn *= (r)->block->rstride;ast_mj *= (a)->block->rstride; ast_mn *= (a)->block->rstride;\
} else {n_mn = (r)->row_length; n_mj = (r)->col_length;\
rst_mn = (r)->row_stride; rst_mj = (r)->col_stride;ast_mn = (a)->row_stride; ast_mj = (a)->col_stride;\
rst_mn *= (r)->block->rstride; rst_mj *= (r)->block->rstride;ast_mn *= (a)->block->rstride; ast_mj *= (a)->block->rstride;\
} while(n_mn-- > 0){vsip_length n = n_mj;while(n-- >0){*rp = *ap;ap += ast_mj;  rp += rst_mj;\
}ap0 += ast_mn; rp0 += rst_mn;ap = ap0; rp = rp0;}}

#define cmcopy_d(a,r) {vsip_length n_mj, n_mn; vsip_stride ast_mj, ast_mn,rst_mj, rst_mn; \
vsip_scalar_d *ap_r = (a)->block->R->array + (a)->offset * (a)->block->cstride,*rp_r = (r)->block->R->array + (r)->offset * (r)->block->cstride;\
vsip_scalar_d *ap_i = (a)->block->I->array + (a)->offset * (a)->block->cstride,*rp_i = (r)->block->I->array + (r)->offset * (r)->block->cstride;\
vsip_scalar_d *ap0_r = ap_r,*rp0_r = rp_r,*ap0_i = ap_i,*rp0_i = rp_i;\
if((r)->row_stride < (r)->col_stride){n_mj = (r)->row_length; n_mn = (r)->col_length;\
rst_mj = (r)->row_stride; rst_mn = (r)->col_stride;ast_mj = (a)->row_stride; ast_mn = (a)->col_stride;\
rst_mj *= (r)->block->cstride; rst_mn *= (r)->block->cstride;ast_mj *= (a)->block->cstride; ast_mn *= (a)->block->cstride;\
} else {n_mn = (r)->row_length; n_mj = (r)->col_length;\
rst_mn = (r)->row_stride; rst_mj = (r)->col_stride;ast_mn = (a)->row_stride; ast_mj = (a)->col_stride;\
rst_mn *= (r)->block->cstride; rst_mj *= (r)->block->cstride;ast_mn *= (a)->block->cstride; ast_mj *= (a)->block->cstride;}\
while(n_mn-- > 0){vsip_length n = n_mj;while(n-- >0){*rp_r = *ap_r;*rp_i = *ap_i;ap_r += ast_mj;  rp_r += rst_mj;\
ap_i += ast_mj;  rp_i += rst_mj;}ap0_r += ast_mn; rp0_r += rst_mn;ap0_i += ast_mn; rp0_i += rst_mn;\
ap_r = ap0_r; rp_r = rp0_r; ap_i = ap0_i; rp_i = rp0_i;}}

#define cmherm_d(_A,_R) {	\
vsip_length  lx = _A->row_length,ly = _A->col_length;vsip_stride cAst = _A->block->cstride,cRst = _R->block->cstride;\
vsip_scalar_d *a_p_r = _A->block->R->array + cAst * _A->offset,\
*a_p_i = _A->block->I->array + cAst * _A->offset,*r_p_r = _R->block->R->array + cRst * _R->offset, *r_p_i;vsip_length i, j;\
vsip_stride stAx = cAst * _A->row_stride, stAy = cAst *_A->col_stride, stRx = cRst * _R->row_stride,stRy = cRst *_R->col_stride;\
for(i=0; i<ly; i++){\
r_p_r = _R->block->R->array + cRst * _R->offset + i * stRx;r_p_i = _R->block->I->array + cRst * _R->offset + i * stRx;\
a_p_r = _A->block->R->array + cAst * _A->offset + i * stAy;a_p_i = _A->block->I->array + cAst * _A->offset + i * stAy;\
for(j=0; j<lx; j++){*r_p_r = *a_p_r;*r_p_i = - *a_p_i;r_p_r += stRy; a_p_r += stAx;r_p_i += stRy; a_p_i += stAx;}}}

#define cmconj_d( a, r) { vsip_length n_mj, n_mn; vsip_stride ast_mj, ast_mn, rst_mj, rst_mn; \
vsip_scalar_d *ap_r = (a)->block->R->array + (a)->offset * (a)->block->cstride, *rp_r = (r)->block->R->array + (r)->offset * (r)->block->cstride, \
*ap_i = (a)->block->I->array + (a)->offset * (a)->block->cstride, *rp_i = (r)->block->I->array + (r)->offset * (r)->block->cstride, \
*ap0_r = ap_r, *rp0_r = rp_r, *ap0_i = ap_i, *rp0_i = rp_i; \
if((r)->row_stride < (r)->col_stride){ n_mj = (r)->row_length; n_mn = (r)->col_length; \
rst_mj = (r)->row_stride; rst_mn = (r)->col_stride; ast_mj = (a)->row_stride; ast_mn = (a)->col_stride; \
rst_mj *= (r)->block->cstride; rst_mn *= (r)->block->cstride; ast_mj *= (a)->block->cstride; ast_mn *= (a)->block->cstride; \
} else { n_mn = (r)->row_length; n_mj = (r)->col_length; \
rst_mn = (r)->row_stride; rst_mj = (r)->col_stride; ast_mn = (a)->row_stride; ast_mj = (a)->col_stride; \
rst_mn *= (r)->block->cstride; rst_mj *= (r)->block->cstride; ast_mn *= (a)->block->cstride; ast_mj *= (a)->block->cstride; \
} while(n_mn-- > 0){ vsip_length _n = n_mj; while(_n-- >0){ \
*rp_r = *ap_r; *rp_i = - *ap_i; ap_r += ast_mj; rp_r += rst_mj; ap_i += ast_mj; rp_i += rst_mj; \
} ap0_r += ast_mn; rp0_r += rst_mn; ap_r = ap0_r;    rp_r = rp0_r; ap0_i += ast_mn; rp0_i += rst_mn; ap_i = ap0_i;rp_i = rp0_i;}}

#define mpermute_onceCol_d(in, p){ vsip_scalar_d *ptr,t;vsip_length ndta, n_ind; vsip_stride indta_strd, in_ind_strd; \
register vsip_index to0; register vsip_index from0; vsip_index _i,_j,*b,from,to;\
ndta = in->col_length; n_ind = in->row_length; indta_strd = in->col_stride * in->block->rstride;\
in_ind_strd = in->row_stride * in->block->rstride; ptr = in->block->array + in->offset * in->block->rstride;\
b = p->block->array + p->offset; for(_i=0; _i<n_ind; _i++){ vsip_index r_or_c = b[_i * p->stride];\
from0 = b[_i * p->stride] * in_ind_strd; to0 = _i * in_ind_strd;\
if(from0 != to0) { for(_j=0; _j<ndta; _j++){to = to0 + _j * indta_strd, from = from0 + _j * indta_strd;\
t = ptr[to]; ptr[to] = ptr[from]; ptr[from] = t; } _j=_i;\
while(_i != b[_j * p->stride]){ _j++; if(_j > n_ind) exit(-1); } b[_j * p->stride] = r_or_c;}}}

#define mpermute_onceRow_d(in, p) { vsip_index _i,_j,from,to; vsip_length ndta, n_ind; \
vsip_stride indta_strd=in->row_stride * in->block->rstride,in_ind_strd=in->col_stride * in->block->rstride;\
vsip_scalar_d *ptr = in->block->array + in->offset * in->block->rstride,t;\
vsip_scalar_vi *b = p->block->array + p->offset; ndta = in->row_length; n_ind = in->col_length;\
for(_i=0; _i<n_ind; _i++){ vsip_index r_or_c = b[_i * p->stride]; \
register vsip_index from0 = b[_i * p->stride] * in_ind_strd; register vsip_index to0 = _i * in_ind_strd;\
if(from0 != to0) { for(_j=0; _j<ndta; _j++){ to = to0 + _j * indta_strd; from = from0 + _j * indta_strd;\
t = ptr[to]; ptr[to] = ptr[from]; ptr[from] = t; } _j=_i; while(_i != b[_j * p->stride])\
{ _j++; if(_j > n_ind) exit(-1);}b[_j * p->stride] = r_or_c; } } }

#define cmpermute_onceCol_d(in, p){\
vsip_length ndta=in->col_length, n_ind=in->row_length; vsip_stride indta_strd, in_ind_strd; vsip_index _i,_j;\
vsip_scalar_d *ptr_re = in->block->R->array + in->offset * in->block->cstride, \
*ptr_im = in->block->I->array + in->offset * in->block->cstride;\
vsip_scalar_vi *b = p->block->array + p->offset;\
indta_strd = in->col_stride * in->block->cstride; in_ind_strd = in->row_stride * in->block->cstride;\
for(_i=0; _i<n_ind; _i++){vsip_index r_or_c = b[_i * p->stride]; \
register vsip_index from0 = b[_i * p->stride] * in_ind_strd; register vsip_index to0 = _i * in_ind_strd;\
if(from0 != to0) { for(_j=0; _j<ndta; _j++){ vsip_index to = to0 + _j * indta_strd; \
vsip_index from = from0 + _j * indta_strd;vsip_scalar_d t = ptr_re[to]; ptr_re[to] = ptr_re[from];\
ptr_re[from] = t; t = ptr_im[to];ptr_im[to] = ptr_im[from]; ptr_im[from] = t;\
}_j=_i; while(_i != b[_j * p->stride]){ _j++; if(_j > n_ind) exit(-1); } b[_j * p->stride] = r_or_c; } } }

#define cmpermute_onceRow_d( in, p){\
vsip_length ndta, n_ind; vsip_stride indta_strd, in_ind_strd; vsip_index _i,_j;\
vsip_scalar_d *ptr_re = in->block->R->array + in->offset * in->block->cstride, \
*ptr_im = in->block->I->array + in->offset * in->block->cstride;\
vsip_scalar_vi *b = p->block->array + p->offset; ndta = in->row_length; n_ind = in->col_length;\
indta_strd = in->row_stride * in->block->cstride; in_ind_strd = in->col_stride * in->block->cstride;\
for(_i=0; _i<n_ind; _i++){ vsip_index r_or_c = b[_i * p->stride]; \
register vsip_index from0 = b[_i * p->stride] * in_ind_strd; register vsip_index to0 = _i * in_ind_strd;\
if(from0 != to0) { for(_j=0; _j<ndta; _j++){ vsip_index to = to0 + _j * indta_strd; \
vsip_index from = from0 + _j * indta_strd;vsip_scalar_d t = ptr_re[to]; ptr_re[to] = ptr_re[from]; \
ptr_re[from] = t; t = ptr_im[to]; ptr_im[to] = ptr_im[from]; ptr_im[from] = t;\
}_j=_i; while(_i != b[_j * p->stride]){ _j++; if(_j > n_ind) exit(-1); } b[_j * p->stride] = r_or_c;}}}

#define vmprod_d(a,B,r) {vsip_length nx=0,mx=0;\
vsip_scalar_d *ap=(a)->block->array+(a)->offset * (a)->block->rstride,*ap0=ap,\
*rp=(r)->block->array+(r)->offset * (r)->block->rstride, *Byp=(B)->block->array+(B)->offset * (B)->block->rstride,*Bxp = Byp;\
vsip_stride BCst = (B)->col_stride * (B)->block->rstride,BRst=(B)->row_stride * (B)->block->rstride,\
rst  = (r)->stride * (r)->block->rstride; while(nx++ < (B)->row_length){*rp=0;mx=0;\
while(mx++ < (B)->col_length){ *rp += *ap * *Byp; ap += (a)->stride; Byp += BCst; }ap = ap0; Byp = (Bxp += BRst); rp += rst;}}

#define mvprod_d(_A, _b, _r) {vsip_length nx=0, mx=0;\
vsip_scalar_d  *bp=(_b)->block->array+(_b)->offset * (_b)->block->rstride,\
*rp=(_r)->block->array+(_r)->offset * (_r)->block->rstride, *Ayp=(_A)->block->array+(_A)->offset * (_A)->block->rstride, *Axp=Ayp;\
vsip_stride rst=(_r)->stride * (_r)->block->rstride, ARst=(_A)->row_stride * (_A)->block->rstride,\
ACst=(_A)->col_stride * (_A)->block->rstride, bst=(_b)->stride * (_b)->block->rstride;\
while(nx++ < (_A)->col_length){ *rp=0; mx=0; while(mx++ < (_A)->row_length){ *rp += *bp * *Axp; bp += bst; Axp += ARst; }\
bp=(_b)->block->array+(_b)->offset * (_b)->block->rstride; Axp=(Ayp += ACst); rp += rst; } }

#define cvmprod_d(_a,_B,_r) { vsip_length nx = 0, mx = 0; \
vsip_stride cast = (_a)->block->cstride, crst = (_r)->block->cstride, cBst = (_B)->block->cstride;\
vsip_scalar_d *ap_r = (vsip_scalar_d*)((_a)->block->R->array + cast * (_a)->offset),\
*ap_i = (vsip_scalar_d*)((_a)->block->I->array + cast * (_a)->offset),\
*rp_r = (vsip_scalar_d*)((_r)->block->R->array + crst * (_r)->offset),\
*rp_i = (vsip_scalar_d*)((_r)->block->I->array + crst * (_r)->offset),\
*Byp_r = (vsip_scalar_d*)((_B)->block->R->array + cBst * (_B)->offset),\
*Byp_i = (vsip_scalar_d*)((_B)->block->I->array + cBst * (_B)->offset),\
*Bxpr = Byp_r, *Bxpi = Byp_i; vsip_stride sta = cast * (_a)->stride, str = crst * (_r)->stride, stB = cBst * (_B)->col_stride;\
while(nx++ < (_B)->row_length){ *rp_r = 0; *rp_i = 0; mx = 0;\
while(mx++ < (_B)->col_length){\
*rp_r += *ap_r * *Byp_r - *ap_i * *Byp_i; \
*rp_i += *ap_i * *Byp_r + *ap_r * *Byp_i;\
ap_r += sta; Byp_r += stB; ap_i += sta; Byp_i += stB; } \
ap_r = (vsip_scalar_d*)((_a)->block->R->array + cast * (_a)->offset); ap_i = (vsip_scalar_d*)((_a)->block->I->array + cast * (_a)->offset);\
Byp_r = (Bxpr += (cBst * (_B)->row_stride)); Byp_i = (Bxpi += (cBst * (_B)->row_stride)); rp_r += str; rp_i += str;}}

#define cvmprodj_d(_a,_B,_r) { vsip_length nx = 0, mx = 0; \
vsip_stride cast = (_a)->block->cstride, crst = (_r)->block->cstride, cBst = (_B)->block->cstride;\
vsip_scalar_d *ap_r = (vsip_scalar_d*)((_a)->block->R->array + cast * (_a)->offset),\
*ap_i = (vsip_scalar_d*)((_a)->block->I->array + cast * (_a)->offset),\
*rp_r = (vsip_scalar_d*)((_r)->block->R->array + crst * (_r)->offset),\
*rp_i = (vsip_scalar_d*)((_r)->block->I->array + crst * (_r)->offset),\
*Byp_r = (vsip_scalar_d*)((_B)->block->R->array + cBst * (_B)->offset),\
*Byp_i = (vsip_scalar_d*)((_B)->block->I->array + cBst * (_B)->offset),\
*Bxpr = Byp_r, *Bxpi = Byp_i; vsip_stride sta = cast * (_a)->stride, str = crst * (_r)->stride, stB = cBst * (_B)->col_stride;\
while(nx++ < (_B)->row_length){ *rp_r = 0; *rp_i = 0; mx = 0;\
while(mx++ < (_B)->col_length){ \
*rp_r += *ap_r * *Byp_r + *ap_i * *Byp_i; \
*rp_i += *ap_i * *Byp_r - *ap_r * *Byp_i;\
ap_r += sta; Byp_r += stB; ap_i += sta; Byp_i += stB; } \
ap_r = (vsip_scalar_d*)((_a)->block->R->array + cast * (_a)->offset); ap_i = (vsip_scalar_d*)((_a)->block->I->array + cast * (_a)->offset);\
Byp_r = (Bxpr += (cBst * (_B)->row_stride)); Byp_i = (Bxpi += (cBst * (_B)->row_stride)); rp_r += str; rp_i += str;}}

#define cmvprod_d(_A,_b,_r){ \
if(((_A)->block->cstride == 2) && ((_b)->block->cstride == 2) && ((_r)->block->cstride == 2)){\
vsip_length nx = 0, mx = 0; vsip_stride cbst = (_b)->block->cstride, crst = (_b)->block->cstride, cAst = (_A)->block->cstride;\
vsip_scalar_d *bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset),\
*rp_r = (vsip_scalar_d*)((_r)->block->R->array + crst * (_r)->offset),\
*Axp_r = (vsip_scalar_d*)((_A)->block->R->array + cAst * (_A)->offset),\
*Aypr = Axp_r; vsip_stride stb = cbst * (_b)->stride, str = crst * (_r)->stride, stA = cAst * (_A)->row_stride;\
vsip_scalar_d dot_r, dot_i; while(nx++ < (_A)->col_length){ mx = 0; dot_r = 0; dot_i = 0;\
while(mx++ < (_A)->row_length){ vsip_scalar_d Ar = *Axp_r, Ai = *(Axp_r + 1); vsip_scalar_d br = *bp_r, bi = *(bp_r + 1);\
dot_r += br * Ar - bi * Ai; \
dot_i += bi * Ar + br * Ai; \
bp_r += stb; Axp_r += stA; } *rp_r = dot_r; *(rp_r + 1) = dot_i;\
bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset); Axp_r = (Aypr += (cAst * (_A)->col_stride));rp_r += str;}\
} else { vsip_length nx = 0, mx = 0;\
vsip_stride cbst = (_b)->block->cstride, crst = (_r)->block->cstride, cAst = (_A)->block->cstride;\
vsip_scalar_d *bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset),\
*bp_i = (vsip_scalar_d*)((_b)->block->I->array + cbst * (_b)->offset),\
*rp_r = (vsip_scalar_d*)((_r)->block->R->array + crst * (_r)->offset),\
*rp_i = (vsip_scalar_d*)((_r)->block->I->array + crst * (_r)->offset),\
*Axp_r = (vsip_scalar_d*)((_A)->block->R->array + cAst * (_A)->offset),\
*Axp_i = (vsip_scalar_d*)((_A)->block->I->array + cAst * (_A)->offset),\
*Aypr = Axp_r, *Aypi = Axp_i; vsip_stride stb = cbst * (_b)->stride, str = crst * (_r)->stride, stA = cAst * (_A)->row_stride;\
vsip_scalar_d dot_r, dot_i; while(nx++ < (_A)->col_length){ dot_r = 0; dot_i = 0; mx = 0;\
while(mx++ < (_A)->row_length){ \
dot_r += *bp_r * *Axp_r - *bp_i * *Axp_i; \
dot_i += *bp_i * *Axp_r + *bp_r * *Axp_i;\
bp_r += stb; Axp_r += stA; bp_i += stb; Axp_i += stA; }\
*rp_r = dot_r; *rp_i = dot_i; bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset);\
bp_i = (vsip_scalar_d*)((_b)->block->I->array + cbst * (_b)->offset); Axp_r = (Aypr += (cAst * (_A)->col_stride));\
Axp_i = (Aypi += (cAst * (_A)->col_stride)); rp_r += str; rp_i += str; }}}

#define cmvjprod_d(_A,_b,_r){ \
if(((_A)->block->cstride == 2) && ((_b)->block->cstride == 2) && ((_r)->block->cstride == 2)){\
vsip_length nx = 0, mx = 0; vsip_stride cbst = (_b)->block->cstride, crst = (_b)->block->cstride, cAst = (_A)->block->cstride;\
vsip_scalar_d *bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset),\
*rp_r = (vsip_scalar_d*)((_r)->block->R->array + crst * (_r)->offset),\
*Axp_r = (vsip_scalar_d*)((_A)->block->R->array + cAst * (_A)->offset),\
*Aypr = Axp_r; vsip_stride stb = cbst * (_b)->stride, str = crst * (_r)->stride, stA = cAst * (_A)->row_stride;\
vsip_scalar_d dot_r, dot_i; while(nx++ < (_A)->col_length){ mx = 0; dot_r = 0; dot_i = 0;\
while(mx++ < (_A)->row_length){ vsip_scalar_d Ar = *Axp_r, Ai = *(Axp_r + 1); vsip_scalar_d br = *bp_r, bi = *(bp_r + 1);\
dot_r += br * Ar + bi * Ai; \
dot_i += bi * Ar - br * Ai ; \
bp_r += stb; Axp_r += stA; } *rp_r = dot_r; *(rp_r + 1) = dot_i;\
bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset); Axp_r = (Aypr += (cAst * (_A)->col_stride));rp_r += str;}\
} else { vsip_length nx = 0, mx = 0;\
vsip_stride cbst = (_b)->block->cstride, crst = (_r)->block->cstride, cAst = (_A)->block->cstride;\
vsip_scalar_d *bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset),\
*bp_i = (vsip_scalar_d*)((_b)->block->I->array + cbst * (_b)->offset),\
*rp_r = (vsip_scalar_d*)((_r)->block->R->array + crst * (_r)->offset),\
*rp_i = (vsip_scalar_d*)((_r)->block->I->array + crst * (_r)->offset),\
*Axp_r = (vsip_scalar_d*)((_A)->block->R->array + cAst * (_A)->offset),\
*Axp_i = (vsip_scalar_d*)((_A)->block->I->array + cAst * (_A)->offset),\
*Aypr = Axp_r, *Aypi = Axp_i; vsip_stride stb = cbst * (_b)->stride, str = crst * (_r)->stride, stA = cAst * (_A)->row_stride;\
vsip_scalar_d dot_r, dot_i; while(nx++ < (_A)->col_length){ dot_r = 0; dot_i = 0; mx = 0;\
while(mx++ < (_A)->row_length){ \
dot_r += *bp_r * *Axp_r + *bp_i * *Axp_i; \
dot_i += *bp_i * *Axp_r - *bp_r * *Axp_i; \
bp_r += stb; Axp_r += stA; bp_i += stb; Axp_i += stA; }\
*rp_r = dot_r; *rp_i = dot_i; bp_r = (vsip_scalar_d*)((_b)->block->R->array + cbst * (_b)->offset);\
bp_i = (vsip_scalar_d*)((_b)->block->I->array + cbst * (_b)->offset); Axp_r = (Aypr += (cAst * (_A)->col_stride));\
Axp_i = (Aypi += (cAst * (_A)->col_stride)); rp_r += str; rp_i += str; }}}

#define svmul_d(alpha, _b, _r) {vsip_length n = (_r)->length;\
vsip_stride bst=(_b)->stride * (_b)->block->rstride, rst = (_r)->stride * (_r)->block->rstride;\
vsip_scalar_d *bp=(_b)->block->array+(_b)->offset * (_b)->block->rstride, *rp=(_r)->block->array+(_r)->offset * (_r)->block->rstride;\
while(n-- > 0){ *rp = alpha * *bp; bp += bst; rp += rst;}}

#define mtrans_d(A, R) { vsip_length  lx = (A)->row_length, ly = (A)->col_length; vsip_index i, j; vsip_scalar_d tmp;\
vsip_scalar_d *a_p = (A)->block->array + (A)->offset * (A)->block->rstride, *r_p = R->block->array + R->offset * R->block->rstride;\
vsip_stride stAx = (A)->row_stride * (A)->block->rstride, stAy = (A)->col_stride * (A)->block->rstride,\
stRx = R->row_stride * R->block->rstride, stRy = R->col_stride * R->block->rstride;\
if((lx == ly) && (a_p == r_p)){ for(i=1; i<lx; i++){ for(j=0; j<i; j++){ tmp = *(a_p + j * stAy + i * stAx);\
*(a_p + j * stAy + i * stAx) = *(a_p + j * stAx + i * stAy); *(a_p + j * stAx + i * stAy) = tmp; } }\
} else { for(i=0; i<ly; i++){ r_p = R->block->array + R->offset * R->block->rstride + i * stRx;\
a_p = (A)->block->array + (A)->offset * (A)->block->rstride + i * stAy; for(j=0; j<lx; j++){ *r_p = *a_p;\
r_p += stRy; a_p += stAx; } } } }

typedef struct {vsip_index i; vsip_index j;} svdCorner;
typedef struct {vsip_scalar_d c; vsip_scalar_d s; vsip_scalar_d r;}givensObj_d ;

static svdObj_d *svdInit_d(vsip_length, vsip_length,int,int);
static void svdFinalize_d(svdObj_d*);
static void svd_d(svdObj_d*,int,int);

static csvdObj_d *csvdInit_d(vsip_length, vsip_length,int,int);
static void csvdFinalize_d(csvdObj_d*);
static void csvd_d(csvdObj_d*,int,int);
static vsip_scalar_d hypot_d(vsip_scalar_d a0,vsip_scalar_d b0){
    vsip_scalar_d a = (a0 < 0.0) ? -a0:a0;
    vsip_scalar_d b = (b0 < 0.0) ? -b0:b0;
    if (a == 0.0)
        return b;
    else if (b == 0.0)
        return a;
    else if (b < a)
        return a * (vsip_scalar_d)sqrt(1.0 + (b/a) * (b/a));
    else
        return b * (vsip_scalar_d)sqrt(1.0 + (a/b) * (a/b));
}

static vsip_vview_d *vsv_d(vsip_vview_d *v, vsip_vview_d *vs, vsip_index i)
{
    *vs=*v;
    vs->offset += i * vs->stride;
    vs->length -= i;
    return vs;
}
static vsip_mview_d* msv_d(vsip_mview_d *B,vsip_mview_d *BS, vsip_index i,vsip_index j)
{
    *BS = *B;
    BS->row_length -= j;
    BS->col_length -= i;
    BS->offset += j * BS->row_stride + i * BS->col_stride;
    return BS;
}
static vsip_mview_d* imsv_d( vsip_mview_d *B, vsip_mview_d *BS, vsip_index i1,vsip_index j1,
                            vsip_index i2, vsip_index j2)
{
    *BS=*B;
    if(j1 == 0) j1 =(B)->col_length;
    if(j2 == 0) j2 =(B)->row_length;
    BS->col_length = (j1 - i1);
    BS->row_length = (j2 - i2);
    BS->offset += i2 * B->row_stride + i1 * B->col_stride;
    return BS;
}
static vsip_vview_d *ivsv_d( vsip_vview_d *v, vsip_vview_d *vs, vsip_index i,vsip_index j)
{
    *vs=*v;
    if(j==0) j=v->length;
    vs->offset += i * v->stride;
    vs->length = j-i;
    return vs;
}
static vsip_vview_d *col_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index col)
{
    vv->block = Am->block;
    vv->offset = Am->offset + col * Am->row_stride;
    vv->stride = Am->col_stride;
    vv->length = Am->col_length;
    return vv;
}
static vsip_vview_d *row_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index row)
{
    vv->block = Am->block;
    vv->offset = Am->offset + row * Am->col_stride;
    vv->stride = Am->row_stride;
    vv->length = Am->row_length;
    return vv;
}
static vsip_vview_d *diag_sv_d(vsip_mview_d* Am,vsip_vview_d* a, vsip_stride i)
{
    a->block = Am->block;
    a->stride=Am->row_stride + Am->col_stride;
    if(i==0){
        a->length = Am->row_length;
        a->offset = Am->offset;
    } else if (i == 1){
        a->offset = Am->offset + Am->row_stride;
        a->length = Am->row_length - 1;
    } else {
        printf("Failed in diag_sv_d\n");
        exit(0);
    }
    return a;
}
static vsip_cmview_d* cimsv_d( vsip_cmview_d *B, vsip_cmview_d *BS, vsip_index i1,vsip_index j1,
                              vsip_index i2, vsip_index j2)
{
    *BS=*B;
    if(j1 == 0) j1 =B->col_length;
    if(j2 == 0) j2 =B->row_length;
    BS->col_length = (j1 - i1);
    BS->row_length = (j2 - i2);
    BS->offset += i2 * B->row_stride + i1 * B->col_stride;
    return BS;
}
static vsip_cvview_d *ccol_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index col)
{
    vv->block = Am->block;
    vv->offset = Am->offset + col * Am->row_stride;
    vv->stride = Am->col_stride;
    vv->length = Am->col_length;
    return vv;
}
static vsip_cvview_d *crow_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index row)
{
    vv->block=Am->block;
    vv->offset = Am->offset + row * Am->col_stride;
    vv->stride = Am->row_stride;
    vv->length = Am->row_length;
    return vv;
}
static vsip_cvview_d *cdiag_sv_d(vsip_cmview_d* Am,vsip_cvview_d* a, vsip_stride i)
{
    a->block = Am->block;
    a->stride=Am->row_stride + Am->col_stride;
    if(i==0){
        a->length = Am->row_length;
        a->offset = Am->offset;
    } else if (i == 1){
        a->offset = Am->offset + Am->row_stride;
        a->length = Am->row_length - 1;
    } else {
        printf("Failed in diag_sv_d\n");
        exit(0);
    }
    return a;
}
static vsip_scalar_d vnorm2_d(vsip_vview_d *a)
{
    vsip_length n = a->length;
    vsip_stride ast = a->stride * a->block->rstride;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,t = 0;
    while(n-- > 0){
        t  += (*ap * *ap);
        ap += ast;
    }
    return (vsip_scalar_d)sqrt(t);
}
static vsip_scalar_d mnormFro_d(vsip_mview_d *v)
{
    vsip_length m=v->col_length,n=v->row_length;
    vsip_index i,j;
    vsip_stride rstrd=v->row_stride*v->block->rstride;
    vsip_stride cstrd=v->col_stride*v->block->rstride;
    vsip_scalar_d *vre=v->block->array+v->offset*v->block->rstride;
    vsip_scalar_d re=0.0;
    for(i=0; i<m; i++){
        vsip_offset o=i*cstrd;
        vsip_scalar_d *rp=vre+o;
        for(j=0; j<n; j++){
            re += *rp * *rp;
            rp += rstrd;
        }
    }
    return sqrt(re);
}
static void meye_d(vsip_mview_d *v)
{
    vsip_length m=v->col_length,n=v->row_length;
    vsip_index i,j;
    vsip_stride rstrd=v->row_stride*v->block->rstride;
    vsip_stride cstrd=v->col_stride*v->block->rstride;
    vsip_scalar_d *vre=v->block->array+v->offset*v->block->rstride;
    for(i=0; i<m; i++){
        vsip_offset o=i*cstrd;
        vsip_scalar_d *rp=vre+o;
        for(j=0; j<n; j++){
            *rp = (i==j) ? 1.0:0.0;
            rp += rstrd;
        }
    }
}
/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_d sign_d(vsip_scalar_d a_in)
{
    return (a_in < 0.0) ? -1.0:1.0;
}
static vsip_cscalar_d csign_d(vsip_cscalar_d a_in)
{
    vsip_scalar_d re = a_in.r < 0.0 ? -a_in.r:a_in.r;
    vsip_scalar_d im = a_in.i < 0.0 ? -a_in.i:a_in.i;
    vsip_scalar_d t= (re==0.0) ? im: ((im==0.0) ? re:((re<im) ? im*sqrt(1.0 + re/im*re/im):re*sqrt(1.0+im/re*im/re)));
    vsip_cscalar_d retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0) {
        retval.r = (a_in.r < 0.0) ? -1.0:1.0;
        return retval;
    } else {
        retval.r = a_in.r/t;
        retval.i = a_in.i/t;
        return retval;
    }
}
static void phaseCheck_d(svdObj_d *svd)
{
    vsip_scalar_d *fptr, *dptr;
    vsip_mview_d *L = svd->L;
    vsip_vview_d *d = svd->d;
    vsip_vview_d *f = svd->f;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_vview_d *l = &svd->ls_one;
    vsip_stride fstrd=f->stride * d->block->rstride;
    vsip_stride dstrd=d->stride * d->block->rstride;
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nd; i++){
        ps=*dptr;
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            col_sv_d(L,l,i);
            {
                vsip_scalar_d *p = l->block->array + l->offset * l->block->rstride;
                vsip_stride std = l->stride * l->block->rstride;
                vsip_length n = l->length * std;
                vsip_index k;
                for(k=0; k<n; k+=std) p[k] *= ps;
            }
            *dptr=m;
            if (i < nf)
                *fptr *= ps;
        } else {
            *dptr = 0.0;
        }
        dptr+=dstrd;fptr+=fstrd;
    }
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fabs(*fptr);
        m = (*dptr + *(dptr+dstrd)) * eps0;
        if (f_i < m) *fptr = 0.0;
        dptr+=dstrd;fptr+=fstrd;
    }
}
static void phaseCheck2_d(svdObj_d *svd) /* save U */
{
    vsip_scalar_d *fptr, *dptr;
    vsip_mview_d *L = svd->L;
    vsip_vview_d *d = svd->d;
    vsip_vview_d *f = svd->f;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_vview_d *l = &svd->ls_one;
    vsip_stride fstrd=f->stride * d->block->rstride;
    vsip_stride dstrd=d->stride * d->block->rstride;
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nd; i++){
        ps=*dptr;
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            col_sv_d(L,l,i);
            {
                vsip_scalar_d *p = l->block->array + l->offset * l->block->rstride;
                vsip_stride std = l->stride * l->block->rstride;
                vsip_length n = l->length * std;
                vsip_index k;
                for(k=0; k<n; k+=std) p[k] *= ps;
            }
            *dptr=m;
            if (i < nf)
                *fptr *= ps;
        } else {
            *dptr = 0.0;
        }
        dptr+=dstrd;fptr+=fstrd;
    }
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fabs(*fptr);
        m = (*dptr + *(dptr+dstrd)) * eps0;
        if (f_i < m) *fptr = 0.0;
        dptr+=dstrd;fptr+=fstrd;
    }
    
}
static void phaseCheck1_d(svdObj_d *svd) /* save V */
{
    vsip_scalar_d *fptr, *dptr;
    vsip_vview_d *d = svd->d;
    vsip_vview_d *f = svd->f;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_stride fstrd=f->stride * d->block->rstride;
    vsip_stride dstrd=d->stride * d->block->rstride;
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nd; i++){
        ps=*dptr;
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            *dptr=m;
            if (i < nf)
                *fptr *= ps;
        } else {
            *dptr = 0.0;
        }
        dptr+=dstrd;fptr+=fstrd;
    }
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fabs(*fptr);
        m = (*dptr + *(dptr+dstrd)) * eps0;
        if (f_i < m) *fptr = 0.0;
        dptr+=dstrd;fptr+=fstrd;
    }
    
}
static void phaseCheck0_d(svdObj_d *svd)
{
    vsip_scalar_d *fptr, *dptr;
    vsip_vview_d *d = svd->d;
    vsip_vview_d *f = svd->f;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_stride fstrd=f->stride * d->block->rstride;
    vsip_stride dstrd=d->stride * d->block->rstride;
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nd; i++){
        ps=*dptr;
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            *dptr=m;
            if (i < nf)
                *fptr *= ps;
        } else {
            *dptr = 0.0;
        }
        dptr+=dstrd;fptr+=fstrd;
    }
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fabs(*fptr);
        m = (*dptr + *(dptr+dstrd)) * eps0;
        if (f_i < m) *fptr = 0.0;
        dptr+=dstrd;fptr+=fstrd;
    }
    
}
static void biDiagPhaseToZero_d( svdObj_d *svd)
{
    vsip_vview_d *x=&svd->bs,*v=svd->d;
    diag_sv_d(&svd->B,x,0);
    vcopy_d(x,v);
    
    diag_sv_d(&svd->B,x,1); v=svd->f;
    vcopy_d(x,v);
    
    phaseCheck_d(svd);
}
static void biDiagPhaseToZero2_d( svdObj_d *svd)
{
    vsip_vview_d *x=&svd->bs,*v=svd->d;
    diag_sv_d(&svd->B,x,0);
    vcopy_d(x,v);
    
    diag_sv_d(&svd->B,x,1); v=svd->f;
    vcopy_d(x,v);
    
    phaseCheck2_d(svd);
}
static void biDiagPhaseToZero1_d( svdObj_d *svd)
{
    vsip_vview_d *x=&svd->bs,*v=svd->d;
    diag_sv_d(&svd->B,x,0);
    vcopy_d(x,v);
    
    diag_sv_d(&svd->B,x,1); v=svd->f;
    vcopy_d(x,v);
    
    phaseCheck1_d(svd);
}
static void biDiagPhaseToZero0_d( svdObj_d *svd)
{
    vsip_vview_d *x=&svd->bs,*v=svd->d;
    diag_sv_d(&svd->B,x,0);
    vcopy_d(x,v);
    
    diag_sv_d(&svd->B,x,1); v=svd->f;
    vcopy_d(x,v);
    
    phaseCheck0_d(svd);
}
#define opu_d(A,x,y) {\
vsip_length m = (A)->col_length,n = (A)->row_length;vsip_index i,ii,j,jj;\
vsip_scalar_d *ap=(A)->block->array + (A)->offset * (A)->block->rstride, \
*xp=x->block->array + x->offset * x->block->rstride,*yp=y->block->array + y->offset * y->block->rstride;\
vsip_stride xstd = x->block->rstride * x->stride,ystd = y->block->rstride * y->stride,\
r_std = (A)->block->rstride * (A)->row_stride,c_std = (A)->block->rstride * (A)->col_stride;\
m *= c_std; n *= r_std;\
for(i=0, ii=0; i<m; i+=c_std, ii+=xstd){vsip_scalar_d c = xp[ii], *app=ap+i;\
for(j=0, jj=0; j<n; j+=r_std, jj+=ystd){ app[j] = app[j] + c * yp[jj];}}}
static void houseProd_d(vsip_vview_d *v, vsip_mview_d *A,vsip_vview_d *w)
{
    vsip_scalar_d *vptr = v->block->array + v->offset*v->block->rstride;
    vsip_stride vstd = v->stride*v->block->rstride;
    vsip_scalar_d beta = 0.0;
    vsip_length n=v->length;
    while(n-- > 0){ beta += *vptr * *vptr;vptr+=vstd;}
    beta=2.0/beta;
    w->length = A->row_length;
    vmprod_d(v,A,w)
    svmul_d(-beta,w,w)
    opu_d(A,v,w)
}
static void prodHouse_d(vsip_mview_d *A, vsip_vview_d *v, vsip_vview_d *w)
{
    vsip_scalar_d *vptr = v->block->array + v->offset*v->block->rstride;
    vsip_stride vstd = v->stride*v->block->rstride;
    vsip_scalar_d beta = 0.0;
    vsip_length n=v->length;
    while(n-- > 0){ beta += *vptr * *vptr;vptr+=vstd;}
    beta=2.0/beta;
    w->length = A->col_length;
    mvprod_d(A,v,w)
    svmul_d(-beta,w,w)
    opu_d(A,w,v)
}
static vsip_vview_d *houseVector_d(vsip_vview_d* x)
{
    vsip_scalar_d *x0=x->block->array + x->offset * x->block->rstride;
    vsip_scalar_d nrm=vnorm2_d(x);
    vsip_scalar_d t = *x0;
    vsip_scalar_d s = t +  sign_d(t) * nrm;
    *x0=s;
    nrm = vnorm2_d(x);
    if (nrm == 0.0)
        *x0=1.0;
    else {
        vsip_stride std = x->stride * x->block->rstride;
        vsip_length n = x->length * std;
        vsip_index k;
        for(k=0; k<n; k+=std) x0[k] /= nrm;
    }
    return x;
}
static void VHmatExtract_d(svdObj_d *svd)
{
    vsip_mview_d* B = &svd->B;
    vsip_index i,j;
    vsip_length n = B->row_length;
    vsip_mview_d *Bs=&svd->Bs;
    vsip_mview_d *V=svd->R;
    vsip_mview_d *Vs=&svd->Rs;
    vsip_vview_d *v=&svd->bs;
    vsip_scalar_d t;
    vsip_scalar_d *vptr;
    if(n < 3)
        return;
    for(i=n-3; i>0; i--){
        j=i+1;
        row_sv_d(msv_d(B,Bs,i,j),v,0);
        vptr=v->block->array+v->offset*v->block->rstride;
        t=*vptr; *vptr = 1.0;
        prodHouse_d(msv_d(V,Vs,j,j),v,svd->w);
        *vptr = t;
    }
    row_sv_d(msv_d(B,Bs,0,1),v,0);
    vptr=v->block->array+v->offset*v->block->rstride;
    t=*vptr; *vptr = 1.0;
    prodHouse_d(msv_d(V,Vs,1,1),v,svd->w);
    *vptr = t;
}
static void UmatExtract_d(svdObj_d *svd)
{
    vsip_mview_d* B=&svd->B;
    vsip_mview_d *U=svd->L;
    vsip_index i;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_mview_d *Bs=&svd->Bs;
    vsip_mview_d *Us=&svd->Ls;
    vsip_vview_d *v=&svd->bs;
    vsip_scalar_d t;
    vsip_scalar_d *vptr;
    if (m > n){
        i=n-1;
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        vptr=v->block->array+v->offset*v->block->rstride;
        t=*vptr; *vptr = 1.0;
        houseProd_d(v,msv_d(U,Us,i,i),svd->w);
        *vptr = t;
    }
    for(i=n-2; i>0; i--){
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        vptr=v->block->array+v->offset*v->block->rstride;
        t=*vptr; *vptr = 1.0;
        houseProd_d(v,msv_d(U,Us,i,i),svd->w);
        *vptr = t;
    }
    col_sv_d(msv_d(B,Bs,0,0),v,0);
    vptr=v->block->array+v->offset*v->block->rstride;
    t=*vptr; *vptr = 1.0;
    houseProd_d(v,msv_d(U,Us,0,0),svd->w);
    *vptr= t;
}
static void bidiag_d(svdObj_d *svd)
{
    vsip_mview_d *B = &svd->B;
    vsip_mview_d *Bs = &svd->Bs;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_vview_d *x=col_sv_d(B,&svd->bs,0);
    vsip_vview_d *v=svd->t;
    vsip_vview_d *vs = &svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        v->length=m-i;
        col_sv_d(msv_d(B,Bs,i,i),x,0);
        vcopy_d(x,v);/*0*/
        houseVector_d(v);
        scaleV(v)
        houseProd_d(v,Bs,svd->w);
        vsv_d(v,vs,1);vsv_d(x,x,1);
        vcopy_d(vs,x);/*1*/
        if(i < n-2){
            j = i+1;
            v->length = n-j;
            row_sv_d(msv_d(B,Bs,i,j),x,0);
            vcopy_d(x,v);/*2*/
            houseVector_d(v);
            scaleV(v)
            prodHouse_d(Bs,v,svd->w);
            vsv_d(v,vs,1);vsv_d(x,x,1);
            vcopy_d(vs,x);/*3*/
        }
    }
    if(m > n){
        i=n-1;
        v->length=m-i;
        col_sv_d(msv_d(B,Bs,i,i),x,0);
        vcopy_d(x,v); /*4*/
        houseVector_d(v);
        scaleV(v)
        houseProd_d(v,Bs,svd->w);
        vsv_d(v,vs,1);vsv_d(x,x,1);
        vcopy_d(vs,x);/*5*/
    }
}
static void gtProd_d(vsip_index i, vsip_index j, vsip_scalar_d c,vsip_scalar_d s, svdObj_d* svd)
{
    vsip_mview_d* R = &svd->Rs;
    vsip_vview_d *a1= row_sv_d(R,&svd->rs_one, i);
    vsip_vview_d *a2= row_sv_d(R,&svd->rs_two, j);
    vsip_index k;
    vsip_scalar_d *t1 = a1->block->array + (a1->offset) * a1->block->rstride;
    vsip_scalar_d *t2 = a2->block->array + (a2->offset) * a2->block->rstride;
    vsip_stride std = a1->stride * a1->block->rstride;
    vsip_length n = a1->length * std;
    for(k=0; k<n; k+=std){
        register vsip_scalar_d b1 = t1[k];
        register vsip_scalar_d b2 = t2[k];
        t1[k] = c * b1 + s * b2;
        t2[k] = c * b2 - s * b1;
    }
}
static void prodG_d(svdObj_d* svd,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_mview_d* L = &svd->Ls;
    vsip_vview_d *a1= col_sv_d(L,&svd->ls_one,i);
    vsip_vview_d *a2= col_sv_d(L,&svd->ls_two,j);
    vsip_index k;
    vsip_scalar_d *t1 = a1->block->array + (a1->offset) * a1->block->rstride;
    vsip_scalar_d *t2 = a2->block->array + (a2->offset) * a2->block->rstride;
    vsip_stride std = a1->stride * a1->block->rstride;
    vsip_length n = a1->length * std;
    for(k=0; k<n; k+=std){
        register vsip_scalar_d b1 = t1[k];
        register vsip_scalar_d b2 = t2[k];
        t1[k] = c * b1 + s * b2;
        t2[k] = c * b2 - s * b1;
    }
}
static givensObj_d givensCoef_d(vsip_scalar_d x1, vsip_scalar_d x2)
{
    givensObj_d retval;
    vsip_scalar_d t = hypot_d(x1,x2);
    if (x2 == 0.0 ){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0  || t == 0.0) {
        retval.c=0.0;retval.s=sign_d(x2);retval.r=t;
    }else{
        vsip_scalar_d sn = sign_d(x1);
        retval.c=((x1 < 0.0) ? -x1:x1)/t;retval.s=sn*x2/t; retval.r=sn*t;
    }
    return retval;
}
static void zeroCol_d(svdObj_d *svd)
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
        gtProd_d(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        gtProd_d(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        gtProd_d(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        gtProd_d(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
            gtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        gtProd_d(0,k+1,g.c,g.s,svd);
    }
}
static void zeroRow_d(svdObj_d *svd)
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d *dptr=d->block->array+d->offset*d->block->rstride;
    vsip_scalar_d *fptr=f->block->array + f->offset*d->block->rstride;
    vsip_stride dstd=d->stride*d->block->rstride;
    vsip_stride fstd=f->stride*f->block->rstride;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
        prodG_d(svd,n,0,g.c,g.s);
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstd)=xf;
        prodG_d(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=*(dptr+dstd*i);
            g=givensCoef_d(xd,t);
            prodG_d(svd,i+1,0,g.c,g.s);
            *(dptr+dstd*i)=g.r;
            xf=*(fptr+fstd*(i+1));
            t=-xf * g.s; xf *= g.c;
            *(fptr+fstd*(i+1))=xf;
        }
        xd=*(dptr+dstd*(n-1));
        g=givensCoef_d(xd,t);
        *(dptr+dstd*(n-1))=g.r;
        prodG_d(svd,n,0,g.c,g.s);
    }
}
static void zeroCol2_d(svdObj_d *svd) /* save U */
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
    }else{
        i=n-1; j=i-1; k=i;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
            gtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
    }
}
static void zeroRow2_d(svdObj_d *svd) /* save U */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d *dptr=d->block->array+d->offset*d->block->rstride;
    vsip_scalar_d *fptr=f->block->array + f->offset*d->block->rstride;
    vsip_stride dstd=d->stride*d->block->rstride;
    vsip_stride fstd=f->stride*f->block->rstride;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
        prodG_d(svd,n,0,g.c,g.s);
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstd)=xf;
        prodG_d(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=*(dptr+dstd*i);
            g=givensCoef_d(xd,t);
            prodG_d(svd,i+1,0,g.c,g.s);
            *(dptr+dstd*i)=g.r;
            xf=*(fptr+fstd*(i+1));
            t=-xf * g.s; xf *= g.c;
            *(fptr+fstd*(i+1))=xf;
        }
        xd=*(dptr+dstd*(n-1));
        g=givensCoef_d(xd,t);
        *(dptr+dstd*(n-1))=g.r;
        prodG_d(svd,n,0,g.c,g.s);
    }
}
static void zeroCol1_d(svdObj_d *svd) /* save V */
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
        gtProd_d(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        gtProd_d(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        gtProd_d(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        gtProd_d(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
            gtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        gtProd_d(0,k+1,g.c,g.s,svd);
    }
}
static void zeroRow1_d(svdObj_d *svd) /* save V */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d *dptr=d->block->array+d->offset*d->block->rstride;
    vsip_scalar_d *fptr=f->block->array + f->offset*d->block->rstride;
    vsip_stride dstd=d->stride*d->block->rstride;
    vsip_stride fstd=f->stride*f->block->rstride;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstd)=xf;
        for(i=1; i<n-1; i++){
            xd=*(dptr+dstd*i);
            g=givensCoef_d(xd,t);
            *(dptr+dstd*i)=g.r;
            xf=*(fptr+fstd*(i+1));
            t=-xf * g.s; xf *= g.c;
            *(fptr+fstd*(i+1))=xf;
        }
        xd=*(dptr+dstd*(n-1));
        g=givensCoef_d(xd,t);
        *(dptr+dstd*(n-1))=g.r;
    }
}
static void zeroCol0_d(svdObj_d *svd)
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
    }else{
        i=n-1; j=i-1;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
    }
}
static void zeroRow0_d(svdObj_d *svd)
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d *dptr=d->block->array+d->offset*d->block->rstride;
    vsip_scalar_d *fptr=f->block->array + f->offset*d->block->rstride;
    vsip_stride dstd=d->stride*d->block->rstride;
    vsip_stride fstd=f->stride*f->block->rstride;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstd)=xf;
        for(i=1; i<n-1; i++){
            xd=*(dptr+dstd*i);
            g=givensCoef_d(xd,t);
            *(dptr+dstd*i)=g.r;
            xf=*(fptr+fstd*(i+1));
            t=-xf * g.s; xf *= g.c;
            *(fptr+fstd*(i+1))=xf;
        }
        xd=*(dptr+dstd*(n-1));
        g=givensCoef_d(xd,t);
        *(dptr+dstd*(n-1))=g.r;
    }
}
static vsip_scalar_d svdMu_d(vsip_scalar_d d2,vsip_scalar_d f1,vsip_scalar_d d3,vsip_scalar_d* f2, vsip_scalar_d eps0)
{
    vsip_scalar_d mu;
    vsip_scalar_d cu=d2 * d2 + f1 * f1;
    vsip_scalar_d cl=d3 * d3 + *f2 * *f2;
    vsip_scalar_d cd = d2 * *f2;
    vsip_scalar_d T = (cu + cl);
    vsip_scalar_d D = (cu * cl - cd * cd)/(T*T);
    vsip_scalar_d root = T * (vsip_scalar_d) sqrt(1.0 - ((4 * D)>1.0 ? 1.0:4*D));
    vsip_scalar_d lambda1 = (T + root)/(2.);
    vsip_scalar_d lambda2 = (T - root)/(2.);
    vsip_scalar_d c1=lambda1-cl,c2=lambda2-cl;
    c1=(c1<0) ? -c1:c1;  c2=(c2<0) ? -c2:c2;
    if(root == 0.0)
        if(fabs(*f2) < (d2 + d3) * eps0) *f2=0.0;
    if(c1 < c2)
        mu = lambda1;
    else
        mu = lambda2;
    return mu;
}
static vsip_index zeroFind_d(vsip_vview_d* d, vsip_scalar_d eps0)
{
    vsip_scalar_d *dptr=d->block->array + d->offset*d->block->rstride;
    vsip_stride dstrd=d->stride*d->block->rstride;
    vsip_index j = d->length;
    vsip_scalar_d xd=*(dptr+(j-1)*dstrd);
    while(xd > eps0){
        if (j > 1){
            j -= 1;
            xd=*(dptr+(j-1)*dstrd);
        }else if(j==1)
            return 0;
    }
    *(dptr+(j-1)*dstrd)=0.0;
    return j;
}
static svdCorner svdCorners_d(vsip_vview_d* f)
{
    svdCorner crnr;
    vsip_scalar_d *fptr=f->block->array + f->offset*f->block->rstride;
    vsip_stride fstrd=f->stride*f->block->rstride;
    vsip_index j=f->length-1;
    vsip_index i;
    while((j > 0) && *(fptr+j*fstrd) == 0.0)
        j-=1;
    if(j == 0 && *fptr == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        while((i > 0) && *(fptr+i*fstrd) != 0.0)
            i -= 1;
        if(i==0 && *fptr == 0.0){
            crnr.i = 1;
            crnr.j = j+2;
        } else if(i == 0 && *fptr != 0.0){
            crnr.i = 0;
            crnr.j= j+2;
            
        }else{
            crnr.i = i+1;
            crnr.j = j+2;
        }
    } /* index and length of f != 0 */
    return crnr;
}
static void svdStep_d(svdObj_d *svd)
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d)\n");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c*x2-g.s*x1;
    *dptr=g.c*x1+g.s*x2;
    t=*(dptr+dstd);
    *(dptr+dstd) *= g.c;
    t*=g.s;
    gtProd_d(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(*(dptr+i*dstd),t);
        *(dptr+i*dstd)=g.r;
        x1=*(dptr+j*dstd)*g.c;
        x2=*(fptr+i*fstd)*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
        *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd)=x1*g.c;
        prodG_d(svd,i, j, g.c, g.s);
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2; *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1; *(dptr+k*dstd)=x1*g.c;
        gtProd_d(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(d->block->array+(i*d->stride+d->offset)*d->block->rstride) = g.r;
    x1=*(dptr+j*dstd)*g.c; x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
    *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
    prodG_d(svd,i, j, g.c, g.s);
}
static void svdStep2_d(svdObj_d *svd) /* save U */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d)\n");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c*x2-g.s*x1;
    *dptr=g.c*x1+g.s*x2;
    t=*(dptr+dstd);
    *(dptr+dstd) *= g.c;
    t*=g.s;
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(*(dptr+i*dstd),t);
        *(dptr+i*dstd)=g.r;
        x1=*(dptr+j*dstd)*g.c;
        x2=*(fptr+i*fstd)*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
        *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd)=x1*g.c;
        prodG_d(svd,i, j, g.c, g.s);
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2; *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1; *(dptr+k*dstd)=x1*g.c;
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(d->block->array+(i*d->stride+d->offset)*d->block->rstride) = g.r;
    x1=*(dptr+j*dstd)*g.c; x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
    *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
    prodG_d(svd,i, j, g.c, g.s);
}
static void svdStep1_d(svdObj_d *svd) /* save V */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d)\n");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c*x2-g.s*x1;
    *dptr=g.c*x1+g.s*x2;
    t=*(dptr+dstd);
    *(dptr+dstd) *= g.c;
    t*=g.s;
    gtProd_d(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(*(dptr+i*dstd),t);
        *(dptr+i*dstd)=g.r;
        x1=*(dptr+j*dstd)*g.c;
        x2=*(fptr+i*fstd)*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
        *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd)=x1*g.c;
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2; *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1; *(dptr+k*dstd)=x1*g.c;
        gtProd_d(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(d->block->array+(i*d->stride+d->offset)*d->block->rstride) = g.r;
    x1=*(dptr+j*dstd)*g.c; x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
    *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
}
static void svdStep0_d(svdObj_d *svd)
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d)\n");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c*x2-g.s*x1;
    *dptr=g.c*x1+g.s*x2;
    t=*(dptr+dstd);
    *(dptr+dstd) *= g.c;
    t*=g.s;
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(*(dptr+i*dstd),t);
        *(dptr+i*dstd)=g.r;
        x1=*(dptr+j*dstd)*g.c;
        x2=*(fptr+i*fstd)*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
        *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd)=x1*g.c;
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2; *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1; *(dptr+k*dstd)=x1*g.c;
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(d->block->array+(i*d->stride+d->offset)*d->block->rstride) = g.r;
    x1=*(dptr+j*dstd)*g.c; x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
    *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
}
static vsip_cvview_d *cvsv_d(vsip_cvview_d *v,vsip_cvview_d *vs,vsip_index i)
{
    *vs=*v;
    vs->offset += i * vs->stride;
    vs->length -= i;
    return vs;
}
static vsip_cmview_d* cmsv_d(vsip_cmview_d *B, vsip_cmview_d *BS, vsip_index i,vsip_index j)
{
    *BS=*B;
    BS->row_length -= j;
    BS->col_length -= i;
    BS->offset += j * BS->row_stride + i * BS->col_stride;
    return BS;
}
static vsip_vview_d *vreal_sv_d(vsip_cvview_d *cv,vsip_vview_d*v)
{
    v->block=cv->block->R;
    v->offset = cv->offset; v->length=cv->length;v->stride= cv->stride;
    v->markings = VSIP_VALID_STRUCTURE_OBJECT;
    return v;
}
static vsip_scalar_d cvnorm2_d(vsip_cvview_d *a)
{
    vsip_length n = a->length;
    vsip_stride cast = a->block->cstride;
    vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset);
    vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset);
    vsip_stride ast = (cast * a->stride);
    vsip_scalar_d t1=0,t2=0;
    while(n-- > 0){
        t1 += *apr * *apr;
        t2 += *api * *api;
        apr += ast; api += ast;
    }
    return (vsip_scalar_d)sqrt(t1+t2);
}
static vsip_scalar_d cmnormFro_d(vsip_cmview_d *v)
{
    vsip_length m=v->col_length,n=v->row_length;
    vsip_index i,j;
    vsip_stride rstrd=v->row_stride*v->block->R->rstride;
    vsip_stride cstrd=v->col_stride*v->block->R->rstride;
    vsip_scalar_d *vre=v->block->R->array+v->offset*v->block->R->rstride;
    vsip_scalar_d *vim=v->block->I->array+v->offset*v->block->I->rstride;
    vsip_scalar_d re=0.0;
    vsip_scalar_d im=0.0;
    for(i=0; i<m; i++){
        vsip_offset o=i*cstrd;
        vsip_scalar_d *rp=vre+o;
        vsip_scalar_d *ip=vim+o;
        for(j=0; j<n; j++){
            re += *rp * *rp;
            im += *ip * *ip;
            rp += rstrd; ip += rstrd;
        }
    }
    return (vsip_scalar_d)sqrt(re+im);
}
static void cmeye_d(vsip_cmview_d *v)
{
    vsip_length m=v->col_length,n=v->row_length;
    vsip_index i,j;
    vsip_stride rstrd=v->row_stride*v->block->R->rstride;
    vsip_stride cstrd=v->col_stride*v->block->R->rstride;
    vsip_scalar_d *vre=v->block->R->array+v->offset*v->block->R->rstride;
    vsip_scalar_d *vim=v->block->I->array+v->offset*v->block->I->rstride;
    for(i=0; i<m; i++){
        vsip_offset o=i*cstrd;
        vsip_scalar_d *rp=vre+o;
        vsip_scalar_d *ip=vim+o;
        for(j=0; j<n; j++){
            *rp = (i==j) ? 1.0:0.0;
            *ip = 0.0;
            rp += rstrd; ip += rstrd;
        }
    }
}
static void cbiDiagPhaseToZero_d( csvdObj_d *svd)
{
    vsip_cmview_d *L = svd->L;
    vsip_cvview_d *d = cdiag_sv_d(&svd->B,&svd->bs,0);
    vsip_cvview_d *f = cdiag_sv_d(&svd->B,&svd->bfs,1);
    vsip_cmview_d *R = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i,j;
    vsip_cscalar_d ps;
    vsip_scalar_d m;
    vsip_cvview_d *l = &svd->ls_one;
    vsip_cvview_d *r = &svd->rs_one;
    vsip_scalar_d *dptr_r=d->block->R->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *dptr_i=d->block->I->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *fptr_r=f->block->R->array+f->block->R->rstride*f->offset;
    vsip_scalar_d *fptr_i=f->block->I->array+f->block->R->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->R->rstride;
    vsip_stride fstrd=f->stride*f->block->R->rstride;
    vsip_scalar_d re,im;
    for(i=0; i<nd; i++){
        ps.r=*(dptr_r+i*dstrd);
        ps.i=*(dptr_i+i*dstrd);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r=-1.0;
            else
                ps.r=1.0;
            m = (m<0) ? -m:m;
        } else {
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_d(L,l,i);csvmul_d(ps,l);
            *(d->block->R->array+(d->offset+i*d->stride)*d->block->cstride)=m;
            *(d->block->I->array+(d->offset+i*d->stride)*d->block->cstride)=0.0;
            if (i < nf){
                vsip_scalar_d *fr=fptr_r+i*fstrd;
                vsip_scalar_d *fi=fptr_i+i*fstrd;
                re=*fr; im=*fi;
                *fr=re*ps.r+im*ps.i;
                *fi=-ps.i*re+ps.r*im;
            }
        }else{
            *(dptr_r+i*dstrd)=0.0;
            *(dptr_i+i*dstrd)=0.0;
        }
    }
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps.r=*(fptr_r+i*fstrd);
        ps.i=*(fptr_i+i*fstrd);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r =-1.0;
            else
                ps.r = 1.0;
            m = (m < 0.0) ? -m:m;
        }else{
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_d(L, l, j);
        ps.i=-ps.i;csvmul_d(ps,l);ps.i=-ps.i;
        crow_sv_d(R,r,j);
        csvmul_d(ps,r);
        *(fptr_r+i*fstrd)=m;
        *(fptr_i+i*fstrd)=0.0;
        re=*(fptr_r+ j * fstrd);
        im=*(fptr_i+ j * fstrd);
        *(fptr_r+ j * fstrd)=re*ps.r-im*ps.i;
        *(fptr_i+ j * fstrd)=re*ps.i+im*ps.r;
    }
    j=nf;
    i=j-1;
    ps.r=*(fptr_r+i*fstrd);
    ps.i=*(fptr_i+i*fstrd);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps.r =-1.0;
        else
            ps.r = 1.0;
        m = (m<0) ? -m:m;
    }else{
        re=fabs(ps.r); im=fabs(ps.i);
        m = CMAG_F(re,im);
        ps.r /= m; ps.i/=m;
    }
    *(fptr_r+i*fstrd)=m;
    *(fptr_i+i*fstrd)=0.0;
    ccol_sv_d(L, l, j);
    ps.i=-ps.i;csvmul_d(ps,l);ps.i=-ps.i;
    crow_sv_d(R,r,j);
    csvmul_d(ps,r);
}
static void cbiDiagPhaseToZero2_d( csvdObj_d *svd) /* save U only */
{
    vsip_cmview_d *L = svd->L;
    vsip_cvview_d *d = cdiag_sv_d(&svd->B,&svd->bs,0);
    vsip_cvview_d *f = cdiag_sv_d(&svd->B,&svd->bfs,1);
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i,j;
    vsip_cscalar_d ps;
    vsip_scalar_d m;
    vsip_cvview_d *l = &svd->ls_one;
    vsip_scalar_d *dptr_r=d->block->R->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *dptr_i=d->block->I->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *fptr_r=f->block->R->array+f->block->R->rstride*f->offset;
    vsip_scalar_d *fptr_i=f->block->I->array+f->block->R->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->R->rstride;
    vsip_stride fstrd=f->stride*f->block->R->rstride;
    vsip_scalar_d re,im;
    for(i=0; i<nd; i++){
        ps.r=*(dptr_r+i*dstrd);
        ps.i=*(dptr_i+i*dstrd);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r=-1.0;
            else
                ps.r=1.0;
            m = (m<0) ? -m:m;
        } else {
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_d(L,l,i);csvmul_d(ps,l);
            *(d->block->R->array+(d->offset+i*d->stride)*d->block->cstride)=m;
            *(d->block->I->array+(d->offset+i*d->stride)*d->block->cstride)=0.0;
            if (i < nf){
                vsip_scalar_d *fr=fptr_r+i*fstrd;
                vsip_scalar_d *fi=fptr_i+i*fstrd;
                re=*fr; im=*fi;
                *fr=re*ps.r+im*ps.i;
                *fi=-ps.i*re+ps.r*im;
            }
        }else{
            *(dptr_r+i*dstrd)=0.0;
            *(dptr_i+i*dstrd)=0.0;
        }
    }
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps.r=*(fptr_r+i*fstrd);
        ps.i=*(fptr_i+i*fstrd);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r =-1.0;
            else
                ps.r = 1.0;
            m = (m < 0.0) ? -m:m;
        }else{
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_d(L, l, j);
        ps.i=-ps.i;csvmul_d(ps,l);ps.i=-ps.i;
        *(fptr_r+i*fstrd)=m;
        *(fptr_i+i*fstrd)=0.0;
        re=*(fptr_r+ j * fstrd);
        im=*(fptr_i+ j * fstrd);
        *(fptr_r+ j * fstrd)=re*ps.r-im*ps.i;
        *(fptr_i+ j * fstrd)=re*ps.i+im*ps.r;
    }
    j=nf;
    i=j-1;
    ps.r=*(fptr_r+i*fstrd);
    ps.i=*(fptr_i+i*fstrd);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps.r =-1.0;
        else
            ps.r = 1.0;
        m = (m<0) ? -m:m;
    }else{
        re=fabs(ps.r); im=fabs(ps.i);
        m = CMAG_F(re,im);
        ps.r /= m; ps.i/=m;
    }
    *(fptr_r+i*fstrd)=m;
    *(fptr_i+i*fstrd)=0.0;
    ccol_sv_d(L, l, j);
    ps.i=-ps.i;csvmul_d(ps,l);ps.i=-ps.i;
}
static void cbiDiagPhaseToZero1_d( csvdObj_d *svd) /* save V only */
{
    vsip_cvview_d *d = cdiag_sv_d(&svd->B,&svd->bs,0);
    vsip_cvview_d *f = cdiag_sv_d(&svd->B,&svd->bfs,1);
    vsip_cmview_d *R = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i,j;
    vsip_cscalar_d ps;
    vsip_scalar_d m;
    vsip_cvview_d *r = &svd->rs_one;
    vsip_scalar_d *dptr_r=d->block->R->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *dptr_i=d->block->I->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *fptr_r=f->block->R->array+f->block->R->rstride*f->offset;
    vsip_scalar_d *fptr_i=f->block->I->array+f->block->R->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->R->rstride;
    vsip_stride fstrd=f->stride*f->block->R->rstride;
    vsip_scalar_d re,im;
    for(i=0; i<nd; i++){
        ps.r=*(dptr_r+i*dstrd);
        ps.i=*(dptr_i+i*dstrd);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r=-1.0;
            else
                ps.r=1.0;
            m = (m<0) ? -m:m;
        } else {
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            *(d->block->R->array+(d->offset+i*d->stride)*d->block->cstride)=m;
            *(d->block->I->array+(d->offset+i*d->stride)*d->block->cstride)=0.0;
            if (i < nf){
                vsip_scalar_d *fr=fptr_r+i*fstrd;
                vsip_scalar_d *fi=fptr_i+i*fstrd;
                re=*fr; im=*fi;
                *fr=re*ps.r+im*ps.i;
                *fi=-ps.i*re+ps.r*im;
            }
        }else{
            *(dptr_r+i*dstrd)=0.0;
            *(dptr_i+i*dstrd)=0.0;
        }
    }
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps.r=*(fptr_r+i*fstrd);
        ps.i=*(fptr_i+i*fstrd);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r =-1.0;
            else
                ps.r = 1.0;
            m = (m < 0.0) ? -m:m;
        }else{
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        crow_sv_d(R,r,j);
        csvmul_d(ps,r);
        *(fptr_r+i*fstrd)=m;
        *(fptr_i+i*fstrd)=0.0;
        re=*(fptr_r+ j * fstrd);
        im=*(fptr_i+ j * fstrd);
        *(fptr_r+ j * fstrd)=re*ps.r-im*ps.i;
        *(fptr_i+ j * fstrd)=re*ps.i+im*ps.r;
    }
    j=nf;
    i=j-1;
    ps.r=*(fptr_r+i*fstrd);
    ps.i=*(fptr_i+i*fstrd);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps.r =-1.0;
        else
            ps.r = 1.0;
        m = (m<0) ? -m:m;
    }else{
        re=fabs(ps.r); im=fabs(ps.i);
        m = CMAG_F(re,im);
        ps.r /= m; ps.i/=m;
    }
    *(fptr_r+i*fstrd)=m;
    *(fptr_i+i*fstrd)=0.0;
    crow_sv_d(R,r,j);
    csvmul_d(ps,r);
}
static void cbiDiagPhaseToZero0_d( csvdObj_d *svd)
{
    vsip_cvview_d *d = cdiag_sv_d(&svd->B,&svd->bs,0);
    vsip_cvview_d *f = cdiag_sv_d(&svd->B,&svd->bfs,1);
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nd=d->length;
    vsip_length nf=f->length;
    vsip_index i,j;
    vsip_cscalar_d ps;
    vsip_scalar_d m;
    vsip_scalar_d *dptr_r=d->block->R->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *dptr_i=d->block->I->array+d->block->R->rstride*d->offset;
    vsip_scalar_d *fptr_r=f->block->R->array+f->block->R->rstride*f->offset;
    vsip_scalar_d *fptr_i=f->block->I->array+f->block->R->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->R->rstride;
    vsip_stride fstrd=f->stride*f->block->R->rstride;
    vsip_scalar_d re,im;
    for(i=0; i<nd; i++){
        ps.r=*(dptr_r+i*dstrd);
        ps.i=*(dptr_i+i*dstrd);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r=-1.0;
            else
                ps.r=1.0;
            m = (m<0) ? -m:m;
        } else {
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            *(d->block->R->array+(d->offset+i*d->stride)*d->block->cstride)=m;
            *(d->block->I->array+(d->offset+i*d->stride)*d->block->cstride)=0.0;
            if (i < nf){
                vsip_scalar_d *fr=fptr_r+i*fstrd;
                vsip_scalar_d *fi=fptr_i+i*fstrd;
                re=*fr; im=*fi;
                *fr=re*ps.r+im*ps.i;
                *fi=-ps.i*re+ps.r*im;
            }
        }else{
            *(dptr_r+i*dstrd)=0.0;
            *(dptr_i+i*dstrd)=0.0;
        }
    }
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps.r=*(fptr_r+i*fstrd);
        ps.i=*(fptr_i+i*fstrd);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r =-1.0;
            else
                ps.r = 1.0;
            m = (m < 0.0) ? -m:m;
        }else{
            re=fabs(ps.r); im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        *(fptr_r+i*fstrd)=m;
        *(fptr_i+i*fstrd)=0.0;
        re=*(fptr_r+ j * fstrd);
        im=*(fptr_i+ j * fstrd);
        *(fptr_r+ j * fstrd)=re*ps.r-im*ps.i;
        *(fptr_i+ j * fstrd)=re*ps.i+im*ps.r;
    }
    j=nf;
    i=j-1;
    ps.r=*(fptr_r+i*fstrd);
    ps.i=*(fptr_i+i*fstrd);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps.r =-1.0;
        else
            ps.r = 1.0;
        m = (m<0) ? -m:m;
    }else{
        re=fabs(ps.r); im=fabs(ps.i);
        m = CMAG_F(re,im);
        ps.r /= m; ps.i/=m;
    }
    *(fptr_r+i*fstrd)=m;
    *(fptr_i+i*fstrd)=0.0;
}
static void cphaseCheck_d(csvdObj_d *svd)
{
    vsip_cmview_d *L = &svd->Ls;
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nf=f->length;
    vsip_index i,k;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_cvview_d *l = &svd->ls_one;
    vsip_scalar_d *fptr=f->block->array + f->offset * f->block->rstride;
    vsip_scalar_d *dptr=d->block->array + d->offset * d->block->rstride;
    vsip_scalar_d *re,*im;
    vsip_stride strd;
    for(i=0; i<d->length; i++){
        ps=dptr[i];
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            ccol_sv_d(L,l,i);
            strd=l->stride*l->block->R->rstride;
            re=l->block->R->array+l->offset*l->block->R->rstride;
            im=l->block->I->array+l->offset*l->block->R->rstride;
            for(k=0; k<l->length*strd; k+=strd){
                re[k]*=ps;
                im[k]*=ps;
            }
            dptr[i]=m;
            if (i < nf)
                fptr[i]*=ps;
        } else {
            dptr[i]=0.0;
        }
    }
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fptr[i];
        if(f_i < 0.0) f_i = -f_i;
        m = (dptr[i] + dptr[i+1]) * eps0;
        if (f_i < m) fptr[i] = 0.0;
    }
}
static void cphaseCheck2_d(csvdObj_d *svd) /* save U */
{
    vsip_cmview_d *L = &svd->Ls;
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nf=f->length;
    vsip_index i,k;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_cvview_d *l = &svd->ls_one;
    vsip_scalar_d *fptr=f->block->array + f->offset * f->block->rstride;
    vsip_scalar_d *dptr=d->block->array + d->offset * d->block->rstride;
    vsip_scalar_d *re,*im;
    vsip_stride strd;
    for(i=0; i<d->length; i++){
        ps=dptr[i];
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            ccol_sv_d(L,l,i);
            strd=l->stride*l->block->R->rstride;
            re=l->block->R->array+l->offset*l->block->R->rstride;
            im=l->block->I->array+l->offset*l->block->R->rstride;
            for(k=0; k<l->length*strd; k+=strd){
                re[k]*=ps;
                im[k]*=ps;
            }
            dptr[i]=m;
            if (i < nf)
                fptr[i]*=ps;
        } else {
            dptr[i]=0.0;
        }
    }
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fptr[i];
        if(f_i < 0.0) f_i = -f_i;
        m = (dptr[i] + dptr[i+1]) * eps0;
        if (f_i < m) fptr[i] = 0.0;
    }
}
static void cphaseCheck1_d(csvdObj_d *svd) /* save V */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length nf=f->length;
    vsip_index i;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_scalar_d *fptr=f->block->array + f->offset * f->block->rstride;
    vsip_scalar_d *dptr=d->block->array + d->offset * d->block->rstride;
    for(i=0; i<d->length; i++){
        ps=dptr[i];
        m = (ps<0) ? -ps:ps;
        ps=sign_d(ps);
        if(m > eps0){
            dptr[i]=m;
            if (i < nf)
                fptr[i]*=ps;
        } else {
            dptr[i]=0.0;
        }
    }
    for(i=0; i<nf; i++){
        vsip_scalar_f f_i= fptr[i];
        if(f_i < 0.0) f_i = -f_i;
        m = (dptr[i] + dptr[i+1]) * eps0;
        if (f_i < m) fptr[i] = 0.0;
    }
}
static void chouseProd_d(vsip_cvview_d *v, vsip_cmview_d *A, vsip_cvview_d*w)
{
    vsip_scalar_d *Aptr_r = A->block->R->array+A->offset * A->block->R->rstride;
    vsip_scalar_d *Aptr_i = A->block->I->array+A->offset * A->block->R->rstride;
    vsip_scalar_d *vptr_r = v->block->R->array+v->offset * v->block->R->rstride;
    vsip_scalar_d *vptr_i = v->block->I->array+v->offset * v->block->R->rstride;
    vsip_scalar_d *wptr_r = w->block->R->array+w->offset * w->block->R->rstride;
    vsip_scalar_d *wptr_i = w->block->I->array+w->offset * w->block->R->rstride;
    vsip_stride vstrd=v->stride * v->block->R->rstride;
    vsip_stride wstrd=w->stride * w->block->R->rstride;
    vsip_stride AcStrd=A->col_stride*A->block->R->rstride;
    vsip_stride ArStrd=A->row_stride*A->block->R->rstride;
    vsip_index i,j,vi,wi;
    vsip_length M = A->col_length * A->col_stride * A->block->R->rstride;
    vsip_length N = A->row_length * A->row_stride * A->block->R->rstride;
    vsip_scalar_d beta = 0.0;
    vsip_scalar_d t1=0,t2=0;
    for(i=0;i<v->length;i++){
        vsip_scalar_d re=vptr_r[i*vstrd],im=vptr_i[i*vstrd];
        t1 += re*re;
        t2 += im*im;
    }
    beta=2.0/(t1+t2);
    w->length = A->row_length;
    for((void)(i=0), wi=0; i<N; (void)(i+=ArStrd), wi+=wstrd){
        vsip_scalar_d *ar_r=&Aptr_r[i], *ar_i=&Aptr_i[i];
        vsip_scalar_d re=0.0,im=0.0;
        for((void)(j=0), vi=0; j<M; (void)(j+=AcStrd), vi+=vstrd){
            re +=  ar_r[j] * vptr_r[vi] + ar_i[j] * vptr_i[vi];
            im += -ar_r[j] * vptr_i[vi] + ar_i[j] * vptr_r[vi];
        }
        wptr_r[wi] = re;
        wptr_i[wi] = -im;
    }
    for((void)(i=0), vi=0; i<M; (void)(i+=AcStrd), vi+=vstrd){
        vsip_scalar_d cr = beta * vptr_r[vi];
        vsip_scalar_d ci = beta * vptr_i[vi];
        vsip_scalar_d *aprp=Aptr_r+i;
        vsip_scalar_d *apip=Aptr_i+i;
        for((void)(j=0, wi=0); j<N; (void)(j+=ArStrd), wi+=wstrd){
            vsip_scalar_d yr =  wptr_r[wi];
            vsip_scalar_d yi = -wptr_i[wi];
            aprp[j] -= (cr * yr - ci * yi);
            apip[j] -= (cr * yi + ci * yr);
        }
    }
}
static void cprodHouse_d(vsip_cmview_d *A, vsip_cvview_d *v, vsip_cvview_d *w)
{
    vsip_scalar_d *Aptr_r = A->block->R->array+A->offset * A->block->R->rstride;
    vsip_scalar_d *Aptr_i = A->block->I->array+A->offset * A->block->R->rstride;
    vsip_scalar_d *vptr_r = v->block->R->array+v->offset * v->block->R->rstride;
    vsip_scalar_d *vptr_i = v->block->I->array+v->offset * v->block->R->rstride;
    vsip_scalar_d *wptr_r = w->block->R->array+w->offset * w->block->R->rstride;
    vsip_scalar_d *wptr_i = w->block->I->array+w->offset * w->block->R->rstride;
    vsip_stride vstrd=v->stride * v->block->R->rstride;
    vsip_stride wstrd=w->stride * w->block->R->rstride;
    vsip_stride AcStrd=A->col_stride*A->block->R->rstride;
    vsip_stride ArStrd=A->row_stride*A->block->R->rstride;
    vsip_index i,j,vi,wi;
    vsip_length M = A->col_length * A->col_stride * A->block->R->rstride;
    vsip_length N = A->row_length * A->row_stride * A->block->R->rstride;
    vsip_scalar_d beta = 0.0;
    vsip_scalar_d t1=0,t2=0;
    for(i=0;i<v->length;i++){
        vsip_scalar_d re=vptr_r[i*vstrd],im=vptr_i[i*vstrd];
        t1 += re*re;
        t2 += im*im;
    }
    beta=2.0/(t1+t2);
    
    w->length = A->col_length;
    for(i=0, wi=0; i<M; (void)(i+=AcStrd),wi+=wstrd){
        vsip_scalar_d *ac_r=&Aptr_r[i], *ac_i=&Aptr_i[i];
        vsip_scalar_d re=0.0,im=0.0;
        for(j=0, vi=0; j<N; (void)(j+=ArStrd), vi+=vstrd){
            re += ac_r[j] * vptr_r[vi] - ac_i[j] * vptr_i[vi];
            im += ac_r[j] * vptr_i[vi] + ac_i[j] * vptr_r[vi];
        }
        wptr_r[wi] = -beta * re;
        wptr_i[wi] = -beta * im;
    }
    for(i=0, wi=0; i<M; (void)(i+=AcStrd), wi+=wstrd){
        vsip_scalar_d cr = wptr_r[wi];
        vsip_scalar_d ci = wptr_i[wi];
        vsip_scalar_d *aprp=Aptr_r+i;
        vsip_scalar_d *apip=Aptr_i+i;
        for(j=0, vi=0; j<N; (void)(j+=ArStrd), vi+=vstrd){
            vsip_scalar_d yr =  vptr_r[vi];
            vsip_scalar_d yi = -vptr_i[vi];
            aprp[j] += (cr * yr - ci * yi);
            apip[j] += (cr * yi + ci * yr);
        }
    }
}
static vsip_cvview_d *chouseVector_d(vsip_cvview_d* x)
{
    vsip_scalar_d *x0r=x->block->R->array + x->offset * x->block->R->rstride;
    vsip_scalar_d *x0i=x->block->I->array + x->offset * x->block->R->rstride;
    vsip_scalar_d nrm=cvnorm2_d(x);
    vsip_cscalar_d t,s;
    t.r=*x0r;t.i=*x0i;
    s=csign_d(t);
    s.r *= nrm; s.i *= nrm;
    s.r += t.r; s.i +=t.i;
    *x0r = s.r;*x0i=s.i;
    nrm = cvnorm2_d(x);
    if (nrm == 0.0){
        *x0r=1.0;*x0i=0.0;
    }else{
        vsip_index i;
        vsip_stride str=x->stride * x->block->R->rstride;
        vsip_length n = x->length * str;
        for(i=0; i<n; i+=str){
            x0r[i] /= nrm;
            x0i[i] /= nrm;
        }
    }
    return x;
}
static void cVHmatExtract_d(csvdObj_d *svd)
{
    vsip_cmview_d *B = &svd->B;
    vsip_index i,j;
    vsip_length n = B->row_length;
    vsip_cmview_d *Bs=&svd->Bs;
    vsip_cmview_d *V=svd->R;
    vsip_cmview_d *Vs=&svd->Rs;
    vsip_cvview_d *v=&svd->bs;
    vsip_cscalar_d t;
    if(n < 3)
        return;
    for(i=n-3; i>0; i--){
        j=i+1;
        crow_sv_d(cmsv_d(B,Bs,i,j),v,0);
        t.r=*(v->block->R->array+v->offset*v->block->cstride);
        t.i=*(v->block->I->array+v->offset*v->block->cstride);
        *(v->block->R->array+v->offset*v->block->cstride)=1.0;
        *(v->block->I->array+v->offset*v->block->cstride)=0.0;
        cprodHouse_d(cmsv_d(V,Vs,j,j),v,svd->w);
        *(v->block->R->array+v->offset*v->block->cstride)=t.r;
        *(v->block->I->array+v->offset*v->block->cstride)=t.i;
    }
    crow_sv_d(cmsv_d(B,Bs,0,1),v,0);
    t.r=*(v->block->R->array+v->offset*v->block->cstride);
    t.i=*(v->block->I->array+v->offset*v->block->cstride);
    *(v->block->R->array+v->offset*v->block->cstride)=1.0;
    *(v->block->I->array+v->offset*v->block->cstride)=0.0;
    cprodHouse_d(cmsv_d(V,Vs,1,1),v,svd->w);
    *(v->block->R->array+v->offset*v->block->cstride)=t.r;
    *(v->block->I->array+v->offset*v->block->cstride)=t.i;
}
static void cUmatExtract_d(csvdObj_d *svd)
{
    vsip_cmview_d* B=&svd->B;
    vsip_cmview_d* U=svd->L;
    vsip_index i;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_cmview_d *Bs=&svd->Bs;
    vsip_cmview_d *Us=&svd->Ls;
    vsip_cvview_d *v=&svd->bs;
    vsip_cscalar_d t;
    if (m > n){
        i=n-1;
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t.r=*(v->block->R->array+v->offset*v->block->cstride);
        t.i=*(v->block->I->array+v->offset*v->block->cstride);
        *(v->block->R->array+v->offset*v->block->cstride)=1.0;
        *(v->block->I->array+v->offset*v->block->cstride)=0.0;
        chouseProd_d(v,cmsv_d(U,Us,i,i),svd->w);
        *(v->block->R->array+v->offset*v->block->cstride)=t.r;
        *(v->block->I->array+v->offset*v->block->cstride)=t.i;
    }
    for(i=n-2; i>0; i--){
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t.r=*(v->block->R->array+v->offset*v->block->cstride);
        t.i=*(v->block->I->array+v->offset*v->block->cstride);
        *(v->block->R->array+v->offset*v->block->cstride)=1.0;
        *(v->block->I->array+v->offset*v->block->cstride)=0.0;
        chouseProd_d(v,cmsv_d(U,Us,i,i),svd->w);
        *(v->block->R->array+v->offset*v->block->cstride)=t.r;
        *(v->block->I->array+v->offset*v->block->cstride)=t.i;
    }
    ccol_sv_d(cmsv_d(B,Bs,0,0),v,0);
    t.r=*(v->block->R->array+v->offset*v->block->cstride);
    t.i=*(v->block->I->array+v->offset*v->block->cstride);
    *(v->block->R->array+v->offset*v->block->cstride)=1.0;
    *(v->block->I->array+v->offset*v->block->cstride)=0.0;
    chouseProd_d(v,cmsv_d(U,Us,0,0),svd->w);
    *(v->block->R->array+v->offset*v->block->cstride)=t.r;
    *(v->block->I->array+v->offset*v->block->cstride)=t.i;
}
static void cbidiag_d(csvdObj_d *svd)
{
    vsip_cmview_d *B = &svd->B;
    vsip_cmview_d *Bs = &svd->Bs;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_cvview_d *x=ccol_sv_d(B,&svd->bs,0);
    vsip_cvview_d *v=svd->t;
    vsip_cvview_d *vs = &svd->ts;
    vsip_index i,j;
    vsip_cscalar_d z;
    vsip_scalar_d re,im;
    v->length = x->length;
    cvcopy_d(x,v);
    for(i=0; i<n-1; i++){
        v->length=m-i;
        ccol_sv_d(cmsv_d(B,Bs,i,i),x,0);
        cvcopy_d(x,v);/*0*/
        chouseVector_d(v);
        re=*(v->block->R->array+v->offset*v->block->cstride);
        im=*(v->block->I->array+v->offset*v->block->cstride);
        z.i=(re*re+im*im);z.r=re/z.i;z.i=-im/z.i;
        csvmul_d(z,v);
        chouseProd_d(v,Bs,svd->w);
        cvsv_d(v,vs,1);cvsv_d(x,x,1);
        cvcopy_d(vs,x);/*1*/
        if(i < n-2){
            j = i+1;
            v->length=n-j;
            crow_sv_d(cmsv_d(B,Bs,i,j),x,0);
            cvcopy_d(x,v);/*2*/
            chouseVector_d(v);
            {
                vsip_length _n = v->length;
                vsip_scalar_d *vpi = v->block->I->array + v->block->cstride * v->offset;
                vsip_stride vst = v->block->cstride * v->stride;
                while(_n-- > 0){
                    *vpi = - *vpi; vpi += vst;
                }
                
            }/*v.conj*/
            re=*(v->block->R->array+v->offset*v->block->cstride);
            im=*(v->block->I->array+v->offset*v->block->cstride);
            z.i=(re*re+im*im);z.r=re/z.i;z.i=-im/z.i;
            csvmul_d(z,v);
            cprodHouse_d(Bs,v,svd->w);
            cvsv_d(v,vs,1);cvsv_d(x,x,1);
            cvcopy_d(vs,x);/*3*/
        }
    }
    if(m > n){
        i=n-1;
        v->length=m-i;
        ccol_sv_d(cmsv_d(B,Bs,i,i),x,0);
        cvcopy_d(x,v);/*4*/
        chouseVector_d(v);
        re=*(v->block->R->array+v->offset*v->block->cstride);
        im=*(v->block->I->array+v->offset*v->block->cstride);
        z.i=(re*re+im*im);z.r=re/z.i;z.i=-im/z.i;
        csvmul_d(z,v);
        chouseProd_d(v,Bs,svd->w);
        cvsv_d(v,vs,1);cvsv_d(x,x,1);
        cvcopy_d(vs,x);/*5*/
    }
}
static void cgtProd_d(vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s,csvdObj_d *svd)
{
    vsip_cmview_d* R=&svd->Rs;
    vsip_cvview_d *a1= crow_sv_d(R,&svd->rs_one,i);
    vsip_cvview_d *a2= crow_sv_d(R,&svd->rs_two,j);
    vsip_index k;
    vsip_offset o = a1->block->R->rstride * a1->offset;
    vsip_stride std=a1->stride * a1->block->R->rstride;
    vsip_length n = a1->length;
    register vsip_scalar_d *a1r= a1->block->R->array;
    register vsip_scalar_d *a1i= a1->block->I->array;
    register vsip_scalar_d *a2r= a1r;
    register vsip_scalar_d *a2i= a1i;
    register vsip_scalar_d b1r,b1i,b2r,b2i;
    a1r+=o; a1i+=o;
    o=a2->block->R->rstride * a2->offset;
    a2r+=o; a2i+=o;
    for(k=0; k<n; k++){
        b1r = *a1r; b1i=*a1i; b2r=*a2r; b2i=*a2i;
        *a1r =c * b1r + s * b2r;
        *a1i =c * b1i + s * b2i;
        *a2r =c * b2r - s * b1r;
        *a2i =c * b2i - s * b1i;
        a1r+=std;a1i+=std;a2r+=std;a2i+=std;
    }
}
static void cprodG_d(csvdObj_d *svd,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_cmview_d* L=&svd->Ls;
    vsip_cvview_d *a1= ccol_sv_d(L,&svd->ls_one,i);
    vsip_cvview_d *a2= ccol_sv_d(L,&svd->ls_two,j);
    vsip_index k;
    vsip_offset o = a1->block->R->rstride * a1->offset;
    register vsip_stride std=a1->stride * a1->block->R->rstride;
    vsip_length n = a1->length;
    register vsip_scalar_d *a1r= a1->block->R->array;
    register vsip_scalar_d *a1i= a1->block->I->array;
    register vsip_scalar_d *a2r= a1r;
    register vsip_scalar_d *a2i= a1i;
    register vsip_scalar_d b1r,b1i,b2r,b2i;
    a1r+=o; a1i+=o;
    o=a2->block->R->rstride * a2->offset;
    a2r+=o; a2i+=o;
    for(k=0; k<n; k++){
        b1r = *a1r; b1i=*a1i; b2r=*a2r; b2i=*a2i;
        *a1r = c * b1r + s * b2r;
        *a1i = c * b1i + s * b2i;
        *a2r = c * b2r - s * b1r;
        *a2i = c * b2i - s * b1i;
        a1r+=std;a1i+=std;a2r+=std;a2i+=std;
    }
}
static void czeroCol_d(csvdObj_d *svd)
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
        cgtProd_d(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        cgtProd_d(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        cgtProd_d(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        cgtProd_d(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
            cgtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        cgtProd_d(0,k+1,g.c,g.s,svd);
    }
}
static void czeroRow_d(csvdObj_d *svd)
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    vsip_scalar_d *dptr=d->block->array+d->block->rstride*d->offset;
    vsip_scalar_d *fptr=f->block->array+f->block->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->rstride;
    vsip_stride fstrd=f->stride*f->block->rstride;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
        cprodG_d(svd,1,0,g.c,g.s);
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstrd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstrd)=xf;
        cprodG_d(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=*(dptr+i*dstrd);
            g=givensCoef_d(xd,t);
            cprodG_d(svd,i+1,0,g.c,g.s);
            *(dptr+i*dstrd)=g.r;
            xf=*(fptr+(i+1)*fstrd);
            t=-xf * g.s; xf *= g.c;
            *(fptr+(i+1)*fstrd)=xf;
        }
        xd=*(dptr+(n-1)*dstrd);
        g=givensCoef_d(xd,t);
        *(dptr+(n-1)*dstrd)=g.r;
        cprodG_d(svd,n,0,g.c,g.s);
    }
}
static void czeroCol2_d(csvdObj_d *svd) /* save U */
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
    }else{
        i=n-1; j=i-1;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
    }
}
static void czeroRow2_d(csvdObj_d *svd) /* save U */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    vsip_scalar_d *dptr=d->block->array+d->block->rstride*d->offset;
    vsip_scalar_d *fptr=f->block->array+f->block->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->rstride;
    vsip_stride fstrd=f->stride*f->block->rstride;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
        cprodG_d(svd,1,0,g.c,g.s);
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstrd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstrd)=xf;
        cprodG_d(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=*(dptr+i*dstrd);
            g=givensCoef_d(xd,t);
            cprodG_d(svd,i+1,0,g.c,g.s);
            *(dptr+i*dstrd)=g.r;
            xf=*(fptr+(i+1)*fstrd);
            t=-xf * g.s; xf *= g.c;
            *(fptr+(i+1)*fstrd)=xf;
        }
        xd=*(dptr+(n-1)*dstrd);
        g=givensCoef_d(xd,t);
        *(dptr+(n-1)*dstrd)=g.r;
        cprodG_d(svd,n,0,g.c,g.s);
    }
}
static void czeroCol1_d(csvdObj_d *svd) /* save V */
{
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_d(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
        cgtProd_d(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_d(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;
        cgtProd_d(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        cgtProd_d(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_d(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
        cgtProd_d(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_d(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;
            cgtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_d(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        cgtProd_d(0,k+1,g.c,g.s,svd);
    }
}
static void czeroRow1_d(csvdObj_d *svd) /* save V */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    vsip_length n = d->length;
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    vsip_scalar_d *dptr=d->block->array+d->block->rstride*d->offset;
    vsip_scalar_d *fptr=f->block->array+f->block->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->rstride;
    vsip_stride fstrd=f->stride*f->block->rstride;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_d(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstrd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstrd)=xf;
        for(i=1; i<n-1; i++){
            xd=*(dptr+i*dstrd);
            g=givensCoef_d(xd,t);
            *(dptr+i*dstrd)=g.r;
            xf=*(fptr+(i+1)*fstrd);
            t=-xf * g.s; xf *= g.c;
            *(fptr+(i+1)*fstrd)=xf;
        }
        xd=*(dptr+(n-1)*dstrd);
        g=givensCoef_d(xd,t);
        *(dptr+(n-1)*dstrd)=g.r;
    }
}
static void csvdStep_d(csvdObj_d *svd)
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr,*tdptr,*tfptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c * x2 - g.s * x1;
    *dptr=x1 * g.c + x2 * g.s;
    tdptr=dptr+dstd;
    t=*tdptr; *tdptr=t*g.c;
    t*=g.s;
    cgtProd_d(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        tdptr=dptr+i*dstd;
        tfptr=fptr+i*fstd;
        g = givensCoef_d(*tdptr,t);
        *tdptr=g.r;
        x1 = *(tdptr+dstd)*g.c;
        x2=*tfptr*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(fptr+i*fstd)= x1+x2;
        *(dptr+j*dstd) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd) = x1*g.c;
        cprodG_d(svd,i, j, g.c, g.s);
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2;
        *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1;
        *(dptr+k*dstd)=x1*g.c;
        cgtProd_d(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(dptr+i*dstd)=g.r;
    x1=*(dptr+j*dstd)*g.c;
    x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(fptr+i*fstd)=x1+x2;
    *(dptr+j*dstd)=t;
    cprodG_d(svd,i, j, g.c, g.s);
}
static void csvdStep2_d(csvdObj_d *svd) /* save U */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr,*tdptr,*tfptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c * x2 - g.s * x1;
    *dptr=x1 * g.c + x2 * g.s;
    tdptr=dptr+dstd;
    t=*tdptr; *tdptr=t*g.c;
    t*=g.s;
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        tdptr=dptr+i*dstd;
        tfptr=fptr+i*fstd;
        g = givensCoef_d(*tdptr,t);
        *tdptr=g.r;
        x1 = *(tdptr+dstd)*g.c;
        x2=*tfptr*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(fptr+i*fstd)= x1+x2;
        *(dptr+j*dstd) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd) = x1*g.c;
        cprodG_d(svd,i, j, g.c, g.s);
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2;
        *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1;
        *(dptr+k*dstd)=x1*g.c;
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(dptr+i*dstd)=g.r;
    x1=*(dptr+j*dstd)*g.c;
    x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(fptr+i*fstd)=x1+x2;
    *(dptr+j*dstd)=t;
    cprodG_d(svd,i, j, g.c, g.s);
}
static void csvdStep1_d(csvdObj_d *svd) /* save V */
{
    vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f = &svd->fs;
    givensObj_d g;
    vsip_length n = d->length;
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_d *fptr,*dptr,*tdptr,*tfptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_d");
        exit(-1);
    }
    mu = svdMu_d(d2,f1,d3,&f2,svd->eps0);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_d(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c * x2 - g.s * x1;
    *dptr=x1 * g.c + x2 * g.s;
    tdptr=dptr+dstd;
    t=*tdptr; *tdptr=t*g.c;
    t*=g.s;
    cgtProd_d(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        tdptr=dptr+i*dstd;
        tfptr=fptr+i*fstd;
        g = givensCoef_d(*tdptr,t);
        *tdptr=g.r;
        x1 = *(tdptr+dstd)*g.c;
        x2=*tfptr*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(fptr+i*fstd)= x1+x2;
        *(dptr+j*dstd) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd) = x1*g.c;
        g=givensCoef_d(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2;
        *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1;
        *(dptr+k*dstd)=x1*g.c;
        cgtProd_d(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(*(dptr+i*dstd),t);
    *(dptr+i*dstd)=g.r;
    x1=*(dptr+j*dstd)*g.c;
    x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(fptr+i*fstd)=x1+x2;
    *(dptr+j*dstd)=t;
}
static void svdFinalize_d(svdObj_d *s)
{
    if(s) {
        vsip_valldestroy_d(s->t);
        vsip_valldestroy_d(s->w);
        vsip_malldestroy_d(s->R);
        vsip_malldestroy_d(s->L);
        vsip_valldestroy_vi(s->indx_L);
        vsip_valldestroy_vi(s->indx_R);
        vsip_valldestroy_d(s->d);
        vsip_valldestroy_d(s->f);
        free(s);
    }
    s=NULL;
}
static svdObj_d* svdInit_d(vsip_length m, vsip_length n,int Usave,int Vsave)
{
    svdObj_d *s=malloc(sizeof(svdObj_d));
    if(m < n){
        printf("Column length must not be less than row length");
        return NULL;
    }
    if(!s) {
        printf("\nfailed to allocate svd object\n");
        return NULL;
    }
    s->init=0;
    if(!(s->t = vsip_vcreate_d(m,VSIP_MEM_NONE)))s->init++;else s->ts = *s->t;
    if(!(s->w = vsip_vcreate_d(m,VSIP_MEM_NONE)))s->init++;
    if(Usave){
        if(Usave == 1 ){
            if(!(s->L=vsip_mcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
            if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
        }else{ /* must be part */
            if(!(s->L=vsip_mcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
            if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
        }
    } else {
        s->L=NULL;
        s->indx_L=NULL;
    }
    if(Vsave){
        if(!(s->R=vsip_mcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
        if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    } else {
        s->R=NULL;
        s->indx_R=NULL;
    }
    if(!(s->d = vsip_vcreate_d(n,VSIP_MEM_NONE)))s->init++;
    if(!(s->f = vsip_vcreate_d(n-1,VSIP_MEM_NONE)))s->init++;
    if(s->init){
        svdFinalize_d(s);
        return NULL;
    }
    if(Usave) meye_d(s->L);
    if(Vsave) meye_d(s->R);
    return s;
}
static void svdBidiag_d(svdObj_d *svd)
{
    svd->eps0=(mnormFro_d((&svd->B))/(vsip_scalar_d)svd->B.row_length)*EPS;
    bidiag_d(svd);
    UmatExtract_d(svd);
    VHmatExtract_d(svd);
    biDiagPhaseToZero_d(svd);
}
static void svdBidiag2_d(svdObj_d *svd) /* save U */
{
    svd->eps0=(mnormFro_d((&svd->B))/(vsip_scalar_d)svd->B.row_length)*EPS;
    bidiag_d(svd);
    UmatExtract_d(svd);
    biDiagPhaseToZero2_d(svd);
}
static void svdBidiag1_d(svdObj_d *svd) /* save V */
{
    svd->eps0=(mnormFro_d((&svd->B))/(vsip_scalar_d)svd->B.row_length)*EPS;
    bidiag_d(svd);
    VHmatExtract_d(svd);
    biDiagPhaseToZero1_d(svd);
}
static void svdBidiag0_d(svdObj_d *svd)
{
    svd->eps0=(mnormFro_d(&svd->B)/(vsip_scalar_d)svd->B.row_length)*EPS;
    bidiag_d(svd);
    biDiagPhaseToZero0_d(svd);
}
static void svdIteration_d(svdObj_d* svd)
{
    vsip_mview_d *L0 = svd->L; vsip_mview_d *L = &svd->Ls;
    vsip_vview_d *d0 = svd->d; vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f0 = svd->f; vsip_vview_d *f = &svd->fs;
    vsip_mview_d *R0 = svd->R; vsip_mview_d *R= &svd->Rs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;*L=*L0; *R=*R0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        imsv_d(L0,L,0,0,cnr.i,cnr.j);
        imsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0 ){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                zeroCol_d(svd);
            }else{
                imsv_d(L,L,0,0,k,0);
                d->length-=k+1;
                d->offset += k+1;
                f->length -= k;
                f->offset += k;
                zeroRow_d(svd);
            }
        }else{
            svdStep_d(svd);
        }
        phaseCheck_d(svd);
    }
}
static void svdIteration2_d(svdObj_d* svd) /* save U */
{
    vsip_mview_d *L0 = svd->L; vsip_mview_d *L = &svd->Ls;
    vsip_vview_d *d0 = svd->d; vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f0 = svd->f; vsip_vview_d *f = &svd->fs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;*L=*L0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        imsv_d(L0,L,0,0,cnr.i,cnr.j);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0 ){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                zeroCol2_d(svd);
            }else{
                imsv_d(L,L,0,0,k,0);
                d->length-=k+1;
                d->offset += k+1;
                f->length -= k;
                f->offset += k;
                zeroRow2_d(svd);
            }
        }else{
            svdStep2_d(svd);
        }
        phaseCheck2_d(svd);
    }
}
static void svdIteration1_d(svdObj_d* svd) /* save V */
{
    vsip_vview_d *d0 = svd->d; vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f0 = svd->f; vsip_vview_d *f = &svd->fs;
    vsip_mview_d *R0 = svd->R; vsip_mview_d *R= &svd->Rs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0; *R=*R0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        imsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0 ){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                zeroCol1_d(svd);
            }else{
                d->length-=k+1;
                d->offset += k+1;
                f->length -= k;
                f->offset += k;
                zeroRow1_d(svd);
            }
        }else{
            svdStep1_d(svd);
        }
        phaseCheck1_d(svd);
    }
}
static void svdIteration0_d(svdObj_d* svd)
{
    vsip_vview_d *d0 = svd->d; vsip_vview_d *d = &svd->ds;
    vsip_vview_d *f0 = svd->f; vsip_vview_d *f = &svd->fs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0 ){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                zeroCol0_d(svd);
            }else{
                d->length-=k+1;
                d->offset += k+1;
                f->length -= k;
                f->offset += k;
                zeroRow0_d(svd);
            }
        }else{
            svdStep0_d(svd);
        }
        phaseCheck0_d(svd);
    }
}
static void svdSort_d(svdObj_d *svd)
{
    vsip_vview_d *d = svd->d;
    vsip_length n=d->length;
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_mview_d *L0 = svd->L; vsip_mview_d *L=&svd->Ls;
    vsip_mview_d *R0 = svd->R;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vcopy_vi(indx_L,indx_R);
    imsv_d( L0, L, 0,0, 0, n);
    mpermute_onceCol_d(L,indx_L);
    mpermute_onceRow_d(R0,indx_R);
}
static void svdSort2_d(svdObj_d *svd) /* save U */
{
    vsip_vview_d *d = svd->d;
    vsip_length n=d->length;
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_mview_d *L0 = svd->L; vsip_mview_d *L=&svd->Ls;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    imsv_d( L0, L, 0,0, 0, n);
    mpermute_onceCol_d(L,indx_L);
}
static void svdSort1_d(svdObj_d *svd) /* save V */
{
    vsip_vview_d *d = svd->d;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_mview_d *R0 = svd->R;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_R);
    mpermute_onceRow_d(R0,indx_R);
}
static void svdSort0_d(svdObj_d *svd)
{
    vsip_vview_d *d = svd->d;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_FALSE,NULL);
}
static void svd_d(svdObj_d *s,int Usave, int Vsave)
{
    if(Usave && Vsave){
        svdBidiag_d(s);
        svdIteration_d(s);
        svdSort_d(s);
    }else if(Usave){
        svdBidiag2_d(s);
        svdIteration2_d(s);
        svdSort2_d(s);
    }else if (Vsave){
        svdBidiag1_d(s);
        svdIteration1_d(s);
        svdSort1_d(s);
    }else{
        svdBidiag0_d(s);
        svdIteration0_d(s);
        svdSort0_d(s);
    }
}
static void csvdFinalize_d(csvdObj_d *s)
{
    if(s) {
        vsip_cvalldestroy_d((s)->t);
        vsip_cvalldestroy_d((s)->w);
        vsip_cmalldestroy_d((s)->R);
        vsip_cmalldestroy_d((s)->L);
        vsip_valldestroy_vi((s)->indx_L);
        vsip_valldestroy_vi((s)->indx_R);
        vsip_valldestroy_d((s)->d);
        vsip_valldestroy_d((s)->f);
        free(s);
    }
    s=NULL;
}
static csvdObj_d* csvdInit_d(vsip_length m, vsip_length n,int Usave,int Vsave)
{
    csvdObj_d *s=malloc(sizeof(csvdObj_d));
    if(m < n){
        printf("Column length must not be less than row length");
        return NULL;
    }
    if(!s) {
        printf("\nfailed to allocate svd object\n");
        return NULL;
    }
    s->init=0;
    if(!(s->t = vsip_cvcreate_d(m,VSIP_MEM_NONE)))s->init++;else s->ts = *s->t;
    if(!(s->w = vsip_cvcreate_d(m,VSIP_MEM_NONE)))s->init++;
    if(Usave){
        if(Usave == 1 ){
            if(!(s->L=vsip_cmcreate_d(m,m,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
            if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
        }else{ /* must be part */
            if(!(s->L=vsip_cmcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
            if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
        }
    } else {
        s->L=NULL;
        s->indx_L=NULL;
    }
    if(Vsave){
        if(!(s->R=vsip_cmcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
        if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    } else {
        s->R=NULL;
        s->indx_R=NULL;
    }
    if(!(s->d = vsip_vcreate_d(n,VSIP_MEM_NONE)))s->init++;
    if(!(s->f = vsip_vcreate_d(n-1,VSIP_MEM_NONE)))s->init++;
    if(s->init){
        csvdFinalize_d(s);
        return NULL;
    }
    if(Usave) cmeye_d(s->L);
    if(Vsave) cmeye_d(s->R);
    return s;
}
static void csvdBidiag_d(csvdObj_d *svd)
{
    svd->eps0=cmnormFro_d(&svd->B)/(vsip_scalar_d)(svd->B.row_length) * EPS;
    cbidiag_d(svd);
    cUmatExtract_d(svd);
    cVHmatExtract_d(svd);
    cbiDiagPhaseToZero_d(svd);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 0),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->d);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 1),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->f);
}
static void csvdBidiag2_d(csvdObj_d *svd)
{
    svd->eps0=cmnormFro_d(&svd->B)/(vsip_scalar_d)(svd->B.row_length) * EPS;
    cbidiag_d(svd);
    cUmatExtract_d(svd);
    cbiDiagPhaseToZero2_d(svd);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 0),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->d);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 1),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->f);
}
static void csvdBidiag1_d(csvdObj_d *svd)
{
    svd->eps0=cmnormFro_d(&svd->B)/(vsip_scalar_d)(svd->B.row_length) * EPS;
    cbidiag_d(svd);
    cVHmatExtract_d(svd);
    cbiDiagPhaseToZero1_d(svd);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 0),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->d);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 1),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->f);
}
static void csvdBidiag0_d(csvdObj_d *svd)
{
    svd->eps0=cmnormFro_d(&svd->B)/(vsip_scalar_d)(svd->B.row_length) * EPS;
    cbidiag_d(svd);
    cbiDiagPhaseToZero0_d(svd);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 0),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->d);
    vreal_sv_d(cdiag_sv_d(&svd->B, &svd->bs, 1),(&svd->rbs));
    vcopy_d((&svd->rbs),svd->f);
}
static void csvdIteration_d(csvdObj_d *svd)
{
    vsip_cmview_d *L0 = svd->L;
    vsip_vview_d *d0 = svd->d;
    vsip_vview_d *f0 = svd->f;
    vsip_cmview_d *R0 = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_cmview_d *L=&svd->Ls;
    vsip_cmview_d *R=&svd->Rs;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;*L=*L0; *R=*R0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        cimsv_d(L0,L,0,0,cnr.i,cnr.j);
        cimsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                czeroCol_d(svd);
            }else{
                cimsv_d(L,L,0,0,k,0);
                d->length-=(k+1);
                d->offset += (k+1);
                f->length -= k;
                f->offset += k;
                czeroRow_d(svd);
            }
        }else{
            csvdStep_d(svd);
        }
        cphaseCheck_d(svd);
    }
}
static void csvdIteration2_d(csvdObj_d *svd) /* save U */
{
    vsip_cmview_d *L0 = svd->L;
    vsip_vview_d *d0 = svd->d;
    vsip_vview_d *f0 = svd->f;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_cmview_d *L=&svd->Ls;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;*L=*L0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        cimsv_d(L0,L,0,0,cnr.i,cnr.j);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                czeroCol2_d(svd);
            }else{
                cimsv_d(L,L,0,0,k,0);
                d->length-=(k+1);
                d->offset += (k+1);
                f->length -= k;
                f->offset += k;
                czeroRow2_d(svd);
            }
        }else{
            csvdStep2_d(svd);
        }
        cphaseCheck2_d(svd);
    }
}
static void csvdIteration1_d(csvdObj_d *svd) /* save V */
{
    vsip_vview_d *d0 = svd->d;
    vsip_vview_d *f0 = svd->f;
    vsip_cmview_d *R0 = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_vview_d *d=&svd->ds;
    vsip_vview_d *f=&svd->fs;
    vsip_cmview_d *R=&svd->Rs;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;*R=*R0;
    while (cntr++ < maxcntr){
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        cimsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=f->length;
        k=zeroFind_d(d,eps0);
        if (k > 0){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                czeroCol1_d(svd);
            }else{
                d->length-=(k+1);
                d->offset += (k+1);
                f->length -= k;
                f->offset += k;
                czeroRow1_d(svd);
            }
        }else{
            csvdStep1_d(svd);
        }
        cphaseCheck1_d(svd);
    }
}
static void csvdSort_d(csvdObj_d *svd)
{
    vsip_cmview_d* L0 = svd->L;
    vsip_vview_d* d = svd->d;
    vsip_cmview_d* R0 = svd->R;
    vsip_length n=d->length;
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_cmview_d *L=&svd->Ls;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vcopy_vi(indx_L,indx_R);
    cimsv_d( L0, L, 0,0, 0, n);
    cmpermute_onceCol_d(L,indx_L);
    cmpermute_onceRow_d(R0,indx_R);
}
static void csvdSort2_d(csvdObj_d *svd) /* save U */
{
    vsip_cmview_d* L0 = svd->L;
    vsip_vview_d* d = svd->d;
    vsip_length n=d->length;
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_cmview_d *L=&svd->Ls;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    cimsv_d( L0, L, 0,0, 0, n);
    cmpermute_onceCol_d(L,indx_L);
}
static void csvdSort1_d(csvdObj_d *svd) /* save V */
{
    vsip_vview_d* d = svd->d;
    vsip_cmview_d* R0 = svd->R;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_R);
    cmpermute_onceRow_d(R0,indx_R);
}
static void csvd_d(csvdObj_d *s,int Usave,int Vsave)
{
    if(Usave && Vsave){
        csvdBidiag_d(s);
        csvdIteration_d(s);
        csvdSort_d(s);
    }else if(Usave){
        csvdBidiag2_d(s);
        csvdIteration2_d(s);
        csvdSort2_d(s);
    }else if (Vsave){
        csvdBidiag1_d(s);
        csvdIteration1_d(s);
        csvdSort1_d(s);
    }else{
        svdObj_d t;
        csvdBidiag0_d(s); /* after bidiag this path same as real */
        t.eps0=s->eps0;
        t.d=s->d;t.ds=s->ds;t.f=s->f;t.fs=s->fs;
        svdIteration0_d(&t);
        svdSort0_d(&t);
    }
}

/* Real */
int
vsip_svd_destroy_d(vsip_sv_d* s)
{
    if(s){
        svdObj_d* svd=(svdObj_d*)s->svd;
        svdFinalize_d(svd);
        free((void*)s);
        s=NULL;
    }
    return 0;
}
vsip_sv_d *
vsip_svd_create_d(vsip_length M, vsip_length N, vsip_svd_uv Usave, vsip_svd_uv Vsave)
{
    vsip_sv_d *s = (vsip_sv_d*) malloc(sizeof(vsip_sv_d));
    if(s){
        if(M < N){
            s->svd = (void*) svdInit_d(N,M,Vsave,Usave);
        }else{
            s->svd = (void*) svdInit_d(M,N,Usave,Vsave);
        }
        if(s->svd){
            s->attr.Usave=Usave;
            s->attr.Vsave=Vsave;
            s->attr.m=M;
            s->attr.n=N;
            s->transpose = M < N ? 1:0;
        } else {
            vsip_svd_destroy_d(s);
        }
    }
    return s;
}
int
vsip_svd_d(vsip_sv_d *svd, const vsip_mview_d *A, vsip_vview_d *sv)
{
    svdObj_d *s = (svdObj_d*) svd->svd;
    if(svd->transpose){
        s->B = *A;
        s->B.col_length=A->row_length;
        s->B.row_length=A->col_length;
        s->B.col_stride=A->row_stride;
        s->B.row_stride=A->col_stride;
    } else {
        s->B=*A;
    }
    if(svd->transpose){
        svd_d(s,svd->attr.Vsave,svd->attr.Usave);
    } else {
        svd_d(s,svd->attr.Usave,svd->attr.Vsave);
    }
    vcopy_d(s->d,sv)
    return 0;
}
void
vsip_svd_getattr_d(const vsip_sv_d *svd, vsip_sv_attr_d *attrib)
{
    attrib->Usave = svd->attr.Usave;
    attrib->Vsave = svd->attr.Vsave;
    attrib->m = svd->attr.m;
    attrib->n = svd->attr.n;
}
int
vsip_svdmatu_d(const vsip_sv_d *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_mview_d *C)
{
    svdObj_d *s = (svdObj_d*) svd->svd;
    sv_attr attr = svd->attr;
    int retval = 0;
    if(attr.Usave){
        if(svd->transpose){
            vsip_mview_d *L = s->R;
            vsip_mview_d *Ls = &s->Rs;
            Ls->offset=L->offset + L->col_stride * low;
            Ls->row_stride=L->col_stride; Ls->col_stride=L->row_stride;
            Ls->row_length = (high-low) + 1; Ls->col_length=L->row_length;
            mcopy_d(Ls,C);
        } else {
            vsip_mview_d *L = s->L;
            vsip_mview_d *Ls = &s->Ls;
            Ls->offset = L->offset + L->row_stride * low;
            Ls->row_length = (high-low) + 1;
            Ls->col_length = L->col_length;
            Ls->row_stride = L->row_stride;
            Ls->col_stride = L->col_stride;
            mcopy_d(Ls,C);
        }
    } else {
        retval = 1;
    }
    return retval;
}
int
vsip_svdmatv_d(const vsip_sv_d *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_mview_d *C)
{
    svdObj_d *s = (svdObj_d*) svd->svd;
    sv_attr attr = svd->attr;
    int retval = 0;
    if(attr.Vsave){
        if(svd->transpose){
            vsip_mview_d *R  = s->L;
            vsip_mview_d *Rs = &s->Ls;
            *Rs=*R;
            Rs->offset += Rs->row_stride * low;
            Rs->row_length = (high-low) + 1;
            mcopy_d(Rs,C);
        } else {
            vsip_mview_d *R  = s->R;
            vsip_mview_d *Rs = &s->Rs;
            Rs->offset=R->offset;
            Rs->row_stride=R->col_stride;
            Rs->col_stride=R->row_stride;
            Rs->row_length=R->col_length;
            Rs->col_length=R->row_length;
            Rs->offset += Rs->row_stride * low;
            Rs->row_length = (high-low) + 1;
            mcopy_d(Rs,C);
        }
    } else {
        retval = 1;
    }
    return retval;
}
int
vsip_svdprodu_d(const vsip_sv_d *svd, vsip_mat_op OpU, vsip_mat_side ApU, const vsip_mview_d *In)
{
    svdObj_d* svdObj=(svdObj_d*)svd->svd;
    vsip_mview_d c = *In;
    vsip_mview_d C = *In;
    vsip_index i;
    vsip_vview_d y;
    vsip_mview_d U;
    if(svd->attr.Usave == VSIP_SVD_UVNOS) return 1;
    if((OpU != VSIP_MAT_NTRANS) && (OpU != VSIP_MAT_TRANS)) return 2;
    if( (ApU != VSIP_MAT_LSIDE) && (ApU != VSIP_MAT_RSIDE)) return 3;
    if(svd->transpose){
        U = *(svdObj->R);
        U.row_stride = svdObj->R->col_stride; U.col_stride=svdObj->R->row_stride;
        U.row_length = svdObj->R->col_length; U.col_length=svdObj->R->row_length;
    } else {
        U = *(svdObj->L);
    }
    /* UVPART and UVFULL operate the same */
    if (ApU == VSIP_MAT_LSIDE){
        if(OpU == VSIP_MAT_NTRANS){
            vsip_vview_d x = *(svdObj->w);
            x.offset=0;x.length=U.col_length;x.stride=1;
            c.col_length=U.col_length;
            for(i=0; i<c.row_length; i++){
                mvprod_d(&U,col_sv_d(&C,&y,i),&x);
                vcopy_d(&x,col_sv_d(&c,&y,i))
            }
        } else { /* must be TRANS */
            vsip_vview_d x = *(svdObj->w);
            vsip_length rl=U.row_length;
            vsip_stride rs=U.row_stride;
            U.row_length = U.col_length;
            U.col_length = rl;
            U.row_stride = U.col_stride;
            U.col_stride = rs;
            x.offset=0;x.length=U.col_length;x.stride=1;
            c.col_length=U.col_length;
            for(i=0; i<c.row_length; i++){
                mvprod_d(&U,col_sv_d(&C,&y,i),&x);
                vcopy_d(&x,col_sv_d(&c,&y,i))
            }
        }
    } else { /* must be MAT_RSIDE */
        if(OpU == VSIP_MAT_NTRANS){
            vsip_vview_d x = *(svdObj->w);
            x.offset=0;x.length=U.row_length;x.stride=1;
            c.row_length = U.row_length;
            for(i=0; i<c.col_length; i++){
                vmprod_d(row_sv_d(&C,&y,i),&U,&x);
                vcopy_d(&x,row_sv_d(&c,&y,i))
            }
        } else {
            vsip_vview_d x = *(svdObj->w);
            vsip_length rl=U.row_length;
            vsip_stride rs=U.row_stride;
            U.row_length = U.col_length;
            U.col_length = rl;
            U.row_stride = U.col_stride;
            U.col_stride = rs;
            x.offset=0;x.length=U.row_length;x.stride=1;
            c.row_length=U.row_length;
            for(i=0; i<c.col_length; i++){
                vmprod_d(row_sv_d(&C,&y,i),&U,&x);
                vcopy_d(&x,row_sv_d(&c,&y,i))
            }
        }
    }
    return 0;
}
int
vsip_svdprodv_d(const vsip_sv_d *svd, vsip_mat_op OpV, vsip_mat_side ApV,const vsip_mview_d *In)
{
    svdObj_d* svdObj=(svdObj_d*)svd->svd;
    vsip_mview_d c = *In;
    vsip_mview_d C = *In;
    vsip_index i;
    vsip_vview_d y;
    vsip_mview_d V;
    if(svd->attr.Vsave == VSIP_SVD_UVNOS) return 1;
    if((OpV != VSIP_MAT_NTRANS) && (OpV != VSIP_MAT_TRANS)) return 2;
    if( (ApV != VSIP_MAT_LSIDE) && (ApV != VSIP_MAT_RSIDE)) return 3;
    if(svd->transpose){
        V = *(svdObj->L);
    } else {
        V = *(svdObj->R);
        V.row_stride = svdObj->R->col_stride; V.col_stride=svdObj->R->row_stride;
        V.row_length = svdObj->R->col_length; V.col_length=svdObj->R->row_length;
    }
    /* UVPART and UVFULL operate the same */
    if (ApV == VSIP_MAT_LSIDE){
        if(OpV == VSIP_MAT_NTRANS){
            vsip_vview_d x = *(svdObj->w);
            x.offset=0;x.length=V.row_length;x.stride=1;
            c.col_length=V.col_length;
            for(i=0; i<c.row_length; i++){
                mvprod_d(&V,col_sv_d(&C,&y,i),&x);
                vcopy_d(&x,col_sv_d(&c,&y,i))
            }
        } else { /* must be TRANS */
            vsip_vview_d x = *(svdObj->w);
            vsip_length rl=V.row_length;
            vsip_stride rs=V.row_stride;
            V.row_length = V.col_length;
            V.col_length = rl;
            V.row_stride = V.col_stride;
            V.col_stride = rs;
            x.offset=0;x.length=V.col_length;x.stride=1;
            c.col_length=V.col_length;
            for(i=0; i<c.row_length; i++){
                mvprod_d(&V,col_sv_d(&C,&y,i),&x);
                vcopy_d(&x,col_sv_d(&c,&y,i))
            }
        }
    } else { /* must be MAT_RSIDE */
        if(OpV == VSIP_MAT_NTRANS){
            vsip_vview_d x = *(svdObj->w);
            x.offset=0;x.length=V.row_length;x.stride=1;
            c.row_length = V.row_length;
            for(i=0; i<c.col_length; i++){
                vmprod_d(row_sv_d(&C,&y,i),&V,&x);
                vcopy_d(&x,row_sv_d(&c,&y,i))
            }
        } else {
            vsip_vview_d x = *(svdObj->w);
            vsip_length rl=V.row_length;
            vsip_stride rs=V.row_stride;
            V.row_length = V.col_length;
            V.col_length = rl;
            V.row_stride = V.col_stride;
            V.col_stride = rs;
            x.offset=0;x.length=V.row_length;x.stride=1;
            c.row_length=V.row_length;
            for(i=0; i<c.col_length; i++){
                vmprod_d(row_sv_d(&C,&y,i),&V,&x);
                vcopy_d(&x,row_sv_d(&c,&y,i))
            }
        }
    }
    return 0;
}

/* Complex */
int
vsip_csvd_destroy_d(vsip_csv_d* s)
{
    if(s){
        csvdObj_d* svd=(csvdObj_d*)s->svd;
        csvdFinalize_d(svd);
        s->svd=NULL;
        free((void*)s);
        s=NULL;
    }
    return 0;
}
vsip_csv_d *
vsip_csvd_create_d(vsip_length M, vsip_length N, vsip_svd_uv Usave, vsip_svd_uv Vsave)
{
    vsip_csv_d *s = (vsip_csv_d*) malloc(sizeof(vsip_csv_d));
    if(s){
        if(M < N){
            s->svd = (void*) csvdInit_d(N,M,Vsave,Usave);
        }else{
            s->svd = (void*)csvdInit_d(M,N,Usave,Vsave);
        }
        if(s->svd){
            s->attr.Usave=Usave;
            s->attr.Vsave=Vsave;
            s->attr.m=M;
            s->attr.n=N;
            s->transpose = M < N ? 1:0;
        } else {
            vsip_svd_destroy_d(s);
            s=NULL;
        }
    }
    return s;
}
int
vsip_csvd_d(vsip_csv_d *svd, const vsip_cmview_d *A, vsip_vview_d *sv)
{
    csvdObj_d *s = (csvdObj_d*) svd->svd;
    if(svd->transpose){
        s->B=*A;
        s->B.row_length=A->col_length;
        s->B.col_length=A->row_length;
        s->B.row_stride=A->col_stride;
        s->B.col_stride=A->row_stride;
        cmconj_d(A, A);
    } else {
        s->B=*A;
    }
    if(svd->transpose){
        csvd_d(s,svd->attr.Vsave,svd->attr.Usave);
    } else {
        csvd_d(s,svd->attr.Usave,svd->attr.Vsave);
    }
    vcopy_d(s->d,sv);
    return 0;
}
void
vsip_csvd_getattr_d(const vsip_csv_d *svd, vsip_csv_attr_d *attrib)
{
    attrib->Usave = svd->attr.Usave;
    attrib->Vsave = svd->attr.Vsave;
    attrib->m = svd->attr.m;
    attrib->n = svd->attr.n;
}
int
vsip_csvdmatu_d(const vsip_csv_d *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_cmview_d *C)
{
    csvdObj_d *s = (csvdObj_d*) svd->svd;
    sv_attr attr = svd->attr;
    int retval = 0;
    if(attr.Usave){
        if(svd->transpose){
            vsip_cmview_d *L = s->R;
            vsip_cmview_d *Ls = &s->Rs;
            Ls->offset=L->offset + L->col_stride * low;
            Ls->row_stride=L->col_stride; Ls->col_stride=L->row_stride;
            Ls->row_length = (high-low) + 1; Ls->col_length=L->row_length;
            cmconj_d(Ls,C);
        } else {
            vsip_cmview_d *L = s->L;
            vsip_cmview_d *Ls = &s->Ls;
            Ls->offset = L->offset + L->row_stride * low;
            Ls->row_length = (high-low) + 1;
            Ls->row_stride = L->row_stride;
            Ls->col_length = L->col_length;
            Ls->col_stride = L->col_stride;
            cmcopy_d(Ls,C);
        }
    } else {
        retval = 1;
    }
    return retval;
}
int
vsip_csvdmatv_d(const vsip_csv_d *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_cmview_d *C)
{
    csvdObj_d *s = (csvdObj_d*) svd->svd;
    sv_attr attr = svd->attr;
    int retval = 0;
    if(attr.Vsave){
        if(svd->transpose){
            vsip_cmview_d *R  = s->L;
            vsip_cmview_d *Rs = &s->Ls;
            *Rs=*R;
            Rs->offset += Rs->row_stride * low;
            Rs->row_length = (high-low) + 1;
            cmcopy_d(Rs,C);
        } else {
            vsip_cmview_d *R  = s->R;
            vsip_cmview_d *Rs = &s->Rs;
            Rs->offset=R->offset;
            Rs->row_stride=R->col_stride;
            Rs->col_stride=R->row_stride;
            Rs->row_length=R->col_length;
            Rs->col_length=R->row_length;
            Rs->offset += Rs->row_stride * low;
            Rs->row_length = (high-low) + 1;
            cmconj_d(Rs,C);
        }
    } else {
        retval = 1;
    }
    return retval;
}
int
vsip_csvdprodu_d(const vsip_csv_d *svd, vsip_mat_op OpU, vsip_mat_side ApU, const vsip_cmview_d *In)
{
    csvdObj_d* svdObj=(csvdObj_d*)svd->svd;
    vsip_cmview_d c = *In;
    vsip_cmview_d C = *In;
    vsip_index i;
    vsip_cvview_d y;
    vsip_cmview_d U;
    if(svd->attr.Usave == VSIP_SVD_UVNOS) return 1;
    if((OpU != VSIP_MAT_NTRANS) && (OpU != VSIP_MAT_HERM)) return 2;
    if( (ApU != VSIP_MAT_LSIDE) && (ApU != VSIP_MAT_RSIDE)) return 3;
    if(svd->transpose){
        U = *(svdObj->R);
        U.row_stride = svdObj->R->col_stride; U.col_stride=svdObj->R->row_stride;
        U.row_length = svdObj->R->col_length; U.col_length=svdObj->R->row_length;
    } else {
        U = *(svdObj->L);
    }
    /* UVPART and UVFULL operate the same */
    if (ApU == VSIP_MAT_LSIDE){
        if(OpU == VSIP_MAT_NTRANS){
            vsip_cvview_d *x = svdObj->w;
            x->offset=0;x->length=U.col_length;x->stride=1;
            c.col_length=U.col_length;
            for(i=0; i<c.row_length; i++){
                cmvprod_d(&U,ccol_sv_d(&C,&y,i),x);
                cvcopy_d(x,ccol_sv_d(&c,&y,i))
            }
            if(svd->transpose) cmconj_d(&c,&c);
        } else { /* must be HERM */
            vsip_cvview_d *x = svdObj->w;
            vsip_length rl=U.row_length;
            vsip_stride rs=U.row_stride;
            U.row_length = U.col_length;
            U.col_length = rl;
            U.row_stride = U.col_stride;
            U.col_stride = rs;
            x->offset=0;x->length=U.col_length;x->stride=1;
            c.col_length=U.col_length;
            if(svd->transpose){
                U = *(svdObj->R);
                for(i=0; i<c.row_length; i++){
                    cmvprod_d(&U,ccol_sv_d(&C,&y,i),x)
                    cvcopy_d(x,ccol_sv_d(&c,&y,i))
                }
            } else {
                for(i=0; i<c.row_length; i++){
                    cmvjprod_d(&U,ccol_sv_d(&C,&y,i),x)
                    cvcopy_d(x,ccol_sv_d(&c,&y,i))
                }
            }
        }
    } else { /* must be MAT_RSIDE */
        if(OpU == VSIP_MAT_NTRANS){
            vsip_cvview_d *x = svdObj->w;
            x->offset=0;x->length=U.row_length;x->stride=1;
            c.row_length = U.row_length;
            for(i=0; i<c.col_length; i++){
                cvmprod_d(crow_sv_d(&C,&y,i),&U,x);
                cvcopy_d(x,crow_sv_d(&c,&y,i))
            }
            if(svd->transpose) cmconj_d(&c,&c);
        } else {/* must be herm */
            vsip_cvview_d *x = svdObj->w;
            vsip_length rl=U.row_length;
            vsip_stride rs=U.row_stride;
            U.row_length = U.col_length;
            U.col_length = rl;
            U.row_stride = U.col_stride;
            U.col_stride = rs;
            x->offset=0;x->length=U.row_length;x->stride=1;
            c.row_length=U.row_length;
            if(svd->transpose){
                U = *(svdObj->R);
                for(i=0; i<c.row_length; i++){
                    cvmprod_d(crow_sv_d(&C,&y,i),&U,x)
                    cvcopy_d(x,crow_sv_d(&c,&y,i))
                }
            } else {
                for(i=0; i<c.col_length; i++){
                    cvmprodj_d(crow_sv_d(&C,&y,i),&U,x);
                    cvcopy_d(x,crow_sv_d(&c,&y,i))
                }
            }
        }
    }
    return 0;
}
int
vsip_csvdprodv_d(const vsip_csv_d *svd, vsip_mat_op OpV, vsip_mat_side ApV,const vsip_cmview_d *In)
{
    csvdObj_d* svdObj=(csvdObj_d*)svd->svd;
    vsip_cmview_d c = *In;
    vsip_cmview_d C = *In;
    vsip_index i;
    vsip_cvview_d y;
    vsip_cmview_d V;
    if(svd->attr.Vsave == VSIP_SVD_UVNOS) return 1;
    if((OpV != VSIP_MAT_NTRANS) && (OpV != VSIP_MAT_HERM)) return 2;
    if( (ApV != VSIP_MAT_LSIDE) && (ApV != VSIP_MAT_RSIDE)) return 3;
    if(svd->transpose){
        V = *(svdObj->L);
    } else {
        V = *(svdObj->R);
        V.row_stride = svdObj->R->col_stride; V.col_stride=svdObj->R->row_stride;
        V.row_length = svdObj->R->col_length; V.col_length=svdObj->R->row_length;
    }
    /* UVPART and UVFULL operate the same */
    if (ApV == VSIP_MAT_LSIDE){
        if(OpV == VSIP_MAT_NTRANS){
            vsip_cvview_d x = *(svdObj->w);
            x.offset=0;x.length=V.row_length;x.stride=1;
            c.col_length=V.col_length;
            for(i=0; i<c.row_length; i++){
                if(svd->transpose)
                    cmvprod_d(&V,ccol_sv_d(&C,&y,i),&x)
                    else
                        cmvjprod_d(&V,ccol_sv_d(&C,&y,i),&x)
                        cvcopy_d(&x,ccol_sv_d(&c,&y,i))
                        }
        } else { /* must be HERM */
            vsip_cvview_d x = *(svdObj->w);
            if(!svd->transpose) V=*(svdObj->R);
            else {
                vsip_length rl=V.row_length;
                vsip_stride rs=V.row_stride;
                V.row_length = V.col_length;
                V.col_length = rl;
                V.row_stride = V.col_stride;
                V.col_stride = rs;
            }
            x.offset=0;x.length=V.col_length;x.stride=1;
            c.col_length=V.col_length;
            for(i=0; i<c.row_length; i++){
                if(!svd->transpose)
                    cmvprod_d(&V,ccol_sv_d(&C,&y,i),&x)
                    else
                        cmvjprod_d(&V,ccol_sv_d(&C,&y,i),&x)
                        cvcopy_d(&x,ccol_sv_d(&c,&y,i))
                        }
        }
    } else { /* must be MAT_RSIDE */
        if(OpV == VSIP_MAT_NTRANS){
            vsip_cvview_d x = *(svdObj->w);
            x.offset=0;x.length=V.row_length;x.stride=1;
            c.row_length = V.row_length;
            for(i=0; i<c.col_length; i++){
                if(svd->transpose)
                    cvmprod_d(crow_sv_d(&C,&y,i),&V,&x)
                    else
                        cvmprodj_d(crow_sv_d(&C,&y,i),&V,&x)
                        cvcopy_d(&x,crow_sv_d(&c,&y,i))
                        }
        } else { /* must be HERM */
            vsip_cvview_d x = *(svdObj->w);
            if(!svd->transpose) V=*(svdObj->R);
            else {
                vsip_length rl=V.row_length;
                vsip_stride rs=V.row_stride;
                V.row_length = V.col_length;
                V.col_length = rl;
                V.row_stride = V.col_stride;
                V.col_stride = rs;
            }
            x.offset=0;x.length=V.row_length;x.stride=1;
            c.row_length=V.row_length;
            for(i=0; i<c.col_length; i++){
                if(!svd->transpose)
                    cvmprod_d(crow_sv_d(&C,&y,i),&V,&x)
                    else
                        cvmprodj_d(crow_sv_d(&C,&y,i),&V,&x)
                        cvcopy_d(&x,crow_sv_d(&c,&y,i))
                        }
        }
    }
    return 0;
}

