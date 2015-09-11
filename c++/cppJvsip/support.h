//
//  support.h
//  jvsip_pp0
//
//  Created by Randall R Judd on 1/28/15.
//  Copyright (c) 2015 Randall R Judd. All rights reserved.
//

#ifndef jvsip_pp0_support_h
#define jvsip_pp0_support_h
#include <cstring>
extern "C"{
#include<vsip.h>
}
#include <iostream>
#include <cassert>
namespace vsip {
    using std::endl;
    using std::cout;
    using std::string;
    //block
    void create(vsip_block_f**b,vsip_length l){
        *b=vsip_blockcreate_f(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_cblock_f**b,vsip_length l){
        *b=vsip_cblockcreate_f(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_block_i**b,vsip_length l){
        *b=vsip_blockcreate_i(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_block_vi**b,vsip_length l){
        *b=vsip_blockcreate_vi(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_block_mi**b,vsip_length l){
        *b=vsip_blockcreate_mi(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_block_d**b,vsip_length l){
        *b=vsip_blockcreate_d(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_cblock_d**b,vsip_length l){
        *b=vsip_cblockcreate_d(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_block_si**b,vsip_length l){
        *b=vsip_blockcreate_si(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    void create(vsip_block_uc**b,vsip_length l){
        *b=vsip_blockcreate_uc(l,VSIP_MEM_NONE);
        assert(b != NULL);
    }
    // views
    // f
    void create(vsip_vview_f**v,vsip_length l){
        vsip_block_f*b; create(&b,l);
        *v=vsip_vbind_f(b,0,1,l);
        assert(v != NULL);
    }
    vsip_vview_f* create(vsip_block_f*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_vview_f *v=vsip_vbind_f(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_mview_f**m,vsip_length cl,vsip_length rl){
        vsip_block_f*b; create(&b,cl*rl);
        *m=vsip_mbind_f(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_mview_f* create(vsip_block_f*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_mview_f*m=vsip_mbind_f(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    // cf
    void create(vsip_cvview_f**v,vsip_length l){
        vsip_cblock_f*b; create(&b,l);
        *v=vsip_cvbind_f(b,0,1,l);
        assert(v != NULL);
    }
    vsip_cvview_f* create(vsip_cblock_f*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_cvview_f*v=vsip_cvbind_f(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_cmview_f**m,vsip_length cl,vsip_length rl){
        vsip_cblock_f*b; create(&b,cl*rl);
        *m=vsip_cmbind_f(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_cmview_f* create(vsip_cblock_f*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_cmview_f*m=vsip_cmbind_f(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    // d
    void create(vsip_vview_d**v,vsip_length l){
        vsip_block_d*b; create(&b,l);
        *v=vsip_vbind_d(b,0,1,l);
        assert(v != NULL);
    }
    vsip_vview_d* create(vsip_block_d*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_vview_d *v=vsip_vbind_d(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_mview_d**m,vsip_length cl,vsip_length rl){
        vsip_block_d*b; create(&b,cl*rl);
        *m=vsip_mbind_d(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_mview_d* create(vsip_block_d*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_mview_d*m=vsip_mbind_d(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    // cd
    void create(vsip_cvview_d**v,vsip_length l){
        vsip_cblock_d*b; create(&b,l);
        *v=vsip_cvbind_d(b,0,1,l);
        assert(v != NULL);
    }
    vsip_cvview_d* create(vsip_cblock_d*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_cvview_d*v=vsip_cvbind_d(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_cmview_d**m,vsip_length cl,vsip_length rl){
        vsip_cblock_d*b; create(&b,cl*rl);
        *m=vsip_cmbind_d(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_cmview_d* create(vsip_cblock_d*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_cmview_d*m=vsip_cmbind_d(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    // i
    void create(vsip_vview_i**v,vsip_length l){
        vsip_block_i*b; create(&b,l);
        *v=vsip_vbind_i(b,0,1,l);
        assert(v != NULL);
    }
    vsip_vview_i* create(vsip_block_i*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_vview_i *v=vsip_vbind_i(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_mview_i**m,vsip_length cl,vsip_length rl){
        vsip_block_i*b; create(&b,cl*rl);
        *m=vsip_mbind_i(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_mview_i* create(vsip_block_i*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_mview_i*m=vsip_mbind_i(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    // si
    void create(vsip_vview_si**v,vsip_length l){
        vsip_block_si*b; create(&b,l);
        *v=vsip_vbind_si(b,0,1,l);
        assert(v != NULL);
    }
    vsip_vview_si* create(vsip_block_si*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_vview_si *v=vsip_vbind_si(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_mview_si**m,vsip_length cl,vsip_length rl){
        vsip_block_si*b; create(&b,cl*rl);
        *m=vsip_mbind_si(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_mview_si* create(vsip_block_si*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_mview_si*m=vsip_mbind_si(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    //uc
    void create(vsip_vview_uc**v,vsip_length l){
        vsip_block_uc*b; create(&b,l);
        *v=vsip_vbind_uc(b,0,1,l);
        assert(v != NULL);
    }
    vsip_vview_uc* create(vsip_block_uc*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_vview_uc *v=vsip_vbind_uc(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    void create(vsip_mview_uc**m,vsip_length cl,vsip_length rl){
        vsip_block_uc*b; create(&b,cl*rl);
        *m=vsip_mbind_uc(b,0,rl,cl,1,rl);
        assert(m != NULL);
    }
    vsip_mview_uc* create(vsip_block_uc*b, vsip_offset o, vsip_stride cs, vsip_length cl,vsip_stride rs, vsip_length rl){
        vsip_mview_uc*m=vsip_mbind_uc(b,o,cs,cl,rs,rl);
        assert(m != NULL);
        return m;
    }
    //vi
    void create(vsip_vview_vi**v,vsip_length l){
        vsip_block_vi*b; create(&b,l);
        *v=vsip_vbind_vi(b,0,1,l);
        assert(v != NULL);
    }
    vsip_vview_vi* create(vsip_block_vi*b, vsip_offset o, vsip_stride s, vsip_length l){
        vsip_vview_vi *v=vsip_vbind_vi(b,o,s,l);
        assert(v != NULL);
        return v;
    }
    //fft_f
    void create(string typ, vsip_fft_f** fftObj){
        if(typ=="cc"){
            
        }else if(typ=="cr"){
            
        }else if(typ=="rc"){
            
        }
        
    }
    //rand

    //block destroy
    void destroy(vsip_block_f* b){vsip_blockdestroy_f(b);b=nullptr;}
    void destroy(vsip_cblock_f* b){vsip_cblockdestroy_f(b);b=nullptr;}
    void destroy(vsip_block_d* b){vsip_blockdestroy_d(b);b=nullptr;}
    void destroy(vsip_cblock_d* b){vsip_cblockdestroy_d(b);b=nullptr;}
    void destroy(vsip_block_i* b){vsip_blockdestroy_i(b);b=nullptr;}
    void destroy(vsip_block_vi* b){vsip_blockdestroy_vi(b);b=nullptr;}
    void destroy(vsip_block_mi* b){vsip_blockdestroy_mi(b);b=nullptr;}
    void destroy(vsip_block_si* b){vsip_blockdestroy_si(b);b=nullptr;}
    void destroy(vsip_block_uc* b){vsip_blockdestroy_uc(b);b=nullptr;}
 
    void destroy(vsip_block_f** b,vsip_vview_f*v){*b=vsip_vdestroy_f(v);v=nullptr;}
    void destroy(vsip_vview_f*v)                 {vsip_vdestroy_f(v);v=nullptr;}
    void destroy(vsip_block_f** b,vsip_mview_f*v){*b=vsip_mdestroy_f(v);v=nullptr;}
    void destroy(vsip_mview_f*v)                 {vsip_mdestroy_f(v);v=nullptr;}
    void destroy(vsip_cblock_f** b,vsip_cvview_f*v){*b=vsip_cvdestroy_f(v);v=nullptr;}
    void destroy(vsip_cvview_f*v)                 {vsip_cvdestroy_f(v);v=nullptr;}
    void destroy(vsip_cblock_f** b,vsip_cmview_f*v){*b=vsip_cmdestroy_f(v);v=nullptr;}
    void destroy(vsip_cmview_f*v)                 {vsip_cmdestroy_f(v);v=nullptr;}
    
    void destroy(vsip_block_d** b,vsip_vview_d*v){*b=vsip_vdestroy_d(v);v=nullptr;}
    void destroy(vsip_vview_d*v)                 {vsip_vdestroy_d(v);v=nullptr;}
    void destroy(vsip_block_d** b,vsip_mview_d*v){*b=vsip_mdestroy_d(v);v=nullptr;}
    void destroy(vsip_mview_d*v)                 {vsip_mdestroy_d(v);v=nullptr;}
    void destroy(vsip_cblock_d** b,vsip_cvview_d*v){*b=vsip_cvdestroy_d(v);v=nullptr;}
    void destroy(vsip_cvview_d*v)                 {vsip_cvdestroy_d(v);v=nullptr;}
    void destroy(vsip_cblock_d** b,vsip_cmview_d*v){*b=vsip_cmdestroy_d(v);v=nullptr;}
    void destroy(vsip_cmview_d*v)                 {vsip_cmdestroy_d(v);v=nullptr;}

    void destroy(vsip_block_i** b, vsip_vview_i *v){*b = vsip_vdestroy_i(v);v=nullptr;}
    void destroy(vsip_block_vi** b, vsip_vview_vi *v){*b = vsip_vdestroy_vi(v);v=nullptr;}
    void destroy(vsip_block_si** b, vsip_vview_si *v){*b = vsip_vdestroy_si(v);v=nullptr;}
    void destroy(vsip_block_uc** b, vsip_vview_uc *v){*b = vsip_vdestroy_uc(v);v=nullptr;}
    void destroy(vsip_vview_i *v){vsip_vdestroy_i(v);v=nullptr;}
    void destroy(vsip_vview_vi *v){vsip_vdestroy_vi(v);v=nullptr;}
    void destroy(vsip_vview_si *v){vsip_vdestroy_si(v);v=nullptr;}
    void destroy(vsip_mview_uc *v){vsip_mdestroy_uc(v);v=nullptr;}
    void destroy(vsip_mview_i *v){vsip_mdestroy_i(v);v=nullptr;}
    void destroy(vsip_mview_si *v){vsip_mdestroy_si(v);v=nullptr;}

    vsip_vview_f * realview(vsip_vview_f **rv,vsip_cvview_f*cv){
        *rv = vsip_vrealview_f(cv);
        return *rv;
    }
    vsip_vview_f *realview(vsip_cvview_f *cv){
        return vsip_vrealview_f(cv);
    }
    vsip_vview_f * imagview(vsip_vview_f **rv,vsip_cvview_f*cv){
        *rv = vsip_vimagview_f(cv);
        return *rv;
    }
    vsip_vview_f *imagview(vsip_cvview_f *cv){
        return vsip_vimagview_f(cv);
    }
    
    vsip_vview_d * realview(vsip_vview_d **rv,vsip_cvview_d*cv){
        *rv = vsip_vrealview_d(cv);
        return *rv;
    }
    vsip_vview_d *realview(vsip_cvview_d *cv){
        return vsip_vrealview_d(cv);
    }
    vsip_vview_d * imagview(vsip_vview_d **rv,vsip_cvview_d*cv){
        *rv = vsip_vimagview_d(cv);
        return *rv;
    }
    vsip_vview_d *imagview(vsip_cvview_d *cv){
        return vsip_vimagview_d(cv);
    }
    
    float get(vsip_vview_f *v,vsip_index i){
        return (float) vsip_vget_f(v,i);
    }
    float get(vsip_mview_f *v,vsip_index r, vsip_index c){
        return (float)vsip_mget_f(v,r,c);
    }
    vsip_cscalar_f get(vsip_cvview_f *v,vsip_index i){
        vsip_cscalar_f ans = vsip_cvget_f(v,i);
        return ans;
    }
    vsip_cscalar_f get(vsip_cmview_f *v,vsip_index r, vsip_index c){
        vsip_cscalar_f ans = vsip_cmget_f(v,r,c);
        return ans;
    }
    
    int get(vsip_vview_i *v,vsip_index i){
        return (int) vsip_vget_i(v,i);
    }
    int get(vsip_mview_i *v,vsip_index r, vsip_index c){
        return (int)vsip_mget_i(v,r,c);
    }
    short get(vsip_vview_si *v,vsip_index i){
        vsip_scalar_si ans = vsip_vget_si(v,i);
        return ans;
    }
    short get(vsip_mview_si *v,vsip_index r, vsip_index c){
        return (short)vsip_mget_si(v,r,c);
    }
    vsip_index get(vsip_vview_vi *v,vsip_index i){
        vsip_index ans = vsip_vget_vi(v,i);
        return ans;
    }


    float get(vsip_vview_d *v,vsip_index i){
        return (float) vsip_vget_d(v,i);
    }
    float get(vsip_mview_d *v,vsip_index r, vsip_index c){
        return (float)vsip_mget_d(v,r,c);
    }
    vsip_cscalar_d get(vsip_cvview_d *v,vsip_index i){
        vsip_cscalar_d ans = vsip_cvget_d(v,i);
        return ans;
    }
    vsip_cscalar_d get(vsip_cmview_d *v,vsip_index r, vsip_index c){
        vsip_cscalar_d ans = vsip_cmget_d(v,r,c);
        return ans;
    }
    
    // size()
    vsip_length vlength(vsip_vview_i*v){return vsip_vgetlength_i(v);}
    vsip_length vlength(vsip_vview_si*v){return vsip_vgetlength_si(v);}
    vsip_length vlength(vsip_vview_vi*v){return vsip_vgetlength_vi(v);}
    vsip_length vlength(vsip_vview_f*v){return vsip_vgetlength_f(v);}
    vsip_length rlength(vsip_mview_f*v){return vsip_mgetrowlength_f(v);}
    vsip_length clength(vsip_mview_f*v){return vsip_mgetcollength_f(v);}
    vsip_length vlength(vsip_cvview_f*v){return vsip_cvgetlength_f(v);}
    vsip_length rlength(vsip_cmview_f*v){return vsip_cmgetrowlength_f(v);}
    vsip_length clength(vsip_cmview_f*v){return vsip_cmgetcollength_f(v);}
    vsip_length vlength(vsip_vview_d*v){return vsip_vgetlength_d(v);}
    vsip_length rlength(vsip_mview_d*v){return vsip_mgetrowlength_d(v);}
    vsip_length clength(vsip_mview_d*v){return vsip_mgetcollength_d(v);}
    vsip_length vlength(vsip_cvview_d*v){return vsip_cvgetlength_d(v);}
    vsip_length rlength(vsip_cmview_d*v){return vsip_cmgetrowlength_d(v);}
    vsip_length clength(vsip_cmview_d*v){return vsip_cmgetcollength_d(v);}
    vsip_length rlength(vsip_mview_i*v){return vsip_mgetrowlength_i(v);}
    vsip_length rlength(vsip_mview_si*v){return vsip_mgetrowlength_si(v);}
    vsip_length clength(vsip_mview_i*v){return vsip_mgetcollength_i(v);}
    vsip_length clength(vsip_mview_si*v){return vsip_mgetcollength_si(v);}

    void mprint(vsip_vview_vi* v){
        for(vsip_length i=0; i<vlength(v); i++) cout<<get(v,i)<<";\n";
    }
    void mprint(vsip_vview_i* v){
        for(vsip_length i=0; i<vlength(v); i++) cout<<get(v,i)<<";\n";
    }
    void mprint(vsip_vview_f* v){
        for(vsip_length i=0; i<vlength(v); i++) cout<<get(v,i)<<";\n";
    }
    void mprint(vsip_cvview_f* v){
        for(vsip_length i=0; i<vlength(v); i++){
            vsip_cscalar_f ans=get(v,i);
            cout << "(" << ans.r << ", " << ans.i << ");\n";
        }
    }
    void mprint(vsip_mview_f* v){
        for(vsip_length i=0; i<rlength(v); i++){
            for(vsip_length j=0; j<clength(v); j++){
                cout << get(v,i,j)<<"; ";
            }
            cout << endl;
        }
    }
    void mprint(vsip_cmview_f* v){
        for(vsip_length i=0; i<rlength(v); i++){
            for(vsip_length j=0; j<clength(v); j++){
                vsip_cscalar_f ans=get(v,i,j);
                cout << "(" << ans.r << ", " << ans.i << "); ";
            }
            cout << endl;
        }
    }
    void mprint(vsip_vview_d* v){
        for(vsip_length i=0; i<vlength(v); i++) cout<<get(v,i)<<";\n";
    }
    void mprint(vsip_cvview_d* v){
        for(vsip_length i=0; i<vlength(v); i++){
            vsip_cscalar_d ans=get(v,i);
            cout << "(" << ans.r << ", " << ans.i << ");\n";
        }
    }
    void mprint(vsip_mview_d* v){
        vsip_length rl=rlength(v),cl=clength(v);
        for(vsip_length i=0; i<rl; i++){
            for(vsip_length j=0; j<cl; j++){
                cout << get(v,i,j)<<"; ";
            }
            cout << endl;
        }
    }
    void mprint(vsip_cmview_d* v){
        vsip_length rl=rlength(v),cl=clength(v);
        for(vsip_length i=0; i<rl; i++){
            if(i==0) cout << "[";
            for(vsip_length j=0; j<cl; j++){
                vsip_cscalar_d ans=get(v,i,j);
                cout << "(" << ans.r << ", " << ans.i << "); ";
            }
            if(i==rl) cout << "]";
            cout << endl;
        }
    }
}

#endif
