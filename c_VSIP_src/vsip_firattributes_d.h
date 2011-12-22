/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_firattributes_d_h
#define _vsip_firattributes_d_h 1
#include<VI.h>

struct vsip_firattributes_d{
     vsip_vview_d  *h;
     vsip_vview_d  *s;
     vsip_length N;
     vsip_length M;
     vsip_length p;
     vsip_length D;
     int ntimes;
     vsip_symmetry symm;
     vsip_alg_hint hint;
     vsip_obj_state state;
};
#endif /* _vsip_firattributes_d_h */
