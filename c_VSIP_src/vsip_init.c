/* Created RJudd September 16, 2000 */
/* SPAWARSYSCEN D857                */
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
/* $Id: vsip_init.c,v 2.2 2009/09/05 18:03:19 judd Exp $ */
#include<vsip.h>

/* this is a NOP but to prevent warnings I do some useless stuff */
int vsip_init( void *ptr){
   int retval;
   if(ptr == NULL){
      retval = 0;
   } else{
      retval = 0;
   }
   return retval;
}
