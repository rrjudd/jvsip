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
/* $Id: vsip_chold_create_f.c,v 2.0 2003/02/22 15:18:41 judd Exp $ */
#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_choldattributes_f.h>

vsip_chol_f*
vsip_chold_create_f(
          vsip_mat_uplo uplo,
          vsip_length N)
{
   vsip_chol_f* chol = (vsip_chol_f*)malloc(sizeof(vsip_chol_f));
   if(chol != NULL){
      chol->N = N;
      chol->uplo = uplo;
      chol->matrix = (vsip_mview_f*)NULL;
   }
   return chol;
}
