/*
 *  vsip_svd_destroy_d.c
 *  svd_test
 *
 *  Created by Randall Judd on 9/11/08.
 *  Copyright 2008 Home. All rights reserved.
 *
 */

#include<vsip.h>
#include"vsip_svdattributes_d.h"

int vsip_svd_destroy_d(vsip_sv_d *obj){
   int retval = 0;
   if(obj){
      vsip_malldestroy_d(obj->mU);
      vsip_malldestroy_d(obj->mV);
      vsip_valldestroy_d(obj->vd);
      vsip_valldestroy_d(obj->buf);
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
