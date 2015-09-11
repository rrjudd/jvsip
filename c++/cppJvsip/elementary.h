//
//  elementary.h
//
//
//  Created by Randall R Judd on 1/28/15.
//
//

#ifndef _elementary_h
#define _elementary_h
#include "support.h"
namespace vsip{
   //add
    vsip_vview_f * add(vsip_vview_f* a,vsip_vview_f* b,vsip_vview_f* c){
        vsip_vadd_f(a,b,c);
        return c;
    }
    vsip_vview_f * add(vsip_vview_f* a,vsip_vview_f* b){
        vsip_vview_f *c;create(&c,vlength(a));
        vsip_vadd_f(a,b,c);
        return c;
    }
    vsip_cvview_f * add(vsip_cvview_f* a,vsip_cvview_f* b,vsip_cvview_f* c){
        vsip_cvadd_f(a,b,c);
        return c;
    }
    vsip_cvview_f * add(vsip_cvview_f* a,vsip_cvview_f* b){
        vsip_cvview_f *c;create(&c,vlength(a));
        vsip_cvadd_f(a,b,c);
        return c;
    }
    vsip_vview_f * add(vsip_scalar_f alpha, vsip_vview_f* b, vsip_vview_f* c){
        vsip_svadd_f(alpha,b,c);
        return c;
    }
    vsip_vview_f * add(vsip_scalar_f alpha, vsip_vview_f* b){
        vsip_vview_f *c;create(&c,vlength(b));
        vsip_svadd_f(alpha,b,c);
        return c;
    }
    vsip_vview_d * add(vsip_vview_d* a,vsip_vview_d* b,vsip_vview_d* c){
        vsip_vadd_d(a,b,c);
        return c;
    }
    vsip_vview_d * add(vsip_vview_d* a,vsip_vview_d* b){
        vsip_vview_d *c;create(&c,vlength(a));
        vsip_vadd_d(a,b,c);
        return c;
    }
    vsip_cvview_d * add(vsip_cvview_d* a,vsip_cvview_d* b,vsip_cvview_d* c){
        vsip_cvadd_d(a,b,c);
        return c;
    }
    vsip_cvview_d * add(vsip_cvview_d* a,vsip_cvview_d* b){
        vsip_cvview_d *c;create(&c,vlength(a));
        vsip_cvadd_d(a,b,c);
        return c;
    }
    vsip_vview_d * add(vsip_scalar_d alpha, vsip_vview_d* b, vsip_vview_d* c){
        vsip_svadd_d(alpha,b,c);
        return c;
    }
    vsip_vview_d * add(vsip_scalar_d alpha, vsip_vview_d* b){
        vsip_vview_d *c;create(&c,vlength(b));
        vsip_svadd_d(alpha,b,c);
        return c;
    }
    //Mull
    vsip_vview_f * mull(vsip_vview_f* a,vsip_vview_f* b,vsip_vview_f* c){
        vsip_vmul_f(a,b,c);
        return c;
    }
    vsip_vview_f * mul(vsip_vview_f* a,vsip_vview_f* b){
        vsip_vview_f *c;create(&c,vlength(a));
        vsip_vmul_f(a,b,c);
        return c;
    }
    vsip_cvview_f * mul(vsip_cvview_f* a,vsip_cvview_f* b,vsip_cvview_f* c){
        vsip_cvmul_f(a,b,c);
        return c;
    }
    vsip_cvview_f * mul(vsip_cvview_f* a,vsip_cvview_f* b){
        vsip_cvview_f *c;create(&c,vlength(a));
        vsip_cvmul_f(a,b,c);
        return c;
    }
    vsip_vview_f * mul(vsip_scalar_f alpha, vsip_vview_f* b, vsip_vview_f* c){
        vsip_svmul_f(alpha,b,c);
        return c;
    }
    vsip_vview_f * mul(vsip_scalar_f alpha, vsip_vview_f* b){
        vsip_vview_f *c;create(&c,vlength(b));
        vsip_svmul_f(alpha,b,c);
        return c;
    }
    vsip_vview_d * mul(vsip_vview_d* a,vsip_vview_d* b,vsip_vview_d* c){
        vsip_vmul_d(a,b,c);
        return c;
    }
    vsip_vview_d * mul(vsip_vview_d* a,vsip_vview_d* b){
        vsip_vview_d *c;create(&c,vlength(a));
        vsip_vmul_d(a,b,c);
        return c;
    }
    vsip_cvview_d * mul(vsip_cvview_d* a,vsip_cvview_d* b,vsip_cvview_d* c){
        vsip_cvmul_d(a,b,c);
        return c;
    }
    vsip_cvview_d * mul(vsip_cvview_d* a,vsip_cvview_d* b){
        vsip_cvview_d *c;create(&c,vlength(a));
        vsip_cvmul_d(a,b,c);
        return c;
    }
    vsip_vview_d * mul(vsip_scalar_d alpha, vsip_vview_d* b, vsip_vview_d* c){
        vsip_svmul_d(alpha,b,c);
        return c;
    }
    vsip_vview_d * mul(vsip_scalar_d alpha, vsip_vview_d* b){
        vsip_vview_d *c;create(&c,vlength(b));
        vsip_svmul_d(alpha,b,c);
        return c;
    }
    //acos
    vsip_vview_f *acos(vsip_vview_f *a, vsip_vview_f *c) {
        vsip_vacos_f(a, c);
        return c;
    }
    vsip_mview_f *acos(vsip_mview_f *a, vsip_mview_f *c){
        vsip_macos_f(a, c);
        return c;
    }
    vsip_vview_d *acos(vsip_vview_d *a, vsip_vview_d *c) {
        vsip_vacos_d(a, c);
        return c;
    }
    vsip_mview_d *acos(vsip_mview_d *a, vsip_mview_d *c){
        vsip_macos_d(a,c);
        return c;
    }
    
