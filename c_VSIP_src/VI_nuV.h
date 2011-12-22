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
/* $Id: VI_nuV.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#ifndef VI_NUV__H
#define VI_NUV__H
#include<vsip.h>

/* nuV*/
/* calculate number of factors of 2,3,4,5,7,8,n in N */
/* so that N = 2^n2 * 4^n4 * 8^n8 * 3^n3 * 5^n5 *7^n7 * n */

static
vsip_length
VI_nuV(vsip_length N, 
         vsip_scalar_vi *pn,
         vsip_scalar_vi *p0,
         vsip_scalar_vi *pF)
{
    vsip_scalar_vi n2=0,n3=0,n4=0,n5=0,n8=0,n7=0;
    vsip_scalar_vi k = 0;
    vsip_scalar_vi n = N;

    while((n % 3) == 0){
        n /= 3;
        n3++;
    }
    if(n3 != 0){ 
          p0[k]=3;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n3 + 1;
          }else{
             pF[k] = 3;
             pn[k] = n3;
          }
          k++;
    }

    while((n % 5) == 0){
        n /= 5;
        n5++;
    }
    if(n5 != 0){ 
          p0[k] = 5;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n5 + 1;
          }else{
             pF[k] = 5;
             pn[k] = n5;
          }
          k++;
    }

    while((n % 7) == 0){
        n /= 7;
        n7++;
    }
    if(n7 != 0){ 
          p0[k] = 7;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n7 + 1;
          }else{
             pF[k] = 7;
             pn[k] = n7;
          }
          k++;
    }

    while((n % 8) == 0) {
        n /= 8;
        n8++;
    }
    if(n8 != 0){ 
          p0[k] = 8;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n8 + 1;
          }else{
             pF[k] = 8;
             pn[k] = n8;
          }
          k++;
    }

    while((n % 4) == 0) {
        n /= 4;
        n4++;
    }
    if(n4 != 0){ 
          p0[k] = 4;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n4 + 1;
          }else{
             pF[k] = 4;
             pn[k] = n4;
          }
          k++;
    }

    while((n % 2) == 0) {
        n /= 2;
        n2++;
    }
    if(n2 != 0){ 
          p0[k] = 2;
          if(n != 1) {
             pF[k] = n;
             pn[k] = n2 + 1;
          }else{
             pF[k] = 2;
             pn[k] = n2;
          }
          k++;
    }

    if((n != 1) && (k == 0)){ 
          p0[k] = 1;
          pF[k] = n;
          pn[k] = 1;
          k++;
    }
    return (vsip_length)k;
}
#endif
