//
//  svd.swift
//  
//
//  Created by Randall R. Judd on 11/10/17.
//

import Foundation
import vsip
public class Svd {
    let type: Scalar.Types
    let n: Int  // length of singular value vector
    var amSet = false
    fileprivate let jVsip : sv?
    var vecSv: Vector?
    public struct Attrib {
        let m: Int
        let n: Int
        let saveU: vsip_svd_uv
        let saveV: vsip_svd_uv
        init(columnLength: Int, rowLength: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            m=columnLength
            n=rowLength
            self.saveU=saveU
            self.saveV=saveV
        }
        var size : (Int, Int) {
            return (m,n)
        }
    }
    let attr : Attrib
    fileprivate class sv {
        var tryVsip : OpaquePointer?
        var tryS: OpaquePointer?
        var vsip: OpaquePointer {
            get {
                return tryVsip!
            }
        }
        var s: OpaquePointer {
            get {
                return tryS!
            }
        }
        let jInit : JVSIP
        var type : Scalar.Types?
        init(){
            jInit = JVSIP()
        }
    }
    fileprivate class sv_f : sv {
        init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            super.init()
            type = .f
            if let svd = vsip_svd_create_f(vsip_length(m),vsip_length(n),saveU,saveV){
                self.tryVsip = svd
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
            if let s = vsip_vcreate_f(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                self.tryS = s
            } else {
                preconditionFailure("Failed to create vsip s object")
            }
        }
        deinit{
            if _isDebugAssertConfiguration(){
                print("vsip_svd_destroy_f \(jInit.myId.int32Value)")
                print("svd s destroy")
            }
            vsip_svd_destroy_f(self.vsip)
            vsip_valldestroy_f(self.s)
        }
    }
    fileprivate class sv_d : sv {
        init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            super.init()
            type = .f
            if let svd = vsip_svd_create_d(vsip_length(m),vsip_length(n),saveU,saveV){
                self.tryVsip = svd
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
            if let s = vsip_vcreate_d(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                self.tryS = s
            } else {
                preconditionFailure("Failed to create vsip s object")
            }
        }
        deinit{
            if _isDebugAssertConfiguration(){
                print("vsip_svd_destroy_d \(jInit.myId.int32Value)")
                print("svd s destroy")
            }
            vsip_svd_destroy_d(self.vsip)
            vsip_valldestroy_d(self.s)
        }
    }
    fileprivate class csv_f : sv {
        init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            super.init()
            type = .cf
            if let svd = vsip_csvd_create_f(vsip_length(m),vsip_length(n),saveU,saveV){
                self.tryVsip = svd
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
            if let s = vsip_vcreate_f(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                self.tryS = s
            } else {
                preconditionFailure("Failed to create vsip s object")
            }
        }
        deinit{
            if _isDebugAssertConfiguration(){
                print("vsip_svd_destroy_f \(jInit.myId.int32Value)")
                print("svd s destroy")
            }
            vsip_csvd_destroy_f(self.vsip)
            vsip_valldestroy_f(self.s)
        }
    }
    fileprivate class csv_d : sv {
        init(m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
            super.init()
            type = .cd
            if let svd = vsip_csvd_create_d(vsip_length(m),vsip_length(n),saveU,saveV){
                self.tryVsip = svd
            } else {
                preconditionFailure("Failed to create vsip svd object")
            }
            if let s = vsip_vcreate_d(vsip_length((m<n) ? m:n),VSIP_MEM_NONE){
                self.tryS = s
            } else {
                preconditionFailure("Failed to create vsip s object")
            }
        }
        deinit{
            if _isDebugAssertConfiguration(){
                print("vsip_csvd_destroy_cd \(jInit.myId.int32Value)")
                print("svd s destroy")
            }
            vsip_csvd_destroy_d(self.vsip)
            vsip_valldestroy_d(self.s)
        }
    }
    
