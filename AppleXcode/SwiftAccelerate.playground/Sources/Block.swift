import Foundation
import Accelerate
public enum BlockTypes: String {
    case f, cf, d, cd, i
}
fileprivate class DataDouble {
    let dta: UnsafeMutablePointer<Double>
    let length: Int
    let derived: Bool
    init(length: Int){
        self.length = length
        self.derived = false
        self.dta = UnsafeMutablePointer<Double>.allocate(capacity: length)
        self.dta.initialize(to: 0.0)
    }
    init(data: UnsafeMutablePointer<Double>, length: Int){
        self.length = length
        self.dta = data
        self.derived = true
    }
    deinit {
        if !self.derived {
            self.dta.deinitialize(count: self.length)
            self.dta.deallocate(capacity: self.length)
        }
    }
}
fileprivate struct DataComplexDouble {
    let dtaReal: DataDouble
    let dtaImag: DataDouble
    init(length: Int){
        self.dtaReal = DataDouble(length: length)
        self.dtaImag = DataDouble(length: length)
    }
}

fileprivate class DataFloat {
    let dta: UnsafeMutablePointer<Float>
    let length: Int
    let derived: Bool
    init(length: Int){
        self.length = length
        self.derived = false
        self.dta = UnsafeMutablePointer<Float>.allocate(capacity: length)
        self.dta.initialize(to: Float(0.0))
    }
    init(data: UnsafeMutablePointer<Float>, length: Int){
        self.length = length
        self.dta = data
        self.derived = true
    }
    deinit {
        if !self.derived {
            self.dta.deinitialize(count: self.length)
            self.dta.deallocate(capacity: self.length)
        }
    }
}
fileprivate struct DataComplexFloat {
    let dtaReal: DataFloat
    let dtaImag: DataFloat
    init(length: Int){
        self.dtaReal = DataFloat(length: length)
        self.dtaImag = DataFloat(length: length)
    }
}

fileprivate class DataInt {
    let dta: UnsafeMutablePointer<Int>
    let length: Int
    init(length: Int){
        self.length = length
        self.dta = UnsafeMutablePointer<Int>.allocate(capacity: length)
        self.dta.initialize(to: 0)
    }
    deinit {
        self.dta.deinitialize(count: self.length)
        self.dta.deallocate(capacity: self.length)
    }
}
public struct Block {
    public let count: Int
    var dta: Any
    public let type: BlockTypes
    public init(length: Int, type: BlockTypes){
        self.count = length
        switch type{
        case .f:
            self.dta = DataDouble(length: length)
            self.type = type
        case .cf:
            self.dta = DataComplexDouble(length: length)
            self.type = type
        case .d:
            self.dta = DataDouble(length: length)
            self.type = type
        case .cd:
            self.dta = DataComplexDouble(length: length)
            self.type = type
        case .i:
            self.dta = DataInt(length: length)
            self.type = type
        }
    }
    public subscript(index: Int) -> Scalar {
        get {
            switch self.type {
            case .f:
                let dta = self.dta as! DataFloat
                return Scalar((dta.dta + index).pointee)
            case .d:
                let dta = self.dta as! DataDouble
                return Scalar((dta.dta + index).pointee)
            case .cf:
                let dta = self.dta as! DataComplexFloat
                return Scalar(DSPComplex(real: (dta.dtaReal.dta + index).pointee,
                                         imag: (dta.dtaImag.dta + index).pointee))
            case .cd:
                let dta = self.dta as! DataComplexDouble
                return Scalar(DSPDoubleComplex(real: (dta.dtaReal.dta + index).pointee,
                                               imag: (dta.dtaImag.dta + index).pointee))
            case .i:
                let dta = self.dta as! DataInt
                return Scalar((dta.dta + index).pointee)
            }
        }
        set(value) {
            switch self.type {
            case .f:
                let dta = self.dta as! DataFloat
                (dta.dta + index).pointee = value.realf
            case .d:
                let dta = self.dta as! DataDouble
                (dta.dta + index).pointee = value.reald
            case .cf:
                let dta = self.dta as! DataComplexFloat
                (dta.dtaReal.dta + index).pointee = value.realf
                (dta.dtaImag.dta + index).pointee = value.imagf
            case .cd:
                let dta = self.dta as! DataComplexDouble
                (dta.dtaReal.dta + index).pointee = value.reald
                (dta.dtaImag.dta + index).pointee = value.imagd
            case .i:
                let dta = self.dta as! DataInt
                (dta.dta + index).pointee = value.int
            }
        }
    }
}


