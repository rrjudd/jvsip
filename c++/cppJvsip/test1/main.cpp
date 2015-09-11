//
//  main.cpp
//  test1
//
//  Created by RANDALL JUDD on 4/21/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//

#include <iostream>
#include <cstring>
#include "../jvsiph.h"
extern "C"{
#include<vsip.h>
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    jvsip::Scalar ascalar(50);
    std::cout << ascalar.scalar_i() << std::endl;
    std::cout << jvsip::Scalar(-100l).stride() << std::endl;
    jvsip::Block aBlock("f",100);
    jvsip::View aView(aBlock,0,1,100);
    aView.ramp(jvsip::Scalar(0.0f),jvsip::Scalar(0.5f));
    vsip_vview_f *aVView=(vsip_vview_f*)aView.vsip();
    std::cout << 10 << " : " << aView[10].scalar_f()<< std::endl;
    vsip_vput_f(aVView,10,9.2);
    vsip_svmul_f(2.0, aVView, aVView);
    std::cout << aView[jvsip::Scalar(10)].scalar_f() << std::endl;
    std::cout << 10.0f << " : " << vsip_vget_f((vsip_vview_f*)aView.vsip(),10)<< std::endl;
    for(int i=0; i<aView.length().length(); i++) std::cout << aView[i].scalar_f() << std::endl;
    aView.length(aView.length().length()/3);
    for(int i=0; i<aView.length().length(); i++) std::cout << aView[i].scalar_f() << std::endl;
    aView.offset(jvsip::Scalar(aView.offset().offset()+2));
    for(int i=0; i<aView.length().length(); i++) std::cout << aView[i].scalar_f() << std::endl;
    aView.stride(jvsip::Scalar(2));
    for(int i=0; i<aView.length().length(); i++) std::cout << aView[i].scalar_f() << std::endl;
    return 0;
}
