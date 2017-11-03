import Foundation

public struct Param{
    public var c: Double?                     /* propagation speed        */
    public var Fs: Double?                   /* Sample Rate              */
    public var Nts: Int?                     /* length of time series    */
    public var Dsens: Double?                /* distance between sensors */
    public var Nsens: Int?                  /* number of sensors        */
    public var Navg: Int?                    /* number of instances to average in beamformer*/
    public var Nsim: Int?             /* number of tones to simulate     */
    public var freqs: [Double] = []      /* (array) frequencies to simulate */
    public var bearings: [Double] = []   /* (array) bearing of each frequencys */
    public var Nsim_noise: Int?              /* number of noise directions to simualte */
    public init(parameterFile: String?){
        let input = try! String(contentsOfFile: parameterFile!)
        let rawParams = input.components(separatedBy: "*")
        var t = rawParams[1].components(separatedBy: " ")[0]
        c = Double(t)
        t = rawParams[2].components(separatedBy: " ")[0]
        Fs = Double(t)
        t = rawParams[3].components(separatedBy: " ")[0]
        Nts = Int(t)
        t = rawParams[4].components(separatedBy: " ")[0]
        Dsens = Double(t)
        t = rawParams[5].components(separatedBy: " ")[0]
        Nsens = Int(t)
        t = rawParams[6].components(separatedBy: " ")[0]
        Navg = Int(t)
        t = rawParams[7].components(separatedBy: " ")[0]
        Nsim = Int(t)
        for i in 8..<(Nsim! + 8) {
            t = rawParams[i].components(separatedBy: " ")[0]
            freqs.append(Double(t)!)
            t = rawParams[i + Nsim!].components(separatedBy: " ")[0]
            bearings.append(Double(t)!)
        }
        t = rawParams[8 + 2 * Nsim!].components(separatedBy: " ")[0]
        Nsim_noise = Int(t)
    }
    public func log(){
        print("c: " + String(format: "%f", self.c!))
        print("Fs: " + String(format: "%f", self.Fs!))
        print("Nts: " + String(format: "%f", self.Nts!))
        print("Dsens: " + String(format: "%f", self.Dsens!))
        print("Nsens: " + String(format: "%f", self.Nsens!))
        print("Navg: " + String(format: "%d", self.Navg!))
        print("Nsim: " + String(format:" %d", self.Nsim!))
        print("Nsim_noise: " + String(format: "%d", Nsim_noise!))
        for i in 0..<self.Nsim! {
            var outString = "Narrow Band Signal \(i): "
            outString += String(format: "%5.1f Hz at %5.1f deg", self.freqs[i], self.bearings[i])
            print(outString)
        }
    }
}
