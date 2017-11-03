//
//  VectorExplorerControllerWindow.swift
//  VectorExplorer
//
//  Created by Randall R. Judd on 1/16/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Cocoa
import SwiftVsip

class VectorExplorerControllerWindow: NSWindowController {
    
    @IBOutlet weak var block: NSTextField!
    @IBOutlet weak var offset: NSTextField!
    @IBOutlet weak var stride: NSTextField!
    @IBOutlet weak var length: NSTextField!
    @IBOutlet weak var vectorValues: NSTextView!
    @IBOutlet weak var blockValues: NSTextView!
    
    var blk: Vsip.Block?
    var vec: Vsip.Vector?
    
    override var windowNibName: String? {
        return "VectorExplorerControllerWindow"
    }
    
    override func windowDidLoad() {
        super.windowDidLoad()
        self.block.integerValue = 1
        self.offset.integerValue = 0
        self.length.integerValue = 1
        self.stride.integerValue = 0

        // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    }
    
    @IBAction func blockCreate(sender: AnyObject){
        let length = block.integerValue
        self.blk = createBlock(length: length)
        self.vec = Vsip.Vector(block: self.blk!, offset: 0, stride: 1, length: length)
        self.offset.integerValue = 0
        self.stride.integerValue = 1
        self.length.integerValue = length
        let _ = self.blk?.vector().ramp(Vsip.Scalar(0.0), increment: Vsip.Scalar(1.0))
        self.vectorValues.string = (self.vec?.mString("3.0"))!
        self.blockValues.string = self.blk?.vector().mString("3.0")
    }
    fileprivate var toLong: Bool {
        return (self.vec?.offset)! + (self.vec?.stride)! * (self.vec?.length)! > (self.blk?.length)!
    }
    fileprivate var toShort: Bool {
        return (self.vec?.offset)! + (self.vec?.stride)! * (self.vec?.length)! < 1
    }
    @IBAction func setOffset(sender: AnyObject){
        self.vec?.offset = self.offset.integerValue
        if toLong {
            self.vectorValues.string = "Too Long"
        } else if toShort {
            self.vectorValues.string = "Too Short"
        } else {
            self.vectorValues.string = (self.vec?.mString("3.0"))!
        }
    }
    @IBAction func setLength(sender: AnyObject){
        self.vec?.length = self.length.integerValue
        if toLong {
            self.vectorValues.string = "Too Long"
        } else if toShort {
            self.vectorValues.string = "Too Short"
        } else {
            self.vectorValues.string = (self.vec?.mString("3.0"))!
        }
    }
    @IBAction func setStride(sender: AnyObject) {
        self.vec?.stride = self.stride.integerValue
        if toLong {
            self.vectorValues.string = "Too Long"
        } else if toShort {
            self.vectorValues.string = "Too Short"
        } else {
            self.vectorValues.string = (self.vec?.mString("3.0"))!
        }
    }
}
