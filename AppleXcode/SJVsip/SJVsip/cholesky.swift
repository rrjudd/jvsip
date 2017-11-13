//
//  cholesky.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/12/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
// MARK: - Chold
public class Chold {
    var size: Int
    var type: Scalar.Types {
        return (jVsip?.type)!
    }
    fileprivate var vsip: OpaquePointer {
        get {
            return (jVsip?.vsip)!
        }
    }
    fileprivate class chol {
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
    fileprivate class chol_d: chol {
        init(size: Int){
            super.init()
            self.type = .d
            if let chold = vsip_chold_create_d(VSIP_TR_LOW, vsip_length(size)){
                self.tryVsip = chold
            } else {
                preconditionFailure("Failed to create vsip cholesky object")
            }
        }
        deinit{
           /* if _isDebugAssertConfiguration(){
                print("vsip_chold_destroy_d \(jInit.myId.int32Value)")
            }*/
            vsip_chold_destroy_d(self.vsip)
            
        }
    }
    fileprivate class chol_f: chol {
        init(size: Int){
            super.init()
            self.type = .f
            if let chold = vsip_chold_create_f(VSIP_TR_LOW, vsip_length(size)){
                self.tryVsip = chold
            } else {
                preconditionFailure("Failed to create vsip cholesky object")
            }
        }
        deinit{
           /* if _isDebugAssertConfiguration(){
                print("vsip_chold_destroy_f \(jInit.myId.int32Value)")
            }*/
            vsip_chold_destroy_f(self.vsip)
            
        }
    }
    fileprivate class chol_cd: chol {
        init(size: Int){
            super.init()
            self.type = .cd
            if let chold = vsip_cchold_create_d(VSIP_TR_LOW, vsip_length(size)){
                self.tryVsip = chold
            } else {
                preconditionFailure("Failed to create vsip cholesky object")
            }
        }
        deinit{
           /* if _isDebugAssertConfiguration(){
                print("vsip_cchold_destroy_d \(jInit.myId.int32Value)")
            }*/
            vsip_cchold_destroy_d(self.vsip)
            
        }
    }
    fileprivate class chol_cf: chol {
        init(size: Int){
            super.init()
            self.type = .cf
            if let chold = vsip_cchold_create_f(VSIP_TR_LOW, vsip_length(size)){
                self.tryVsip = chold
            } else {
                preconditionFailure("Failed to create vsip cholesky object")
            }
        }
        deinit{
          /*  if _isDebugAssertConfiguration(){
                print("vsip_cchold_destroy_f \(jInit.myId.int32Value)")
            }*/
            vsip_cchold_destroy_f(self.vsip)
        }
    }
    fileprivate let jVsip : chol?
    init(type: Scalar.Types, size: Int) {
        self.size = size
        switch type {
        case .f:
            self.jVsip = chol_f(size: size)
        case .d:
            self.jVsip = chol_d(size: size)
        case .cf:
            self.jVsip = chol_cf(size: size)
        case .cd:
            self.jVsip = chol_cd(size: size)
        default:
            preconditionFailure ("type \(type) not found for cholesky decomposition")
        }
    }
    public func decompose(_ A: Matrix) -> Int {
        let t = (self.type, A.type)
        switch t {
        case (.f, .f):
            return Int(vsip_chold_f(self.vsip, A.vsip))
        case (.d, .d):
            return Int(vsip_chold_d(self.vsip, A.vsip))
        case (.cf, .cf):
            return Int(vsip_cchold_f(self.vsip, A.vsip))
        case (.cd, .cd):
            return Int(vsip_cchold_d(self.vsip, A.vsip))
        default:
            preconditionFailure("Type \(t) not supported for cholesky decompostion")
        }
    }
    public func solve(_ XB: Matrix) -> Int {
        let t = (self.type, XB.type)
        switch t {
        case (.f, .f):
            return Int(vsip_cholsol_f(self.vsip, XB.vsip))
        case (.d, .d):
            return Int(vsip_cholsol_d(self.vsip, XB.vsip))
        case (.cf, .cf):
            return Int(vsip_ccholsol_f(self.vsip, XB.vsip))
        case (.cd, .cd):
            return Int(vsip_ccholsol_d(self.vsip, XB.vsip))
        default:
            preconditionFailure ("type \(type) not found for cholesky decomposition")
        }
    }
}

