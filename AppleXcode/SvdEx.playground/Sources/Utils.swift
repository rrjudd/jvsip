import Foundation
import SJVsip

public func checkSvd(_ svd:Svd, against M: Matrix) -> Bool {
    let chk = M.empty
    chk.fill(Scalar(0.0))
    let tmp = chk.newCopy
    let U = svd.matU!
    let Vt = svd.matV!.transview
    let s = svd.vecS
    copy(from: s, to: chk.diagview)
    prod(chk, times: Vt, resultsIn: tmp)
    prod(U, times: tmp, resultsIn:chk)
    sub(chk, subtract: M, resultsIn: chk)
    let aNumber = sumsqval(chk).reald/sumsqval(M).reald
    print(aNumber)
    return aNumber < 1E-10
}
