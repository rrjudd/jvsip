/* Created RJudd */
/* SPAWARSYSCEN D857 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: VI_support_priv_si.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#include<vsip.h>
#include<vsip_tviewattributes_si.h>
#include<vsip_blockattributes_si.h>

#ifdef VI_TVIEW_SI_
static vsip_tview_si *VI_tview_si(void)
{
    vsip_tview_si *tview;
    tview = (vsip_tview_si*) malloc(sizeof(vsip_tview_si));
    return tview;
}
#endif /* VI_TVIEW_SI_ */
