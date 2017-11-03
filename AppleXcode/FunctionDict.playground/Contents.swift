//: Using a Dictionary to hold a list of function pointers

import Cocoa
import vsip
import SwiftVsip
var unaryVectorOperation: Dictionary<String, (_: Vsip.Vector, _: Vsip.Vector) -> Void >  = [:]
var binaryVectorOperation: Dictionary<String,(_: Vsip.Vector, _: Vsip.Vector, _: Vsip.Vector) -> Void >  = [:]
unaryVectorOperation["sin"] = Vsip.sin
unaryVectorOperation["cos"] = Vsip.cos
unaryVectorOperation["tan"] = Vsip.tan
unaryVectorOperation["acos"] = Vsip.acos
unaryVectorOperation["asin"] = Vsip.asin
binaryVectorOperation["add"] = Vsip.add
binaryVectorOperation["sub"] = Vsip.sub
binaryVectorOperation["mul"] = Vsip.mul
binaryVectorOperation["div"] = Vsip.add
    //{(x: Vsip.Vector, y: Vsip.Vector) ->  Void in Vsip.sin(x, resultsIn: y)}
let x = Vsip.Vector(length: 1000, type: .d)
let y = x.empty
x.ramp(Vsip.Scalar(0.0), increment: Vsip.Scalar(Double.pi/200.0))
unaryVectorOperation["cos"]!(x, y)
for i in 0..<x.length {
    x[i].reald
    y[i].reald
}
let z = y.empty
unaryVectorOperation["acos"]!(y,z)
for i in 0..<y.length {
    z[i].reald
}
binaryVectorOperation["div"]!(x,y,z)
for item in z {
    item.reald
}