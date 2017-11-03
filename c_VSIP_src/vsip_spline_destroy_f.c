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
/* $Id: vsip_spline_destroy_f.c,v 2.2 2009/10/13 02:51:41 judd Exp $ */

#include"vsip.h"
#include"vsip_splineattributes_f.h"

void vsip_spline_destroy_f(vsip_spline_f *spline){
   if(spline){
      spline->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free(spline->h);
      free(spline);
   }
   return;
}

