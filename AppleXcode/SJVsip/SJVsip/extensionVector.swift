//
//  extensionVector.swift
//  SJVsip
//
//  Created by Randall R. Judd on 11/4/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import vsip
extension Vector {
    public static func + (left: Vector, right: Vector) -> Vector {
        let retval = left.empty
        add(left, right, resultsIn: retval)
        return retval
    }
    public static func - (left: Vector, right: Vector) -> Vector {
        let retval = left.empty
        sub(left, subtract: right, resultsIn: retval)
        return retval
    }
    public func randn(_ seed: vsip_index, portable: Bool) -> Vector {
        let state = Rand(seed: seed, portable: portable)
        state.randn(self)
        return self
    }
    public func randn(_ seed: vsip_index) -> Vector {
        return self.randn(seed, portable: true)
    }
    public func randu(_ seed: vsip_index, portable: Bool) -> Vector{
        let state = Rand(seed: seed, portable: portable)
        state.randu(self)
        return self
    }
    public func randu(_ seed: vsip_index) -> Vector {
        return self.randu(seed, portable: true)
    }
    public var normFro: Double {
        get {
            return (SJvsip.normFro(view: self).reald)
        }
    }
}
