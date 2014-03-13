/* Created RJudd */
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
/* $Id: example1.c,v 2.0 2003/02/22 15:27:21 judd Exp $ */


#include<stdio.h>
#include<vsip.h>

#define N 8 /* the length of the vector */
void VU_vprint_f(vsip_vview_f* a){
   vsip_length i;
   for(i=0; i<vsip_vgetlength_f(a); i++)
   printf("%4.0f",vsip_vget_f(a,i));
   printf("\n");
   return;
}
int main(){vsip_init((void*)0);
{
   vsip_vview_f *A = vsip_vcreate_f(N,0),
                *B = vsip_vcreate_f(N,0),
                *C = vsip_vcreate_f(N,0);
   vsip_vramp_f(0,1,A);
   printf("A = \n");VU_vprint_f(A);

   vsip_vfill_f(5,B);
   printf("B = \n");VU_vprint_f(B);

   vsip_vadd_f(A,B,C);
   printf("C = A+B\n");
   printf("C = \n");VU_vprint_f(C);
      
   vsip_valldestroy_f(A);
   vsip_valldestroy_f(B);
   vsip_valldestroy_f(C);
   } 
   vsip_finalize((void*)0); 
   return 1;
}


