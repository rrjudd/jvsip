/* Created RJudd March 18, 2012 */
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
#include<vsip_rcfirattributes_d.h>
#include"VI_valldestroy_d.h"
#include"VI_cvalldestroy_d.h"

int vsip_rcfir_destroy_d(
                        vsip_rcfir_d* filt)
{
   if(filt != NULL){
      VI_valldestroy_d(filt->h);
      VI_cvalldestroy_d(filt->s);
      free((void*) filt);
   }
   return 0;
}
