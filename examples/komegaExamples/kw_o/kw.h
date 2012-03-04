//
//  Kw.h
//  param
//
//  Created by RANDALL JUDD on 2/8/12.
//  Copyright (c) 2012 JVSIP, Independent Consultant. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <jvsipF/vsip.h>

@interface Kw : NSObject
{
   vsip_length Navg;
   vsip_length Nfreq;
   vsip_cmview_f *cm_freq;
   vsip_mview_f *rm_freq;
   vsip_mview_f *m_gram;
   vsip_fftm_f *rcfftm;
   vsip_fftm_f *ccfftm;
   vsip_vview_f *ts_taper;
   vsip_vview_f *array_taper;
   
}

-(id) initWithParams:(NSMutableDictionary*) params;

-(void) zero;
-(void) kw:(vsip_mview_f*) m_data;
-(vsip_mview_f*) instance;

@end
