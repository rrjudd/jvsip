//
//  jvsipFTests.swift
//  jvsipFTests
//
//  Created by Randall Judd on 10/2/16.
//  Copyright © 2016 Independent Consultant. All rights reserved.
//

import XCTest

class jvsipFTests: XCTestCase {
    
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
    func testAdd(){
        let _ = vsip_init(nil)
        let v = vsip_vcreate_f(10, VSIP_MEM_NONE)
        vsip_vramp_f(0,1.0,v)
        vsip_vadd_f(v,v,v)
        for i in 0..<10{
            print(vsip_vget_f(v,vsip_index(i)))
        }
        vsip_valldestroy_f(v)
        vsip_finalize(nil)
    }
    func testMul(){
        let _ = vsip_init(nil)
        let v = vsip_vcreate_d(10, VSIP_MEM_NONE)
        vsip_vramp_d(0.0,1.0,v)
        vsip_vmul_d(v,v,v)
        for i in 0..<10{
            print(vsip_vget_d(v,vsip_index(i)))
        }
        vsip_valldestroy_d(v)
        vsip_finalize(nil)
    }
    
}
