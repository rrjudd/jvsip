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
