//
//  Matrix.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip

public func sizeEqual(_ check: Matrix, against: Matrix) -> Bool{
    return (check.rowLength == against.rowLength && check.columnLength == against.columnLength)
}
public class Matrix : View, Sequence {
    fileprivate var tryVsip: OpaquePointer?
    public var vsip: OpaquePointer {
        get {
            return tryVsip!
        }
    }
    public func makeIterator() -> AnyIterator<Vector> {
        var vindex = 0
        return AnyIterator {
            let nextIndex = vindex
            guard vindex < self.columnLength else {
                return nil
            }
            vindex += 1
            // return DSPDoubleComplex(real: self.rdata[nextIndex], imag: self.idata[nextIndex])
            return self.row(nextIndex)
        }
    }
    // matrix bind
    // matrix create
    // Matrix bind returns vsip object (may be null on malloc failure)
    private func mBind(_ offset : Int,
                       columnStride : Int, columnLength : Int,
                       rowStride : Int, rowLength : Int) -> OpaquePointer? {
        let blk = self.block.vsip
        let t = self.block.type
        switch t{
        case .f:
            return vsip_mbind_f(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                vsip_stride(rowStride), vsip_length(rowLength))
        case .d:
            return vsip_mbind_d(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                vsip_stride(rowStride), vsip_length(rowLength))
        case .cf:
            return vsip_cmbind_f(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                 vsip_stride(rowStride), vsip_length(rowLength))
        case .cd:
            return vsip_cmbind_d(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                 vsip_stride(rowStride), vsip_length(rowLength))
        case .i:
            return vsip_mbind_i(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                vsip_stride(rowStride), vsip_length(rowLength))
        case .li:
            return vsip_mbind_li(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                 vsip_stride(rowStride), vsip_length(rowLength))
        case .si:
            return vsip_mbind_si(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                 vsip_stride(rowStride), vsip_length(rowLength))
        case .uc:
            return vsip_mbind_uc(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                 vsip_stride(rowStride), vsip_length(rowLength))
        case .bl:
            return vsip_mbind_bl(blk, vsip_offset(offset), vsip_stride(columnStride), vsip_length(columnLength),
                                 vsip_stride(rowStride), vsip_length(rowLength))
        default:
            print("Not supported.")
            return nil
        }
    }
    public init(block: Block, offset: Int, columnStride: Int, columnLength: Int, rowStride: Int, rowLength: Int){
        super.init(block: block, shape: .m)
        if let m = self.mBind(offset, columnStride: columnStride, columnLength: columnLength, rowStride: rowStride, rowLength: rowLength){
            self.tryVsip = m
        } else {
            preconditionFailure("Failed to bind to a vsip matrix")
        }
    }
    public convenience init(columnLength :Int, rowLength: Int, type : Scalar.Types, major : vsip_major){
        let N = rowLength * columnLength
        let blk = Block(length: N, type: type)
        if major == VSIP_COL {
            self.init(block: blk, offset: 0, columnStride: 1, columnLength: columnLength, rowStride: Int(columnLength), rowLength: rowLength)
        } else {
            self.init(block: blk, offset: 0, columnStride: Int(rowLength), columnLength: columnLength, rowStride: 1, rowLength: rowLength)
        }
    }
    // create view to hold derived subview
    public init(block: Block, cView: OpaquePointer){
        super.init(block: block, shape: .m)
        self.tryVsip = cView
    }
    deinit{
        let t = self.block.type
        let id = self.myId.int32Value
        switch t {
        case .f:
            vsip_mdestroy_f(self.vsip)
            if _isDebugAssertConfiguration(){
                print("deinit mdestroy_f \(id)")
            }
        case .d:
            vsip_mdestroy_d(self.vsip)
            if _isDebugAssertConfiguration(){
                print("deinit mdestroy_d \(id)")
            }
        case .cf:
            vsip_cmdestroy_f(self.vsip)
            if _isDebugAssertConfiguration(){
                print("deinit cmdestroy_f \(id)")
            }
        case .cd:
            vsip_cmdestroy_d(self.vsip)
            if _isDebugAssertConfiguration(){
                print("cmdestroy_d id \(id)")
            }
        case .i:
            vsip_mdestroy_i(self.vsip)
            if _isDebugAssertConfiguration(){
                print("mdestroy_i id \(id)")
            }
        case .li:
            vsip_mdestroy_li(self.vsip)
            if _isDebugAssertConfiguration(){
                print("mdestroy_li id \(id)")
            }
        case .si:
            vsip_mdestroy_si(self.vsip)
            if _isDebugAssertConfiguration(){
                print("mdestroy_si id \(id)")
            }
        case .uc:
            vsip_mdestroy_uc(self.vsip)
            if _isDebugAssertConfiguration(){
                print("mdestroy_uc id \(id)")
            }
        case .bl:
            vsip_mdestroy_bl(self.vsip)
            if _isDebugAssertConfiguration(){
                print("mdestroy_bl id \(id)")
            }
        default:
            break
        }
    }
    // MARK: Attributes
    public var offset: Int {
        get{
            switch self.type {
            case .f :
                return Int(vsip_mgetoffset_f(self.vsip))
            case .d :
                return Int(vsip_mgetoffset_d(self.vsip))
            case .cf :
                return Int(vsip_cmgetoffset_f(self.vsip))
            case .cd :
                return Int(vsip_cmgetoffset_d(self.vsip))
            case .si :
                return Int(vsip_mgetoffset_si(self.vsip))
            case .i :
                return Int(vsip_mgetoffset_i(self.vsip))
            case .li :
                return Int(vsip_mgetoffset_li(self.vsip))
            case .uc :
                return Int(vsip_mgetoffset_uc(self.vsip))
            case .bl :
                return Int(vsip_mgetoffset_bl(self.vsip))
            default:
                return 0
            }
        }
        set(offset) {
            switch self.type {
            case .f :
                vsip_mputoffset_f(self.vsip, vsip_offset(offset))
            case .d :
                vsip_mputoffset_d(self.vsip, vsip_offset(offset))
            case .cf :
                vsip_cmputoffset_f(self.vsip, vsip_offset(offset))
            case .cd :
                vsip_cmputoffset_d(self.vsip, vsip_offset(offset))
            case .si :
                vsip_mputoffset_si(self.vsip, vsip_offset(offset))
            case .i :
                vsip_mputoffset_i(self.vsip, vsip_offset(offset))
            case .li :
                vsip_mputoffset_li(self.vsip, vsip_offset(offset))
            case .uc :
                vsip_mputoffset_uc(self.vsip, vsip_offset(offset))
            case .bl :
                vsip_mputoffset_bl(self.vsip, vsip_offset(offset))
            default:
                break
            }
        }
    }
    public var rowStride: Int{
        get{
            switch self.type {
            case .f :
                return Int(vsip_mgetrowstride_f(self.vsip))
            case .d :
                return Int(vsip_mgetrowstride_d(self.vsip))
            case .cf :
                return Int(vsip_cmgetrowstride_f(self.vsip))
            case .cd :
                return Int(vsip_cmgetrowstride_d(self.vsip))
            case .i :
                return Int(vsip_mgetrowstride_i(self.vsip))
            case .si :
                return Int(vsip_mgetrowstride_si(self.vsip))
            case .li :
                return Int(vsip_mgetrowstride_li(self.vsip))
            default :
                return 0
            }
        }
        set(stride){
            switch self.type{
            case .f :
                vsip_mputrowstride_f(self.vsip,vsip_stride(stride))
            case .d :
                vsip_mputrowstride_d(self.vsip,vsip_stride(stride))
            case .cf :
                vsip_cmputrowstride_f(self.vsip,vsip_stride(stride))
            case .cd :
                vsip_cmputrowstride_d(self.vsip,vsip_stride(stride))
            case .i :
                vsip_mputrowstride_i(self.vsip,vsip_stride(stride))
            case .si :
                vsip_mputrowstride_si(self.vsip,vsip_stride(stride))
            case .li :
                vsip_mputrowstride_li(self.vsip,vsip_stride(stride))
            default :
                break
            }
        }
    }
    public var columnStride: Int{
        get{
            switch self.type {
            case .f :
                return Int(vsip_mgetcolstride_f(self.vsip))
            case .d :
                return Int(vsip_mgetcolstride_d(self.vsip))
            case .cf :
                return Int(vsip_cmgetcolstride_f(self.vsip))
            case .cd :
                return Int(vsip_cmgetcolstride_d(self.vsip))
            case .i :
                return Int(vsip_mgetcolstride_i(self.vsip))
            case .si :
                return Int(vsip_mgetcolstride_si(self.vsip))
            case .li :
                return Int(vsip_mgetcolstride_li(self.vsip))
            default :
                return 0
            }
        }
        set(stride){
            switch self.type{
            case .f :
                vsip_mputcolstride_f(self.vsip,vsip_stride(stride))
            case .d :
                vsip_mputcolstride_d(self.vsip,vsip_stride(stride))
            case .cf :
                vsip_cmputcolstride_f(self.vsip,vsip_stride(stride))
            case .cd :
                vsip_cmputcolstride_d(self.vsip,vsip_stride(stride))
            case .i :
                vsip_mputcolstride_i(self.vsip,vsip_stride(stride))
            case .si :
                vsip_mputcolstride_si(self.vsip,vsip_stride(stride))
            case .li :
                vsip_mputcolstride_li(self.vsip,vsip_stride(stride))
            default :
                break
            }
        }
    }
    public var rowLength: Int {
        get{
            switch self.type {
            case .f :
                return Int(vsip_mgetrowlength_f(self.vsip))
            case .d :
                return Int(vsip_mgetrowlength_d(self.vsip))
            case .cf :
                return Int(vsip_cmgetrowlength_f(self.vsip))
            case .cd :
                return Int(vsip_cmgetrowlength_d(self.vsip))
            case .i :
                return Int(vsip_mgetrowlength_i(self.vsip))
            case .si :
                return Int(vsip_mgetrowlength_si(self.vsip))
            case .li :
                return Int(vsip_mgetrowlength_li(self.vsip))
            default :
                return 0
            }
        }
        set(length){
            switch self.type{
            case .f :
                vsip_mputrowlength_f(self.vsip,vsip_length(length))
            case .d :
                vsip_mputrowlength_d(self.vsip,vsip_length(length))
            case .cf :
                vsip_cmputrowlength_f(self.vsip,vsip_length(length))
            case .cd :
                vsip_cmputrowlength_d(self.vsip,vsip_length(length))
            case .i :
                vsip_mputrowlength_i(self.vsip,vsip_length(length))
            case .si :
                vsip_mputrowlength_si(self.vsip,vsip_length(length))
            case .li :
                vsip_mputrowlength_li(self.vsip,vsip_length(length))
            default :
                break
            }
        }
    }
    public var columnLength: Int{
        get{
            switch self.type {
            case .f :
                return Int(vsip_mgetcollength_f(self.vsip))
            case .d :
                return Int(vsip_mgetcollength_d(self.vsip))
            case .cf :
                return Int(vsip_cmgetcollength_f(self.vsip))
            case .cd :
                return Int(vsip_cmgetcollength_d(self.vsip))
            case .i :
                return Int(vsip_mgetcollength_i(self.vsip))
            case .si :
                return Int(vsip_mgetcollength_si(self.vsip))
            case .li :
                return Int(vsip_mgetcollength_li(self.vsip))
            default :
                return 0
            }
        }
        set(length){
            switch self.type{
            case .f :
                vsip_mputcollength_f(self.vsip,vsip_length(length))
            case .d :
                vsip_mputcollength_d(self.vsip,vsip_length(length))
            case .cf :
                vsip_cmputcollength_f(self.vsip,vsip_length(length))
            case .cd :
                vsip_cmputcollength_d(self.vsip,vsip_length(length))
            case .i :
                vsip_mputcollength_i(self.vsip,vsip_length(length))
            case .si :
                vsip_mputcollength_si(self.vsip,vsip_length(length))
            case .li :
                vsip_mputcollength_li(self.vsip,vsip_length(length))
            default :
                break
            }
        }
    }
    public var real: Matrix {
        get{
            let ans = super.real(self.vsip) // C VSIP real view
            let blk = ans.0
            let v = ans.1
            return Matrix(block: blk, cView: v)
            
        }
    }
    public var imag: Matrix{
        get{
            let ans = super.imag(self.vsip) // C VSIP imag view
            let blk = ans.0!
            let v = ans.1!
            return Matrix(block: blk, cView: v)
        }
    }
    subscript(rowIndex: Int, columnIndex: Int) -> Scalar {
        get{
            return super.get(self.vsip, rowIndex: vsip_index(rowIndex), columnIndex: vsip_index(columnIndex))
        }
        set(value){
            super.put(self.vsip, rowIndex: vsip_index(rowIndex), columnIndex: vsip_index(columnIndex), value: value)
        }
    }
    subscript() -> Scalar {
        get{
            return self[0,0]
        }
        set(value){
            self.fill(value)
        }
    }
    
    
    // MARK: Matrix Data Generators
    public func fill(_ value: Scalar){
        switch self.type{
        case .d:
            vsip_mfill_d(value.vsip_d, self.vsip)
        case .f:
            vsip_mfill_f(value.vsip_f,self.vsip)
        case .cd:
            vsip_cmfill_d(value.vsip_cd,self.vsip)
        case .cf:
            vsip_cmfill_f(value.vsip_cf,self.vsip)
        case .i:
            vsip_mfill_i(value.vsip_i,self.vsip)
        case .li:
            vsip_mfill_li(value.vsip_li,self.vsip)
        case .si:
            vsip_mfill_si(value.vsip_si,self.vsip)
        case .uc:
            vsip_mfill_uc(value.vsip_uc,self.vsip)
        default:
            break
        }
    }
    
