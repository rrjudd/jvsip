/* Created RJudd  */
/* SPAWARSYSCEN D857                */
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
/* $Id: vsip_tdestroy_uc.c,v 2.0 2003/02/22 15:19:05 judd Exp $ */
#include"VI_support_priv_uc.h"

vsip_block_uc *vsip_tdestroy_uc(
  vsip_tview_uc *v){
   vsip_block_uc *b = (vsip_block_uc*)NULL;
   if(v != (vsip_tview_uc*)NULL){
      b = v->block;
      v->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free((void*)v);
   }
   return b;
}
