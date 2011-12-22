/* Created RJudd August 30, 2002 */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_cchold_create_f.c,v 2.0 2003/02/22 15:18:39 judd Exp $ */
#include<vsip.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_ccholdattributes_f.h>

vsip_cchol_f*
vsip_cchold_create_f(
          vsip_mat_uplo uplo,
          vsip_length N)
{
   vsip_cchol_f* chol = (vsip_cchol_f*)malloc(sizeof(vsip_cchol_f));
   if(chol != NULL){
      chol->N = N;
      chol->uplo = uplo;
      chol->matrix = (vsip_cmview_f*)NULL;
   }
   return chol;
}
