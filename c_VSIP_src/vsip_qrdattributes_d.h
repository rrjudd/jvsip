/* Created RJudd August 28, 1999 */
/* SPAWARSYSCEN D881 */
/* private attributes for real qrd */
#ifndef _vsip_qrddattributes_d_h  
#define _vsip_qrdattributes_d_h 1 

#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>


struct vsip_qrdattributes_d{
   vsip_qrd_qopt qopt;
   vsip_length M;
   vsip_length N;
   vsip_mview_d *A;
   vsip_mview_d AA;
   vsip_vview_d *v;
   vsip_vview_d *w;
   vsip_scalar_d *beta;
};

#endif /*_vsip_qrdattributes_d_h */
