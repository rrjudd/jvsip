/* Created RJudd  */
/* $Id: vsip_permute_init.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */


/*
 *  vsip_permute_init.c
 *  Created by Randall Judd on 8/5/07.
 *
 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#include<vsip.h>
#include<vsip_permuteattributes.h>
#include<vsip_vviewattributes_vi.h>

/* this will init or re-init */
vsip_permute *vsip_permute_init(
    vsip_permute *perm, 
    const vsip_vview_vi *vi){
   vsip_length m = perm->n_vi;
   vsip_scalar_vi *in_p = vi->block->array + vi->offset;
   vsip_stride in_strd = vi->stride;
   if(perm){ /* check to make sure we have a created perm object */
      vsip_index i;
      vsip_scalar_vi *in  = perm->in;
      /* find rows that need to move*/
      for(i=0; i<m; i++){
         /* out i is an index of rows (cols) that are permuted; other rows do not permute */
         in[i] = in_p[i * in_strd]; /* perm has its own copy of input vi */
      }
   }
   return perm; /* for convenience */
}



