/*
 *  vsip_svd_create_f.c
 *  VI_svd
 *
 *  Created by Randall Judd on 12/25/07.
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

#include"vsip_svdattributes_f.h"

vsip_sv_f *vsip_svd_create_f(
                             vsip_length m,
                             vsip_length n,
                             vsip_svd_uv usave,
                             vsip_svd_uv vsave){
   vsip_sv_f *obj = (vsip_sv_f*)malloc(sizeof(vsip_sv_f));
   int init = 0;
   if(obj){
      obj->U = NULL;
      obj->V = NULL;
      obj->M = m;
      obj->N = n;
      obj->L = (m >= n) ? n : m;
      obj->optU = usave;
      obj->optV = vsave;
      obj->A = &obj->Aval;
      /*if(usave == VSIP_SVD_UVPART)*/{
         obj->mU = vsip_mcreate_f(m,m,VSIP_ROW,VSIP_MEM_NONE);
         if(obj->mU){
         obj->U = obj->mU->block->array;
         } else {
            init++;
         }
      }
      /*if(vsave == VSIP_SVD_UVPART)*/{
         obj->mV = vsip_mcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
         if(obj->mV){
            obj->V = obj->mV->block->array;
         } else {
            init++;
         }
         
      }
      obj->buf = vsip_vcreate_f(((m>=n) ? m : n),VSIP_MEM_NONE);
      if(!obj->buf) init++;
      obj->vi = vsip_vcreate_vi(((m>=n) ? m : n),VSIP_MEM_NONE);
      if(!obj->vi) init++;
      obj->ui = vsip_vcreate_vi(((m>=n) ? m : n),VSIP_MEM_NONE);
      if(!obj->ui) init++;
      obj->v = (vsip_scalar_f*)malloc((m > n ? m:n) * sizeof(vsip_scalar_f));
      if(!obj->v) init++;
      obj->w = (vsip_scalar_f*)malloc((m > n ? m:n) * sizeof(vsip_scalar_f));
      if(!obj->w) init++;
      /* diagonal storage */
      obj->vd = vsip_vcreate_f((m<n ? m:n),VSIP_MEM_NONE);
      if(obj->vd)
         obj->d = obj->vd->block->array;
      else
         init++;
      /* super diagonal storage */
      obj->f = (vsip_scalar_f*)malloc((m < n ? m:n) * sizeof(vsip_scalar_f));
      if(!obj->d) init++;
      obj->betaR = (vsip_scalar_f*)malloc( obj->L * sizeof(vsip_scalar_f));
      if(!obj->betaR) init++;
      obj->betaL = (vsip_scalar_f*)malloc( obj->L * sizeof(vsip_scalar_f));
      if(!obj->betaL) init++;
      obj->c_l = (vsip_scalar_f*)malloc( obj->L * sizeof(vsip_scalar_f));
      if(!obj->c_l) init++;
      obj->s_l = (vsip_scalar_f*)malloc( obj->L * sizeof(vsip_scalar_f));
      if(!obj->s_l) init++;
      obj->c_r = (vsip_scalar_f*)malloc( obj->L * sizeof(vsip_scalar_f));
      if(!obj->c_r) init++;
      obj->s_r = (vsip_scalar_f*)malloc( obj->L * sizeof(vsip_scalar_f));
      if(!obj->s_r) init++;
      if(init){/* failed to malloc objects*/
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
         obj = (vsip_sv_f*)NULL;
      }
   }      
   return obj;
}
      

