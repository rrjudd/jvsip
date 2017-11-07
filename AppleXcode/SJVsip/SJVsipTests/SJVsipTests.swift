//
//  SJVsip.Tests.swift
//  SJVsip.Tests
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import XCTest
import vsip
@testable import SJVsip

class SJVsipTests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    //
    //  SwiftVsipTests.swift
    //  SwiftVsipTests
    //
    //  Created by Randall Judd on 10/7/16.
    //  Copyright © 2016 JVSIP. All rights reserved.
    //
    
    func testVector() { // All we do here is make sure some stuff runs without failing
        var v = SJVsip.Vector(length: 10, type: .cd)
        let _ = v.randn(8)
        v.mPrint("4.3")
        v.real.mPrint("4.3")
        v.imag.mPrint("4.3")
        SJVsip.add(v.real, v.imag, resultsIn: v.real)
        v.mPrint("4.3")
        v.randn(9).mPrint("4.3")
        v = SJVsip.Vector(length: 11, type: .cf)
        v.randu(11).mPrint("5.4")
    }
    func testMatrix() { // All we do here is make sure some stuff runs without failing
        var m = SJVsip.Matrix(columnLength: 4, rowLength: 3, type: .cf, major: VSIP_ROW)
        let _ = m.randn(8, portable: true)
        m.mPrint("4.3")
        m.real.mPrint("4.3")
        m.imag.mPrint("4.3")
        SJVsip.add(m.real, m.imag, resultsIn: m.real)
        m.mPrint("4.3")
        m.randn(9, portable: true).mPrint("4.3")
        m = SJVsip.Matrix(columnLength: 5, rowLength: 3, type: .d, major: VSIP_COL)
        m.randu(11, portable: false).mPrint("5.4")
    }
    func testScalarPlus(){
        let a = SJVsip.Scalar(15.0)
        let b = SJVsip.Scalar(4.0)
        let d = a + b
        print("a + b = \(d.reald)")
    }
    func testDiv(){
        let a = SJVsip.Vector(length: 10, type: .f)
        let b = a.empty
        let c = a.empty
        a.fill(SJVsip.Scalar(1.0))
        b.fill(SJVsip.Scalar(2.0))
        SJVsip.div(numerator: a, denominator: b, quotient: c)
        c.mPrint("3.2")
    }
    func testScalarSqrt(){
        let a = SJVsip.Scalar(vsip_cmplx_d(4.0, 5.0))
        let b = vsip_csqrt_d(vsip_cmplx_d(4.0, 5.0))
        let c = a.sqrt
        print("( \(b.r), \(b.i))")
        print("( \(c.reald), \(c.imagd))")
        XCTAssert((b.r == c.reald) && (b.i == c.imagd))
    }
    func testSvd(){
        let n = 5
        let A = SJVsip.Matrix(columnLength: n, rowLength: n, type: .d, major: VSIP_ROW)
        let x = SJVsip.Vector(length: A.rowLength, type: A.type)
        let b = SJVsip.Vector(length: A.columnLength, type: A.type)
        let fmt = "6.5"
        let chk = 1E-14
        let _ = A.randn(5, portable: true)
        let _ = x.randn(9, portable: true)
        let normA = SJvsip.normFro(view: A)
        SJVsip.prod(A, times: x, resultsIn: b)
        print("Matrix A");A.mPrint(fmt)
        print("Known x vector");x.mPrint(fmt)
        print("Calculated b=Ax vector"); b.mPrint(fmt)
        // check that U S V^t gives back A
        let Ac = A.newCopy  // Ac is used for decompostion to keep original A
        let Ar = A.empty // new data space for result
        let svd = SJVsip.Svd(view: Ac)
        let sValues = svd.decompose(Ac)
        let U = svd.matU!
        let V = svd.matV!
        print("U");U.mPrint(fmt)
        print("Singular Values");sValues.mPrint(fmt)
        print("V");V.mPrint(fmt)
        let USr = U.empty // result of matrix product of U and Singular Vaules
        SJVsip.vmmul(vector: sValues, matrix: U, major: VSIP_ROW, resultsIn: USr)
        SJVsip.prod(USr, prod: V.transview, resultsIn: Ar)
        print("Result of USV^t"); Ar.mPrint(fmt)
        SJVsip.sub(A, subtract: Ar, resultsIn: Ar)
        var normChk = SJvsip.normFro(view:Ar).reald / normA.reald
        print("normChk: \(normChk)")
        print("Check USV^t equal input matrprix within reasonable bounds")
        XCTAssert( normChk < chk, "Check Failed for equality of USV^t with input matrix within reasonable bounds")
        let xe = x.empty  // x estimate for backsolve
        SJVsip.prod(U.transview, times: b, resultsIn: xe)
        SJVsip.div(numerator: xe, denominator: sValues, quotient: xe)
        SJVsip.prod(V, times: xe.newCopy, resultsIn: xe)
        print("solve for estimate of x from b");xe.mPrint(fmt)
        SJVsip.sub(x, subtract: xe, resultsIn: xe)
        normChk = SJvsip.normFro(view: xe).reald/SJvsip.normFro(view: x).reald
        print("Check estimate of x equal x within reasonable bounds (for Ax=b then x_est = V S^-1 U^T b)")
        XCTAssert( normChk < chk, "Check Failed for (in Ax=b) estimate of x equal to x within reasonable bounds")
    }
    func testHouseReflection(){ // create and check a householder reflection
        let n = 3
        let v = SJVsip.Vector(length: n, type: .d)
        let A = SJVsip.Matrix(columnLength: n, rowLength: n, type: .d, major: VSIP_ROW)
        let I = A.empty
        I.fill(SJVsip.Scalar(0.0))
        let Id = I.diagview
        Id.fill(SJVsip.Scalar(1.0))
        v[0] = SJVsip.Scalar(2.0); v[1] = SJVsip.Scalar(3.0); v[2] = SJVsip.Scalar(1.0)
        SJVsip.outer(alpha: SJVsip.Scalar(1.0), vecX: v, vecY: v, matC: A)
        let beta = SJVsip.Scalar(2.0 / SJVsip.dot(product: v, with: v).reald)
        SJVsip.mul(beta.reald, A, resultsIn: A)
        let P = A.empty
        P.fill(SJVsip.Scalar(0.0))
        P.diagview.fill(SJVsip.Scalar(1.0))
        SJVsip.sub(P, subtract: A, resultsIn: P)
        print(beta.reald)
        A.mPrint("4.3")
        P.mPrint("4.3")
        SJVsip.prod(P, prod: P, resultsIn: A)
        A.mPrint("4.3")
        let chk = (I-A).normFro //SJvsip.normFro(view: tmp).reald
        print("chk is \(chk)")
        XCTAssert(chk < 1E-10)
    }
    func testQrd(){
        let m = 6
        let n = 4
        let A = SJVsip.Matrix(columnLength: m, rowLength: n, type: .d, major: VSIP_ROW)
        // generate some data
        let _ = A.randn(8, portable: true)
        // keep a copy of original
        let Acopy = A.newCopy
        // make some space for an estimate of A to be calculated with Q and R
        let Ae = A.empty
        // get (Q,R)
        let qr = SJvsip.decompose(Acopy)
        let Q = qr.0
        let R = qr.1
        // Calculate Ae
        SJVsip.prod(Q, prod: R, resultsIn: Ae)
        // print original and estimate
        A.mPrint("5.3")
        Ae.mPrint("5.3")
        let chk = SJvsip.normFro(view: (A - Ae)).reald
        print("chk is \(chk)")
        XCTAssert(chk < 1E-10)
    }
    func testCgemp(){
        print("********\nTEST cgemp_f\n");
        let alpha = SJVsip.Scalar(vsip_cmplx_f(1.5,0.25))
        let beta  = SJVsip.Scalar(vsip_cmplx_f(-0.5,2.0))
        var data_ar: [Float] = [1.0, 2.0, -3.0,  4.0,  5.0,
                                5.0, 0.1,  0.2,  0.3,  0.4,
                                -4.0, 3.0,  2.0,  0.0, -1.0]
        var data_ai: [Float] = [0.1, 2.1, -2.0,  3.0,  5.0,
                                3.1, 1.1,  1.2, -5.3,  1.4,
                                -2.0, 2.2,  2.2,  0.5,  1.1]
        var data_br: [Float] = [0.4,  1.5, -2.7,  3.0,  9.0,
                                -1.1, -0.2, -0.3, -0.2,  1.3,
                                3.0,  2.0,  1.0,  4.0, -1.0]
        var data_bi: [Float] = [1.4,  1.2, -1.7,  3.0,  9.0,
                                -1.1, -3.1, -1.3, -0.2,  1.3,
                                2.2,  2.1,  1.1, 40.0, -1.0]
        var ans_nh_data_r: [Float] = [ 192.1675,    8.0525,  234.2950,
                                       11.6775,  -18.4175, -273.6475,
                                       -13.0900,  -10.6825,   26.1100 ]
        var ans_nh_data_i: [Float] = [ 28.9250,    9.0000, -188.0425,
                                       -19.1325,    6.0375,  -94.8375,
                                       34.2900,   17.5325,    7.5850 ]
        var ans_hn_data_r: [Float] = [
            -35.0800,  -25.7575,  -18.3475, -103.0250,   37.2750,
            24.6250,   19.8000,   -7.4075,  141.3150,   51.6400,
            10.0750,   -1.7650,   22.5000,  104.9800,  -67.5450,
            20.4150,   42.2025,  -11.5300,   64.0300,   80.8050,
            10.5100,   16.7750,  -35.2700,  116.5100,  139.1600
        ]
        var ans_hn_data_i: [Float] = [
            -7.1250,  -28.0950,  -13.2625, -243.6250,   30.1250,
            13.1550,    9.2675,    8.6025,  199.1650,    8.3150,
            -0.9250,    2.2200,    7.7750,  127.2800,  -22.4950,
            2.7100,    7.2200,    0.5925,   14.8200,   43.6700,
            7.0100,   -3.2925,    2.6175,  -44.3900,   28.7600
        ]
        var ans_tn_data_r: [Float] = [
            23.0200,  84.6762,  36.7462, 679.7875, -66.4125,
            -37.8225, -24.4900, -12.2688,-618.3525, -55.2650,
            1.4875,  -2.4025, -21.7000,-449.6300,  75.4575,
            -33.8675, -60.8587, -11.9650, -94.8350,-116.5725,
            -35.2850,  -2.6475,   9.8700, -39.6850,-148.9600
        ]
        var ans_tn_data_i: [Float] = [
            -102.2225, -76.7225, -54.2013,-317.1125, 102.1125,
            66.7325,  59.8587, -25.1238, 375.3125, 148.2625,
            28.2675,  -2.6900,  63.9775, 235.9000,-197.4375,
            57.7100,  92.6550, -46.4638, 152.1200, 227.9700,
            27.3650,  53.6788,-107.6362, 234.3250, 402.5000
        ]
        func blockbind_cf(length: Int, real: UnsafeMutablePointer<Float>, imag: UnsafeMutablePointer<Float>) -> SJVsip.Block {
            let blk = SJVsip.Block(length: length, type: .cf)
            let v = blk.bind(offset: 0, stride: 1, length: length)
            vsip_cvcopyfrom_user_f(real, imag, v.vsip)
            return blk
        }
        let block_a = blockbind_cf(length: 15, real: &data_ar, imag: &data_ai)
        let block_b = blockbind_cf(length: 15, real: &data_br, imag: &data_bi)
        let block_ans_nh = blockbind_cf(length: 9, real: &ans_nh_data_r, imag: &ans_nh_data_i)
        let block_ans_hn = blockbind_cf(length: 25, real: &ans_hn_data_r, imag: &ans_hn_data_i)
        let block_ans_tn = blockbind_cf(length: 25, real: &ans_tn_data_r, imag: &ans_tn_data_i)
        
        let block  = SJVsip.Block(length: 400, type: .cf)
        let au = block_a.bind(offset: 0,columnStride: 5,columnLength: 3,rowStride: 1,rowLength: 5);
        let bu = block_b.bind(offset: 0,columnStride: 5,columnLength: 3,rowStride: 1,rowLength: 5);
        let ans_nh = block_ans_nh.bind(offset: 0,columnStride: 3,columnLength: 3,rowStride: 1,rowLength: 3);
        let ans_hn = block_ans_hn.bind(offset: 0,columnStride: 5,columnLength: 5,rowStride: 1,rowLength: 5);
        let ans_tn = block_ans_tn.bind(offset: 0,columnStride: 5,columnLength: 5,rowStride: 1,rowLength: 5)
        let a = block.bind(offset: 15,columnStride: -1,columnLength: 3,rowStride: -3,rowLength: 5);
        let b = block.bind(offset: 100,columnStride: 2,columnLength: 3,rowStride: 10,rowLength: 5);
        let cnt = block.bind(offset: 200,columnStride: -8,columnLength: 3,rowStride: -2,rowLength: 3);
        let ctn = block.bind(offset: 300,columnStride: 2,columnLength: 5,rowStride: 15,rowLength: 5);
        let chk_nt = SJVsip.Matrix(columnLength: 3,rowLength: 3, type: .cf, major: VSIP_COL)
        let chk_nt_r = chk_nt.real
        let chk_tn = SJVsip.Matrix(columnLength: 5,rowLength: 5, type: .cf, major: VSIP_ROW)
        SJVsip.copy(from: au, to: a)
        SJVsip.copy(from: bu, to: b)
        cnt.fill(SJVsip.Scalar(vsip_cmplx_f(1.0,0.5)))
        ctn.fill(SJVsip.Scalar(vsip_cmplx_f(2.0,-1.0)))
        
        // test nh n=>NTRANS, h=>Herm
        print("\nvsip_cgemp_f(alpha,a,VSIP_MAT_NTRANS,b,VSIP_MAT_HERM,beta,c)\n")
        print("alpha = \(alpha)")
        print("matrix a = ");a.mPrint("6.4")
        print("matrix b = ");b.mPrint("6.4")
        print("beta = \(beta)")
        print("on input matrix c = "); cnt.mPrint("6.4")
        // for manual calculation
        let cexact = cnt.newCopy
        SJVsip.mul(beta, cexact, resultsIn: cexact)
        let aexact = a.newCopy
        SJVsip.mul(alpha, aexact, resultsIn: aexact)
        let bexact = b.transview.newCopy
        SJVsip.herm(b, output: bexact)
        let tmp = cnt.empty
        SJVsip.prod(aexact, prod: bexact, resultsIn: tmp)
        SJVsip.add(cexact, tmp, resultsIn: cexact)
        // cexact has result of gemp as manual calculation
        SJVsip.gemp(alpha: alpha,matA: a,opA: VSIP_MAT_NTRANS,matB: b,opB: VSIP_MAT_HERM,beta: beta,matC: cnt);
        print("on resultsIn matrix c = "); cnt.mPrint("6.4")
        print("right answer = "); ans_nh.mPrint("6.4")
        SJVsip.sub(cnt,subtract: ans_nh, resultsIn: chk_nt)
        var chk = SJvsip.normFro(view: chk_nt_r).reald
        print(chk); fflush(stdout)
        chk > 0.5 ? print("error\n") : print("correct\n")
        chk = SJvsip.normFro(view: (cnt - cexact)).reald
        XCTAssert(chk < 1E-4)
        print("Checking using manual calculation against gemp calculation gives error \(chk)"); fflush(stdout)
        
        /* test hn */
        print("\nvsip_cgemp_f(alpha,a,VSIP_MAT_HERM,b,VSIP_MAT_NTRANS,beta,c)\n");
        print("alpha = " + alpha.string(format: "4.2"))
        print("matrix a = ");a.mPrint("6.4")
        print("matrix b = ");b.mPrint("6.4")
        print("beta = " + beta.string(format: "4.2"))
        print("on input matrix c = ");ctn.mPrint("6.4")
        SJVsip.gemp(alpha: alpha,matA: a,opA: VSIP_MAT_HERM,matB: b,opB: VSIP_MAT_NTRANS,beta: beta,matC: ctn);
        print("on results In matrix c = ");ctn.mPrint("6.4")
        print("right answer = ");ans_hn.mPrint("6.4")
        SJVsip.sub(ctn, subtract: ans_hn, resultsIn: chk_tn)
        chk = SJvsip.normFro(view: chk_tn).reald
        if chk > 1E-4 {
            print("error\n");
        } else {
            print("correct\n");
        }
        
        /* test tn */
        print("\nvsip_cgemp_f(alpha,a,VSIP_MAT_TRANS,b,VSIP_MAT_NTRANS,beta,c)\n");
        print("alpha = " + alpha.string(format: "6.4"))
        print("matrix a = ");a.mPrint("6.4")
        print("matrix b = ");b.mPrint("6.4")
        print("beta = " + beta.string(format: "6.4"))
        print("on input matrix c = ");ctn.mPrint("6.4")
        SJVsip.gemp(alpha: alpha,matA: a,opA: VSIP_MAT_TRANS,matB: b,opB: VSIP_MAT_NTRANS,beta: beta,matC: ctn);
        print("on results In matrix c = ");ctn.mPrint("6.4")
        print("right answer = "); ans_tn.mPrint("6.4")
        SJVsip.sub(ctn, subtract: ans_tn, resultsIn: chk_tn)
        chk = SJvsip.normFro(view: chk_tn).reald
        if chk > 1E-4 {
            print("error\n")
        } else {
            print("correct\n")
        }
    }
    func testPut() {
        print("Testing Put")
        let v = SJVsip.Vector(length: 10, type: .d)
        v.fill(SJVsip.Scalar(0.0))
        v.put(1.0,1.3,1.4,1.2,0.9,3.9,5.6)
        v.mPrint("3.2")
    }
    func testKvc(){// KVC fails; must be doing something wrong."
        let v = SJVsip.Vector(length: 35, type: .d)
        let _ = v.ramp(SJVsip.Scalar(0.1), increment: SJVsip.Scalar(0.2))
        v.mPrint("3.2")
        //v.setValue(10, forKey: "length")
        //v.setValue(2, forKey: "stride")
        v.length = 10
        v.stride = 2
        v.mPrint("3.2")
        v.offset = 1
        v.mPrint("3.2")
    }
}
