//
//  jvsiph.h
//  jvsip_pp0
//
//  Created by Randall R Judd on 1/30/15.
//  Copyright (c) 2015 Randall R Judd. All rights reserved.
//

#ifndef jvsip_pp0_jvsiph_h
#define jvsip_pp0_jvsiph_h
#include<cstring>
extern "C"{
#include<vsip.h>
}
#include"support.h"
#include"gen.h"
#include"elementary.h"
namespace jvsip{
    using namespace vsip;
    struct vsipObject{
        void *obj;
        string t;//type string
        string p;//precision string
        void** getObjPtr(){
            return &obj;
        }
        void *getObj(){
            return obj;
        }
        string type(){return t;}
        string precision(){return p;}
    };
    
    class jvsipState{
        friend class block;
        static int vsipinit;
        static int count;
    };
    
    class block{
        jvsipState vsipObj;
        vsipObject obj;
    public:
        block(string t, vsip_length l){
            obj.p=t;
            obj.t="block";
            void **b = obj.getObjPtr();
            if     (t== "f"){ create((vsip_block_f**)b,l);}
            else if(t== "d"){ create((vsip_block_d**)b,l);}
            else if(t== "cf"){ create((vsip_cblock_f**)b,l);}
            else if(t== "cd"){ create((vsip_cblock_d**)b,l);}
            else if(t== "i"){ create((vsip_block_i**)b,l);}
            else if(t== "vi"){ create((vsip_block_vi**)b,l);}
            else{std::cout << "precision case not found" << std::endl;exit(-1);}
        }
        
