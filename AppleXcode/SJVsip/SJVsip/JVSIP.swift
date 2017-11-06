//
//  JVSIP.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//
/**
 An instance of JVSIP class is stored in every VSIP object.
 The first time it is called it will call vsip_init
 When the garbage collector has collected the last one vsip_finalize is called
 The reference count is kept as a class variable
 */
import Foundation
import vsip
public class JVSIP {
    static var vsipInit : UInt = 0
    static var num = NSNumber(value: 0 as Int32)
    var myId: NSNumber
    func initInc() {
        JVSIP.vsipInit += 1;
    }
    func initDec() {
        JVSIP.vsipInit -= 1;
    }
    func vsipInitGTzero() -> Bool{
        if JVSIP.vsipInit > 0{
            return true
        } else {
            return false
        }
    }
    func vsipInitEQzero() -> Bool{
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
