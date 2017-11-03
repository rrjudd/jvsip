//
//  AppDelegate.swift
//  VectorInspector
//
//  Created by Randall R. Judd on 1/16/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    var vectorExplorerControllerWindow: VectorExplorerControllerWindow?
    
    func applicationDidFinishLaunching(_ aNotification: Notification) {
        // Insert code here to initialize your application
        let window = VectorExplorerControllerWindow()
        window.showWindow(self)
        self.vectorExplorerControllerWindow = window
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }


}

