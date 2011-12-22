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
/* $Id: vsip_spline_create_d.c,v 2.2 2009/09/12 23:15:46 judd Exp $ */

#include<vsip.h>
#include<VI.h>
#include<vsip_splineattributes_d.h>


vsip_spline_d *vsip_spline_create_d(vsip_length N){
   vsip_spline_d *spline = (vsip_spline_d*)malloc(sizeof(vsip_spline_d));
   if(spline){
      spline->h = (vsip_scalar_d*)malloc(sizeof(vsip_scalar_d) * N * 5);
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

