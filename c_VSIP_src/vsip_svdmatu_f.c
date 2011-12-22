#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_svdattributes_f.h>


int vsip_svdmatu_f(
         const vsip_sv_f *obj,
         vsip_scalar_vi low,
         vsip_scalar_vi high,
         const vsip_mview_f *C){
     int retval = 0;
     vsip_mview_f U = *(obj->mU);
     U.row_length = (high - low) + 1;
     U.offset = U.offset + low * U.row_stride;
     vsip_mcopy_f_f(&U,C);
     return retval;
}
