#include<stdio.h>
#include<vsip.h>

#define N 6 /* the length of the vector */
void VU_vprint_f(vsip_vview_f* a){
   vsip_length i;
   for(i=0; i<vsip_vgetlength_f(a); i++)
       printf("%+.2f ",vsip_vget_f(a,i));
   printf("\n");
   return;
}
int main(){vsip_init((void*)0);
{
   vsip_vview_f *A = vsip_vcreate_f(N,0),
                *B = vsip_vcreate_f(N,0),
                *C = vsip_vcreate_f(N,0);
   vsip_randstate *rndm=\
        vsip_randcreate(7,1,1,VSIP_PRNG);
   vsip_vrandn_f(rndm,A);
   printf("A = ");VU_vprint_f(A);

   vsip_vfill_f(5,B);
   printf("B = ");VU_vprint_f(B);

   vsip_vadd_f(A,B,C);
   printf("C = A+B\n");
   printf("C = ");VU_vprint_f(C);
      
   vsip_valldestroy_f(A);
   vsip_valldestroy_f(B);
   vsip_valldestroy_f(C);
   vsip_randdestroy(rndm);
   } 
   vsip_finalize((void*)0); 
   return 1;
}

/* output */
/*
A = -0.05 +0.59 +0.73 -0.37 -0.21 -0.83 
B = +5.00 +5.00 +5.00 +5.00 +5.00 +5.00 
C = A+B
C = +4.95 +5.59 +5.73 +4.63 +4.79 +4.17 
*/
