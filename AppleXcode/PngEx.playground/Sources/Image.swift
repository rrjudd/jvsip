import Cocoa
public func makeRGBImageContext(width: Int, height: Int, buffer: [Double]) -> CGContext
{
    let bitmapInfo = CGImageAlphaInfo.premultipliedLast.rawValue
    let colorSpace = CGColorSpaceCreateDeviceRGB()
    let context = CGContext(data: nil, width: width, height: height, bitsPerComponent: 8, bytesPerRow: 4 * width, space: colorSpace, bitmapInfo: bitmapInfo)
    var pix: [UInt8] = [0,0,0,0]
    let dta = UnsafeMutablePointer<UInt8>(mutating: context?.data?.assumingMemoryBound(to: UInt8.self))!
    // Write image data
    for y in 0..<height {
        let jmp = 4 * width * y
        for x in 0..<width {
            let indxBuf = y * width + x
            setRGB(ptr: &pix, val: buffer[indxBuf])
            let indxPix = 4 * x + jmp
            dta[indxPix] = pix[0]   // red
            dta[indxPix+1] = pix[1] // green
            dta[indxPix+2] = pix[2] // blue
            dta[indxPix+3] = pix[3] // alpha
        }
    }
    return context!
}

public func makeImage(context: CGContext) -> NSImage {
    let size = NSSize(width: context.width, height: context.height)
    return NSImage(cgImage: context.makeImage()!, size: size)
}
