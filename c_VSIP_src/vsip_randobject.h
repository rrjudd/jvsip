/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_randobject_h
#define _vsip_randobject_h 1
#include<VI.h>

struct vsip_randobject{
     vsip_scalar_ue32  a; /* multiplier in LCG */
     vsip_scalar_ue32  c; /* adder in LCG */
     vsip_scalar_ue32  a1;
     vsip_scalar_ue32  c1;
     vsip_scalar_ue32  X; /* Last or initial X */
     vsip_scalar_ue32  X1;
     vsip_scalar_ue32  X2;
     
     int               type;
};
#endif /* _vsip_randobject_h */
