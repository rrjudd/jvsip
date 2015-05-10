//
//  elementary.h
//
//
//  Created by Randall R Judd on 1/28/15.
//
//

#ifndef _elementary_h
#define _elementary_h
extern "C"{
#include<vsip.h>
}
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
    //add
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

}
#endif
