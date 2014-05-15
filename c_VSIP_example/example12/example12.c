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
/* $Id: example12.c,v 2.0 2003/02/22 15:27:27 judd Exp $ */

#include<vsip.h>
void VU_madd_f(vsip_mview_f* A,
               vsip_mview_f* B,
               vsip_mview_f* C){
  vsip_length L = vsip_mgetrowlength_f(A);
  vsip_index i;
  vsip_vview_f *a = vsip_mcolview_f(A,0),
               *b = vsip_mcolview_f(B,0),
               *c = vsip_mcolview_f(C,0);
  vsip_vadd_f(a,b,c);
  for(i=1; i<L; i++){
      vsip_vdestroy_f(a); a = vsip_mcolview_f(A,i);
      vsip_vdestroy_f(b); b = vsip_mcolview_f(B,i);
      vsip_vdestroy_f(c); c = vsip_mcolview_f(C,i);
      vsip_vadd_f(a,b,c);
  }
  vsip_vdestroy_f(a);vsip_vdestroy_f(b);
  vsip_vdestroy_f(c);
  return;
}
void VU_mprintm_f(char format[],vsip_mview_f *X)
{ vsip_length RL = vsip_mgetrowlength_f(X),
              CL = vsip_mgetcollength_f(X),
              row,col;
  vsip_scalar_f x;
  printf("[\n");
  for(row=0; row<CL; row++){
    for(col=0; col<RL; col++){
      x=vsip_mget_f(X,row,col);
      printf(format,x,((col==(RL-1)) ? ";" : " "));
    } printf("\n");
  }printf("];\n");
  return;
}

int main(){vsip_init((void*)0);
{   vsip_vview_f *a = vsip_vcreate_f(50,0),
                 *b = vsip_vcreate_f(50,0),
                 *c = vsip_vcreate_f(50,0);
   vsip_mview_f 
      *A = vsip_mbind_f(vsip_vgetblock_f(a),0,4,3,1,4),
      *B = vsip_mbind_f(vsip_vgetblock_f(b),0,4,3,1,4),
      *C = vsip_mbind_f(vsip_vgetblock_f(c),0,4,3,1,4);
   vsip_vramp_f(0.0,.01,a); vsip_vramp_f(0.0,1.0,b);
   VU_madd_f(A,B,C);
   printf("A = \n");VU_mprintm_f("%5.2f ",A);
   printf("B = \n");VU_mprintm_f("%5.2f ",B);
   printf("A + B = C = \n");VU_mprintm_f("%5.2f ",C);
   vsip_mdestroy_f(A); vsip_mdestroy_f(B);
   vsip_mdestroy_f(C);
   vsip_valldestroy_f(a); vsip_valldestroy_f(b);
   vsip_valldestroy_f(c);
   } vsip_finalize((void*)0);return 0;
}   
