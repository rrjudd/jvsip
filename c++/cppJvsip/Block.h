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
        block(string t, Scalar l){
            obj.p=t;
            obj.t="block";
            void **b = obj.getObjPtr();
            if     (t== "f"){ create((vsip_block_f**)b,l.length());}
            else if(t== "d"){ create((vsip_block_d**)b,l.length());}
            else if(t== "cf"){ create((vsip_cblock_f**)b,l.length());}
            else if(t== "cd"){ create((vsip_cblock_d**)b,l.length());}
            else if(t== "i"){ create((vsip_block_i**)b,l.length());}
            else if(t== "vi"){ create((vsip_block_vi**)b,l.length());}
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
}
