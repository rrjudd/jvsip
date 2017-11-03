import Foundation
import vsip

public func VU_vfprintxyg_d(_ format: String,_ x: OpaquePointer ,_ y: OpaquePointer,_ fname: String)
{
    let N = vsip_length(vsip_vgetlength_d(y))
    let of = fopen(fname.cString(using: .ascii)!,"w".cString(using: .ascii))
    for i in 0..<N {
        let out = String(format: format, vsip_vget_d(x,i), vsip_vget_d(y,i)).cString(using: .ascii)!
        fwrite(out, MemoryLayout<Int8>.size, out.count - 1, of)
    }
    fclose(of);
}
