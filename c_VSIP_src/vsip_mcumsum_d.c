/* Created RJudd  */
/* SPAWARSYSCEN   */
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
/* $Id: vsip_mcumsum_d.c,v 2.1 2004/04/03 14:19:03 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include"VI_mcolview_d.h"
#include"VI_mrowview_d.h"
#include"VI_vcumsum_d.h"

void vsip_mcumsum_d(
   const vsip_mview_d *a,
   vsip_major major,
   const vsip_mview_d *r) {
   {
      vsip_vview_d *va,vaa;
      vsip_vview_d *vr,vrr;
      vsip_index i;
      vsip_length m = a->col_length;
      vsip_length n = a->row_length;
      va = &vaa; vr = &vrr;
      if(major == VSIP_ROW){
         for(i=0; i<m; i++){
            VI_mrowview_d(a,i,va);
            VI_mrowview_d(r,i,vr);
            VI_vcumsum_d(va,vr);
         }
      } else { /* must be VSIP_COL */
         for(i=0; i<n; i++){
            VI_mcolview_d(a,i,va);
            VI_mcolview_d(r,i,vr);
            VI_vcumsum_d(va,vr);
         }
      }
   }
   return;
}
