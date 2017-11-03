//: Blocks are a data storage abstraction. We support Float, Double (real and complex) and Int blocks.
//: Complex blocks are structures made up of two real Blocks. This is a split storage format.
//: Real blocks are classes to allow for deinit and ARC to free memory.

import Foundation
import Accelerate

//: Data types; for this implementation everything is done dynamically
public enum BlockTypes: String {
    case f, cf, d, cd, i, ui
}

//: a class to handle creation and deinit for Views of type Double
fileprivate class DataDouble: NSObject {
    let dta: UnsafeRawPointer
    let length: Int
    let derived: Bool
    init(length: Int){
        self.length = length
        self.derived = false
        let dta = UnsafeMutablePointer<Double>.allocate(capacity: length)
        dta.initialize(to: 0.0, count: length )
        self.dta = UnsafeRawPointer(dta)
    }
    init(data: UnsafeRawPointer, length: Int){
        self.length = length
        self.dta = data
        self.derived = true
    }
    deinit {
        if !self.derived {
            let dta = UnsafeMutablePointer<Double>(mutating: self.dta.assumingMemoryBound(to: Double.self))
            dta.deinitialize(count: self.length)
            dta.deallocate(capacity: self.length)
        }
    }
}
//: a class to handle creation and deinit for Views of type Float
fileprivate class DataFloat: NSObject {
    let dta: UnsafeRawPointer
    let length: Int
    let derived: Bool
    init(length: Int){
        self.length = length
        self.derived = false
        let dta = UnsafeMutablePointer<Float>.allocate(capacity: length)
        dta.initialize(to: 0.0, count: length )
        self.dta = UnsafeRawPointer(dta)
    }
    init(data: UnsafeRawPointer, length: Int){
        self.length = length
        self.dta = data
        self.derived = true
    }
    deinit {
        if !self.derived {
            let dta = UnsafeMutablePointer<Float>(mutating: self.dta.assumingMemoryBound(to: Float.self))
            dta.deinitialize(count: self.length)
            dta.deallocate(capacity: self.length)
        }
    }
}
//: Accelerate uses UInt32 for indexing, offsets and length
fileprivate class DataUInt32: NSObject {
    let dta: UnsafeRawPointer
    let length: Int
    let derived: Bool
    init(length: Int){
        self.length = length
        self.derived = false
        let dta = UnsafeMutablePointer<UInt32>.allocate(capacity: length)
        dta.initialize(to: 0, count: length )
        self.dta = UnsafeRawPointer(dta)
    }
    init(data: UnsafeRawPointer, length: Int){
        self.length = length
        self.dta = data
        self.derived = true
    }
    deinit {
        if !self.derived {
            let dta = UnsafeMutablePointer<UInt32>(mutating: self.dta.assumingMemoryBound(to: UInt32.self))
            dta.deinitialize(count: self.length)
            dta.deallocate(capacity: self.length)
        }
    }
}
//: Accelerate uses Int32 for strides
fileprivate class DataInt32: NSObject {
    let dta: UnsafeRawPointer
    let length: Int
    let derived: Bool
    init(length: Int){
        self.length = length
        self.derived = false
        let dta = UnsafeMutablePointer<Int32>.allocate(capacity: length)
        dta.initialize(to: 0, count: length )
        self.dta = UnsafeRawPointer(dta)
    }
    init(data: UnsafeRawPointer, length: Int){
        self.length = length
        self.dta = data
        self.derived = true
    }
    deinit {
        if !self.derived {
            let dta = UnsafeMutablePointer<Int32>(mutating: self.dta.assumingMemoryBound(to: Int32.self))
            dta.deinitialize(count: self.length)
            dta.deallocate(capacity: self.length)
        }
    }
}

