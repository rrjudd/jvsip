//
//  Kw.m
//  param
//
//  Created by RANDALL JUDD on 2/8/12.
//  Copyright (c) 2012 JVSIP, Independent Consultant. All rights reserved.
//

#import "kw.h"

@implementation Kw

-(id) init
{
   if((self = [super init]))
   {
      Navg = 0;
      Nfreq = 0;
      cm_freq = NULL;
      rm_freq = NULL;
      m_gram = NULL;
      rcfftm = NULL;
      ccfftm = NULL;
      ts_taper = NULL;
      array_taper = NULL;
   }
   return self;
}

-(id) initWithParams:(NSMutableDictionary *)params
{
   vsip_init((void*)0);
   vsip_memory_hint mem=VSIP_MEM_NONE;
   vsip_major col = VSIP_COL;
   vsip_major row = VSIP_ROW;
   vsip_fft_dir fftfwd=VSIP_FFT_FWD;
   vsip_length Nsens=(vsip_length)[[params objectForKey:@"Nsens"] intValue];
   vsip_length Nts = (vsip_length)[[params objectForKey:@"Nts"] intValue];
   if((self = [self init])){
      Navg = (vsip_length) [[params objectForKey:@"Navg"] intValue];
      Nfreq = Nts/2 + 1;
      cm_freq=vsip_cmcreate_f(Nsens,Nfreq,col,mem);
      rm_freq=vsip_mcreate_f(Nsens,Nts,row,mem);
      m_gram=vsip_mcreate_f(Nsens,Nfreq,col,mem);
      rcfftm=vsip_rcfftmop_create_f(Nsens,Nts,1,row,0,0);
      ccfftm=vsip_ccfftmip_create_f(Nsens,Nfreq,fftfwd,1,col,0,0);
      ts_taper=vsip_vcreate_hanning_f(Nts, mem);
      array_taper=vsip_vcreate_hanning_f(Nsens,0);
   }
   return self;
}

-(void) dealloc
{
   if(cm_freq) vsip_cmalldestroy_f(cm_freq);
   if(rm_freq) vsip_malldestroy_f(rm_freq);
   if(m_gram) vsip_malldestroy_f(m_gram);
   if(ts_taper) vsip_valldestroy_f(ts_taper);
   if(array_taper) vsip_valldestroy_f(array_taper);
   if(rcfftm) vsip_fftm_destroy_f(rcfftm);
   if(ccfftm) vsip_fftm_destroy_f(ccfftm);
   vsip_finalize((void*)0);
   [super dealloc];
}

-(void) zero
{
   vsip_mfill_f(0.0, m_gram);
}

-(void) kw:(vsip_mview_f*)m_data
{
   vsip_major row = VSIP_ROW;
   vsip_major col = VSIP_COL;
   vsip_vmmul_f(ts_taper, m_data, row, m_data);
   vsip_vmmul_f(array_taper,m_data,col,m_data);
   vsip_rcfftmop_f(rcfftm, m_data, cm_freq);
   vsip_ccfftmip_f(ccfftm, cm_freq);
   vsip_mcmagsq_f(cm_freq, rm_freq);
   vsip_smmul_f(1.0/(vsip_scalar_f)Navg,rm_freq,rm_freq);
   vsip_madd_f(rm_freq,m_gram,m_gram);
}

-(vsip_mview_f*) instance
{
   return m_gram;
}


@end
