//
//  main.swift
//  vsipExampleAdd
//
//  Created by Randall Judd on 10/5/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import Foundation
import vsip
print("Hello, World!")

let jvsipInit = vsip_init(nil)
let v = vsip_vcreate_d(10,VSIP_MEM_NONE)
vsip_vramp_d(0.0,0.1,v)
for i in 0..<vsip_vgetlength_d(v){
    print(vsip_vget_d(v,i))
}
vsip_valldestroy_d(v)
let jvsipFin = vsip_finalize(nil)
