import Foundation
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
    public mutating func ramp(start: Scalar, increment: Scalar) {
        for i in 0..<self.length {
            self[i] = Scalar(i) * increment + start
        }
    }
}
