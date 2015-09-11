#ifndef __cppJvsip__Block__
#define __cppJvsip__Block__

#include<cstring>
#include<iostream>
#include"gen.h"
#include"elementary.h"
#include"scalar.h"
namespace jvsip{
    using namespace vsip;
    class Block{
        friend class View;
        void *obj; // Vsip object Pointer. Must be Cast on use.
        string d;  // depth "r" or "c" or "mi"
        string p;  // precision string "f", "d", "i", "vi", "l"
        string s;  // shape, for Block is "block";
        string t;  // type is depth and precision as in "f", "cf", "d", "mi", "cd"
        vsip_length n;
        int count;
    public:
        Block(string t, Scalar l);
        Block(const Block & blk) : d(blk.d), p(blk.p), s(blk.s), t(blk.t),n(blk.n),obj(blk.obj){
            count ++;
        }
        ~Block();
        void* vsip() const {return obj;}
        string shape() const {return s;}
        string precision() const {return p;}
        string depth() const {return d;}
        string type() const {return t;}
        Scalar length() const {return Scalar(n);}
    };
}
#endif /* defined(__cppJvsip__Block_) */
