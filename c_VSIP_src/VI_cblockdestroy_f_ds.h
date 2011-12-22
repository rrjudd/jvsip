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
/* $Id: VI_cblockdestroy_f_ds.h,v 2.0 2003/02/22 15:18:28 judd Exp $ */
/* VI_cblockdestroy_f default split */

if(b != NULL ){
   b->markings    = VSIP_FREED_STRUCTURE_OBJECT;
   b->R->markings = VSIP_FREED_STRUCTURE_OBJECT;
   b->I->markings = VSIP_FREED_STRUCTURE_OBJECT;
   if(b->kind == VSIP_VSIPL_BLOCK){
      free((void*)b->R->array);
      free((void*)b->I->array);
   }
   free((void*)b->R);
   free((void*)b->I);
   free((void*)b);
}
