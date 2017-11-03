//
//  meansqvalEx.swift
//  vsip
//
//  Created by Randall R. Judd on 4/19/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
func meansqvalEx_cd(length: vsip_length) {
    let _ = vsip_init(nil)
    let v = vsip_cvcreate_d(length, VSIP_MEM_NONE)
    let vr = vsip_vrealview_d(v)
    let vi = vsip_vimagview_d(v)
    vsip_vramp_d(0.1,0.2,vr)
    vsip_vramp_d(0.5, -0.2, vi)
    print(vsip_cvmeansqval_d(v))
    vsip_vdestroy_d(vr); vsip_vdestroy_d(vi);
    vsip_cvalldestroy_d(v)
    let _ = vsip_finalize(nil)
}
func meansqvalEx_cd(rows: vsip_length, cols: vsip_length) {
    let _ = vsip_init(nil)
    let length = rows * cols
    let m = vsip_cmcreate_d(rows, cols, VSIP_ROW, VSIP_MEM_NONE)
    let mr = vsip_mrealview_d(m)
    let mi = vsip_mimagview_d(m)
    let vr = vsip_vbind_d(vsip_vgetblock_d(mr),0,1,length)
    let vi = vsip_vbind_d(vsip_vgetblock_d(mi),0,1,length)
    vsip_vramp_d(0.1,0.2,vr)
    vsip_vramp_d(0.5, -0.2, vi)
    print(vsip_cmmeansqval_d(m))
    vsip_vdestroy_d(vr); vsip_vdestroy_d(vi);
    vsip_mdestroy_d(mr); vsip_mdestroy_d(mi);
    vsip_cmalldestroy_d(m)
    let _ = vsip_finalize(nil)
}
