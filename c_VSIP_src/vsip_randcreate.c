/* Created by RJudd */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_randcreate.c,v 2.0 2003/02/22 15:19:01 judd Exp $ */
#include"vsip.h"
#include"vsip_randobject.h"

#define A0 1664525
#define C0 1013904223
#define A1 69069

vsip_randstate* vsip_randcreate(
           vsip_index seed,
           vsip_index numseqs,
           vsip_index id,
           vsip_rng typegen)
{
    vsip_scalar_ue32 x0 = (vsip_scalar_ue32) seed;
    vsip_scalar_ue32 k  = (vsip_scalar_ue32) numseqs;
    vsip_randstate *state = (vsip_randstate*) malloc(sizeof(vsip_randstate));
    if(state == NULL) return (vsip_randstate*)NULL;
    state->type = (int)typegen;
    if(typegen)
  { /* create non portable generator */
    vsip_scalar_ue32 a;
    vsip_scalar_ue32 c;
    vsip_scalar_ue32 i,n,k0;
    vsip_scalar_ue32 t;
    for(i=0; i< id; i++)
          x0 = A0 * x0 + C0;
    state->X = x0; /*find the seed to start out for id */
    n = 0;
    k0 = k;
    while((k0 % 2) == 0){
    k0 = k0/2;
    n++;
    }
    i = k - 1;
    a = A0;
    while(i-- >0) a *= A0; /* find a for numseqs */
    c = 1; /* find c for numseqs */
    t = 1;
    for(i=0; i<k0; i++) t *=A0;
    while(n-- >0) {
          c *= (t + 1);
          t *= t;
    }
    t = 1;
    n = A0;
    for(i=1; i<k0; i++){
      t += n;
      n *= A0;
    }
    c *= (t * C0);
    state->a = a;
    state->c = c;
  } else { /* create portable generator */
    vsip_scalar_ue32 c[]=
        {  3,   5,   7,  11,  13,  17,  19,  23,  29,  31,
          37,  41,  43,  47,  53,  59,  61,  67,  71,  73,
          79,  83,  89,  97, 101, 103, 107, 109, 113, 127,
         131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
         181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
         239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
         293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
         359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
         421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
         479, 487, 491, 499, 503, 509, 521, 523, 541, 547}; /* 100 prime numbers */
    vsip_scalar_ue32 c1 = c[id-1];
    if(id > 1) { 
      vsip_scalar_ue32 a0 = A0,
                       c0 = C0;
      vsip_scalar_ue32 mask = 1;
      vsip_scalar_ue32 big  = 4294967295ul;
      vsip_scalar_ue32 skip = (vsip_scalar_ue32)((big/k) * (id -1));
      int i; 
      for(i=0; i<32; i++) {
         if(mask & skip) {
               x0 = a0 * x0 + c0;
         }
         c0 = (a0+1) * c0;
         a0 = a0*a0;
         mask <<= 1;
      } 
    }
    state->X  = x0;
    state->X1 = 1;
    state->X2 = 1;
    state->a  = A0;
    state->c  = C0;
    state->a1 = A1; 
    state->c1 = c1;
  }
  return state;
}
