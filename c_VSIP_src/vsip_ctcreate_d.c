/* Created RJudd September 18, 2000 */
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
/* $Id: vsip_ctcreate_d.c,v 2.1 2004/09/21 02:07:24 judd Exp $ */

#define VI_CTVIEW_D_
#include"VI_support_cpriv_d.h"
#include"VI_cblockcreate_d.h"
#include"VI_cblockdestroy_d.h"

vsip_ctview_d* vsip_ctcreate_d(
     vsip_length zlength,
     vsip_length ylength,
     vsip_length xlength,
     vsip_tmajor major,
     vsip_memory_hint hint)
{
    vsip_cblock_d *block;
    vsip_ctview_d *ctview;
    block = VI_cblockcreate_d(zlength * ylength * xlength,hint);
    if(block == NULL) return (vsip_ctview_d*) NULL;
    ctview = VI_ctview_d();
    if(ctview == NULL){
         VI_cblockdestroy_d(block);
         return ctview;
     }
     ctview->block = block;
     ctview->offset = (vsip_offset)0;
     ctview->x_length = xlength;
     ctview->y_length = ylength;
     ctview->z_length = zlength;
     if(major == VSIP_TRAILING){
        ctview->z_stride = xlength * ylength;
        ctview->y_stride = xlength;
        ctview->x_stride = 1;
     } else { /* VSIP_LEADING */
        ctview->x_stride = zlength * ylength;
        ctview->y_stride = zlength;
        ctview->z_stride = 1;
     }
     ctview->markings = vsip_valid_structure_object;
     return ctview;        
}

