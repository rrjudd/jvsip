//
//  LUD.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/11/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
// MARK: - LU
public class LUD {
    var type: Scalar.Types {
        return (jVsip?.type)!
    }
    fileprivate class lu {
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
    fileprivate class lu_f: lu{
        init(_ size: Int){
            super.init()
            type = .f
            if let lud = vsip_lud_create_f(vsip_length(size)){
                self.tryVsip = lud
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
        }
        deinit{
            /*if _isDebugAssertConfiguration(){
                print("vsip_lud_destroy_f \(jInit.myId.int32Value)")
            }*/
            vsip_lud_destroy_f(self.vsip)
        }
    }
    fileprivate class lu_d: lu{
        init(_ size: Int){
            super.init()
            type = .d
            if let lud = vsip_lud_create_d(vsip_length(size)){
                self.tryVsip = lud
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
        }
        deinit{
            /*if _isDebugAssertConfiguration(){
                print("vsip_lud_destroy_d \(jInit.myId.int32Value)")
            }*/
            vsip_lud_destroy_d(self.vsip)
        }
    }
    fileprivate class clu_f: lu{
        init(_ size: Int){
            super.init()
            type = .cf
            if let lud = vsip_clud_create_f(vsip_length(size)){
                self.tryVsip = lud
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
        }
        deinit{
            /*if _isDebugAssertConfiguration(){
                print("vsip_clud_destroy_f \(jInit.myId.int32Value)")
            }*/
            vsip_clud_destroy_f(self.vsip)
        }
    }
    fileprivate class clu_d: lu{
        init(_ size: Int){
            super.init()
            type = .cd
            if let lud = vsip_clud_create_d(vsip_length(size)){
                self.tryVsip = lud
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
        }
        deinit{
            /*if _isDebugAssertConfiguration(){
                print("vsip_clud_destroy_d \(jInit.myId.int32Value)")
            }*/
            vsip_clud_destroy_d(self.vsip)
        }
    }
    fileprivate let jVsip : lu?
    fileprivate var vsip: OpaquePointer {
        get {
            return (jVsip?.vsip)!
        }
    }
    public init(type: Scalar.Types, size: Int) {
        switch type {
        case .f:
            jVsip = lu_f(size)
        case .d:
            jVsip = lu_d(size)
        case .cf:
            jVsip = clu_f(size)
        case .cd:
            jVsip = clu_d(size)
        default:
            preconditionFailure("Type \(type) not supported")
        }
    }
    public func decompose(_ A: Matrix) -> Int{
        let t = (self.type, A.type)
        switch t{
        case (.f, .f):
            return Int(vsip_lud_f(self.vsip, A.vsip))
        case (.d, .d):
            return Int(vsip_lud_d(self.vsip, A.vsip))
        case (.cf, .cf):
            return Int(vsip_clud_f(self.vsip, A.vsip))
        case (.cd, .cd):
            return Int(vsip_clud_d(self.vsip, A.vsip))
        default:
            preconditionFailure("Type \(t) not found for lud decompose")
        }
    }
    public func solve(matOp: vsip_mat_op, _ XB: Matrix) -> Int{
        let t = (matOp, self.type, XB.type)
        switch t {
        case (VSIP_MAT_NTRANS,.f,.f):
            return Int(vsip_lusol_f(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
        case (VSIP_MAT_NTRANS,.d,.d):
            return Int(vsip_lusol_d(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
        case (VSIP_MAT_NTRANS,.cf,.cf):
            return Int(vsip_clusol_f(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
        case (VSIP_MAT_NTRANS,.cd,.cd):
            return Int(vsip_clusol_d(self.vsip, VSIP_MAT_NTRANS, XB.vsip))
        case (VSIP_MAT_TRANS,.f,.f):
            return Int(vsip_lusol_f(self.vsip, VSIP_MAT_TRANS, XB.vsip))
        case (VSIP_MAT_TRANS,.d,.d):
            return Int(vsip_lusol_d(self.vsip, VSIP_MAT_TRANS, XB.vsip))
        case (VSIP_MAT_HERM,.cf,.cf):
            return Int(vsip_clusol_f(self.vsip, VSIP_MAT_HERM, XB.vsip))
        case (VSIP_MAT_HERM,.cd,.cd):
            return Int(vsip_clusol_d(self.vsip, VSIP_MAT_HERM, XB.vsip))
        default:
            preconditionFailure("Type \(t) not found for lud solve")
        }
    }
}

