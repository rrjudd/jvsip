//
//  scalar.cpp
//  cppJvsip
//
//  Created by RANDALL JUDD on 4/21/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//

#include "scalar.h"
//constructors
jvsip::Scalar::Scalar(float in){
    p="f";
    d="r";
    s="scalar";
    rvalue.re_f=in;
    cvalue.im_f=0.0f;
}
jvsip::Scalar::Scalar(double in){
    p="d";
    d="r";
    s="scalar";
    rvalue.re_d=in;
    cvalue.im_d=0.0;
}
jvsip::Scalar::Scalar(vsip_cscalar_f in){
    p="f";
    d="c";
    s="scalar";
    rvalue.re_f=in.r;
    cvalue.im_f=in.i;
}
jvsip::Scalar::Scalar(vsip_cscalar_d in){
    p="d";
    d="c";
    s="scalar";
    rvalue.re_d=in.r;
    cvalue.im_d=in.i;
}
jvsip::Scalar::Scalar(vsip_scalar_i in){
    p="i";
    d="r";
    s="scalar";
    rvalue.i=in;
}
jvsip::Scalar::Scalar(vsip_scalar_vi in){
    p="vi";
    d="r";
    s="scalar";
    rvalue.vi=in;
}
jvsip::Scalar::Scalar(vsip_stride in){
    p="l";
    d="r";
    s="scalar";
    rvalue.stride=in;
}

//getters
float jvsip::Scalar::scalar_f() const {
    assert (this->depth()=="r");
    if (this->precision()=="f") {
        return this->rvalue.re_f;
    } else if (this->precision()=="d"){
        return (float)this->rvalue.re_d;
    } else if (this->precision()=="i"){
        return (float) this->rvalue.i;
    } else if (this->precision()=="vi"){
        return (float) this->rvalue.vi;
    } else return 0.0f/0.0f;
}
double jvsip::Scalar::scalar_d() const{
    assert (this->depth()=="r");
    if (this->precision()=="f") {
        return (double)this->rvalue.re_f;
    } else if (this->precision()=="d"){
        return (double)this->rvalue.re_d;
    } else if (this->precision()=="i"){
        return (double) this->rvalue.i;
    } else if (this->precision()=="vi"){
        return (double) this->rvalue.vi;
    } else return 0.0f/0.0f;
}
vsip_scalar_i jvsip::Scalar::scalar_i() const{
    assert (this->depth()=="r");
    if (this->precision()=="f") {
        return (vsip_scalar_i)this->rvalue.re_f;
    } else if (this->precision()=="d"){
        return (vsip_scalar_i)this->rvalue.re_d;
    } else if (this->precision()=="i"){
        return (vsip_scalar_i) this->rvalue.i;
    } else if (this->precision()=="vi"){
        return (vsip_scalar_i) this->rvalue.vi;
    } else return 0.0f/0.0f;
}
vsip_scalar_vi jvsip::Scalar::scalar_vi() const{
    assert (this->depth()=="r");
    if (this->precision()=="f") {
        return (vsip_scalar_vi)this->rvalue.re_f;
    } else if (this->precision()=="d"){
        return (vsip_scalar_vi)this->rvalue.re_d;
    } else if (this->precision()=="i"){
        return (vsip_scalar_vi) this->rvalue.i;
    } else if (this->precision()=="vi"){
        return (vsip_scalar_vi) this->rvalue.vi;
    } else return 0.0f/0.0f;
}
vsip_cscalar_f jvsip::Scalar::scalar_cf() const{
    assert(this->depth()=="c");
    float re=0.0,im=0.0;
    if (this->precision()=="f") {
        re=this->rvalue.re_f;im = this->cvalue.im_f;
    }else if (this->precision()=="d"){
        re=(float)this->rvalue.re_d;im = (float)this->cvalue.im_d;
    }
    return vsip_cmplx_f(re, im);
}
vsip_cscalar_d jvsip::Scalar::scalar_cd() const{
    assert(this->depth()=="c");
    double re=0.0,im=0.0;
    if (this->precision()=="f") {
        re= (double)this->rvalue.re_f;im = (double)this->cvalue.im_f;
    }else if (this->precision()=="d"){
        re=this->rvalue.re_d;im = this->cvalue.im_d;
    }
    return vsip_cmplx_d(re, im);
}
vsip_stride jvsip::Scalar::stride() const{
    if (this->precision()=="f") {
        return (vsip_length)this->rvalue.re_f;
    } else if (this->precision()=="d"){
        return (vsip_length)this->rvalue.re_d;
    } else if (this->precision()=="i"){
        return (vsip_length) this->rvalue.i;
    } else if (this->precision()=="vi"){
        return (vsip_length) this->rvalue.vi;
    }else if(this->precision()=="l"){
        return this->rvalue.stride;
    } else return 0.0f/0.0f;
}

std::ostream &operator<<(std::ostream &output, const jvsip::Scalar &in){
    std::string prec = in.precision();
    if(prec=="f") {
        output << in.scalar_f();
    } else if(prec=="d"){
        output << in.scalar_d();
    } else if(prec=="i"){
        output << in.scalar_i();
    } else if(prec=="vi"){
        output << in.scalar_vi();
    } else output << 0.0/0.0;
    return output;
}


