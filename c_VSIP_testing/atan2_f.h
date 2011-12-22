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
/* $Id: atan2_f.h,v 2.0 2003/02/22 15:23:16 judd Exp $ */
static void atan2_f(void){
   printf("********\nTEST atan2_f\n");
   {
       vsip_scalar_f a = .25;
       vsip_scalar_f b = .5;
       vsip_scalar_f r = vsip_atan2_f(a,b);
       vsip_scalar_f ans = 0.463647609000806; 
       printf("atan2(%2.2f / %2.2f)\n",a,b);
       (fabs(ans - r) > .0001) ? printf("error\n") :
                                printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = -.25;
       vsip_scalar_f b = -.5;
       vsip_scalar_f r = vsip_atan2_f(a,b);
       vsip_scalar_f ans = -2.677945044588987;
       printf("atan2(%2.2f / %2.2f)\n",a,b);
       (fabs(ans - r) > .0001) ? printf("error\n") :
                                printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = 0.5;
       vsip_scalar_f b = 0.0;
       vsip_scalar_f r = vsip_atan2_f(a,b);
       vsip_scalar_f ans = M_PI/2;
       printf("atan2(%2.2f / %2.2f)\n",a,b);
       (fabs(ans - r) > .0001) ? printf("error\n") :
                                printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = -0.5;
       vsip_scalar_f b = 0.0;
       vsip_scalar_f r = vsip_atan2_f(a,b);
       vsip_scalar_f ans = -M_PI/2; 
       printf("atan2(%2.2f / %2.2f)\n",a,b);
       (fabs(ans - r) > .0001) ? printf("error\n") :
                                printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = 0.0;
       vsip_scalar_f b = .5;
       vsip_scalar_f r = vsip_atan2_f(a,b);
       vsip_scalar_f ans = 0.0;
       printf("atan2(%2.2f / %2.2f)\n",a,b);
       (fabs(ans - r) > .0001) ? printf("error\n") :
                                printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_f a = 0.0;
       vsip_scalar_f b = -.5;
       vsip_scalar_f r = vsip_atan2_f(a,b);
       vsip_scalar_f ans = M_PI; 
       printf("atan2(%2.2f / %2.2f)\n",a,b);
       (fabs(ans - r) > .0001) ? printf("error\n") :
                                printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
