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
/* $Id: polar_f.h,v 2.0 2003/02/22 15:23:18 judd Exp $ */
static void polar_f(void){
   printf("********\nTEST polar_f\n");
   {
       vsip_cscalar_f s = vsip_cmplx_f(3,4);
       vsip_scalar_f  r = 5;
       vsip_scalar_f  a = 0.927295218002;
       vsip_scalar_f x,y;
       vsip_polar_f(s,&x,&y);
       printf("vsip_polar_f((%3.2f + %3.2fi),r = %5.4f,theta = %5.4f);\n",s.r,s.i,x,y);
       ((fabs(r-x) > .0001) || (fabs(a-y) > .0001)) ? 
                  printf("error\n") : printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
