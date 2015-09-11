//
//  Block.cpp
//  cppJvsip
//
//  Created by RANDALL JUDD on 4/28/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//

#include "Block.h"
jvsip::Block::Block(string t, Scalar l) : t(t), s("block"),n(l.length()),count(0) { // t is d+p usually; "mi" for matrix index
    if(t== "f"){
        create((vsip_block_f**)&obj,l.length());
        d="r";
        p="f";
    }
    else if(t== "d"){
        create((vsip_block_d**)&obj,l.length());
        d="r";
        p="d";
    }
    else if(t== "cf"){
        create((vsip_cblock_f**)&obj,l.length());
        d="c";
        p="f";
    }
    else if(t== "cd"){
        create((vsip_cblock_d**)&obj,l.length());
        d="c";
        p="d";
    }
    else if(t== "i"){
        create((vsip_block_i**)&obj,l.length());
        d="r";
        p="i";
    }
    else if(t== "vi"){
        create((vsip_block_vi**)&obj,l.length());
        d="r";
        p="vi";
    }
    else if(t== "mi"){
        create((vsip_block_mi**)&obj,l.length());
        d="mi";
        p="mi";
    }
    else{std::cout << "precision case not found" << std::endl;exit(-1);
    }
}

jvsip::Block:: ~Block(){
    if(count == 0){
        string pcsn=precision();
        if (pcsn=="f"){
            destroy((vsip_block_f*)vsip());
            std::cout<<type() << " block destroyed\n";
        } else if (pcsn=="d"){
            destroy((vsip_block_d*)vsip());
            std::cout<<"block_d destroyed\n";
        }else if (pcsn=="cf"){
            destroy((vsip_cblock_f*)vsip());
            std::cout<<"cblock_f destroyed\n";
        }else if (pcsn=="cd"){
            destroy((vsip_cblock_d*)vsip());
            std::cout<<"cblock_d destroyed\n";
        }else if (pcsn=="i"){
            destroy((vsip_block_i*)vsip());
            std::cout<<"block_d destroyed\n";
        }else if (pcsn=="vi"){
            destroy((vsip_block_vi*)vsip());
            std::cout<<"block_d destroyed\n";
        }else if (pcsn=="mi"){
            destroy((vsip_block_mi*)vsip());
            std::cout<<"block_mi destroyed\n";
        }
    } else count--;
}

