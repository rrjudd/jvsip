//: Playground - noun: a place where people can play

import Cocoa

let mb = createMandelbrotImage(width: 500, height: 500, xS:  -0.802, yS: -0.177, rad: 0.011, maxIteration: 110)
let context = makeRGBImageContext(width: 500, height: 500, buffer: mb)
let image = makeImage(context: context)