    public init(type: Scalar.Types,columnLength m: Int, rowLength n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
        self.n = (m<n) ? m:n
        self.type = type
        self.attr = Attrib(columnLength: m, rowLength: n, saveU: saveU, saveV: saveV)
        switch type {
        case .d:
            self.jVsip = sv_d(m: m,n: n,saveU: saveU, saveV: saveV)
        case .f:
            self.jVsip = sv_f(m: m,n: n,saveU: saveU, saveV: saveV)
        case .cd:
            self.jVsip = csv_d(m: m,n: n,saveU: saveU, saveV: saveV)
        case .cf:
            self.jVsip = csv_f(m: m,n: n,saveU: saveU, saveV: saveV)
        default:
            self.jVsip = nil
            assert(false, "SVD not supported for this type")
        }
    }
    public convenience init(view: Matrix, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
        self.init(type: view.type, columnLength: view.columnLength, rowLength: view.rowLength, saveU: saveU, saveV: saveV)
    }
    public convenience init(view: Matrix){
        self.init(type: view.type, columnLength: view.columnLength, rowLength: view.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
    }
    fileprivate var vsip: OpaquePointer? {
        return self.jVsip!.vsip
    }
    fileprivate var s: OpaquePointer? {// singular values
        return self.jVsip!.s
    }
    public func decompose(_ matrix: Matrix, singularValues: Vector){
        switch (self.type, matrix.type, singularValues.type){
        case (.d, .d, .d):
            vsip_svd_d(self.vsip, matrix.vsip, self.s!)
            vsip_vcopy_d_d(self.s!, singularValues.vsip)
        case (.f, .f, .f):
            vsip_svd_f(self.vsip, matrix.vsip, self.s!)
            vsip_vcopy_f_f(self.s!, singularValues.vsip)
        case (.cd, .cd, .d):
            vsip_csvd_d(self.vsip, matrix.vsip, self.s!)
            vsip_vcopy_d_d(self.s!, singularValues.vsip)
        case (.cf, .cf, .f):
            vsip_csvd_f(self.vsip, matrix.vsip, self.s!)
            vsip_vcopy_f_f(self.s!, singularValues.vsip)
        default:
            preconditionFailure("function not supported for input/resultsIn views")
        }
        self.vecSv = singularValues.newCopy
        self.amSet = true
    }
    public func decompose(_ matrix: Matrix) -> Vector {
        let v: Vector
        switch matrix.type {
        case .cd, .d:
            v = Vector(length: self.n, type: .d)
        case .cf, .f:
            v = Vector(length: self.n, type: .f)
        default:
            preconditionFailure("Case not found for decompose")
        }
        self.decompose(matrix, singularValues: v)
        self.vecSv = v.newCopy
        return v
    }
    /*!
     Function matU returns 0 on success
     Output data is stored in matrix matU in natural order starting at
     element index (0,0). Matrix matU must be large enough to hold the
     resultsIn data
     */
    public func matU(_ lowColumn: Int, highColumn: Int, matU: Matrix) -> Int {
        let low = vsip_scalar_vi(lowColumn)
        let high = vsip_scalar_vi(highColumn)
        assert(low <= high, "Error in column selection")
        let highMax = vsip_scalar_vi((matU.rowLength))
        let vsipSv = self.vsip // VSIPL pointer to singular value object
        let vsipC = matU.vsip // VSIPL pointer to U Matrix
        
        switch (self.attr.saveU, matU.type, self.type){
        case (VSIP_SVD_UVFULL, .f, .f):
            return Int(vsip_svdmatu_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVFULL, .cf, .cf):
            return Int(vsip_csvdmatu_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVFULL, .d, .d):
            return Int(vsip_svdmatu_d(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVFULL, .cd, .cd):
            return Int(vsip_csvdmatu_d(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .f, .f):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_svdmatu_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .cf, .cf):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_csvdmatu_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .d, .d):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_svdmatu_d(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .cd, .cd):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_csvdmatu_d(vsipSv, low, high, vsipC))
        default:
            if self.attr.saveU == VSIP_SVD_UVNOS{
                preconditionFailure("SVD Created without U Matrix")
            } else {
                preconditionFailure("SVD Not supported for these types")
            }
        }
    }
    /*!
     Function matV returns 0 on success
     Output data is stored in matrix matV in natural order starting at
     element index (0,0). Matrix matV must be large enough to hold the
     resultsIn data
     */
    public func matV(_ lowColumn: Int, highColumn: Int, matV: Matrix) -> Int {
        let low = vsip_scalar_vi(lowColumn)
        let high = vsip_scalar_vi(highColumn)
        assert(low <= high, "Error in column selection")
        let highMax = vsip_scalar_vi(matV.rowLength)
        let vsipSv = self.vsip // VSIPL pointer to singular value object
        let vsipC = matV.vsip // VSIPL pointer to V Matrix
        switch (self.attr.saveU, matV.type, self.type){
        case (VSIP_SVD_UVFULL, .f, .f):
            return Int(vsip_svdmatv_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVFULL, .cf, .cf):
            return Int(vsip_csvdmatv_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVFULL, .d, .d):
            return Int(vsip_svdmatv_d(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVFULL, .cd, .cd):
            return Int(vsip_csvdmatv_d(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .f, .f):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_svdmatv_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .cf, .cf):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_csvdmatv_f(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .d, .d):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_svdmatv_d(vsipSv, low, high, vsipC))
        case (VSIP_SVD_UVPART, .cd, .cd):
            precondition(high <= highMax, "Input matrix row length to small")
            return Int(vsip_csvdmatv_d(vsipSv, low, high, vsipC))
        default:
            if self.attr.saveU == VSIP_SVD_UVNOS {
                preconditionFailure("SVD Created without V Matrix")
            } else {
                preconditionFailure("SVD Not supported for these types")
            }
        }
    }
    public func produ(op: vsip_mat_op, side: vsip_mat_side, matrix: Matrix) -> Int {
        let vsipSv = self.vsip
        let vsipC = matrix.vsip
        switch (self.attr.saveU, matrix.type, self.type){
        case (VSIP_SVD_UVFULL, .f, .f):
            return Int(vsip_svdprodu_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVFULL, .cf, .cf):
            return Int(vsip_csvdprodu_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVFULL, .d, .d):
            return Int(vsip_svdprodu_d(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVFULL, .cd, .cd):
            return Int(vsip_csvdprodu_d(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .f, .f):
            return Int(vsip_svdprodu_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .cf, .cf):
            return Int(vsip_csvdprodu_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .d, .d):
            return Int(vsip_svdprodu_d(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .cd, .cd):
            return Int(vsip_csvdprodu_d(vsipSv, op, side, vsipC))
        default:
            if self.attr.saveU == VSIP_SVD_UVNOS {
                preconditionFailure("SVD Created without U Matrix")
            } else {
                preconditionFailure("SVD Not supported for these types")
            }
        }
    }
    public func prodv(op: vsip_mat_op, side: vsip_mat_side, matrix: Matrix) -> Int {
        let vsipSv = self.vsip
        let vsipC = matrix.vsip
        switch (self.attr.saveV, matrix.type, self.type){
        case (VSIP_SVD_UVFULL, .f, .f):
            return Int(vsip_svdprodv_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVFULL, .cf, .cf):
            return Int(vsip_csvdprodv_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVFULL, .d, .d):
            return Int(vsip_svdprodv_d(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVFULL, .cd, .cd):
            return Int(vsip_csvdprodv_d(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .f, .f):
            return Int(vsip_svdprodv_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .cf, .cf):
            return Int(vsip_csvdprodv_f(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .d, .d):
            return Int(vsip_svdprodv_d(vsipSv, op, side, vsipC))
        case (VSIP_SVD_UVPART, .cd, .cd):
            return Int(vsip_csvdprodv_d(vsipSv, op, side, vsipC))
        default:
            if self.attr.saveU == VSIP_SVD_UVNOS {
                preconditionFailure("SVD Created without V Matrix")
            } else {
                preconditionFailure("SVD Not supported for these types")
            }
        }
    }
    public var sizeU: (Int, Int){
        get {
            var retval = (self.attr.m, self.attr.m)
            switch self.attr.saveU {
            case VSIP_SVD_UVFULL:
                return retval
            case VSIP_SVD_UVPART:
                if self.attr.m > self.attr.n {
                    retval.1 = self.attr.n
                }
                return retval
            default:
                return (0,0)
            }
        }
    }
    public var sizeV: (Int, Int){
        get {
            var retval = (self.attr.n, self.attr.n)
            switch self.attr.saveU {
            case VSIP_SVD_UVFULL:
                return retval
            case VSIP_SVD_UVPART:
                if self.attr.n > self.attr.m {
                    retval.1 = self.attr.m
                }
                return retval
            default:
                return (0,0)
            }
        }
    }
    
    public var matU: Matrix? {
        get {
            if !amSet {
                return nil
            }
            if self.attr.saveU == VSIP_SVD_UVNOS {
                return nil
            }
            let (m,n) = self.sizeU
            let mat = Matrix(columnLength: m, rowLength: n, type: self.type, major: VSIP_ROW)
            let success = self.matU(0, highColumn: n-1, matU: mat)
            if success == 0 {
                return mat
            } else {
                return nil
            }
        }
    }
    public var matV: Matrix? {
        get {
            if !amSet {
                return nil
            }
            if self.attr.saveU == VSIP_SVD_UVNOS {
                return nil
            }
            let (m,n) = self.sizeV
            let mat = Matrix(columnLength: m, rowLength: n, type: self.type, major: VSIP_ROW)
            let success = self.matV(0, highColumn: n-1, matV: mat)
            if success == 0 {
                return mat
            } else {
                return nil
            }
        }
    }
    public var vecS: Vector {
        get {
            let vec = self.vecSv!.newCopy
            return vec
        }
    }
}
