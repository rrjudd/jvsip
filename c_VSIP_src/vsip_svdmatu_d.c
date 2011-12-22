#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_svdattributes_d.h>


int vsip_svdmatu_d(
         const vsip_sv_d *obj,
         vsip_scalar_vi low,
         vsip_scalar_vi high,
         const vsip_mview_d *C){
     int retval = 0;
     vsip_mview_d U = *(obj->mU);
     U.row_length = (high - low) + 1;
     U.offset = U.offset + low * U.row_stride;
     vsip_mcopy_d_d(&U,C);
     return retval;
}