    //asin
    vsip_vview_f *asin(vsip_vview_f *a, vsip_vview_f *c) {
        vsip_vacos_f(a, c);
        return c;
    }
    vsip_mview_f *asin(vsip_mview_f *a, vsip_mview_f *c){
        vsip_masin_f(a, c);
        return c;
    }
    vsip_vview_d *asin(vsip_vview_d *a, vsip_vview_d *c) {
        vsip_vasin_d(a, c);
        return c;
    }
    vsip_mview_d *asin(vsip_mview_d *a, vsip_mview_d *c){
        vsip_masin_d(a,c);
        return c;
    }
    //cos
    vsip_vview_f *cos(vsip_vview_f *a, vsip_vview_f *c) {
        vsip_vacos_f(a, c);
        return c;
    }
    vsip_mview_f *cos(vsip_mview_f *a, vsip_mview_f *c){
        vsip_mcos_f(a, c);
        return c;
    }
    vsip_vview_d *cos(vsip_vview_d *a, vsip_vview_d *c) {
        vsip_vcos_d(a, c);
        return c;
    }
    vsip_mview_d *cos(vsip_mview_d *a, vsip_mview_d *c){
        vsip_mcos_d(a,c);
        return c;
    }
    //sin
    vsip_vview_f *sin(vsip_vview_f *a, vsip_vview_f *c) {
        vsip_vacos_f(a, c);
        return c;
    }
    vsip_mview_f *sin(vsip_mview_f *a, vsip_mview_f *c){
        vsip_msin_f(a, c);
        return c;
    }
    vsip_vview_d *sin(vsip_vview_d *a, vsip_vview_d *c) {
        vsip_vsin_d(a, c);
        return c;
    }
    vsip_mview_d *sin(vsip_mview_d *a, vsip_mview_d *c){
        vsip_msin_d(a,c);
        return c;
    }
    //exp
    vsip_vview_f *exp(vsip_vview_f *a, vsip_vview_f *c) {
        vsip_vexp_f(a, c);
        return c;
    }
    vsip_mview_f *exp(vsip_mview_f *a, vsip_mview_f *c){
        vsip_mexp_f(a, c);
        return c;
    }
    vsip_vview_d *exp(vsip_vview_d *a, vsip_vview_d *c) {
        vsip_vexp_d(a, c);
        return c;
    }
    vsip_mview_d *exp(vsip_mview_d *a, vsip_mview_d *c){
        vsip_mexp_d(a,c);
        return c;
    }
    vsip_cvview_f *exp(vsip_cvview_f *a, vsip_cvview_f *c) {
        vsip_cvexp_f(a, c);
        return c;
    }
    vsip_cmview_f *exp(vsip_cmview_f *a, vsip_cmview_f *c){
        vsip_cmexp_f(a, c);
        return c;
    }
    vsip_cvview_d *exp(vsip_cvview_d *a, vsip_cvview_d *c) {
        vsip_cvexp_d(a, c);
        return c;
    }
    vsip_cmview_d *exp(vsip_cmview_d *a, vsip_cmview_d *c){
        vsip_cmexp_d(a,c);
        return c;
    }

}
#endif
