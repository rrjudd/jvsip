/* Created RJudd November 2, 2002 */
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
/* $Id: VI_cblockrebind_f_as.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
/* VI_cblockrebind_f always split */

if (b == (vsip_cblock_f*) NULL){
   *pRp = (vsip_scalar_f*) NULL; *pIp = (vsip_scalar_f*) NULL; 
} else {
   if (b->admit != VSIP_RELEASED_BLOCK) {
      *pRp = (vsip_scalar_f*) NULL; *pIp = (vsip_scalar_f*) NULL; 
   } else {
      *pRp = b->Rp;
      *pIp = b->Ip;
      b->Rp = Rp;
      b->Ip = Ip;
   }
}
