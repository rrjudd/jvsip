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

#include"vsip.h"
#include"vsip_rcfirattributes_f.h"
#include"VI_valldestroy_f.h"
#include"VI_cvalldestroy_f.h"

int vsip_rcfir_destroy_f(
                        vsip_rcfir_f* filt)
{
   if(filt != NULL){
      VI_valldestroy_f(filt->h);
      VI_cvalldestroy_f(filt->s);
      free((void*) filt);
   }
   return 0;
}
