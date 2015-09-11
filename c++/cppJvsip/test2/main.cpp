//
//  main.cpp
//  test2
//
//  Created by RANDALL JUDD on 4/26/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
extern "C"{
#include <vsip.h>
}
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    assert(!vsip_init((void*)0));
    vsip_vview_f *aView = vsip_vcreate_f(100,VSIP_MEM_NONE);
    vsip_vfill_f(1.2,aView);
    cout << vsip_vget_f(aView, 10) << endl;
    vsip_vramp_f(0,.1,aView);
    for(int i=5; i<10; i++) cout << to_string(vsip_vget_f(aView, i)) << endl;
    vsip_valldestroy_f(aView);
    vsip_finalize((void*)0);
    return 0;
}
