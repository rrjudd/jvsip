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
/* $Id: asin_d.h,v 2.0 2003/02/22 15:23:16 judd Exp $ */
static void asin_d(void){
   printf("********\nTEST asin_d\n");
   {
       vsip_scalar_d a = 0.5510695830994463;
       vsip_scalar_d s = M_PI/6;
       vsip_scalar_d b = vsip_asin_d(s);
       (fabs(a-b) > .0001) ? printf("error\n") :
                            printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
