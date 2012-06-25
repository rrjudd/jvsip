/*
 *  vsip_svd_destroy_f.c
 *  svd_test
 *
 *  Created by Randall Judd on 9/11/08.
 *
 */
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

#include<vsip.h>
#include"vsip_svdattributes_f.h"

int vsip_svd_destroy_f(vsip_sv_f *obj){
   int retval = 0;
   if(obj){
      vsip_malldestroy_f(obj->mU);
      vsip_malldestroy_f(obj->mV);
      vsip_valldestroy_f(obj->vd);
      vsip_valldestroy_f(obj->buf);
      vsip_valldestroy_vi(obj->vi);
      vsip_valldestroy_vi(obj->ui);
      if(obj->f) free(obj->f);
      if(obj->w) free(obj->w);
      if(obj->v) free(obj->v);
      if(obj->betaR) free(obj->betaR);
      if(obj->betaL) free(obj->betaL);
      if(obj->c_l) free(obj->c_l);
      if(obj->c_r) free(obj->c_r);
      if(obj->s_l) free(obj->s_l);
      if(obj->s_r) free(obj->s_r);
      free(obj);
   }
   return retval;
}
