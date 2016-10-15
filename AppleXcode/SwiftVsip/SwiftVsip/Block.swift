//
//  Block.swift
//  vsip
//
//  Created by Randall Judd on 4/21/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip

//MARK: Block Class
 public class Block {
     public enum Types: String{
        case f
        case d
        case cf
        case cd
        case si
        case i
        case li
        case uc
        case vi
        case mi
        case bl
    }
    fileprivate class Block_f{
        var vsip : OpaquePointer?
        let owner = true
        let jInit : JVSIP
        let precision = "f"
        let depth = "r"
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_f(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_d(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_cblockcreate_f(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_cblockcreate_d(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_vi(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_si(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_i(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_li(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_bl(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_uc(length, VSIP_MEM_NONE)
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
        init(length : vsip_length){
            self.vsip = vsip_blockcreate_mi(length, VSIP_MEM_NONE)
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
    fileprivate(set) public var type: Block.Types
    fileprivate(set) var jVsip : AnyObject?
    fileprivate(set) public var length : vsip_length
    fileprivate var owner = true
    var myId : NSNumber?
    let blockTypeSel = ["f":Block.Types.f,"block_f":Block.Types.f,
                        "cf":Block.Types.cf,"cblock_f":Block.Types.cf,
                        "d":Block.Types.d,"block_d":Block.Types.d,
                        "cd":Block.Types.cd,"cblock_d":Block.Types.cd,
                        "i":Block.Types.i,"block_i":Block.Types.i,
                        "li":Block.Types.li,"block_li":Block.Types.li,
                        "si":Block.Types.si,"block_si":Block.Types.si,
                        "uc":Block.Types.uc,"block_uc":Block.Types.uc,
                        "vi":Block.Types.vi,"block_vi":Block.Types.vi,
                        "mi":Block.Types.mi,"block_mi":Block.Types.mi,
                        "bl":Block.Types.bl,"block_bl":Block.Types.bl]
    // create normal block
     public init(length : vsip_length, type : String){
        switch blockTypeSel[type]! {
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
        self.type = blockTypeSel[type]!
    }
    convenience init(length : vsip_length, type : Types){
        self.init(length: length, type: type.rawValue)
    }
    // create special block for derived blocks
     public init(block : Block, cVsipDerivedBlock : OpaquePointer){
        self.length = block.length
        self.owner = false
        switch block.type{
        case .cf:
            let b = DBlock_f(block: block, cVsipDerivedBlock: cVsipDerivedBlock)
            jVsip = b
            type = Block.Types.f
            myId = b.jInit.myId
        case .cd:
            let b = DBlock_d(block: block, cVsipDerivedBlock: cVsipDerivedBlock)
            jVsip = b
            type = Block.Types.d
            myId = b.jInit.myId
        default:
            jVsip = nil
            type = block.type
        }
    }
    // Vector bind returns vsip object (may be null on malloc failure)
    var vsip: OpaquePointer{
        switch self.type {
        case .f:
            let blk = self.jVsip as! Block_f
            return blk.vsip!
        case .d:
            let blk = self.jVsip as! Block_d
            return blk.vsip!
        case .cf:
            let blk = self.jVsip as! Block_cf
            return blk.vsip!
        case .cd:
            let blk = self.jVsip as! Block_cd
            return blk.vsip!
        case .i:
            let blk = self.jVsip as! Block_i
            return blk.vsip!
        case .li:
            let blk = self.jVsip as! Block_li
            return blk.vsip!
        case .si:
            let blk = self.jVsip as! Block_si
            return blk.vsip!
        case .uc:
            let blk = self.jVsip as! Block_uc
            return blk.vsip!
        case .vi:
            let blk = self.jVsip as! Block_vi
            return blk.vsip!
        case .mi:
            let blk = self.jVsip as! Block_mi
            return blk.vsip!
        case .bl:
            let blk = self.jVsip as! Block_bl
            return blk.vsip!
        }
    }
    
    // Return JVSIP Swift View object.  Allows block.bind for shape vector
    public func bind(_ offset : vsip_offset,
              stride : vsip_stride,
              length : vsip_length) -> Vector {
        return Vector(block: self, offset: offset, stride: stride, length: length)
    }
    // Return JVSIP Swift View object.  Allows block.bind for shape matrix
    public func bind(_ offset : vsip_offset,
              columnStride : vsip_stride, columnLength : vsip_length,
              rowStride : vsip_stride, rowLength : vsip_length) -> Matrix {
        return Matrix(block: self, offset: offset,
                      columnStride: columnStride, columnLength: columnLength,
                      rowStride: rowStride, rowLength: rowLength)
    }
    public func vector() -> Vector{
        return self.bind(0, stride: 1, length: self.length)
    }
    
}
