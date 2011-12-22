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
/* $Id: vsip_cchold_create_d.c,v 2.0 2003/02/22 15:18:39 judd Exp $ */
#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_ccholdattributes_d.h>

vsip_cchol_d*
vsip_cchold_create_d(
          vsip_mat_uplo uplo,
          vsip_length N)
{
   vsip_cchol_d* chol = (vsip_cchol_d*)malloc(sizeof(vsip_cchol_d));
   if(chol != NULL){
      chol->N = N;
      chol->uplo = uplo;
      chol->matrix = (vsip_cmview_d*)NULL;
   }
   return chol;
}
