/* Created RJudd December 14, 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_cfir_destroy_f.c,v 2.0 2003/02/22 15:18:40 judd Exp $ */
/* destroy complex fir object */
#include"vsip.h"
#include"vsip_cfirattributes_f.h"
#include"VI_cvalldestroy_f.h"

int vsip_cfir_destroy_f(
          vsip_cfir_f* filt)
{
    if(filt != NULL){
       VI_cvalldestroy_f(filt->h);
       VI_cvalldestroy_f(filt->s);
       free((void*) filt);
    }
    return 0;
}

