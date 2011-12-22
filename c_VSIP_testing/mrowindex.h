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
/* $Id: mrowindex.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void mrowindex(void){
   printf("********\nTEST mrowindex\n");
   {
      vsip_scalar_vi a_r = 2;
      vsip_scalar_vi a_c = 3;
      vsip_scalar_mi a   = vsip_matindex(a_r,a_c);
      vsip_scalar_vi row = vsip_rowindex(a);
      printf(" %u = vsip_mrowindex((%2u,%2u))\n",(unsigned)row,(unsigned)a.r,(unsigned)a.c);
      ((row == a_r)) ?
                 printf("correct\n") : printf("error\n");
      fflush(stdout);
   }
}
/* done */
