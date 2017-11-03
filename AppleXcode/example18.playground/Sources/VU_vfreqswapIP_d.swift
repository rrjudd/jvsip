import Foundation
import vsip

public func oddNumber(_ n: Int) -> Bool {
    let b = n % 2
    return b == 1
}

public func VU_vfreqswapIP_d(b: OpaquePointer){
    let N = vsip_vgetlength_d(b);
    if oddNumber(Int(N)) {
        let a1 = vsip_vsubview_d(b,vsip_index((N/2)+1),vsip_length(N/2))
        let a2 = vsip_vsubview_d(b,vsip_index(0), vsip_length((N/2)+1))
        let a3 = vsip_vcreate_d(vsip_length((N/2)+1), VSIP_MEM_NONE);
        vsip_vcopy_d_d(a2,a3);
        vsip_vputlength_d(a2,(vsip_length)(N/2));
        vsip_vcopy_d_d(a1,a2);
        vsip_vputlength_d(a2,(vsip_length)(N/2) + 1);
        vsip_vputoffset_d(a2,(vsip_offset)(N/2));
        vsip_vcopy_d_d(a3,a2);
        vsip_vdestroy_d(a1); vsip_vdestroy_d(a2);
        vsip_valldestroy_d(a3);
    } else { /* even */
        let a1 = vsip_vsubview_d(b,vsip_index(N/2),vsip_length(N/2))
        vsip_vputlength_d(b,(vsip_length)(N/2));
        vsip_vswap_d(b,a1);
        vsip_vdestroy_d(a1);
        vsip_vputlength_d(b,N);
    }
    return;
}
