//
//  qrd.swift
//  
//
//  Created by Randall R. Judd on 11/11/17.
//

import Foundation
import vsip
// MARK: - QRD
public class QRD{
    fileprivate struct Attrib {
        let m: Int
        let n: Int
        let op: vsip_qrd_qopt
    }
    var type: Scalar.Types {
        return (jVsip?.type)!
    }
    fileprivate(set) var amSet = false
    fileprivate let attrib: Attrib
    var columnLength: Int {
        get{
            return attrib.m
        }
    }
    var rowLength: Int {
        get {
            return attrib.n
        }
    }
    var qrdNoSaveQ: Bool{
        get {
            return attrib.op == VSIP_QRD_NOSAVEQ
        }
    }
    var qrdSaveQ: Bool{
        get {
            return attrib.op == VSIP_QRD_SAVEQ
        }
    }
    var qrdSaveQ1: Bool{
        get {
            return attrib.op == VSIP_QRD_SAVEQ1
        }
    }
    fileprivate class qr {
        var tryVsip : OpaquePointer?
        var vsip: OpaquePointer {
            get {
                return tryVsip!
            }
        }
        let jInit : JVSIP
        var type : Scalar.Types?
        init(){
            jInit = JVSIP()
        }
        
    }
    fileprivate class qr_f: qr {
        init(m: Int, n: Int, qopt: vsip_qrd_qopt){
            super.init()
            type = .f
            if let qrd = vsip_qrd_create_f(vsip_length(m),vsip_length(n),qopt){
                self.tryVsip = qrd
            } else {
                preconditionFailure("Failed to create vsip qrd object")
            }
        }
        deinit{
           /* if _isDebugAssertConfiguration(){
                print("vsip_qrd_destroy_f \(jInit.myId.int32Value)")
            }*/
            vsip_qrd_destroy_f(self.vsip)
            
        }
    }
    fileprivate class qr_d: qr {
        init(m: Int, n: Int, qopt: vsip_qrd_qopt){
            super.init()
            type = .d
            if let qrd = vsip_qrd_create_d(vsip_length(m),vsip_length(n),qopt){
                self.tryVsip = qrd
            } else {
                preconditionFailure("Failed to create vsip qrd object")
            }
        }
        deinit{
           /* if _isDebugAssertConfiguration(){
                print("vsip_qrd_destroy_d \(jInit.myId.int32Value)")
            }*/
            vsip_qrd_destroy_d(self.vsip)
            
        }
    }
    fileprivate class cqr_f: qr {
        init(m: Int, n: Int, qopt: vsip_qrd_qopt){
            super.init()
            type = .cf
            if let qrd = vsip_cqrd_create_f(vsip_length(m),vsip_length(n),qopt){
                self.tryVsip = qrd
            } else {
                preconditionFailure("Failed to create vsip qrd object")
            }
        }
        deinit{
            /*if _isDebugAssertConfiguration(){
                print("vsip_cqrd_destroy_f \(jInit.myId.int32Value)")
            }*/
            vsip_cqrd_destroy_f(self.vsip)
            
        }
    }
    fileprivate class cqr_d: qr {
        init(m: Int, n: Int, qopt: vsip_qrd_qopt){
            super.init()
            type = .cd
            if let qrd = vsip_cqrd_create_d(vsip_length(m),vsip_length(n),qopt){
                self.tryVsip = qrd
            } else {
                preconditionFailure("Failed to create vsip qrd object")
            }
        }
        deinit{
            /*if _isDebugAssertConfiguration(){
                print("vsip_cqrd_destroy_d \(jInit.myId.int32Value)")
            }*/
            vsip_cqrd_destroy_d(self.vsip)
            
        }
    }
    fileprivate let jVsip : qr?
    fileprivate var vsip: OpaquePointer {
        get {
            return (jVsip?.vsip)!
        }
    }
    public init(type: Scalar.Types, columnLength: Int, rowLength: Int, qopt: vsip_qrd_qopt) {
        attrib = Attrib(m: columnLength, n: rowLength, op: qopt)
        self.amSet = false
        switch type {
        case .f:
            jVsip = qr_f(m: columnLength, n: rowLength, qopt: qopt)
        case .d:
            jVsip = qr_d(m: columnLength, n: rowLength, qopt: qopt)
        case .cf:
            jVsip = cqr_f(m: columnLength, n: rowLength, qopt: qopt)
        case .cd:
            jVsip = cqr_d(m: columnLength, n: rowLength, qopt: qopt)
        default:
            self.jVsip = nil
            assert(false, "QRD not supported for this type")
        }
    }
    