//: complex views are structures.  They don't allocate any memory from the heap directly
fileprivate struct DataComplexDouble {
    let dtaReal: DataDouble
    let dtaImag: DataDouble
    init(length: Int){
        self.dtaReal = DataDouble(length: length)
        self.dtaImag = DataDouble(length: length)
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

//: Blocks are data raw data containers.  The type is set at create.
public struct Block {
    public let count: Int
    public var dta: UnsafeRawPointer?
    public var imagDta: UnsafeRawPointer?
    public let type: BlockTypes
    let derived: Bool
    let dtaObj: Any //need to retain data object so ARC does not collect it
    public init(length: Int, type: BlockTypes){
        self.count = length
        self.derived = false
        switch type{
        case .f:
            let dta = DataFloat(length: length)
            self.dtaObj = dta
            self.dta = dta.dta
            self.type = type
        case .cf:
            let dta = DataComplexFloat(length: length)
            self.dtaObj = dta
            self.dta = dta.dtaReal.dta
            self.imagDta = dta.dtaImag.dta
            self.type = type
        case .d:
            let dta = DataDouble(length: length)
            self.dtaObj = dta
            self.dta = dta.dta
            self.type = type
        case .cd:
            let dta = DataComplexDouble(length: length)
            self.dtaObj = dta
            self.dta = dta.dtaReal.dta
            self.imagDta = dta.dtaImag.dta
            self.type = type
        case .i:
            let dta = DataInt32(length: length)
            self.dtaObj = dta
            self.dta = dta.dta
            self.type = type
        case .ui:
            let dta = DataUInt32(length: length)
            self.dtaObj = dta
            self.dta = dta.dta
            self.type = type
        }
    }
    public subscript(index: Int) -> Scalar {
        get {
            switch self.type {
            case .f:
                let dta = UnsafeMutablePointer<Float>(mutating: self.dta?.assumingMemoryBound(to: Float.self))
                return Scalar((dta! + index).pointee)
            case .d:
                let dta = UnsafeMutablePointer<Double>(mutating: self.dta?.assumingMemoryBound(to: Double.self))
                return Scalar((dta! + index).pointee)
            case .cf:
                let dtaReal = UnsafeMutablePointer<Float>(mutating: self.dta?.assumingMemoryBound(to: Float.self))
                let dtaImag = UnsafeMutablePointer<Float>(mutating: self.imagDta?.assumingMemoryBound(to: Float.self))
                return Scalar(DSPComplex(real: (dtaReal! + index).pointee,
                                         imag: (dtaImag! + index).pointee))
            case .cd:
                let dtaReal = UnsafeMutablePointer<Double>(mutating: self.dta?.assumingMemoryBound(to: Double.self))
                let dtaImag = UnsafeMutablePointer<Double>(mutating: self.imagDta?.assumingMemoryBound(to: Double.self))
                return Scalar(DSPDoubleComplex(real: (dtaReal! + index).pointee, imag: (dtaImag! + index).pointee))
            case .i:
                let dta = UnsafeMutablePointer<Int32>(mutating: self.dta?.assumingMemoryBound(to: Int32.self))
                return Scalar((dta! + index).pointee)
            case .ui:
                let dta = UnsafeMutablePointer<UInt32>(mutating: self.dta?.assumingMemoryBound(to: UInt32.self))
                return Scalar((dta! + index).pointee)
            }
        }
        set(value) {
            switch self.type {
            case .f:
                let dta = UnsafeMutablePointer<Float>(mutating: self.dta?.assumingMemoryBound(to: Float.self))
                (dta! + index).pointee = value.realf
            case .d:
                let dta = UnsafeMutablePointer<Double>(mutating: self.dta?.assumingMemoryBound(to: Double.self))
                (dta! + index).pointee = value.reald
                
            case .cf:
                let dtaReal = UnsafeMutablePointer<Float>(mutating: self.dta?.assumingMemoryBound(to: Float.self))
                let dtaImag = UnsafeMutablePointer<Float>(mutating: self.imagDta?.assumingMemoryBound(to: Float.self))
                (dtaReal! + index).pointee = value.realf
                (dtaImag! + index).pointee = value.imagf
            case .cd:
                let dtaReal = UnsafeMutablePointer<Double>(mutating: self.dta?.assumingMemoryBound(to: Double.self))
                let dtaImag = UnsafeMutablePointer<Double>(mutating: self.imagDta?.assumingMemoryBound(to: Double.self))
                (dtaReal! + index).pointee = value.reald
                (dtaImag! + index).pointee = value.imagd
            case .i:
                let dta = UnsafeMutablePointer<Int32>(mutating: self.dta?.assumingMemoryBound(to: Int32.self))
                (dta! + index).pointee = value.int
            case .ui:
                let dta = UnsafeMutablePointer<UInt32>(mutating: self.dta?.assumingMemoryBound(to: UInt32.self))
                (dta! + index).pointee = UInt32(value.int)
            }
        }
    }
}


