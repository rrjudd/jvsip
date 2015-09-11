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
/* $Id: example14.c,v 2.0 2003/02/22 15:27:30 judd Exp $ */

#include<vsip.h>
void VU_vsort_f(vsip_vview_f *x){ /* do this in place */
  vsip_scalar_f temp; /* need to store some temp data */
  vsip_vview_f *x_clone = vsip_vcloneview_f(x);
  vsip_index index;
  vsip_length x_length = vsip_vgetlength_f(x);
  vsip_offset x_offset = vsip_vgetoffset_f(x);
  vsip_stride x_stride = vsip_vgetstride_f(x);
  while(x_length-- >1){
     temp = vsip_vget_f(x_clone,0);
     vsip_vput_f(x_clone,0,vsip_vminval_f(x_clone,&index));
     vsip_vput_f(x_clone,index,temp);
     x_offset += x_stride;
     vsip_vputlength_f(x_clone,x_length);
     vsip_vputoffset_f(x_clone,x_offset);
  }
  vsip_vdestroy_f(x_clone);
  return;
}
int main(){vsip_init((void*)0);{
  vsip_scalar_f u_data[] = {5.0, -3.0, 3.0, 2.0, 1.0, 9.0,
                            8.5, 11.5, 9.0};
  vsip_block_f *u_block = vsip_blockbind_f(u_data,9,0);
  vsip_vview_f  *u_view = vsip_vbind_f(u_block,0,1,9);
  printf("input\n");
  {int i; for(i=0; i<9; i++) printf("%5.1f\n",u_data[i]);}
  vsip_blockadmit_f(u_block, VSIP_TRUE);
  VU_vsort_f(u_view);
  vsip_blockrelease_f(u_block,VSIP_TRUE);
  printf("output\n");
  {int i; for(i=0; i<9; i++) printf("%5.1f\n",u_data[i]);}
  }vsip_finalize((void*)0);return 0;
}
