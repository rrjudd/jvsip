//
//  View.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
public class View: NSObject {
    public enum Shape: String {
        case v // vector
        case m // matrix
    }
    let block: Block
    let shape : Shape
    public var type: Scalar.Types{
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
        super.init()
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
    public func get(_ vsip:OpaquePointer, index: vsip_index) -> Scalar {
        let t = self.type
        switch t{
        case .f:
            return Scalar(vsip_vget_f(vsip, index))
        case .d:
            return Scalar(vsip_vget_d(vsip, index))
        case .cf:
            return Scalar(vsip_cvget_f(vsip, index))
        case .cd:
            return Scalar(vsip_cvget_d(vsip, index))
        case .vi:
            return Scalar(vsip_vget_vi(vsip, index))
        case .mi:
            return Scalar(vsip_vget_mi(vsip,index))
        case .li:
            return Scalar(vsip_vget_li(vsip, index))
        case .i:
            return Scalar(vsip_vget_i(vsip, index))
        case .si:
            return Scalar(vsip_vget_si(vsip, index))
        case .uc:
            return Scalar(vsip_vget_uc(vsip, index))
        default:
            preconditionFailure("No Scalar Found for this case")
        }
    }
    public func get(_ vsip:OpaquePointer, rowIndex: vsip_index, columnIndex: vsip_index) -> Scalar {
        let t = self.type
        switch t{
        case .f:
            return Scalar(vsip_mget_f(vsip, rowIndex, columnIndex))
        case .d:
            return Scalar(vsip_mget_d(vsip, rowIndex, columnIndex))
        case .cf:
            return Scalar(vsip_cmget_f(vsip, rowIndex, columnIndex))
        case .cd:
            return Scalar(vsip_cmget_d(vsip,rowIndex, columnIndex))
        case .li:
            return Scalar(vsip_mget_li(vsip,rowIndex, columnIndex))
        case .i:
            return Scalar(vsip_mget_i(vsip,rowIndex, columnIndex))
        case .si:
            return Scalar(vsip_mget_si(vsip,rowIndex, columnIndex))
        case .uc:
            return Scalar(vsip_mget_uc(vsip,rowIndex, columnIndex))
        default:
            preconditionFailure("No Scalar Found for this case")
        }
    }
    public func put(_ vsip:OpaquePointer, index: vsip_index, value: Scalar){
        let t = self.type
        switch t{
        case .f:
            vsip_vput_f(vsip, index, value.vsip_f)
        case .d:
            vsip_vput_d(vsip, index, value.vsip_d)
        case .cf:
            vsip_cvput_f(vsip,index,value.vsip_cf)
        case .cd:
            vsip_cvput_d(vsip,index,value.vsip_cd)
        case .vi:
            vsip_vput_vi(vsip,index,value.vsip_vi)
        case .mi:
            vsip_vput_mi(vsip,index,value.vsip_mi)
        case .li:
            vsip_vput_li(vsip, index, value.vsip_li)
        case .i:
            vsip_vput_i(vsip,index,value.vsip_i)
        case .si:
            vsip_vput_si(vsip,index,value.vsip_si)
        case .uc:
            vsip_vput_uc(vsip,index,value.vsip_uc)
        default:
            preconditionFailure("No Scalar Found for this case")
            
        }
    }
    public func put(_ vsip:OpaquePointer, rowIndex: vsip_index, columnIndex: vsip_index, value: Scalar){
        let t = self.type
        switch t{
        case .f:
            vsip_mput_f(vsip, rowIndex, columnIndex, value.vsip_f)
        case .d:
            vsip_mput_d(vsip, rowIndex, columnIndex, value.vsip_d)
        case .cf:
            vsip_cmput_f(vsip, rowIndex, columnIndex,value.vsip_cf)
        case .cd:
            vsip_cmput_d(vsip, rowIndex, columnIndex,value.vsip_cd)
        case .li:
            vsip_mput_li(vsip, rowIndex, columnIndex, value.vsip_li)
        case .i:
            vsip_mput_i(vsip, rowIndex, columnIndex,value.vsip_i)
        case .si:
            vsip_mput_si(vsip, rowIndex, columnIndex,value.vsip_si)
        case .uc:
            vsip_mput_uc(vsip, rowIndex, columnIndex,value.vsip_uc)
        default:
            preconditionFailure("No Scalar Found for this case")
        }
    }
}
