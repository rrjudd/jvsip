//
//  VectorExplorer.swift
//  VectorExplorer
//
//  Created by Randall R. Judd on 1/17/17.
//  Copyright © 2017 JVSIP. All rights reserved.
//

import Foundation
import SwiftVsip

func createBlock(length: Int) -> Vsip.Block {
    return Vsip.Block(length: length, type: .d)
}
