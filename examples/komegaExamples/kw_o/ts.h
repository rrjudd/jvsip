//
//  Sim_ts.h
//  param
//
//  Created by RANDALL JUDD on 2/7/12.
//  Copyright (c) 2012 JVSIP, Independent Consultant. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <jvsipF/vsip.h>

@interface Sim_ts : NSObject
{
   vsip_length Nsim_freqs;
   vsip_length Nsens;
   vsip_length Nsim_noise;
   vsip_length Nts;
   vsip_scalar_f Fs;
   vsip_fir_f *fir;
   vsip_vview_f *noise;
   vsip_vview_f *bl_noise;
   vsip_randstate *rand;
   vsip_vview_f *t;
   vsip_vview_f *t_dt;
   vsip_mview_f *m_data;
   vsip_vview_f *v_data;
   vsip_scalar_f d_t;
   NSMutableArray *sim_freqs;
   NSMutableArray *sim_bearings;
}

-(id) initWithParams:(NSMutableDictionary*)params;

-(void) noise_sim;

-(void) nb_sim;

-(void) zero;

-(vsip_mview_f*) instance;

@end
