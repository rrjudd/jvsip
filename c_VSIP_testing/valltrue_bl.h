/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: valltrue_bl.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
#include"VU_vprintm_d.include"
static void valltrue_bl(void){
   printf("********\nTEST valltrue_bl\n");
   {
     vsip_scalar_bl  data1[] = { 1,  1, 1, 1, 1 };
     vsip_scalar_bl  data2[] = { 1,  0, 0, 0, 0 };
     vsip_scalar_bl  data3[] = { 0,  0, 0, 0, 0 };
     vsip_block_bl  *block1 = vsip_blockbind_bl(data1,5,VSIP_MEM_NONE);
     vsip_block_bl  *block2 = vsip_blockbind_bl(data2,5,VSIP_MEM_NONE);
     vsip_block_bl  *block3 = vsip_blockbind_bl(data3,5,VSIP_MEM_NONE);
     vsip_vview_bl  *a1 = vsip_vbind_bl(block1,0,1,5);
     vsip_vview_bl  *a2 = vsip_vbind_bl(block2,0,1,5);
     vsip_vview_bl  *a3 = vsip_vbind_bl(block3,0,1,5);
     vsip_vview_bl  *b = vsip_vcreate_bl(20,VSIP_MEM_NONE);
     vsip_vview_d *fv = vsip_vcreate_d(5,VSIP_MEM_NONE);
     vsip_blockadmit_bl(block1,VSIP_TRUE);
     vsip_blockadmit_bl(block2,VSIP_TRUE);
     vsip_blockadmit_bl(block3,VSIP_TRUE);
     vsip_vputlength_bl(b,1); /* to keep performance mode from complaining */
     vsip_vputoffset_bl(b,18);
     vsip_vputstride_bl(b,-2);
     vsip_vputlength_bl(b,5);

     vsip_vcopy_bl_d(a1,fv);vsip_vcopy_bl_bl(a1,b);
     printf("a1 = \n");VU_vprintm_d("1.0",fv);
     printf("vsip_valltrue_bl(a1)\n");
     if(vsip_valltrue_bl(b))
         printf("true, correct\n");
     else
         printf("false, error\n");

     vsip_vcopy_bl_d(a2,fv);vsip_vcopy_bl_bl(a2,b);
     printf("a2 = \n");VU_vprintm_d("1.0",fv);
     printf("vsip_valltrue_bl(a2)\n");
     if(vsip_valltrue_bl(b))
         printf("true, error\n");
     else
         printf("false, correct\n");

     vsip_vcopy_bl_bl(a3,b); vsip_vcopy_bl_d(b,fv);
     printf("a3 = \n");VU_vprintm_d("1.0",fv);
     printf("vsip_valltrue_bl(a3)\n");
     if(vsip_valltrue_bl(b))
         printf("true, error\n");
     else
         printf("false, correct\n");

     vsip_valldestroy_bl(a1);
     vsip_valldestroy_bl(a2);
     vsip_valldestroy_bl(a3);
     vsip_valldestroy_bl(b);
     vsip_valldestroy_d(fv);
   }
   return;
}
