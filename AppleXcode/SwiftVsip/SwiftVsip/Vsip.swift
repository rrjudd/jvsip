//
//  Elementwise.swift
//  SwiftVsip
//
//  Created by Randall Judd on 9/3/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip

public class Vsip {
    fileprivate static func sizeEqual(_ check: Vector, against: Vector) -> Bool{
        return check.length == against.length
    }
    fileprivate static func sizeEqual(_ check: Matrix, against: Matrix) -> Bool{
        return (check.rowLength == against.rowLength && check.columnLength == against.columnLength)
    }
    // MARK: - Scalar
    public struct Scalar {
        var value: (Block.Types?, NSNumber?,  NSNumber?)
        public init(_ type: Block.Types,_ valueOne: NSNumber?,_ valueTwo: NSNumber?){
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
        var realf: vsip_scalar_f{
            return vsip_scalar_f((value.1?.floatValue)!)
        }
        var reald: vsip_scalar_d{
            return vsip_scalar_d((value.1?.doubleValue)!)
        }
        var cmplxf: vsip_cscalar_f{
            var c = vsip_cmplx_f(vsip_scalar_f(0.0),(0.0))
            if let r = value.1 {
                c.r = vsip_scalar_f(r.floatValue)
            }
            if let i = value.2 {
                c.i = vsip_scalar_f(i.floatValue)
            }
            return c
        }
        var cmplxd: vsip_cscalar_d{
            var c = vsip_cmplx_d(vsip_scalar_d(0.0),vsip_scalar_d(0.0))
            if let r = value.1 {
                c.r = vsip_scalar_d(r.floatValue)
            }
            if let i = value.2 {
                c.i = vsip_scalar_d(i.floatValue)
            }
            return c
        }
    }
    // MARK:  - Elementary Math Functions
    public static func acos(_ input: Vector, output: Vector) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_vacos_f(input.vsip!, output.vsip!)
        case (.d, .d):
            vsip_vacos_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for this type vector")
        }
    }
    public static func acos(_ input: Matrix, output: Matrix) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_macos_f(input.vsip!, output.vsip!)
        case (.d, .d):
            vsip_macos_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for this type vector")
        }
    }
    public static func asin(_ input: Vector, output: Vector) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_vasin_f(input.vsip!, output.vsip!)
        case (.d, .d):
            vsip_vasin_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for this type vector")
        }
    }
    public static func asin(_ input: Matrix, output: Matrix) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_masin_f(input.vsip!, output.vsip!)
        case (.d, .d):
            vsip_masin_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for this type vector")
        }
    }
    public static func atan(_ input: Vector, output: Vector) {
        assert(sizeEqual(input, against: output), "View sizes must be the same")
        switch input.type {
        case .f:
            vsip_vatan_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vatan_d(input.vsip!, output.vsip!)
        default:
            precondition(true, "function not supported for this type vector")
            break
        }
    }
    public static func atan(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_matan_f(input.vsip!, output.vsip!)
        case .d:
            vsip_matan_d(input.vsip!, output.vsip!)
        default:
            precondition(true, "function not supported for this type matrix")
            break
        }
    }
    public static func atan2(_ numerator: Vector, denominator: Vector, output: Vector) {
        let tn = numerator.type
        let td = denominator.type
        let to = output.type
        assert(tn == td && tn == to, "View types must agree")
        assert(sizeEqual(numerator, against: denominator) && sizeEqual(numerator, against: output), "View sizes musta be equal")
        switch tn{
        case .f:
            vsip_vatan2_f(numerator.vsip!,denominator.vsip!,output.vsip!)
        case .d:
            vsip_vatan2_d(numerator.vsip!,denominator.vsip!,output.vsip!)
        default:
            precondition(false, "function not supported for this type matrix")
            break
        }
        
    }
    public static func atan2(_ numerator: Matrix, denominator: Matrix, output: Matrix) {
        let tn = numerator.type
        let td = denominator.type
        let to = output.type
        assert(tn == td && tn == to, "input types must be the same")
        assert(sizeEqual(numerator, against: denominator) && sizeEqual(numerator, against: output), "View sizes musta be equal")
        switch tn {
        case .f:
            vsip_matan2_f(numerator.vsip!,denominator.vsip!,output.vsip!)
        case .d:
            vsip_matan2_d(numerator.vsip!,denominator.vsip!,output.vsip!)
        default:
            precondition(false, "function not supported for this type matrix")
            break
        }
        
    }
    public static func cos(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vcos_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vcos_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func cos(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mcos_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mcos_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func cosh(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vcosh_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vcosh_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func cosh(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mcosh_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mcosh_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func sin(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vsin_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vsin_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func sin(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_msin_f(input.vsip!, output.vsip!)
        case .d:
            vsip_msin_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func sinh(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vsinh_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vsinh_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func sinh(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_msinh_f(input.vsip!, output.vsip!)
        case .d:
            vsip_msinh_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func exp(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vexp_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vexp_d(input.vsip!, output.vsip!)
        case .cf:
            vsip_cvexp_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cvexp_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func exp(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mexp_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mexp_d(input.vsip!, output.vsip!)
        case .cf:
            vsip_cmexp_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cmexp_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func exp10(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vexp10_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vexp10_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func exp10(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mexp10_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mexp10_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func log(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vlog_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vlog_d(input.vsip!, output.vsip!)
        case .cf:
            vsip_cvlog_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cvlog_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func log(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mlog_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mlog_d(input.vsip!, output.vsip!)
        case .cf:
            vsip_cmlog_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cmlog_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func log10(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vlog10_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vlog10_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func log10(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mlog10_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mlog10_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func sqrt(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vsqrt_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vsqrt_d(input.vsip!, output.vsip!)
        case .cf:
            vsip_cvsqrt_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cvsqrt_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func sqrt(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_msqrt_f(input.vsip!, output.vsip!)
        case .d:
            vsip_msqrt_d(input.vsip!, output.vsip!)
        case .cf:
            vsip_cmsqrt_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cmsqrt_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func tan(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vtan_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vtan_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func tan(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mtan_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mtan_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func tanh(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vtanh_f(input.vsip!, output.vsip!)
        case .d:
            vsip_vtanh_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func tanh(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mtanh_f(input.vsip!, output.vsip!)
        case .d:
            vsip_mtanh_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    
    // MARK: - Unary Functions
    public static func arg(_ input: Vector, output: Vector) {
        let type = (input.type, output.type)
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch type {
        case (.cf, .f):
            vsip_varg_f(input.vsip!, output.vsip!)
        case (.cd, .d):
            vsip_varg_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for input/output views")
        }
    }
    public static func arg(_ input: Matrix, output: Matrix) {
        let type = (input.type, output.type)
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch type {
        case (.cf, .f):
            vsip_marg_f(input.vsip!, output.vsip!)
        case (.cd, .d):
            vsip_marg_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for input/output views")
        }
    }
    public static func ceil(_ input: Vector, output: Vector){
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch (input.type, output.type) {
        case (.d, .d):
            vsip_vceil_d_d(input.vsip!, output.vsip!)
        case (.d,.i):
            vsip_vceil_d_i(input.vsip!, output.vsip!)
        case (.f, .f):
            vsip_vceil_f_f(input.vsip!, output.vsip!)
        case (.f,.i):
            vsip_vceil_f_i(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for input/output views")
            break
        }
    }
    public static func ceil(_ input: Matrix, output: Matrix){
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch (input.type, output.type) {
        case (.d, .d):
            vsip_mceil_d_d(input.vsip!, output.vsip!)
        case (.d,.i):
            vsip_mceil_d_i(input.vsip!, output.vsip!)
        case (.f, .f):
            vsip_mceil_f_f(input.vsip!, output.vsip!)
        case (.f,.i):
            vsip_mceil_f_i(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported for input/output views")
            break
        }
        
    }
    public static func conj(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .cf:
            vsip_cvconj_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cvconj_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func conj(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .cf:
            vsip_cmconj_f(input.vsip!, output.vsip!)
        case .cd:
            vsip_cmconj_d(input.vsip!, output.vsip!)
        default:
            precondition(false, "function not supported")
            break
        }
    }
    public static func neg(_ input: Vector, output: Vector){
        assert(sizeEqual(input, against: output), "View size of input an output must be equal for neg")
        assert(input.type == output.type, "View types of input and output must be the same for neg")
        switch input.type {
        case .f:
            vsip_vneg_f(input.vsip!,output.vsip!)
        case .d:
            vsip_vneg_d(input.vsip!,output.vsip!)
        case .cf:
            vsip_cvneg_f(input.vsip!,output.vsip!)
        case .cd:
            vsip_cvneg_d(input.vsip!,output.vsip!)
        case .i:
            vsip_vneg_i(input.vsip!,output.vsip!)
        case .li:
            vsip_vneg_li(input.vsip!,output.vsip!)
        case .vi:
            vsip_vneg_si(input.vsip!,output.vsip!)
        default:
            assert(false, "type not found for neg")
            break
        }
        
    }
    public static func neg(_ input: Matrix, output: Matrix){
        assert(sizeEqual(input, against: output), "View size of input an output must be equal for neg")
        assert(input.type == output.type, "View types of input and output must be the same for neg")
        switch input.type {
        case .f:
            vsip_mneg_f(input.vsip!,output.vsip!)
        case .d:
            vsip_mneg_d(input.vsip!,output.vsip!)
        case .cf:
            vsip_cmneg_f(input.vsip!,output.vsip!)
        case .cd:
            vsip_cmneg_d(input.vsip!,output.vsip!)
        default:
            assert(false, "type not found for neg")
            break
        }
        
    }
    public static func sumval(_ input: Vector) -> (Block.Types?, NSNumber?, NSNumber?){
        switch input.type {
        case .d:
            return (.d, NSNumber(value: vsip_vsumval_d(input.vsip!) as Double), nil)
        case .f:
            return (.f, NSNumber(value: vsip_vsumval_f(input.vsip!) as Float), nil)
        case .cd:
            let ans = vsip_cvsumval_d(input.vsip!)
            return (.cd, NSNumber(value: ans.r as Double), NSNumber(value: ans.i as Double))
        case .cf:
            let ans = vsip_cvsumval_f(input.vsip!)
            return (.cf, NSNumber(value: ans.r as Float), NSNumber(value: ans.i as Float))
        case .i:
            return (.i, NSNumber(value: vsip_vsumval_i(input.vsip!) as Int32), nil)
        case .bl:
            return (.vi, NSNumber(value: vsip_vsumval_bl(input.vsip!) as UInt), nil)
        default:
            precondition(false, "sumval not supported for this type")
            break
        }
    }
    public static func sumval(_ input: Matrix) -> (Block.Types?, NSNumber?, NSNumber?){
        switch input.type {
        case .d:
            return (.d, NSNumber(value: vsip_msumval_d(input.vsip!) as Double), nil)
        case .f:
            return (.f, NSNumber(value: vsip_msumval_f(input.vsip!) as Float), nil)
        case .cd:
            let ans = vsip_cmsumval_d(input.vsip!)
            return (.cd, NSNumber(value: ans.r as Double), NSNumber(value: ans.i as Double))
        case .cf:
            let ans = vsip_cmsumval_f(input.vsip!)
            return (.cf, NSNumber(value: ans.r as Float), NSNumber(value: ans.i as Float))
        case .bl:
            return (.vi, NSNumber(value: vsip_msumval_bl(input.vsip!) as UInt), nil)
        default:
            precondition(false, "sumval not supported for this type")
            break
        }
    }
    
    // MARK: - Binary Functions
    public static func add(_ one: Vector, to: Vector, resultsIn: Vector) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        assert(to.type == resultsIn.type, "Output view type not compliant with input")
        switch one.type {
        case .f:
            switch to.type{
            case .f:
                vsip_vadd_f(one.vsip!, to.vsip!, resultsIn.vsip!)
            case .cf:
                vsip_rcvadd_f(one.vsip!, to.vsip!, resultsIn.vsip!)
            default:
                break
            }
        case .d:
            switch to.type{
            case .d:
                vsip_vadd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
            case .cd:
                vsip_rcvadd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
            default:
                break
            }
        case .cf:
            vsip_cvadd_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .cd:
            vsip_cvadd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .i:
            vsip_vadd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .li:
            vsip_vadd_li(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .uc:
            vsip_vadd_li(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .si:
            vsip_vadd_si(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .vi:
            vsip_vadd_vi(one.vsip!, to.vsip!, resultsIn.vsip!)
        default:
            precondition(false, "View type not supported")
            break
        }
        
    }
    public static func add(_ one: Matrix, to: Matrix, resultsIn: Matrix) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        assert(to.type == resultsIn.type, "Output view type not compliant with input")
        switch one.type {
        case .f:
            switch to.type{
            case .f:
                vsip_madd_f(one.vsip!, to.vsip!, resultsIn.vsip!)
            case .cf:
                vsip_rcmadd_f(one.vsip!, to.vsip!, resultsIn.vsip!)
            default:
                break
            }
        case .d:
            switch to.type{
            case .d:
                vsip_madd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
            case .cd:
                vsip_rcmadd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
            default:
                break
            }
        case .cf:
            vsip_cmadd_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .cd:
            vsip_cmadd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .i:
            vsip_madd_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .li:
            vsip_madd_li(one.vsip!, to.vsip!, resultsIn.vsip!)
        case .si:
            vsip_madd_si(one.vsip!, to.vsip!, resultsIn.vsip!)
        default:
            precondition(false, "View type not supported")
            break
        }
    }
    public static func add(_ aScalar: Double, toAVector: Vector, resultIn: Vector){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.d, aScalar as NSNumber?, nil)
        Vsip.add(aNumber, toAVector: toAVector, resultIn: resultIn)
        
    }
    public static func add(_ aScalar: Float, toAVector: Vector, resultIn: Vector){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.f, aScalar as NSNumber?, nil)
        Vsip.add(aNumber, toAVector: toAVector, resultIn: resultIn)
    }
    public static func add(_ aScalar: Int, toAVector: Vector, resultIn: Vector){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.i, aScalar as NSNumber?, nil)
        Vsip.add(aNumber, toAVector: toAVector, resultIn: resultIn)
    }
    public static func add(_ aScalar: (Block.Types?, NSNumber?, NSNumber?), toAVector: Vector, resultIn: Vector){
        assert(toAVector.type == resultIn.type, "View types must agrees")
        let t = toAVector.type
        switch t {
        case .f:
            vsip_svadd_f((aScalar.1?.floatValue)!, toAVector.vsip!, resultIn.vsip!)
        case .d:
            vsip_svadd_d((aScalar.1?.doubleValue)!, toAVector.vsip!, resultIn.vsip!)
        case .cf:
            switch aScalar.0!{
            case .f:
                vsip_rscvadd_f((aScalar.1?.floatValue)!, toAVector.vsip!, resultIn.vsip!)
            case .d:
                vsip_rscvadd_f((aScalar.1?.floatValue)!, toAVector.vsip!, resultIn.vsip!)
            case .cf:
                let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
                vsip_csvadd_f(aNumber, toAVector.vsip!, resultIn.vsip!)
            case .cd:
                let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
                vsip_csvadd_f(aNumber, toAVector.vsip!, resultIn.vsip!)
            default:
                break
            }
        case .cd:
            switch aScalar.0!{
            case .f:
                vsip_rscvadd_d((aScalar.1?.doubleValue)!, toAVector.vsip!, resultIn.vsip!)
            case .d:
                vsip_rscvadd_d((aScalar.1?.doubleValue)!, toAVector.vsip!, resultIn.vsip!)
            case .cf:
                let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
                vsip_csvadd_d(aNumber, toAVector.vsip!, resultIn.vsip!)
            case .cd:
                let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
                vsip_csvadd_d(aNumber, toAVector.vsip!, resultIn.vsip!)
            default:
                break
            }
        case .i:
            vsip_svadd_i((aScalar.1?.int32Value)!, toAVector.vsip!, resultIn.vsip!)
        case .li:
            vsip_svadd_li((aScalar.1?.intValue)!, toAVector.vsip!, resultIn.vsip!)
        case .si:
            vsip_svadd_si((aScalar.1?.int16Value)!, toAVector.vsip!, resultIn.vsip!)
        case .uc:
            vsip_svadd_uc((aScalar.1?.uint8Value)!, toAVector.vsip!, resultIn.vsip!)
        case .vi:
            vsip_svadd_vi((aScalar.1?.uintValue)!, toAVector.vsip!, resultIn.vsip!)
        default:
            precondition(false, "Argument string not supported for svadd")
        }
        
    }
    public static func add(_ aScalar: Double, toAMatrix: Matrix, resultIn: Matrix){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.d, aScalar as NSNumber?, nil)
        Vsip.add(aNumber, toAMatrix: toAMatrix, resultIn: resultIn)
        
    }
    public static func add(_ aScalar: Float, toAMatrix: Matrix, resultIn: Matrix){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.f, aScalar as NSNumber?, nil)
        Vsip.add(aNumber, toAMatrix: toAMatrix, resultIn: resultIn)
    }
    public static func add(_ aScalar: (Block.Types?, NSNumber?, NSNumber?), toAMatrix: Matrix, resultIn: Matrix){
        assert(toAMatrix.type == resultIn.type, "View types must agrees")
        let t = toAMatrix.type
        switch t {
        case .f:
            vsip_smadd_f((aScalar.1?.floatValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case .d:
            vsip_smadd_d((aScalar.1?.doubleValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case .cf:
            switch aScalar.0!{
            case .f:
                vsip_rscmadd_f((aScalar.1?.floatValue)!, toAMatrix.vsip!, resultIn.vsip!)
            case .d:
                vsip_rscmadd_f((aScalar.1?.floatValue)!, toAMatrix.vsip!, resultIn.vsip!)
            case .cf:
                let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
                vsip_csmadd_f(aNumber, toAMatrix.vsip!, resultIn.vsip!)
            case .cd:
                let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
                vsip_csmadd_f(aNumber, toAMatrix.vsip!, resultIn.vsip!)
            default:
                break
            }
        case .cd:
            switch aScalar.0!{
            case .f:
                vsip_rscmadd_d((aScalar.1?.doubleValue)!, toAMatrix.vsip!, resultIn.vsip!)
            case .d:
                vsip_rscmadd_d((aScalar.1?.doubleValue)!, toAMatrix.vsip!, resultIn.vsip!)
            case .cf:
                let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
                vsip_csmadd_d(aNumber, toAMatrix.vsip!, resultIn.vsip!)
            case .cd:
                let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
                vsip_csmadd_d(aNumber, toAMatrix.vsip!, resultIn.vsip!)
            default:
                break
            }
        default:
            precondition(false, "Argument string not supported for svadd")
        }
        
    }
    
    public static func mul(_ one: Vector, to: Vector, resultsIn: Vector) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        switch (one.type, to.type, resultsIn.type) {
        case (.f,.f,.f):
            vsip_vmul_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.f,.cf, .cf):
            vsip_rcvmul_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.d, .d,.d):
            vsip_vmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.d, .cd, .cd):
            vsip_rcvmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.cf, .cf, .cf):
            vsip_cvmul_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.cd, .cd, .cd):
            vsip_cvmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.i, .i, .i):
            vsip_vmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.li, .li, .li):
            vsip_vmul_li(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.uc,.uc,.uc):
            vsip_vmul_uc(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.si,.si,.si):
            vsip_vmul_si(one.vsip!, to.vsip!, resultsIn.vsip!)
        default:
            precondition(false, "function not supported for input/output views")
        }
        
    }
    public static func mul(_ one: Matrix, to: Matrix, resultsIn: Matrix) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        switch (one.type, to.type, resultsIn.type) {
        case (.f, .f, .f):
            vsip_mmul_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.f, .cf, .cf):
            vsip_rcmmul_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.d, .d, .d):
            vsip_mmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.f, .cd, .cd):
            vsip_rcmmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.cf, .cf, .cf):
            vsip_cmmul_f(one.vsip!, to.vsip!, resultsIn.vsip!)
        case (.cd, .cd, .cd):
            vsip_cmmul_d(one.vsip!, to.vsip!, resultsIn.vsip!)
        default:
            precondition(false, "function not supported for input/output views")
        }
    }
    public static func mul(_ aScalar: Double, toAVector: Vector, resultIn: Vector){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.d, aScalar as NSNumber?, nil)
        Vsip.mul(aNumber, toAVector: toAVector, resultIn: resultIn)
        
    }
    public static func mul(_ aScalar: Float, toAVector: Vector, resultIn: Vector){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.f, aScalar as NSNumber?, nil)
        Vsip.mul(aNumber, toAVector: toAVector, resultIn: resultIn)
    }
    public static func mul(_ aScalar: Int, toAVector: Vector, resultIn: Vector){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.i, aScalar as NSNumber?, nil)
        Vsip.mul(aNumber, toAVector: toAVector, resultIn: resultIn)
    }
    public static func mul(_ aScalar: (Block.Types?, NSNumber?, NSNumber?), toAVector: Vector, resultIn: Vector){
        let t = (aScalar.0!, resultIn.type)
        switch t {
        case (.f,.f):
            vsip_svmul_f((aScalar.1?.floatValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.d,.d):
            vsip_svmul_d((aScalar.1?.doubleValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.f, .cf):
            vsip_rscvmul_f((aScalar.1?.floatValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.d, .cf):
            vsip_rscvmul_f((aScalar.1?.floatValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.cf, .cf):
            let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
            vsip_csvmul_f(aNumber, toAVector.vsip!, resultIn.vsip!)
        case (.cd, .cf):
            let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
            vsip_csvmul_f(aNumber, toAVector.vsip!, resultIn.vsip!)
        case (.f,.cd):
            vsip_rscvmul_d((aScalar.1?.doubleValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.d,.cd):
            vsip_rscvmul_d((aScalar.1?.doubleValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.cf, .cd):
            let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
            vsip_csvmul_d(aNumber, toAVector.vsip!, resultIn.vsip!)
        case (.cd,.cd):
            let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
            vsip_csvmul_d(aNumber, toAVector.vsip!, resultIn.vsip!)
        case (.i, .i):
            vsip_svmul_i((aScalar.1?.int32Value)!, toAVector.vsip!, resultIn.vsip!)
        case (.li,.li):
            vsip_svmul_li((aScalar.1?.intValue)!, toAVector.vsip!, resultIn.vsip!)
        case (.si,.si):
            vsip_svmul_si((aScalar.1?.int16Value)!, toAVector.vsip!, resultIn.vsip!)
        case (.uc,.uc):
            vsip_svmul_uc((aScalar.1?.uint8Value)!, toAVector.vsip!, resultIn.vsip!)
        default:
            precondition(false, "Argument string not supported for svmul")
        }
        
    }
    public static func mul(_ aScalar: Double, toAMatrix: Matrix, resultIn: Matrix){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.d, aScalar as NSNumber?, nil)
        Vsip.mul(aNumber, toAMatrix: toAMatrix, resultIn: resultIn)
        
    }
    public static func mul(_ aScalar: Float, toAMatrix: Matrix, resultIn: Matrix){
        let aNumber: (Block.Types?, NSNumber?, NSNumber?) = (.f, aScalar as NSNumber?, nil)
        Vsip.mul(aNumber, toAMatrix: toAMatrix, resultIn: resultIn)
    }
    public static func mul(_ aScalar: (Block.Types?, NSNumber?, NSNumber?), toAMatrix: Matrix, resultIn: Matrix){
        assert(sizeEqual(toAMatrix, against: resultIn),"Views must be the same size")
        let t = (aScalar.0!,toAMatrix.type)
        switch t {
        case (.f,.f):
            vsip_smmul_f((aScalar.1?.floatValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case (.d,.d):
            vsip_smmul_d((aScalar.1?.doubleValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case (.f,.cf):
            vsip_rscmmul_f((aScalar.1?.floatValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case (.d,.f):
            vsip_rscmmul_f((aScalar.1?.floatValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case (.cf,.f):
            let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
            vsip_csmmul_f(aNumber, toAMatrix.vsip!, resultIn.vsip!)
        case (.cd,.f):
            let aNumber = vsip_cmplx_f((aScalar.1?.floatValue)!,(aScalar.2?.floatValue)!)
            vsip_csmmul_f(aNumber, toAMatrix.vsip!, resultIn.vsip!)
        case (.f,.cd):
            vsip_rscmmul_d((aScalar.1?.doubleValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case (.d,.cd):
            vsip_rscmmul_d((aScalar.1?.doubleValue)!, toAMatrix.vsip!, resultIn.vsip!)
        case (.cf,.cd):
            let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
            vsip_csmmul_d(aNumber, toAMatrix.vsip!, resultIn.vsip!)
        case (.cd,.cd):
            let aNumber = vsip_cmplx_d((aScalar.1?.doubleValue)!,(aScalar.2?.doubleValue)!)
            vsip_csmmul_d(aNumber, toAMatrix.vsip!, resultIn.vsip!)
        default:
            precondition(false, "Argument string not supported for mmul")
        }
        
    }
    public static func vmmul(vector: Vector, matrix: Matrix, major: vsip_major, output: Matrix){
        let vsipVec = vector.vsip!
        let vsipMat = matrix.vsip!
        let vsipOut = output.vsip!
        let t = (vector.type, matrix.type, output.type)
        switch t {
        case(.cd, .cd, .cd):
            vsip_cvmmul_d ( vsipVec, vsipMat, major, vsipOut)
        case(.cf, .cf, .cf):
            vsip_cvmmul_f ( vsipVec, vsipMat, major, vsipOut)
        case(.d, .cd, .cd):
            vsip_rvcmmul_d ( vsipVec, vsipMat, major, vsipOut)
        case(.f, .cf, .cf):
            vsip_rvcmmul_f ( vsipVec, vsipMat, major, vsipOut)
        case(.d, .d, .d):
            vsip_vmmul_d ( vsipVec, vsipMat, major, vsipOut)
        case(.f, .f, .f):
            vsip_vmmul_f ( vsipVec, vsipMat, major, vsipOut)
        default:
            precondition(false, "Argument list not supported for vmmul")
        }
    }
    // Mark: - Random
    public class Rand {
        var vsip : OpaquePointer? = nil
        let jInit : JVSIP
        var myId : NSNumber?
        public init(seed: vsip_index, numberOfSubSequences: vsip_index, mySequence: vsip_index, portable: Bool){
            let rng = portable ? VSIP_PRNG : VSIP_NPRNG
            let id = mySequence
            let numprocs = numberOfSubSequences
            self.vsip = vsip_randcreate(seed, numprocs, id, rng)
            jInit = JVSIP()
            myId = jInit.myId
        }
        public convenience init(seed: vsip_index, portable: Bool){
            self.init(seed: seed, numberOfSubSequences: 1, mySequence: 1, portable: portable)
        }
        public func randu(_ view: Vector){
            let definedTypes: Set = ["f","d","cf","cd"]
            let t = view.type.rawValue
            assert(definedTypes.contains(t), "Random only defined for real or complex float values")
            switch t{
            case "f":
                vsip_vrandu_f(self.vsip!,view.vsip!)
            case "d":
                vsip_vrandu_d(self.vsip!,view.vsip!)
            case "cf":
                vsip_cvrandu_f(self.vsip!,view.vsip!)
            case "cd":
                vsip_cvrandu_d(self.vsip!,view.vsip!)
            default:
                precondition (false ,"Should not get to default in randu switch statement")            }
        }
        public func randu(_ view: Matrix){
            let definedTypes: Set = ["f","d","cf","cd"]
            let t = view.type.rawValue
            assert(definedTypes.contains(t), "Random only defined for real or complex float values")
            switch t{
            case "f":
                vsip_mrandu_f(self.vsip!,view.vsip!)
            case "d":
                vsip_mrandu_d(self.vsip!,view.vsip!)
            case "cf":
                vsip_cmrandu_f(self.vsip!,view.vsip!)
            case "cd":
                vsip_cmrandu_d(self.vsip!,view.vsip!)
            default:
                precondition (false ,"Should not get to default in randu switch statement")
            }
        }
        public func randn(_ view: Vector) {
            let definedTypes: Set = ["f","d","cf","cd"]
            let t = view.type.rawValue
            assert(definedTypes.contains(t), "Random only defined for real or complex float values")
            switch t{
            case "f":
                vsip_vrandn_f(self.vsip!,view.vsip!)
            case "d":
                vsip_vrandn_d(self.vsip!,view.vsip!)
            case "cf":
                vsip_cvrandn_f(self.vsip!,view.vsip!)
            case "cd":
                vsip_cvrandn_d(self.vsip!,view.vsip!)
            default:
                precondition (false ,"Should not get to default in randn switch statement")
            }
        }
        public func randn(_ view: Matrix) {
            let definedTypes: Set = ["f","d","cf","cd"]
            let t = view.type.rawValue
            assert(definedTypes.contains(t), "Random only defined for real or complex float values")
            switch t{
            case "f":
                vsip_mrandn_f(self.vsip!,view.vsip!)
            case "d":
                vsip_mrandn_d(self.vsip!,view.vsip!)
            case "cf":
                vsip_cmrandn_f(self.vsip!,view.vsip!)
            case "cd":
                vsip_cmrandn_d(self.vsip!,view.vsip!)
            default:
                precondition (false ,"Should not get to default in randn switch statement")
            }
        }
        deinit{
            let id = self.myId?.int32Value
            vsip_randdestroy(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("randdestroy id \(id!)")
            }
        }
        
    }
    // MARK: - Linear Algebra Matrix and Vector Operations
    public static func herm(_ complexInputMatrix: Matrix?, complexOuputMatrix: Matrix?){
        let vsipA = complexInputMatrix?.vsip!
        let vsipB = complexOuputMatrix?.vsip!
        let t = (complexInputMatrix!.type, complexOuputMatrix!.type)
        switch t {
        case (.cf, .cf):
            vsip_cmherm_f(vsipA, vsipB)
        case (.cd, .cd):
            vsip_cmherm_d(vsipA, vsipB)
        default:
            precondition(false, "Type not supported for herm")
        }
    }
    public static func jdot(_ complexInputVector: Vector?, complexOuputVector: Vector?) -> Scalar {
        let vsipA = complexInputVector?.vsip!
        let vsipB = complexOuputVector?.vsip!
        let t = (complexInputVector!.type, complexInputVector!.type)
        switch t {
        case (.cf, .cf):
            return Scalar(vsip_cvjdot_f(vsipA, vsipB))
        case (.cd, .cd):
            return Scalar(vsip_cvjdot_d(vsipA, vsipB))
        default:
            precondition(false, "Type not supported for jdot")
        }
    }
    public static func gemp(alpha: Scalar, matA: Matrix?, opA: vsip_mat_op, matB: Matrix?, opB: vsip_mat_op, beta: Scalar, matC: Matrix?) {
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.d, .d, .d):
            vsip_gemp_d(alpha.reald, vsipA, opA, vsipB, opB, beta.reald, vsipC)
        case (.f, .f, .f):
            vsip_gemp_f(alpha.realf, vsipA, opA, vsipB, opB, beta.realf, vsipC)
        case (.cd, .cd, .cd):
            vsip_cgemp_d(alpha.cmplxd, vsipA, opA, vsipB, opB, beta.cmplxd, vsipC)
        case (.cf, .cf, .cf):
            vsip_cgemp_f(alpha.cmplxf, vsipA, opA, vsipB, opB, beta.cmplxf, vsipC)
        default:
            precondition(false, "Type not supported for gemp")
        }
        
    }
    public static func gems(alpha: Scalar, matA: Matrix?, opA: vsip_mat_op, beta: Scalar, matC: Matrix?){
        let t = (matA!.type,  matC!.type)
        let vsipA = matA?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.d, .d):
            vsip_gems_d(alpha.reald, vsipA, opA, beta.reald, vsipC)
        case (.f, .f):
            vsip_gems_f(alpha.realf, vsipA, opA, beta.realf, vsipC)
        case (.cd, .cd):
            vsip_cgems_d(alpha.cmplxd, vsipA, opA, beta.cmplxd, vsipC)
        case (.cf, .cf):
            vsip_cgems_f(alpha.cmplxf, vsipA, opA, beta.cmplxf, vsipC)
        default:
            precondition(false, "Type not supported for gemp")
        }
    }
    public static func kron(alpha: Scalar, vecX: Vector?, vecY: Vector?, matC: Matrix?){
        let t = (vecX!.type, vecY!.type, matC!.type)
        let vsipX = vecX?.vsip!
        let vsipY = vecY?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.f, .f, .f):
            vsip_vkron_f(alpha.realf, vsipX, vsipY, vsipC)
        case (.d, .d, .d):
            vsip_vkron_d(alpha.reald, vsipX, vsipY, vsipC)
        case (.cf, .cf, .cf):
            vsip_cvkron_f(alpha.cmplxf, vsipX, vsipY, vsipC)
        case (.cd, .cd, .cd):
            vsip_cvkron_d(alpha.cmplxd, vsipX, vsipY, vsipC)
        default:
            precondition(false, "Kron not supported for argument list")
        }
    }
    public static func kron(alpha: Scalar, matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.f, .f, .f):
            vsip_mkron_f(alpha.realf, vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mkron_d(alpha.reald, vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmkron_f(alpha.cmplxf, vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmkron_d(alpha.cmplxd, vsipA, vsipB, vsipC)
        default:
            precondition(false, "Kron not supported for argument list")
        }
    }
    public static func prod3(matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.f, .f, .f):
            vsip_mprod3_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mprod3_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmprod3_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmprod3_d(vsipA, vsipB, vsipC)
        default:
            precondition(false, "VSIP function prod3 not supported for argument list")
        }
    }
    public static func prod3(matA: Matrix?, vecB: Vector?, vecC: Vector?){
        let t = (matA!.type, vecB!.type, vecC!.type)
        let vsipA = matA?.vsip!
        let vsipB = vecB?.vsip!
        let vsipC = vecC?.vsip!
        switch(t){
        case (.f, .f, .f):
            vsip_mvprod3_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mvprod3_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmvprod3_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmvprod3_d(vsipA, vsipB, vsipC)
        default:
            precondition(false, "VSIP function prod4 not supported for argument list")
        }
    }
    public static func prod4(matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.f, .f, .f):
            vsip_mprod4_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mprod4_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmprod4_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmprod4_d(vsipA, vsipB, vsipC)
        default:
            precondition(false, "VSIP function prod4 not supported for argument list")
        }
    }
    public static func prod4(matA: Matrix?, vecB: Vector?, vecC: Vector?){
        let t = (matA!.type, vecB!.type, vecC!.type)
        let vsipA = matA?.vsip!
        let vsipB = vecB?.vsip!
        let vsipC = vecC?.vsip!
        switch(t){
        case (.f, .f, .f):
            vsip_mvprod4_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mvprod4_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmvprod4_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmvprod4_d(vsipA, vsipB, vsipC)
        default:
            precondition(false, "VSIP function prod4 not supported for argument list")
        }
    }

    public static func prod(matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprod_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprod_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_mprod_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_mprod_f ( vsipA, vsipB, vsipC )
        default:
            precondition(false, "VSIP function prod not supported for argument list")
        }
    }
    public static func prod(matA: Matrix?, vecB: Vector?, vecC: Vector?){
        let t = (matA!.type, vecB!.type, vecC!.type)
        let vsipA = matA?.vsip!
        let vsipB = vecB?.vsip!
        let vsipC = vecC?.vsip!
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmvprod_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmvprod_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_mvprod_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_mvprod_f ( vsipA, vsipB, vsipC )
        default:
            precondition(false, "VSIP function prod not supported for argument list")
        }
    }
    public static func prod(vecA: Vector?, matB: Matrix?, vecC: Vector?){
        let t = (vecA!.type, matB!.type, vecC!.type)
        let vsipA = vecA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = vecC?.vsip!
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cvmprod_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cvmprod_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_vmprod_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_vmprod_f ( vsipA, vsipB, vsipC )
        default:
            precondition(false, "VSIP function prod not supported for argument list")
        }
    }
    public static func prodh(matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprodh_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprodh_f ( vsipA, vsipB, vsipC )
        default:
            precondition(false, "VSIP function prodh not supported for argument list")
        }
    }
    public static func prodj(matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprodj_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprodj_f ( vsipA, vsipB, vsipC )
        default:
            precondition(false, "VSIP function prodj not supported for argument list")
        }
    }
    public static func prodt(matA: Matrix?, matB: Matrix?, matC: Matrix?){
        let t = (matA!.type, matB!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipB = matB?.vsip!
        let vsipC = matC?.vsip!
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprodt_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprodt_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_mprodt_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_mprodt_f ( vsipA, vsipB, vsipC )
        default:
            precondition(false, "VSIP function prodt not supported for argument list")
        }
    }
    public static func trans(matA: Matrix?, matC: Matrix?){
        let t = (matA!.type, matC!.type)
        let vsipA = matA?.vsip!
        let vsipC = matC?.vsip!
        switch(t) {
        case (.cd, .cd):
            vsip_cmtrans_d(vsipA, vsipC)
        case(.cf, .cf):
            vsip_cmtrans_f(vsipA, vsipC)
        case(.d, .d):
            vsip_mtrans_d(vsipA, vsipC)
        case(.f, .f):
            vsip_mtrans_f(vsipA, vsipC)
        default:
            precondition(false, "VSIP function trans not supported for argument list")
        }
    }
    public static func dot(vecX: Vector?, vecY: Vector?) -> Scalar {
        let t = (vecX!.type, vecY!.type)
        let vsipX = vecX?.vsip!
        let vsipY = vecY?.vsip!
        switch(t){
        case (.f, .f):
            return Scalar(Float(vsip_vdot_f(vsipX, vsipY)))
        case (.d, .d):
            return Scalar(Double(vsip_vdot_d(vsipX, vsipY)))
        case (.cf, .cf):
            return Scalar(vsip_cvdot_f(vsipX, vsipY))
        case (.cd, .cd):
            return Scalar(vsip_cvdot_d(vsipX, vsipY))
        default:
            precondition(false, "Kron not supported for argument list")
        }
    }
    public static func outer(alpha: Scalar, vecX: Vector?, vecY: Vector?, matC: Matrix?){
        let vsipX = vecX?.vsip!
        let vsipY = vecY?.vsip!
        let vsipC = matC?.vsip!
        let t = (vecX!.type, vecY!.type, matC!.type)
        switch(t){
        case (.f, .f, .f):
            vsip_vouter_f(alpha.realf, vsipX, vsipY, vsipC)
        case (.d, .d, .d):
            vsip_vouter_d(alpha.reald, vsipX, vsipY, vsipC)
        case (.cf, .cf, .cf):
            vsip_cvouter_f(alpha.cmplxf, vsipX, vsipY, vsipC)
        case (.cd, .cd, .cd):
            vsip_cvouter_d(alpha.cmplxd, vsipX, vsipY, vsipC)
        default:
            precondition(false, "Function outer not supported for argument list")
        }
    }
    
    // MARK: - LU
    
    // MARK: - QRD
    
    // MARK: - SVD
    // needs work on error checks
    /*!
     For SVD given input matrix A we have
     A = U S transpose(V)
     */
    public class Svd {
        let type: Block.Types
        let n: Int  // length of singular value vector
        var amSet = false
        fileprivate let jVsip : sv?
        public struct Attrib {
            let m: Int
            let n: Int
            let saveU: vsip_svd_uv
            let saveV: vsip_svd_uv
            init(columnLength: Int, rowLength: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                m=columnLength
                n=rowLength
                self.saveU=saveU
                self.saveV=saveV
            }
            var size : (Int, Int) {
                return (m,n)
            }
        }
        let attr : Attrib
        fileprivate class sv {
            var vsip : OpaquePointer?
            var s: OpaquePointer?
            let jInit : JVSIP
            var type : Block.Types?
            init(){
                jInit = JVSIP()
            }
        }
        fileprivate class sv_f : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .f
                self.vsip = vsip_svd_create_f(vsip_length(m),vsip_length(n),saveU,saveV)
                self.s = vsip_vcreate_f(vsip_length((m<n) ? m:n),VSIP_MEM_NONE)
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_svd_destroy_f \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_svd_destroy_f(self.vsip!)
                vsip_valldestroy_f(self.s!)
            }
        }
        fileprivate class sv_d : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .d
                self.vsip = vsip_svd_create_d(vsip_length(m),vsip_length(n),saveU,saveV)
                self.s = vsip_vcreate_d(vsip_length((m<n) ? m:n),VSIP_MEM_NONE)
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_svd_destroy_d \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_svd_destroy_d(self.vsip!)
                vsip_valldestroy_d(self.s!)
            }
        }
        fileprivate class csv_f : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .cf
                self.vsip = vsip_csvd_create_f(vsip_length(m),vsip_length(n),saveU,saveV)
                self.s = vsip_vcreate_f(vsip_length((m<n) ? m:n),VSIP_MEM_NONE)
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_csvd_destroy_cf \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_csvd_destroy_f(self.vsip!)
                vsip_valldestroy_f(self.s!)
            }
        }
        fileprivate class csv_d : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .cd
                self.vsip = vsip_csvd_create_d(vsip_length(m),vsip_length(n),saveU,saveV)
                self.s = vsip_vcreate_d(vsip_length((m<n) ? m:n),VSIP_MEM_NONE)
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_csvd_destroy_cd \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_svd_destroy_d(self.vsip!)
                vsip_valldestroy_d(self.s!)
            }
        }
        
        public init(type: Block.Types, m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            self.n = (m<n) ? m:n
            self.type = type
            self.attr = Attrib(columnLength: m, rowLength: n, saveU: saveU, saveV: saveV)
            switch type {
            case .d:
                self.jVsip = sv_d(m: m,n: n,saveU: saveU, saveV: saveV)
            case .f:
                self.jVsip = sv_f(m: m,n: n,saveU: saveU, saveV: saveV)
            case .cd:
                self.jVsip = csv_d(m: m,n: n,saveU: saveU, saveV: saveV)
            case .cf:
                self.jVsip = csv_f(m: m,n: n,saveU: saveU, saveV: saveV)
            default:
                self.jVsip = nil
                assert(false, "SVD not supported for this type")
            }
        }
        public convenience init(view: Matrix, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            self.init(type: view.type, m: view.columnLength, n: view.rowLength, saveU: saveU, saveV: saveV)
        }
        public convenience init(view: Matrix){
            self.init(type: view.type, m: view.columnLength, n: view.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
        }
        fileprivate var vsip: OpaquePointer? {
            return self.jVsip!.vsip
        }
        fileprivate var s: OpaquePointer? {// singular values
            return self.jVsip!.s
        }
        public func decompose(_ matrix: Matrix, singularValues: Vector){
            switch (self.type, matrix.type, singularValues.type){
            case (.d, .d, .d):
                vsip_svd_d(self.vsip!, matrix.vsip!, self.s!)
                vsip_vcopy_d_d(self.s!, singularValues.vsip!)
            case (.f, .f, .f):
                vsip_svd_f(self.vsip!, matrix.vsip!, self.s!)
                vsip_vcopy_f_f(self.s!, singularValues.vsip!)
            case (.cd, .cd, .d):
                vsip_csvd_d(self.vsip!, matrix.vsip!, self.s!)
                vsip_vcopy_d_d(self.s!, singularValues.vsip!)
            case (.cf, .cf, .f):
                vsip_csvd_f(self.vsip!, matrix.vsip!, self.s!)
                vsip_vcopy_f_f(self.s!, singularValues.vsip!)
            default:
                precondition(false, "function not supported for input/output views")
            }
            self.amSet = true
        }
        public func decompose(_ matrix: Matrix) -> Vector? {
            let v = Vector(length: self.n, type: self.type)
            self.decompose(matrix, singularValues: v)
            return v
        }
        /*!
         Function matU returns 0 on success
         Output data is stored in matrix matU in natural order starting at
         element index (0,0). Matrix matU must be large enough to hold the
         output data
         */
        public func matU(_ lowColumn: Int, highColumn: Int, matU: Matrix?) -> Int {
            let low = vsip_scalar_vi(lowColumn)
            let high = vsip_scalar_vi(highColumn)
            assert(low <= high, "Error in column selection")
            let highMax = vsip_scalar_vi((matU?.rowLength)!)
            let vsipSv = self.vsip! // VSIPL pointer to singular value object
            let vsipC = matU?.vsip! // VSIPL pointer to U Matrix
            if matU == nil{
                return -1
            }
            switch (self.attr.saveU, matU!.type, self.type){
            case (VSIP_SVD_UVFULL, .f, .f):
                return Int(vsip_svdmatu_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVFULL, .cf, .cf):
                return Int(vsip_csvdmatu_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVFULL, .d, .d):
                return Int(vsip_svdmatu_d(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVFULL, .cd, .cd):
                return Int(vsip_csvdmatu_d(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .f, .f):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_svdmatu_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .cf, .cf):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_csvdmatu_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .d, .d):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_svdmatu_d(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .cd, .cd):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_csvdmatu_d(vsipSv, low, high, vsipC))
            default:
                if self.attr.saveU == VSIP_SVD_UVNOS{
                    precondition(false, "SVD Created without U Matrix")
                    return -1
                } else {
                    precondition(false, "SVD Not supported for these types")
                    return -1
                }
            }
        }
        /*!
         Function matV returns 0 on success
         Output data is stored in matrix matV in natural order starting at
         element index (0,0). Matrix matV must be large enough to hold the
         output data
         */
        public func matV(_ lowColumn: Int, highColumn: Int, matV: Matrix?) -> Int {
            let low = vsip_scalar_vi(lowColumn)
            let high = vsip_scalar_vi(highColumn)
            assert(low <= high, "Error in column selection")
            let highMax = vsip_scalar_vi((matV?.rowLength)!)
            let vsipSv = self.vsip! // VSIPL pointer to singular value object
            let vsipC = matV?.vsip! // VSIPL pointer to V Matrix
            if matV == nil{
                return -1
            }
            switch (self.attr.saveU, matV!.type, self.type){
            case (VSIP_SVD_UVFULL, .f, .f):
                return Int(vsip_svdmatv_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVFULL, .cf, .cf):
                return Int(vsip_csvdmatv_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVFULL, .d, .d):
                return Int(vsip_svdmatv_d(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVFULL, .cd, .cd):
                return Int(vsip_csvdmatv_d(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .f, .f):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_svdmatv_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .cf, .cf):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_csvdmatv_f(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .d, .d):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_svdmatv_d(vsipSv, low, high, vsipC))
            case (VSIP_SVD_UVPART, .cd, .cd):
                precondition(high <= highMax, "Input matrix row length to small")
                return Int(vsip_csvdmatv_d(vsipSv, low, high, vsipC))
            default:
                if self.attr.saveU == VSIP_SVD_UVNOS {
                    precondition(false, "SVD Created without V Matrix")
                    return -1
                } else {
                    precondition(false, "SVD Not supported for these types")
                    return -1
                }
            }
        }
        public func produ(op: vsip_mat_op, side: vsip_mat_side, matrix: Matrix?) -> Int {
            let vsipSv = self.vsip!
            let vsipC = matrix?.vsip!
            switch (self.attr.saveU, matrix!.type, self.type){
            case (VSIP_SVD_UVFULL, .f, .f):
                return Int(vsip_svdprodu_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVFULL, .cf, .cf):
                return Int(vsip_csvdprodu_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVFULL, .d, .d):
                return Int(vsip_svdprodu_d(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVFULL, .cd, .cd):
                return Int(vsip_csvdprodu_d(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .f, .f):
                return Int(vsip_svdprodu_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .cf, .cf):
                return Int(vsip_csvdprodu_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .d, .d):
                return Int(vsip_svdprodu_d(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .cd, .cd):
                return Int(vsip_csvdprodu_d(vsipSv, op, side, vsipC))
            default:
                if self.attr.saveU == VSIP_SVD_UVNOS {
                    precondition(false, "SVD Created without U Matrix")
                    return -1
                } else {
                    precondition(false, "SVD Not supported for these types")
                    return -1
                }
            }
        }
        public func prodv(op: vsip_mat_op, side: vsip_mat_side, matrix: Matrix?) -> Int {
            let vsipSv = self.vsip!
            let vsipC = matrix?.vsip!
            switch (self.attr.saveV, matrix!.type, self.type){
            case (VSIP_SVD_UVFULL, .f, .f):
                return Int(vsip_svdprodv_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVFULL, .cf, .cf):
                return Int(vsip_csvdprodv_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVFULL, .d, .d):
                return Int(vsip_svdprodv_d(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVFULL, .cd, .cd):
                return Int(vsip_csvdprodv_d(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .f, .f):
                return Int(vsip_svdprodv_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .cf, .cf):
                return Int(vsip_csvdprodv_f(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .d, .d):
                return Int(vsip_svdprodv_d(vsipSv, op, side, vsipC))
            case (VSIP_SVD_UVPART, .cd, .cd):
                return Int(vsip_csvdprodv_d(vsipSv, op, side, vsipC))
            default:
                if self.attr.saveU == VSIP_SVD_UVNOS {
                    precondition(false, "SVD Created without V Matrix")
                    return -1
                } else {
                    precondition(false, "SVD Not supported for these types")
                    return -1
                }
            }
        }
        public var sizeU: (Int, Int){
            get {
                var retval = (self.attr.m, self.attr.m)
                switch self.attr.saveU {
                case VSIP_SVD_UVFULL:
                    return retval
                case VSIP_SVD_UVPART:
                    if self.attr.m > self.attr.n {
                        retval.1 = self.attr.n
                    }
                    return retval
                default:
                    return (0,0)
                }
            }
        }
        public var sizeV: (Int, Int){
            get {
                var retval = (self.attr.n, self.attr.n)
                switch self.attr.saveU {
                case VSIP_SVD_UVFULL:
                    return retval
                case VSIP_SVD_UVPART:
                    if self.attr.n > self.attr.m {
                        retval.1 = self.attr.m
                    }
                    return retval
                default:
                    return (0,0)
                }
            }
        }

        public var matU: Matrix? {
            get {
                if !amSet {
                    return nil
                }
                if self.attr.saveU == VSIP_SVD_UVNOS {
                    return nil
                }
                let (m,n) = self.sizeU
                let mat = Matrix(columnLength: m, rowLength: n, type: self.type, major: VSIP_ROW)
                let success = self.matU(0, highColumn: n-1, matU: mat)
                if success == 0 {
                     return mat
                } else {
                    return nil
                }
            }
        }
        public var matV: Matrix? {
            get {
                if !amSet {
                    return nil
                }
                if self.attr.saveU == VSIP_SVD_UVNOS {
                    return nil
                }
                let (m,n) = self.sizeV
                let mat = Matrix(columnLength: m, rowLength: n, type: self.type, major: VSIP_ROW)
                let success = self.matV(0, highColumn: n-1, matV: mat)
                if success == 0 {
                    return mat
                } else {
                    return nil
                }
            }
        }
    }
    
}
