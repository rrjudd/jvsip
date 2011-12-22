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
/* $Id: vsip_splineattributes_d.h,v 2.1 2008/09/14 20:50:30 judd Exp $ */

#include<vsip.h>
#include<VI.h>

struct vsip_splineattributes_d{
   vsip_scalar_d *h,*b,*u,*v,*z;
   int markings;
};

