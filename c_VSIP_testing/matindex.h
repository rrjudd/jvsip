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
/* $Id: matindex.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void matindex(void){
   printf("********\nTEST matindex\n");
   {
      vsip_scalar_vi a_r = 2;
      vsip_scalar_vi a_c = 3;
      vsip_scalar_mi a  = vsip_matindex(a_r,a_c);
      printf("(%u %u) = vsip_matindex(%2u,%2u)\n",(unsigned)a.r,(unsigned)a.c,(unsigned)a_r,(unsigned)a_c);
      ((a.r == a_r) && (a.c == a_c)) ? 
                    printf("correct\n") : printf("error\n");
      fflush(stdout);
   }
   return;
}
/* done */
