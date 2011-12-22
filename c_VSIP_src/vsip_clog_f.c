/* Created RJudd October 14, 2000 */
/* SPAWARSYSCEN D881              */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_clog_f.c,v 2.0 2003/02/22 15:18:41 judd Exp $ */

#include<vsip.h>

vsip_cscalar_f (vsip_clog_f)(
  vsip_cscalar_f x) {
    vsip_cscalar_f a;
    vsip_scalar_f s = ((x.r > 0) ? x.r: -x.r) + ((x.i >0) ? x.i: -x.i);
    vsip_scalar_f ss = s * s;
    if(s == 0){
        a.i = VSIP_MAX_SCALAR_F;
        a.r = VSIP_MAX_SCALAR_F;
    } else if(x.i == 0){
        a.i = (vsip_scalar_f)((x.r < 0) ? M_PI : 0);
        a.r = (vsip_scalar_f)log((x.r < 0) ? -x.r : x.r);
    } else {
        a.i = (vsip_scalar_f)atan2(x.i,x.r);
        a.r = (vsip_scalar_f)log( s * sqrt((x.r * x.r)/ss + 
                                           (x.i * x.i)/ss));
    }
    return a;
}
