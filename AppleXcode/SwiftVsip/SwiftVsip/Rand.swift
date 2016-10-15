//
//  Rand.swift
//  vsip
//
//  Created by Randall Judd on 4/21/16.
//  Copyright © 2016 RANDALL JUDD. All rights reserved.
//

import Foundation
import vsip
public class Rand {
    var vsip : OpaquePointer? = nil
    let jInit : JVSIP
    var myId : NSNumber?
    public init(seed: vsip_index, numberOfSubSequences: vsip_index, mySequence: vsip_index, portable: Bool){
        let rng = portable ? VSIP_PRNG : VSIP_NPRNG
        let id = mySequence
        let numprocs = numberOfSubSequences
        self.vsip = vsip_randcreate(seed, numprocs, id, rng)
        jInit = JVSIP()
        myId = jInit.myId
    }
    public convenience init(seed: vsip_index, portable: Bool){
        self.init(seed: seed, numberOfSubSequences: 1, mySequence: 1, portable: portable)
    }
    public func randu(_ view: Vector) -> Vector{
        let definedTypes: Set = ["f","d","cf","cd"]
        let t = view.type.rawValue
        assert(definedTypes.contains(t), "Random only defined for real or complex float values")
        switch t{
        case "f":
            vsip_vrandu_f(self.vsip!,view.vsip!)
        case "d":
            vsip_vrandu_d(self.vsip!,view.vsip!)
        case "cf":
            vsip_cvrandu_f(self.vsip!,view.vsip!)
        case "cd":
            vsip_cvrandu_d(self.vsip!,view.vsip!)
        default:
            assert(true,"Should not get to default in randu switch statement")
        }
        return view
    }
    public func randu(_ view: Matrix) -> Matrix{
        let definedTypes: Set = ["f","d","cf","cd"]
        let t = view.type.rawValue
        assert(definedTypes.contains(t), "Random only defined for real or complex float values")
        switch t{
        case "f":
            vsip_mrandu_f(self.vsip!,view.vsip!)
        case "d":
            vsip_mrandu_d(self.vsip!,view.vsip!)
        case "cf":
            vsip_cmrandu_f(self.vsip!,view.vsip!)
        case "cd":
            vsip_cmrandu_d(self.vsip!,view.vsip!)
        default:
            assert(true,"Should not get to default in randu switch statement")
        }
        return view
    }
    public func randn(_ view: Vector) -> Vector {
        let definedTypes: Set = ["f","d","cf","cd"]
        let t = view.type.rawValue
        assert(definedTypes.contains(t), "Random only defined for real or complex float values")
        switch t{
        case "f":
            vsip_vrandn_f(self.vsip!,view.vsip!)
        case "d":
            vsip_vrandn_d(self.vsip!,view.vsip!)
        case "cf":
            vsip_cvrandn_f(self.vsip!,view.vsip!)
        case "cd":
            vsip_cvrandn_d(self.vsip!,view.vsip!)
        default:
            assert(true,"Should not get to default in randu switch statement")
        }
        return view
    }
    public func randn(_ view: Matrix) -> Matrix {
        let definedTypes: Set = ["f","d","cf","cd"]
        let t = view.type.rawValue
        assert(definedTypes.contains(t), "Random only defined for real or complex float values")
        switch t{
        case "f":
            vsip_mrandn_f(self.vsip!,view.vsip!)
        case "d":
            vsip_mrandn_d(self.vsip!,view.vsip!)
        case "cf":
            vsip_cmrandn_f(self.vsip!,view.vsip!)
        case "cd":
            vsip_cmrandn_d(self.vsip!,view.vsip!)
        default:
            assert(true,"Should not get to default in randu switch statement")
        }
        return view
    }
    deinit{
        let id = self.myId?.int32Value
        vsip_randdestroy(self.vsip!)
        if _isDebugAssertConfiguration(){
            print("randdestroy id \(id!)")
        }
    }
    
}
