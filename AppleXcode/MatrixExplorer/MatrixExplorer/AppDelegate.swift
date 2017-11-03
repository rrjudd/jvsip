//
//  AppDelegate.swift
//  MatrixExplorer
//
//  Created by Randall R. Judd on 1/17/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Cocoa

@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    var window: MainWindowController?

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        // Insert code here to initialize your application
        let window = MainWindowController()
        window.showWindow(self)
        self.window = window
    }

    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }


}