    public func randn(_ seed: vsip_index, portable: Bool) -> Matrix{
        let state = Rand(seed: seed, portable: portable)
        state.randn(self)
        return self
    }
    public func randu(_ seed: vsip_index, portable: Bool) -> Matrix{
        let state = Rand(seed: seed, portable: portable)
        state.randu(self)
        return self
    }
    
    // MARK: Views, Sub-Views, Copies, Clones and convenience creaters.
    // create empty Matrix of same type and view size. New data space created, created as row major
    public var empty: Matrix{
        return Matrix(columnLength: self.columnLength, rowLength: self.rowLength, type: self.type, major: VSIP_ROW)
    }
    public func empty(_ type: Scalar.Types) -> Matrix{
        return Matrix(columnLength: self.columnLength, rowLength: self.rowLength, type: type, major: VSIP_ROW)
    }
    // copy is new data space, view of same size, copy of data
    public var newCopy: Matrix {
        let view = self.empty
        switch view.type{
        case .f:
            vsip_mcopy_f_f(self.vsip,view.vsip)
        case .d:
            vsip_mcopy_d_d(self.vsip, view.vsip)
        case .cf:
            vsip_cmcopy_f_f(self.vsip,view.vsip)
        case .cd:
            vsip_cmcopy_d_d(self.vsip, view.vsip)
        case .i:
            vsip_mcopy_i_i(self.vsip,view.vsip)
        default:
            break
        }
        return view
    }
    
