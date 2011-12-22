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
/* $Id: get_put_attrib_mi.h,v 2.0 2003/02/22 15:23:33 judd Exp $ */
static void get_put_attrib_mi(void){
   printf("********\nTEST get_put_attrib_mi\n");
   {
       vsip_offset ivo = 3;
       vsip_stride ivs = 2;
       vsip_length ivl = 3;
       vsip_offset jvo = 2;
       vsip_stride jvs = 3;
       vsip_length jvl = 5;

       vsip_block_mi *b = vsip_blockcreate_mi(80,VSIP_MEM_NONE);
       vsip_vview_mi *v = vsip_vbind_mi(b,ivo,ivs,ivl);
       vsip_vattr_mi  attr;
       
       printf("test vgetattrib_mi\n"); fflush(stdout);
       {
          vsip_vgetattrib_mi(v,&attr);
          (attr.offset == ivo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == ivs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == ivl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       
       /* the next test requires the previous test to be correct */
       printf("test vputattrib_mi\n"); fflush(stdout);
       {
          attr.offset = jvo; attr.stride = jvs; attr.length = jvl;
          vsip_vputattrib_mi(v,&attr);
          vsip_vgetattrib_mi(v,&attr);
          (attr.offset == jvo) ? printf("offset correct\n") : 
                                 printf("offset error \n");
          (attr.stride == jvs) ? printf("stride correct\n") : 
                                 printf("stride error \n");
          (attr.length == jvl) ? printf("length correct\n") : 
                                 printf("length error \n");
          fflush(stdout);
       }       
       vsip_valldestroy_mi(v);
   }
   return;
}
