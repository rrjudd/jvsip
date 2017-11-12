//: Singular Value Decompostion Example

import Foundation
import vsip
import SJVsip
let zero = Scalar(0.0)
let aMatrix = Matrix(columnLength: 5, rowLength: 4, type: .f, major: VSIP_ROW)
aMatrix.randn(8, portable: true)
let fmt = "%4.3f"
let chk = aMatrix.empty
aMatrix.mPrint(fmt)
let sv = aMatrix.sv
sv.mPrint(fmt)
let (U,s,V) = aMatrix.svdPart
U.mPrint(fmt);s.mPrint(fmt); V.mPrint(fmt)
chk.fill(zero)
vmmul(vector: s, matrix: U, major: VSIP_ROW, resultsIn: U)
prod(U, prod: V.transview, resultsIn: chk)
chk.mPrint(fmt)
let svd = Svd(type: aMatrix.type, columnLength: aMatrix.columnLength, rowLength: aMatrix.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
svd.decompose(aMatrix.newCopy)
if checkSvd(svd, against: aMatrix) {
    print("svd works")
} else {
    print("svd failed")
}

