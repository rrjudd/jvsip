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
    public func row(_ row: Int) -> Vector {
        return Vector(block: self.block, offset: self.offset + row * self.colstride, stride: self.rowstride, length: self.rowlength)
    }
    public func col(_ col: Int) -> Vector {
        return Vector(block: self.block, offset: self.offset + col * self.rowstride, stride: self.colstride, length: self.collength)
    }
    public func diag(_ diag: Int) -> Vector {
        let i = (diag < 0) ? -diag : 0  // row index of origin
        let j = (diag > 0) ?  diag : 0  // col index of origin
        let n_row = self.collength - i  // # rows from origin to end
        let	n_col = self.rowlength - j  // # cols from origin to end
        return Vector(
            block: self.block,
            offset: self.offset + i * self.colstride + j * self.rowstride,
            stride: self.rowstride + self.colstride,
            length: (n_row < n_col) ? n_row : n_col);
    }
    
    public static func prod(_ left: Matrix, times right: Matrix, output: Matrix) {
        // left M by N, right N by P, output M by P
        let M = left.collength
        let N = left.rowlength
        let P = right.rowlength
        assert(N == right.collength && M == output.collength && P == output.rowlength, "Matrix size error")
        
    }
    public func string(format: String) -> String {
        var s = ""
        for i in 0..<self.collength {
            for j in 0..<self.rowlength {
                s.append(self[i,j].string(format: format) + " ")
            }
            s.append("\n")
        }
        return s
    }
}

