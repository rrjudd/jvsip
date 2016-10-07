//
//  SwiftVsipTests.swift
//  SwiftVsipTests
//
//  Created by Randall Judd on 10/7/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import XCTest
@testable import SwiftVsip

class SwiftVsipTests: XCTestCase {
    
    override func setUp() {
        super.setUp()
        // Put setup code here. This method is called before the invocation of each test method in the class.
    }
    
    override func tearDown() {
        // Put teardown code here. This method is called after the invocation of each test method in the class.
        super.tearDown()
    }
    
    func testExample() {
        // This is an example of a functional test case.
        // Use XCTAssert and related functions to verify your tests produce the correct results.
    }
    
    func testPerformanceExample() {
        // This is an example of a performance test case.
        self.measure {
            // Put the code you want to measure the time of here.
        }
    }
    func testVector() {
        let v = Vector(length: 10, type: .cd)
        v.randn(8)
        v.mPrint("4.3")
        v.real.mPrint("4.3")
        v.imag.mPrint("4.3")
        
    }
    
}
