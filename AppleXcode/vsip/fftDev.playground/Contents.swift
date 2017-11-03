//: Playground - noun: a place where people can play
import Foundation

let N = 16812*7*11*7*7*19*27*89*1280
let p = nuV(N: N)
print(N)
print(p.0)
print(p.1)
print(p.2)
var n = pow(Double(p.1[0]), Double(p.0[0]))
for i in 1..<p.0.count{
    n *= pow(Double(p.1[i]), Double(p.0[i]))
}
print(n)
