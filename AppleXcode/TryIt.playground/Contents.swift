//: Playground - noun: a place where people can play

import Foundation
import vsip
import SJVsip
// a vector of length 10 and type double
let zero = Scalar(0.0), one = Scalar(1.0)
let fmt = "4.3"
let aMatrix = Matrix(columnLength: 5, rowLength: 5, type: .d, major: VSIP_ROW)
aMatrix.randn(8, portable: true)
aMatrix.mPrint(fmt)
let lu = LUD(type: aMatrix.type, size: aMatrix.columnLength)
let xb = Matrix(columnLength: 5, rowLength: 2, type: .d, major: VSIP_ROW)
let b = xb.empty
xb.randn(9, portable: true)
prod(aMatrix, prod: xb, resultsIn: b)
lu.decompose(aMatrix)
xb.mPrint(fmt); b.mPrint(fmt)
lu.solve(matOp: VSIP_MAT_NTRANS, b)
b.mPrint(fmt)

