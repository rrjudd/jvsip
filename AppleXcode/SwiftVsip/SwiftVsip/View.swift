//
//  View.swift
//  vsip
//
//  Created by Randall Judd on 4/21/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip
public class View {
    public enum Shape: String {
        case v // vector
        case m // matrix
    }
    let block: Block
    let shape : Shape
    var type: Block.Types{
        return block.type
    }
    let jInit : JVSIP
    var myId = NSNumber(value: 0 as Int32)
    // Used to initialize a derived JVSIP View object
    public init(block: Block, shape: View.Shape){
        self.block = block
        self.shape = shape
        jInit = JVSIP()
        myId = jInit.myId
    }
    func real(_ vsip: OpaquePointer) -> (Block, OpaquePointer){
        let t = (self.type, self.shape)
        switch t{
        case (.cf, .v):
            if let cRealView = vsip_vrealview_f(vsip) {
                let blk = vsip_vgetblock_f(cRealView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cRealView)
            } else {
                break
            }
        case(.cf, .m):
            if let cRealView = vsip_mrealview_f(vsip){
                let blk = vsip_mgetblock_f(cRealView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cRealView)
            } else {
                break
            }
        case (.cd, .v):
            if let cRealView = vsip_vrealview_d(vsip){
                let blk = vsip_vgetblock_d(cRealView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cRealView)
            } else {
                break
            }
        case (.cd, .m):
            if let cRealView = vsip_mrealview_d(vsip){
                let blk = vsip_mgetblock_d(cRealView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cRealView)
            } else {
                break
            }
        default:
            print("Case not found")
            break
        }
        preconditionFailure("Failure of imag method")
    }
    public func imag(_ vsip: OpaquePointer) -> (Block?, OpaquePointer?){
        let t = (self.type, self.shape)
        switch t{
        case (.cf, .v):
            if let cImagView = vsip_vimagview_f(vsip){
                let blk = vsip_vgetblock_f(cImagView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cImagView)
            } else {
                break
            }
        case(.cf, .m):
            if let cImagView = vsip_mimagview_f(vsip){
                let blk = vsip_mgetblock_f(cImagView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cImagView)
            } else {
                break
            }
        case (.cd, .v):
            if let cImagView = vsip_vimagview_d(vsip){
                let blk = vsip_vgetblock_d(cImagView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cImagView)
            } else {
                break
            }
        case (.cd, .m):
            if let cImagView = vsip_mimagview_d(vsip){
                let blk = vsip_mgetblock_d(cImagView)
                return (Block(block: self.block, cVsipDerivedBlock: blk!), cImagView)
            } else {
                break
            }
        default:
            print("Case not found")
            break
        }
        preconditionFailure("Failure of imag method")
    }
    
