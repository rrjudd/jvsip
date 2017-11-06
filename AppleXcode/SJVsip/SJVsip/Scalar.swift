//
//  Scalar.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
public struct Scalar {
    public enum Types: String{
        case f
        case d
        case cf
        case cd
        case si
        case i
        case li
        case uc
        case vi
        case mi
        case bl
    }
    var value: (Types?, NSNumber?,  NSNumber?)
    public init(_ type: Types,_ valueOne: NSNumber?,_ valueTwo: NSNumber?){
        value.0 = type
        value.1 = valueOne
        value.2 = valueTwo
    }
    public init(_ value: Double){
        self.value.0 = .d
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: Float){
        self.value.0 = .f
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: Int){
        self.value.0 = .i
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: vsip_cscalar_d){
        self.value.0 = .cd
        self.value.1 = NSNumber(value: value.r)
        self.value.2 = NSNumber(value: value.i)
    }
    public init(_ value: vsip_cscalar_f){
        self.value.0 = .cf
        self.value.1 = NSNumber(value: value.r)
        self.value.2 = NSNumber(value: value.i)
    }
    public init(_ value: vsip_scalar_mi){
        self.value.0 = .mi
        self.value.1 = NSNumber(value: value.r)
        self.value.2 = NSNumber(value: value.c)
    }
    public init(_ value: vsip_scalar_i){
        self.value.0 = .i
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: vsip_scalar_vi){
        self.value.0 = .vi
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: vsip_scalar_si){
        self.value.0 = .si
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: vsip_scalar_uc){
        self.value.0 = .uc
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public var type: Types {
        return value.0!
    }
    public var realf: Float{
        return Float((value.1?.floatValue)!)
    }
    public var reald: Double{
        return Double((value.1?.doubleValue)!)
    }
    public var imagf: Float{
        if let i = value.2 {
            return i.floatValue
        } else {
            return Float(0.0)
        }
    }
    public var imagd: Double{
        if let i = value.2 {
            return i.doubleValue
        } else {
            return Double(0.0)
        }
    }
    public var int: Int{
        return Int((value.1?.intValue)!)
    }
    public var row: Int{
        return Int((value.1?.intValue)!)
    }
    public var col: Int{
        return Int((value.2?.intValue)!)
    }
    public var cmplxf: Scalar{
        var c = vsip_cmplx_f(vsip_scalar_f(0.0),(0.0))
        if let r = value.1 {
            c.r = vsip_scalar_f(r.floatValue)
        }
        if let i = value.2 {
            c.i = vsip_scalar_f(i.floatValue)
        }
        return Scalar(c)
    }
    public var cmplxd: Scalar{
        var c = vsip_cmplx_d(vsip_scalar_d(0.0),vsip_scalar_d(0.0))
        if let r = value.1 {
            c.r = vsip_scalar_d(r.doubleValue)
        }
        if let i = value.2 {
            c.i = vsip_scalar_d(i.doubleValue)
        }
        return Scalar(c)
    }
    public var vsip_f: vsip_scalar_f {
        return vsip_scalar_f((value.1?.floatValue)!)
    }
    public var vsip_d: vsip_scalar_d {
        return vsip_scalar_d((value.1?.doubleValue)!)
    }
    public var vsip_cf: vsip_cscalar_f {
        var c = vsip_cmplx_f(vsip_scalar_f(0.0),vsip_scalar_f(0.0))
        if let r = value.1 {
            c.r = vsip_scalar_f(r.floatValue)
        }
        if let i = value.2 {
            c.i = vsip_scalar_f(i.floatValue)
        }
        return c
    }
    public var vsip_cd: vsip_cscalar_d {
        var c = vsip_cmplx_d(vsip_scalar_d(0.0),vsip_scalar_d(0.0))
        if let r = value.1 {
            c.r = vsip_scalar_d(r.doubleValue)
        }
        if let i = value.2 {
            c.i = vsip_scalar_d(i.doubleValue)
        }
        return c
    }
    public var vsip_i: vsip_scalar_i{
        return vsip_scalar_i((value.1?.int32Value)!)
    }
    public var vsip_li: vsip_scalar_li{
        return vsip_scalar_li((value.1?.intValue)!)
    }
    public var vsip_vi: vsip_scalar_vi{
        return vsip_scalar_vi((value.1?.uintValue)!)
    }
    public var vsip_si: vsip_scalar_si{
        return vsip_scalar_si((value.1?.int16Value)!)
    }
    public var vsip_uc: vsip_scalar_uc{
        return vsip_scalar_uc((value.1?.uint8Value)!)
    }
    public var vsip_mi: vsip_scalar_mi{
        var i = vsip_matindex(vsip_scalar_vi(0), vsip_scalar_vi(0))
        if let row = value.1 {
            i.r = vsip_scalar_vi(row.uintValue)
        }
        if let col = value.2 {
            i.c = vsip_scalar_vi(col.uintValue)
        }
        return i
    }
    
    public static func + (left: Scalar, right: Scalar) -> Scalar {
        switch (left.type, right.type) {
        case (.f, .f):
            return Scalar( left.realf + right.realf)
        case (.d, .d):
            return Scalar( left.reald + right.reald)
        case (.cf, .f):
            return Scalar(vsip_cmplx_f(left.realf + right.realf, left.imagf))
        case (.cd, .d):
            return Scalar(vsip_cmplx_d(left.reald + right.reald, left.imagd))
        case (.f, .cf):
            return Scalar(vsip_cmplx_f(left.realf + right.realf, right.imagf))
        case (.d, .cd):
            return Scalar(vsip_cmplx_d(left.reald + right.reald, right.imagd))
        case(.cf, .cf):
            return Scalar(vsip_cmplx_f(left.realf + right.realf, left.imagf + right.imagf))
        case(.cd, .cd):
            return Scalar(vsip_cmplx_d(left.reald + right.reald, left.imagd + right.imagd))
        default:
            preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for +")
        }
    }
    public static func * (left: Scalar, right: Scalar) -> Scalar {
        switch (left.type, right.type) {
        case (.f, .f):
            return Scalar( left.realf * right.realf)
        case (.d, .d):
            return Scalar( left.reald * right.reald)
        case (.cf, .f):
            return Scalar(vsip_rcmul_f(right.vsip_f, left.vsip_cf))
        case (.cd, .d):
            return Scalar(vsip_rcmul_d(right.vsip_d, left.vsip_cd))
        case (.f, .cf):
            return Scalar(vsip_rcmul_f(left.vsip_f, right.vsip_cf))
        case (.d, .cd):
            return Scalar(vsip_rcmul_d(left.vsip_d, right.vsip_cd))
        case(.cf, .cf):
            return Scalar(vsip_cmul_f(left.vsip_cf, right.vsip_cf))
        case(.cd, .cd):
            return Scalar(vsip_cmul_d(left.vsip_cd, right.vsip_cd))
        default:
            preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for *")
        }
    }
    public static func - (left: Scalar, right: Scalar) -> Scalar {
        switch (left.type, right.type) {
        case (.f, .f):
            return Scalar( left.realf - right.realf)
        case (.d, .d):
            return Scalar( left.reald - right.reald)
        case (.cf, .f):
            return Scalar(vsip_cmplx_f(left.realf - right.realf, left.imagf))
        case (.cd, .d):
            return Scalar(vsip_cmplx_d(left.reald - right.reald, left.imagd))
        case (.f, .cf):
            return Scalar(vsip_cmplx_f(left.realf - right.realf, -right.imagf))
        case (.d, .cd):
            return Scalar(vsip_cmplx_d(left.reald - right.reald, -right.imagd))
        case(.cf, .cf):
            return Scalar(vsip_cmplx_f(left.realf - right.realf, left.imagf - right.imagf))
        case(.cd, .cd):
            return Scalar(vsip_cmplx_d(left.reald - right.reald, left.imagd - right.imagd))
        case(.f, .i):
            return Scalar( left.realf - right.realf)
        case(.i, .f):
            return Scalar( left.realf - right.realf)
        case(.d, .i):
            return Scalar( left.reald - right.reald)
        case(.i, .d):
            return Scalar( left.reald - right.reald)
        default:
            preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for - ")
        }
    }
    public var sqrt: Scalar {
        switch self.type {
        case .f:
            return Scalar(sqrtf(self.realf))
        case .d:
            let x = Foundation.sqrt(self.reald)
            return Scalar(x)
        case .cf:
            return Scalar(vsip_csqrt_f(self.vsip_cf))
        case .cd:
            return Scalar(vsip_csqrt_d(self.vsip_cd))
        default:
            preconditionFailure("sqrt not supported for type \(self.type)")
        }
    }
    public func string(format fmt: String) -> String {
        return scalarString(formatFmt(fmt), value:self)
    }
}

