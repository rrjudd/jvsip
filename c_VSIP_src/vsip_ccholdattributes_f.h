/* Created RJudd August 30, 2002 */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_ccholdattributes_f.h,v 2.0 2003/02/22 15:48:15 judd Exp $ */
#ifndef VI_CCHOLDATTRIBUTES_F_H
#define VI_CCHOLDATTRIBUTES_F_H
#include<vsip.h>
#include<vsip_cmviewattributes_f.h>

struct vsip_ccholdattributes_f{
       const vsip_cmview_f* matrix;
       vsip_length N;
       vsip_mat_uplo uplo;
       };

#endif /* VI_CCHOLDATTRIBUTES_F_H */
