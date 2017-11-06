
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
    public  func prod3(_ matA: Matrix,prod matB: Matrix, resutltsIn matC: Matrix){
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
    public  func prod3(_ matA: Matrix,prod  vecB: Vector, resutltsIn  vecC: Vector){
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
    public  func prod4(_ matA: Matrix, prod matB: Matrix, resutltsIn matC: Matrix){
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
    public  func prod4(_ matA: Matrix, prod vecB: Vector, resutltsIn vecC: Vector){
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
    
    public  func prod(_ matA: Matrix,prod matB: Matrix,resultsIn matC: Matrix){
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
    // MARK: - Chold
    public class Chold {
        var size: Int
        var type: Scalar.Types {
            return (jVsip?.type)!
        }
        fileprivate var vsip: OpaquePointer {
            get {
                return (jVsip?.vsip)!
            }
        }
        fileprivate class chol {
            var tryVsip : OpaquePointer?
            var vsip: OpaquePointer {
                get {
                    return tryVsip!
                }
            }
            let jInit : JVSIP
            var type : Scalar.Types?
            init(){
                jInit = JVSIP()
            }
        }
        fileprivate class chol_d: chol {
            init(size: Int){
                super.init()
                self.type = .d
                if let chold = vsip_chold_create_d(VSIP_TR_LOW, vsip_length(size)){
                    self.tryVsip = chold
                } else {
                    preconditionFailure("Failed to create vsip cholesky object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_chold_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_chold_destroy_d(self.vsip)
                
            }
        }
        fileprivate class chol_f: chol {
            init(size: Int){
                super.init()
                self.type = .f
                if let chold = vsip_chold_create_f(VSIP_TR_LOW, vsip_length(size)){
                    self.tryVsip = chold
                } else {
                    preconditionFailure("Failed to create vsip cholesky object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_chold_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_chold_destroy_f(self.vsip)
                
            }
        }
        fileprivate class chol_cd: chol {
            init(size: Int){
                super.init()
                self.type = .cd
                if let chold = vsip_cchold_create_d(VSIP_TR_LOW, vsip_length(size)){
                    self.tryVsip = chold
                } else {
                    preconditionFailure("Failed to create vsip cholesky object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_cchold_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_cchold_destroy_d(self.vsip)
                
            }
        }
        fileprivate class chol_cf: chol {
            init(size: Int){
                super.init()
                self.type = .cf
                if let chold = vsip_cchold_create_f(VSIP_TR_LOW, vsip_length(size)){
                    self.tryVsip = chold
                } else {
                    preconditionFailure("Failed to create vsip cholesky object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_cchold_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_cchold_destroy_f(self.vsip)
            }
        }
        fileprivate let jVsip : chol?
        init(type: Scalar.Types, size: Int) {
            self.size = size
            switch type {
            case .f:
                self.jVsip = chol_f(size: size)
            case .d:
                self.jVsip = chol_d(size: size)
            case .cf:
                self.jVsip = chol_cf(size: size)
            case .cd:
                self.jVsip = chol_cd(size: size)
            default:
                preconditionFailure ("type \(type) not found for cholesky decomposition")
            }
        }
        public func decompose(_ A: Matrix) -> Int {
            let t = (self.type, A.type)
            switch t {
            case (.f, .f):
                return Int(vsip_chold_f(self.vsip, A.vsip))
            case (.d, .d):
                return Int(vsip_chold_d(self.vsip, A.vsip))
            case (.cf, .cf):
                return Int(vsip_cchold_f(self.vsip, A.vsip))
            case (.cd, .cd):
                return Int(vsip_cchold_d(self.vsip, A.vsip))
            default:
                preconditionFailure("Type \(t) not supported for cholesky decompostion")
            }
        }
        public func solve(_ XB: Matrix) -> Int {
            let t = (self.type, XB.type)
            switch t {
            case (.f, .f):
                return Int(vsip_cholsol_f(self.vsip, XB.vsip))
            case (.d, .d):
                return Int(vsip_cholsol_d(self.vsip, XB.vsip))
            case (.cf, .cf):
                return Int(vsip_ccholsol_f(self.vsip, XB.vsip))
            case (.cd, .cd):
                return Int(vsip_ccholsol_d(self.vsip, XB.vsip))
            default:
                preconditionFailure ("type \(type) not found for cholesky decomposition")
            }
        }
    }
    // MARK: - LU
    public class LUD {
        var type: Scalar.Types {
            return (jVsip?.type)!
        }
        fileprivate class lu {
            var tryVsip : OpaquePointer?
            var vsip: OpaquePointer {
                get {
                    return tryVsip!
                }
            }
            let jInit : JVSIP
            var type : Scalar.Types?
            init(){
                jInit = JVSIP()
            }
        }
        fileprivate class lu_f: lu{
            init(_ size: Int){
                super.init()
                type = .f
                if let lud = vsip_lud_create_f(vsip_length(size)){
                    self.tryVsip = lud
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_lud_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_lud_destroy_f(self.vsip)
            }
        }
        fileprivate class lu_d: lu{
            init(_ size: Int){
                super.init()
                type = .d
                if let lud = vsip_lud_create_d(vsip_length(size)){
                    self.tryVsip = lud
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_lud_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_lud_destroy_d(self.vsip)
            }
        }
        fileprivate class clu_f: lu{
            init(_ size: Int){
                super.init()
                type = .cf
                if let lud = vsip_clud_create_f(vsip_length(size)){
                    self.tryVsip = lud
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_clud_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_clud_destroy_f(self.vsip)
            }
        }
        fileprivate class clu_d: lu{
            init(_ size: Int){
                super.init()
                type = .cd
                if let lud = vsip_clud_create_d(vsip_length(size)){
                    self.tryVsip = lud
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_clud_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_clud_destroy_d(self.vsip)
            }
        }
        fileprivate let jVsip : lu?
        fileprivate var vsip: OpaquePointer {
            get {
                return (jVsip?.vsip)!
            }
        }
        init(type: Scalar.Types, size: Int) {
            switch type {
            case .f:
                jVsip = lu_f(size)
            case .d:
                jVsip = lu_d(size)
            case .cf:
                jVsip = clu_f(size)
            case .cd:
                jVsip = clu_d(size)
            default:
                preconditionFailure("Type \(type) not supported")
            }
        }
        public func decompose(_ A: Matrix) -> Int{
            let t = (self.type, A.type)
            switch t{
            case (.f, .f):
                return Int(vsip_lud_f(self.vsip, A.vsip))
            case (.d, .d):
                return Int(vsip_lud_d(self.vsip, A.vsip))
            case (.cf, .cf):
                return Int(vsip_clud_f(self.vsip, A.vsip))
            case (.cd, .cd):
                return Int(vsip_clud_d(self.vsip, A.vsip))
            default:
                preconditionFailure("Type \(t) not found for lud decompose")
            }
        }
        public func solve(matOp: vsip_mat_op, _ XB: Matrix) -> Int{
            let t = (matOp, self.type, XB.type)
            switch t {
            case (VSIP_MAT_NTRANS,.f,.f):
                return Int(vsip_lusol_f(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
            case (VSIP_MAT_NTRANS,.d,.d):
                return Int(vsip_lusol_d(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
            case (VSIP_MAT_NTRANS,.cf,.cf):
                return Int(vsip_clusol_f(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
            case (VSIP_MAT_NTRANS,.cd,.cd):
                return Int(vsip_clusol_d(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
            case (VSIP_MAT_TRANS,.f,.f):
                return Int(vsip_lusol_f(self.vsip, VSIP_MAT_TRANS, XB.vsip))
            case (VSIP_MAT_TRANS,.d,.d):
                return Int(vsip_lusol_d(self.vsip, VSIP_MAT_TRANS, XB.vsip))
            case (VSIP_MAT_HERM,.cf,.cf):
                return Int(vsip_clusol_f(self.vsip, VSIP_MAT_HERM, XB.vsip))
            case (VSIP_MAT_HERM,.cd,.cd):
                return Int(vsip_clusol_d(self.vsip, VSIP_MAT_HERM, XB.vsip))
            default:
                preconditionFailure("Type \(t) not found for lud solve")
            }
        }
        
    }
    
    // MARK: - QRD
    public class QRD{
        fileprivate struct Attrib {
            let m: Int
            let n: Int
            let op: vsip_qrd_qopt
        }
        var type: Scalar.Types {
            return (jVsip?.type)!
        }
        fileprivate(set) var amSet = false
        fileprivate let attrib: Attrib
        var columnLength: Int {
            get{
                return attrib.m
            }
        }
        var rowLength: Int {
            get {
                return attrib.n
            }
        }
        var qrdNoSaveQ: Bool{
            get {
                return attrib.op == VSIP_QRD_NOSAVEQ
            }
        }
        var qrdSaveQ: Bool{
            get {
                return attrib.op == VSIP_QRD_SAVEQ
            }
        }
        var qrdSaveQ1: Bool{
            get {
                return attrib.op == VSIP_QRD_SAVEQ1
            }
        }
        fileprivate class qr {
            var tryVsip : OpaquePointer?
            var vsip: OpaquePointer {
                get {
                    return tryVsip!
                }
            }
            let jInit : JVSIP
            var type : Scalar.Types?
            init(){
                jInit = JVSIP()
            }
            
        }
        fileprivate class qr_f: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .f
                if let qrd = vsip_qrd_create_f(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_qrd_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_qrd_destroy_f(self.vsip)
                
            }
        }
        fileprivate class qr_d: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .d
                if let qrd = vsip_qrd_create_d(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_qrd_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_qrd_destroy_d(self.vsip)
                
            }
        }
        fileprivate class cqr_f: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .cf
                if let qrd = vsip_cqrd_create_f(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_cqrd_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_cqrd_destroy_f(self.vsip)
                
            }
        }
        fileprivate class cqr_d: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .cd
                if let qrd = vsip_cqrd_create_d(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_cqrd_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_cqrd_destroy_d(self.vsip)
                
            }
        }
        fileprivate let jVsip : qr?
        fileprivate var vsip: OpaquePointer {
            get {
                return (jVsip?.vsip)!
            }
        }
        init(type: Scalar.Types, columnLength: Int, rowLength: Int, qopt: vsip_qrd_qopt) {
            attrib = Attrib(m: columnLength, n: rowLength, op: qopt)
            self.amSet = false
            switch type {
            case .f:
                jVsip = qr_f(m: columnLength, n: rowLength, qopt: qopt)
            case .d:
                jVsip = qr_d(m: columnLength, n: rowLength, qopt: qopt)
            case .cf:
                jVsip = cqr_f(m: columnLength, n: rowLength, qopt: qopt)
            case .cd:
                jVsip = cqr_d(m: columnLength, n: rowLength, qopt: qopt)
            default:
                self.jVsip = nil
                assert(false, "QRD not supported for this type")
            }
        }
        
        public func decompose(_ aMatrix: Matrix) -> Scalar {
            let t = (aMatrix.type, self.type)
            switch t {
            case(.f,.f):
                return Scalar(vsip_qrd_f(self.vsip, aMatrix.vsip))
            case(.d,.d):
                return Scalar(vsip_qrd_d(self.vsip, aMatrix.vsip))
            case(.cf,.cf):
                return Scalar(vsip_cqrd_f(self.vsip, aMatrix.vsip))
            case(.cd,.cd):
                return Scalar(vsip_cqrd_d(self.vsip, aMatrix.vsip))
            default:
                preconditionFailure("Types \(t) not supported for qrd decompostion")
            }
        }
        public func prodq(matrixOperator op: vsip_mat_op, matrixSide side: vsip_mat_side, matrix: Matrix) {
            let t = (self.type, op, side, matrix.type)
            switch t{
            case (.f, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.f, VSIP_MAT_TRANS, VSIP_MAT_LSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_TRANS, VSIP_MAT_LSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_HERM, VSIP_MAT_LSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_HERM, VSIP_MAT_LSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.f, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.f, VSIP_MAT_TRANS, VSIP_MAT_RSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_TRANS, VSIP_MAT_RSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_HERM, VSIP_MAT_RSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_HERM, VSIP_MAT_RSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            default:
                preconditionFailure("Type \(t) not supported for QRD prodq.")
            }
        }
        public func solveR(matrixOperator opR: vsip_mat_op, alpha: Scalar, XB: Matrix) -> Int {
            let t = (opR, XB.type)
            switch t {
            case (VSIP_MAT_NTRANS, .f):
                return Int(vsip_qrdsolr_f(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_f, XB.vsip))
            case (VSIP_MAT_TRANS, .f):
                return Int(vsip_qrdsolr_f(self.vsip, VSIP_MAT_TRANS, alpha.vsip_f, XB.vsip))
            case (VSIP_MAT_NTRANS, .d):
                return Int(vsip_qrdsolr_d(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_d, XB.vsip))
            case (VSIP_MAT_TRANS, .f):
                return Int(vsip_qrdsolr_d(self.vsip, VSIP_MAT_TRANS, alpha.vsip_d, XB.vsip))
            case (VSIP_MAT_NTRANS, .cf):
                return Int(vsip_cqrdsolr_f(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_cf, XB.vsip))
            case (VSIP_MAT_TRANS, .cf):
                return Int(vsip_cqrdsolr_f(self.vsip, VSIP_MAT_HERM, alpha.vsip_cf, XB.vsip))
            case (VSIP_MAT_NTRANS, .d):
                return Int(vsip_cqrdsolr_d(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_cd, XB.vsip))
            case (VSIP_MAT_TRANS, .f):
                return Int(vsip_cqrdsolr_d(self.vsip, VSIP_MAT_HERM, alpha.vsip_cd, XB.vsip))
            default:
                preconditionFailure("Case \(t) not found for solveR")
            }
        }
        public func solveCovariance(solveProblem prob: vsip_qrd_prob, XB: Matrix) -> Int {
            let t = (prob, XB.type)
            switch t {
            case (VSIP_COV, .f):
                return Int(vsip_qrsol_f(self.vsip, VSIP_COV, XB.vsip))
            case (VSIP_LLS, .f):
                return Int(vsip_qrsol_f(self.vsip, VSIP_LLS, XB.vsip))
            case (VSIP_COV, .d):
                return Int(vsip_qrsol_d(self.vsip, VSIP_COV, XB.vsip))
            case (VSIP_LLS, .d):
                return Int(vsip_qrsol_d(self.vsip, VSIP_LLS, XB.vsip))
            case (VSIP_COV, .cf):
                return Int(vsip_cqrsol_f(self.vsip, VSIP_COV, XB.vsip))
            case (VSIP_LLS, .cf):
                return Int(vsip_cqrsol_f(self.vsip, VSIP_LLS, XB.vsip))
            case (VSIP_COV, .cd):
                return Int(vsip_cqrsol_d(self.vsip, VSIP_COV, XB.vsip))
            case (VSIP_LLS, .cd):
                return Int(vsip_cqrsol_d(self.vsip, VSIP_LLS, XB.vsip))
            default:
                preconditionFailure("Case \(t) not found for Covariance/LeastSquare solver")
            }
        }
        
    }
    
    // MARK: - SVD
    // needs work on error checks
    /*!
     For SVD given input matrix A we have
     A = U S transpose(V)
     */
    public class Svd {
        let type: Scalar.Types
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
            var tryVsip : OpaquePointer?
            var tryS: OpaquePointer?
            var vsip: OpaquePointer {
                get {
                    return tryVsip!
                }
            }
            var s: OpaquePointer {
                get {
                    return tryS!
                }
            }
            let jInit : JVSIP
            var type : Scalar.Types?
            init(){
                jInit = JVSIP()
            }
        }
        fileprivate class sv_f : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .f
                if let svd = vsip_svd_create_f(vsip_length(m),vsip_length(n),saveU,saveV){
                    self.tryVsip = svd
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
                if let s = vsip_vcreate_f(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                    self.tryS = s
                } else {
                    preconditionFailure("Failed to create vsip s object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_svd_destroy_f \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_svd_destroy_f(self.vsip)
                vsip_valldestroy_f(self.s)
            }
        }
        fileprivate class sv_d : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .f
                if let svd = vsip_svd_create_d(vsip_length(m),vsip_length(n),saveU,saveV){
                    self.tryVsip = svd
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
                if let s = vsip_vcreate_d(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                    self.tryS = s
                } else {
                    preconditionFailure("Failed to create vsip s object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_svd_destroy_d \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_svd_destroy_d(self.vsip)
                vsip_valldestroy_d(self.s)
            }
        }
        fileprivate class csv_f : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .cf
                if let svd = vsip_csvd_create_f(vsip_length(m),vsip_length(n),saveU,saveV){
                    self.tryVsip = svd
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
                if let s = vsip_vcreate_f(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                    self.tryS = s
                } else {
                    preconditionFailure("Failed to create vsip s object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_svd_destroy_f \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_csvd_destroy_f(self.vsip)
                vsip_valldestroy_f(self.s)
            }
        }
        fileprivate class csv_d : sv {
            init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
                super.init()
                type = .cd
                if let svd = vsip_csvd_create_d(vsip_length(m),vsip_length(n),saveU,saveV){
                    self.tryVsip = svd
                } else {
                    preconditionFailure("Failed to create vsip svd object")
                }
                if let s = vsip_vcreate_d(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                    self.tryS = s
                } else {
                    preconditionFailure("Failed to create vsip s object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_csvd_destroy_cd \(jInit.myId.int32Value)")
                    print("svd s destroy")
                }
                vsip_csvd_destroy_d(self.vsip)
                vsip_valldestroy_d(self.s)
            }
        }
        
        public init(type: Scalar.Types,columnLength m: Int, rowLength n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
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
            self.init(type: view.type, columnLength: view.columnLength, rowLength: view.rowLength, saveU: saveU, saveV: saveV)
        }
        public convenience init(view: Matrix){
            self.init(type: view.type, columnLength: view.columnLength, rowLength: view.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
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
                vsip_svd_d(self.vsip, matrix.vsip, self.s!)
                vsip_vcopy_d_d(self.s!, singularValues.vsip)
            case (.f, .f, .f):
                vsip_svd_f(self.vsip, matrix.vsip, self.s!)
                vsip_vcopy_f_f(self.s!, singularValues.vsip)
            case (.cd, .cd, .d):
                vsip_csvd_d(self.vsip, matrix.vsip, self.s!)
                vsip_vcopy_d_d(self.s!, singularValues.vsip)
            case (.cf, .cf, .f):
                vsip_csvd_f(self.vsip, matrix.vsip, self.s!)
                vsip_vcopy_f_f(self.s!, singularValues.vsip)
            default:
                preconditionFailure("function not supported for input/resultsIn views")
            }
            self.amSet = true
        }
        public func decompose(_ matrix: Matrix) -> Vector {
            let v: Vector
            switch matrix.type {
            case .cd, .d:
                v = Vector(length: self.n, type: .d)
            case .cf, .f:
                v = Vector(length: self.n, type: .f)
            default:
                preconditionFailure("Case not found for decompose")
            }
            self.decompose(matrix, singularValues: v)
            return v
        }
        /*!
         Function matU returns 0 on success
         Output data is stored in matrix matU in natural order starting at
         element index (0,0). Matrix matU must be large enough to hold the
         resultsIn data
         */
        public func matU(_ lowColumn: Int, highColumn: Int, matU: Matrix) -> Int {
            let low = vsip_scalar_vi(lowColumn)
            let high = vsip_scalar_vi(highColumn)
            assert(low <= high, "Error in column selection")
            let highMax = vsip_scalar_vi((matU.rowLength))
            let vsipSv = self.vsip // VSIPL pointer to singular value object
            let vsipC = matU.vsip // VSIPL pointer to U Matrix
            
            switch (self.attr.saveU, matU.type, self.type){
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
                    preconditionFailure("SVD Created without U Matrix")
                } else {
                    preconditionFailure("SVD Not supported for these types")
                }
            }
        }
        /*!
         Function matV returns 0 on success
         Output data is stored in matrix matV in natural order starting at
         element index (0,0). Matrix matV must be large enough to hold the
         resultsIn data
         */
        public func matV(_ lowColumn: Int, highColumn: Int, matV: Matrix) -> Int {
            let low = vsip_scalar_vi(lowColumn)
            let high = vsip_scalar_vi(highColumn)
            assert(low <= high, "Error in column selection")
            let highMax = vsip_scalar_vi(matV.rowLength)
            let vsipSv = self.vsip // VSIPL pointer to singular value object
            let vsipC = matV.vsip // VSIPL pointer to V Matrix
            switch (self.attr.saveU, matV.type, self.type){
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
                    preconditionFailure("SVD Created without V Matrix")
                } else {
                    preconditionFailure("SVD Not supported for these types")
                }
            }
        }
        public func produ(op: vsip_mat_op, side: vsip_mat_side, matrix: Matrix) -> Int {
            let vsipSv = self.vsip
            let vsipC = matrix.vsip
            switch (self.attr.saveU, matrix.type, self.type){
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
                    preconditionFailure("SVD Created without U Matrix")
                } else {
                    preconditionFailure("SVD Not supported for these types")
                }
            }
        }
        public func prodv(op: vsip_mat_op, side: vsip_mat_side, matrix: Matrix) -> Int {
            let vsipSv = self.vsip
            let vsipC = matrix.vsip
            switch (self.attr.saveV, matrix.type, self.type){
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
                    preconditionFailure("SVD Created without V Matrix")
                } else {
                    preconditionFailure("SVD Not supported for these types")
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
