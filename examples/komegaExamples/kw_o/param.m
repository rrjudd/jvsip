//
//  main.m
//  param
//
//  Created by RANDALL JUDD on 2/5/12.
//  Copyright (c) 2012 JVSIP, Independent Consultant. All rights reserved.
//

#import <Foundation/Foundation.h>
NSMutableDictionary *param(NSString*);

NSMutableDictionary *param (NSString *paramFile)
{
   NSString *file = [[NSString alloc] initWithContentsOfFile:paramFile encoding:1 error:NULL];
   NSArray *lines=[file componentsSeparatedByString:@"\n"];
   NSCharacterSet *sepChars = [NSCharacterSet characterSetWithCharactersInString:@" \n"];
   int i,j;
   NSMutableArray *freqs = [[NSMutableArray alloc] initWithCapacity:1];
   NSMutableArray *bearings=[[NSMutableArray alloc] initWithCapacity:1];
   NSMutableDictionary *params = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                  [NSNumber numberWithFloat:0.0], @"c",
                                  [NSNumber numberWithFloat:0.0], @"Fs",
                                  [NSNumber numberWithInt:0], @"Nts",
                                  [NSNumber numberWithFloat:0], @"Dsens",
                                  [NSNumber numberWithInt:0], @"Nsens",
                                  [NSNumber numberWithInt:0], @"Navg",
                                  [NSNumber numberWithInt:0], @"Nsim",
                                  freqs,@"Freqs",
                                  bearings,@"Bearings",
                                  [NSNumber numberWithInt:0], @"Nnoise",
                                  nil];
   i=0;
   NSString *l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   NSString *val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithFloat:[val floatValue]] forKey:@"c"];
   
   i++;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithFloat:[val floatValue]] forKey:@"Fs"];
   
   i++;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithInt:[val intValue]] forKey:@"Nts"];
   
   i++;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithFloat:[val floatValue]] forKey:@"Dsens"];
   
   i++;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithInt:[val intValue]] forKey:@"Nsens"];
   
   i++;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithInt:[val intValue]] forKey:@"Navg"];
   
   i++;
   int Nsim=0;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   Nsim=[val intValue];
   [params setValue:[NSNumber numberWithInt:Nsim] forKey:@"Nsim"];
   
   for(j=0; j<Nsim; j++){
      i++;
      l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
      val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
      [freqs addObject:[NSNumber numberWithFloat:[val floatValue]]];
   }
   for(j=0; j<Nsim; j++){
      i++;
      l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
      val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
      [bearings addObject:[NSNumber numberWithFloat:[val floatValue]]];
   }
   i++;
   l = [[[lines objectAtIndex:i] componentsSeparatedByString:@"*"] objectAtIndex:1];
   val=[[l componentsSeparatedByCharactersInSet:sepChars] objectAtIndex:0];
   [params setValue:[NSNumber numberWithInt:[val intValue]] forKey:@"Nnoise"];
   [file release];
   [freqs release];
   [bearings release];
   return params;
}

