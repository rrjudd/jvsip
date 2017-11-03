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
/* $Id: vsip_spline_destroy_d.c,v 2.1 2008/09/14 20:48:40 judd Exp $ */

#include"vsip.h"
#include"vsip_splineattributes_d.h"

void vsip_spline_destroy_d(vsip_spline_d *spline){
   if(spline){
      spline->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free(spline->h);
      free(spline);
   }
   return;
}
