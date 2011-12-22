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
/* $Id: fmod_f.h,v 2.0 2003/02/22 15:23:17 judd Exp $ */
static void fmod_f(void){
   printf("********\nTEST fmod_f\n");
   {
       vsip_scalar_f a = 2.7;
       vsip_scalar_f x = 50.3;
       vsip_scalar_f y = 3.4;
       vsip_scalar_f b = vsip_fmod_f(x,y);
       printf("%5.3f = vsip_fmod_f(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = -2.7;
       vsip_scalar_f x = -50.3;
       vsip_scalar_f y = 3.4;
       vsip_scalar_f b = vsip_fmod_f(x,y);
       printf("%5.3f = vsip_fmod_f(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = -2.7;
       vsip_scalar_f x = -50.3;
       vsip_scalar_f y = -3.4;
       vsip_scalar_f b = vsip_fmod_f(x,y);
       printf("%5.3f = vsip_fmod_f(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = 2.7;
       vsip_scalar_f x = 50.3;
       vsip_scalar_f y = -3.4;
       vsip_scalar_f b = vsip_fmod_f(x,y);
       printf("%5.3f = vsip_fmod_f(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
}
