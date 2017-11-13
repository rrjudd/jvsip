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
            let ac = A.col(i)
            let _ = ac.real.ramp(Vsip.Scalar(-1.3), increment: Vsip.Scalar(1.1))
            let _ = ac.imag.ramp(Vsip.Scalar(1.3), increment: Vsip.Scalar(-1.1))
        }
        let ad = A.diagview
        let _ = ad.real.ramp(Vsip.Scalar(3.0), increment: Vsip.Scalar(1.2))
        let _ = ad.imag.ramp(Vsip.Scalar(3.0), increment: Vsip.Scalar(-1.2))
        for i in 0..<BX.columnLength {  //Data for matrix B; fill by row
            let bxr = BX.row(i)
            let _ = bxr.real.ramp(Vsip.Scalar(0.1), increment: Vsip.Scalar(Double(i)/3.0))
            let _ = bxr.imag.ramp(Vsip.Scalar(0.2), increment: Vsip.Scalar(Double(i)/3.0))
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
        Vsip.herm(A, output: AH);
        Vsip.prod(AH, times: A,resultsIn: AHA);
        /* calculate AH * B */
        Vsip.prod(AH, times: BX, resultsIn: X);
        print("\nAH prod A = "); AHA.mPrint("4.2")
        print("\nAH prod B = ");X.mPrint("4.2")
        let _ = chol.decompose(AHA)
        let _ = chol.solve(X) // B replaced by X
        print("\nX = "); X.mPrint("7.5")
        /* check */
        print("\ncheck\n (AH prod A) prod X := AH prod B");
        /* restore AHA */
        Vsip.prod(AH, times: A, resultsIn: AHA)
        /* calculate AHA prod X */
        Vsip.prod(AHA, times: X, resultsIn: B)
        Vsip.copy(from: X, to: ANS); /* if correct Need ANSwer */
        /* for check place AH * BX into X */
        Vsip.prod(AH, times: BX, resultsIn: X)
        print("\nAHA * X ="); //VU_cmprintm_d("4.2",B);
        Vsip.sub(X, subtract: B, resultsIn: X)
        var check = Vsip.Jvsip.normFro(view: X).reald
        if(check < 0.0001) {
            print("correct")
        } else {
            print("error")
        }
        /* restore X for use by covsol */
        Vsip.prod(AH, times: BX, resultsIn: X);
        /* solve using ccovsol */
        /* copy data so we can solve covariance problem later on */
        
        Vsip.copy(from: A, to: A1)
        print("\nSolve using ccovsol_d ");
        let _ = Vsip.covsol(A1,inputOutput: X)
        print("Expect X to be\n");
        ANS.mPrint("7.5")
        print("\nX = ")
        X.mPrint("7.5")
        Vsip.sub(ANS, subtract: X, resultsIn: X)
        check = Vsip.Jvsip.normFro(view: X).reald
        if check < 0.0001 {
            print("correct");
        } else {
            print("error\n");
        }
    }
    func testlud(){
        print("********\nTEST lud_d\n");
        let block = Vsip.Block(length: 500, type: .d);
        let AC = block.bind(0, columnStride: 6, columnLength: 6, rowStride: 1, rowLength: 6)
        let AG = block.bind(36, columnStride: 2, columnLength: 6, rowStride: 18, rowLength: 6)
        let IC = block.bind(150, columnStride: 1, columnLength: 6, rowStride: 6, rowLength: 6)
        let IG = block.bind(200, columnStride: 2, columnLength: 6, rowStride: 14, rowLength: 6)
        let B = block.bind(300, columnStride: 6, columnLength: 6, rowStride: 1, rowLength: 6)
        let A = block.bind(350, columnStride: 6, columnLength: 6, rowStride: 1, rowLength: 6)
        let X = block.bind(400, columnStride: 5, columnLength: 6, rowStride: 1, rowLength: 3)
        let Y = block.bind(450, columnStride: 3, columnLength: 6, rowStride: 1, rowLength: 3)
        let ludC = Vsip.LUD(type: .d, size: 6)
        let ludG = Vsip.LUD(type: .d, size: 6)
        var chk = 0.0
        // data[6][6]
        let data = [
            [0.50,     7.00,    10.00,    12.00,    -3.00,     0.00],
            [2.00,    13.00,    18.00,     6.00,     0.00,   130.00],
            [3.00,    -9.00,     2.00,     3.00,     2.00,    -9.00],
            [4.00,     2.00,     2.00,     4.00,     1.00,     2.00],
            [0.20,     2.00,     9.00,     4.00,     1.00,     2.00],
            [0.10,     2.00,     0.30,     4.00,     1.00,     2.00]]
        
        // ydata[6][3]
        let ydata = [
            [  77.85,   155.70,   311.40],
            [ 942.00,  1884.00,  3768.00],
            [   1.00,     2.00,     4.00],
            [  68.00,   136.00,   272.00],
            [  85.20,   170.40,   340.80],
            [  59.00,   118.00,   236.00]]
        let Ydata = X.empty
        
        // Ident[6][6] => identity matrix
        let Ident = Vsip.Matrix(columnLength: 6, rowLength: 6, type: .d, major: VSIP_COL)
        Ident.fill(Vsip.Scalar(0.0))
        Ident.diagview.fill(Vsip.Scalar(1.0))
        
        // put data in our matrices
        // we could use (for instance) > let AC = A.copy but we also test view indexing for robustness
        // thus the obnoxious block binds in the first few lines.
        for i in 0..<6 {
            for j in 0..<6 {
                A[i,j] = Vsip.Scalar(data[i][j])
            }
            for j in 0..<3 {
                X[i,j] = Vsip.Scalar(ydata[i][j])
            }
        }
        Vsip.copy(from: A, to: AC)
        Vsip.copy(from: A, to: AG)
        Vsip.copy(from: Ident, to: IG)
        Vsip.copy(from: Ident, to: IC)
        Vsip.copy(from: X, to: Ydata)
        
        print("Matrix A = \n");A.mPrint("7.2");fflush(stdout)
        let _ = ludC.decompose(AC)  // AC and AG are modified and used by lud decompose operation
        let _ = ludG.decompose(AG)
        print("vsip_lusol(lud,VSIP_MAT_NTRANS,X)\n");
        print("Where I is the identity matrix")
        print("Solve A X = I \n"); fflush(stdout);
        let _ = ludC.solve(matOp: VSIP_MAT_NTRANS, IC)
        let _ = ludG.solve(matOp: VSIP_MAT_NTRANS, IG)
        
        print("for compact case X = \n");IC.mPrint("8.4"); fflush(stdout);
        print("for general case X = \n");IG.mPrint("8.4"); fflush(stdout);
        chk = Vsip.Jvsip.normFro(view: (IC - IG)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout);
        Vsip.prod(A,times: IC, resultsIn: B)
        chk = Vsip.Jvsip.normFro(view: (B - Ident)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout);
        print("(line 175) chk = \(chk)")
        Vsip.prod(A,times: IG, resultsIn: B)
        chk = Vsip.Jvsip.normFro(view: (B - Ident)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout);
        print("(line 179) chk = \(chk)")
        print("mprod(A,X) = \n"); B.mPrint("8.4"); fflush(stdout);
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout);
        
        /************************************************/
        /* check case VSIP_MAT_TRANS */
        print("Matrix Transpose A = \n"); A.transview.mPrint("7.2");fflush(stdout)
        Vsip.copy(from: Ident, to: IC)
        Vsip.copy(from: Ident, to: IG)
        
        print("vsip_lusol(lud,VSIP_MAT_TRANS,X)\n");
        print("Solve trans(A) X = I \n"); fflush(stdout);
        let _ = ludC.solve(matOp: VSIP_MAT_TRANS, IC)
        let _ = ludG.solve(matOp: VSIP_MAT_TRANS,IG)
        print("for compact case X = \n");IC.mPrint("8.4"); fflush(stdout);
        print("for general case X = \n");IG.mPrint("8.4"); fflush(stdout);
        chk = Vsip.Jvsip.normFro(view: (IC - IG)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout);
        Vsip.prod(A.transview,times: IC, resultsIn: B);
        
        chk = Vsip.Jvsip.normFro(view: (B-Ident)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n")
        Vsip.prod(A.transview,times: IG, resultsIn: B);
        chk = Vsip.Jvsip.normFro(view: (B - Ident)).reald
        print("mprod(trans(A),X) = \n"); B.mPrint("8.3")
        (chk > 1.0E-10) ? print("error\n") : print("correct\n")
        
        /************************************************/
        /* check case A X = B for VSIP_MAT_NTRANS */
        print("check A X = Y; VSIP_MAT_NTRANS\n");
        print("Y = \n");X.mPrint("8.4")
        let _ = ludC.solve(matOp: VSIP_MAT_NTRANS, X)
        print("X = \n"); X.mPrint("8.4");
        Vsip.prod(A,times: X, resultsIn: Y)
        print(" Y = A X\n");Y.mPrint("8.4")
        chk = Vsip.Jvsip.normFro(view: (Y - Ydata)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout);
        
        /************************************************/
        /* check case trans(A) X = B for VSIP_MAT_TRANS */
        Vsip.copy(from: Ydata, to: X)
        print("Y = \n"); X.mPrint("8.4")
        let _ = ludG.solve(matOp: VSIP_MAT_TRANS, X)
        Vsip.prod(A.transview,times: X, resultsIn: Y)
        print("X = \n");X.mPrint("8.4")
        print("Y = trans(A) X\n");Y.mPrint("8.4")
        chk = Vsip.Jvsip.normFro(view: (Y - Ydata)).reald
        (chk > 1.0E-10) ? print("error\n") : print("correct\n"); fflush(stdout)
    }
    
    
}

