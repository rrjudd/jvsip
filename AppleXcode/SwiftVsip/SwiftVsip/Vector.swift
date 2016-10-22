//
//  Vector.swift
//  vsip
//
//  Created by Randall Judd on 4/22/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip
public class Vector : View {
    var vsip: OpaquePointer?
    // vector bind
    public func vBind(_ offset : Int, stride : Int, length : Int) -> OpaquePointer? {
        let blk = self.sBlock.vsip
        let t = self.sBlock.type
        switch t {
        case .f:
            return vsip_vbind_f(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .d:
            return vsip_vbind_d(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .cf:
            return vsip_cvbind_f(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .cd:
            return vsip_cvbind_d(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .i:
            return vsip_vbind_i(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .li:
            return vsip_vbind_li(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .si:
            return vsip_vbind_si(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .uc:
            return vsip_vbind_uc(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .vi:
            return vsip_vbind_vi(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .mi:
            return vsip_vbind_mi(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        case .bl:
            return vsip_vbind_bl(blk, vsip_offset(offset), vsip_stride(stride), vsip_length(length))
        }
    }
    public init(block: Block, offset: Int, stride: Int, length: Int){
        super.init(block: block, shape: "vector")
        self.vsip = self.vBind(offset, stride: stride, length: length)
    }
    // vector create
    public convenience init(length : Int, type : String){
        let blk = Block(length: length, type: type)
        self.init(block: blk, offset: 0, stride: 1, length: length)
    }
    public convenience init(length : Int, type : Block.Types){
        let blk = Block(length: length, type: type)
        self.init(block: blk, offset: 0, stride: 1, length: length)
    }
    // create view to hold derived subview
    public init(block: Block, cView: OpaquePointer){
        super.init(block: block, shape: "vector")
        self.vsip = cView
    }
    deinit{
        let t = self.sBlock.type
        let id = self.myId.int32Value
        switch t {
        case .f:
            vsip_vdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_f id \(id)")
            }
        case .d:
            vsip_vdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_d id \(id)")
            }
        case .cf:
            vsip_cvdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cvdestroy_f id \(id)")
            }
        case .cd:
            vsip_cvdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cvdestroy_d id \(id)")
            }
        case .i:
            vsip_vdestroy_i(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_i id \(id)")
            }
        case .li:
            vsip_vdestroy_li(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_li id \(id)")
            }
        case .si:
            vsip_vdestroy_si(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_si id \(id)")
            }
        case .uc:
            vsip_vdestroy_uc(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_uc id \(id)")
            }
        case .vi:
            vsip_vdestroy_vi(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_vi id \(id)")
            }
        case .mi:
            vsip_vdestroy_mi(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_mi id \(id)")
            }
        case .bl:
            vsip_vdestroy_bl(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("vdestroy_bl id \(id)")
            }
        }
    }
    // MARK: Attributes
    public var offset: Int {
        get{
            switch self.type {
            case .f :
                return Int(vsip_vgetoffset_f(self.vsip!))
            case .d :
                return Int(vsip_vgetoffset_d(self.vsip!))
            case .cf :
                return Int(vsip_cvgetoffset_f(self.vsip!))
            case .cd :
                return Int(vsip_cvgetoffset_d(self.vsip!))
            case .si :
                return Int(vsip_vgetoffset_si(self.vsip!))
            case .i :
                return Int(vsip_vgetoffset_i(self.vsip!))
            case .li :
                return Int(vsip_vgetoffset_li(self.vsip!))
            case .uc :
                return Int(vsip_vgetoffset_uc(self.vsip!))
            case .vi :
                return Int(vsip_vgetoffset_vi(self.vsip!))
            case .mi :
                return Int(vsip_vgetoffset_mi(self.vsip!))
            case .bl :
                return Int(vsip_vgetoffset_bl(self.vsip!))
            }
        }
        set(offset){
            switch self.type {
            case .f :
                vsip_vputoffset_f(self.vsip!, vsip_offset(offset))
            case .d :
                vsip_vputoffset_d(self.vsip!, vsip_offset(offset))
            case .cf :
                vsip_cvputoffset_f(self.vsip!, vsip_offset(offset))
            case .cd :
                vsip_cvputoffset_d(self.vsip!, vsip_offset(offset))
            case .si :
                vsip_vputoffset_si(self.vsip!, vsip_offset(offset))
            case .i :
                vsip_vputoffset_i(self.vsip!, vsip_offset(offset))
            case .li :
                vsip_vputoffset_li(self.vsip!, vsip_offset(offset))
            case .uc :
                vsip_vputoffset_uc(self.vsip!, vsip_offset(offset))
            case .mi :
                vsip_vputoffset_mi(self.vsip!, vsip_offset(offset))
            case .vi :
                vsip_vputoffset_vi(self.vsip!, vsip_offset(offset))
            case .bl :
                vsip_vputoffset_bl(self.vsip!, vsip_offset(offset))
            }
        }
    }
    public var stride: Int {
        get{
            switch self.type {
            case .f :
                return Int(vsip_vgetstride_f(self.vsip!))
            case .d :
                return Int(vsip_vgetstride_d(self.vsip!))
            case .cf :
                return Int(vsip_cvgetstride_f(self.vsip!))
            case .cd :
                return Int(vsip_cvgetstride_d(self.vsip!))
            case .si :
                return Int(vsip_vgetstride_si(self.vsip!))
            case .i :
                return Int(vsip_vgetstride_i(self.vsip!))
            case .li :
                return Int(vsip_vgetstride_li(self.vsip!))
            case .uc :
                return Int(vsip_vgetstride_uc(self.vsip!))
            case .vi :
                return Int(vsip_vgetstride_vi(self.vsip!))
            case .mi :
                return Int(vsip_vgetstride_mi(self.vsip!))
            case .bl :
                return Int(vsip_vgetstride_bl(self.vsip!))
            }
        }
        set(stride){
            switch self.type {
            case .f :
                vsip_vputstride_f(self.vsip!, vsip_stride(stride))
            case .d :
                vsip_vputstride_d(self.vsip!, vsip_stride(stride))
            case .cf :
                vsip_cvputstride_f(self.vsip!, vsip_stride(stride))
            case .cd :
                vsip_cvputstride_d(self.vsip!, vsip_stride(stride))
            case .si :
                vsip_vputstride_si(self.vsip!, vsip_stride(stride))
            case .i :
                vsip_vputstride_i(self.vsip!, vsip_stride(stride))
            case .li :
                vsip_vputstride_li(self.vsip!, vsip_stride(stride))
            case .uc :
                vsip_vputstride_uc(self.vsip!, vsip_stride(stride))
            case .mi :
                vsip_vputstride_mi(self.vsip!, vsip_stride(stride))
            case .vi :
                vsip_vputstride_vi(self.vsip!, vsip_stride(stride))
            case .bl :
                vsip_vputstride_bl(self.vsip!, vsip_stride(stride))
            }
        }
    }
    public var length: Int {
        get{
            switch self.type {
            case .f :
                return Int(vsip_vgetlength_f(self.vsip!))
            case .d :
                return Int(vsip_vgetlength_d(self.vsip!))
            case .cf :
                return Int(vsip_cvgetlength_f(self.vsip!))
            case .cd :
                return Int(vsip_cvgetlength_d(self.vsip!))
            case .si :
                return Int(vsip_vgetlength_si(self.vsip!))
            case .i :
                return Int(vsip_vgetlength_i(self.vsip!))
            case .li :
                return Int(vsip_vgetlength_li(self.vsip!))
            case .uc :
                return Int(vsip_vgetlength_uc(self.vsip!))
            case .vi :
                return Int(vsip_vgetlength_vi(self.vsip!))
            case .mi :
                return Int(vsip_vgetlength_mi(self.vsip!))
            case .bl :
                return Int(vsip_vgetlength_bl(self.vsip!))
            }
        }
        set(length){
            switch self.type {
            case .f :
                vsip_vputlength_f(self.vsip!, vsip_length(length))
            case .d :
                vsip_vputlength_d(self.vsip!, vsip_length(length))
            case .cf :
                vsip_cvputlength_f(self.vsip!, vsip_length(length))
            case .cd :
                vsip_cvputlength_d(self.vsip!, vsip_length(length))
            case .si :
                vsip_vputlength_si(self.vsip!, vsip_length(length))
            case .i :
                vsip_vputlength_i(self.vsip!, vsip_length(length))
            case .li :
                vsip_vputlength_li(self.vsip!, vsip_length(length))
            case .uc :
                vsip_vputlength_uc(self.vsip!, vsip_length(length))
            case .mi :
                vsip_vputlength_mi(self.vsip!, vsip_length(length))
            case .vi :
                vsip_vputlength_vi(self.vsip!, vsip_length(length))
            case .bl :
                vsip_vputlength_bl(self.vsip!, vsip_length(length))
            }
        }
    }
    // MARK: sub views
    public var real: Vector{
        get{
            let ans = super.real(self.vsip!) // C VSIP real view
            let blk = ans.0!
            let v = ans.1!
            return Vector(block: blk, cView: v)
            
        }
    }
    public var imag: Vector{
        get{
            let ans = super.imag(self.vsip!) // C VSIP imag view
            let blk = ans.0!
            let v = ans.1!
            return Vector(block: blk, cView: v)
            
        }
    }
    // vector subscript operator
    public subscript(index: Int) -> (Block.Types?, NSNumber?, NSNumber?) {
        get{
            return super.get(self.vsip!, index: vsip_index(index))
        }
        set(value){
            super.put(self.vsip!, index: vsip_index(index), value: value)
        }
    }
    public subscript() -> (Block.Types?, NSNumber?, NSNumber?){
        get{
            return self[0]
        }
        set(value){
            self.fill(value)
        }
    }
    // MARK: data generators
    public func ramp(_ start : NSNumber, increment : NSNumber) -> Vector {
        switch self.type {
        case .d:
            vsip_vramp_d(start.doubleValue, increment.doubleValue, self.vsip!)
        case .f:
            vsip_vramp_f(start.floatValue, increment.floatValue, self.vsip!)
        case .i:
            vsip_vramp_i(start.int32Value, increment.int32Value, self.vsip!)
        case .si:
            vsip_vramp_si(start.int16Value, increment.int16Value, self.vsip!)
        case .uc:
            vsip_vramp_uc(start.uint8Value, increment.uint8Value, self.vsip!)
        case .vi:
            vsip_vramp_vi(start.uintValue, increment.uintValue, self.vsip!)
        default:
            print("Type " + self.type.rawValue + " not supported for ramp")
        }
        return self
    }
    public func ramp(_ start : Double, increment : Double) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    public func ramp(_ start : Float, increment : Float) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    
    public func ramp(_ start : Int, increment : Int) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    
    public func ramp(_ start : UInt, increment : UInt) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    public func ramp(_ start : vsip_scalar_si, increment : vsip_scalar_si) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    public func ramp(_ start : UInt8, increment : UInt8) -> Vector {
        let s = NSNumber( value: start)
        let i = NSNumber( value: increment)
        return ramp(s, increment: i)
    }
    public func fill(_ value: (Block.Types?, NSNumber?,  NSNumber?)){
        switch self.type{
        case .d:
            vsip_vfill_d(value.1!.doubleValue,self.vsip!)
        case .f:
            vsip_vfill_f(value.1!.floatValue,self.vsip!)
        case .cd:
            vsip_cvfill_d(vsip_cmplx_d(value.1!.doubleValue,value.2!.doubleValue),self.vsip!)
        case .cf:
            vsip_cvfill_f(vsip_cmplx_f(value.1!.floatValue,value.2!.floatValue),self.vsip!)
        case .vi:
            vsip_vfill_vi(value.1!.uintValue,self.vsip!)
        case .i:
            vsip_vfill_i(value.1!.int32Value,self.vsip!)
        case .li:
            vsip_vfill_li(value.1!.intValue,self.vsip!)
        case .si:
            vsip_vfill_si(value.1!.int16Value,self.vsip!)
        case .uc:
            vsip_vfill_uc(value.1!.uint8Value,self.vsip!)
        default:
            break
        }
    }
    public func fill(_ value: Vsip.Scalar){
        switch self.type{
        case .d:
            vsip_vfill_d(value.vsip_d,self.vsip!)
        case .f:
            vsip_vfill_f(value.vsip_f,self.vsip!)
        case .cd:
            vsip_cvfill_d(value.vsip_cd,self.vsip!)
        case .cf:
            vsip_cvfill_f(value.vsip_cf,self.vsip!)
        case .vi:
            vsip_vfill_vi(value.vsip_vi,self.vsip!)
        case .i:
            vsip_vfill_i(value.vsip_i,self.vsip!)
        case .li:
            vsip_vfill_li(value.vsip_li,self.vsip!)
        case .si:
            vsip_vfill_si(value.vsip_si,self.vsip!)
        case .uc:
            vsip_vfill_uc(value.vsip_uc,self.vsip!)
        default:
            break
        }
    }
    public func fill(_ value: NSNumber){
        switch self.type{
        case .d:
            vsip_vfill_d(value.doubleValue,self.vsip!)
        case .f:
            vsip_vfill_f(value.floatValue,self.vsip!)
        case .cd:
            vsip_cvfill_d(vsip_cmplx_d(value.doubleValue,0.0),self.vsip!)
        case .cf:
            vsip_cvfill_f(vsip_cmplx_f(value.floatValue,0.0),self.vsip!)
        case .vi:
            vsip_vfill_vi(value.uintValue,self.vsip!)
        case .i:
            vsip_vfill_i(value.int32Value,self.vsip!)
        case .li:
            vsip_vfill_li(value.intValue,self.vsip!)
        case .si:
            vsip_vfill_si(value.int16Value,self.vsip!)
        case .uc:
            vsip_vfill_uc(value.uint8Value,self.vsip!)
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
    public func randn(_ seed: vsip_index, portable: Bool) -> Vector {
        let state = Vsip.Rand(seed: seed, portable: portable)
        state.randn(self)
        return self
    }
    public func randn(_ seed: vsip_index) -> Vector {
        return self.randn(seed, portable: true)
    }
    public func randu(_ seed: vsip_index, portable: Bool) -> Vector{
        let state = Vsip.Rand(seed: seed, portable: portable)
        state.randu(self)
        return self
    }
    public func randu(_ seed: vsip_index) -> Vector {
        return self.randu(seed, portable: true)
    }
    // create empty vector of same type and view size. New data space created
    public var empty: Vector?{
        return Vector(length: self.length, type: self.type.rawValue)
    }
    public func empty(_ type: String) -> Vector{
        return Vector(length: self.length, type: type)
    }
    public var copy: Vector? {
        let view = self.empty
        assert(view != nil, "Allocation Error")
        switch view!.type{
        case .f:
            vsip_vcopy_f_f(self.vsip!,view!.vsip!)
        case .d:
            vsip_vcopy_d_d(self.vsip!, view!.vsip!)
        case .cf:
            vsip_cvcopy_f_f(self.vsip!,view!.vsip!)
        case .cd:
            vsip_cvcopy_d_d(self.vsip!, view!.vsip!)
        case .i:
            vsip_vcopy_i_i(self.vsip!,view!.vsip!)
        case .si:
            vsip_vcopy_si_si(self.vsip!, view!.vsip!)
        case .vi:
            vsip_vcopy_vi_vi(self.vsip!,view!.vsip!)
        case .mi:
            vsip_vcopy_mi_mi(self.vsip!, view!.vsip!)
        default:
            break
        }
        return view
    }
    public func copy(_ output: Vector) -> Vector{
        let t1 = self.type.rawValue
        let t2 = output.type.rawValue
        let t = t1+t2
        switch t{
        case "ff":
            vsip_vcopy_f_f(self.vsip!,output.vsip!)
        case "fcf":
            let r = output.real;let i = output.real
            vsip_vcopy_f_f(self.vsip!,r.vsip!)
            vsip_vfill_f(0.0,i.vsip!)
        case "dd":
            vsip_vcopy_d_d(self.vsip!,output.vsip!)
        case "dcd":
            let r = output.real;let i = output.real
            vsip_vcopy_d_d(self.vsip!,r.vsip!)
            vsip_vfill_d(0.0,i.vsip!)
        case "df":
            vsip_vcopy_d_f(self.vsip!,output.vsip!)
        case "fd":
            vsip_vcopy_f_d(self.vsip!,output.vsip!)
        case "if":
            vsip_vcopy_i_f(self.vsip!,output.vsip!)
        case "id":
            vsip_vcopy_i_d(self.vsip!, output.vsip!)
        case "ii":
            vsip_vcopy_i_i(self.vsip!, output.vsip!)
        case "iuc":
            vsip_vcopy_i_uc(self.vsip!, output.vsip!)
        case "ivi":
            vsip_vcopy_i_vi(self.vsip!, output.vsip!)
        case "sisi":
            vsip_vcopy_si_si(self.vsip!, output.vsip!)
        case "sid":
            vsip_vcopy_si_d(self.vsip!, output.vsip!)
        case "sif":
            vsip_vcopy_si_f(self.vsip!, output.vsip!)
        case "vivi":
            vsip_vcopy_vi_vi(self.vsip!, output.vsip!)
        case "vii":
            vsip_vcopy_vi_i(self.vsip!, output.vsip!)
        case "vid":
            vsip_vcopy_vi_d(self.vsip!, output.vsip!)
        case "vif":
            vsip_vcopy_i_f(self.vsip!, output.vsip!)
        default:
            break
        }
        return output
    }
    public var clone: Vector? {
        return Vector(block: self.sBlock, offset: self.offset, stride: self.stride, length: self.length)
    }
    // MARK: Print
    public func mString(_ format: String) -> String {
        let fmt = formatFmt(format)
        var retval = ""
        let n = self.length - 1
        for i in 0...n{
            retval += (i == 0) ? "[" : " "
            retval += super.scalarString(fmt, value: self[i])
            retval += (i == n) ?  "]\n" : ";\n"
        }
        return retval
    }
    public func mPrint(_ format: String){
        let m = mString(format)
        print(m)
    }
    // MARK: Elementary Functions
    public func acos(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vacos_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vacos_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func asin(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vasin_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vasin_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func atan(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vatan_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vatan_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func cos(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vcos_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vcos_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func sin(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vasin_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vasin_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func tan(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vtan_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vtan_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func exp(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vexp_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vexp_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func exp10(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vexp10_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vexp10_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out
    }
    public func log(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vlog_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vlog_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out    }
    public func log10(_ out: Vector) -> Vector {
        switch self.type{
        case .d:
            vsip_vlog10_d(self.vsip!, out.vsip!)
        case .f:
            vsip_vlog10_f(self.vsip!, out.vsip!)
        default:
            return out
        }
        return out    }
    
    // MARK: Binary Functions
    public func add(_ to: Vector, resultIn: Vector) -> Vector{
        switch self.type{
        case .f:
            vsip_vadd_f(self.vsip!, to.vsip!, resultIn.vsip!)
        case .d:
            vsip_vadd_d(self.vsip!, to.vsip!, resultIn.vsip!)
        case .cf:
            vsip_cvadd_f(self.vsip!, to.vsip!, resultIn.vsip!)
        case .cd:
            vsip_cvadd_d(self.vsip!, to.vsip!, resultIn.vsip!)
        case .si:
            vsip_vadd_si(self.vsip!, to.vsip!, resultIn.vsip!)
        case .i:
            vsip_vadd_i(self.vsip!, to.vsip!, resultIn.vsip!)
        case .li:
            vsip_vadd_li(self.vsip!, to.vsip!, resultIn.vsip!)
        case .uc:
            vsip_vadd_uc(self.vsip!, to.vsip!, resultIn.vsip!)
        case .vi:
            vsip_vadd_vi(self.vsip!, to.vsip!, resultIn.vsip!)
        default:
            break
        }
        return resultIn
    }
    public func sub(_ from: Vector, resultIn: Vector) -> Vector{
        switch self.type{
        case .f:
            vsip_vsub_f(self.vsip!, from.vsip!, resultIn.vsip!)
        case .d:
            vsip_vadd_d(self.vsip!, from.vsip!, resultIn.vsip!)
        case .cf:
            vsip_cvsub_f(self.vsip!, from.vsip!, resultIn.vsip!)
        case .cd:
            vsip_cvsub_d(self.vsip!, from.vsip!, resultIn.vsip!)
        case .si:
            vsip_vsub_si(self.vsip!, from.vsip!, resultIn.vsip!)
        case .i:
            vsip_vsub_i(self.vsip!, from.vsip!, resultIn.vsip!)
        case .uc:
            vsip_vsub_uc(self.vsip!, from.vsip!, resultIn.vsip!)
        default:
            break
        }
        return resultIn
    }
}


