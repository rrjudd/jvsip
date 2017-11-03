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
#include"vsip_rcfirattributes_d.h"

void vsip_rcfir_getattr_d(
     const vsip_rcfir_d *fir,
     vsip_rcfir_attr *attr)
{
    attr->symm = fir->symm;
    attr->kernel_len = fir->M;
    attr->decimation = fir->D;
    attr->in_len = fir->N;
    attr->out_len = fir->N/fir->D + ((fir->N % fir->D) ? 1:0);
    attr->state = fir->state;
    return;
}
