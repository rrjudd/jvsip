/* Created RJudd August 28, 1999 */
/* SPAWARSYSCEN D881 */
/* private attributes for real qrd */
#ifndef _vsip_qrddattributes_f_h  
#define _vsip_qrdattributes_f_h 1 

#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>


struct vsip_qrdattributes_f{
   vsip_qrd_qopt qopt;
   vsip_length M;
   vsip_length N;
   vsip_mview_f *A;
   vsip_mview_f AA;
   vsip_vview_f *v;
   vsip_vview_f *w;
   vsip_scalar_f *beta;
};

#endif /*_vsip_qrdattributes_f_h */
