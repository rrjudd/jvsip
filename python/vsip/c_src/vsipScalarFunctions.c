#include"vsipScalarFunctions.h"

vsip_scalar_d vsip_acos_d(vsip_scalar_d a){
    return (vsip_scalar_d) acos(a);
}
vsip_scalar_f vsip_acos_f(vsip_scalar_f a){
    return (vsip_scalar_f) acos(a);
}
vsip_scalar_d vsip_asin_d(vsip_scalar_d a){
    return (vsip_scalar_d) asin(a);
}
vsip_scalar_f vsip_asin_f(vsip_scalar_f a){
    return (vsip_scalar_f) asin(a);
}
vsip_scalar_d vsip_atan_d(vsip_scalar_d a){
    return (vsip_scalar_d) atan(a);
}
vsip_scalar_f vsip_atan_f(vsip_scalar_f a){
    return (vsip_scalar_f) atan(a);
}
vsip_scalar_d vsip_cos_d(vsip_scalar_d a){
    return (vsip_scalar_d)cos(a);
}
vsip_scalar_f vsip_cos_f(vsip_scalar_f a){
    return (vsip_scalar_f)cos(a);
}
vsip_scalar_d vsip_cosh_d(vsip_scalar_d a){
    return (vsip_scalar_d)cosh(a);
}
vsip_scalar_f vsip_cosh_f(vsip_scalar_f a){
    return (vsip_scalar_f)cosh(a);
}
vsip_scalar_d vsip_sin_d(vsip_scalar_d a){
    return (vsip_scalar_d)sin(a);
}
vsip_scalar_f vsip_sin_f(vsip_scalar_f a){
    return (vsip_scalar_f)sin(a);
}
vsip_scalar_d vsip_sinh_d(vsip_scalar_d a){
    return (vsip_scalar_d)sinh(a);
}
vsip_scalar_f vsip_sinh_f(vsip_scalar_f a){
    return (vsip_scalar_f)sinh(a);
}
vsip_scalar_d vsip_ceil_d(vsip_scalar_d a){
    return (vsip_scalar_d)ceil(a);
}
vsip_scalar_f vsip_ceil_f(vsip_scalar_f a){
    return (vsip_scalar_f)ceil(a);
}
vsip_scalar_d vsip_atan2_d(vsip_scalar_d a, vsip_scalar_d b){
    return (vsip_scalar_d) atan2(a,b);
}
vsip_scalar_f vsip_atan2_f(vsip_scalar_f a, vsip_scalar_f b){
    return (vsip_scalar_f) atan2(a,b);
}
vsip_scalar_d vsip_hypot_d(vsip_scalar_d a, vsip_scalar_d b){
   vsip_scalar_d retval = 0.0;
   vsip_scalar_d x=(vsip_scalar_d)fabs(a); 
   vsip_scalar_d y=(vsip_scalar_d)fabs(b);
   if (a == 0.0)
      retval = y;
   else if (b == 0.0)
      retval = x;
   else if (y < x)
      retval = x * (vsip_scalar_d)sqrt(1.0 + (y/x) * (y/x));
   else
      retval = y * (vsip_scalar_d)sqrt(1.0 + (x/y) * (x/y));
   return retval;
}
vsip_scalar_f vsip_hypot_f(vsip_scalar_f a, vsip_scalar_f b){
   vsip_scalar_f retval = 0.0;
   vsip_scalar_f x=(vsip_scalar_f)fabs(a); 
   vsip_scalar_f y=(vsip_scalar_f)fabs(b);
   if (a == 0.0)
      retval = y;
   else if (b == 0.0)
      retval = x;
   else if (y < x)
      retval = x * (vsip_scalar_f)sqrt(1.0 + (y/x) * (y/x));
   else
      retval = y * (vsip_scalar_f)sqrt(1.0 + (x/y) * (x/y));
   return retval;

}
vsip_scalar_d vsip_exp_d(vsip_scalar_d a){
    return (vsip_scalar_d)exp(a);
}
vsip_scalar_f vsip_exp_f(vsip_scalar_f a){
    return (vsip_scalar_f)exp(a);
}
vsip_scalar_d vsip_floor_d(vsip_scalar_d a){
    return (vsip_scalar_d)floor(a);
}
vsip_scalar_f vsip_floor_f(vsip_scalar_f a){
    return (vsip_scalar_f)floor(a);
}
vsip_scalar_d vsip_log_d(vsip_scalar_d a){
    return (vsip_scalar_d)log(a);
}
vsip_scalar_f vsip_log_f(vsip_scalar_f a){
    return (vsip_scalar_f)log(a);
}
vsip_scalar_d vsip_log10_d(vsip_scalar_d a){
    return (vsip_scalar_d)log10(a);
}
vsip_scalar_f vsip_log10_f(vsip_scalar_f a){
    return (vsip_scalar_f)log10(a);
}
vsip_scalar_d vsip_mag_d(vsip_scalar_d a){
    return (vsip_scalar_d)abs(a);
}
vsip_scalar_f vsip_mag_f(vsip_scalar_f a){
    return (vsip_scalar_f)abs(a);
}
vsip_scalar_d vsip_pow_d(vsip_scalar_d x, vsip_scalar_d y){
    return (vsip_scalar_d)pow(x,y);
}
vsip_scalar_f vsip_pow_f(vsip_scalar_f x, vsip_scalar_f y){
    return (vsip_scalar_f)pow(x,y);
}
vsip_scalar_d vsip_sqrt_d(vsip_scalar_d a){
    return (vsip_scalar_d)sqrt(a);
}
vsip_scalar_f vsip_sqrt_f(vsip_scalar_f a){
    return (vsip_scalar_f)sqrt(a);
}
vsip_scalar_d vsip_tan_d(vsip_scalar_d a){
    return (vsip_scalar_d)tan(a);
}
vsip_scalar_f vsip_tan_f(vsip_scalar_f a){
    return (vsip_scalar_f)tan(a);
}
vsip_scalar_d vsip_tanh_d(vsip_scalar_d a){
    return (vsip_scalar_d)tanh(a);
}
vsip_scalar_f vsip_tanh_f(vsip_scalar_f a){
    return (vsip_scalar_f)tanh(a);
}
vsip_scalar_d vsip_exp10_d(vsip_scalar_d x){
    return (vsip_scalar_d)pow(10.0,x);
}
vsip_scalar_f vsip_exp10_f(vsip_scalar_f x){
    return (vsip_scalar_f)pow(10.0,x);
}
vsip_scalar_d vsip_min_d(vsip_scalar_d x,vsip_scalar_d y){ return (vsip_scalar_d) (x<y) ? x:y;}
vsip_scalar_f vsip_min_f(vsip_scalar_f x,vsip_scalar_f y){ return (vsip_scalar_f) (x<y) ? x:y;}
vsip_scalar_d vsip_max_d(vsip_scalar_d x,vsip_scalar_d y){ return (vsip_scalar_d) (x<y) ? y:x;}
vsip_scalar_f vsip_max_f(vsip_scalar_f x,vsip_scalar_f y){ return (vsip_scalar_f) (x<y) ? y:x;}
