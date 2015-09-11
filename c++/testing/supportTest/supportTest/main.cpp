//
//  main.cpp
//  supportTest
//
//  Created by RANDALL JUDD on 4/20/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//

#include <iostream>
#include <jvsiph.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    jvsip::view aView("f",10);
    aView.ramp(.1f, .2f);
    jvsip::scalar aScalar(100.0f);
    return 0;
}
