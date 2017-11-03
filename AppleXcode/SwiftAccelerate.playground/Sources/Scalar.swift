/// Scalar is a structure to allow generalized return of scalars from a view
//: To support the SwiftAccelerate framework we need a Scalar type to handle the various
//: atomic data types.
import Foundation
import Accelerate


func scalarString(_ format : String, value : Scalar) -> String{
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
    case .i:
        let fmt = "%d"
        retval = String(format: fmt, value.int)
    case .ui:
        let fmt = "%d"
        retval = String(format: fmt, value.int)
    }
    return retval
}
func formatFmt(_ fmt: String) -> String{
    var retval = ""
    func charCheck(_ char: Character) -> Bool {
        let validChars = "0123456789."
        for item in validChars.characters{
            if char == item {
                return true
            }
        }
        return false
    }
    for char in fmt.characters{
        if charCheck(char){
            retval.append(char)
        }
    }
    return retval
}
public struct Scalar {
    var value: (BlockTypes?, NSNumber?,  NSNumber?)
    public init(_ type: BlockTypes,_ valueOne: NSNumber?,_ valueTwo: NSNumber?){
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
    public init(_ value: Int32){
        self.value.0 = .i
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: UInt32){
        self.value.0 = .i
        self.value.1 = NSNumber(value: value)
        self.value.2 = nil
    }
    public init(_ value: DSPDoubleComplex){
        self.value.0 = .cd
        self.value.1 = NSNumber(value: value.real)
        self.value.2 = NSNumber(value: value.imag)
    }
    public init(_ value: DSPComplex){
        self.value.0 = .cf
        self.value.1 = NSNumber(value: value.real)
        self.value.2 = NSNumber(value: value.imag)
    }
    public var type: BlockTypes {
        return self.value.0!
    }
    public var realf: Float{
        return Float((value.1?.floatValue)!)
    }
    public var reald: Double{
        return Double((value.1?.doubleValue)!)
    }
    public var imagf: Float{
        if let i = value.2 {
            return Float(i)
        } else {
            return Float(0.0)
        }
    }
    public var imagd: Double{
        if let i = value.2 {
            return Double(i)
        } else {
            return Double(0.0)
        }
    }
    public var int: Int32{
        return Int32((value.1?.intValue)!)
    }
    public var rowIndex: UInt32{
        return UInt32((value.1?.intValue)!)
    }
    public var colIndex: UInt32{
        return UInt32((value.2?.intValue)!)
    }
    public var index: UInt32{
        return UInt32((value.1?.intValue)!)
    }
    public var length: UInt32{
        return UInt32((value.1?.intValue)!)
    }
    public var offset: UInt32{
        return self.length
    }
    public var stride: Int32{
        return self.int
    }
    public var cmplxf: DSPComplex {
        return DSPComplex(real: self.realf, imag: self.imagf)
    }
    public var cmplxd: DSPDoubleComplex{
        return DSPDoubleComplex(real: self.reald, imag: self.imagd)
    }
    
    public static func + (left: Scalar, right: Scalar) -> Scalar {
        switch (left.type, right.type) {
        case (.i, .i):
            return Scalar( left.int + right.int)
        case (.i, .f):
            return Scalar( left.realf + right.realf)
        case (.f, .i):
            return Scalar( left.realf + right.realf)
        case (.i, .d):
            return Scalar( left.reald + right.reald)
        case (.d, .i):
            return Scalar( left.reald + right.reald)
        case (.f, .f):
            return Scalar( left.realf + right.realf)
        case (.f, .d):
            return Scalar( left.realf + right.realf)
        case (.d, .f):
            return Scalar( left.realf + right.realf)
        case (.d, .d):
            return Scalar( left.reald + right.reald)
        case (.cf, .f):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: left.imagf))
        case (.cf, .d):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: left.imagf))
        case (.cd, .f):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: left.imagf))
        case (.cd, .d):
            return Scalar(DSPDoubleComplex(real: left.reald + right.reald, imag: left.imagd))
        case (.f, .cf):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: right.imagf))
        case (.d, .cf):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: right.imagf))
        case (.f, .cd):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: right.imagf))
        case (.d, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald + right.reald, imag: right.imagd))
        case(.cf, .cf):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: left.imagf + right.imagf))
        case(.cd, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald + right.reald, imag: left.imagd + right.imagd))
        case (.i, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald + right.reald, imag: right.imagd))
        case (.i, .cf):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: right.imagf))
        case (.cf, .i):
            return Scalar(DSPComplex(real: left.realf + right.realf, imag: left.imagf))
        case (.cd, .i):
            return Scalar(DSPDoubleComplex(real: left.reald + right.reald, imag: left.imagd))
        case (.ui, .ui):
            return Scalar(UInt32(left.int + right.int))
        case (.i, .ui):
            return Scalar(Int32(left.int + right.int))
        case (.ui, .i):
            return Scalar(Int32(left.int + right.int))
        case (.ui, .f):
            return Scalar(left.realf + right.realf)
        case (.f, .ui):
            return Scalar(left.realf + right.realf)
        case (.ui, .d):
            return Scalar(left.reald + right.reald)
        case (.d, .ui):
            return Scalar(left.reald + right.reald)
        default:
            preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for +")
        }
    }
    public static func * (left: Scalar, right: Scalar) -> Scalar {
        switch (left.type, right.type) {
        case (.f, .d):
            return Scalar( left.realf * right.realf)
        case (.d, .f):
            return Scalar( left.realf * right.realf)
        case (.d, .i):
            return Scalar( left.reald * right.reald)
        case (.i, .d):
            return Scalar( left.reald * right.reald)
        case (.f, .i):
            return Scalar( left.realf * right.realf)
        case (.i, .f):
            return Scalar( left.realf * right.realf)
        case (.f, .f):
            return Scalar( left.realf * right.realf)
        case (.d, .d):
            return Scalar( left.reald * right.reald)
        case (.cf, .f):
            let r = right.realf * left.realf
            let i = right.realf * left.imagf
            return Scalar(DSPComplex(real: r, imag: i))
        case (.cf, .i):
            let r = right.realf * left.realf
            let i = right.realf * left.imagf
            return Scalar(DSPComplex(real: r, imag: i))
        case (.cd, .i):
            let r = right.reald * left.reald
            let i = right.reald * left.imagd
            return Scalar(DSPDoubleComplex(real: r, imag: i))
        case (.cd, .f):
            let r = right.realf * left.realf
            let i = right.realf * left.imagf
            return Scalar(DSPComplex(real: r, imag: i))
        case (.cd, .d):
            let r = right.reald * left.reald
            let i = right.reald * left.imagd
            return Scalar(DSPDoubleComplex(real: r, imag: i))
        case (.f, .cf):
            let r = left.realf * right.realf
            let i = left.realf * right.imagf
            return Scalar(DSPComplex(real: r, imag: i))
        case (.f, .cd):
            let r = left.realf * right.realf
            let i = left.realf * right.imagf
            return Scalar(DSPComplex(real: r, imag: i))
        case (.i, .cf):
            let r = left.realf * right.realf
            let i = left.realf * right.imagf
            return Scalar(DSPComplex(real: r, imag: i))
        case (.i, .cd):
            let r = left.reald * right.reald
            let i = left.reald * right.imagd
            return Scalar(DSPDoubleComplex(real: r, imag: i))
        case (.d, .cd):
            let r = left.reald * right.reald
            let i = left.reald * right.imagd
            return Scalar(DSPDoubleComplex(real: r, imag: i))
        case(.cf, .cf):
            return Scalar(DSPComplex(real: left.realf * right.realf - left.imagf * right.imagf,
                                     imag: left.realf * left.imagf + left.imagf * right.imagf))
        case(.cd, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald * right.reald - left.imagd * right.imagd,
                                           imag: left.reald * left.imagd + left.imagd * right.imagd))
        case (.ui, .ui):
            return Scalar(UInt32(left.int * right.int))
        case (.i, .ui):
            return Scalar(Int32(left.int * right.int))
        case (.ui, .i):
            return Scalar(Int32(left.int * right.int))
        case (.ui, .f):
            return Scalar(left.realf * right.realf)
        case (.f, .ui):
            return Scalar(left.realf * right.realf)
        case (.ui, .d):
            return Scalar(left.reald * right.reald)
        case (.d, .ui):
            return Scalar(left.reald * right.reald)
        default:
            preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for *")
        }
    }
    public static func - (left: Scalar, right: Scalar) -> Scalar {
        switch (left.type, right.type) {
        case (.f, .f):
            return Scalar( left.realf - right.realf)
        case (.d, .f):
            return Scalar( left.realf - right.realf)
        case (.f, .d):
            return Scalar( left.realf - right.realf)
        case (.d, .d):
            return Scalar( left.reald - right.reald)
        case (.cf, .f):
            return Scalar(DSPComplex(real: left.realf - right.realf, imag: left.imagf))
        case (.cd, .d):
            return Scalar(DSPDoubleComplex(real: left.reald - right.reald, imag: left.imagd))
        case (.cf, .i):
            return Scalar(DSPComplex(real: left.realf - right.realf, imag: left.imagf))
        case (.cd, .i):
            return Scalar(DSPDoubleComplex(real: left.reald - right.reald, imag: left.imagd))
        case (.f, .cf):
            return Scalar(DSPComplex(real: left.realf - right.realf, imag: -right.imagf))
        case (.d, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald - right.reald, imag: -right.imagd))
        case (.i, .cf):
            return Scalar(DSPComplex(real: left.realf - right.realf, imag: -right.imagf))
        case (.i, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald - right.reald, imag: -right.imagd))
        case(.cf, .cf):
            return Scalar(DSPComplex(real: left.realf - right.realf, imag: left.imagf - right.imagf))
        case(.cd, .cd):
            return Scalar(DSPDoubleComplex(real: left.reald - right.reald, imag: left.imagd - right.imagd))
        case(.f, .i):
            return Scalar( left.realf - right.realf)
        case(.i, .f):
            return Scalar( left.realf - right.realf)
        case(.d, .i):
            return Scalar( left.reald - right.reald)
        case(.i, .d):
            return Scalar( left.reald - right.reald)
        case (.i, .i):
            return Scalar( left.int - right.int)
        default:
            preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for - ")
        }
    }
    public static func / (left: Scalar, right: Scalar) -> Scalar {
        return left * right.inverse
    }
    public static func cmagd(value: Scalar) -> Scalar {
        var retval: Double
        let re = Foundation.fabs(value.reald)
        let im = Foundation.fabs(value.imagd)
        if re == 0.0 {
            retval = im
        } else if im == 0.0 {
            retval = re
        } else if im < re {
            retval = re * Foundation.sqrt(1.0 + (im/re) * (im/re))
        } else {
            retval = im * Foundation.sqrt(1.0 + (re/im) * (re/im));
        }
        return Scalar(retval)
    }
    public static func cmagf(value: Scalar) -> Scalar {
        var retval: Float
        let re = Foundation.fabsf(value.realf)
        let im = Foundation.fabsf(value.imagf)
        if re == Float(0.0) {
            retval = im
        } else if im == Float(0.0) {
            retval = re
        } else if im < re {
            retval = re * Foundation.sqrtf(1.0 + (im/re) * (im/re))
        } else {
            retval = im * Foundation.sqrtf(1.0 + (re/im) * (re/im));
        }
        return Scalar(retval)
    }
    public static func csqrtd(value: Scalar) -> Scalar {
        if value.imagd == 0.0 {
            if value.reald < 0.0 {
                return Scalar(DSPDoubleComplex(real: 0.0,
                                               imag: Foundation.sqrt(-value.reald)))
            } else {
                return Scalar(DSPDoubleComplex(real: Foundation.sqrt(value.reald),
                                               imag: 0.0))
            }
        } else if 0.0 == value.reald {		// pure imaginary
            
            let r = Foundation.sqrt((0.5 * Foundation.fabs(value.imagd)))
            if value.imagd < 0.0 {
                return Scalar(DSPDoubleComplex(real:r, imag: -(r)))
            } else {
                return Scalar(DSPDoubleComplex(real: r, imag: r))
            }
        } else {
            let r = Foundation.sqrt(0.5 * (Scalar.cmagd(value: value).reald + Foundation.fabs(value.reald)))
            let s = value.imagd / (2.0 * r)
            if value.reald < 0.0 {
                if value.imagd < 0.0 {
                    return Scalar(DSPDoubleComplex(real: -(s), imag: -(r)))
                } else {
                    return Scalar(DSPDoubleComplex(real: s, imag: r))
                }
            } else {
                return Scalar(DSPDoubleComplex(real: r, imag: s))
            }
        }
    }
    public static func csqrtf(value: Scalar) -> Scalar {
        if value.imagf == 0.0 {
            if value.realf < 0.0 {
                return Scalar(DSPComplex(real: 0.0,
                                         imag: Foundation.sqrt(-value.realf)))
            } else {
                return Scalar(DSPComplex(real: Foundation.sqrt(value.realf),
                                         imag: 0.0))
            }
        } else if 0.0 == value.realf {		// pure imaginary
            
            let r = Foundation.sqrt((0.5 * Foundation.fabs(value.imagf)))
            if value.imagf < 0.0 {
                return Scalar(DSPComplex(real:r, imag: -(r)))
            } else {
                return Scalar(DSPComplex(real: r, imag: r))
            }
        } else {
            let r = Foundation.sqrt(0.5 * (Scalar.cmagd(value: value).realf + Foundation.fabs(value.realf)))
            let s = value.imagf / (2.0 * r)
            if value.realf < 0.0 {
                if value.imagf < 0.0 {
                    return Scalar(DSPComplex(real: -(s), imag: -(r)))
                } else {
                    return Scalar(DSPComplex(real: s, imag: r))
                }
            } else {
                return Scalar(DSPComplex(real: r, imag: s))
            }
        }
    }
    public var conj: Scalar {
        switch self.type {
        case .d:
            return self
        case .f:
            return self
        case .cf:
            return Scalar(self.type, NSNumber(value: self.realf), NSNumber(value: -self.imagf))
        case .cd:
            return Scalar(self.type, NSNumber(value: self.reald), NSNumber(value: -self.imagd))
        case .i:
            return self
        case .ui:
            return self
        }
    }
    public var inverse: Scalar {
        let mag = Scalar.cmagd(value: self)
        if mag.reald == 0.0 {
            preconditionFailure("Cannot take inverse of zero")
        }
        let type = self.type
        switch type {
        case .f:
            return Scalar(Float(1.0)/self.realf)
        case .d:
            return Scalar(1.0/self.reald)
        case .cf:
            return Scalar(DSPComplex(real: self.realf/mag.realf, imag: self.imagf/mag.realf))
        case .cd:
            return Scalar(DSPDoubleComplex(real: self.reald/mag.reald, imag: self.imagd/mag.reald))
        case .i:
            return Scalar(1/self.int)
        case .ui:
            return Scalar(1/self.int)
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
            return Scalar.csqrtf(value: self)
        case .cd:
            return Scalar.csqrtd(value: self)
        default:
            preconditionFailure("sqrt not supported for type \(self.type)")
        }
    }
    public var mag: Scalar {
        switch self.type {
        case .d:
            return Scalar(Foundation.fabs(self.reald))
        case .f:
            return Scalar(Foundation.fabsf(self.realf))
        case .cf:
            return Scalar.cmagf(value: self)
        case .cd:
            return Scalar.cmagd(value: self)
        case .i:
            return Scalar((self.int > 0 ? self.int : -self.int))
        case .ui:
            return Scalar(self.int)
        }
    }
    public func string(format fmt: String) -> String {
        return scalarString(formatFmt(fmt), value:self)
    }
}
