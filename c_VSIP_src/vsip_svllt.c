/* Created RJudd August 13, 2013 */
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
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_vviewattributes_bl.h>

void vsip_svllt_f(
  vsip_scalar_f a,
  const vsip_vview_f* b,
  const vsip_vview_bl* r) {
    {
      vsip_length n = r->length;
      vsip_stride    bst = b->stride * b->block->rstride,
                     rst = r->stride;
      vsip_scalar_f  *bp = (b->block->array) + b->offset * b->block->rstride;
      vsip_scalar_bl *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
           *rp = (a  < *bp);
            bp += bst; rp += rst;
      }
    }
}

void vsip_svllt_d(
  vsip_scalar_d a,
  const vsip_vview_d* b,
  const vsip_vview_bl* r) {
    {
      vsip_length n = r->length;
      vsip_stride    bst = b->stride * b->block->rstride,
                     rst = r->stride;
      vsip_scalar_d  *bp = (b->block->array) + b->offset * b->block->rstride;
      vsip_scalar_bl *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
           *rp = (a  < *bp);
            bp += bst; rp += rst;
      }
    }
}

