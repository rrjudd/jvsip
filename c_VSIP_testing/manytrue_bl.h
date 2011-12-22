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
/* $Id: manytrue_bl.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void manytrue_bl(void){
   printf("\n*******\nTEST manytrue_bl\n");
   {
       vsip_scalar_bl data0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
       vsip_scalar_bl data1[] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
       vsip_scalar_bl data2[] = {0, 1, 0, 1, 0, 1, 1, 1, 1, 0};
       vsip_scalar_bl data3[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
       vsip_scalar_bl data4[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

       vsip_mview_bl *m0 = vsip_mbind_bl(
                 vsip_blockbind_bl(data0,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_mview_bl *m1 = vsip_mbind_bl(
                 vsip_blockbind_bl(data1,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_mview_bl *m2 = vsip_mbind_bl(
                 vsip_blockbind_bl(data2,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_mview_bl *m3 = vsip_mbind_bl(
                 vsip_blockbind_bl(data3,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_mview_bl *m4 = vsip_mbind_bl(
                 vsip_blockbind_bl(data4,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_mview_d *pm = vsip_mcreate_d(2,5,VSIP_COL,VSIP_MEM_NONE);

       vsip_blockadmit_bl(vsip_mgetblock_bl(m0),VSIP_TRUE);
       vsip_blockadmit_bl(vsip_mgetblock_bl(m1),VSIP_TRUE);
       vsip_blockadmit_bl(vsip_mgetblock_bl(m2),VSIP_TRUE);
       vsip_blockadmit_bl(vsip_mgetblock_bl(m3),VSIP_TRUE);
       vsip_blockadmit_bl(vsip_mgetblock_bl(m4),VSIP_TRUE);

       printf("matrix m0\n");
       vsip_mcopy_bl_d(m0,pm); VU_mprintm_d("1.0",pm);
       printf("matrix m1\n");
       vsip_mcopy_bl_d(m1,pm); VU_mprintm_d("1.0",pm);
       printf("matrix m2\n");
       vsip_mcopy_bl_d(m2,pm); VU_mprintm_d("1.0",pm);
       printf("matrix m3\n");
       vsip_mcopy_bl_d(m3,pm); VU_mprintm_d("1.0",pm);
       printf("matrix m4\n");
       vsip_mcopy_bl_d(m4,pm); VU_mprintm_d("1.0",pm);

       printf("check anytrue \n");
       printf("vsip_manytrue_bl(m0)");
       if(vsip_manytrue_bl(m0))
            printf("true: error\n");
       else
            printf("false: correct\n");

       printf("vsip_manytrue_bl(m1)");
       if(vsip_manytrue_bl(m1))
            printf("true: correct\n");
       else
            printf("false: error\n");

       printf("vsip_manytrue_bl(m2)");
       if(vsip_manytrue_bl(m2))
            printf("true: correct\n");
       else
            printf("false: error\n");

       printf("vsip_manytrue_bl(m3)");
       if(vsip_manytrue_bl(m3))
            printf("true: correct\n");
       else
            printf("false: error\n");

       printf("vsip_manytrue_bl(m4)");
       if(vsip_manytrue_bl(m4))
            printf("true: correct\n");
       else
            printf("false: error\n");

       vsip_malldestroy_bl(m0); 
       vsip_malldestroy_bl(m1); 
       vsip_malldestroy_bl(m2); 
       vsip_malldestroy_bl(m3); 
       vsip_malldestroy_bl(m4); 
       vsip_malldestroy_d(pm);
    }
    return;
}
