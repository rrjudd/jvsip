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
/* $Id: acos_f.h,v 2.0 2003/02/22 15:23:16 judd Exp $ */
static void acos_f(void){
   printf("********\nTEST acos_f\n");
   {
       vsip_scalar_f a = 1.01972674369545;
       vsip_scalar_f s = M_PI/6;
       vsip_scalar_f b = vsip_acos_f(s);
       (fabs(a-b) > .0001) ? printf("error\n") :
                            printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
