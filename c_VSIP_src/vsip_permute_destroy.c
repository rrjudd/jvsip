/* Created RJudd  */
/* $Id: vsip_permute_destroy.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */

/*
 *  vsip_permute_destroy.c
 *  VU_permute
 *
 *  Created by Randall Judd on 7/21/07.
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

void vsip_permute_destroy(vsip_permute *perm){
   if(perm){
      if(perm->in) free(perm->in);
      if(perm->b) free(perm->b);
      free(perm); 
      perm=NULL;
   }
   return;
}



