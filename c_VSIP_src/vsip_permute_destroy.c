/* Created RJudd  */
/* $Id: vsip_permute_destroy.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */

/*
 *  vsip_permute_destroy.c
 *  VU_permute
 *
 *  Created by Randall Judd on 7/21/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
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



