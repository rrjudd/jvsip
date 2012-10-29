/* Created RJudd Oct 26, 2012 */
/* Retired */
/* https://github.com/rrjudd/jvsip */
/***********************************************************************
 // This code includes no warranty, express or implied, including the  /
 // warranties of merchantability and fitness for a particular purpose./
 // No person or entity assumes any legal liability or responsibility  /
 // for the accuracy, completeness, or usefulness of an information    /
 // apparatus,  product, or process disclosed, or represents that its  /
 // use would not infringe privately owned rights.                     /
 **********************************************************************/
/* created by modifying vsip_vfill_si.c */

#include<vsip.h>
#include<vsip_vviewattributes_vi.h>

void vsip_vfill_vi(vsip_scalar_vi alpha,
                    const vsip_vview_vi* r) {
     unsigned int n = (unsigned int) r->length;
     int rst = (int) r->stride;
     vsip_scalar_vi *rp = (r->block->array) + r->offset;
     while(n-- > 0){
           *rp  = alpha;
            rp += rst;
     }
}
