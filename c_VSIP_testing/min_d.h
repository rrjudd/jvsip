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
/* $Id: min_d.h,v 2.0 2003/02/22 15:23:18 judd Exp $ */
static void min_d(void){
   printf("********\nTEST min_d\n");
   {
       vsip_scalar_d x = 5;
       vsip_scalar_d y = -1;
       vsip_scalar_d a = -1;
       vsip_scalar_d b = vsip_min_d(x,y);
       printf(" %5.4f = vsip_min_d(%5.4f,%5.4f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_d x = -5;
       vsip_scalar_d y = -1;
       vsip_scalar_d a = -5;
       vsip_scalar_d b = vsip_min_d(x,y);
       printf(" %5.4f = vsip_min_d(%5.4f,%5.4f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_d x = -5;
       vsip_scalar_d y =  1;
       vsip_scalar_d a = -5;
       vsip_scalar_d b = vsip_min_d(x,y);
       printf(" %5.4f = vsip_min_d(%5.4f,%5.4f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   {
       vsip_scalar_d x =  5;
       vsip_scalar_d y =  1;
       vsip_scalar_d a = 1;
       vsip_scalar_d b = vsip_min_d(x,y);
       printf(" %5.4f = vsip_min_d(%5.4f,%5.4f)\n",b,x,y);
       (fabs(a-b) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
