/* Created RJudd March 17, 2012 */
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

#ifndef _vsip_rcfirattributes_d_h
#define _vsip_rcfirattributes_d_h
#include"VI.h"

struct vsip_rcfirattributes_d{
   vsip_vview_d  *h;
   vsip_cvview_d  *s;
   vsip_length N;
   vsip_length M;
   vsip_length p;
   vsip_length D;
   int ntimes;
   vsip_symmetry symm;
   vsip_alg_hint hint;
   vsip_obj_state state;
};

#endif /* _vsip_rcfirattributes_d_h */
