//
//  modulateEx.swift
//  vsip
//
//  Created by Randall R. Judd on 4/20/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
func modulate_cd(length: vsip_length) {
    let _ = vsip_init(nil)
    let vo = vsip_cvcreate_d(length, VSIP_MEM_NONE)
    let vin = vsip_vcreate_d(length, VSIP_MEM_NONE)
    let rnd = vsip_randcreate(8, 1, 1, VSIP_PRNG)
    vsip_vrandn_d(rnd,vin)
    vsip_vmodulate_d(vin, Double.pi/3.0, Double.pi/10.0, vo)
    for i in 0..<length {
        let x = vsip_cvget_d(vo,i)
        print("\(x.r) + \(x.i)i")
    }
    vsip_valldestroy_d(vin)
    vsip_cvalldestroy_d(vo)
    vsip_randdestroy(rnd)
    let _ = vsip_finalize(nil)
}
