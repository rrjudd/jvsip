//
//  jofkTest.swift
//  vsip
//
//  Created by Randall R. Judd on 6/10/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
public func jofk(){
    let _ = vsip_init(nil)
    let N = 8 * 3 * 3 * 7
    let fft = vsip_ccfftop_create_d(vsip_scalar_vi(N),1.0,VSIP_FFT_FWD,1,VSIP_ALG_TIME)
    let _ = vsip_finalize(nil)
}
