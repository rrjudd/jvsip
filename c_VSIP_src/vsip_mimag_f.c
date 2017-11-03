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
#include"VI_mimagview_f.h"
#include"VI_mcopy_f_f.h"

void vsip_mimag_f(const vsip_cmview_f* a, const vsip_mview_f* r){
   vsip_mview_f R;
   VI_mimagview_f(a,&R);
   VI_mcopy_f_f(&R,r);
}
