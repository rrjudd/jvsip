/* Created RJudd  */
/* private attributes for permute */

/* $Id: vsip_permuteattributes.h,v 2.1 2008/08/17 17:52:11 judd Exp $ */
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

#ifndef _vsip_permute_h
#define _vsip_permtue_h 1 

#include<vsip.h>

struct vsip_permuteattributes{
                           
   vsip_scalar_vi *in;    /* copy of raw input vector */
   vsip_scalar_vi *b;
   vsip_length n_vi;      /* length of in[ ], true, ordered */
   vsip_major major;      /* VSIP_ROW if A(:,v); VSIP_COL if A(v,:) */
};

#endif /*_vsip_permute_h */
