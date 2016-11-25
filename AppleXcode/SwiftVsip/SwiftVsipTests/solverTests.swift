//
//  solverTests.swift
//  SwiftVsip
//
//  Created by Randall R. Judd on 11/23/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import XCTest
@testable import SwiftVsip

class solverTests: XCTestCase {
    func testCovarianceSolver() {
        
        let A = Vsip.Matrix(columnLength: 10, rowLength: 6, type: .cd, major: VSIP_ROW)
        let BX = Vsip.Matrix(columnLength: 10, rowLength: 3, type: .cd, major: VSIP_ROW)
        let X = Vsip.Matrix(columnLength: 6, rowLength: 3, type: .cd, major: VSIP_ROW)
        let ANS = Vsip.Matrix(columnLength: 6, rowLength: 3, type: .cd, major: VSIP_ROW)
        
        /* create space for ccovsol data */
        let ablock = Vsip.Block(length: 500,type: .cd)
        let A1 = ablock.bind(200,columnStride: -3,columnLength: 10,rowStride: -31,rowLength: 6)
        let a0 = Vsip.Scalar(vsip_cmplx_d(0.0,0.0))
        A.fill(a0)
        BX.fill(a0)
        
        
        print("********\nTEST ccovsol_d\n");
        print("Test covariance solver vsip_ccovsol_d\n");
        /* Solving for X in A X = B */
        /* A is (M,N) M >= N; X is (N,K), B is (N,K) */
        for i in 0..<A.rowLength {  // Data for matrix A; fill by column
            let ac = A.colview(col: i)
            let _ = ac.real.ramp(-1.3, increment: 1.1)
            let _ = ac.imag.ramp(1.3, increment: -1.1)
        }
        let ad = A.diagview
        let _ = ad.real.ramp(3.0, increment: 1.2)
        let _ = ad.imag.ramp(3.0, increment: -1.2)
        for i in 0..<BX.columnLength {  //Data for matrix B; fill by row
            let bxr = BX.rowview(row: i)
            let _ = bxr.real.ramp(0.1, increment: Double(i)/3.0)
            let _ = bxr.imag.ramp(0.2, increment: Double(i)/3.0)
        }
        print("Input data \n")
        print("A = "); A.mPrint("4.2")
        print("\nB = "); BX.mPrint("4.2")
        let chol = Vsip.Chold(type: .cd, size: 6)
        let B = Vsip.Matrix(columnLength: 6, rowLength: 3, type: .cd, major: VSIP_ROW)
        let AHA = Vsip.Matrix(columnLength: 6, rowLength: 6, type: .cd, major: VSIP_ROW)
        let AH = Vsip.Matrix(columnLength: 6, rowLength: 10,type: .cd, major: VSIP_ROW)
        /* solve using Cholesky and AHA matrix */
        print("\nSolve using Cholesky");
        
        print("\nA is input matrix, AT (AH) is transpose (Hermitian) of A\n");
        print("Solve for X least squares using (AH prod A ) prod X = AH prod B\n");
        /* calculate matrix AHA = AH * A */
        Vsip.herm(A, complexOuputMatrix: AH);
        Vsip.prod(AH, times: A,resultIn: AHA);
        /* calculate AH * B */
        Vsip.prod(AH, times: BX, resultIn: X);
        print("\nAH prod A = "); AHA.mPrint("4.2")
        print("\nAH prod B = ");X.mPrint("4.2")
        let _ = chol.decompose(AHA)
        let _ = chol.solve(X) // B replaced by X
        print("\nX = "); X.mPrint("7.5")
        /* check */
        print("\ncheck\n (AH prod A) prod X := AH prod B");
        /* restore AHA */
        Vsip.prod(AH, times: A, resultIn: AHA)
        /* calculate AHA prod X */
        Vsip.prod(AHA, times: X, resultIn: B)
        Vsip.copy(from: X, to: ANS); /* if correct Need ANSwer */
        /* for check place AH * BX into X */
        Vsip.prod(AH, times: BX, resultIn: X)
        print("\nAHA * X ="); //VU_cmprintm_d("4.2",B);
        Vsip.sub(X, subtract: B, output: X)
        var check = Vsip.Jvsip.normFro(view: X).reald
        if(check < 0.0001) {
            print("correct")
        } else {
            print("error")
        }
        /* restore X for use by covsol */
        Vsip.prod(AH, times: BX, resultIn: X);
        /* solve using ccovsol */
        /* copy data so we can solve covariance problem later on */
        
        Vsip.copy(from: A, to: A1)
        print("\nSolve using ccovsol_d ");
        let _ = Vsip.covsol(A1,inputOutput: X)
        print("Expect X to be\n");
        ANS.mPrint("7.5")
        print("\nX = ")
        X.mPrint("7.5")
        Vsip.sub(ANS, subtract: X, output: X)
        check = Vsip.Jvsip.normFro(view: X).reald
        if check < 0.0001 {
            print("correct");
        } else {
            print("error\n");
        }
    }
}

