//
//  jvsip.swift
//  vsip
//
//  Created by Randall Judd on 3/21/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//
// An instance of this class is stored in every VSIP object.
// The first time it is called it will call vsip_init
// When the garbage collector has collected the last one vsip_finalize is called
// The reference count is kept as a class variable

import Foundation
import vsip
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


