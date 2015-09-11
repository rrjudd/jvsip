//
//  gen.h
//  jvsip_pp0
//
//  Created by Randall R Judd on 1/28/15.
//  Copyright (c) 2015 Randall R Judd. All rights reserved.
//

#ifndef jvsip_pp0_gen_h
#define jvsip_pp0_gen_h
#include "support.h"
namespace vsip {
    vsip_vview_vi * fill(vsip_scalar_vi x0, vsip_length l){
        vsip_vview_vi *v;create(&v,l);
        vsip_vfill_vi(x0,v);
        return v;
    }
    vsip_vview_vi * fill(vsip_scalar_vi x0, vsip_vview_vi *v){
        vsip_vfill_vi(x0,v);
        return v;
    }
    vsip_vview_i * fill(vsip_scalar_i x0, vsip_length l){
        vsip_vview_i *v;create(&v,l);
        vsip_vfill_i(x0,v);
        return v;
    }
    vsip_vview_i * fill(vsip_scalar_i x0, vsip_vview_i *v){
        vsip_vfill_i(x0,v);
        return v;
    }
   vsip_vview_f * fill(vsip_scalar_f x0, vsip_length l){
      vsip_vview_f *v;create(&v,l);
      vsip_vfill_f(x0,v);
      return v;
   }
   vsip_vview_f * fill(vsip_scalar_f x0, vsip_vview_f *v){
      vsip_vfill_f(x0,v);
      return v;
   }
   vsip_mview_f * fill(vsip_scalar_f x0, vsip_length cl, vsip_length rl){
      vsip_mview_f *v;create(&v,cl,rl);
      vsip_mfill_f(x0,v);
      return v;
   }
   vsip_mview_f * fill(vsip_scalar_f x0, vsip_mview_f *v){
      vsip_mfill_f(x0,v);
      return v;
   }
    vsip_vview_d * fill(vsip_scalar_d x0, vsip_length l){
        vsip_vview_d *v;create(&v,l);
        vsip_vfill_d(x0,v);
        return v;
    }
    vsip_vview_d * fill(vsip_scalar_d x0, vsip_vview_d *v){
        vsip_vfill_d(x0,v);
        return v;
    }
    vsip_mview_d * fill(vsip_scalar_d x0, vsip_length cl, vsip_length rl){
        vsip_mview_d *v;create(&v,cl,rl);
        vsip_mfill_d(x0,v);
        return v;
    }
    vsip_mview_d * fill(vsip_scalar_d x0, vsip_mview_d *v){
        vsip_mfill_d(x0,v);
        return v;
    }

   vsip_vview_f * ramp(vsip_scalar_f x0, vsip_scalar_f xinc, vsip_length l){
      vsip_vview_f *v;create(&v,l);
      vsip_vramp_f(x0,xinc,v);
      return v;
   }
   vsip_vview_f * ramp(vsip_scalar_f x0, vsip_scalar_f xinc, vsip_vview_f *v){
      vsip_vramp_f(x0,xinc,v);
      return v;
   }
   vsip_cvview_f *ramp(vsip_scalar_f x0, vsip_scalar_f xinc, vsip_cvview_f *cv){
      vsip_vview_f *v;
      fill((float)0.0,imagview(&v, cv));
      return cv;
   }
    vsip_vview_d * ramp(vsip_scalar_d x0, vsip_scalar_d xinc, vsip_length l){
        vsip_vview_d *v;create(&v,l);
        vsip_vramp_d(x0,xinc,v);
        return v;
    }
    vsip_vview_d * ramp(vsip_scalar_d x0, vsip_scalar_d xinc, vsip_vview_d *v){
        vsip_vramp_d(x0,xinc,v);
        return v;
    }
    vsip_cvview_d *ramp(vsip_scalar_d x0, vsip_scalar_d xinc, vsip_cvview_d *cv){
        vsip_vview_d *v;
        fill((float)0.0,imagview(&v, cv));
        return cv;
    }
    vsip_vview_i * ramp(vsip_scalar_i x0, vsip_scalar_i xinc, vsip_length l){
        vsip_vview_i *v;create(&v,l);
        vsip_vramp_i(x0,xinc,v);
        return v;
    }
    vsip_vview_vi * ramp(vsip_scalar_vi x0, vsip_scalar_vi xinc, vsip_length l){
        vsip_vview_vi *v;create(&v,l);
        vsip_vramp_vi(x0,xinc,v);
        return v;
    }
    vsip_vview_i * ramp(vsip_scalar_i x0, vsip_scalar_i xinc, vsip_vview_i *v){
        vsip_vramp_i(x0,xinc,v);
        return v;
    }
    vsip_vview_vi * ramp(vsip_scalar_vi x0, vsip_scalar_vi xinc, vsip_vview_vi *v){
        vsip_vramp_vi(x0,xinc,v);
        return v;
    }


}
#endif
   