    // MARK: Attribute get/put options
    public func get(_ vsip:OpaquePointer, index: vsip_index) -> (Block.Types?, NSNumber?, NSNumber?){
        let t = self.type
        switch t{
        case .f:
            return (t, NSNumber(value: vsip_vget_f(vsip, index) as Float), nil)
        case .d:
            return (t,  NSNumber(value: vsip_vget_d(vsip, index) as Double), nil)
        case .cf:
            let ans = vsip_cvget_f(vsip, index)
            return (t, NSNumber(value: ans.r as Float),  NSNumber(value: ans.i as Float))
        case .cd:
            let ans = vsip_cvget_d(vsip,index)
            return (t,  NSNumber(value: ans.r as Double),  NSNumber(value: ans.i as Double))
        case .vi:
            return (t,  NSNumber(value: vsip_vget_vi(vsip,index) as UInt),  nil)
        case .mi:
            let ans = vsip_vget_mi(vsip,index)
            return (t,  NSNumber(value: ans.c as UInt), NSNumber(value: ans.r as UInt))
        case .li:
            return (t, NSNumber(value: vsip_vget_li(vsip,index) as Int), nil)
        case .i:
            return (t, NSNumber(value: vsip_vget_i(vsip,index) as Int32), nil)
        case .si:
            return (t, NSNumber(value: vsip_vget_si(vsip,index) as Int16), nil)
        case .uc:
            return (t, NSNumber(value: vsip_vget_uc(vsip,index) as UInt8), nil)
        default:
            return (nil, nil, nil)
        }
    }
    public func get(_ vsip:OpaquePointer, rowIndex: vsip_index, columnIndex: vsip_index) -> (Block.Types?, NSNumber?, NSNumber?){
        let t = self.type
        switch t{
        case .f:
            return (t, NSNumber(value: vsip_mget_f(vsip, rowIndex, columnIndex) as Float), nil)
        case .d:
            return (t,  NSNumber(value: vsip_mget_d(vsip, rowIndex, columnIndex) as Double), nil)
        case .cf:
            let ans = vsip_cmget_f(vsip, rowIndex, columnIndex)
            return (t, NSNumber(value: ans.r as Float),  NSNumber(value: ans.i as Float))
        case .cd:
            let ans = vsip_cmget_d(vsip,rowIndex, columnIndex)
            return (t,  NSNumber(value: ans.r as Double),  NSNumber(value: ans.i as Double))
        case .li:
            return (t, NSNumber(value: vsip_mget_li(vsip,rowIndex, columnIndex) as Int), nil)
        case .i:
            return (t, NSNumber(value: vsip_mget_i(vsip,rowIndex, columnIndex) as Int32), nil)
        case .si:
            return (t, NSNumber(value: vsip_mget_si(vsip,rowIndex, columnIndex) as Int16), nil)
        case .uc:
            return (t, NSNumber(value: vsip_mget_uc(vsip,rowIndex, columnIndex) as UInt8), nil)
        default:
            return (nil, nil, nil)
        }
    }
    public func put(_ vsip:OpaquePointer, index: vsip_index, value: (Block.Types?, NSNumber?, NSNumber?)){
        let t = self.type
        switch t{
        case .f:
            let vsipValue = value.1!
            vsip_vput_f(vsip, index, vsipValue.floatValue)
        case .d:
            let vsipValue = value.1!
            vsip_vput_d(vsip, index, vsipValue.doubleValue)
        case .cf:
            let arg = vsip_cmplx_f(value.1!.floatValue, value.2!.floatValue)
            vsip_cvput_f(vsip,index,arg)
        case .cd:
            let arg = vsip_cmplx_d(value.1!.doubleValue, value.2!.doubleValue)
            vsip_cvput_d(vsip,index,arg)
        case .vi:
            let vsipValue = value.1!
            vsip_vput_vi(vsip,index,vsipValue.uintValue)
        case .mi:
            let arg = vsip_matindex(value.1!.uintValue, value.2!.uintValue)
            vsip_vput_mi(vsip,index,arg)
        case .li:
            let vsipValue = value.1!
            vsip_vput_li(vsip, index, vsipValue.intValue)
        case .i:
            let vsipValue = value.1!
            vsip_vput_i(vsip,index,vsipValue.int32Value)
        case .si:
            let vsipValue = value.1!
            vsip_vput_si(vsip,index,vsipValue.int16Value)
        case .uc:
            let vsipValue = value.1!
            vsip_vput_uc(vsip,index,vsipValue.uint8Value)
        default:
            break
        }
    }
    public func put(_ vsip:OpaquePointer, rowIndex: vsip_index, columnIndex: vsip_index, value: (Block.Types?, NSNumber?, NSNumber?)){
        let t = self.type
        switch t{
        case .f:
            let vsipValue = value.1!.floatValue
            vsip_mput_f(vsip, rowIndex, columnIndex, vsipValue)
        case .d:
            let vsipValue = value.1!
            vsip_mput_d(vsip, rowIndex, columnIndex, vsipValue.doubleValue)
        case .cf:
            let arg = vsip_cmplx_f(value.1!.floatValue, value.2!.floatValue)
            vsip_cmput_f(vsip, rowIndex, columnIndex,arg)
        case .cd:
            let arg = vsip_cmplx_d(value.1!.doubleValue, value.2!.doubleValue)
            vsip_cmput_d(vsip, rowIndex, columnIndex,arg)
        case .li:
            let vsipValue = value.1!
            vsip_mput_li(vsip, rowIndex, columnIndex, vsipValue.intValue)
        case .i:
            let vsipValue = value.1!
            vsip_mput_i(vsip, rowIndex, columnIndex,vsipValue.int32Value)
        case .si:
            let vsipValue = value.1!
            vsip_mput_si(vsip, rowIndex, columnIndex,vsipValue.int16Value)
        case .uc:
            let vsipValue = value.1!
            vsip_mput_uc(vsip, rowIndex, columnIndex,vsipValue.uint8Value)
        default:
            break
            
        }
    }
    // MARK: Conversion to String and Print
    public func scalarString(_ format : String, value : (Block.Types?, NSNumber?, NSNumber?)) -> String{
        var retval = ""
        switch value.0! {
        case .f:
            let fmt = "%" + format + "f"
            retval = String(format: fmt, value.1!.floatValue)
            break
        case .d:
            let fmt = "%" + format + "f"
            retval = String(format: fmt, value.1!.doubleValue)
            break
        case .cf:
            let fmt1 = "%" + format + "f"
            let fmt2 = "%+" + format + "f"
            let r = String(format: fmt1, value.1!.floatValue)
            let i = String(format: fmt2, value.2!.floatValue)
            retval = r + i + "i"
            break
        case .cd:
            let fmt1 = "%" + format + "f"
            let fmt2 = "%+" + format + "f"
            let r = String(format: fmt1, value.1!.doubleValue)
            let i = String(format: fmt2, value.2!.doubleValue)
            retval = r + i + "i"
            break
        default:
            let fmt = "%" + format + "d"
            retval = String(format: fmt, value.1!.intValue)
            break
        }
        return retval
    }
    public func formatFmt(_ fmt: String) -> String{
        var retval = ""
        func charCheck(_ char: Character) -> Bool {
            let validChars = "0123456789."
            for item in validChars.characters{
                if char == item {
                    return true
                }
            }
            return false
        }
        for char in fmt.characters{
            if charCheck(char){
                retval.append(char)
            }
        }
        return retval
    }
}



