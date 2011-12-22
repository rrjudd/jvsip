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
/* $Id: fmod_d.h,v 2.0 2003/02/22 15:23:17 judd Exp $ */
static void fmod_d(void){
   printf("********\nTEST fmod_d\n");
   {
       vsip_scalar_d a = 2.7;
       vsip_scalar_d x = 50.3;
       vsip_scalar_d y = 3.4;
       vsip_scalar_d b = vsip_fmod_d(x,y);
       printf("%5.3f = vsip_fmod_d(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_d a = -2.7;
       vsip_scalar_d x = -50.3;
       vsip_scalar_d y = 3.4;
       vsip_scalar_d b = vsip_fmod_d(x,y);
       printf("%5.3f = vsip_fmod_d(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_d a = -2.7;
       vsip_scalar_d x = -50.3;
       vsip_scalar_d y = -3.4;
       vsip_scalar_d b = vsip_fmod_d(x,y);
       printf("%5.3f = vsip_fmod_d(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_d a = 2.7;
       vsip_scalar_d x = 50.3;
       vsip_scalar_d y = -3.4;
       vsip_scalar_d b = vsip_fmod_d(x,y);
       printf("%5.3f = vsip_fmod_d(%5.3f,%5.3f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
}
