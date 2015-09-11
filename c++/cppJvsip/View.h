//
//  View.h
//  cppJvsip
//
//  Created by RANDALL JUDD on 4/27/15.
//  Copyright (c) 2015 RANDALL JUDD. All rights reserved.
//
#include <iostream>
#include <cstring>
#include "Block.h"
#ifndef __cppJvsip__View__
#define __cppJvsip__View__


namespace jvsip{
    class View{
        string s;  //shape
        Block *obj;
        void *vsipView;
        int count;
        View ramp(vsip_scalar_f s, vsip_scalar_f inc){
            string typ=precision();
            if(typ=="f")
                vsip::ramp(s, inc, (vsip_vview_f*)this->vsip());
            else if(typ== "d")
                ramp((vsip_scalar_d) s, (vsip_scalar_d) inc);
            else if(typ=="i")
                ramp((vsip_scalar_i) s, (vsip_scalar_i) inc);
            else if(typ=="vi")
                ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
        View ramp(vsip_scalar_d s, vsip_scalar_d inc){
            string typ=precision();
            if(typ=="d")
                vsip::ramp(s, inc, (vsip_vview_d*)this->vsip());
            else if(typ== "f")
                ramp((vsip_scalar_f) s, (vsip_scalar_f) inc);
            else if(typ=="i")
                ramp((vsip_scalar_i) s, (vsip_scalar_i) inc);
            else if(typ=="vi")
                ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
        View ramp(vsip_scalar_i s, vsip_scalar_i inc){
            string typ=precision();
            if(typ=="i")
                vsip::ramp(s, inc, (vsip_vview_i*)this->vsip());
            else if(typ== "d")
                ramp((vsip_scalar_d) s, (vsip_scalar_d) inc);
            else if(typ=="f")
                ramp((vsip_scalar_f) s, (vsip_scalar_f) inc);
            else if(typ=="vi")
                ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
        View ramp(vsip_scalar_vi s, vsip_scalar_vi inc){
            string typ=precision();
            if(typ=="f")
                vsip::ramp(s, inc, (vsip_vview_f*)this->vsip());
            else if(typ== "d")
                ramp((vsip_scalar_d) s, (vsip_scalar_d) inc);
            else if(typ=="i")
                ramp((vsip_scalar_i) s, (vsip_scalar_i) inc);
            else if(typ=="vi")
                ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }

    public:
        //constructors
        View(Block blk,Scalar o, Scalar s, Scalar l) : s("vector") , count(0){
            obj=&blk;
            std::string t=blk.type();
            if(t== "f") {vsipView=(void*)vsip::create((vsip_block_f*)obj->vsip(),o.offset(),s.stride(),l.length());}
            else if (t== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),o.offset(),s.stride(),l.length());}
            else if (t== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),o.offset(),s.stride(),l.length());}
            else if (t== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),o.offset(),s.stride(),l.length());}
            else if (t== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),o.offset(),s.stride(),l.length());}
            else if (t== "vi"){ vsipView=(void*)vsip::create((vsip_block_vi*)obj->vsip(),o.offset(),s.stride(),l.length());}
            else{std::cout << "View precision case not found" << std::endl;exit(-1);}
        }
        View(Block blk,Scalar o, Scalar cs, Scalar cl, Scalar rs, Scalar rl) : s("matrix") , count(0){
            obj=&blk;
            std::string t=blk.type();
            if      (t== "f") {
                vsipView=(void*)vsip::create((vsip_block_f*)obj->vsip(),o.offset(),cs.stride(),cl.length(),rs.stride(),rl.length());
            } else if (t== "d") {
                vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),o.offset(),cs.stride(),cl.length(),rs.stride(),rl.length());
            } else if (t== "cf"){
                vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),o.offset(),cs.stride(),cl.length(),rs.stride(),rl.length());
            } else if (t== "cd"){
                vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),o.offset(),cs.stride(),cl.length(),rs.stride(),rl.length());
            } else if (t== "i") {
                vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),o.offset(),cs.stride(),cl.length(),rs.stride(),rl.length());
            }else{std::cout << "View precision case not found" << std::endl;exit(-1);}
        }
        //copy constructor
        View(const View& other) : s(other.s), obj(other.obj){
            count++;
            vsipView=(other.vsipView);
        }
        ~View(){
            string p=obj->p;
            if(count == 0){
                if(s=="vector"){
                    if     (p=="f"){destroy((vsip_vview_f*)vsipView); std::cout << "delete view f" << std::endl;}
                    else if(p=="d"){destroy((vsip_vview_d*)vsipView); std::cout << "delete view d" << std::endl;}
                    else if(p=="cf"){destroy((vsip_cvview_f*)vsipView); std::cout << "delete view cf" << std::endl;}
                    else if(p=="cd"){destroy((vsip_cvview_d*)vsipView); std::cout << "delete view cd" << std::endl;}
                    else if(p=="i") {destroy((vsip_vview_i*)vsipView); std::cout << "delete view i" << std::endl;}
                    else if(p=="vi"){destroy((vsip_vview_d*)vsipView); std::cout << "delete view vi" << std::endl;}
                    else exit(-1);
                } else { // must be matrix
                    if(p=="f"){destroy((vsip_mview_f*)vsipView); std::cout << "delete view f" << std::endl;}
                    else if(p=="d"){destroy((vsip_mview_d*)vsipView); std::cout << "delete view d" << std::endl;}
                    else if(p=="cf"){destroy((vsip_cmview_f*)vsipView); std::cout << "delete view cf" << std::endl;}
                    else if(p=="cd"){destroy((vsip_cmview_d*)vsipView); std::cout << "delete view cd" << std::endl;}
                    else if(p=="i"){destroy((vsip_mview_i*)vsipView); std::cout << "delete view i" << std::endl;}
                    else exit(-1);
                }
            }else count--;
        }
        void* vsip() const {return vsipView;}
        string type() const {return obj->t;}
        string precision()const {return obj->precision();}
        string shape() const {return s;}
        View ramp(Scalar s, Scalar inc){
            string typ = precision();
            if(typ=="f")
                return this->ramp(s.scalar_f(), inc.scalar_f());
            else if(typ== "d")
                return ramp(s.scalar_d(), inc.scalar_d());
            else if(typ=="i")
                return ramp(s.scalar_i(), inc.scalar_i());
            else if(typ=="vi")
                return ramp(s.scalar_vi(), inc.scalar_vi());
            else
                return *this;
        }
        Scalar operator[](Scalar i){
            string typ = precision();
            if(typ=="f"){
                return Scalar(vsip_vget_f((vsip_vview_f*)vsip(), i.scalar_vi()));
            } else if(typ== "d"){
                return Scalar(vsip_vget_d((vsip_vview_d*)vsip(), i.scalar_vi()));
            }else if(typ== "cf"){
                return Scalar(vsip_cvget_f((vsip_cvview_f*)vsip(), i.scalar_vi()));
            }else if(typ== "cd"){
                return Scalar(vsip_cvget_d((vsip_cvview_d*)vsip(), i.scalar_vi()));
            }else if(typ=="i"){
                return Scalar(vsip_vget_i((vsip_vview_i*)vsip(), i.scalar_vi()));
            }else if(typ=="vi"){
                return Scalar(vsip_vget_vi((vsip_vview_vi*)vsip(), i.scalar_vi()));
            }else{
                return Scalar(0);
            }
        }
        Scalar offset(){
            string typ = precision();
            string shp = shape();
            if(typ=="f" && shp == "vector"){
                return Scalar(vsip_vgetoffset_f((vsip_vview_f*)vsip()));
            } else if(typ =="f" && shp == "matrix"){
                return Scalar(vsip_mgetoffset_f((vsip_mview_f*)vsip()));
            } else if(typ=="cf"&& shp == "vector"){
                return Scalar(vsip_cvgetoffset_f((vsip_cvview_f*)vsip()));
            } else if(typ=="cd"&& shp == "vector"){
                return Scalar(vsip_cvgetoffset_d((vsip_cvview_d*)vsip()));
            } else if(typ== "d"&& shp == "vector"){
                return Scalar(vsip_vgetoffset_d((vsip_vview_d*)vsip()));
            } else if(typ=="i"&& shp == "vector"){
                return Scalar(vsip_vgetoffset_i((vsip_vview_i*)vsip()));
            } else if(typ=="vi"&& shp == "vector"){
                return Scalar(vsip_vgetoffset_vi((vsip_vview_vi*)vsip()));
            } else{
                return Scalar(0);
            }
        }
        void offset(Scalar o){
            string typ = precision();
            string shp = shape();
            if(typ=="f" && shp == "vector"){
                vsip_vputoffset_f((vsip_vview_f*)vsip(),o.offset());
            } else if(typ =="f" && shp == "matrix"){
                vsip_mputoffset_f((vsip_mview_f*)vsip(),o.offset());
            } else if(typ=="cf"&& shp == "vector"){
                vsip_cvputoffset_f((vsip_cvview_f*)vsip(),o.offset());
            } else if(typ =="cf" && shp == "matrix"){
                vsip_cmputoffset_f((vsip_cmview_f*)vsip(),o.offset());
            } else if(typ=="cd"&& shp == "vector"){
                vsip_cvputoffset_d((vsip_cvview_d*)vsip(),o.offset());
            } else if(typ== "d"&& shp == "vector"){
                vsip_vputoffset_d((vsip_vview_d*)vsip(),o.offset());
            } else if(typ=="i"&& shp == "vector"){
                vsip_vputoffset_i((vsip_vview_i*)vsip(),o.offset());
            } else if(typ=="vi"&& shp == "vector"){
                vsip_vputoffset_vi((vsip_vview_vi*)vsip(),o.offset());
            } 
        }
        Scalar length(){
            string typ = precision();
            if(typ=="f"){
                return Scalar(vsip_vgetlength_f((vsip_vview_f*)vsip()));
            } else if(typ=="cf"){
                return Scalar(vsip_cvgetlength_f((vsip_cvview_f*)vsip()));
            }else if(typ=="cd"){
                return Scalar(vsip_cvgetlength_d((vsip_cvview_d*)vsip()));
            } else if(typ== "d"){
                return Scalar(vsip_vgetlength_d((vsip_vview_d*)vsip()));
            }else if(typ=="i"){
                return Scalar(vsip_vgetlength_i((vsip_vview_i*)vsip()));
            }else if(typ=="vi"){
                return Scalar(vsip_vgetlength_vi((vsip_vview_vi*)vsip()));
            }else{
                return Scalar(0);
            }
        }
        void length(Scalar l){
            string typ = precision();
            if(typ=="f"){
                vsip_vputlength_f((vsip_vview_f*)vsip(),l.length());
            } else if(typ=="cf"){
                vsip_cvputlength_f((vsip_cvview_f*)vsip(),l.length());
            }else if(typ=="cd"){
                vsip_cvputlength_d((vsip_cvview_d*)vsip(),l.length());
            } else if(typ== "d"){
                vsip_vputlength_d((vsip_vview_d*)vsip(),l.length());
            }else if(typ=="i"){
                vsip_vputlength_i((vsip_vview_i*)vsip(),l.length());
            }else if(typ=="vi"){
                vsip_vputlength_vi((vsip_vview_vi*)vsip(),l.length());
            }
        }
        Scalar stride(){
            string typ = precision();
            if(typ=="f"){
                return Scalar(vsip_vgetstride_f((vsip_vview_f*)vsip()));
            } else if(typ=="cf"){
                return Scalar(vsip_cvgetstride_f((vsip_cvview_f*)vsip()));
            }else if(typ=="cd"){
                return Scalar(vsip_cvgetstride_d((vsip_cvview_d*)vsip()));
            } else if(typ== "d"){
                return Scalar(vsip_vgetstride_d((vsip_vview_d*)vsip()));
            }else if(typ=="i"){
                return Scalar(vsip_vgetstride_i((vsip_vview_i*)vsip()));
            }else if(typ=="vi"){
                return Scalar(vsip_vgetstride_vi((vsip_vview_vi*)vsip()));
            }else{
                return Scalar(0);
            }
        }
        void stride(Scalar l){
            string typ = precision();
            if(typ=="f"){
                vsip_vputstride_f((vsip_vview_f*)vsip(),l.stride());
            } else if(typ=="cf"){
                vsip_cvputstride_f((vsip_cvview_f*)vsip(),l.stride());
            }else if(typ=="cd"){
                vsip_cvputstride_d((vsip_cvview_d*)vsip(),l.stride());
            } else if(typ== "d"){
                vsip_vputstride_d((vsip_vview_d*)vsip(),l.stride());
            }else if(typ=="i"){
                vsip_vputstride_i((vsip_vview_i*)vsip(),l.stride());
            }else if(typ=="vi"){
                vsip_vputstride_vi((vsip_vview_vi*)vsip(),l.stride());
            }
        }

        View fill(Scalar s){
            string typ = precision();
            if(typ=="f"){
                vsip_vfill_f(s.scalar_f(),(vsip_vview_f*)vsip());
            } else if(typ== "d"){
                vsip::fill(s.scalar_d(),(vsip_vview_d*)vsip());
            } else if(typ=="i"){
                vsip::fill(s.scalar_i(),(vsip_vview_i*)vsip());
            }else if(typ=="vi"){
                vsip::fill(s.scalar_vi(),(vsip_vview_vi*)vsip());
            }
            return *this;
        }
    };
}

#endif /* defined(__cppJvsip__View__) */