        ~block(){
            if (this->precision()=="f"){
                destroy((vsip_block_f*)this->obj.getObj());
                std::cout<<this->type() << " destroyed\n";
            } else if (this->precision()=="d"){
                destroy((vsip_block_d*)this->vsip());
                std::cout<<"block_d destroyed\n";
            }else if (this->precision()=="cf"){
                destroy((vsip_cblock_f*)this->vsip());
                std::cout<<"cblock_f destroyed\n";
            }else if (this->precision()=="cd"){
                destroy((vsip_cblock_d*)this->vsip());
                std::cout<<"cblock_d destroyed\n";
            }else if (this->precision()=="i"){
                destroy((vsip_block_i*)this->vsip());
                std::cout<<"block_d destroyed\n";
            }else if (this->precision()=="vi"){
                destroy((vsip_block_vi*)this->vsip());
                std::cout<<"block_d destroyed\n";
            }
        }
        void* vsip(){return this->obj.getObj();}
        string type(){return this->obj.type();}
        string precision(){return this->obj.precision();}
    };
    class view{
        string t;
        block *obj;
        bool blkOwner;
        void *vsipView;
    public:
        view(block* blk,int o, int s, int l){
            string typ=blk->precision();
            t="vector";
            blkOwner=false;
            obj=blk;
            if      (typ== "f") {vsipView=(void*)vsip::create((vsip_block_f*)obj->vsip(),(vsip_offset)o,(vsip_stride)s,(vsip_length)l);}
            else if (typ== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),(vsip_offset)o,(vsip_stride)s,(vsip_length)l);}
            else if (typ== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),(vsip_offset)o,(vsip_stride)s,(vsip_length)l);}
            else if (typ== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),(vsip_offset)o,(vsip_stride)s,(vsip_length)l);}
            else if (typ== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),(vsip_offset)o,(vsip_stride)s,(vsip_length)l);}
            else if (typ== "vi"){ vsipView=(void*)vsip::create((vsip_block_vi*)obj->vsip(),(vsip_offset)o,(vsip_stride)s,(vsip_length)l);}
            else{std::cout << "view precision case not found" << std::endl;exit(-1);}           
        }
        view(block* blk,int o, int cs, int cl, int rs, int rl){
            string typ=blk->precision();
            t="matrix";
            blkOwner=false;
            obj=blk;
            if      (typ== "f") {vsipView=(void*)vsip::create((vsip_block_f*)obj->vsip(),(vsip_offset)o,(vsip_stride)cs,(vsip_length)cl,(vsip_stride)rs,(vsip_length)rl);}
            else if (typ== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),(vsip_offset)o,(vsip_stride)cs,(vsip_length)cl,(vsip_stride)rs,(vsip_length)rl);}
            else if (typ== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),(vsip_offset)o,(vsip_stride)cs,(vsip_length)cl,(vsip_stride)rs,(vsip_length)rl);}
            else if (typ== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),(vsip_offset)o,(vsip_stride)cs,(vsip_length)cl,(vsip_stride)rs,(vsip_length)rl);}
            else if (typ== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),(vsip_offset)o,(vsip_stride)cs,(vsip_length)cl,(vsip_stride)rs,(vsip_length)rl);}
            else{std::cout << "view precision case not found" << std::endl;exit(-1);}
        }
        view(block* blk,vsip_offset o, vsip_stride s, vsip_length l){
            string typ=blk->precision();
            t="vector";
            blkOwner=false;
            obj=blk;
            if      (typ== "f") {vsipView=(void*)vsip::create((vsip_block_f*)obj->vsip(),o,s,l);}
            else if (typ== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),o,s,l);}
            else if (typ== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),o,s,l);}
            else if (typ== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),o,s,l);}
            else if (typ== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),o,s,l);}
            else if (typ== "vi"){ vsipView=(void*)vsip::create((vsip_block_vi*)obj->vsip(),o,s,l);}
            else{std::cout << "view precision case not found" << std::endl;exit(-1);}

        }
        view(block* blk,vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
            string typ=blk->precision();
            t="matrix";
            blkOwner=false;
            obj=blk;
            if      (typ== "f") {vsipView=(void*)vsip::create((vsip_block_f*)obj->vsip(),o,cs,cl,rs,rl);}
            else if (typ== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),o,cs,cl,rs,rl);}
            else if (typ== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),o,cs,cl,rs,rl);}
            else if (typ== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),o,cs,cl,rs,rl);}
            else if (typ== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),o,cs,cl,rs,rl);}
            else{std::cout << "view precision case not found" << std::endl;exit(-1);}
        }
        view(string typ, vsip_length l){
            t="vector";
            obj = new block(typ,l);
            blkOwner=true;
            if      (typ== "f") { vsipView=(void*) vsip::create((vsip_block_f*)obj->vsip(),0,1,l);}
            else if (typ== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),0,1,l);}
            else if (typ== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),0,1,l);}
            else if (typ== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),0,1,l);}
            else if (typ== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),0,1,l);}
            else if (typ== "vi"){ vsipView=(void*)vsip::create((vsip_block_vi*)obj->vsip(),0,1,l);}
            else{std::cout << "view precision case not found" << std::endl;exit(-1);}
        }
        view(string typ, vsip_length cl, vsip_length rl){
            t="matrix";
            obj = new block(typ,cl*rl);
            blkOwner=true;
            if      (typ== "f") { vsipView=(void*) vsip::create((vsip_block_f*)obj->vsip(),0,rl,cl,1,rl);}
            else if (typ== "d") { vsipView=(void*)vsip::create((vsip_block_d*)obj->vsip(),0,rl,cl,1,rl);}
            else if (typ== "cf"){ vsipView=(void*)vsip::create((vsip_cblock_f*)obj->vsip(),0,rl,cl,1,rl);}
            else if (typ== "cd"){ vsipView=(void*)vsip::create((vsip_cblock_d*)obj->vsip(),0,rl,cl,1,rl);}
            else if (typ== "i") { vsipView=(void*)vsip::create((vsip_block_i*)obj->vsip(),0,rl,cl,1,rl);}
            else{std::cout << "view precision case not found" << std::endl;exit(-1);}
        }

        ~view(){
            if (t=="vview_f"){destroy((vsip_vview_f*)vsipView); if(blkOwner) delete(obj); std::cout << t << " destroyed\n";}
            else if (t=="vview_d"){destroy((vsip_vview_d*)vsipView);if(blkOwner) delete(obj);std::cout<< t << " destroyed\n";}
        }
        void* vsip(){return vsipView;}
        string type(){return t;}
        string precision(){return obj->precision();}
        void setBlockOwner(bool state){
            this->blkOwner=state;
        }
        view ramp(vsip_scalar_f s, vsip_scalar_f inc){
            string typ=this->obj->precision();
            if(typ=="f")
                vsip::ramp(s, inc, (vsip_vview_f*)this->vsip());
            else if(typ== "d")
                this->ramp((vsip_scalar_d) s, (vsip_scalar_d) inc);
            else if(typ=="i")
                this->ramp((vsip_scalar_i) s, (vsip_scalar_i) inc);
            else if(typ=="vi")
                this->ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
        view ramp(vsip_scalar_d s, vsip_scalar_d inc){
            string typ=this->obj->precision();
            if(typ=="d")
                vsip::ramp(s, inc, (vsip_vview_d*)this->vsip());
            else if(typ== "f")
                this->ramp((vsip_scalar_f) s, (vsip_scalar_f) inc);
            else if(typ=="i")
                this->ramp((vsip_scalar_i) s, (vsip_scalar_i) inc);
            else if(typ=="vi")
                this->ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
        view ramp(vsip_scalar_i s, vsip_scalar_i inc){
            string typ=this->obj->precision();
            if(typ=="i")
                vsip::ramp(s, inc, (vsip_vview_i*)this->vsip());
            else if(typ== "d")
                this->ramp((vsip_scalar_d) s, (vsip_scalar_d) inc);
            else if(typ=="f")
                this->ramp((vsip_scalar_f) s, (vsip_scalar_f) inc);
            else if(typ=="vi")
                this->ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
        view ramp(vsip_scalar_vi s, vsip_scalar_vi inc){
            string typ=this->obj->precision();
            if(typ=="f")
                vsip::ramp(s, inc, (vsip_vview_f*)this->vsip());
            else if(typ== "d")
                this->ramp((vsip_scalar_d) s, (vsip_scalar_d) inc);
            else if(typ=="i")
                this->ramp((vsip_scalar_i) s, (vsip_scalar_i) inc);
            else if(typ=="vi")
                this->ramp((vsip_scalar_vi) s, (vsip_scalar_vi) inc);
            return *this;
        }
    };
}
#endif
