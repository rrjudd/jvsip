import Foundation

public func setRGB(ptr: inout [UInt8], val: Double)
{
    var v = Int(val * 767)
    if (v < 0) {
        v = 0
    } else if (v > 767){
        v = 767
    }
    let offset: Int = v % 256
    
    if (v<256) {
        ptr[0] = 0; ptr[1] = 0; ptr[2] = UInt8(offset)
    }
    else if (v<512) {
        ptr[0] = 0; ptr[1] = UInt8(offset); ptr[2] = 255 - UInt8(offset)
    }
    else {
        ptr[0] = UInt8(offset); ptr[1] = 255 - UInt8(offset); ptr[2] = 0
    }
    ptr[3] = 255
}
