
//  SwiftVsip
//
//  Created by Randall Judd on 9/3/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//
import Foundation
import vsip
// MARK:  - Elementary Math Functions
public  func acos(_ input: Vector, resultsIn: Vector) {
    assert(sizeEqual(input, against: resultsIn), "vectors must be the same size")
    switch (input.type, resultsIn.type) {
    case (.f, .f):
        vsip_vacos_f(input.vsip, resultsIn.vsip)
    case (.d, .d):
        vsip_vacos_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for this type vector")
    }
}
public  func acos(_ input: Matrix, resultsIn: Matrix) {
    assert(sizeEqual(input, against: resultsIn), "vectors must be the same size")
    switch (input.type, resultsIn.type) {
    case (.f, .f):
        vsip_macos_f(input.vsip, resultsIn.vsip)
    case (.d, .d):
        vsip_macos_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for this type vector")
    }
}
public  func asin(_ input: Vector, resultsIn: Vector) {
    assert(sizeEqual(input, against: resultsIn), "vectors must be the same size")
    switch (input.type, resultsIn.type) {
    case (.f, .f):
        vsip_vasin_f(input.vsip, resultsIn.vsip)
    case (.d, .d):
        vsip_vasin_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for this type vector")
    }
}
public  func asin(_ input: Matrix, resultsIn: Matrix) {
    assert(sizeEqual(input, against: resultsIn), "vectors must be the same size")
    switch (input.type, resultsIn.type) {
    case (.f, .f):
        vsip_masin_f(input.vsip, resultsIn.vsip)
    case (.d, .d):
        vsip_masin_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for this type vector")
    }
}
public  func atan(_ input: Vector, resultsIn: Vector) {
    assert(sizeEqual(input, against: resultsIn), "View sizes must be the same")
    switch input.type {
    case .f:
        vsip_vatan_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vatan_d(input.vsip, resultsIn.vsip)
    default:
        precondition(true, "function not supported for this type vector")
        break
    }
}
public  func atan(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_matan_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_matan_d(input.vsip, resultsIn.vsip)
    default:
        precondition(true, "function not supported for this type matrix")
        break
    }
}
public  func atan2(numerator: Vector, denominator: Vector, resultsIn: Vector) {
    let tn = numerator.type
    let td = denominator.type
    let to = resultsIn.type
    assert(tn == td && tn == to, "View types must agree")
    assert(sizeEqual(numerator, against: denominator) && sizeEqual(numerator, against: resultsIn), "View sizes musta be equal")
    switch tn{
    case .f:
        vsip_vatan2_f(numerator.vsip,denominator.vsip,resultsIn.vsip)
    case .d:
        vsip_vatan2_d(numerator.vsip,denominator.vsip,resultsIn.vsip)
    default:
        preconditionFailure("function not supported for this type matrix")
        break
    }
    
}
public  func atan2(numerator: Matrix, denominator: Matrix, resultsIn: Matrix) {
    let tn = numerator.type
    let td = denominator.type
    let to = resultsIn.type
    assert(tn == td && tn == to, "input types must be the same")
    assert(sizeEqual(numerator, against: denominator) && sizeEqual(numerator, against: resultsIn), "View sizes musta be equal")
    switch tn {
    case .f:
        vsip_matan2_f(numerator.vsip,denominator.vsip,resultsIn.vsip)
    case .d:
        vsip_matan2_d(numerator.vsip,denominator.vsip,resultsIn.vsip)
    default:
        preconditionFailure("function not supported for this type matrix")
        break
    }
    
}
public  func cos(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vcos_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vcos_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func cos(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mcos_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mcos_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func cosh(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vcosh_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vcosh_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func cosh(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mcosh_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mcosh_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func sin(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vsin_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vsin_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func sin(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_msin_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_msin_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func sinh(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vsinh_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vsinh_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func sinh(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_msinh_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_msinh_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func exp(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vexp_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vexp_d(input.vsip, resultsIn.vsip)
    case .cf:
        vsip_cvexp_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cvexp_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func exp(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mexp_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mexp_d(input.vsip, resultsIn.vsip)
    case .cf:
        vsip_cmexp_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cmexp_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func exp10(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vexp10_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vexp10_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func exp10(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mexp10_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mexp10_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func log(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vlog_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vlog_d(input.vsip, resultsIn.vsip)
    case .cf:
        vsip_cvlog_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cvlog_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func log(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mlog_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mlog_d(input.vsip, resultsIn.vsip)
    case .cf:
        vsip_cmlog_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cmlog_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func log10(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vlog10_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vlog10_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func log10(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mlog10_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mlog10_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func sqrt(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vsqrt_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vsqrt_d(input.vsip, resultsIn.vsip)
    case .cf:
        vsip_cvsqrt_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cvsqrt_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func sqrt(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_msqrt_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_msqrt_d(input.vsip, resultsIn.vsip)
    case .cf:
        vsip_cmsqrt_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cmsqrt_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func tan(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vtan_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vtan_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func tan(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mtan_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mtan_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func tanh(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_vtanh_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_vtanh_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func tanh(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .f:
        vsip_mtanh_f(input.vsip, resultsIn.vsip)
    case .d:
        vsip_mtanh_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}

// MARK: - Unary Functions
public  func arg(_ input: Vector, resultsIn: Vector) {
    let type = (input.type, resultsIn.type)
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch type {
    case (.cf, .f):
        vsip_varg_f(input.vsip, resultsIn.vsip)
    case (.cd, .d):
        vsip_varg_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views")
    }
}
public  func arg(_ input: Matrix, resultsIn: Matrix) {
    let type = (input.type, resultsIn.type)
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch type {
    case (.cf, .f):
        vsip_marg_f(input.vsip, resultsIn.vsip)
    case (.cd, .d):
        vsip_marg_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views")
    }
}
public  func ceil(_ input: Vector, resultsIn: Vector){
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch (input.type, resultsIn.type) {
    case (.d, .d):
        vsip_vceil_d_d(input.vsip, resultsIn.vsip)
    case (.d,.i):
        vsip_vceil_d_i(input.vsip, resultsIn.vsip)
    case (.f, .f):
        vsip_vceil_f_f(input.vsip, resultsIn.vsip)
    case (.f,.i):
        vsip_vceil_f_i(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views")
        break
    }
}
public  func ceil(_ input: Matrix, resultsIn: Matrix){
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch (input.type, resultsIn.type) {
    case (.d, .d):
        vsip_mceil_d_d(input.vsip, resultsIn.vsip)
    case (.d,.i):
        vsip_mceil_d_i(input.vsip, resultsIn.vsip)
    case (.f, .f):
        vsip_mceil_f_f(input.vsip, resultsIn.vsip)
    case (.f,.i):
        vsip_mceil_f_i(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views")
        break
    }
    
}
public  func conj(_ input: Vector, resultsIn: Vector) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .cf:
        vsip_cvconj_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cvconj_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func conj(_ input: Matrix, resultsIn: Matrix) {
    assert(input.type == resultsIn.type, "View types must agree")
    assert(sizeEqual(input, against: resultsIn), "Views must be the same size")
    switch input.type {
    case .cf:
        vsip_cmconj_f(input.vsip, resultsIn.vsip)
    case .cd:
        vsip_cmconj_d(input.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported")
        break
    }
}
public  func neg(_ input: Vector, resultsIn: Vector){
    assert(sizeEqual(input, against: resultsIn), "View size of input an resultsIn must be equal for neg")
    assert(input.type == resultsIn.type, "View types of input and resultsIn must be the same for neg")
    switch input.type {
    case .f:
        vsip_vneg_f(input.vsip,resultsIn.vsip)
    case .d:
        vsip_vneg_d(input.vsip,resultsIn.vsip)
    case .cf:
        vsip_cvneg_f(input.vsip,resultsIn.vsip)
    case .cd:
        vsip_cvneg_d(input.vsip,resultsIn.vsip)
    case .i:
        vsip_vneg_i(input.vsip,resultsIn.vsip)
    case .li:
        vsip_vneg_li(input.vsip,resultsIn.vsip)
    case .vi:
        vsip_vneg_si(input.vsip,resultsIn.vsip)
    default:
        assert(false, "type not found for neg")
        break
    }
    
}
public  func neg(_ input: Matrix, resultsIn: Matrix){
    assert(sizeEqual(input, against: resultsIn), "View size of input an resultsIn must be equal for neg")
    assert(input.type == resultsIn.type, "View types of input and resultsIn must be the same for neg")
    switch input.type {
    case .f:
        vsip_mneg_f(input.vsip,resultsIn.vsip)
    case .d:
        vsip_mneg_d(input.vsip,resultsIn.vsip)
    case .cf:
        vsip_cmneg_f(input.vsip,resultsIn.vsip)
    case .cd:
        vsip_cmneg_d(input.vsip,resultsIn.vsip)
    default:
        assert(false, "type not found for neg")
        break
    }
    
}
public  func sumval(_ input: Vector) -> Scalar {
    switch input.type {
    case .d:
        return Scalar(vsip_vsumval_d(input.vsip))
    case .f:
        return Scalar(vsip_vsumval_f(input.vsip))
    case .cd:
        return Scalar(vsip_cvsumval_d(input.vsip))
    case .cf:
        return Scalar(vsip_cvsumval_f(input.vsip))
    case .i:
        return Scalar(vsip_vsumval_i(input.vsip))
    case .bl:
        return Scalar(vsip_vsumval_bl(input.vsip))
    default:
        preconditionFailure("sumval not supported for this type")
    }
}
public  func sumval(_ input: Matrix) -> Scalar {
    switch input.type {
    case .d:
        return Scalar(vsip_msumval_d(input.vsip))
    case .f:
        return Scalar(vsip_msumval_f(input.vsip))
    case .cd:
        return Scalar(vsip_cmsumval_d(input.vsip))
    case .cf:
        return Scalar(vsip_cmsumval_f(input.vsip))
    case .bl:
        return Scalar(vsip_msumval_bl(input.vsip))
    default:
        preconditionFailure("sumval not supported for this type")
        
    }
}
public  func sumsqval(_ input: Vector) -> Scalar {
    switch input.type {
    case .d:
        return Scalar(Double(vsip_vsumsqval_d(input.vsip)))
    case .f:
        return Scalar(Float(vsip_vsumsqval_f(input.vsip)))
    default:
        preconditionFailure("sumsqval not supported for this type")
        break
    }
}
public  func sumsqval(_ input: Matrix) -> Scalar {
    switch input.type {
    case .d:
        return Scalar(Double(vsip_msumsqval_d(input.vsip)))
    case .f:
        return Scalar(Float(vsip_msumsqval_f(input.vsip)))
    default:
        preconditionFailure("sumsqval not supported for this type")
        break
    }
}

// MARK: - Binary Functions
public  func add(_ one: Vector, _ to: Vector, resultsIn: Vector) {
    assert(sizeEqual(one, against: to),"Views must be the same size")
    assert(to.type == resultsIn.type, "Output view type not compliant with input")
    switch one.type {
    case .f:
        switch to.type{
        case .f:
            vsip_vadd_f(one.vsip, to.vsip, resultsIn.vsip)
        case .cf:
            vsip_rcvadd_f(one.vsip, to.vsip, resultsIn.vsip)
        default:
            break
        }
    case .d:
        switch to.type{
        case .d:
            vsip_vadd_d(one.vsip, to.vsip, resultsIn.vsip)
        case .cd:
            vsip_rcvadd_d(one.vsip, to.vsip, resultsIn.vsip)
        default:
            break
        }
    case .cf:
        vsip_cvadd_f(one.vsip, to.vsip, resultsIn.vsip)
    case .cd:
        vsip_cvadd_d(one.vsip, to.vsip, resultsIn.vsip)
    case .i:
        vsip_vadd_d(one.vsip, to.vsip, resultsIn.vsip)
    case .li:
        vsip_vadd_li(one.vsip, to.vsip, resultsIn.vsip)
    case .uc:
        vsip_vadd_li(one.vsip, to.vsip, resultsIn.vsip)
    case .si:
        vsip_vadd_si(one.vsip, to.vsip, resultsIn.vsip)
    case .vi:
        vsip_vadd_vi(one.vsip, to.vsip, resultsIn.vsip)
    default:
        preconditionFailure("View type not supported")
        break
    }
    
}
public  func add(_ one: Matrix, _ to: Matrix, resultsIn: Matrix) {
    assert(sizeEqual(one, against: to),"Views must be the same size")
    assert(to.type == resultsIn.type, "Output view type not compliant with input")
    switch one.type {
    case .f:
        switch to.type{
        case .f:
            vsip_madd_f(one.vsip, to.vsip, resultsIn.vsip)
        case .cf:
            vsip_rcmadd_f(one.vsip, to.vsip, resultsIn.vsip)
        default:
            break
        }
    case .d:
        switch to.type{
        case .d:
            vsip_madd_d(one.vsip, to.vsip, resultsIn.vsip)
        case .cd:
            vsip_rcmadd_d(one.vsip, to.vsip, resultsIn.vsip)
        default:
            break
        }
    case .cf:
        vsip_cmadd_f(one.vsip, to.vsip, resultsIn.vsip)
    case .cd:
        vsip_cmadd_d(one.vsip, to.vsip, resultsIn.vsip)
    case .i:
        vsip_madd_d(one.vsip, to.vsip, resultsIn.vsip)
    case .li:
        vsip_madd_li(one.vsip, to.vsip, resultsIn.vsip)
    case .si:
        vsip_madd_si(one.vsip, to.vsip, resultsIn.vsip)
    default:
        preconditionFailure("View type not supported")
        break
    }
}
public  func add(_ scalar: Double, _ vector: Vector, resultsIn: Vector){
    add(Scalar(scalar), vector, resultsIn: resultsIn)
    
}
public  func add(_ scalar: Float, _ vector: Vector, resultsIn: Vector){
    add(Scalar(scalar), vector, resultsIn: resultsIn)
    
}
public  func add(_ scalar: Int, _ vector: Vector, resultsIn: Vector){
    add(Scalar(scalar), vector, resultsIn: resultsIn)
}
public  func add(_ scalar: Scalar, _ vector: Vector, resultsIn: Vector){
    assert(vector.type == resultsIn.type, "View types must agrees")
    let t = (scalar.type, vector.type, resultsIn.type)
    switch t {
    case (.f, .f, .f):
        vsip_svadd_f(scalar.vsip_f, vector.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_svadd_d(scalar.vsip_d, vector.vsip, resultsIn.vsip)
    case (.f, .cf, .cf):
        vsip_rscvadd_f(scalar.vsip_f, vector.vsip, resultsIn.vsip)
    case (.d, .cd, .cd):
        vsip_rscvadd_d(scalar.vsip_d, vector.vsip, resultsIn.vsip)
    case  (.cf, .cf, .cf):
        vsip_csvadd_f(scalar.vsip_cf, vector.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_csvadd_d(scalar.vsip_cd, vector.vsip, resultsIn.vsip)
    case (.i, .i, .i):
        vsip_svadd_i(scalar.vsip_i, vector.vsip, resultsIn.vsip)
    case (.li, .li, .li):
        vsip_svadd_li(scalar.vsip_li, vector.vsip, resultsIn.vsip)
    case (.si, .si, .si):
        vsip_svadd_si(scalar.vsip_si, vector.vsip, resultsIn.vsip)
    case (.uc, .uc, .uc):
        vsip_svadd_uc(scalar.vsip_uc, vector.vsip, resultsIn.vsip)
    case (.vi, .vi, .vi):
        vsip_svadd_vi(scalar.vsip_vi, vector.vsip, resultsIn.vsip)
    default:
        preconditionFailure("Argument string not supported for svadd")
    }
}
public  func add(_ scalar: Double, _ matrix: Matrix, resultsIn: Matrix){
    add(Scalar(scalar), matrix, resultsIn: resultsIn)
}
public  func add(_ scalar: Float, _ matrix: Matrix, resultsIn: Matrix){
    add(Scalar(scalar), matrix, resultsIn: resultsIn)
    
}
public  func add(_ scalar: Scalar, _ matrix: Matrix, resultsIn: Matrix){
    assert(sizeEqual(matrix, against: resultsIn),"Views must be the same size")
    let t = (scalar.type, matrix.type, resultsIn.type)
    switch t {
    case (.f, .f, .f):
        vsip_smadd_f(scalar.vsip_f, matrix.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_smadd_d(scalar.vsip_d, matrix.vsip, resultsIn.vsip)
    case (.f, .cf, .cf):
        vsip_rscmadd_f(scalar.vsip_f, matrix.vsip, resultsIn.vsip)
    case (.d, .cd, .cd):
        vsip_rscmadd_d(scalar.vsip_d, matrix.vsip, resultsIn.vsip)
    case  (.cf, .cf, .cf):
        vsip_csmadd_f(scalar.vsip_cf, matrix.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_csmadd_d(scalar.vsip_cd, matrix.vsip, resultsIn.vsip)
    default:
        preconditionFailure("Argument string not supported for scalar matrix add")
        
    }
}

public  func div(numerator aView: Vector, denominator by: Vector, quotient resultsIn: Vector){
    assert(sizeEqual(aView, against: by),"Views must be the same size")
    assert(sizeEqual(aView, against: resultsIn),"Views must be the same size")
    let t = (aView.type, by.type, resultsIn.type)
    switch t {
    case (.d, .cd, .cd):
        vsip_rcvdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.f, .cf, .cf):
        vsip_rcvdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_vdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.f, .f, .f):
        vsip_vdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cd, .d, .cd):
        vsip_crvdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cf, .f, .cf):
        vsip_crvdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_cvdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cf, .cf, .cf):
        vsip_cvdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views of type (\t)")
    }
    
}
public  func div(numerator aView: Matrix, denominator by: Matrix, quotient resultsIn: Matrix){
    assert(sizeEqual(aView, against: by),"Views must be the same size")
    assert(sizeEqual(aView, against: resultsIn),"Views must be the same size")
    let t = (aView.type, by.type, resultsIn.type)
    switch t {
    case (.cd, .cd, .cd):
        vsip_cmdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cf, .cf, .cf):
        vsip_cmdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cd, .d, .cd):
        vsip_crmdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.cf, .f, .cf):
        vsip_crmdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_mdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.f, .f, .f):
        vsip_mdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    case (.d, .cd, .cd):
        vsip_rcmdiv_d(aView.vsip, by.vsip, resultsIn.vsip)
    case (.f, .cf, .cf):
        vsip_rcmdiv_f(aView.vsip, by.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views of type (\t)")
    }
    
}

public  func mul(_ one: Vector, _ to: Vector, resultsIn: Vector) {
    assert(sizeEqual(one, against: to),"Views must be the same size")
    switch (one.type, to.type, resultsIn.type) {
    case (.f,.f,.f):
        vsip_vmul_f(one.vsip, to.vsip, resultsIn.vsip)
    case (.f,.cf, .cf):
        vsip_rcvmul_f(one.vsip, to.vsip, resultsIn.vsip)
    case (.d, .d,.d):
        vsip_vmul_d(one.vsip, to.vsip, resultsIn.vsip)
    case (.d, .cd, .cd):
        vsip_rcvmul_d(one.vsip, to.vsip, resultsIn.vsip)
    case (.cf, .cf, .cf):
        vsip_cvmul_f(one.vsip, to.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_cvmul_d(one.vsip, to.vsip, resultsIn.vsip)
    case (.i, .i, .i):
        vsip_vmul_d(one.vsip, to.vsip, resultsIn.vsip)
    case (.li, .li, .li):
        vsip_vmul_li(one.vsip, to.vsip, resultsIn.vsip)
    case (.uc,.uc,.uc):
        vsip_vmul_uc(one.vsip, to.vsip, resultsIn.vsip)
    case (.si,.si,.si):
        vsip_vmul_si(one.vsip, to.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views")
    }
}
public  func mul(_ one: Matrix, _ to: Matrix, resultsIn: Matrix) {
    assert(sizeEqual(one, against: to),"Views must be the same size")
    switch (one.type, to.type, resultsIn.type) {
    case (.f, .f, .f):
        vsip_mmul_f(one.vsip, to.vsip, resultsIn.vsip)
    case (.f, .cf, .cf):
        vsip_rcmmul_f(one.vsip, to.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_mmul_d(one.vsip, to.vsip, resultsIn.vsip)
    case (.f, .cd, .cd):
        vsip_rcmmul_d(one.vsip, to.vsip, resultsIn.vsip)
    case (.cf, .cf, .cf):
        vsip_cmmul_f(one.vsip, to.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_cmmul_d(one.vsip, to.vsip, resultsIn.vsip)
    default:
        preconditionFailure("function not supported for input/resultsIn views")
    }
}
public  func mul(_ scalar: Double, _ vector: Vector, resultsIn: Vector){
    mul(Scalar(scalar), vector, resultsIn: resultsIn)
}
public  func mul(_ scalar: Float, _ vector: Vector, resultsIn: Vector){
    mul(Scalar(scalar), vector, resultsIn: resultsIn)
}
public  func mul(_ scalar: Int, _ vector: Vector, resultsIn: Vector){
    mul(Scalar(scalar), vector, resultsIn: resultsIn)
}
public  func mul(_ scalar: Scalar,_ vector: Vector, resultsIn: Vector){
    assert(sizeEqual(vector, against: resultsIn), "View sizes must be the same")
    let t = (scalar.type, vector.type, resultsIn.type)
    switch t {
    case (.f, .f, .f):
        vsip_svmul_f(scalar.vsip_f, vector.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_svmul_d(scalar.vsip_d, vector.vsip, resultsIn.vsip)
    case (.f, .cf, .cf):
        vsip_rscvmul_f(scalar.vsip_f, vector.vsip, resultsIn.vsip)
    case (.d, .cd, .cd):
        vsip_rscvmul_d(scalar.vsip_d, vector.vsip, resultsIn.vsip)
    case (.cf, .cf, .cf):
        vsip_csvmul_f(scalar.vsip_cf, vector.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_csvmul_d(scalar.vsip_cd, vector.vsip, resultsIn.vsip)
    case (.i, .i, .i):
        vsip_svmul_i(scalar.vsip_i, vector.vsip, resultsIn.vsip)
    case (.li, .li, .li):
        vsip_svmul_li(scalar.vsip_li, vector.vsip, resultsIn.vsip)
    case (.si, .si, .si):
        vsip_svmul_si(scalar.vsip_si, vector.vsip, resultsIn.vsip)
    case (.uc, .uc, .uc):
        vsip_svmul_uc(scalar.vsip_uc, vector.vsip, resultsIn.vsip)
    default:
        preconditionFailure("Argument string not supported for svmul")
    }
    
}
public  func mul(_ scalar: Double, _ matrix: Matrix, resultsIn: Matrix){
    mul(Scalar(scalar), matrix, resultsIn: resultsIn)
    
}
public  func mul(_ scalar: Float, _ matrix: Matrix, resultsIn: Matrix){
    mul(Scalar(scalar), matrix, resultsIn: resultsIn)
    
}
public  func mul(_ scalar: Scalar,_ matrix: Matrix, resultsIn: Matrix){
    assert(sizeEqual(matrix, against: resultsIn),"Views must be the same size")
    let t = (scalar.type, matrix.type, resultsIn.type)
    switch t {
    case (.f, .f, .f):
        vsip_smmul_f(scalar.vsip_f, matrix.vsip, resultsIn.vsip)
    case (.d, .d, .d):
        vsip_smmul_d(scalar.vsip_d, matrix.vsip, resultsIn.vsip)
    case (.f,.cf, .cf):
        vsip_rscmmul_f(scalar.vsip_f, matrix.vsip, resultsIn.vsip)
    case (.d, .cd, .cd):
        vsip_rscmmul_d(scalar.vsip_d, matrix.vsip, resultsIn.vsip)
    case (.cd, .cd, .cd):
        vsip_csmmul_d(scalar.vsip_cd, matrix.vsip, resultsIn.vsip)
    case (.cf, .cf, .cf):
        vsip_csmmul_f(scalar.vsip_cf, matrix.vsip, resultsIn.vsip)
    default:
        preconditionFailure("Argument string not supported for mul")
    }
    
}
public  func vmmul(vector: Vector, matrix: Matrix, major: vsip_major, resultsIn: Matrix){
    let vsipVec = vector.vsip
    let vsipMat = matrix.vsip
    let vsipOut = resultsIn.vsip
    let t = (vector.type, matrix.type, resultsIn.type)
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
        preconditionFailure("Argument list not supported for vmmul")
    }
}
public  func sub(_ aView: Vector, subtract: Vector, resultsIn: Vector){
    assert(sizeEqual(aView, against: subtract),"Views must be the same size")
    assert(sizeEqual(aView, against: resultsIn), "Views must be the same size")
    let t = (aView.type, subtract.type, resultsIn.type)
    switch t{
    case (.cd, .d, .cd):
        vsip_crvsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.cf, .f, .cf):
        vsip_crvsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.cd, .cd, .cd):
        vsip_cvsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.cf, .cf, .cf):
        vsip_cvsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.d, .cd, .cd):
        vsip_rcvsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.f, .cf, .cf):
        vsip_rcvsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.d, .d, .d):
        vsip_vsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.f, .f, .f):
        vsip_vsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.i, .i, .i):
        vsip_vsub_i (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.li, .li, .li):
        vsip_vsub_li (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.si, .si, .si):
        vsip_vsub_si (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.uc, .uc, .uc):
        vsip_vsub_uc (aView.vsip,subtract.vsip,resultsIn.vsip )
    default:
        preconditionFailure("function not supported for input/resultsIn views")
    }
}
public  func sub(_ aView: Matrix, subtract: Matrix, resultsIn: Matrix){
    assert(sizeEqual(aView, against: subtract),"Views must be the same size")
    assert(sizeEqual(aView, against: resultsIn), "Views must be the same size")
    let t = (aView.type, subtract.type, resultsIn.type)
    switch t{
    case (.cd, .cd, .cd):
        vsip_cmsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.cf, .cf, .cf):
        vsip_cmsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.cd, .d, .cd):
        vsip_crmsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.cf, .f, .cf):
        vsip_crmsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.si, .si, .si):
        vsip_msub_si (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.d, .cd, .cd):
        vsip_rcmsub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.d, .d, .d):
        vsip_msub_d (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.f, .f, .f):
        vsip_msub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.i, .i, .i):
        vsip_msub_i (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.li, .li, .li):
        vsip_msub_li (aView.vsip,subtract.vsip,resultsIn.vsip )
    case (.f, .cf, .cf):
        vsip_rcmsub_f (aView.vsip,subtract.vsip,resultsIn.vsip )
    default:
        preconditionFailure("function not supported for input/resultsIn views \(t)")
    }
}
// Mark: - Random
public class Rand {
    fileprivate var tryVsip : OpaquePointer?
    var vsip: OpaquePointer {
        get {
            return tryVsip!
        }
    }
    let jInit : JVSIP
    var myId : NSNumber?
    public init(seed: vsip_index, numberOfSubSequences: vsip_index, mySequence: vsip_index, portable: Bool){
        let rng = portable ? VSIP_PRNG : VSIP_NPRNG
        let id = mySequence
        let numprocs = numberOfSubSequences
        if let randObj = vsip_randcreate(seed, numprocs, id, rng){
            tryVsip = randObj
        } else {
            preconditionFailure("Failed to create vsip rand object")
        }
        jInit = JVSIP()
        myId = jInit.myId
    }
    public convenience init(seed: vsip_index, portable: Bool){
        self.init(seed: seed, numberOfSubSequences: 1, mySequence: 1, portable: portable)
    }
    public func randu(_ view: Vector){
        let t = view.type
        switch t{
        case .f:
            vsip_vrandu_f(self.vsip,view.vsip)
        case .d:
            vsip_vrandu_d(self.vsip,view.vsip)
        case .cf:
            vsip_cvrandu_f(self.vsip,view.vsip)
        case .cd:
            vsip_cvrandu_d(self.vsip,view.vsip)
        default:
            preconditionFailure("Type \(t) not defined for randu")
        }
    }
    public func randu(_ view: Matrix){
        let t = view.type
        switch t {
        case .f:
            vsip_mrandu_f(self.vsip,view.vsip)
        case .d:
            vsip_mrandu_d(self.vsip,view.vsip)
        case .cf:
            vsip_cmrandu_f(self.vsip,view.vsip)
        case .cd:
            vsip_cmrandu_d(self.vsip,view.vsip)
        default:
            preconditionFailure("Type \(t) not defined for randu")
        }
    }
    public func randn(_ view: Vector) {
        let t = view.type
        switch t{
        case .f:
            vsip_vrandn_f(self.vsip,view.vsip)
        case .d:
            vsip_vrandn_d(self.vsip,view.vsip)
        case .cf:
            vsip_cvrandn_f(self.vsip,view.vsip)
        case .cd:
            vsip_cvrandn_d(self.vsip,view.vsip)
        default:
            preconditionFailure("Type \(t) not defined for randn")
        }
    }
    public func randn(_ view: Matrix) {
        let t = view.type
        switch t{
        case .f:
            vsip_mrandn_f(self.vsip,view.vsip)
        case .d:
            vsip_mrandn_d(self.vsip,view.vsip)
        case .cf:
            vsip_cmrandn_f(self.vsip,view.vsip)
        case .cd:
            vsip_cmrandn_d(self.vsip,view.vsip)
        default:
            preconditionFailure("Type \(t) not defined for randn")
        }
    }
    deinit{
        let id = self.myId?.int32Value
        vsip_randdestroy(self.vsip)
        if _isDebugAssertConfiguration(){
            print("randdestroy id \(id!)")
        }
    }
    
}
// MARK: - Element Generation and Copy
public  func copy(from: Matrix, to: Matrix) {
    let t = (from.type, to.type)
    switch t{
    case (.f, .f):
        vsip_mcopy_f_f(from.vsip, to.vsip)
    case (.f, .d):
        vsip_mcopy_f_d(from.vsip, to.vsip)
    case (.d, .f):
        vsip_mcopy_d_f(from.vsip, to.vsip)
    case(.d, .d):
        vsip_mcopy_d_d(from.vsip, to.vsip)
    case (.cf, .cf):
        vsip_cmcopy_f_f(from.vsip, to.vsip)
    case (.cf, .cd):
        vsip_cmcopy_f_d(from.vsip, to.vsip)
    case (.cd, .cf):
        vsip_cmcopy_d_f(from.vsip, to.vsip)
    case(.cd, .cd):
        vsip_cmcopy_d_d(from.vsip, to.vsip)
    case(.i, .i):
        vsip_mcopy_i_i(from.vsip, to.vsip)
    case(.f, .i):
        vsip_mcopy_f_i(from.vsip, to.vsip)
    case(.i, .f):
        vsip_mcopy_f_i(from.vsip, to.vsip)
    case(.d, .i):
        vsip_mcopy_f_i(from.vsip, to.vsip)
    case(.i, .d):
        vsip_mcopy_f_i(from.vsip, to.vsip)
    default:
        preconditionFailure("Copy not supported for type \(t)")
    }
}
public  func copy(from: Vector, to: Vector) {
    let t = (from.type, to.type)
    switch t {
    case (.f, .f):
        vsip_vcopy_f_f(from.vsip, to.vsip)
    case (.f, .d):
        vsip_vcopy_f_d(from.vsip, to.vsip)
    case (.d, .f):
        vsip_vcopy_d_f(from.vsip, to.vsip)
    case(.d, .d):
        vsip_vcopy_d_d(from.vsip, to.vsip)
    case (.cf, .cf):
        vsip_cvcopy_f_f(from.vsip, to.vsip)
    case (.cf, .cd):
        vsip_cvcopy_f_d(from.vsip, to.vsip)
    case (.cd, .cf):
        vsip_cvcopy_d_f(from.vsip, to.vsip)
    case(.cd, .cd):
        vsip_cvcopy_d_d(from.vsip, to.vsip)
    case(.i, .i):
        vsip_vcopy_i_i(from.vsip, to.vsip)
    case(.f, .i):
        vsip_vcopy_f_i(from.vsip, to.vsip)
    case(.i, .f):
        vsip_vcopy_f_i(from.vsip, to.vsip)
    case(.d, .i):
        vsip_vcopy_f_i(from.vsip, to.vsip)
    case(.i, .d):
        vsip_vcopy_f_i(from.vsip, to.vsip)
    default:
        preconditionFailure("Copy not supported for type \(t)")
    }
}

// MARK: - Linear Algebra Matrix and Vector Operations
public  func herm(_ complexInputMatrix: Matrix, output: Matrix){
    let vsipA = complexInputMatrix.vsip
    let vsipB = output.vsip
    let t = (complexInputMatrix.type, output.type)
    switch t {
    case (.cf, .cf):
        vsip_cmherm_f(vsipA, vsipB)
    case (.cd, .cd):
        vsip_cmherm_d(vsipA, vsipB)
    default:
        preconditionFailure("Type not supported for herm")
    }
}
public  func jdot(_ complexInputVector: Vector,dot complexOuputVector: Vector) -> Scalar {
    let vsipA = complexInputVector.vsip
    let vsipB = complexOuputVector.vsip
    let t = (complexInputVector.type, complexInputVector.type)
    switch t {
    case (.cf, .cf):
        return Scalar(vsip_cvjdot_f(vsipA, vsipB))
    case (.cd, .cd):
        return Scalar(vsip_cvjdot_d(vsipA, vsipB))
    default:
        preconditionFailure("Type not supported for jdot")
    }
}
public  func gemp(alpha: Scalar, matA: Matrix, opA: vsip_mat_op, matB: Matrix, opB: vsip_mat_op, beta: Scalar, matC: Matrix) {
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
    switch(t){
    case (.d, .d, .d):
        vsip_gemp_d(alpha.reald, vsipA, opA, vsipB, opB, beta.reald, vsipC)
    case (.f, .f, .f):
        vsip_gemp_f(alpha.realf, vsipA, opA, vsipB, opB, beta.realf, vsipC)
    case (.cd, .cd, .cd):
        vsip_cgemp_d(alpha.vsip_cd, vsipA, opA, vsipB, opB, beta.vsip_cd, vsipC)
    case (.cf, .cf, .cf):
        vsip_cgemp_f(alpha.vsip_cf, vsipA, opA, vsipB, opB, beta.vsip_cf, vsipC)
    default:
        preconditionFailure("Type not supported for gemp")
    }
    
}
public  func gems(alpha: Scalar, matA: Matrix, opA: vsip_mat_op, beta: Scalar, matC: Matrix){
    let t = (matA.type,  matC.type)
    let vsipA = matA.vsip
    let vsipC = matC.vsip
    switch(t){
    case (.d, .d):
        vsip_gems_d(alpha.reald, vsipA, opA, beta.reald, vsipC)
    case (.f, .f):
        vsip_gems_f(alpha.realf, vsipA, opA, beta.realf, vsipC)
    case (.cd, .cd):
        vsip_cgems_d(alpha.vsip_cd, vsipA, opA, beta.vsip_cd, vsipC)
    case (.cf, .cf):
        vsip_cgems_f(alpha.vsip_cf, vsipA, opA, beta.vsip_cf, vsipC)
    default:
        preconditionFailure("Type not supported for gemp")
    }
}
public  func kron(alpha: Scalar, vecX: Vector, vecY: Vector, resutltsIn matC: Matrix){
    let t = (vecX.type, vecY.type, matC.type)
    let vsipX = vecX.vsip
    let vsipY = vecY.vsip
    let vsipC = matC.vsip
    switch(t){
    case (.f, .f, .f):
        vsip_vkron_f(alpha.realf, vsipX, vsipY, vsipC)
    case (.d, .d, .d):
        vsip_vkron_d(alpha.reald, vsipX, vsipY, vsipC)
    case (.cf, .cf, .cf):
        vsip_cvkron_f(alpha.vsip_cf, vsipX, vsipY, vsipC)
    case (.cd, .cd, .cd):
        vsip_cvkron_d(alpha.vsip_cd, vsipX, vsipY, vsipC)
    default:
        preconditionFailure("Kron not supported for argument list")
    }
}
public  func kron(alpha: Scalar, matA: Matrix, matB: Matrix, resutltsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
    switch(t){
    case (.f, .f, .f):
        vsip_mkron_f(alpha.realf, vsipA, vsipB, vsipC)
    case (.d, .d, .d):
        vsip_mkron_d(alpha.reald, vsipA, vsipB, vsipC)
    case (.cf, .cf, .cf):
        vsip_cmkron_f(alpha.vsip_cf, vsipA, vsipB, vsipC)
    case (.cd, .cd, .cd):
        vsip_cmkron_d(alpha.vsip_cd, vsipA, vsipB, vsipC)
    default:
        preconditionFailure("Kron not supported for argument list")
    }
}
public  func prod3(_ matA: Matrix,times matB: Matrix, resutltsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
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
        preconditionFailure("VSIP function prod3 not supported for argument list")
    }
}
public  func prod3(_ matA: Matrix,times  vecB: Vector, resutltsIn  vecC: Vector){
    let t = (matA.type, vecB.type, vecC.type)
    let vsipA = matA.vsip
    let vsipB = vecB.vsip
    let vsipC = vecC.vsip
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
        preconditionFailure("VSIP function prod4 not supported for argument list")
    }
}
public  func prod4(_ matA: Matrix, times matB: Matrix, resutltsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
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
        preconditionFailure("VSIP function prod4 not supported for argument list")
    }
}
public  func prod4(_ matA: Matrix, times vecB: Vector, resutltsIn vecC: Vector){
    let t = (matA.type, vecB.type, vecC.type)
    let vsipA = matA.vsip
    let vsipB = vecB.vsip
    let vsipC = vecC.vsip
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
        preconditionFailure("VSIP function prod4 not supported for argument list")
    }
}

public  func prod(_ matA: Matrix,times matB: Matrix,resultsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
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
        preconditionFailure("VSIP function prod not supported for argument list")
    }
}
public  func prod(_ matA: Matrix, times vecB: Vector,resultsIn vecC: Vector){
    let t = (matA.type, vecB.type, vecC.type)
    let vsipA = matA.vsip
    let vsipB = vecB.vsip
    let vsipC = vecC.vsip
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
        preconditionFailure("VSIP function prod not supported for argument list")
    }
}
public  func prod(_ vecA: Vector, times matB: Matrix, resultsIn vecC: Vector){
    let t = (vecA.type, matB.type, vecC.type)
    let vsipA = vecA.vsip
    let vsipB = matB.vsip
    let vsipC = vecC.vsip
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
        preconditionFailure("VSIP function prod not supported for argument list")
    }
}
public  func prodh(_ matA: Matrix,timesHermitian matB: Matrix, resultsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
    switch(t){
    case (.cd, .cd, .cd):
        vsip_cmprodh_d ( vsipA, vsipB, vsipC )
    case (.cf, .cf, .cf):
        vsip_cmprodh_f ( vsipA, vsipB, vsipC )
    default:
        preconditionFailure("VSIP function prodh not supported for argument list")
    }
}
public  func prodj(_ matA: Matrix, timesConjugate matB: Matrix, resultsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
    switch(t){
    case (.cd, .cd, .cd):
        vsip_cmprodj_d ( vsipA, vsipB, vsipC )
    case (.cf, .cf, .cf):
        vsip_cmprodj_f ( vsipA, vsipB, vsipC )
    default:
        preconditionFailure("VSIP function prodj not supported for argument list")
    }
}
public  func prodt(_ matA: Matrix,timesTranspose matB: Matrix, resultsIn matC: Matrix){
    let t = (matA.type, matB.type, matC.type)
    let vsipA = matA.vsip
    let vsipB = matB.vsip
    let vsipC = matC.vsip
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
        preconditionFailure("VSIP function prodt not supported for argument list")
    }
}
public  func trans(_ matA: Matrix, transposeIn matC: Matrix){
    let t = (matA.type, matC.type)
    let vsipA = matA.vsip
    let vsipC = matC.vsip
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
        preconditionFailure("VSIP function trans not supported for argument list")
    }
}
public  func dot(product vecX: Vector, with vecY: Vector) -> Scalar {
    let t = (vecX.type, vecY.type)
    let vsipX = vecX.vsip
    let vsipY = vecY.vsip
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
        preconditionFailure("Kron not supported for argument list")
    }
}
public  func outer(alpha: Scalar, vecX: Vector, vecY: Vector, matC: Matrix){
    let vsipX = vecX.vsip
    let vsipY = vecY.vsip
    let vsipC = matC.vsip
    let t = (vecX.type, vecY.type, matC.type)
    switch(t){
    case (.f, .f, .f):
        vsip_vouter_f(alpha.realf, vsipX, vsipY, vsipC)
    case (.d, .d, .d):
        vsip_vouter_d(alpha.reald, vsipX, vsipY, vsipC)
    case (.cf, .cf, .cf):
        vsip_cvouter_f(alpha.vsip_cf, vsipX, vsipY, vsipC)
    case (.cd, .cd, .cd):
        vsip_cvouter_d(alpha.vsip_cd, vsipX, vsipY, vsipC)
    default:
        preconditionFailure("Function outer not supported for argument list")
    }
}
// Mark: - Simple Solvers
public  func covsol(_ A: Matrix, inputOutput: Matrix) -> Int {
    let t = (A.type, inputOutput.type)
    switch t {
    case (.f, .f):
        return Int(vsip_covsol_f(A.vsip, inputOutput.vsip))
    case (.d, .d):
        return Int(vsip_covsol_d(A.vsip, inputOutput.vsip))
    case (.cf, .cf):
        return Int(vsip_ccovsol_f(A.vsip, inputOutput.vsip))
    case (.cd, .cd):
        return Int(vsip_ccovsol_d(A.vsip, inputOutput.vsip))
    default:
        preconditionFailure("Type \(t) not supported by covsol")
    }
}

