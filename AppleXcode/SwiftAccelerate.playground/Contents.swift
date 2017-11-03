import Foundation
import Accelerate

var vec = Vector(length: 15, type: .d)
print("local ramp")
vec.ramp(start: Scalar(0.1), increment: Scalar(0.2))
for i in 0..<vec.length {
    print(vec[i].string(format: "4.2"))
}
vec.length = vec.length/2
vec.stride = vec.stride * 2
print("\nvdsp_Ramp")
vec.vdsp_ramp(start: Scalar(1.0), increment: Scalar(2.0))
for i in 0..<vec.length {
    print(vec[i].string(format: "4.2"))
}
vec.stride = 1
vec.length = 15
print("\n Combined Ramp")
for i in 0..<vec.length {
    print(vec[i].string(format: "4.2"))
}
vec.length = vec.length/2
vec.stride = vec.stride * 2
vec.offset = 1
print("\new vdsp_ramp")
vec.vdsp_ramp(start: Scalar(1.0), increment: Scalar(2.0))
for i in 0..<vec.length {
    print(vec[i].string(format: "4.2"))
}
vec.stride = 1
vec.length = 15
vec.offset = 0
print("\n New Combined Ramp")
for i in 0..<vec.length {
    print(vec[i].string(format: "4.2"))
}

print("\nsumval " + vec.sumval.string(format: "5.3"))
print("\nvdsp_sumval " + vec.vdsp_sumval.string(format: "5.3"))
let blk = Block(length: 1000, type: .d)
var mat = Matrix(block: blk, offset: 10, colstride: 15, collength: 5, rowstride: 2, rowlength: 5)
var v = Vector(block: blk, offset: 0, stride: 1, length: blk.count)
v.ramp(start: Scalar(0.0), increment: Scalar(1.0))
print(mat.string(format: "3.1"))
var r = mat.row(2)
r.ramp(start: Scalar(0.1), increment: Scalar(0.3))
print(mat.row(1).string(format: "3.2"))
print(mat.col(2).string(format: "3.2"))
print(mat.diag(-1).string(format: "3.2)"))
print(mat.string(format: "3.2"))

var b = Block(length: 100, type: .d)
b[5] = Scalar(3.2)
print(b[5].string(format: "4.2"))
var v_b = Vector(block: b, offset: 7, stride: 2, length: 8)
v_b.vdsp_fill(value: Scalar(5.0))
print(v_b.string(format: "4.2"))

