//: Playground - noun: a place where people can play

import Foundation
import vsip
import SJVsip
let zero = Scalar(0.0)
let fmt = "4.3"
let aMatrix = Matrix(columnLength: 5, rowLength: 4, type: .d, major: VSIP_ROW)
aMatrix.randn(8, portable: true)
let aMatrixCp = aMatrix.newCopy
let (Q,R) = aMatrixCp.qr
let chk = aMatrix.empty
chk.fill(zero)
prod(Q, prod: R, resultsIn: chk)
aMatrix.mPrint(fmt)
chk.mPrint(fmt)

