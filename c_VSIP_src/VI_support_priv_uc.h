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
/* $Id: VI_support_priv_uc.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#include<vsip.h>
#include<vsip_tviewattributes_uc.h>
#include<vsip_blockattributes_uc.h>

#ifdef VI_TVIEW_UC_
static vsip_tview_uc *VI_tview_uc(void)
{
    vsip_tview_uc *tview;
    tview = (vsip_tview_uc*) malloc(sizeof(vsip_tview_uc));
    return tview;
}
#endif /* VI_TVIEW_SI_ */
