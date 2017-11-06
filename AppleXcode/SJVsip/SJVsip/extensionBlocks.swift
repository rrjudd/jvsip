//
//  extensionBlocks.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
// Return JVSIP Swift View object.  Allows block.bind for shape vector
extension Block {
    public func bind(offset : Int,
                     stride : Int,
                     length : Int) -> Vector {
        return Vector(block: self, offset: offset, stride: stride, length: length)
    }
    // Return JVSIP Swift View object.  Allows block.bind for shape matrix
    public func bind(offset : Int,
                     columnStride : Int, columnLength : Int,
                     rowStride : Int, rowLength : Int) -> Matrix {
        return Matrix(block: self, offset: offset,
                      columnStride: columnStride, columnLength: columnLength,
                      rowStride: rowStride, rowLength: rowLength)
    }
    public func vector() -> Vector{
        return self.bind(offset: 0, stride: 1, length: self.length)
    }
}
