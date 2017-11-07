//: K-Omega Beaformer Example

//: This example is a straightforward conversion (more or less) of a C example using C-VSIPL
//: The C code is stored in the Resources directory along with the parameters.

import Cocoa
import vsip
var filePath = Bundle.main.path(forResource: "param_file", ofType: nil)
let param = Param(parameterFile: filePath)
param.log()
let ts = TimeSeries(param: param)
let kw = KW(param: param)
let Navg = param.Navg!
let dtaIn = ts.instance()
let gramOut = kw.instance()
kw.zero();
for _ in 0..<Navg {
    ts.zero();
    ts.nb_sim();
    ts.noise_sim();
    kw.komega(m_data: dtaIn);
}
for i in 0..<vsip_mgetrowlength_d(gramOut){/* move zero to middle */
    let v = vsip_mcolview_d(gramOut, i);
    vsip_vfreqswap_d(v)
    vsip_vdestroy_d(v)
}
/* massage the data for plot*/
var max = vsip_mmaxval_d(gramOut, nil)
let avg = vsip_mmeanval_d(gramOut);
vsip_mclip_d(gramOut,0.0, max, avg/100000.0, max, gramOut);
vsip_mlog10_d(gramOut,gramOut);
let min = -vsip_mminval_d(gramOut, nil)
vsip_smadd_d(min, gramOut, gramOut);
max = vsip_mmaxval_d(gramOut, nil);
vsip_smmul_d(1.0/max, gramOut, gramOut);
/* output data and plot with octave */
let fptr = fopen("/Users/judd/gramOut","w");
let size = Int(vsip_mgetrowlength_d(gramOut) * vsip_mgetcollength_d(gramOut))
var out: [Double] = Array<Double>(repeating: 0.0, count: size)
vsip_mcopyto_user_d(gramOut, VSIP_COL, &out)
let imageContext = makeRGBImage(width: 128, height: 512, buffer: out)
let image = imageContext.makeImage()
let nsimage = NSImage(cgImage: image!, size: NSSize(width: 128, height: 512))
fwrite(out,size,MemoryLayout<vsip_scalar_d>.size,fptr)
fclose(fptr)
let w = Int(vsip_mgetrowlength_d(gramOut))
let h = Int(vsip_mgetcollength_d(gramOut))
let s = NSSize(width: w, height: h)
CGBitmapInfo.alphaInfoMask
CGBitmapInfo.floatComponents
CGBitmapInfo.floatInfoMask


