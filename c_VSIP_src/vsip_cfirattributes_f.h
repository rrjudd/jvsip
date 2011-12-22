/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_cfirattributes_f_h
#define _vsip_cfirattributes_f_h 1
#include<VI.h>

struct vsip_cfirattributes_f{
     vsip_cvview_f  *h;
     vsip_cvview_f  *s;
     vsip_length N;
     vsip_length M;
     vsip_length p;
     vsip_length D;
     int ntimes;
     vsip_symmetry symm;
     vsip_alg_hint hint;
     vsip_obj_state state;
};
#endif /* _vsip_cfirattributes_f_h */
