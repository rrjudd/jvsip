import Foundation
import vsip

public func VU_vfprintyg_d(format: String, a: OpaquePointer, fname: String){
    let N = vsip_vgetlength_d(a);
    let of = fopen(fname,"w+");
    for i in 0..<N {
        let out = String(format: format, vsip_vget_d(a,i)).cString(using: .ascii)
        fwrite(out, MemoryLayout<Int8>.size, out!.count - 1, of)
    }
    fclose(of);
}
