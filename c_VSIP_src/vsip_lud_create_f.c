/* Created By RJudd October 17, 1999 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_lud_create_f.c,v 2.0 2003/02/22 15:18:53 judd Exp $ */

#include<vsip.h>
#include<vsip_ludattributes_f.h>

vsip_lu_f* (vsip_lud_create_f)(
             vsip_length N)
{
  vsip_lu_f *lud = (vsip_lu_f*) malloc(sizeof(vsip_lu_f));
  if(lud == NULL) return (vsip_lu_f*) NULL;
  lud->N       = N;
  lud->P = (vsip_index*)malloc(N * sizeof(vsip_index));
  /* check for allocation failure, 
     clean up and return NULL if found */
  if((lud->N == (vsip_length)0) |
     (lud->P == NULL) ){ 
       vsip_lud_destroy_f(lud);
       return(vsip_lu_f*) NULL;
  }
  return lud;
}
