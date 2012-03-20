/* Created RJudd March 18, 2018 */
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
#include"VI_mimagview_d.h"
#include"VI_mcopy_d_d.h"

void vsip_mimag_d(const vsip_cmview_d* a, const vsip_mview_d* r){
   vsip_mview_d R;
   VI_mimagview_d(a,&R);
   VI_mcopy_d_d(&R,r);
}
