//
//  Elementwise.swift
//  SwiftVsip
//
//  Created by Randall Judd on 9/3/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Cocoa
import vsip

public class Vsip {
    fileprivate static func sizeEqual(_ check: Vector, against: Vector) -> Bool{
        return check.length == against.length
    }
    fileprivate static func sizeEqual(_ check: Matrix, against: Matrix) -> Bool{
        return (check.rowLength == against.rowLength && check.columnLength == against.columnLength)
    }
    // MARK: - Scalar
    public struct Scalar {
        var value: (Block.Types?, NSNumber?,  NSNumber?)
        public init(_ type: Block.Types,_ valueOne: NSNumber?,_ valueTwo: NSNumber?){
            value.0 = type
            value.1 = valueOne
            value.2 = valueTwo
        }
        public init(_ value: Double){
            self.value.0 = .d
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public init(_ value: Float){
            self.value.0 = .f
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public init(_ value: Int){
            self.value.0 = .i
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public init(_ value: vsip_cscalar_d){
            self.value.0 = .cd
            self.value.1 = NSNumber(value: value.r)
            self.value.2 = NSNumber(value: value.i)
        }
        public init(_ value: vsip_cscalar_f){
            self.value.0 = .cf
            self.value.1 = NSNumber(value: value.r)
            self.value.2 = NSNumber(value: value.i)
        }
        public init(_ value: vsip_scalar_mi){
            self.value.0 = .mi
            self.value.1 = NSNumber(value: value.r)
            self.value.2 = NSNumber(value: value.c)
        }
        public init(_ value: vsip_scalar_i){
            self.value.0 = .i
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public init(_ value: vsip_scalar_vi){
            self.value.0 = .vi
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public init(_ value: vsip_scalar_si){
            self.value.0 = .si
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public init(_ value: vsip_scalar_uc){
            self.value.0 = .uc
            self.value.1 = NSNumber(value: value)
            self.value.2 = nil
        }
        public var type: Block.Types {
            return value.0!
        }
        public var realf: Float{
            return Float((value.1?.floatValue)!)
        }
        public var reald: Double{
            return Double((value.1?.doubleValue)!)
        }
        public var imagf: Float{
            if let i = value.2 {
                return Float(i)
            } else {
                return Float(0.0)
            }
        }
        public var imagd: Double{
            if let i = value.2 {
                return Double(i)
            } else {
                return Double(0.0)
            }
        }
        public var int: Int{
            return Int((value.1?.intValue)!)
        }
        public var row: Int{
            return Int((value.1?.intValue)!)
        }
        public var col: Int{
            return Int((value.2?.intValue)!)
        }
        public var cmplxf: Scalar{
            var c = vsip_cmplx_f(vsip_scalar_f(0.0),(0.0))
            if let r = value.1 {
                c.r = vsip_scalar_f(r.floatValue)
            }
            if let i = value.2 {
                c.i = vsip_scalar_f(i.floatValue)
            }
            return Scalar(c)
        }
        public var cmplxd: Scalar{
            var c = vsip_cmplx_d(vsip_scalar_d(0.0),vsip_scalar_d(0.0))
            if let r = value.1 {
                c.r = vsip_scalar_d(r.doubleValue)
            }
            if let i = value.2 {
                c.i = vsip_scalar_d(i.doubleValue)
            }
            return Scalar(c)
        }
        public var vsip_f: vsip_scalar_f {
            return vsip_scalar_f((value.1?.floatValue)!)
        }
        public var vsip_d: vsip_scalar_d {
            return vsip_scalar_d((value.1?.doubleValue)!)
        }
        public var vsip_cf: vsip_cscalar_f {
            var c = vsip_cmplx_f(vsip_scalar_f(0.0),vsip_scalar_f(0.0))
            if let r = value.1 {
                c.r = vsip_scalar_f(r.floatValue)
            }
            if let i = value.2 {
                c.i = vsip_scalar_f(i.floatValue)
            }
            return c
        }
        public var vsip_cd: vsip_cscalar_d {
            var c = vsip_cmplx_d(vsip_scalar_d(0.0),vsip_scalar_d(0.0))
            if let r = value.1 {
                c.r = vsip_scalar_d(r.doubleValue)
            }
            if let i = value.2 {
                c.i = vsip_scalar_d(i.doubleValue)
            }
            return c
        }
        public var vsip_i: vsip_scalar_i{
            return vsip_scalar_i((value.1?.int32Value)!)
        }
        public var vsip_li: vsip_scalar_li{
            return vsip_scalar_li((value.1?.intValue)!)
        }
        public var vsip_vi: vsip_scalar_vi{
            return vsip_scalar_vi((value.1?.uintValue)!)
        }
        public var vsip_si: vsip_scalar_si{
            return vsip_scalar_si((value.1?.int16Value)!)
        }
        public var vsip_uc: vsip_scalar_uc{
            return vsip_scalar_uc((value.1?.uint8Value)!)
        }
        public var vsip_mi: vsip_scalar_mi{
            var i = vsip_matindex(vsip_scalar_vi(0), vsip_scalar_vi(0))
            if let row = value.1 {
                i.r = vsip_scalar_vi(row.uintValue)
            }
            if let col = value.2 {
                i.c = vsip_scalar_vi(col.uintValue)
            }
            return i
        }
        
        public static func + (left: Scalar, right: Scalar) -> Scalar {
            switch (left.type, right.type) {
            case (.f, .f):
                return Scalar( left.realf + right.realf)
            case (.d, .d):
                return Scalar( left.reald + right.reald)
            case (.cf, .f):
                return Scalar(vsip_cmplx_f(left.realf + right.realf, left.imagf))
            case (.cd, .d):
                return Scalar(vsip_cmplx_d(left.reald + right.reald, left.imagd))
            case (.f, .cf):
                return Scalar(vsip_cmplx_f(left.realf + right.realf, right.imagf))
            case (.d, .cd):
                return Scalar(vsip_cmplx_d(left.reald + right.reald, right.imagd))
            case(.cf, .cf):
                return Scalar(vsip_cmplx_f(left.realf + right.realf, left.imagf + right.imagf))
            case(.cd, .cd):
                return Scalar(vsip_cmplx_d(left.reald + right.reald, left.imagd + right.imagd))
            default:
                preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for +")
            }
        }
        public static func * (left: Scalar, right: Scalar) -> Scalar {
            switch (left.type, right.type) {
            case (.f, .f):
                return Scalar( left.realf * right.realf)
            case (.d, .d):
                return Scalar( left.reald * right.reald)
            case (.cf, .f):
                return Scalar(vsip_rcmul_f(right.vsip_f, left.vsip_cf))
            case (.cd, .d):
                return Scalar(vsip_rcmul_d(right.vsip_d, left.vsip_cd))
            case (.f, .cf):
                return Scalar(vsip_rcmul_f(left.vsip_f, right.vsip_cf))
            case (.d, .cd):
                return Scalar(vsip_rcmul_d(left.vsip_d, right.vsip_cd))
            case(.cf, .cf):
                return Scalar(vsip_cmul_f(left.vsip_cf, right.vsip_cf))
            case(.cd, .cd):
                return Scalar(vsip_cmul_d(left.vsip_cd, right.vsip_cd))
            default:
                preconditionFailure("Vsip Scalar types (\(left.type), \(right.type)) not supported for *")
            }
        }
        public var sqrt: Scalar {
            switch self.type {
            case .f:
                return Scalar(sqrtf(self.realf))
            case .d:
                let x = Foundation.sqrt(self.reald)
                return Scalar(x)
            case .cf:
                return Scalar(vsip_csqrt_f(self.vsip_cf))
            case .cd:
                return Scalar(vsip_csqrt_d(self.vsip_cd))
            default:
                preconditionFailure("sqrt not supported for type \(self.type)")
            }
        }
    }
    // MARK: - Support Classes
    //
    // An instance of JVSIP class is stored in every VSIP object.
    // The first time it is called it will call vsip_init
    // When the garbage collector has collected the last one vsip_finalize is called
    // The reference count is kept as a class variable
    
    class JVSIP {
        static var vsipInit : UInt = 0
        static var num = NSNumber(value: 0 as Int32)
        var myId: NSNumber
        fileprivate func initInc() {
            JVSIP.vsipInit += 1;
        }
        fileprivate func initDec() {
            JVSIP.vsipInit -= 1;
        }
        fileprivate func vsipInitGTzero() -> Bool{
            if JVSIP.vsipInit > 0{
                return true
            } else {
                return false
            }
        }
        fileprivate func vsipInitEQzero() -> Bool{
            if JVSIP.vsipInit == 0{
                return true
            } else {
                return false
            }
        }
        init() {
            self.myId = JVSIP.num
            if self.vsipInitGTzero(){
                self.initInc()
            } else {
                let jInit = vsip_init(nil)
                if jInit != 0 {
                    print("vsip_init failed; returned \(jInit)")
                }
                if _isDebugAssertConfiguration(){
                    print("called vsip_init")
                }
                self.initInc()
            }
            let n = JVSIP.num.int32Value + 1
            JVSIP.num = NSNumber(value: n as Int32)
            self.myId = JVSIP.num
            if _isDebugAssertConfiguration(){
                print("called jinit id \(self.myId)")
            }
        }
        deinit{
            self.initDec()
            if self.vsipInitEQzero(){
                vsip_finalize(nil)
                if _isDebugAssertConfiguration(){
                    print("called vsip_finalize")
                }
            }
        }
    }
    // MARK: - Block Class
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
        fileprivate(set) public var type: Block.Types
        fileprivate(set) var jVsip : AnyObject?
        fileprivate(set) public var length : Int
        fileprivate var owner = true
        var myId : NSNumber?
        // create normal block
        public init(length : Int, type : Block.Types){
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
        
        // Return JVSIP Swift View object.  Allows block.bind for shape vector
        public func bind(_ offset : Int,
                         stride : Int,
                         length : Int) -> Vector {
            return Vector(block: self, offset: offset, stride: stride, length: length)
        }
        // Return JVSIP Swift View object.  Allows block.bind for shape matrix
        public func bind(_ offset : Int,
                         columnStride : Int, columnLength : Int,
                         rowStride : Int, rowLength : Int) -> Matrix {
            return Matrix(block: self, offset: offset,
                          columnStride: columnStride, columnLength: columnLength,
                          rowStride: rowStride, rowLength: rowLength)
        }
        public func vector() -> Vector{
            return self.bind(0, stride: 1, length: self.length)
        }
        
    }
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
        // MARK: Conversion to String and Print
        public func scalarString(_ format : String, value : Scalar) -> String{
            var retval = ""
            switch value.type{
            case .f:
                let fmt = "%" + format + "f"
                retval = String(format: fmt, value.realf)
            case .d:
                let fmt = "%" + format + "f"
                retval = String(format: fmt, value.reald)
            case .cf:
                let fmt1 = "%" + format + "f"
                let fmt2 = "%+" + format + "f"
                let r = String(format: fmt1, value.realf)
                let i = String(format: fmt2, value.imagf)
                retval = r + i + "i"
            case .cd:
                let fmt1 = "%" + format + "f"
                let fmt2 = "%+" + format + "f"
                let r = String(format: fmt1, value.reald)
                let i = String(format: fmt2, value.imagd)
                retval = r + i + "i"
            case .mi:
                let fmt1 = "(%d,"
                let fmt2 = " %d)"
                let r = String(format: fmt1, value.row)
                let c = String(format: fmt2, value.col)
                retval = r + c
            default:
                let fmt = "%d"
                retval = String(format: fmt, value.int)            }
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
    // MARK: - Vector Class
    public class Vector : View {
        fileprivate var tryVsip: OpaquePointer? = nil
        public var vsip: OpaquePointer {
            get {
                return tryVsip!
            }
        }
        // vector bind
        private func vBind(_ offset : Int, stride : Int, length : Int) -> OpaquePointer? {
            let blk = self.block.vsip
            let t = self.block.type
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
            super.init(block: block, shape: .v)
            if let v = self.vBind(offset, stride: stride, length: length){
                self.tryVsip = v
            } else {
                preconditionFailure("Failed to bind to a vsip vector")
            }
        }
        // vector create
        public convenience init(length : Int, type : Block.Types){
            let blk = Block(length: length, type: type)
            self.init(block: blk, offset: 0, stride: 1, length: length)
        }
        // create view to hold derived subview
        public init(block: Block, cView: OpaquePointer){
            super.init(block: block, shape: .v)
            self.tryVsip = cView
        }
        deinit{
            let t = self.block.type
            let id = self.myId.int32Value
            switch t {
            case .f:
                vsip_vdestroy_f(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_f id \(id)")
                }
            case .d:
                vsip_vdestroy_d(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_d id \(id)")
                }
            case .cf:
                vsip_cvdestroy_f(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("cvdestroy_f id \(id)")
                }
            case .cd:
                vsip_cvdestroy_d(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("cvdestroy_d id \(id)")
                }
            case .i:
                vsip_vdestroy_i(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_i id \(id)")
                }
            case .li:
                vsip_vdestroy_li(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_li id \(id)")
                }
            case .si:
                vsip_vdestroy_si(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_si id \(id)")
                }
            case .uc:
                vsip_vdestroy_uc(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_uc id \(id)")
                }
            case .vi:
                vsip_vdestroy_vi(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_vi id \(id)")
                }
            case .mi:
                vsip_vdestroy_mi(self.vsip)
                if _isDebugAssertConfiguration(){
                    print("vdestroy_mi id \(id)")
                }
            case .bl:
                vsip_vdestroy_bl(self.vsip)
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
                    return Int(vsip_vgetoffset_f(self.vsip))
                case .d :
                    return Int(vsip_vgetoffset_d(self.vsip))
                case .cf :
                    return Int(vsip_cvgetoffset_f(self.vsip))
                case .cd :
                    return Int(vsip_cvgetoffset_d(self.vsip))
                case .si :
                    return Int(vsip_vgetoffset_si(self.vsip))
                case .i :
                    return Int(vsip_vgetoffset_i(self.vsip))
                case .li :
                    return Int(vsip_vgetoffset_li(self.vsip))
                case .uc :
                    return Int(vsip_vgetoffset_uc(self.vsip))
                case .vi :
                    return Int(vsip_vgetoffset_vi(self.vsip))
                case .mi :
                    return Int(vsip_vgetoffset_mi(self.vsip))
                case .bl :
                    return Int(vsip_vgetoffset_bl(self.vsip))
                }
            }
            set(offset){
                switch self.type {
                case .f :
                    vsip_vputoffset_f(self.vsip, vsip_offset(offset))
                case .d :
                    vsip_vputoffset_d(self.vsip, vsip_offset(offset))
                case .cf :
                    vsip_cvputoffset_f(self.vsip, vsip_offset(offset))
                case .cd :
                    vsip_cvputoffset_d(self.vsip, vsip_offset(offset))
                case .si :
                    vsip_vputoffset_si(self.vsip, vsip_offset(offset))
                case .i :
                    vsip_vputoffset_i(self.vsip, vsip_offset(offset))
                case .li :
                    vsip_vputoffset_li(self.vsip, vsip_offset(offset))
                case .uc :
                    vsip_vputoffset_uc(self.vsip, vsip_offset(offset))
                case .mi :
                    vsip_vputoffset_mi(self.vsip, vsip_offset(offset))
                case .vi :
                    vsip_vputoffset_vi(self.vsip, vsip_offset(offset))
                case .bl :
                    vsip_vputoffset_bl(self.vsip, vsip_offset(offset))
                }
            }
        }
        public var stride: Int {
            get{
                switch self.type {
                case .f :
                    return Int(vsip_vgetstride_f(self.vsip))
                case .d :
                    return Int(vsip_vgetstride_d(self.vsip))
                case .cf :
                    return Int(vsip_cvgetstride_f(self.vsip))
                case .cd :
                    return Int(vsip_cvgetstride_d(self.vsip))
                case .si :
                    return Int(vsip_vgetstride_si(self.vsip))
                case .i :
                    return Int(vsip_vgetstride_i(self.vsip))
                case .li :
                    return Int(vsip_vgetstride_li(self.vsip))
                case .uc :
                    return Int(vsip_vgetstride_uc(self.vsip))
                case .vi :
                    return Int(vsip_vgetstride_vi(self.vsip))
                case .mi :
                    return Int(vsip_vgetstride_mi(self.vsip))
                case .bl :
                    return Int(vsip_vgetstride_bl(self.vsip))
                }
            }
            set(stride){
                switch self.type {
                case .f :
                    vsip_vputstride_f(self.vsip, vsip_stride(stride))
                case .d :
                    vsip_vputstride_d(self.vsip, vsip_stride(stride))
                case .cf :
                    vsip_cvputstride_f(self.vsip, vsip_stride(stride))
                case .cd :
                    vsip_cvputstride_d(self.vsip, vsip_stride(stride))
                case .si :
                    vsip_vputstride_si(self.vsip, vsip_stride(stride))
                case .i :
                    vsip_vputstride_i(self.vsip, vsip_stride(stride))
                case .li :
                    vsip_vputstride_li(self.vsip, vsip_stride(stride))
                case .uc :
                    vsip_vputstride_uc(self.vsip, vsip_stride(stride))
                case .mi :
                    vsip_vputstride_mi(self.vsip, vsip_stride(stride))
                case .vi :
                    vsip_vputstride_vi(self.vsip, vsip_stride(stride))
                case .bl :
                    vsip_vputstride_bl(self.vsip, vsip_stride(stride))
                }
            }
        }
        public var length: Int {
            get{
                switch self.type {
                case .f :
                    return Int(vsip_vgetlength_f(self.vsip))
                case .d :
                    return Int(vsip_vgetlength_d(self.vsip))
                case .cf :
                    return Int(vsip_cvgetlength_f(self.vsip))
                case .cd :
                    return Int(vsip_cvgetlength_d(self.vsip))
                case .si :
                    return Int(vsip_vgetlength_si(self.vsip))
                case .i :
                    return Int(vsip_vgetlength_i(self.vsip))
                case .li :
                    return Int(vsip_vgetlength_li(self.vsip))
                case .uc :
                    return Int(vsip_vgetlength_uc(self.vsip))
                case .vi :
                    return Int(vsip_vgetlength_vi(self.vsip))
                case .mi :
                    return Int(vsip_vgetlength_mi(self.vsip))
                case .bl :
                    return Int(vsip_vgetlength_bl(self.vsip))
                }
            }
            set(length){
                switch self.type {
                case .f :
                    vsip_vputlength_f(self.vsip, vsip_length(length))
                case .d :
                    vsip_vputlength_d(self.vsip, vsip_length(length))
                case .cf :
                    vsip_cvputlength_f(self.vsip, vsip_length(length))
                case .cd :
                    vsip_cvputlength_d(self.vsip, vsip_length(length))
                case .si :
                    vsip_vputlength_si(self.vsip, vsip_length(length))
                case .i :
                    vsip_vputlength_i(self.vsip, vsip_length(length))
                case .li :
                    vsip_vputlength_li(self.vsip, vsip_length(length))
                case .uc :
                    vsip_vputlength_uc(self.vsip, vsip_length(length))
                case .mi :
                    vsip_vputlength_mi(self.vsip, vsip_length(length))
                case .vi :
                    vsip_vputlength_vi(self.vsip, vsip_length(length))
                case .bl :
                    vsip_vputlength_bl(self.vsip, vsip_length(length))
                }
            }
        }
        // MARK: sub views
        public var real: Vector{
            get{
                let ans = super.real(self.vsip) // C VSIP real view
                let blk = ans.0
                let v = ans.1
                return Vector(block: blk, cView: v)
                
            }
        }
        public var imag: Vector{
            get{
                let ans = super.imag(self.vsip) // C VSIP imag view
                let blk = ans.0!
                let v = ans.1!
                return Vector(block: blk, cView: v)
                
            }
        }
        // vector subscript operator
        public subscript(index: Int) -> Scalar {
            get{
                return super.get(self.vsip, index: vsip_index(index))
            }
            set(value){
                super.put(self.vsip, index: vsip_index(index), value: value)
            }
        }
        public subscript() -> Scalar{
            get{
                return self[0]
            }
            set(value){
                self.fill(value)
            }
        }
        // create empty vector of same type and view size. New data space created
        public var empty: Vector {
            return Vector(length: self.length, type: self.type)
        }
        public func empty(_ type: Block.Types) -> Vector {
            return Vector(length: self.length, type: type)
        }
        public var copy: Vector {
            let view = self.empty
            switch view.type{
            case .f:
                vsip_vcopy_f_f(self.vsip,view.vsip)
            case .d:
                vsip_vcopy_d_d(self.vsip, view.vsip)
            case .cf:
                vsip_cvcopy_f_f(self.vsip,view.vsip)
            case .cd:
                vsip_cvcopy_d_d(self.vsip, view.vsip)
            case .i:
                vsip_vcopy_i_i(self.vsip,view.vsip)
            case .si:
                vsip_vcopy_si_si(self.vsip, view.vsip)
            case .vi:
                vsip_vcopy_vi_vi(self.vsip,view.vsip)
            case .mi:
                vsip_vcopy_mi_mi(self.vsip, view.vsip)
            default:
                break
            }
            return view
        }
        public func copy(_ output: Vector) -> Vector{
            let t = (self.type, output.type)
            switch t{
            case (.f,.f):
                vsip_vcopy_f_f(self.vsip,output.vsip)
            case (.f,.cf):
                let r = output.real;let i = output.real
                vsip_vcopy_f_f(self.vsip,r.vsip)
                vsip_vfill_f(0.0,i.vsip)
            case (.d,.d):
                vsip_vcopy_d_d(self.vsip,output.vsip)
            case (.d,.cd):
                let r = output.real;let i = output.real
                vsip_vcopy_d_d(self.vsip,r.vsip)
                vsip_vfill_d(0.0,i.vsip)
            case (.d,.f):
                vsip_vcopy_d_f(self.vsip,output.vsip)
            case (.f,.d):
                vsip_vcopy_f_d(self.vsip,output.vsip)
            case (.i,.f):
                vsip_vcopy_i_f(self.vsip,output.vsip)
            case (.i,.d):
                vsip_vcopy_i_d(self.vsip, output.vsip)
            case (.i,.i):
                vsip_vcopy_i_i(self.vsip, output.vsip)
            case (.i,.uc):
                vsip_vcopy_i_uc(self.vsip, output.vsip)
            case (.i,.vi):
                vsip_vcopy_i_vi(self.vsip, output.vsip)
            case (.si, .si):
                vsip_vcopy_si_si(self.vsip, output.vsip)
            case (.si, .d):
                vsip_vcopy_si_d(self.vsip, output.vsip)
            case (.si, .f):
                vsip_vcopy_si_f(self.vsip, output.vsip)
            case (.vi,.vi):
                vsip_vcopy_vi_vi(self.vsip, output.vsip)
            case (.vi, .i):
                vsip_vcopy_vi_i(self.vsip, output.vsip)
            case (.vi,.d):
                vsip_vcopy_vi_d(self.vsip, output.vsip)
            default:
                break
            }
            return output
        }
        public var clone: Vector {
            return Vector(block: self.block, offset: self.offset, stride: self.stride, length: self.length)
        }
        
        // MARK: Vector Data Generators
        public func ramp(_ start : Scalar, increment : Scalar) -> Vector {
            switch self.type {
            case .d:
                vsip_vramp_d(start.vsip_d, increment.vsip_d, self.vsip)
            case .f:
                vsip_vramp_f(start.vsip_f, increment.vsip_f, self.vsip)
            case .i:
                vsip_vramp_i(start.vsip_i, increment.vsip_i, self.vsip)
            case .si:
                vsip_vramp_si(start.vsip_si, increment.vsip_si, self.vsip)
            case .uc:
                vsip_vramp_uc(start.vsip_uc, increment.vsip_uc, self.vsip)
            case .vi:
                vsip_vramp_vi(start.vsip_vi, increment.vsip_vi, self.vsip)
            default:
                print("Type " + self.type.rawValue + " not supported for ramp")
            }
            return self
        }
        public func ramp(_ start : Double, increment : Double) -> Vector {
            let s = Scalar(start)
            let i = Scalar(increment)
            return ramp(s, increment: i)
        }
        public func ramp(_ start : Float, increment : Float) -> Vector {
            let s = Scalar(start)
            let i = Scalar(increment)
            return ramp(s, increment: i)
        }
        
        public func ramp(_ start : Int, increment : Int) -> Vector {
            let s = Scalar(start)
            let i = Scalar(increment)
            return ramp(s, increment: i)
        }
    
        public func fill(_ value: Scalar){
            switch self.type{
            case .d:
                vsip_vfill_d(value.vsip_d, self.vsip)
            case .f:
                vsip_vfill_f(value.vsip_f, self.vsip)
            case .cd:
                vsip_cvfill_d(value.vsip_cd,self.vsip)
            case .cf:
                vsip_cvfill_f(value.vsip_cf,self.vsip)
            case .vi:
                vsip_vfill_vi(value.vsip_vi,self.vsip)
            case .i:
                vsip_vfill_i(value.vsip_i,self.vsip)
            case .li:
                vsip_vfill_li(value.vsip_li,self.vsip)
            case .si:
                vsip_vfill_si(value.vsip_si,self.vsip)
            case .uc:
                vsip_vfill_uc(value.vsip_uc,self.vsip)
            default:
                break
            }
        }
        public func fill(_ value: Double){
            self.fill(Scalar(value))
        }
        public func fill(_ value: Int){
            self.fill(Scalar(value))
        }
        public func fill(_ value: vsip_cscalar_d){
            self.fill(Scalar(value))
        }
        public func fill(_ value: vsip_cscalar_f){
            self.fill(Scalar(value))
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
                vsip_vacos_d(self.vsip, out.vsip)
            case .f:
                vsip_vacos_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func asin(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vasin_d(self.vsip, out.vsip)
            case .f:
                vsip_vasin_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func atan(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vatan_d(self.vsip, out.vsip)
            case .f:
                vsip_vatan_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func cos(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vcos_d(self.vsip, out.vsip)
            case .f:
                vsip_vcos_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func sin(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vasin_d(self.vsip, out.vsip)
            case .f:
                vsip_vasin_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func tan(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vtan_d(self.vsip, out.vsip)
            case .f:
                vsip_vtan_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func exp(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vexp_d(self.vsip, out.vsip)
            case .f:
                vsip_vexp_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func exp10(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vexp10_d(self.vsip, out.vsip)
            case .f:
                vsip_vexp10_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out
        }
        public func log(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vlog_d(self.vsip, out.vsip)
            case .f:
                vsip_vlog_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out    }
        public func log10(_ out: Vector) -> Vector {
            switch self.type{
            case .d:
                vsip_vlog10_d(self.vsip, out.vsip)
            case .f:
                vsip_vlog10_f(self.vsip, out.vsip)
            default:
                return out
            }
            return out    }
        
        // MARK: Binary Functions
        public func add(_ to: Vector, output: Vector) -> Vector{
            switch self.type{
            case .f:
                vsip_vadd_f(self.vsip, to.vsip, output.vsip)
            case .d:
                vsip_vadd_d(self.vsip, to.vsip, output.vsip)
            case .cf:
                vsip_cvadd_f(self.vsip, to.vsip, output.vsip)
            case .cd:
                vsip_cvadd_d(self.vsip, to.vsip, output.vsip)
            case .si:
                vsip_vadd_si(self.vsip, to.vsip, output.vsip)
            case .i:
                vsip_vadd_i(self.vsip, to.vsip, output.vsip)
            case .li:
                vsip_vadd_li(self.vsip, to.vsip, output.vsip)
            case .uc:
                vsip_vadd_uc(self.vsip, to.vsip, output.vsip)
            case .vi:
                vsip_vadd_vi(self.vsip, to.vsip, output.vsip)
            default:
                break
            }
            return output
        }
        public func sub(_ from: Vector, output: Vector) -> Vector{
            switch self.type{
            case .f:
                vsip_vsub_f(self.vsip, from.vsip, output.vsip)
            case .d:
                vsip_vadd_d(self.vsip, from.vsip, output.vsip)
            case .cf:
                vsip_cvsub_f(self.vsip, from.vsip, output.vsip)
            case .cd:
                vsip_cvsub_d(self.vsip, from.vsip, output.vsip)
            case .si:
                vsip_vsub_si(self.vsip, from.vsip, output.vsip)
            case .i:
                vsip_vsub_i(self.vsip, from.vsip, output.vsip)
            case .uc:
                vsip_vsub_uc(self.vsip, from.vsip, output.vsip)
            default:
                break
            }
            return output
        }
    }
    // MARK: - Matrix Class
    public class Matrix : View {
        fileprivate var tryVsip: OpaquePointer?
        public var vsip: OpaquePointer {
            get {
                return tryVsip!
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
        public convenience init(columnLength :Int, rowLength: Int, type : Block.Types, major : vsip_major){
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
        public func fill(_ value: Double){
            self.fill(Scalar(value))
        }
        public func fill(_ value: vsip_cscalar_d){
            self.fill(Scalar(value))
        }
        public func fill(_ value: vsip_cscalar_f){
            self.fill(Scalar(value))
        }
        
        public func randn(_ seed: vsip_index, portable: Bool) -> Matrix{
            let state = Vsip.Rand(seed: seed, portable: portable)
            state.randn(self)
            return self
        }
        public func randu(_ seed: vsip_index, portable: Bool) -> Matrix{
            let state = Vsip.Rand(seed: seed, portable: portable)
            state.randu(self)
            return self
        }
        
        // MARK: Views, Sub-Views, Copies, Clones and convenience creaters.
        // create empty Matrix of same type and view size. New data space created, created as row major
        public var empty: Matrix{
            return Matrix(columnLength: self.columnLength, rowLength: self.rowLength, type: self.type, major: VSIP_ROW)
        }
        public func empty(_ type: Block.Types) -> Matrix{
            return Matrix(columnLength: self.columnLength, rowLength: self.rowLength, type: type, major: VSIP_ROW)
        }
        // copy is new data space, view of same size, copy of data
        public var copy: Matrix {
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
        
        public func copy(_ output: Matrix) -> Matrix{
            let t = (self.type, output.type)
            switch t{
            case (.f,.f):
                vsip_mcopy_f_f(self.vsip,output.vsip)
            case (.f,.cf):
                let r = output.real;let i = output.real
                vsip_mcopy_f_f(self.vsip,r.vsip)
                vsip_mfill_f(0.0,i.vsip)
            case (.d,.d):
                vsip_mcopy_d_d(self.vsip,output.vsip)
            case (.d,.cd):
                let r = output.real;let i = output.real
                vsip_mcopy_d_d(self.vsip,r.vsip)
                vsip_mfill_d(0.0,i.vsip)
            case (.d,.f):
                vsip_mcopy_d_f(self.vsip,output.vsip)
            case (.f,.d):
                vsip_mcopy_f_d(self.vsip,output.vsip)
            case (.i,.f):
                vsip_mcopy_i_f(self.vsip,output.vsip)
            case (.i,.i):
                vsip_mcopy_i_i(self.vsip, output.vsip)
            case (.si,.f):
                vsip_mcopy_si_f(self.vsip, output.vsip)
            default:
                break
            }
            return output
        }
        // clone is same data space just new view
        public var clone: Matrix {
            return Matrix(block: self.block, offset: self.offset, columnStride: self.columnStride, columnLength: self.columnLength, rowStride: self.rowStride, rowLength: self.rowLength)
        }
        // transview is new view of same data space as a transpose.
        public var transview: Matrix {
            return Matrix(block: self.block, offset: self.offset, columnStride: self.rowStride, columnLength: self.rowLength, rowStride: self.columnStride, rowLength: self.columnLength)
        }
        private func diagview(diagIndex: Int) -> Vector {
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
    
    // MARK:  - Elementary Math Functions
    public static func acos(_ input: Vector, output: Vector) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_vacos_f(input.vsip, output.vsip)
        case (.d, .d):
            vsip_vacos_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for this type vector")
        }
    }
    public static func acos(_ input: Matrix, output: Matrix) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_macos_f(input.vsip, output.vsip)
        case (.d, .d):
            vsip_macos_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for this type vector")
        }
    }
    public static func asin(_ input: Vector, output: Vector) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_vasin_f(input.vsip, output.vsip)
        case (.d, .d):
            vsip_vasin_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for this type vector")
        }
    }
    public static func asin(_ input: Matrix, output: Matrix) {
        assert(sizeEqual(input, against: output), "vectors must be the same size")
        switch (input.type, output.type) {
        case (.f, .f):
            vsip_masin_f(input.vsip, output.vsip)
        case (.d, .d):
            vsip_masin_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for this type vector")
        }
    }
    public static func atan(_ input: Vector, output: Vector) {
        assert(sizeEqual(input, against: output), "View sizes must be the same")
        switch input.type {
        case .f:
            vsip_vatan_f(input.vsip, output.vsip)
        case .d:
            vsip_vatan_d(input.vsip, output.vsip)
        default:
            precondition(true, "function not supported for this type vector")
            break
        }
    }
    public static func atan(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_matan_f(input.vsip, output.vsip)
        case .d:
            vsip_matan_d(input.vsip, output.vsip)
        default:
            precondition(true, "function not supported for this type matrix")
            break
        }
    }
    public static func atan2(numerator: Vector, denominator: Vector, output: Vector) {
        let tn = numerator.type
        let td = denominator.type
        let to = output.type
        assert(tn == td && tn == to, "View types must agree")
        assert(sizeEqual(numerator, against: denominator) && sizeEqual(numerator, against: output), "View sizes musta be equal")
        switch tn{
        case .f:
            vsip_vatan2_f(numerator.vsip,denominator.vsip,output.vsip)
        case .d:
            vsip_vatan2_d(numerator.vsip,denominator.vsip,output.vsip)
        default:
            preconditionFailure("function not supported for this type matrix")
            break
        }
        
    }
    public static func atan2(numerator: Matrix, denominator: Matrix, output: Matrix) {
        let tn = numerator.type
        let td = denominator.type
        let to = output.type
        assert(tn == td && tn == to, "input types must be the same")
        assert(sizeEqual(numerator, against: denominator) && sizeEqual(numerator, against: output), "View sizes musta be equal")
        switch tn {
        case .f:
            vsip_matan2_f(numerator.vsip,denominator.vsip,output.vsip)
        case .d:
            vsip_matan2_d(numerator.vsip,denominator.vsip,output.vsip)
        default:
            preconditionFailure("function not supported for this type matrix")
            break
        }
        
    }
    public static func cos(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vcos_f(input.vsip, output.vsip)
        case .d:
            vsip_vcos_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func cos(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mcos_f(input.vsip, output.vsip)
        case .d:
            vsip_mcos_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func cosh(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vcosh_f(input.vsip, output.vsip)
        case .d:
            vsip_vcosh_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func cosh(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mcosh_f(input.vsip, output.vsip)
        case .d:
            vsip_mcosh_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func sin(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vsin_f(input.vsip, output.vsip)
        case .d:
            vsip_vsin_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func sin(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_msin_f(input.vsip, output.vsip)
        case .d:
            vsip_msin_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func sinh(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vsinh_f(input.vsip, output.vsip)
        case .d:
            vsip_vsinh_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func sinh(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_msinh_f(input.vsip, output.vsip)
        case .d:
            vsip_msinh_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func exp(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vexp_f(input.vsip, output.vsip)
        case .d:
            vsip_vexp_d(input.vsip, output.vsip)
        case .cf:
            vsip_cvexp_f(input.vsip, output.vsip)
        case .cd:
            vsip_cvexp_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func exp(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mexp_f(input.vsip, output.vsip)
        case .d:
            vsip_mexp_d(input.vsip, output.vsip)
        case .cf:
            vsip_cmexp_f(input.vsip, output.vsip)
        case .cd:
            vsip_cmexp_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func exp10(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vexp10_f(input.vsip, output.vsip)
        case .d:
            vsip_vexp10_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func exp10(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mexp10_f(input.vsip, output.vsip)
        case .d:
            vsip_mexp10_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func log(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vlog_f(input.vsip, output.vsip)
        case .d:
            vsip_vlog_d(input.vsip, output.vsip)
        case .cf:
            vsip_cvlog_f(input.vsip, output.vsip)
        case .cd:
            vsip_cvlog_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func log(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mlog_f(input.vsip, output.vsip)
        case .d:
            vsip_mlog_d(input.vsip, output.vsip)
        case .cf:
            vsip_cmlog_f(input.vsip, output.vsip)
        case .cd:
            vsip_cmlog_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func log10(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vlog10_f(input.vsip, output.vsip)
        case .d:
            vsip_vlog10_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func log10(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mlog10_f(input.vsip, output.vsip)
        case .d:
            vsip_mlog10_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func sqrt(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vsqrt_f(input.vsip, output.vsip)
        case .d:
            vsip_vsqrt_d(input.vsip, output.vsip)
        case .cf:
            vsip_cvsqrt_f(input.vsip, output.vsip)
        case .cd:
            vsip_cvsqrt_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func sqrt(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_msqrt_f(input.vsip, output.vsip)
        case .d:
            vsip_msqrt_d(input.vsip, output.vsip)
        case .cf:
            vsip_cmsqrt_f(input.vsip, output.vsip)
        case .cd:
            vsip_cmsqrt_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func tan(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vtan_f(input.vsip, output.vsip)
        case .d:
            vsip_vtan_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func tan(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mtan_f(input.vsip, output.vsip)
        case .d:
            vsip_mtan_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func tanh(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_vtanh_f(input.vsip, output.vsip)
        case .d:
            vsip_vtanh_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func tanh(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .f:
            vsip_mtanh_f(input.vsip, output.vsip)
        case .d:
            vsip_mtanh_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    
    // MARK: - Unary Functions
    public static func arg(_ input: Vector, output: Vector) {
        let type = (input.type, output.type)
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch type {
        case (.cf, .f):
            vsip_varg_f(input.vsip, output.vsip)
        case (.cd, .d):
            vsip_varg_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views")
        }
    }
    public static func arg(_ input: Matrix, output: Matrix) {
        let type = (input.type, output.type)
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch type {
        case (.cf, .f):
            vsip_marg_f(input.vsip, output.vsip)
        case (.cd, .d):
            vsip_marg_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views")
        }
    }
    public static func ceil(_ input: Vector, output: Vector){
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch (input.type, output.type) {
        case (.d, .d):
            vsip_vceil_d_d(input.vsip, output.vsip)
        case (.d,.i):
            vsip_vceil_d_i(input.vsip, output.vsip)
        case (.f, .f):
            vsip_vceil_f_f(input.vsip, output.vsip)
        case (.f,.i):
            vsip_vceil_f_i(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views")
            break
        }
    }
    public static func ceil(_ input: Matrix, output: Matrix){
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch (input.type, output.type) {
        case (.d, .d):
            vsip_mceil_d_d(input.vsip, output.vsip)
        case (.d,.i):
            vsip_mceil_d_i(input.vsip, output.vsip)
        case (.f, .f):
            vsip_mceil_f_f(input.vsip, output.vsip)
        case (.f,.i):
            vsip_mceil_f_i(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views")
            break
        }
        
    }
    public static func conj(_ input: Vector, output: Vector) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .cf:
            vsip_cvconj_f(input.vsip, output.vsip)
        case .cd:
            vsip_cvconj_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func conj(_ input: Matrix, output: Matrix) {
        assert(input.type == output.type, "View types must agree")
        assert(sizeEqual(input, against: output), "Views must be the same size")
        switch input.type {
        case .cf:
            vsip_cmconj_f(input.vsip, output.vsip)
        case .cd:
            vsip_cmconj_d(input.vsip, output.vsip)
        default:
            preconditionFailure("function not supported")
            break
        }
    }
    public static func neg(_ input: Vector, output: Vector){
        assert(sizeEqual(input, against: output), "View size of input an output must be equal for neg")
        assert(input.type == output.type, "View types of input and output must be the same for neg")
        switch input.type {
        case .f:
            vsip_vneg_f(input.vsip,output.vsip)
        case .d:
            vsip_vneg_d(input.vsip,output.vsip)
        case .cf:
            vsip_cvneg_f(input.vsip,output.vsip)
        case .cd:
            vsip_cvneg_d(input.vsip,output.vsip)
        case .i:
            vsip_vneg_i(input.vsip,output.vsip)
        case .li:
            vsip_vneg_li(input.vsip,output.vsip)
        case .vi:
            vsip_vneg_si(input.vsip,output.vsip)
        default:
            assert(false, "type not found for neg")
            break
        }
        
    }
    public static func neg(_ input: Matrix, output: Matrix){
        assert(sizeEqual(input, against: output), "View size of input an output must be equal for neg")
        assert(input.type == output.type, "View types of input and output must be the same for neg")
        switch input.type {
        case .f:
            vsip_mneg_f(input.vsip,output.vsip)
        case .d:
            vsip_mneg_d(input.vsip,output.vsip)
        case .cf:
            vsip_cmneg_f(input.vsip,output.vsip)
        case .cd:
            vsip_cmneg_d(input.vsip,output.vsip)
        default:
            assert(false, "type not found for neg")
            break
        }
        
    }
    public static func sumval(_ input: Vector) -> Scalar {
        switch input.type {
        case .d:
            return Scalar(vsip_vsumval_d(input.vsip))
        case .f:
            return Scalar(vsip_vsumval_f(input.vsip))
        case .cd:
            return Scalar(vsip_cvsumval_d(input.vsip))
        case .cf:
            return Scalar(vsip_cvsumval_f(input.vsip))
        case .i:
            return Scalar(vsip_vsumval_i(input.vsip))
        case .bl:
            return Scalar(vsip_vsumval_bl(input.vsip))
        default:
            preconditionFailure("sumval not supported for this type")
        }
    }
    public static func sumval(_ input: Matrix) -> Scalar {
        switch input.type {
        case .d:
            return Scalar(vsip_msumval_d(input.vsip))
        case .f:
            return Scalar(vsip_msumval_f(input.vsip))
        case .cd:
            return Scalar(vsip_cmsumval_d(input.vsip))
        case .cf:
            return Scalar(vsip_cmsumval_f(input.vsip))
        case .bl:
            return Scalar(vsip_msumval_bl(input.vsip))
        default:
            preconditionFailure("sumval not supported for this type")
            
        }
    }
    public static func sumsqval(_ input: Vector) -> Scalar {
        switch input.type {
        case .d:
            return Scalar(Double(vsip_vsumsqval_d(input.vsip)))
        case .f:
            return Scalar(Float(vsip_vsumsqval_f(input.vsip)))
        default:
            preconditionFailure("sumsqval not supported for this type")
            break
        }
    }
    public static func sumsqval(_ input: Matrix) -> Scalar {
        switch input.type {
        case .d:
            return Scalar(Double(vsip_msumsqval_d(input.vsip)))
        case .f:
            return Scalar(Float(vsip_msumsqval_f(input.vsip)))
        default:
            preconditionFailure("sumsqval not supported for this type")
            break
        }
    }
    
    // MARK: - Binary Functions
    public static func add(_ one: Vector, _ to: Vector, output: Vector) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        assert(to.type == output.type, "Output view type not compliant with input")
        switch one.type {
        case .f:
            switch to.type{
            case .f:
                vsip_vadd_f(one.vsip, to.vsip, output.vsip)
            case .cf:
                vsip_rcvadd_f(one.vsip, to.vsip, output.vsip)
            default:
                break
            }
        case .d:
            switch to.type{
            case .d:
                vsip_vadd_d(one.vsip, to.vsip, output.vsip)
            case .cd:
                vsip_rcvadd_d(one.vsip, to.vsip, output.vsip)
            default:
                break
            }
        case .cf:
            vsip_cvadd_f(one.vsip, to.vsip, output.vsip)
        case .cd:
            vsip_cvadd_d(one.vsip, to.vsip, output.vsip)
        case .i:
            vsip_vadd_d(one.vsip, to.vsip, output.vsip)
        case .li:
            vsip_vadd_li(one.vsip, to.vsip, output.vsip)
        case .uc:
            vsip_vadd_li(one.vsip, to.vsip, output.vsip)
        case .si:
            vsip_vadd_si(one.vsip, to.vsip, output.vsip)
        case .vi:
            vsip_vadd_vi(one.vsip, to.vsip, output.vsip)
        default:
            preconditionFailure("View type not supported")
            break
        }
        
    }
    public static func add(_ one: Matrix, _ to: Matrix, output: Matrix) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        assert(to.type == output.type, "Output view type not compliant with input")
        switch one.type {
        case .f:
            switch to.type{
            case .f:
                vsip_madd_f(one.vsip, to.vsip, output.vsip)
            case .cf:
                vsip_rcmadd_f(one.vsip, to.vsip, output.vsip)
            default:
                break
            }
        case .d:
            switch to.type{
            case .d:
                vsip_madd_d(one.vsip, to.vsip, output.vsip)
            case .cd:
                vsip_rcmadd_d(one.vsip, to.vsip, output.vsip)
            default:
                break
            }
        case .cf:
            vsip_cmadd_f(one.vsip, to.vsip, output.vsip)
        case .cd:
            vsip_cmadd_d(one.vsip, to.vsip, output.vsip)
        case .i:
            vsip_madd_d(one.vsip, to.vsip, output.vsip)
        case .li:
            vsip_madd_li(one.vsip, to.vsip, output.vsip)
        case .si:
            vsip_madd_si(one.vsip, to.vsip, output.vsip)
        default:
            preconditionFailure("View type not supported")
            break
        }
    }
    public static func add(_ scalar: Double, _ vector: Vector, output: Vector){
        Vsip.add(Scalar(scalar), vector, output: output)
        
    }
    public static func add(_ scalar: Float, _ vector: Vector, output: Vector){
        Vsip.add(Scalar(scalar), vector, output: output)
        
    }
    public static func add(_ scalar: Int, _ vector: Vector, output: Vector){
        Vsip.add(Scalar(scalar), vector, output: output)
    }
    public static func add(_ scalar: Scalar, _ vector: Vector, output: Vector){
        assert(vector.type == output.type, "View types must agrees")
        let t = (scalar.type, vector.type, output.type)
        switch t {
        case (.f, .f, .f):
            vsip_svadd_f(scalar.vsip_f, vector.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_svadd_d(scalar.vsip_d, vector.vsip, output.vsip)
        case (.f, .cf, .cf):
            vsip_rscvadd_f(scalar.vsip_f, vector.vsip, output.vsip)
        case (.d, .cd, .cd):
            vsip_rscvadd_d(scalar.vsip_d, vector.vsip, output.vsip)
        case  (.cf, .cf, .cf):
            vsip_csvadd_f(scalar.vsip_cf, vector.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_csvadd_d(scalar.vsip_cd, vector.vsip, output.vsip)
        case (.i, .i, .i):
            vsip_svadd_i(scalar.vsip_i, vector.vsip, output.vsip)
        case (.li, .li, .li):
            vsip_svadd_li(scalar.vsip_li, vector.vsip, output.vsip)
        case (.si, .si, .si):
            vsip_svadd_si(scalar.vsip_si, vector.vsip, output.vsip)
        case (.uc, .uc, .uc):
            vsip_svadd_uc(scalar.vsip_uc, vector.vsip, output.vsip)
        case (.vi, .vi, .vi):
            vsip_svadd_vi(scalar.vsip_vi, vector.vsip, output.vsip)
        default:
            preconditionFailure("Argument string not supported for svadd")
        }
    }
    public static func add(_ scalar: Double, _ matrix: Matrix, output: Matrix){
        Vsip.add(Scalar(scalar), matrix, output: output)
    }
    public static func add(_ scalar: Float, _ matrix: Matrix, output: Matrix){
        Vsip.add(Scalar(scalar), matrix, output: output)
        
    }
    public static func add(_ scalar: Scalar, _ matrix: Matrix, output: Matrix){
        assert(sizeEqual(matrix, against: output),"Views must be the same size")
        let t = (scalar.type, matrix.type, output.type)
        switch t {
        case (.f, .f, .f):
            vsip_smadd_f(scalar.vsip_f, matrix.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_smadd_d(scalar.vsip_d, matrix.vsip, output.vsip)
        case (.f, .cf, .cf):
            vsip_rscmadd_f(scalar.vsip_f, matrix.vsip, output.vsip)
        case (.d, .cd, .cd):
            vsip_rscmadd_d(scalar.vsip_d, matrix.vsip, output.vsip)
        case  (.cf, .cf, .cf):
            vsip_csmadd_f(scalar.vsip_cf, matrix.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_csmadd_d(scalar.vsip_cd, matrix.vsip, output.vsip)
        default:
            preconditionFailure("Argument string not supported for scalar matrix add")
            
        }
    }
    
    public static func div(numerator aView: Vector, denominator by: Vector, quotient output: Vector){
        assert(sizeEqual(aView, against: by),"Views must be the same size")
        assert(sizeEqual(aView, against: output),"Views must be the same size")
        let t = (aView.type, by.type, output.type)
        switch t {
        case (.d, .cd, .cd):
            vsip_rcvdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.f, .cf, .cf):
            vsip_rcvdiv_f(aView.vsip, by.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_vdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.f, .f, .f):
            vsip_vdiv_f(aView.vsip, by.vsip, output.vsip)
        case (.cd, .d, .cd):
            vsip_crvdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.cf, .f, .cf):
            vsip_crvdiv_f(aView.vsip, by.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_cvdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.cf, .cf, .cf):
            vsip_cvdiv_f(aView.vsip, by.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views of type (\t)")
        }
        
    }
    public static func div(numerator aView: Matrix, denominator by: Matrix, quotient output: Matrix){
        assert(sizeEqual(aView, against: by),"Views must be the same size")
        assert(sizeEqual(aView, against: output),"Views must be the same size")
        let t = (aView.type, by.type, output.type)
        switch t {
        case (.cd, .cd, .cd):
            vsip_cmdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.cf, .cf, .cf):
            vsip_cmdiv_f(aView.vsip, by.vsip, output.vsip)
        case (.cd, .d, .cd):
            vsip_crmdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.cf, .f, .cf):
            vsip_crmdiv_f(aView.vsip, by.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_mdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.f, .f, .f):
            vsip_mdiv_f(aView.vsip, by.vsip, output.vsip)
        case (.d, .cd, .cd):
            vsip_rcmdiv_d(aView.vsip, by.vsip, output.vsip)
        case (.f, .cf, .cf):
            vsip_rcmdiv_f(aView.vsip, by.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views of type (\t)")
        }
        
    }
    
    public static func mul(_ one: Vector, _ to: Vector, output: Vector) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        switch (one.type, to.type, output.type) {
        case (.f,.f,.f):
            vsip_vmul_f(one.vsip, to.vsip, output.vsip)
        case (.f,.cf, .cf):
            vsip_rcvmul_f(one.vsip, to.vsip, output.vsip)
        case (.d, .d,.d):
            vsip_vmul_d(one.vsip, to.vsip, output.vsip)
        case (.d, .cd, .cd):
            vsip_rcvmul_d(one.vsip, to.vsip, output.vsip)
        case (.cf, .cf, .cf):
            vsip_cvmul_f(one.vsip, to.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_cvmul_d(one.vsip, to.vsip, output.vsip)
        case (.i, .i, .i):
            vsip_vmul_d(one.vsip, to.vsip, output.vsip)
        case (.li, .li, .li):
            vsip_vmul_li(one.vsip, to.vsip, output.vsip)
        case (.uc,.uc,.uc):
            vsip_vmul_uc(one.vsip, to.vsip, output.vsip)
        case (.si,.si,.si):
            vsip_vmul_si(one.vsip, to.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views")
        }
    }
    public static func mul(_ one: Matrix, _ to: Matrix, output: Matrix) {
        assert(sizeEqual(one, against: to),"Views must be the same size")
        switch (one.type, to.type, output.type) {
        case (.f, .f, .f):
            vsip_mmul_f(one.vsip, to.vsip, output.vsip)
        case (.f, .cf, .cf):
            vsip_rcmmul_f(one.vsip, to.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_mmul_d(one.vsip, to.vsip, output.vsip)
        case (.f, .cd, .cd):
            vsip_rcmmul_d(one.vsip, to.vsip, output.vsip)
        case (.cf, .cf, .cf):
            vsip_cmmul_f(one.vsip, to.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_cmmul_d(one.vsip, to.vsip, output.vsip)
        default:
            preconditionFailure("function not supported for input/output views")
        }
    }
    public static func mul(_ scalar: Double, _ vector: Vector, output: Vector){
            Vsip.mul(Scalar(scalar), vector, output: output)
    }
    public static func mul(_ scalar: Float, _ vector: Vector, output: Vector){
        Vsip.mul(Scalar(scalar), vector, output: output)
    }
    public static func mul(_ scalar: Int, _ vector: Vector, output: Vector){
        Vsip.mul(Scalar(scalar), vector, output: output)
    }
    public static func mul(_ scalar: Scalar,_ vector: Vector, output: Vector){
        assert(sizeEqual(vector, against: output), "View sizes must be the same")
        let t = (scalar.type, vector.type, output.type)
        switch t {
        case (.f, .f, .f):
            vsip_svmul_f(scalar.vsip_f, vector.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_svmul_d(scalar.vsip_d, vector.vsip, output.vsip)
        case (.f, .cf, .cf):
            vsip_rscvmul_f(scalar.vsip_f, vector.vsip, output.vsip)
        case (.d, .cd, .cd):
            vsip_rscvmul_d(scalar.vsip_d, vector.vsip, output.vsip)
        case (.cf, .cf, .cf):
            vsip_csvmul_f(scalar.vsip_cf, vector.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_csvmul_d(scalar.vsip_cd, vector.vsip, output.vsip)
        case (.i, .i, .i):
            vsip_svmul_i(scalar.vsip_i, vector.vsip, output.vsip)
        case (.li, .li, .li):
            vsip_svmul_li(scalar.vsip_li, vector.vsip, output.vsip)
        case (.si, .si, .si):
            vsip_svmul_si(scalar.vsip_si, vector.vsip, output.vsip)
        case (.uc, .uc, .uc):
            vsip_svmul_uc(scalar.vsip_uc, vector.vsip, output.vsip)
        default:
            preconditionFailure("Argument string not supported for svmul")
        }
        
    }
    public static func mul(_ scalar: Double, _ matrix: Matrix, output: Matrix){
        Vsip.mul(Scalar(scalar), matrix, output: output)
        
    }
    public static func mul(_ scalar: Float, _ matrix: Matrix, output: Matrix){
        Vsip.mul(Scalar(scalar), matrix, output: output)
        
    }
    public static func mul(_ scalar: Scalar,_ matrix: Matrix, output: Matrix){
        assert(sizeEqual(matrix, against: output),"Views must be the same size")
        let t = (scalar.type, matrix.type, output.type)
        switch t {
        case (.f, .f, .f):
            vsip_smmul_f(scalar.vsip_f, matrix.vsip, output.vsip)
        case (.d, .d, .d):
            vsip_smmul_d(scalar.vsip_d, matrix.vsip, output.vsip)
        case (.f,.cf, .cf):
            vsip_rscmmul_f(scalar.vsip_f, matrix.vsip, output.vsip)
        case (.d, .cd, .cd):
            vsip_rscmmul_d(scalar.vsip_d, matrix.vsip, output.vsip)
        case (.cd, .cd, .cd):
            vsip_csmmul_d(scalar.vsip_cd, matrix.vsip, output.vsip)
        default:
            preconditionFailure("Argument string not supported for mmul")
        }
        
    }
    public static func vmmul(vector: Vector, matrix: Matrix, major: vsip_major, output: Matrix){
        let vsipVec = vector.vsip
        let vsipMat = matrix.vsip
        let vsipOut = output.vsip
        let t = (vector.type, matrix.type, output.type)
        switch t {
        case(.cd, .cd, .cd):
            vsip_cvmmul_d ( vsipVec, vsipMat, major, vsipOut)
        case(.cf, .cf, .cf):
            vsip_cvmmul_f ( vsipVec, vsipMat, major, vsipOut)
        case(.d, .cd, .cd):
            vsip_rvcmmul_d ( vsipVec, vsipMat, major, vsipOut)
        case(.f, .cf, .cf):
            vsip_rvcmmul_f ( vsipVec, vsipMat, major, vsipOut)
        case(.d, .d, .d):
            vsip_vmmul_d ( vsipVec, vsipMat, major, vsipOut)
        case(.f, .f, .f):
            vsip_vmmul_f ( vsipVec, vsipMat, major, vsipOut)
        default:
            preconditionFailure("Argument list not supported for vmmul")
        }
    }
    public static func sub(_ aView: Vector, subtract: Vector, output: Vector){
        assert(sizeEqual(aView, against: subtract),"Views must be the same size")
        assert(sizeEqual(aView, against: output), "Views must be the same size")
        let t = (aView.type, subtract.type, output.type)
        switch t{
        case (.cd, .d, .cd):
            vsip_crvsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.cf, .f, .cf):
            vsip_crvsub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.cd, .cd, .cd):
            vsip_cvsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.cf, .cf, .cf):
            vsip_cvsub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.d, .cd, .cd):
            vsip_rcvsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.f, .cf, .cf):
            vsip_rcvsub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.d, .d, .d):
            vsip_vsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.f, .f, .f):
            vsip_vsub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.i, .i, .i):
            vsip_vsub_i (aView.vsip,subtract.vsip,output.vsip )
        case (.li, .li, .li):
            vsip_vsub_li (aView.vsip,subtract.vsip,output.vsip )
        case (.si, .si, .si):
            vsip_vsub_si (aView.vsip,subtract.vsip,output.vsip )
        case (.uc, .uc, .uc):
            vsip_vsub_uc (aView.vsip,subtract.vsip,output.vsip )
        default:
            preconditionFailure("function not supported for input/output views")
        }
    }
    public static func sub(_ aView: Matrix, subtract: Matrix, output: Matrix){
        assert(sizeEqual(aView, against: subtract),"Views must be the same size")
        assert(sizeEqual(aView, against: output), "Views must be the same size")
        let t = (aView.type, subtract.type, output.type)
        switch t{
        case (.cd, .cd, .cd):
            vsip_cmsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.cf, .cf, .cf):
            vsip_cmsub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.cd, .d, .cd):
            vsip_crmsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.cf, .f, .cf):
            vsip_crmsub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.si, .si, .si):
            vsip_msub_si (aView.vsip,subtract.vsip,output.vsip )
        case (.d, .cd, .cd):
            vsip_rcmsub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.d, .d, .d):
            vsip_msub_d (aView.vsip,subtract.vsip,output.vsip )
        case (.f, .f, .f):
            vsip_msub_f (aView.vsip,subtract.vsip,output.vsip )
        case (.i, .i, .i):
            vsip_msub_i (aView.vsip,subtract.vsip,output.vsip )
        case (.li, .li, .li):
            vsip_msub_li (aView.vsip,subtract.vsip,output.vsip )
        case (.f, .cf, .cf):
            vsip_rcmsub_f (aView.vsip,subtract.vsip,output.vsip )
        default:
            preconditionFailure("function not supported for input/output views \(t)")
        }
    }
    // Mark: - Random
    public class Rand {
        fileprivate var tryVsip : OpaquePointer?
        var vsip: OpaquePointer {
            get {
                return tryVsip!
            }
        }
        let jInit : JVSIP
        var myId : NSNumber?
        public init(seed: vsip_index, numberOfSubSequences: vsip_index, mySequence: vsip_index, portable: Bool){
            let rng = portable ? VSIP_PRNG : VSIP_NPRNG
            let id = mySequence
            let numprocs = numberOfSubSequences
            if let randObj = vsip_randcreate(seed, numprocs, id, rng){
                tryVsip = randObj
            } else {
                preconditionFailure("Failed to create vsip rand object")
            }
            jInit = JVSIP()
            myId = jInit.myId
        }
        public convenience init(seed: vsip_index, portable: Bool){
            self.init(seed: seed, numberOfSubSequences: 1, mySequence: 1, portable: portable)
        }
        public func randu(_ view: Vector){
            let t = view.type
            switch t{
            case .f:
                vsip_vrandu_f(self.vsip,view.vsip)
            case .d:
                vsip_vrandu_d(self.vsip,view.vsip)
            case .cf:
                vsip_cvrandu_f(self.vsip,view.vsip)
            case .cd:
                vsip_cvrandu_d(self.vsip,view.vsip)
            default:
                preconditionFailure("Type \(t) not defined for randu")
            }
        }
        public func randu(_ view: Matrix){
            let t = view.type
            switch t {
            case .f:
                vsip_mrandu_f(self.vsip,view.vsip)
            case .d:
                vsip_mrandu_d(self.vsip,view.vsip)
            case .cf:
                vsip_cmrandu_f(self.vsip,view.vsip)
            case .cd:
                vsip_cmrandu_d(self.vsip,view.vsip)
            default:
                preconditionFailure("Type \(t) not defined for randu")
            }
        }
        public func randn(_ view: Vector) {
            let t = view.type
            switch t{
            case .f:
                vsip_vrandn_f(self.vsip,view.vsip)
            case .d:
                vsip_vrandn_d(self.vsip,view.vsip)
            case .cf:
                vsip_cvrandn_f(self.vsip,view.vsip)
            case .cd:
                vsip_cvrandn_d(self.vsip,view.vsip)
            default:
                preconditionFailure("Type \(t) not defined for randn")
            }
        }
        public func randn(_ view: Matrix) {
            let t = view.type
            switch t{
            case .f:
                vsip_mrandn_f(self.vsip,view.vsip)
            case .d:
                vsip_mrandn_d(self.vsip,view.vsip)
            case .cf:
                vsip_cmrandn_f(self.vsip,view.vsip)
            case .cd:
                vsip_cmrandn_d(self.vsip,view.vsip)
            default:
                preconditionFailure("Type \(t) not defined for randn")
            }
        }
        deinit{
            let id = self.myId?.int32Value
            vsip_randdestroy(self.vsip)
            if _isDebugAssertConfiguration(){
                print("randdestroy id \(id!)")
            }
        }
        
    }
    // MARK: - Element Generation and Copy
    public static func copyTo(_ vector: Vector) -> [Any] {
        switch vector.type {
        case .d:
            var a = Array(repeating: vsip_scalar_d(0.0), count: vector.length)
            vsip_vcopyto_user_d(vector.vsip, &a)
            return a
        case .f:
            var a = Array(repeating: vsip_scalar_f(0.0), count: vector.length)
            vsip_vcopyto_user_f(vector.vsip, &a)
            return a
        default:
            preconditionFailure("Copy from vsip to array not supported for type \(vector.type)")
        }
    }
    public static func copyTo(_ vector: Vector, array: UnsafeMutablePointer<vsip_scalar_d>){
        switch vector.type {
        case .d:
            vsip_vcopyto_user_d(vector.vsip, array)
        default:
            preconditionFailure("Copy from vsip to array not supported for type \(vector.type)")
        }
    }
    
    // MARK: - Linear Algebra Matrix and Vector Operations
    public static func herm(_ complexInputMatrix: Matrix, complexOuputMatrix: Matrix){
        let vsipA = complexInputMatrix.vsip
        let vsipB = complexOuputMatrix.vsip
        let t = (complexInputMatrix.type, complexOuputMatrix.type)
        switch t {
        case (.cf, .cf):
            vsip_cmherm_f(vsipA, vsipB)
        case (.cd, .cd):
            vsip_cmherm_d(vsipA, vsipB)
        default:
            preconditionFailure("Type not supported for herm")
        }
    }
    public static func jdot(_ complexInputVector: Vector, complexOuputVector: Vector) -> Scalar {
        let vsipA = complexInputVector.vsip
        let vsipB = complexOuputVector.vsip
        let t = (complexInputVector.type, complexInputVector.type)
        switch t {
        case (.cf, .cf):
            return Scalar(vsip_cvjdot_f(vsipA, vsipB))
        case (.cd, .cd):
            return Scalar(vsip_cvjdot_d(vsipA, vsipB))
        default:
            preconditionFailure("Type not supported for jdot")
        }
    }
    public static func gemp(alpha: Scalar, matA: Matrix, opA: vsip_mat_op, matB: Matrix, opB: vsip_mat_op, beta: Scalar, matC: Matrix) {
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.d, .d, .d):
            vsip_gemp_d(alpha.reald, vsipA, opA, vsipB, opB, beta.reald, vsipC)
        case (.f, .f, .f):
            vsip_gemp_f(alpha.realf, vsipA, opA, vsipB, opB, beta.realf, vsipC)
        case (.cd, .cd, .cd):
            vsip_cgemp_d(alpha.vsip_cd, vsipA, opA, vsipB, opB, beta.vsip_cd, vsipC)
        case (.cf, .cf, .cf):
            vsip_cgemp_f(alpha.vsip_cf, vsipA, opA, vsipB, opB, beta.vsip_cf, vsipC)
        default:
            preconditionFailure("Type not supported for gemp")
        }
        
    }
    public static func gems(alpha: Scalar, matA: Matrix, opA: vsip_mat_op, beta: Scalar, matC: Matrix){
        let t = (matA.type,  matC.type)
        let vsipA = matA.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.d, .d):
            vsip_gems_d(alpha.reald, vsipA, opA, beta.reald, vsipC)
        case (.f, .f):
            vsip_gems_f(alpha.realf, vsipA, opA, beta.realf, vsipC)
        case (.cd, .cd):
            vsip_cgems_d(alpha.vsip_cd, vsipA, opA, beta.vsip_cd, vsipC)
        case (.cf, .cf):
            vsip_cgems_f(alpha.vsip_cf, vsipA, opA, beta.vsip_cf, vsipC)
        default:
            preconditionFailure("Type not supported for gemp")
        }
    }
    public static func kron(alpha: Scalar, vecX: Vector, vecY: Vector, matC: Matrix){
        let t = (vecX.type, vecY.type, matC.type)
        let vsipX = vecX.vsip
        let vsipY = vecY.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.f, .f, .f):
            vsip_vkron_f(alpha.realf, vsipX, vsipY, vsipC)
        case (.d, .d, .d):
            vsip_vkron_d(alpha.reald, vsipX, vsipY, vsipC)
        case (.cf, .cf, .cf):
            vsip_cvkron_f(alpha.vsip_cf, vsipX, vsipY, vsipC)
        case (.cd, .cd, .cd):
            vsip_cvkron_d(alpha.vsip_cd, vsipX, vsipY, vsipC)
        default:
            preconditionFailure("Kron not supported for argument list")
        }
    }
    public static func kron(alpha: Scalar, matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.f, .f, .f):
            vsip_mkron_f(alpha.realf, vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mkron_d(alpha.reald, vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmkron_f(alpha.vsip_cf, vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmkron_d(alpha.vsip_cd, vsipA, vsipB, vsipC)
        default:
            preconditionFailure("Kron not supported for argument list")
        }
    }
    public static func prod3(matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.f, .f, .f):
            vsip_mprod3_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mprod3_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmprod3_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmprod3_d(vsipA, vsipB, vsipC)
        default:
            preconditionFailure("VSIP function prod3 not supported for argument list")
        }
    }
    public static func prod3(matA: Matrix, vecB: Vector, vecC: Vector){
        let t = (matA.type, vecB.type, vecC.type)
        let vsipA = matA.vsip
        let vsipB = vecB.vsip
        let vsipC = vecC.vsip
        switch(t){
        case (.f, .f, .f):
            vsip_mvprod3_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mvprod3_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmvprod3_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmvprod3_d(vsipA, vsipB, vsipC)
        default:
            preconditionFailure("VSIP function prod4 not supported for argument list")
        }
    }
    public static func prod4(matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.f, .f, .f):
            vsip_mprod4_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mprod4_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmprod4_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmprod4_d(vsipA, vsipB, vsipC)
        default:
            preconditionFailure("VSIP function prod4 not supported for argument list")
        }
    }
    public static func prod4(matA: Matrix, vecB: Vector, vecC: Vector){
        let t = (matA.type, vecB.type, vecC.type)
        let vsipA = matA.vsip
        let vsipB = vecB.vsip
        let vsipC = vecC.vsip
        switch(t){
        case (.f, .f, .f):
            vsip_mvprod4_f(vsipA, vsipB, vsipC)
        case (.d, .d, .d):
            vsip_mvprod4_d(vsipA, vsipB, vsipC)
        case (.cf, .cf, .cf):
            vsip_cmvprod4_f(vsipA, vsipB, vsipC)
        case (.cd, .cd, .cd):
            vsip_cmvprod4_d(vsipA, vsipB, vsipC)
        default:
            preconditionFailure("VSIP function prod4 not supported for argument list")
        }
    }
    
    public static func prod(matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprod_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprod_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_mprod_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_mprod_f ( vsipA, vsipB, vsipC )
        default:
            preconditionFailure("VSIP function prod not supported for argument list")
        }
    }
    public static func prod(matA: Matrix, vecB: Vector, vecC: Vector){
        let t = (matA.type, vecB.type, vecC.type)
        let vsipA = matA.vsip
        let vsipB = vecB.vsip
        let vsipC = vecC.vsip
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmvprod_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmvprod_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_mvprod_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_mvprod_f ( vsipA, vsipB, vsipC )
        default:
            preconditionFailure("VSIP function prod not supported for argument list")
        }
    }
    public static func prod(vecA: Vector, matB: Matrix, vecC: Vector){
        let t = (vecA.type, matB.type, vecC.type)
        let vsipA = vecA.vsip
        let vsipB = matB.vsip
        let vsipC = vecC.vsip
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cvmprod_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cvmprod_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_vmprod_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_vmprod_f ( vsipA, vsipB, vsipC )
        default:
            preconditionFailure("VSIP function prod not supported for argument list")
        }
    }
    public static func prodh(matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprodh_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprodh_f ( vsipA, vsipB, vsipC )
        default:
            preconditionFailure("VSIP function prodh not supported for argument list")
        }
    }
    public static func prodj(matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprodj_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprodj_f ( vsipA, vsipB, vsipC )
        default:
            preconditionFailure("VSIP function prodj not supported for argument list")
        }
    }
    public static func prodt(matA: Matrix, matB: Matrix, matC: Matrix){
        let t = (matA.type, matB.type, matC.type)
        let vsipA = matA.vsip
        let vsipB = matB.vsip
        let vsipC = matC.vsip
        switch(t){
        case (.cd, .cd, .cd):
            vsip_cmprodt_d ( vsipA, vsipB, vsipC )
        case (.cf, .cf, .cf):
            vsip_cmprodt_f ( vsipA, vsipB, vsipC )
        case (.d, .d, .d):
            vsip_mprodt_d ( vsipA, vsipB, vsipC )
        case (.f, .f, .f):
            vsip_mprodt_f ( vsipA, vsipB, vsipC )
        default:
            preconditionFailure("VSIP function prodt not supported for argument list")
        }
    }
    public static func trans(matA: Matrix, matC: Matrix){
        let t = (matA.type, matC.type)
        let vsipA = matA.vsip
        let vsipC = matC.vsip
        switch(t) {
        case (.cd, .cd):
            vsip_cmtrans_d(vsipA, vsipC)
        case(.cf, .cf):
            vsip_cmtrans_f(vsipA, vsipC)
        case(.d, .d):
            vsip_mtrans_d(vsipA, vsipC)
        case(.f, .f):
            vsip_mtrans_f(vsipA, vsipC)
        default:
            preconditionFailure("VSIP function trans not supported for argument list")
        }
    }
    public static func dot(vecX: Vector, vecY: Vector) -> Scalar {
        let t = (vecX.type, vecY.type)
        let vsipX = vecX.vsip
        let vsipY = vecY.vsip
        switch(t){
        case (.f, .f):
            return Scalar(Float(vsip_vdot_f(vsipX, vsipY)))
        case (.d, .d):
            return Scalar(Double(vsip_vdot_d(vsipX, vsipY)))
        case (.cf, .cf):
            return Scalar(vsip_cvdot_f(vsipX, vsipY))
        case (.cd, .cd):
            return Scalar(vsip_cvdot_d(vsipX, vsipY))
        default:
            preconditionFailure("Kron not supported for argument list")
        }
    }
    public static func outer(alpha: Scalar, vecX: Vector, vecY: Vector, matC: Matrix){
        let vsipX = vecX.vsip
        let vsipY = vecY.vsip
        let vsipC = matC.vsip
        let t = (vecX.type, vecY.type, matC.type)
        switch(t){
        case (.f, .f, .f):
            vsip_vouter_f(alpha.realf, vsipX, vsipY, vsipC)
        case (.d, .d, .d):
            vsip_vouter_d(alpha.reald, vsipX, vsipY, vsipC)
        case (.cf, .cf, .cf):
            vsip_cvouter_f(alpha.vsip_cf, vsipX, vsipY, vsipC)
        case (.cd, .cd, .cd):
            vsip_cvouter_d(alpha.vsip_cd, vsipX, vsipY, vsipC)
        default:
            preconditionFailure("Function outer not supported for argument list")
        }
    }
    
    // MARK: - LU
    public class LU {
        
    }
    
    // MARK: - QRD
    public class QRD{
        fileprivate struct Attrib {
            let m: Int
            let n: Int
            let op: vsip_qrd_qopt
        }
        var type: Block.Types {
            return (jVsip?.type)!
        }
        fileprivate(set) var amSet = false
        fileprivate let attrib: Attrib
        var columnLength: Int {
            get{
                return attrib.m
            }
        }
        var rowLength: Int {
            get {
                return attrib.n
            }
        }
        var qrdNoSaveQ: Bool{
            get {
                return attrib.op == VSIP_QRD_NOSAVEQ
            }
        }
        var qrdSaveQ: Bool{
            get {
                return attrib.op == VSIP_QRD_SAVEQ
            }
        }
        var qrdSaveQ1: Bool{
            get {
                return attrib.op == VSIP_QRD_SAVEQ1
            }
        }
        fileprivate class qr {
            var tryVsip : OpaquePointer?
            var vsip: OpaquePointer {
                get {
                    return tryVsip!
                }
            }
            let jInit : JVSIP
            var type : Block.Types?
            init(){
                jInit = JVSIP()
            }
            
        }
        fileprivate class qr_f: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .f
                if let qrd = vsip_qrd_create_f(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_qrd_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_qrd_destroy_f(self.vsip)
                
            }
        }
        fileprivate class qr_d: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .d
                if let qrd = vsip_qrd_create_d(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_qrd_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_qrd_destroy_d(self.vsip)
                
            }
        }
        fileprivate class cqr_f: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .cf
                if let qrd = vsip_cqrd_create_f(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_cqrd_destroy_f \(jInit.myId.int32Value)")
                }
                vsip_cqrd_destroy_f(self.vsip)
                
            }
        }
        fileprivate class cqr_d: qr {
            init(m: Int, n: Int, qopt: vsip_qrd_qopt){
                super.init()
                type = .cd
                if let qrd = vsip_cqrd_create_d(vsip_length(m),vsip_length(n),qopt){
                    self.tryVsip = qrd
                } else {
                    preconditionFailure("Failed to create vsip qrd object")
                }
            }
            deinit{
                if _isDebugAssertConfiguration(){
                    print("vsip_cqrd_destroy_d \(jInit.myId.int32Value)")
                }
                vsip_cqrd_destroy_d(self.vsip)
                
            }
        }
        fileprivate let jVsip : qr?
        fileprivate var vsip: OpaquePointer {
            get {
                return (jVsip?.vsip)!
            }
        }
        init(type: Block.Types, columnLength: Int, rowLength: Int, qopt: vsip_qrd_qopt) {
            attrib = Attrib(m: columnLength, n: rowLength, op: qopt)
            self.amSet = false
            switch type {
            case .f:
                jVsip = qr_f(m: columnLength, n: rowLength, qopt: qopt)
            case .d:
                jVsip = qr_d(m: columnLength, n: rowLength, qopt: qopt)
            case .cf:
                jVsip = cqr_f(m: columnLength, n: rowLength, qopt: qopt)
            case .cd:
                jVsip = cqr_d(m: columnLength, n: rowLength, qopt: qopt)
            default:
                self.jVsip = nil
                assert(false, "QRD not supported for this type")
            }
        }
        
        public func decompose(_ aMatrix: Matrix) -> Scalar {
            let t = (aMatrix.type, self.type)
            switch t {
            case(.f,.f):
                return Scalar(vsip_qrd_f(self.vsip, aMatrix.vsip))
            case(.d,.d):
                return Scalar(vsip_qrd_d(self.vsip, aMatrix.vsip))
            case(.cf,.cf):
                return Scalar(vsip_cqrd_f(self.vsip, aMatrix.vsip))
            case(.cd,.cd):
                return Scalar(vsip_cqrd_d(self.vsip, aMatrix.vsip))
            default:
                preconditionFailure("Types \(t) not supported for qrd decompostion")
            }
        }
        public func prodq(matrixOperator op: vsip_mat_op, matrixSide side: vsip_mat_side, matrix: Matrix) {
            let t = (self.type, op, side, matrix.type)
            switch t{
            case (.f, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_NTRANS, VSIP_MAT_LSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.f, VSIP_MAT_TRANS, VSIP_MAT_LSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_TRANS, VSIP_MAT_LSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_HERM, VSIP_MAT_LSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_HERM, VSIP_MAT_LSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.f, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_NTRANS, VSIP_MAT_RSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.f, VSIP_MAT_TRANS, VSIP_MAT_RSIDE, .f):
                vsip_qrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.d, VSIP_MAT_TRANS, VSIP_MAT_RSIDE, .d):
                vsip_qrdprodq_d(self.vsip, op, side, matrix.vsip)
            case (.cf, VSIP_MAT_HERM, VSIP_MAT_RSIDE, .cf):
                vsip_cqrdprodq_f(self.vsip, op, side, matrix.vsip)
            case (.cd, VSIP_MAT_HERM, VSIP_MAT_RSIDE, .cd):
                vsip_cqrdprodq_d(self.vsip, op, side, matrix.vsip)
            default:
                preconditionFailure("Type \(t) not supported for QRD prodq.")
            }
        }
        public func solveR() {
            
        }
        public func solveCovariance() {
            
        }
        
    }
    
    // MARK: - SVD
    // needs work on error checks
    /*!
     For SVD given input matrix A we have
     A = U S transpose(V)
     */
    public class Svd {
        let type: Block.Types
        let n: Int  // length of singular value vector
        var amSet = false
        fileprivate let jVsip : sv?
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
            var type : Block.Types?
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
                vsip_svd_destroy_d(self.vsip)
                vsip_valldestroy_d(self.s)
            }
        }
        
        public init(type: Block.Types, m: Int, n: Int, saveU: vsip_svd_uv, saveV: vsip_svd_uv){
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
            self.init(type: view.type, m: view.columnLength, n: view.rowLength, saveU: saveU, saveV: saveV)
        }
        public convenience init(view: Matrix){
            self.init(type: view.type, m: view.columnLength, n: view.rowLength, saveU: VSIP_SVD_UVFULL, saveV: VSIP_SVD_UVFULL)
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
                preconditionFailure("function not supported for input/output views")
            }
            self.amSet = true
        }
        public func decompose(_ matrix: Matrix) -> Vector {
            let v = Vector(length: self.n, type: self.type)
            self.decompose(matrix, singularValues: v)
            return v
        }
        /*!
         Function matU returns 0 on success
         Output data is stored in matrix matU in natural order starting at
         element index (0,0). Matrix matU must be large enough to hold the
         output data
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
         output data
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
    }
    
    // MARK: - JVSIP added functionality
    public class Jvsip {
        public static func normFro(view: Vector) -> Vsip.Scalar {
            switch view.type {
            case .f:
                return Vsip.sumsqval(view).sqrt
            case .d:
                return Vsip.sumsqval(view).sqrt
            case.cf:
                return (Vsip.sumsqval(view.real) + Vsip.sumsqval(view.imag)).sqrt
            case.cd:
                return (Vsip.sumsqval(view.real) + Vsip.sumsqval(view.imag)).sqrt
            default:
                preconditionFailure("normFro not supported for this view")
            }
        }
        public static func normFro(view: Matrix) -> Vsip.Scalar {
            switch view.type {
            case .f:
                return Vsip.sumsqval(view).sqrt
            case .d:
                return Vsip.sumsqval(view).sqrt
            case.cf:
                return (Vsip.sumsqval(view.real) + Vsip.sumsqval(view.imag)).sqrt
            case.cd:
                return (Vsip.sumsqval(view.real) + Vsip.sumsqval(view.imag)).sqrt
            default:
                preconditionFailure("normFro not supported for this view")
            }
        }
        
        public static func decompose(_ aMatrix: Vsip.Matrix) -> (Q: Vsip.Matrix, R: Vsip.Matrix){
            let qrd = Vsip.QRD(type: aMatrix.type, columnLength: aMatrix.columnLength, rowLength: aMatrix.rowLength, qopt: VSIP_QRD_SAVEQ)
            let Q = Vsip.Matrix(columnLength: qrd.columnLength, rowLength: qrd.columnLength, type: aMatrix.type, major: VSIP_ROW)
            let R = Vsip.Matrix(columnLength: qrd.columnLength, rowLength: qrd.rowLength, type: aMatrix.type, major: VSIP_ROW)
            let aCopy = aMatrix.copy
            Q.fill(0.0)
            R.fill(0.0)
            print("create/destroy Q.diagview")
            Q.diagview.fill(1.0)
            print("call qrd.decompose")
            let _ = qrd.decompose(aMatrix)
            qrd.prodq(matrixOperator: VSIP_MAT_NTRANS, matrixSide: VSIP_MAT_LSIDE, matrix: Q)
            print("create Qt")
            let Qt = Q.transview
            Vsip.prod(matA: Qt, matB: aCopy, matC: R)
            return (Q,R)
        }
        
    }
    
}
