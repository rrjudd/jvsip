/* Created RJudd November 2, 2002 */
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
/* $Id: VI_cblockrelease_d_as.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
/* VI_cblockrelease_d always split */

if (b == (vsip_cblock_d*) NULL ) {
   *Rp = (vsip_scalar_d*)NULL;     /* if block null return null */
   *Ip = (vsip_scalar_d*)NULL;
} else {
   if (b->kind != VSIP_USER_BLOCK) {
      *Rp = (vsip_scalar_d*)NULL;  /* null if not user block    */
      *Ip = (vsip_scalar_d*)NULL;
   } else {
      if((b->r_data == b->R->array) && (update)){
         vsip_length n = b->size;
         vsip_scalar_d *ptr_R = b->R->array,
                       *ptr_I = b->I->array,
                       *ptr_Rp = b->Rp;
         while(n-- > 0){
            *ptr_Rp = *ptr_R; 
             ptr_Rp++; ptr_R++;
            *ptr_Rp = *ptr_I;
             ptr_Rp++; ptr_I++;
         }
      }
      b->admit    = VSIP_RELEASED_BLOCK;
      b->R->admit = VSIP_RELEASED_BLOCK;
      b->I->admit = VSIP_RELEASED_BLOCK;
      *Rp = b->Rp;
      *Ip = b->Ip;
   }
}

