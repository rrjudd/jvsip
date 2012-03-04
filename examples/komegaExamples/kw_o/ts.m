//
//  Sim_ts.m
//  param
//
//  Created by RANDALL JUDD on 2/7/12.
//  Copyright (c) 2012 JVSIP, Independent Consultant. All rights reserved.
//

#import "ts.h"

@implementation Sim_ts

-(id) init
{
   if((self = [super init]))
   {
      Nsim_freqs = 0;
      Nsens = 0;
      Nsim_noise = 0;
      Nts = 0;
      Fs=0.0;
      d_t=0.0;
      fir=NULL;
      noise=NULL;
      bl_noise=NULL;
      rand=NULL;
      t=NULL;
      t_dt = NULL;
      m_data=NULL;
      v_data=NULL;
      sim_freqs = NULL;
      sim_bearings = NULL;
   }
   return self;
}

-(id) initWithParams:params
{
   if((self = [self init]))
   {
      vsip_init((void*)0);
      vsip_scalar_f Dsens = (vsip_scalar_f)[[params objectForKey:@"Dsens"] floatValue];
      vsip_scalar_f c = (vsip_scalar_f) [[params objectForKey:@"c"] floatValue];
      Nsim_freqs = (vsip_length)[[params objectForKey:@"Nsim"] intValue];
      Nsens = (vsip_length)[[params objectForKey:@"Nsens"] intValue];
      Nsim_noise = (vsip_length)[[params objectForKey:@"Nnoise"] intValue];
      Nts = (vsip_length) [[params objectForKey:@"Nts"] intValue];
      Fs = (vsip_scalar_f) [[params objectForKey:@"Fs"] floatValue];
      vsip_length L          = (vsip_length)(2 * Fs/(Nsens * Dsens/c) + Nts + 1);
      vsip_vview_f *kernel = vsip_vcreate_kaiser_f(6,1,0);
      noise = vsip_vcreate_f(2*L,VSIP_MEM_NONE);
      bl_noise = vsip_vcreate_f(L,VSIP_MEM_NONE);
      rand  = vsip_randcreate(7,1,1,VSIP_PRNG);
      t = vsip_vcreate_f(Nts,VSIP_MEM_NONE);
      vsip_vramp_f(0,1.0/Fs,t); //vector of sample times
      t_dt = vsip_vcreate_f(Nts,VSIP_MEM_NONE);
      m_data = vsip_mcreate_f(Nsens,Nts,VSIP_ROW,VSIP_MEM_NONE);
      v_data = vsip_mrowview_f(m_data,0);
      d_t = Dsens/c; //travel time at end-fire between sensors
      sim_freqs = [params objectForKey:@"Freqs"];
      sim_bearings = [params objectForKey:@"Bearings"];
      if(kernel)
         fir   = vsip_fir_create_f(kernel, VSIP_NONSYM, 2*L, 2, VSIP_STATE_SAVE, 0,0);
      vsip_valldestroy_f(kernel);
   }
   return self;
}

-(void) dealloc
{
   if(noise) vsip_valldestroy_f(noise);
   if(bl_noise) vsip_valldestroy_f(bl_noise);
   if(rand) vsip_randdestroy(rand);
   if(t) vsip_valldestroy_f(t);
   if(t_dt) vsip_valldestroy_f(t_dt);
   if(v_data) vsip_vdestroy_f(v_data);
   if(m_data) vsip_malldestroy_f(m_data);
   vsip_finalize((void*)0);
   [super dealloc];
}

static void VU_rowview(vsip_vview_f *v, vsip_mview_f *m, vsip_index i){
   vsip_mattr_f mattr;
   vsip_vattr_f vattr;
   vsip_mgetattrib_f(m,&mattr);
   vsip_vgetattrib_f(v,&vattr);
   vattr.offset = mattr.offset + i * mattr.col_stride;
   vattr.length = mattr.row_length;
   vattr.stride = mattr.row_stride;
   vsip_vputattrib_f(v,&vattr);
}

-(void) noise_sim
{
   int i,j;
   vsip_scalar_f D_t= d_t * Fs; 
   vsip_scalar_f o_0    = D_t * Nsens + 1;
   vsip_scalar_f a_stp = M_PI/(vsip_scalar_f)Nsim_noise;
   vsip_vattr_f bl_attr;
   vsip_vgetattrib_f(bl_noise, &bl_attr);
   for(j=0; j<Nsim_noise; j++){
      vsip_scalar_f a_crct = cos((float)j * a_stp);
      vsip_vrandn_f(rand,noise);
      vsip_firflt_f(fir,noise,bl_noise);
      vsip_svmul_f(12.0/(float)(Nsim_noise),bl_noise,bl_noise);
      vsip_vputlength_f(bl_noise,Nts);
      for(i=0; i<Nsens; i++){
         vsip_vputoffset_f(bl_noise,(vsip_offset)(o_0 + i * D_t * a_crct));
         VU_rowview(v_data,m_data,i);
         vsip_vadd_f(bl_noise,v_data,v_data);
         vsip_vputattrib_f(bl_noise,&bl_attr);
      }
   }
   vsip_smadd_f(-vsip_mmeanval_f(m_data),m_data,m_data);
}
-(void) nb_sim
{
   vsip_index i,j;
   for(i=0; i<Nsim_freqs; i++){
      vsip_scalar_f f = (vsip_scalar_f)[[sim_freqs objectAtIndex:i] floatValue];
      vsip_scalar_f b = d_t * cos((vsip_scalar_f)[[sim_bearings objectAtIndex:i] floatValue] * M_PI/180.0);
      for(j=0; j<Nsens; j++){
         vsip_scalar_f dt = (vsip_scalar_f)j * b;
         vsip_svadd_f(dt, t, t_dt);
         vsip_svmul_f(2 * M_PI * f, t_dt, t_dt);
         vsip_vcos_f(t_dt,t_dt);
         vsip_svmul_f(3.0,t_dt,t_dt);
         VU_rowview(v_data,m_data,j);
         vsip_vadd_f(t_dt,v_data,v_data);
      }
   }
   
}
-(void) zero
{
   vsip_mfill_f(0.0,m_data);
}
-(vsip_mview_f*) instance
{
   return m_data;
}



@end
