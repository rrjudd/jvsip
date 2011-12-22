/* Created RJudd November 2, 2002 */
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
/* $Id: VI_cblockrebind_f_ds.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
/* VI_cblockrebind_f default split */

if (b == (vsip_cblock_f*) NULL){
   *pRp = (vsip_scalar_f*) NULL; *pIp = (vsip_scalar_f*) NULL; 
   } else {
      if (b->admit != VSIP_RELEASED_BLOCK) {
      *pRp = (vsip_scalar_f*) NULL; *pIp = (vsip_scalar_f*) NULL; 
   } else {
      *pRp = b->R->array;
      *pIp = (b->cstride == 1) ? b->I->array : (vsip_scalar_f*) NULL;
      b->R->array = Rp;
      b->cstride = ((Ip == NULL) ? 2 : 1);
      b->R->rstride = b->cstride;
      b->I->rstride = b->cstride;
      b->I->array = (b->cstride == 1) ? Ip : Rp + 1;
   }
}
