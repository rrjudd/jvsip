/* Created RJudd December 28, 1999 */
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
/* $Id: vsip_cfir_reset_d.c,v 2.1 2003/03/08 14:43:33 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cfirattributes_d.h>
#include"VI_cvfill_d.h"

void vsip_cfir_reset_d(
              vsip_cfir_d *fir)
{
    fir->p = 0;
    fir->s->length = fir->M - 1;
    VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),fir->s);
    return;
}
