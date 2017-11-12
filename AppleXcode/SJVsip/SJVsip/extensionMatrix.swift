//
//  extensionMatrix.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
extension Matrix {
    public static func + (left: Matrix, right: Matrix) -> Matrix {
        let retval = left.empty
        add(left, right, resultsIn: retval)
        return retval
    }
    public static func - (left: Matrix, right: Matrix) -> Matrix {
        let retval = left.empty
        sub(left, subtract: right, resultsIn: retval)
        return retval
    }
    public var normFro: Double {
        get {
            return (SJvsip.normFro(view: self).reald)
        }
    }
    public var qr: (Matrix, Matrix){
        let qrd = QRD(type: self.type, columnLength: self.columnLength, rowLength: self.rowLength, qopt: VSIP_QRD_SAVEQ)
        let Q = Matrix(columnLength: qrd.columnLength, rowLength: qrd.columnLength, type: self.type, major: VSIP_ROW)
        let R = Matrix(columnLength: qrd.columnLength, rowLength: qrd.rowLength, type: self.type, major: VSIP_ROW)
        let aCopy = self.newCopy
        Q.fill(Scalar(0.0))
        R.fill(Scalar(0.0))
        Q.diagview.fill(Scalar(1.0))
        let _ = qrd.decompose(aCopy)
        qrd.prodq(matrixOperator: VSIP_MAT_NTRANS, matrixSide: VSIP_MAT_LSIDE, matrix: Q)
        let Qt = Q.transview
        prod(Qt, prod: self, resultsIn: R)
        return (Q,R)
    }
    public var sv: Vector {
        let svd = Svd(type: self.type, columnLength: self.columnLength, rowLength: self.rowLength, saveU: VSIP_SVD_UVNOS, saveV: VSIP_SVD_UVNOS)
        let acopy = self.newCopy
        return svd.decompose(acopy)
    }
    public var svd: (Matrix, Vector, Matrix) {
        let svd = Svd(type: self.type, columnLength: self.columnLength, rowLength: self.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
        let acopy = self.newCopy
        let s = svd.decompose(acopy)
        let U = svd.matU!
        let V = svd.matV!
        return (U,s,V)
    }
    public var svdPart: (Matrix, Vector, Matrix) {
        let svd = Svd(type: self.type, columnLength: self.columnLength, rowLength: self.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
        let acopy = self.newCopy
        let s = svd.decompose(acopy)
        let U = svd.matU!
        let V = svd.matV!
        if self.rowLength > self.columnLength {
            V.rowLength = s.length
            return (U,s,V.newCopy)
        } else {
            U.rowLength = s.length
            return (U.newCopy,s,V)
        }
    }
}
