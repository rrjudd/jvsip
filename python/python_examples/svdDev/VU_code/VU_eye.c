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
vsip_mview_f*
meye_f(vsip_length n){
    vsip_vview_f *d = (vsip_vview_f*) NULL;
    vsip_mview_f *retval = (vsip_mview_f*)NULL;
    retval = vsip_mcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_mdiagview_f(retval,0);
    if(d){
        vsip_mfill_f(0.0,retval);
        vsip_vfill_f(1.0,d);
        vsip_vdestroy_f(d);
    } else {
        vsip_malldestroy_f(retval);
        retval = (vsip_mview_f*) NULL;
    }
    return retval;
}
vsip_cmview_f*
cmeye_f(vsip_length n){
    vsip_cvview_f *d = (vsip_cvview_f*) NULL;
    vsip_cmview_f *retval = (vsip_cmview_f*)NULL;
    retval = vsip_cmcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_cmdiagview_f(retval,0);
    if(d){
        vsip_cmfill_f(vsip_cmplx_f(0.0,0.0),retval);
        vsip_cvfill_f(vsip_cmplx_f(1.0,0.0),d);
        vsip_cvdestroy_f(d);
    } else {
        vsip_cmalldestroy_f(retval);
        retval = (vsip_cmview_f*) NULL;
    }
    return retval;
}
vsip_mview_d*
meye_d(vsip_length n){
    vsip_vview_d *d = (vsip_vview_d*) NULL;
    vsip_mview_d *retval = (vsip_mview_d*)NULL;
    retval = vsip_mcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_mdiagview_d(retval,0);
    if(d){
        vsip_mfill_d(0.0,retval);
        vsip_vfill_d(1.0,d);
        vsip_vdestroy_d(d);
    } else {
        vsip_malldestroy_d(retval);
        retval = (vsip_mview_d*) NULL;
    }
    return retval;
}
vsip_cmview_d*
cmeye_d(vsip_length n){
    vsip_cvview_d *d = (vsip_cvview_d*) NULL;
    vsip_cmview_d *retval = (vsip_cmview_d*)NULL;
    retval = vsip_cmcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_cmdiagview_d(retval,0);
    if(d){
        vsip_cmfill_d(vsip_cmplx_d(0.0,0.0),retval);
        vsip_cvfill_d(vsip_cmplx_d(1.0,0.0),d);
        vsip_cvdestroy_d(d);
    } else {
        vsip_cmalldestroy_d(retval);
        retval = (vsip_cmview_d*) NULL;
    }
    return retval;
}
