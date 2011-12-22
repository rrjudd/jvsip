/* Created RJudd August 28, 1999 */
/* SPAWARSYSCEN D881 */
/* private attributes for real qrd */
#ifndef _vsip_cqrddattributes_d_h  
#define _vsip_cqrdattributes_d_h 1

#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<VI.h>


struct vsip_cqrdattributes_d{
   vsip_qrd_qopt qopt;
   vsip_length M;
   vsip_length N;
   vsip_cmview_d *A;
   vsip_cmview_d AA;
   vsip_cvview_d *v;
   vsip_cvview_d *w;
   vsip_cvview_d *cI;
   vsip_scalar_d *beta;
};

#endif /*_vsip_cqrdattributes_d_h */
