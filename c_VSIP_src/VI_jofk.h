/* Created By RJudd August 3, 2002 */
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
/* $Id: VI_jofk.h,v 2.0 2003/02/22 15:18:32 judd Exp $ */
#ifndef VI_JOFK__H
#define VI_JOFK__H
#include<vsip.h>

/* Index conversion routine for DFT's */
/* 2.2.3 of Van Loan, "computational Frameworks for the */
/* Fast Fourier Transform */
static
vsip_scalar_vi 
VI_jofk(vsip_scalar_vi k, /* index to reverse */
                    vsip_scalar_vi *pn,
                    vsip_scalar_vi *p0,
                    vsip_scalar_vi pF,
                    vsip_length fn)
{
   vsip_scalar_vi l = (vsip_scalar_vi)fn;
   vsip_scalar_vi i,q; 
   vsip_scalar_vi j = 0; 
   vsip_scalar_vi m = k; 
   vsip_scalar_vi aq,s,p; 
   for(q = 0; q < l; q++){ 
       i = pn[q] - 1; 
       p = p0[q]; 
       while(i-- > 0){ 
          s = m/p; 
          aq = m - s * p; 
          j = p * j + aq; 
          m = s; 
       }  
   } 
   s = m/pF; 
   aq = m - s * pF; 
   j = pF * j + aq; 
   return j; 
}
#endif
