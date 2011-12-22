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
/* $Id: mindexbool.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void mindexbool(void){
   printf("\n*******\nTEST mindexbool\n");
   {
       vsip_scalar_bl crct = VSIP_TRUE;
       vsip_scalar_bl data1[] = {0, 0, 0, 0, 0, 
                                 1, 0, 0, 0, 0};
       vsip_scalar_vi ans_data1[]  = {1,0};

       vsip_scalar_bl data2[] = {0, 1, 0, 1, 0,    
                                 1, 1, 1, 1, 0};
       vsip_scalar_vi ans_data2[]  = {0,1 , 0,3 , 1,0 , 1,1 , 1,2 , 1,3};
       vsip_scalar_vi ans_data2_1[]  = {1,0 , 0,1 , 1,1 , 1,2 , 0,3 , 1,3};
 
       vsip_mview_f *pm = vsip_mcreate_f(2,5,VSIP_ROW,VSIP_MEM_NONE);
       vsip_mview_bl *m2_0 = vsip_mcreate_bl(4,40,VSIP_COL,VSIP_MEM_NONE);
       vsip_mview_bl *m2_1 = vsip_msubview_bl(m2_0,1,1,2,5);

       vsip_vview_mi  *index  = vsip_vcreate_mi(10,VSIP_MEM_NONE);

       vsip_mview_bl *m1 = vsip_mbind_bl(
                 vsip_blockbind_bl(data1,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_mview_bl *m2 = vsip_mbind_bl(
                 vsip_blockbind_bl(data2,10,VSIP_MEM_NONE),0,5,2,1,5);       
 
       vsip_vview_mi *ans1 = vsip_vbind_mi(
                  vsip_blockbind_mi(ans_data1,1,VSIP_MEM_NONE),0,1,1);
       vsip_vview_mi *ans2 = vsip_vbind_mi(
                  vsip_blockbind_mi(ans_data2,1,VSIP_MEM_NONE),0,1,6);
       vsip_vview_mi *ans2_1 = vsip_vbind_mi(
                  vsip_blockbind_mi(ans_data2_1,1,VSIP_MEM_NONE),0,1,6);

       vsip_length check;
       vsip_scalar_mi c1,c2;
       int i;

       vsip_blockadmit_bl(vsip_mgetblock_bl(m1),VSIP_TRUE);
       vsip_blockadmit_bl(vsip_mgetblock_bl(m2),VSIP_TRUE);
       vsip_blockadmit_mi(vsip_vgetblock_mi(ans1),VSIP_TRUE);
       vsip_blockadmit_mi(vsip_vgetblock_mi(ans2),VSIP_TRUE);
       vsip_blockadmit_mi(vsip_vgetblock_mi(ans2_1),VSIP_TRUE);
       vsip_mcopy_bl_bl(m2,m2_1);

       printf("matrix m1\n");
       vsip_mcopy_bl_f(m1,pm); VU_mprintm_f("1",pm);
       printf("vsip_mindexbool(m1,index) returns");
       printf(" %ld\n",(check = vsip_mindexbool(m1,index)));
       if(check != 1){
           printf("error: return value incorrect\n");
           crct = VSIP_FALSE;
       }
       if(check != vsip_vgetlength_mi(index)) {
           printf("error: return value not equal returned index length\n");
           crct = VSIP_FALSE;
       }
       printf("index equals \n"); VU_vprintm_mi("1",index);
       printf("right answer \n"); VU_vprintm_mi("1",ans1);
       c1 = vsip_vget_mi(index,VSIP_MEM_NONE); c2 = vsip_vget_mi(ans1,VSIP_MEM_NONE);
       if((vsip_rowindex(c1)-vsip_rowindex(c2))){
           printf("row index error\n");
           crct = VSIP_FALSE;
       }
       if((vsip_colindex(c1)-vsip_colindex(c2))){
           printf("column index error\n");
           crct = VSIP_FALSE;
       }
       
       vsip_vputlength_mi(index,10);

       printf("matrix m2 row major\n");
       vsip_mcopy_bl_f(m2,pm); VU_mprintm_f("1",pm);
       printf("vsip_mindexbool(m2,index) returns");
       printf(" %ld\n",(check = vsip_mindexbool(m2,index)));
       if(check != 6){
           printf("error: return value incorrect\n");
           crct = VSIP_FALSE;
       }
       if(check != vsip_vgetlength_mi(index)){
           printf("error: return value not equal returned index length\n");
           crct = VSIP_FALSE;
       }
       printf("index equals \n"); VU_vprintm_mi("1",index);
       printf("right answer \n"); VU_vprintm_mi("1",ans2);
       { int ckr=0, ckc=0;
         for(i=0; i<6; i++){
             c1 = vsip_vget_mi(index,i); c2 = vsip_vget_mi(ans2,i);
             if((vsip_rowindex(c1)-vsip_rowindex(c2))) ckr++;
             if((vsip_colindex(c1)-vsip_colindex(c2))) ckc++;
         }
         if(ckr != 0){
            printf("row index error\n");
            crct = VSIP_FALSE;
         }
         if(ckc != 0){
            printf("column index error\n");
            crct = VSIP_FALSE;
         }
       }

       printf("matrix m2 column major\n");
       vsip_mcopy_bl_f(m2_1,pm); VU_mprintm_f("1",pm);
       printf("vsip_mindexbool(m2,index) returns");
       printf(" %ld\n",(check = vsip_mindexbool(m2_1,index)));
       if(check != 6){
           printf("error: return value incorrect\n");
           crct = VSIP_FALSE;
       }
       if(check != vsip_vgetlength_mi(index)){
           printf("error: return value not equal returned index length\n");
           crct = VSIP_FALSE;
       }
       printf("index equals \n"); VU_vprintm_mi("1",index);
       printf("right answer \n"); VU_vprintm_mi("1",ans2_1);
       { int ckr=0, ckc=0;
         for(i=0; i<6; i++){
             c1 = vsip_vget_mi(index,i); c2 = vsip_vget_mi(ans2_1,i);
             if((vsip_rowindex(c1)-vsip_rowindex(c2))) ckr++;
             if((vsip_colindex(c1)-vsip_colindex(c2))) ckc++;
         }
         if(ckr != 0){
            printf("row index error\n");
            crct = VSIP_FALSE;
         }
         if(ckc != 0){
            printf("column index error\n");
            crct = VSIP_FALSE;
         }
       }

       if(crct) printf("correct\n");


       vsip_malldestroy_bl(m1); 
       vsip_malldestroy_bl(m2); 
       vsip_valldestroy_mi(ans1); 
       vsip_valldestroy_mi(ans2); 
       vsip_valldestroy_mi(index); 
       vsip_malldestroy_f(pm);
    }
    return;
}