    public func copy(_ resultsIn: Matrix) -> Matrix{
        let t = (self.type, resultsIn.type)
        switch t{
        case (.f,.f):
            vsip_mcopy_f_f(self.vsip,resultsIn.vsip)
        case (.f,.cf):
            let r = resultsIn.real;let i = resultsIn.real
            vsip_mcopy_f_f(self.vsip,r.vsip)
            vsip_mfill_f(0.0,i.vsip)
        case (.d,.d):
            vsip_mcopy_d_d(self.vsip,resultsIn.vsip)
        case (.d,.cd):
            let r = resultsIn.real;let i = resultsIn.real
            vsip_mcopy_d_d(self.vsip,r.vsip)
            vsip_mfill_d(0.0,i.vsip)
        case (.d,.f):
            vsip_mcopy_d_f(self.vsip,resultsIn.vsip)
        case (.f,.d):
            vsip_mcopy_f_d(self.vsip,resultsIn.vsip)
        case (.i,.f):
            vsip_mcopy_i_f(self.vsip,resultsIn.vsip)
        case (.i,.i):
            vsip_mcopy_i_i(self.vsip, resultsIn.vsip)
        case (.si,.f):
            vsip_mcopy_si_f(self.vsip, resultsIn.vsip)
        default:
            break
        }
        return resultsIn
    }
    // clone is same data space just new view
    public var clone: Matrix {
        return Matrix(block: self.block, offset: self.offset, columnStride: self.columnStride, columnLength: self.columnLength, rowStride: self.rowStride, rowLength: self.rowLength)
    }
    // transview is new view of same data space as a transpose.
    public var transview: Matrix {
        return Matrix(block: self.block, offset: self.offset, columnStride: self.rowStride, columnLength: self.rowLength, rowStride: self.columnStride, rowLength: self.columnLength)
    }
    public func diagview(diagIndex: Int) -> Vector {
        let blk = self.block
        switch self.type {
        case .f:
            if let v = vsip_mdiagview_f(self.vsip, vsip_stride(diagIndex)) {
                return Vector(block: blk, cView: v)
            } else {
                break
            }
            
        case .d:
            if let v = vsip_mdiagview_d(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .cf:
            if let v = vsip_cmdiagview_f(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .cd:
            if let v = vsip_cmdiagview_d(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .i:
            if let v = vsip_mdiagview_i(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .li:
            if let v = vsip_mdiagview_li(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .si:
            if let v = vsip_mdiagview_si(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .uc:
            if let v = vsip_mdiagview_uc(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .bl:
            if let v = vsip_mdiagview_bl(self.vsip, vsip_stride(diagIndex)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        default:
            print("diagview not available for this view")
        }
        preconditionFailure("Failed to return valid vsip diagview")
    }
    public var diagview: Vector {
        return self.diagview(diagIndex: 0)
    }
    public func row(_ row: Int) -> Vector {
        let blk = self.block
        switch self.type {
        case .f:
            if let v = vsip_mrowview_f(self.vsip, vsip_index(row)) {
                return Vector(block: blk, cView: v)
            } else {
                break
            }
            
        case .d:
            if let v = vsip_mrowview_d(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .cf:
            if let v = vsip_cmrowview_f(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .cd:
            if let v = vsip_cmrowview_d(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .i:
            if let v = vsip_mrowview_i(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .li:
            if let v = vsip_mrowview_li(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .si:
            if let v = vsip_mrowview_si(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .uc:
            if let v = vsip_mrowview_uc(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .bl:
            if let v = vsip_mrowview_bl(self.vsip, vsip_index(row)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        default:
            print("diagview not available for this view")
        }
        preconditionFailure("Failed to return valid vsip diagview")
    }
    public func col(_ col: Int) -> Vector {
        let blk = self.block
        switch self.type {
        case .f:
            if let v = vsip_mcolview_f(self.vsip, vsip_index(col)) {
                return Vector(block: blk, cView: v)
            } else {
                break
            }
            
        case .d:
            if let v = vsip_mcolview_d(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .cf:
            if let v = vsip_cmcolview_f(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .cd:
            if let v = vsip_cmcolview_d(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .i:
            if let v = vsip_mcolview_i(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .li:
            if let v = vsip_mcolview_li(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .si:
            if let v = vsip_mcolview_si(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .uc:
            if let v = vsip_mcolview_uc(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        case .bl:
            if let v = vsip_mcolview_bl(self.vsip, vsip_index(col)){
                return Vector(block: blk, cView: v)
            } else {
                break
            }
        default:
            print("diagview not available for this view")
        }
        preconditionFailure("Failed to return valid vsip diagview")
    }
    // MARK: Print
    public func mString(_ format: String) -> String {
        let fmt = formatFmt(format)
        var retval = ""
        let m = self.columnLength - 1
        let n = self.rowLength - 1
        for i in 0...m{
            retval += (i == 0) ? "[" : " "
            for j in 0...n{
                retval += scalarString(fmt, value: self[i,j])
                if j < n {
                    retval += ", "
                }
            }
            retval += (i == m) ?  "]\n" : ";\n"
        }
        return retval
    }
    public func mPrint(_ format: String){
        let m = mString(format)
        print(m)
    }
}
