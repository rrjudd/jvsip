//
//  JVVector.swift
//  SJvsipEx
//
//  Created by Randall Judd on 10/12/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import Foundation
import vsip

public class JVVector_d {
    private let vsip: OpaquePointer?
    private let maxLength: Int
    public init(length: Int){
        vsip_init(nil)
        maxLength = length
        vsip = vsip_vcreate_d(vsip_length(length), VSIP_MEM_NONE)
        
    }
    deinit{
        vsip_valldestroy_d(self.vsip)
        vsip_finalize(nil)
    }
    public var length: Int {
        get {
            return Int(vsip_vgetlength_d(self.vsip))
        }
        set(length) {
            precondition(length * self.stride + self.offset <= self.maxLength)
            vsip_vputlength_d(self.vsip, vsip_length(length))
        }
    }
    public var offset: Int {
        get {
            return Int(vsip_vgetoffset_d(self.vsip))
        }
        set(offset) {
            precondition(offset + self.length * self.stride <= self.maxLength+1)
            vsip_vputoffset_d(self.vsip, vsip_offset(offset))
        }
    }
    public var stride: Int {
        get {
            return Int(vsip_vgetstride_d(self.vsip))
        }
        set(stride) {
            precondition(stride * self.length + self.offset <= self.maxLength)
            precondition(stride * self.length + self.offset >= 0)
            vsip_vputstride_d(self.vsip, vsip_stride(stride))
        }
    }
    public subscript(index: Int) -> Double {
        get{
            return Double(vsip_vget_d(self.vsip, vsip_index(index)))
        }
        set(value){
            vsip_vput_d(self.vsip, vsip_index(index), vsip_scalar_d(value))
        }
    }
    public func ramp(start: Double, step: Double) {
        vsip_vramp_d(vsip_scalar_d(start), vsip_scalar_d(step), self.vsip)
    }
}
