import Foundation

public func createMandelbrotImage(width: Int, height: Int, xS: Double, yS: Double, rad: Double, maxIteration:  Int) -> [Double] {
    var buffer = Array<Double>(repeating: 0.0, count: width * height)
    var minMu = Double(maxIteration)
    var maxMu = 0.0
    for yPos in 0..<height {
        let yP: Double = (yS-rad) + (2.0 * rad/Double(height)) * Double(yPos);
        
        for xPos in 0..<width {
            let xP: Double = (xS - rad) + (2.0 * rad/Double(width)) * Double(xPos)
            
            var iteration:Int = 0
            var x = 0.0
            var y = 0.0
            while x * x + y * y <= 4 && iteration < maxIteration {
                let tmp = x * x - y * y + xP
                y = 2 * x * y + yP
                x = tmp;
                iteration += 1
            }
            if iteration < maxIteration {
                let modZ = sqrt(x * x + y * y)
                let mu = Double(iteration) - (log(log(modZ))) / log(2.0)
                if mu > maxMu {
                    maxMu = mu
                }
                if mu < minMu {
                    minMu = mu
                }
                buffer[yPos * width + xPos] = mu
            }
            else {
                buffer[yPos * width + xPos] = 0
            }
        }
    }
    // Scale buffer values between 0 and 1
    var count = width * height;
    while count > 0 {
        count -= 1
        buffer[count] = (buffer[count] - minMu) / (maxMu - minMu)
    }
    return buffer
}
