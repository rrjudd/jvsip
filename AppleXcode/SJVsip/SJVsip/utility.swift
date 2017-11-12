//
//  utility.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip

public func scalarString(_ format : String, value : Scalar) -> String{
    var retval = ""
    switch value.type{
    case .f:
        let fmt = "%" + format + "f"
        retval = String(format: fmt, value.realf)
    case .d:
        let fmt = "%" + format + "f"
        retval = String(format: fmt, value.reald)
    case .cf:
        let fmt1 = "%" + format + "f"
        let fmt2 = "%+" + format + "f"
        let r = String(format: fmt1, value.realf)
        let i = String(format: fmt2, value.imagf)
        retval = r + i + "i"
    case .cd:
        let fmt1 = "%" + format + "f"
        let fmt2 = "%+" + format + "f"
        let r = String(format: fmt1, value.reald)
        let i = String(format: fmt2, value.imagd)
        retval = r + i + "i"
    case .mi:
        let fmt1 = "(%d,"
        let fmt2 = " %d)"
        let r = String(format: fmt1, value.row)
        let c = String(format: fmt2, value.col)
        retval = r + c
    default:
        let fmt = "%d"
        retval = String(format: fmt, value.int)            }
    return retval
}
public func formatFmt(_ fmt: String) -> String{
    var retval = ""
    func charCheck(_ char: Character) -> Bool {
        let validChars = "0123456789."
        for item in validChars {
            if char == item {
                return true
            }
        }
        return false
    }
    for char in fmt{
        if charCheck(char){
            retval.append(char)
        }
    }
    return retval
}

public class SJvsip {
    public static func normFro(view: Vector) -> Scalar {
        switch view.type {
        case .f:
            return sumsqval(view).sqrt
        case .d:
            return sumsqval(view).sqrt
        case.cf:
            return (sumsqval(view.real) + sumsqval(view.imag)).sqrt
        case.cd:
            return (sumsqval(view.real) + sumsqval(view.imag)).sqrt
        default:
            preconditionFailure("normFro not supported for this view")
        }
    }
    public static func normFro(view: Matrix) -> Scalar {
        switch view.type {
        case .f:
            return sumsqval(view).sqrt
        case .d:
            return sumsqval(view).sqrt
        case.cf:
            return (sumsqval(view.real) + sumsqval(view.imag)).sqrt
        case.cd:
            return (sumsqval(view.real) + sumsqval(view.imag)).sqrt
        default:
            preconditionFailure("normFro not supported for this view")
        }
    }
}
