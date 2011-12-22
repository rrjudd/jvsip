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
/* $Id: vsip_cchold_destroy_d.c,v 2.0 2003/02/22 15:18:39 judd Exp $ */
#include<vsip.h>
#include<vsip_ccholdattributes_d.h>

int
vsip_cchold_destroy_d(
          vsip_cchol_d *chol)
{
   if(chol != NULL)
      free((void*)chol);
   return 0;
}
