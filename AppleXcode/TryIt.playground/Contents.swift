//: Playground - noun: a place where people can play

import Foundation
import vsip

//: Run some C VSIPL code
/*print("A C VSIPL ramp")
let vsipInit = vsip_init(nil)
let v = vsip_vcreate_d(10, VSIP_MEM_NONE)
vsip_vramp_d(0.1, 0.2, v)
for i in 0..<vsip_vgetlength_d(v){
    print(vsip_vget_d(v,i))
}
vsip_valldestroy_d(v)
let vsipFin = vsip_finalize(nil)


//: Run some Swift Vsip code*/
import SwiftVsip
print("\nA Swift VSIPL Ramp")
var Vec: Vsip.Vector
Vec = Vsip.Vector(length: 10, type: .d)
Vec.ramp(0.1, increment: 0.2)
Vec.mPrint("2.1")

//: work with SVD
let m = 4
let n = 5
var M = Vsip.Matrix(columnLength: m, rowLength: n, type: .cd, major: VSIP_ROW)
M.randn(8, portable: true)
M.mPrint("0.5")

var svd: Vsip.Svd = Vsip.Svd(type: (M.type), columnLength: (M.columnLength), rowLength: (M.rowLength), saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
let s = svd.decompose(M.copy)
let sizeU = svd.sizeU
let sizeV = svd.sizeV
print("Singular values")
s.mPrint("4.3")
var U = Vsip.Matrix(columnLength: sizeU.0, rowLength: sizeU.1,type: .cd, major: VSIP_ROW)
svd.matU(0, highColumn: sizeU.1, matU: U)
var V = Vsip.Matrix(columnLength: sizeV.0, rowLength: sizeV.1,type: .cd, major: VSIP_ROW)
svd.matV(0, highColumn: sizeV.1, matV: V)
U.mPrint("4.3")
V.mPrint("4.3")
let Uout = U.empty
let Uherm = U.transview.empty
Vsip.herm(U, output: Uherm)
Vsip.prod(U, prod: Uherm, resultsIn: Uout)
Uout.mPrint("4.3")