    public func decompose(_ aMatrix: Matrix) -> Scalar {
        let t = (aMatrix.type, self.type)
        switch t {
        case(.f,.f):
            return Scalar(vsip_qrd_f(self.vsip, aMatrix.vsip))
        case(.d,.d):
            return Scalar(vsip_qrd_d(self.vsip, aMatrix.vsip))
        case(.cf,.cf):
            return Scalar(vsip_cqrd_f(self.vsip, aMatrix.vsip))
        case(.cd,.cd):
            return Scalar(vsip_cqrd_d(self.vsip, aMatrix.vsip))
        default:
            preconditionFailure("Types \(t) not supported for qrd decompostion")
        }
    }
    public func prodq(matrixOperator op: vsip_mat_op, matrixSide side: vsip_mat_side, matrix: Matrix) {
        let t = (self.type, op, side, matrix.type)
        switch t{
        case (.f, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .f):
            vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.d, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .d):
            vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.cf, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .cf):
            vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.cd, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .cd):
            vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.f, VSIP_MAT_TRANS, VSIP_MAT_LSIDE, .f):
            vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.d, VSIP_MAT_TRANS, VSIP_MAT_LSIDE, .d):
            vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.cf, VSIP_MAT_HERM, VSIP_MAT_LSIDE, .cf):
            vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.cd, VSIP_MAT_HERM, VSIP_MAT_LSIDE, .cd):
            vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.f, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .f):
            vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.d, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .d):
            vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.cf, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .cf):
            vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.cd, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .cd):
            vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.f, VSIP_MAT_TRANS, VSIP_MAT_RSIDE, .f):
            vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.d, VSIP_MAT_TRANS, VSIP_MAT_RSIDE, .d):
            vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
        case (.cf, VSIP_MAT_HERM, VSIP_MAT_RSIDE, .cf):
            vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
        case (.cd, VSIP_MAT_HERM, VSIP_MAT_RSIDE, .cd):
            vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
        default:
            preconditionFailure("Type \(t) not supported for QRD prodq.")
        }
    }
    public func solveR(matrixOperator opR: vsip_mat_op, alpha: Scalar, XB: Matrix) -> Int {
        let t = (opR, XB.type)
        switch t {
        case (VSIP_MAT_NTRANS, .f):
            return Int(vsip_qrdsolr_f(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_f, XB.vsip))
        case (VSIP_MAT_TRANS, .f):
            return Int(vsip_qrdsolr_f(self.vsip, VSIP_MAT_TRANS, alpha.vsip_f, XB.vsip))
        case (VSIP_MAT_NTRANS, .d):
            return Int(vsip_qrdsolr_d(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_d, XB.vsip))
        case (VSIP_MAT_TRANS, .f):
            return Int(vsip_qrdsolr_d(self.vsip, VSIP_MAT_TRANS, alpha.vsip_d, XB.vsip))
        case (VSIP_MAT_NTRANS, .cf):
            return Int(vsip_cqrdsolr_f(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_cf, XB.vsip))
        case (VSIP_MAT_TRANS, .cf):
            return Int(vsip_cqrdsolr_f(self.vsip, VSIP_MAT_HERM, alpha.vsip_cf, XB.vsip))
        case (VSIP_MAT_NTRANS, .d):
            return Int(vsip_cqrdsolr_d(self.vsip, VSIP_MAT_NTRANS, alpha.vsip_cd, XB.vsip))
        case (VSIP_MAT_TRANS, .f):
            return Int(vsip_cqrdsolr_d(self.vsip, VSIP_MAT_HERM, alpha.vsip_cd, XB.vsip))
        default:
            preconditionFailure("Case \(t) not found for solveR")
        }
    }
    public func solveCovariance(solveProblem prob: vsip_qrd_prob, XB: Matrix) -> Int {
        let t = (prob, XB.type)
        switch t {
        case (VSIP_COV, .f):
            return Int(vsip_qrsol_f(self.vsip, VSIP_COV, XB.vsip))
        case (VSIP_LLS, .f):
            return Int(vsip_qrsol_f(self.vsip, VSIP_LLS, XB.vsip))
        case (VSIP_COV, .d):
            return Int(vsip_qrsol_d(self.vsip, VSIP_COV, XB.vsip))
        case (VSIP_LLS, .d):
            return Int(vsip_qrsol_d(self.vsip, VSIP_LLS, XB.vsip))
        case (VSIP_COV, .cf):
            return Int(vsip_cqrsol_f(self.vsip, VSIP_COV, XB.vsip))
        case (VSIP_LLS, .cf):
            return Int(vsip_cqrsol_f(self.vsip, VSIP_LLS, XB.vsip))
        case (VSIP_COV, .cd):
            return Int(vsip_cqrsol_d(self.vsip, VSIP_COV, XB.vsip))
        case (VSIP_LLS, .cd):
            return Int(vsip_cqrsol_d(self.vsip, VSIP_LLS, XB.vsip))
        default:
            preconditionFailure("Case \(t) not found for Covariance/LeastSquare solver")
        }
    }
}

