import Foundation
public enum Major: String {
    case row, col
}
public struct Matrix {
    public var block: Block
    public var offset: Int
    public var colstride: Int
    public var collength: Int
    public var rowstride: Int
    public var rowlength: Int
    public var type: BlockTypes {
        get {
            return self.block.type
        }
    }
    public init(block: Block, offset: Int, colstride: Int, collength: Int, rowstride: Int, rowlength: Int) {
        self.block = block
        self.offset = offset
        self.colstride = colstride
        self.collength = collength
        self.rowstride = rowstride
        self.rowlength = rowlength
    }
    
    public init(collength: Int, rowlength: Int, type: BlockTypes, major: Major = .row) {
        self.block = Block(length: rowlength * collength, type: type)
        self.collength = collength
        self.rowlength = rowlength
        self.offset = 0
        if major == .row {
            self.rowstride = 1
            self.colstride = rowlength
        } else {
            self.colstride = 1
            self.rowstride = collength
        }
    }
    public subscript(rowIndex: Int, colIndex: Int) -> Scalar {
        get {
            return self.block[self.offset + rowIndex * self.colstride + colIndex * self.rowstride]
        }
        set(value) {
            self.block[self.offset + rowIndex * self.colstride + colIndex * self.rowstride] = value
        }
    }
    public static func prod(_ left: Matrix, times right: Matrix, output: Matrix) {
        // left M by N, right N by P, output M by P
        let M = left.collength
        let N = left.rowlength
        let P = right.rowlength
        assert(N == right.collength && M == output.collength && P == output.rowlength, "Matrix size error")
        
    }
}

