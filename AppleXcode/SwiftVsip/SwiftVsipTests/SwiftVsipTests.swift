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
    
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }
    
    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }
    func testVector() {
        var v = Vector(length: 10, type: .cd)
        let _ = v.randn(8)
        v.mPrint("4.3")
        v.real.mPrint("4.3")
        v.imag.mPrint("4.3")
        Vsip.add(v.real, to: v.imag, resultsIn: v.real)
        v.mPrint("4.3")
        v.randn(9).mPrint("4.3")
        v = Vector(length: 11, type: .cf)
        v.randu(11).mPrint("5.4")
    }
    func testPlus(){
        let a = Vsip.Scalar(15.0)
        let b = Vsip.Scalar(4.0)
        let d = a + b
        print("a + b = \(d.reald)")
    }
    func testDiv(){
        let a = Vector(length: 10, type: .f)
        let b = a.empty
        let c = a.empty
        a.fill(Vsip.Scalar(1.0))
        b.fill(Vsip.Scalar(2.0))
        Vsip.div(numerator: a, denominator: b, quotient: c)
        c.mPrint("3.2")
    }
    func testSqrt(){
        let a = Vsip.Scalar(vsip_cmplx_d(4.0, 5.0))
        let b = vsip_csqrt_d(vsip_cmplx_d(4.0, 5.0))
        let c = a.sqrt
        print("( \(b.r), \(b.i))")
        print("( \(c.reald), \(c.imagd))")
        XCTAssert((b.r == c.reald) && (b.i == c.imagd))
    }
    func testSvd(){
        let n = 5
        let A = Matrix(columnLength: n, rowLength: n, type: .d, major: VSIP_ROW)
        let x = Vector(length: A.rowLength, type: A.type)
        let b = Vector(length: A.columnLength, type: A.type)
        let fmt = "6.5"
        let chk = 1E-14
        let _ = A.randn(5, portable: true)
        let _ = x.randn(9, portable: true)
        let normA = Vsip.Jvsip.normFro(view: A)
        Vsip.prod(matA: A, vecB: x, vecC: b)
        print("Matrix A");A.mPrint(fmt)
        print("Known x vector");x.mPrint(fmt)
        print("Calculated b=Ax vector"); b.mPrint(fmt)
        // check that U S V^t gives back A
        let Ac = A.copy  // Ac is used for decompostion to keep original A
        let Ar = A.empty // new data space for result
        let svd = Vsip.Svd(view: Ac!)
        let sValues = svd.decompose(Ac!)
        let U = svd.matU!
        let V = svd.matV!
        print("U");U.mPrint(fmt)
        print("Singular Values");sValues?.mPrint(fmt)
        print("V");V.mPrint(fmt)
        let USr = U.empty // result of matrix product of U and Singular Vaules
        Vsip.vmmul(vector: sValues!, matrix: U, major: VSIP_ROW, output: USr)
        Vsip.prod(matA: USr, matB: V.transview, matC: Ar)
        print("Result of USV^t"); Ar.mPrint(fmt)
        Vsip.sub(A, subtract: Ar, resultIn: Ar)
        let normChk = Vsip.Jvsip.normFro(view:Ar).reald / normA.reald
        print("normChk: \(normChk)")
        XCTAssert( normChk < chk)
    }
}
