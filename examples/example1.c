#include<stdio.h>
#include<vsip.h>
#define N 8 /* the length of the vector */

void VU_vprint_d(vsip_vview_d* a){
   vsip_length i;
   for(i=0; i<vsip_vgetlength_d(a); i++)
   printf("%4.0f",vsip_vget_d(a,i));
   printf("\n");
}

int main(){
   vsip_init((void*)0);
   vsip_vview_d *A = vsip_vcreate_d(N,0), *B = vsip_vcreate_d(N,0),
                         *C = vsip_vcreate_d(N,0);
   vsip_vramp_d(0,1,A);
   printf("A = \n");VU_vprint_d(A);
   vsip_vfill_d(5,B);
   printf("B = \n");VU_vprint_d(B);
   vsip_vadd_d(A,B,C);
   printf("C = \n");VU_vprint_d(C);      
   vsip_valldestroy_d(A);
   vsip_valldestroy_d(B);
   vsip_valldestroy_d(C);
   vsip_finalize((void*)0);
   return 1;
}
