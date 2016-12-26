import Foundation
import Accelerate
public struct Vector {
    public var block: Block
    public var offset: Int
    public var stride: Int
    public var length: Int
    public var type: BlockTypes {
        get {
            return self.block.type
        }
    }
    public init(block: Block, offset: Int, stride: Int, length: Int) {
        self.block = block
        self.offset = offset
        self.stride = stride
        self.length = length
    }
    public init(length: Int, type: BlockTypes) {
        self.block = Block(length: length, type: type)
        self.offset = 0
        self.stride = 1
        self.length = length
    }
    public subscript(index: Int) -> Scalar {
        get {
            return self.block[self.offset + index * self.stride]
        }
        set(value)  {
            self.block[self.offset + index * self.stride] = value
        }
    }
    public mutating func fill(value: Scalar){
        for index in 0..<self.length {
            self[index] = value
        }
    }
    public func vdsp_fill(value: Scalar) {
        switch self.type {
        case .f:
            var s = value.realf
            let dta = UnsafeMutablePointer<Float>(mutating: self.block.dta?.assumingMemoryBound(to: Float.self))
            vDSP_vfill((dta! + self.offset), &s, vDSP_Stride(self.stride), vDSP_Length(self.length))
        case .d:
            var s = value.reald
            let dta = UnsafeMutablePointer<Double>(mutating: self.block.dta?.assumingMemoryBound(to: Double.self))
            vDSP_vfillD((dta! + self.offset), &s, vDSP_Stride(self.stride), vDSP_Length(self.length))
        case .cf:
            var sr = value.realf
            var si = value.imagf
            let dtaReal = UnsafeMutablePointer<Float>(mutating: self.block.dta?.assumingMemoryBound(to: Float.self))
            let dtaImag = UnsafeMutablePointer<Float>(mutating: self.block.imagDta?.assumingMemoryBound(to: Float.self))
            vDSP_vfill((dtaReal! + self.offset), &sr, vDSP_Stride(self.stride), vDSP_Length(self.length))
            vDSP_vfill((dtaImag! + self.offset), &si, vDSP_Stride(self.stride), vDSP_Length(self.length))

        case .cd:
            var sr = value.reald
            var si = value.imagd
            let dtaReal = UnsafeMutablePointer<Double>(mutating: self.block.dta?.assumingMemoryBound(to: Double.self))
            let dtaImag = UnsafeMutablePointer<Double>(mutating: self.block.imagDta?.assumingMemoryBound(to: Double.self))
            vDSP_vfillD((dtaReal! + self.offset), &sr, vDSP_Stride(self.stride), vDSP_Length(self.length))
            vDSP_vfillD((dtaImag! + self.offset), &si, vDSP_Stride(self.stride), vDSP_Length(self.length))
        default:
            preconditionFailure("type \(self.type) not supported for fill")
        }
    }
    public mutating func ramp(start: Scalar, increment: Scalar) {
        for i in 0..<self.length {
            self[i] = Scalar(Int32(i)) * increment + start
        }
    }
    public func vdsp_ramp(start: Scalar, increment: Scalar){
        switch self.type {
        case .f:
            let dta = UnsafeMutablePointer<Float>(mutating: self.block.dta?.assumingMemoryBound(to: Float.self))
            var st = start.realf
            var inc = increment.realf
            vDSP_vramp(&st, &inc, (dta! + self.offset), vDSP_Stride(self.stride), vDSP_Length(self.length))
        case .d:
            let dta = UnsafeMutablePointer<Double>(mutating: self.block.dta?.assumingMemoryBound(to: Double.self))
            var st = start.reald
            var inc = increment.reald
            vDSP_vrampD(&st, &inc, (dta! + self.offset), vDSP_Stride(self.stride), vDSP_Length(self.length))
        default:
            preconditionFailure("vdsp_ramp not supported for \(self.type)")
        }
    }
    public var sumval: Scalar {
        var sum = self[0]
        for i in 1..<self.length {
            sum = sum + self[i]
        }
        return sum
    }
    public var vdsp_sumval: Scalar {
        var retval: Scalar
        switch self.type {
        case .f:
            var sum: Float = 0.0
            let dta = UnsafeMutablePointer<Float>(mutating: self.block.dta?.assumingMemoryBound(to: Float.self))
            vDSP_sve((dta! + self.offset), vDSP_Stride(self.stride),&sum, vDSP_Length(self.length))
            retval = Scalar(sum)
        case .d:
            var sum: Double = 0.0
            let dta = UnsafeMutablePointer<Double>(mutating: self.block.dta?.assumingMemoryBound(to: Double.self))
            vDSP_sveD((dta! + self.offset), vDSP_Stride(self.stride),&sum, vDSP_Length(self.length))
            retval = Scalar(sum)
        default:
            preconditionFailure("vdsp_sumval not supported for \(self.type)")
            
        }
        return retval
    }
}
