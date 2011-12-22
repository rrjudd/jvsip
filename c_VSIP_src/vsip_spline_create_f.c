/* Created RJudd */
/**********************************************************************
// TASP VSIPL Documentation and Code includes no warranty,            /
// express or implied, including the warranties of merchantability    /
// and fitness for a particular purpose. No person or organization    /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_spline_create_f.c,v 2.2 2009/09/12 23:15:46 judd Exp $ */

#include<vsip.h>
#include<VI.h>
#include<vsip_splineattributes_f.h>


vsip_spline_f *vsip_spline_create_f(vsip_length N){
   vsip_spline_f *spline = (vsip_spline_f*)malloc(sizeof(vsip_spline_f));
   if(spline){
      spline->h = (vsip_scalar_f*)malloc(sizeof(vsip_scalar_f) * N * 5);
      spline->markings = VSIP_VALID_STRUCTURE_OBJECT;
      if(spline->h){
         spline->b = spline->h + N;
         spline->u = spline->b + N;
         spline->v = spline->u + N;
         spline->z = spline->v + N;
      } else {
         free(spline);
         spline = NULL;
      }
   }
   return spline;
}

