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
vsip_scalar_f 
sign_f(vsip_scalar_f a_in){
    if(a_in < 0.0)
       return -1.0;
    else 
       return 1.0;
}

vsip_cscalar_f 
csign_f(vsip_cscalar_f a_in){
    vsip_scalar_f re = a_in.r;
    vsip_scalar_f im = a_in.i;
    vsip_scalar_f t=vsip_hypot_f(re,im);
    vsip_cscalar_f retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0) {
        retval.r = sign_f(re);
        return retval;
    } else {
        retval.r = re/t;
        retval.i = im/t;
        return retval;
    }
}

vsip_scalar_d 
sign_d(vsip_scalar_d a_in){
    if(a_in < 0.0)
        return -1.0;
    else 
        return 1.0; 
}

vsip_cscalar_d 
csign_d(vsip_cscalar_d a_in){
    vsip_scalar_d re = a_in.r;
    vsip_scalar_d im = a_in.i;
    vsip_scalar_d t=vsip_hypot_d(re,im);
    vsip_cscalar_d retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0){
        retval.r = sign_d(re);
        return retval;
    } else {
        retval.r = re/t;
        retval.i = im/t;
        return retval;
    }
}
