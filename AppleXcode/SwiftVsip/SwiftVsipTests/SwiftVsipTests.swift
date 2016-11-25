//
//  SwiftVsipTests.swift
//  SwiftVsipTests
//
//  Created by Randall Judd on 10/7/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import XCTest
@testable import SwiftVsip

class SwiftVsipTests: XCTestCase {
    func testVector() { // All we do here is make sure some stuff runs without failing
        var v = Vsip.Vector(length: 10, type: .cd)
        let _ = v.randn(8)
        v.mPrint("4.3")
        v.real.mPrint("4.3")
        v.imag.mPrint("4.3")
        Vsip.add(v.real, v.imag, output: v.real)
        v.mPrint("4.3")
        v.randn(9).mPrint("4.3")
        v = Vsip.Vector(length: 11, type: .cf)
        v.randu(11).mPrint("5.4")
    }
    func testMatrix() { // All we do here is make sure some stuff runs without failing
        var m = Vsip.Matrix(columnLength: 4, rowLength: 3, type: .cf, major: VSIP_ROW)
        let _ = m.randn(8, portable: true)
        m.mPrint("4.3")
        m.real.mPrint("4.3")
        m.imag.mPrint("4.3")
        Vsip.add(m.real, m.imag, output: m.real)
        m.mPrint("4.3")
        m.randn(9, portable: true).mPrint("4.3")
        m = Vsip.Matrix(columnLength: 5, rowLength: 3, type: .d, major: VSIP_COL)
        m.randu(11, portable: false).mPrint("5.4")
    }
    func testScalarPlus(){
        let a = Vsip.Scalar(15.0)
        let b = Vsip.Scalar(4.0)
        let d = a + b
        print("a + b = \(d.reald)")
    }
    func testDiv(){
        let a = Vsip.Vector(length: 10, type: .f)
        let b = a.empty
        let c = a.empty
        a.fill(Vsip.Scalar(1.0))
        b.fill(Vsip.Scalar(2.0))
        Vsip.div(numerator: a, denominator: b, quotient: c)
        c.mPrint("3.2")
    }
    func testScalarSqrt(){
        let a = Vsip.Scalar(vsip_cmplx_d(4.0, 5.0))
        let b = vsip_csqrt_d(vsip_cmplx_d(4.0, 5.0))
        let c = a.sqrt
        print("( \(b.r), \(b.i))")
        print("( \(c.reald), \(c.imagd))")
        XCTAssert((b.r == c.reald) && (b.i == c.imagd))
    }
    func testSvd(){
        let n = 5
        let A = Vsip.Matrix(columnLength: n, rowLength: n, type: .d, major: VSIP_ROW)
        let x = Vsip.Vector(length: A.rowLength, type: A.type)
        let b = Vsip.Vector(length: A.columnLength, type: A.type)
        let fmt = "6.5"
        let chk = 1E-14
        let _ = A.randn(5, portable: true)
        let _ = x.randn(9, portable: true)
        let normA = Vsip.Jvsip.normFro(view: A)
        Vsip.prod(A, times: x, resultIn: b)
        print("Matrix A");A.mPrint(fmt)
        print("Known x vector");x.mPrint(fmt)
        print("Calculated b=Ax vector"); b.mPrint(fmt)
        // check that U S V^t gives back A
        let Ac = A.copy  // Ac is used for decompostion to keep original A
        let Ar = A.empty // new data space for result
        let svd = Vsip.Svd(view: Ac)
        let sValues = svd.decompose(Ac)
        let U = svd.matU!
        let V = svd.matV!
        print("U");U.mPrint(fmt)
        print("Singular Values");sValues.mPrint(fmt)
        print("V");V.mPrint(fmt)
        let USr = U.empty // result of matrix product of U and Singular Vaules
        Vsip.vmmul(vector: sValues, matrix: U, major: VSIP_ROW, output: USr)
        Vsip.prod(USr, times: V.transview, resultIn: Ar)
        print("Result of USV^t"); Ar.mPrint(fmt)
        Vsip.sub(A, subtract: Ar, output: Ar)
        var normChk = Vsip.Jvsip.normFro(view:Ar).reald / normA.reald
        print("normChk: \(normChk)")
        print("Check USV^t equal input matrprix within reasonable bounds")
        XCTAssert( normChk < chk, "Check Failed for equality of USV^t with input matrix within reasonable bounds")
        let xe = x.empty  // x estimate for backsolve
        Vsip.prod(U.transview, times: b, resultIn: xe)
        Vsip.div(numerator: xe, denominator: sValues, quotient: xe)
        Vsip.prod(V, times: xe.copy, resultIn: xe)
        print("solve for estimate of x from b");xe.mPrint(fmt)
        Vsip.sub(x, subtract: xe, output: xe)
        normChk = Vsip.Jvsip.normFro(view: xe).reald/Vsip.Jvsip.normFro(view: x).reald
        print("Check estimate of x equal x within reasonable bounds (for Ax=b then x_est = V S^-1 U^T b)")
        XCTAssert( normChk < chk, "Check Failed for (in Ax=b) estimate of x equal to x within reasonable bounds")
    }
    func testHouseReflection(){
        let n = 3
        let v = Vsip.Vector(length: n, type: .d)
        let A = Vsip.Matrix(columnLength: n, rowLength: n, type: .d, major: VSIP_ROW)
        v[0] = Vsip.Scalar(2.0); v[1] = Vsip.Scalar(3.0); v[2] = Vsip.Scalar(1.0)
        Vsip.outer(alpha: Vsip.Scalar(1.0), vecX: v, vecY: v, matC: A)
        let beta = Vsip.Scalar(2.0 / Vsip.dot(product: v, with: v).reald)
        Vsip.mul(beta.reald, A, output: A)
        let P = A.empty
        P.fill(0.0)
        P.diagview.fill(1.0)
        Vsip.sub(P, subtract: A, output: P)
        print(beta.reald)
        A.mPrint("4.3")
        P.mPrint("4.3")
        Vsip.prod(P, times: P, resultIn: A)
        A.mPrint("4.3")
    }
    func testQrd(){
        let m = 6
        let n = 4
        let A = Vsip.Matrix(columnLength: m, rowLength: n, type: .d, major: VSIP_ROW)
        // generate some data
        let _ = A.randn(8, portable: true)
        // keep a copy of original
        let Acopy = A.copy
        // make some space for an estimate of A to be calculated with Q and R
        let Ae = A.empty
        // get (Q,R)
        let qr = Vsip.Jvsip.decompose(Acopy)
        let Q = qr.0
         let R = qr.1
         // Calculate Ae
         Vsip.prod(Q, times: R, resultIn: Ae)
         // print original and estimate
         A.mPrint("5.3")
         Ae.mPrint("5.3")
    }
    
}
