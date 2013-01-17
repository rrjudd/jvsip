/* Created RJudd January 8, 2013 */
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
#include"VU_svdUtils.h"
int  /* return 0 on success, 1 on failure */
bidiag_f(
    vsip_mview_f *in, /* input matrix */
    vsip_mview_f *left,
    vsip_vview_f *d, 
    vsip_vview_f *f, 
    vsip_mview_f *right){
    int retval = 0;
    vsip_length m = vsip_mgetcollength_f(in);
    vsip_length n = vsip_mgetrowlength_f(in);
    vsip_mview_f *A = vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mcopy_f_f(in,A);
    left = meye_f(m);
    right = meye_f(n);
    return retval;
}
