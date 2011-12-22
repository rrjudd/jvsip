/* Created RJudd September 22, 2000 */
/* SPAWARSYSCEN D857                */
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
/* $Id: vsip_ctget_d.c,v 2.0 2003/02/22 15:18:48 judd Exp $ */

#include"VI_support_cpriv_d.h"

vsip_cscalar_d vsip_ctget_d(
     const vsip_ctview_d *v,
     vsip_index zindex,
     vsip_index yindex,
     vsip_index xindex)
{
     vsip_cscalar_d retval;
     vsip_offset offset = (vsip_offset)((v->offset +       
                           v->z_stride * (vsip_stride)zindex +  
                           v->y_stride * (vsip_stride)yindex + 
                           v->x_stride * (vsip_stride)xindex) * 
                                v->block->cstride);
     retval.r =  *(v->block->R->array + offset);
     retval.i =  *(v->block->I->array + offset);
     return retval;
}
