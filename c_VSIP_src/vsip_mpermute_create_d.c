/* Created RJudd  */
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


#include"vsip.h"
#include"vsip_permuteattributes.h"

vsip_permute* 
vsip_mpermute_create_d(
     vsip_length m,
     vsip_length n,
     vsip_major major) {
   vsip_permute *retval= (vsip_permute *)malloc(sizeof(vsip_permute));
   vsip_length Nindex;
   if(major == VSIP_ROW){
      Nindex = m;
   } else {
      Nindex = n;
   }
   if(retval){ /* create space */
      int check=0;
      retval->n_vi = Nindex;
      retval->major = major;
      if(!(retval->in = (vsip_scalar_vi*)malloc(sizeof(vsip_scalar_vi) * Nindex))) check++;
      if(!(retval->b = (vsip_scalar_vi*)malloc(sizeof(vsip_scalar_vi) * Nindex))) check++;
      if(check){
         if(retval->in) free(retval->in);
         if(retval->b) free(retval->b);
         free(retval); retval = NULL;
      }
   }
   return retval;
}
