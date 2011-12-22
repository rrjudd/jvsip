/* Created RJudd August 28, 1999 */
/* SPAWARSYSCEN D881 */
/* private attributes for real qrd */
#ifndef _vsip_cqrddattributes_f_h  
#define _vsip_cqrdattributes_f_h 1

#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<VI.h>


struct vsip_cqrdattributes_f{
   vsip_qrd_qopt qopt;
   vsip_length M;
   vsip_length N;
   vsip_cmview_f *A;
   vsip_cmview_f AA;
   vsip_cvview_f *v;
   vsip_cvview_f *w;
   vsip_cvview_f *cI;
   vsip_scalar_f *beta;
};

#endif /*_vsip_cqrdattributes_f_h */
