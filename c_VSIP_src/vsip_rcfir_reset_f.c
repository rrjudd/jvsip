/* Created RJudd March 17, 2012 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/
#include"vsip.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_vviewattributes_f.h"
#include"vsip_rcfirattributes_f.h"
#include"VI_cvfill_f.h"

void vsip_rcfir_reset_f(
                       vsip_rcfir_f *fir)
{
   fir->p = 0;
   fir->s->length = fir->M - 1;
   VI_cvfill_f(vsip_cmplx_f((vsip_scalar_f)0,(vsip_scalar_f)0),fir->s);
   return;
}
