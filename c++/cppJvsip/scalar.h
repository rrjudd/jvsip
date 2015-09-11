//
//  scalar.h
//  cppJvsip
//
//  Created by RANDALL JUDD on 4/21/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//

#ifndef __cppJvsip__scalar__
#define __cppJvsip__scalar__
#include <cstring>
#include <iostream>
#include <cassert>
extern "C"{
#include<vsip.h>
}
namespace jvsip {
    using std::string;
    class Scalar{
        friend std::ostream &operator<<(std::ostream &, const Scalar &);
    private:
         string p; //precision
         string d; //depth
         string s; //shape
        union {
            float re_f;
            double re_d;
            vsip_scalar_i i;
            vsip_scalar_vi vi;
            vsip_stride stride;
        } rvalue;
        union {
            float im_f;
            double im_d;
        } cvalue;
    public:
        Scalar(float);
        Scalar(double);
        Scalar(vsip_cscalar_f);
        Scalar(vsip_cscalar_d);
        Scalar(vsip_scalar_i);
        Scalar(vsip_scalar_vi);
        Scalar(vsip_stride);
        //copy constructor
        Scalar(const Scalar& other) : p(other.p),s(other.s),d(other.d){
            if(p=="f"){
                rvalue.re_f=other.scalar_f();
                cvalue.im_f=0.0f;
            } else if (p=="d"){
                rvalue.re_d=other.scalar_d();
                cvalue.im_d=0.0;
            } else if (p=="i"){
                rvalue.i=other.scalar_i();
            } else{
                rvalue.vi=other.scalar_vi();
            }
        }
        ~Scalar(){}
        string precision() const{
            return p;
        }
        string depth() const{
            return d;
        }
        string shape() const{
            return s;
        }
        float scalar_f() const;
        double scalar_d() const;
        vsip_cscalar_f scalar_cf() const;
        vsip_cscalar_d scalar_cd() const;
        vsip_scalar_i scalar_i() const;
        vsip_scalar_vi scalar_vi() const;
        vsip_stride stride() const;
        vsip_length length() const { return scalar_vi();}
        vsip_offset offset() const { return scalar_vi();}
    };
}

#endif /* defined(__cppJvsip__scalar__) */
