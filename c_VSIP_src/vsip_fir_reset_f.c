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
/* $Id: vsip_fir_reset_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_firattributes_f.h>
#include"VI_vfill_f.h"

void vsip_fir_reset_f(
              vsip_fir_f *fir)
{
    fir->p = 0;
    fir->s->length = fir->M - 1;
    VI_vfill_f(0,fir->s);
    return;
}
