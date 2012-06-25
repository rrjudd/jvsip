/* Created RJudd */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_svdattributes_d.h>


int vsip_svdmatv_d(
         const vsip_sv_d *obj,
         vsip_scalar_vi low,
         vsip_scalar_vi high,
         const vsip_mview_d *C){
     int retval = 0;
     vsip_mview_d V = *(obj->mV);
     V.row_length = (high - low) + 1;
     V.offset = V.offset + low * V.row_stride;
     vsip_mcopy_d_d(&V,C);
     return retval;
}
