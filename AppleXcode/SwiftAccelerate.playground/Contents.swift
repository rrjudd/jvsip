import Foundation
import Accelerate
var b1 = Block(length: 100, type: .d)
var b2 = Block(length: 100, type: .cd)
var b3 = Block(length: 100, type: .i)
var v1 = Vector(block: b1,offset: 0,stride: 1,length: b1.count)
var v2 = Vector(block: b2,offset: 0, stride: 1, length: b2.count)
var v3 = Vector(block: b3, offset: 1, stride: 1, length: b3.count)
var v4 = Vector(length: 50, type: .d)

let a = Scalar(DSPDoubleComplex(real: 1.0, imag: 2.0))
var m2 = Matrix(block: b2, offset: 2, colstride: 10, collength: 5, rowstride: 2, rowlength: 4)
v2.fill(value: Scalar(1.0))//Scalar(DSPDoubleComplex(real: 0.0, imag: 0.0)))
for i in 0..<5{
    print(v2[i].string(format: "5.1"))
}
m2[3,3] = a
for j in 0..<m2.collength{
    var s = ""
    for i in 0..<m2.rowlength {
        s += m2[i,j].string(format: "5.1") + ", "
    }
    s += ";"
    print(s)
}
let result = Scalar(1) * Scalar(1.0) + Scalar(0.1)
v2.ramp(start: Scalar(1.0), increment: Scalar(DSPDoubleComplex(real: 0.1, imag: 0.1)))
for i in 0..<5{
    print(v2[i].string(format: "5.1"))
}
for j in 0..<m2.collength{
    var s = ""
    for i in 0..<m2.rowlength {
        s += m2[i,j].string(format: "5.1") + ", "
    }
    s += ";"
    print(s)
}


/* let buffer:UnsafeMutablePointer<Float>
buffer = UnsafeMutablePointer<Float>.allocate(capacity: 100)
buffer.initialize(to: 0.0, count: 100)
var aFloat = Float(10.0)
vDSP_vfill(&aFloat, buffer, 1, 100)
var s = Float(1.0)
var i = Float(1.0)
vDSP_vramp(&s, &i, buffer, 1, 100)
for i in 0..<10{
    print(buffer[i])
}
s = -1.0; i = -1.0
vDSP_vramp(&s, &i, buffer, 2, 50)
for i in 0..<10{
    print(buffer[i])
}
for i in 0..<10{
    print(buffer[2 * i])
}
buffer.deinitialize()
print(buffer[1])
free(buffer)
print(buffer[1]) */




