#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_svdattributes_f.h>


int vsip_svdmatv_f(
         const vsip_sv_f *obj,
         vsip_scalar_vi low,
         vsip_scalar_vi high,
         const vsip_mview_f *C){
     int retval = 0;
     vsip_mview_f V = *(obj->mV);
     V.row_length = (high - low) + 1;
     V.offset = V.offset + low * V.row_stride;
     vsip_mcopy_f_f(&V,C);
     return retval;
}
