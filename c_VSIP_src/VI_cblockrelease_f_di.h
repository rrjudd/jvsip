/* Created RJudd June 2, 2002 */
/* SPAWARSYSCEN D857          */
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
/* $Id: VI_cblockrelease_f_di.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
/* VI_cblockrelease_f default interleaved */

{
   if ((vsip_cblock_f*) NULL == b) {
      *Rp = (vsip_scalar_f*)NULL;     /* if block null return null */
      *Ip = (vsip_scalar_f*)NULL;
   } else {
      if (b->kind != VSIP_USER_BLOCK) {
         *Rp = (vsip_scalar_f*)NULL;  /* null if not user block    */
         *Ip = (vsip_scalar_f*)NULL;
      } else {
         b->admit    = VSIP_RELEASED_BLOCK;
         b->R->admit = VSIP_RELEASED_BLOCK;
         b->I->admit = VSIP_RELEASED_BLOCK;
         *Rp = b->R->array;
         *Ip = (b->cstride == 1) ? /* if one split complex */
                 /* if split return array      */ b->I->array :
                 /* if interleaved return null */ (vsip_scalar_f*)NULL;
      }
   }
}
