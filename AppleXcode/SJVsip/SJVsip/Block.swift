//
//  Block.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
public class Block {
    fileprivate class Block_f{
        var vsip : OpaquePointer?
        let owner = true
        let jInit : JVSIP
        let precision = "f"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_f(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_f id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class DBlock_f{ // Derived Block
        var vsip : OpaquePointer?
        var parent : Block
        let owner = false
        let precision = "f"
        let depth = "r"
        let jInit : JVSIP
        init(block : Block, cVsipDerivedBlock : OpaquePointer){
            self.parent = block
            self.vsip = cVsipDerivedBlock
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_f (derived) id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_d{
        var vsip : OpaquePointer?
        let owner = true
        let jInit : JVSIP
        let precision = "d"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_d(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_d id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class DBlock_d{
        var vsip : OpaquePointer?
        var parent : Block
        let owner = false
        let precision = "f"
        let depth = "r"
        let jInit : JVSIP
        init(block : Block, cVsipDerivedBlock : OpaquePointer){
            self.parent = block
            self.vsip = cVsipDerivedBlock
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_d (derived) id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_cf{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "f"
        let depth = "c"
        init(length : Int){
            self.vsip = vsip_cblockcreate_f(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_cblockdestroy_f(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cblockdestroy_f id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_cd{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "f"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_cblockcreate_d(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_cblockdestroy_d(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("cblockdestroy_d id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_vi{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "vi"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_vi(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_vi(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_vi id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_si{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "si"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_si(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_si(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_si id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_i{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "i"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_i(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_i(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_i id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_li{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "li"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_li(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_li(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_li id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_bl{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "bool"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_bl(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_bl(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_bl id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_uc{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "uc"
        let depth = "r"
        init(length : Int){
            self.vsip = vsip_blockcreate_uc(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_uc(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_uc id \(jInit.myId.int32Value)")
            }
        }
    }
    fileprivate class Block_mi{
        var vsip : OpaquePointer?
        let jInit : JVSIP
        let precision = "vi"
        let depth = "m"
        init(length : Int){
            self.vsip = vsip_blockcreate_mi(vsip_length(length), VSIP_MEM_NONE)
            jInit = JVSIP()
        }
        deinit{
            vsip_blockdestroy_mi(self.vsip!)
            if _isDebugAssertConfiguration(){
                print("blockdestroy_mi id \(jInit.myId.int32Value)")
            }
        }
    }
    // MARK: Block Attributes
    fileprivate(set) public var type: Scalar.Types
    fileprivate(set) var jVsip : AnyObject?
    fileprivate(set) public var length : Int
    fileprivate var owner = true
    var myId : NSNumber?
    // create normal block
    public init(length : Int, type : Scalar.Types){
        switch type {
        case .f:
            let b = Block_f(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .d:
            let b = Block_d(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .cf:
            let b = Block_cf(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .cd:
            let b = Block_cd(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .i:
            let b = Block_i(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .li:
            let b = Block_li(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .si:
            let b = Block_si(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .uc:
            let b = Block_uc(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .vi:
            let b = Block_vi(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .mi:
            let b = Block_mi(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        case .bl:
            let b = Block_bl(length : length)
            jVsip = b
            self.myId = b.jInit.myId
        }
        self.length = length
        self.type = type
    }
    // create special block for derived blocks
    public init(block : Block, cVsipDerivedBlock : OpaquePointer){
        self.length = block.length
        self.owner = false
        switch block.type{
        case .cf:
            let b = DBlock_f(block: block, cVsipDerivedBlock: cVsipDerivedBlock)
            jVsip = b
            type = Scalar.Types.f
            myId = b.jInit.myId
        case .cd:
            let b = DBlock_d(block: block, cVsipDerivedBlock: cVsipDerivedBlock)
            jVsip = b
            type = Scalar.Types.d
            myId = b.jInit.myId
        default:
            jVsip = nil
            type = block.type
        }
    }
    // Vector bind returns vsip object (may be null on malloc failure)
    var vsip: OpaquePointer?{
        switch self.type {
        case .f:
            let blk = self.jVsip as! Block_f
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .d:
            let blk = self.jVsip as! Block_d
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .cf:
            let blk = self.jVsip as! Block_cf
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .cd:
            let blk = self.jVsip as! Block_cd
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .i:
            let blk = self.jVsip as! Block_i
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .li:
            let blk = self.jVsip as! Block_li
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .si:
            let blk = self.jVsip as! Block_si
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .uc:
            let blk = self.jVsip as! Block_uc
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .vi:
            let blk = self.jVsip as! Block_vi
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .mi:
            let blk = self.jVsip as! Block_mi
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        case .bl:
            let blk = self.jVsip as! Block_bl
            if let vsip = blk.vsip {
                return vsip
            } else {
                preconditionFailure("No vsip object in Block")
            }
        }
    }
}
