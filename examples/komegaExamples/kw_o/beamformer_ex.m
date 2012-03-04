//
//  main.m
//  param
//
//  Created by RANDALL JUDD on 2/5/12.
//  Copyright (c) 2012 Independent Consultant. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <jvsipF/vsip.h>
#import "ts.h"
#import "kw.h"
NSMutableDictionary *param(NSString*);

int main (int argc, const char * argv[])
{
   @autoreleasepool {
      NSString *paramFile = [[NSString alloc] initWithCString:argv[1] encoding:1];
      NSMutableDictionary *myParams=param(paramFile);
      Sim_ts *ts = [[Sim_ts alloc] initWithParams:myParams];
      Kw *kw = [[Kw alloc] initWithParams:myParams];
      int i;
      [kw zero];
      vsip_mview_f *dtaIn = [ts instance];
      vsip_mview_f *gramOut = [kw instance];
      for(i=0; i<[[myParams objectForKey:@"Navg"] intValue]; i++){
         [ts zero];         
         [ts nb_sim];
         [ts noise_sim];
         [kw kw:dtaIn];
      }
      for(i=0; i<vsip_mgetrowlength_f(gramOut); i++)
      {/* move zero to middle */
         vsip_vview_f *v = vsip_mcolview_f(gramOut, i);
         vsip_vfreqswap_f(v);
         vsip_vdestroy_f(v);
      }
      {/* massage the data for plot*/
         vsip_scalar_f max = vsip_mmaxval_f(gramOut, NULL),min;
         vsip_scalar_f avg = vsip_mmeanval_f(gramOut);
         vsip_mclip_f(gramOut,0.0, max, avg/100000.0, max, gramOut);
         vsip_mlog10_f(gramOut,gramOut);
         min = -vsip_mminval_f(gramOut, NULL);
         vsip_smadd_f(min, gramOut, gramOut);
         max = vsip_mmaxval_f(gramOut, NULL);
         vsip_smmul_f(1.0/max, gramOut, gramOut);
      }
      { /* output data and plot with octave */
         FILE *fptr = fopen("gramOut","w");
         size_t size = vsip_mgetrowlength_f(gramOut) * vsip_mgetcollength_f(gramOut);
         vsip_scalar_f *out = (vsip_scalar_f*)malloc(size * sizeof(vsip_scalar_f));
         vsip_mcopyto_user_f(gramOut, VSIP_COL, out);
         fwrite(out,size,sizeof(vsip_scalar_f),fptr);
         fclose(fptr);
         free(out);
      }
      [ts release];
      [kw release];
      NSLog(@"%@",myParams);
      [paramFile release];
   }
   return 0;
}

