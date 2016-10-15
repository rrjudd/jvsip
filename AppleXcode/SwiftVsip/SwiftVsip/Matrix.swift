//
//  Matrix.swift
//  vsip
//
//  Created by Randall Judd on 4/22/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip

public class Matrix : View {
    var vsip: OpaquePointer?
    // matrix bind
    // matrix create
    // Matrix bind returns vsip object (may be null on malloc failure)
    public func mBind(_ offset : vsip_index,
                      columnStride : vsip_stride, columnLength : vsip_length,
                      rowStride : vsip_stride, rowLength : vsip_length) -> OpaquePointer? {
        let blk = self.sBlock.vsip
        let t = self.sBlock.type
        switch t{
        case .f:
            return vsip_mbind_f(blk, offset, columnStride, columnLength,
                                rowStride, rowLength)
        case .d:
            return vsip_mbind_d(blk, offset, columnStride, columnLength,
                                rowStride, rowLength)
        case .cf:
            return vsip_cmbind_f(blk, offset, columnStride, columnLength,
                                 rowStride, rowLength)
        case .cd:
            return vsip_cmbind_d(blk, offset, columnStride, columnLength,
                                 rowStride, rowLength)
        case .i:
            return vsip_mbind_i(blk, offset, columnStride, columnLength,
                                rowStride, rowLength)
        case .li:
            return vsip_mbind_li(blk, offset, columnStride, columnLength,
                                 rowStride, rowLength)
        case .si:
            return vsip_mbind_si(blk, offset, columnStride, columnLength,
                                 rowStride, rowLength)
        case .uc:
            return vsip_mbind_uc(blk, offset, columnStride, columnLength,
                                 rowStride, rowLength)
        case .bl:
            return vsip_mbind_bl(blk, offset, columnStride, columnLength,
                                 rowStride, rowLength)
        default:
            print("Not supported.")
            return nil
        }
    }
    public init(block: Block, offset: vsip_offset, columnStride: vsip_stride, columnLength: vsip_length, rowStride: vsip_stride, rowLength: vsip_length){
        super.init(block: block, shape: "matrix")
        self.vsip = self.mBind(offset, columnStride: columnStride, columnLength: columnLength, rowStride: rowStride, rowLength: rowLength)}
    public convenience init(columnLength :vsip_length, rowLength: vsip_length, type : String, major : vsip_major){
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
        super.init(block: block, shape: "matrix")
        self.vsip = cView
    }
    deinit{
        let t = self.sBlock.type
        let id = self.myId.int32Value
        switch t {
        case .f:
            vsip_mdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("deinit mdestroy_f \(id)")
            }
        case .d:
            vsip_mdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("deinit mdestroy_d \(id)")
            }
        case .cf:
            vsip_cmdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("deinit cmdestroy_f \(id)")
            }
        case .cd:
            vsip_cmdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cmdestroy_d id \(id)")
            }
        case .i:
            vsip_mdestroy_i(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("mdestroy_i id \(id)")
            }
        case .li:
            vsip_mdestroy_li(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("mdestroy_li id \(id)")
            }
        case .si:
            vsip_mdestroy_si(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("mdestroy_si id \(id)")
            }
        case .uc:
            vsip_mdestroy_uc(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("mdestroy_uc id \(id)")
            }
        case .bl:
            vsip_mdestroy_bl(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("mdestroy_bl id \(id)")
            }
        default:
            break
        }
    }
    // MARK: Attributes
    public var offset: vsip_offset {
        get{
            switch self.type {
            case .f :
                return vsip_mgetoffset_f(self.vsip!)
            case .d :
                return vsip_mgetoffset_d(self.vsip!)
            case .cf :
                return vsip_cmgetoffset_f(self.vsip!)
            case .cd :
                return vsip_cmgetoffset_d(self.vsip!)
            case .si :
                return vsip_mgetoffset_si(self.vsip!)
            case .i :
                return vsip_mgetoffset_i(self.vsip!)
            case .li :
                return vsip_mgetoffset_li(self.vsip!)
            case .uc :
                return vsip_mgetoffset_uc(self.vsip!)
            case .bl :
                return vsip_mgetoffset_bl(self.vsip!)
            default:
                return 0
            }
        }
        set(offset) {
            switch self.type {
            case .f :
                vsip_mputoffset_f(self.vsip!, offset)
            case .d :
                vsip_mputoffset_d(self.vsip!, offset)
            case .cf :
                vsip_cmputoffset_f(self.vsip!, offset)
            case .cd :
                vsip_cmputoffset_d(self.vsip!, offset)
            case .si :
                vsip_mputoffset_si(self.vsip!, offset)
            case .i :
                vsip_mputoffset_i(self.vsip!, offset)
            case .li :
                vsip_mputoffset_li(self.vsip!, offset)
            case .uc :
                vsip_mputoffset_uc(self.vsip!, offset)
            case .bl :
                vsip_mputoffset_bl(self.vsip!, offset)
            default:
                break
            }
        }
    }
    public var rowStride: vsip_stride{
        get{
            switch self.type {
            case .f :
                return vsip_mgetrowstride_f(self.vsip!)
            case .d :
                return vsip_mgetrowstride_d(self.vsip!)
            case .cf :
                return vsip_cmgetrowstride_f(self.vsip!)
            case .cd :
                return vsip_cmgetrowstride_d(self.vsip!)
            case .i :
                return vsip_mgetrowstride_i(self.vsip!)
            case .si :
                return vsip_mgetrowstride_si(self.vsip!)
            case .li :
                return vsip_mgetrowstride_li(self.vsip!)
            default :
                return 0
            }
        }
        set(stride){
            switch self.type{
            case .f :
                vsip_mputrowstride_f(self.vsip!,stride)
            case .d :
                vsip_mputrowstride_d(self.vsip!,stride)
            case .cf :
                vsip_cmputrowstride_f(self.vsip!,stride)
            case .cd :
                vsip_cmputrowstride_d(self.vsip!,stride)
            case .i :
                vsip_mputrowstride_i(self.vsip!,stride)
            case .si :
                vsip_mputrowstride_si(self.vsip!,stride)
            case .li :
                vsip_mputrowstride_li(self.vsip!,stride)
            default :
                break
            }
        }
    }
    public var columnStride: vsip_stride{
        get{
            switch self.type {
            case .f :
                return vsip_mgetcolstride_f(self.vsip!)
            case .d :
                return vsip_mgetcolstride_d(self.vsip!)
            case .cf :
                return vsip_cmgetcolstride_f(self.vsip!)
            case .cd :
                return vsip_cmgetcolstride_d(self.vsip!)
            case .i :
                return vsip_mgetcolstride_i(self.vsip!)
            case .si :
                return vsip_mgetcolstride_si(self.vsip!)
            case .li :
                return vsip_mgetcolstride_li(self.vsip!)
            default :
                return 0
            }
        }
        set(stride){
            switch self.type{
            case .f :
                vsip_mputcolstride_f(self.vsip!,stride)
            case .d :
                vsip_mputcolstride_d(self.vsip!,stride)
            case .cf :
                vsip_cmputcolstride_f(self.vsip!,stride)
            case .cd :
                vsip_cmputcolstride_d(self.vsip!,stride)
            case .i :
                vsip_mputcolstride_i(self.vsip!,stride)
            case .si :
                vsip_mputcolstride_si(self.vsip!,stride)
            case .li :
                vsip_mputcolstride_li(self.vsip!,stride)
            default :
                break
            }
        }
    }
    public var rowLength: vsip_length{
        get{
            switch self.type {
            case .f :
                return vsip_mgetrowlength_f(self.vsip!)
            case .d :
                return vsip_mgetrowlength_d(self.vsip!)
            case .cf :
                return vsip_cmgetrowlength_f(self.vsip!)
            case .cd :
                return vsip_cmgetrowlength_d(self.vsip!)
            case .i :
                return vsip_mgetrowlength_i(self.vsip!)
            case .si :
                return vsip_mgetrowlength_si(self.vsip!)
            case .li :
                return vsip_mgetrowlength_li(self.vsip!)
            default :
                return 0
            }
        }
        set(length){
            switch self.type{
            case .f :
                vsip_mputrowlength_f(self.vsip!,length)
            case .d :
                vsip_mputrowlength_d(self.vsip!,length)
            case .cf :
                vsip_cmputrowlength_f(self.vsip!,length)
            case .cd :
                vsip_cmputrowlength_d(self.vsip!,length)
            case .i :
                vsip_mputrowlength_i(self.vsip!,length)
            case .si :
                vsip_mputrowlength_si(self.vsip!,length)
            case .li :
                vsip_mputrowlength_li(self.vsip!,length)
            default :
                break
            }
        }
    }
    public var columnLength: vsip_length{
        get{
            switch self.type {
            case .f :
                return vsip_mgetcollength_f(self.vsip!)
            case .d :
                return vsip_mgetcollength_d(self.vsip!)
            case .cf :
                return vsip_cmgetcollength_f(self.vsip!)
            case .cd :
                return vsip_cmgetcollength_d(self.vsip!)
            case .i :
                return vsip_mgetcollength_i(self.vsip!)
            case .si :
                return vsip_mgetcollength_si(self.vsip!)
            case .li :
                return vsip_mgetcollength_li(self.vsip!)
            default :
                return 0
            }
        }
        set(length){
            switch self.type{
            case .f :
                vsip_mputcollength_f(self.vsip!,length)
            case .d :
                vsip_mputcollength_d(self.vsip!,length)
            case .cf :
                vsip_cmputcollength_f(self.vsip!,length)
            case .cd :
                vsip_cmputcollength_d(self.vsip!,length)
            case .i :
                vsip_mputcollength_i(self.vsip!,length)
            case .si :
                vsip_mputcollength_si(self.vsip!,length)
            case .li :
                vsip_mputcollength_li(self.vsip!,length)
            default :
                break
            }
        }
    }
    public var real: Matrix {
        get{
            let ans = super.real(self.vsip!) // C VSIP real view
            let blk = ans.0!
            let v = ans.1!
            return Matrix(block: blk, cView: v)
            
        }
    }
    public var imag: Matrix{
        get{
            let ans = super.imag(self.vsip!) // C VSIP imag view
            let blk = ans.0!
            let v = ans.1!
            return Matrix(block: blk, cView: v)
        }
    }
    subscript(rowIndex: vsip_index, columnIndex: vsip_index) -> (Block.Types?, NSNumber?, NSNumber?){
        get{
            return super.get(self.vsip!, rowIndex: rowIndex, columnIndex: columnIndex)
        }
        set(value){
            super.put(self.vsip!, rowIndex: rowIndex, columnIndex: columnIndex, value: value)
        }
    }
    subscript() -> (Block.Types?, NSNumber?, NSNumber?){
        get{
            return self[0,0]
        }
        set(value){
            self.fill(value)
        }
    }
    // MARK: Data Generators
    public func fill(_ value: (Block.Types?, NSNumber?,  NSNumber?)){
        switch self.type{
        case .d:
            vsip_mfill_d(value.1!.doubleValue,self.vsip!)
        case .f:
            vsip_mfill_f(value.1!.floatValue,self.vsip!)
        case .cd:
            vsip_cmfill_d(vsip_cmplx_d(value.1!.doubleValue,value.2!.doubleValue),self.vsip!)
        case .cf:
            vsip_cmfill_f(vsip_cmplx_f(value.1!.floatValue,value.2!.floatValue),self.vsip!)
        case .i:
            vsip_mfill_i(value.1!.int32Value,self.vsip!)
        case .li:
            vsip_mfill_li(value.1!.intValue,self.vsip!)
        case .si:
            vsip_mfill_si(value.1!.int16Value,self.vsip!)
        case .uc:
            vsip_mfill_uc(value.1!.uint8Value,self.vsip!)
        default:
            break
        }
    }
    public func fill(_ value: NSNumber){
        switch self.type{
        case .d:
            vsip_mfill_d(value.doubleValue,self.vsip!)
        case .f:
            vsip_mfill_f(value.floatValue,self.vsip!)
        case .cd:
            vsip_cmfill_d(vsip_cmplx_d(value.doubleValue,0.0),self.vsip!)
        case .cf:
            vsip_cmfill_f(vsip_cmplx_f(value.floatValue,0.0),self.vsip!)
        case .i:
            vsip_mfill_i(value.int32Value,self.vsip!)
        case .li:
            vsip_mfill_li(value.intValue,self.vsip!)
        case .si:
            vsip_mfill_si(value.int16Value,self.vsip!)
        case .uc:
            vsip_mfill_uc(value.uint8Value,self.vsip!)
        default:
            break
        }
    }
    public func fill(_ value: vsip_cscalar_d){
        self.fill((Block.Types.cd, NSNumber(value: value.r), NSNumber(value: value.i)))
    }
    public func fill(_ value: vsip_cscalar_f){
        self.fill((Block.Types.cd, NSNumber(value: value.r), NSNumber(value: value.i)))
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
    // create empty Matrix of same type and view size. New data space created, created as row major
    public var empty: Matrix?{
        return Matrix(columnLength: self.columnLength, rowLength: self.rowLength, type: self.type.rawValue, major: VSIP_ROW)
    }
    public func empty(_ type: String) -> Matrix{
        return Matrix(columnLength: self.columnLength, rowLength: self.rowLength, type: self.type.rawValue, major: VSIP_ROW)
    }
    public var copy: Matrix? {
        let view = self.empty
        assert(view != nil, "Allocation Error")
        switch view!.type{
        case .f:
            vsip_mcopy_f_f(self.vsip!,view!.vsip!)
        case .d:
            vsip_mcopy_d_d(self.vsip!, view!.vsip!)
        case .cf:
            vsip_cmcopy_f_f(self.vsip!,view!.vsip!)
        case .cd:
            vsip_cmcopy_d_d(self.vsip!, view!.vsip!)
        case .i:
            vsip_mcopy_i_i(self.vsip!,view!.vsip!)
        default:
            break
        }
        return view
    }
    public func copy(_ output: Matrix) -> Matrix{
        let t1 = self.type.rawValue
        let t2 = output.type.rawValue
        let t = t1+t2
        switch t{
        case "ff":
            vsip_mcopy_f_f(self.vsip!,output.vsip!)
        case "fcf":
            let r = output.real;let i = output.real
            vsip_mcopy_f_f(self.vsip!,r.vsip!)
            vsip_mfill_f(0.0,i.vsip!)
        case "dd":
            vsip_mcopy_d_d(self.vsip!,output.vsip!)
        case "dcd":
            let r = output.real;let i = output.real
            vsip_mcopy_d_d(self.vsip!,r.vsip!)
            vsip_mfill_d(0.0,i.vsip!)
        case "df":
            vsip_mcopy_d_f(self.vsip!,output.vsip!)
        case "fd":
            vsip_mcopy_f_d(self.vsip!,output.vsip!)
        case "if":
            vsip_mcopy_i_f(self.vsip!,output.vsip!)
        case "ii":
            vsip_mcopy_i_i(self.vsip!, output.vsip!)
        case "sif":
            vsip_mcopy_si_f(self.vsip!, output.vsip!)
        default:
            break
        }
        return output
    }
    public var clone: Matrix? {
        return Matrix(block: self.sBlock, offset: self.offset, columnStride: self.columnStride, columnLength: self.columnLength, rowStride: self.rowStride, rowLength: self.rowLength)
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
                retval += super.scalarString(fmt, value: self[i,j])
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
