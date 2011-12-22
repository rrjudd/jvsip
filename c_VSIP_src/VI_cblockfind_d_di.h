/* Created RJudd June 5, 2002 */
/* SPAWARSYSCEN D881          */
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
/* $Id: VI_cblockfind_d_di.h,v 2.0 2003/02/22 15:18:28 judd Exp $ */
/* VI_cblockfind_d default interleaved */

if(b->admit == VSIP_RELEASED_BLOCK){
   if(b->cstride == 1){
      *Rp = b->R->array;
      *Ip = b->I->array;
   } else {
      *Rp = b->R->array;
      *Ip = (vsip_scalar_d*)NULL;
   }
} else {
   *Rp = (vsip_scalar_d*)NULL;
   *Ip = (vsip_scalar_d*)NULL;
}
