//
//  main.swift
//  JVExVector
//
//  Created by Randall Judd on 10/15/16.
//  Copyright © 2016 JVSIP. All rights reserved.
//

import Foundation

let v = JVVector_d(length: 10)
v.ramp(start: 0.1, step: 0.2)
print("vector of length 10 and offset 0")
for i in 0..<v.length{
    print(v[i])
}
v.length = 5
v.stride = 2
print("vector of length 5 and offset 0")
for i in 0..<v.length{
    print(v[i])
}
v.offset = 1
print("vector of length 5 and offset 1")
for i in 0..<v.length{
    print(v[i])
}


