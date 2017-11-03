//
//  MainWindowController.swift
//  MatrixExplorer
//
//  Created by Randall R. Judd on 1/17/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Cocoa
import SwiftVsip

class MainWindowController: NSWindowController {
    
    var blk: Vsip.Block?
    var mtrx: Vsip.Matrix?
    @IBOutlet weak var size: NSTextField!
    @IBOutlet weak var block: NSTextView!
    @IBOutlet weak var matrix: NSTextField!
    @IBOutlet weak var offset: NSTextField!
    @IBOutlet weak var rowLength: NSTextField!
    @IBOutlet weak var rowStride: NSTextField!
    @IBOutlet weak var colLength: NSTextField!
    @IBOutlet weak var colStride: NSTextField!

    var blockLength: Int {
        return (blk?.length)!
    }
    
    override var windowNibName: String? {
        return "MainWindowController"
    }
    override func windowDidLoad() {
        super.windowDidLoad()
        self.offset.integerValue = 0
        self.rowStride.integerValue = 0
        self.colStride.integerValue = 0
        self.rowLength.integerValue = 1
        self.colLength.integerValue = 1

        // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
    }
    var maxBlockIndex: Int {
        return (self.mtrx?.offset)! +
            ((self.mtrx?.columnLength)! - 1) * (self.mtrx?.rowStride)! +
            ((self.mtrx?.rowLength)! - 1) * (self.mtrx?.columnStride)!
    }
    var toLong: Bool {
        return maxBlockIndex > self.blockLength - 1
    }
    var toShort: Bool {
        return maxBlockIndex < 0
    }
    @IBAction func createBlock(sender: AnyObject) {
        self.blk = Vsip.Block(length: self.size.integerValue, type: .d)
        let v = self.blk?.vector().ramp(Vsip.Scalar(0.0), increment: Vsip.Scalar(1.0))
        self.block.string = v?.mString("5.0")
        let m = Int(sqrt(Double(blockLength)))
        self.mtrx = Vsip.Matrix(block: self.blk!, offset: 0, columnStride: m, columnLength: m, rowStride: 1, rowLength: m)
        self.matrix.stringValue = (self.mtrx?.mString("5.0"))!
        self.rowLength.integerValue = m
        self.colLength.integerValue = m
        self.rowStride.integerValue = 1
        self.colStride.integerValue = m
        self.offset.integerValue = 0
    }
    @IBAction func setOffset(sender: AnyObject) {
        self.mtrx?.offset = self.offset.integerValue
        if !toLong && !toShort {
            self.matrix.stringValue = (self.mtrx?.mString("%5.0"))!
        } else {
            self.matrix.stringValue = toLong ? "Too Long" : "Too Short"
        }
    }
    @IBAction func setRowLength(sender: AnyObject) {
        self.mtrx?.rowLength = self.rowLength.integerValue
        if !toLong && !toShort {
            self.matrix.stringValue = (self.mtrx?.mString("5.0"))!
        } else {
            self.matrix.stringValue = toLong ? "Too Long" : "Too Short"
        }
    }
    @IBAction func setRowStride(sender: AnyObject) {
        self.mtrx?.rowStride = self.rowStride.integerValue
        if !toLong && !toShort {
            self.matrix.stringValue = (self.mtrx?.mString("5.0"))!
        } else {
            self.matrix.stringValue = toLong ? "Too Long" : "Too Short"
        }
    }
    @IBAction func setColLength(sender: AnyObject) {
        self.mtrx?.columnLength = self.colLength.integerValue
        if !toLong && !toShort {
            self.matrix.stringValue = (self.mtrx?.mString("5.0"))!
        } else {
            self.matrix.stringValue = toLong ? "Too Long" : "Too Short"
        }
        self.matrix.maximumNumberOfLines = self.colLength.integerValue
        
    }
    @IBAction func setColStride(sender: AnyObject) {
        self.mtrx?.columnStride = self.colStride.integerValue
        if !toLong && !toShort {
            self.matrix.stringValue = (self.mtrx?.mString("5.0"))!
        } else {
            self.matrix.stringValue = toLong ? "Too Long" : "Too Short"
        }
    }
    
    
}
