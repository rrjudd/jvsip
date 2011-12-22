/* Modified RJudd June 27, 1998 */
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
/* $Id: VI_valldestroy_d.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */

#include<vsip.h>
#ifndef VI_VALLDESTROY_D_H
#define VI_VALLDESTROY_D_H
#include"VI_blockdestroy_d.h"
#include"VI_vdestroy_d.h"

static
void 
VI_valldestroy_d(
  vsip_vview_d* v) {	/* vector view  destructor	*/
  VI_blockdestroy_d(VI_vdestroy_d(v));
  return;
}

#endif
