//
//  main.swift
//  vsipExampleAdd
//
//  Created by Randall Judd on 10/5/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import Foundation
import vsip
let N = vsip_length(500)
let _ = vsip_init(nil)
let m = vsip_cmcreate_d(N, N, VSIP_ROW, VSIP_MEM_NONE)
let rnd = vsip_randcreate(8,1,1,VSIP_PRNG)
let svd = vsip_csvd_create_d(N, N, VSIP_SVD_UVFULL, VSIP_SVD_UVFULL)
let s = vsip_vcreate_d(N,VSIP_MEM_NONE)
vsip_cmrandn_d(rnd,m)
vsip_csvd_d(svd,m,s)
for i in 0..<N{
    print("i:\(i) -> \(vsip_vget_d(s,i))")
}
vsip_cmalldestroy_d(m)
vsip_csvd_destroy_d(svd)
vsip_valldestroy_d(s)
vsip_randdestroy(rnd)
let _ = vsip_finalize(nil)
