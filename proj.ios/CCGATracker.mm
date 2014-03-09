//
//  CCGATracker.m
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

#import "CCGATracker.h"
#import "GAI.h"
#import "GAIDictionaryBuilder.h"
#import "GAIFields.h"

//@implementation CCGATracker

//@end

void CCGATracker::sendView(const char *screen){
    NSLog(@"sendView");
    NSString* scr = [NSString stringWithUTF8String:screen];
    id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
    //[tracker sendView:scr];
    NSDictionary *params = [NSDictionary dictionaryWithObjectsAndKeys:
                            @"appview", kGAIHitType, scr, kGAIScreenName, nil];
    [tracker send:params];
}

void CCGATracker::sendEvent(const char* category, const char * action, const char *label, int value){
    NSString* cat = [NSString stringWithUTF8String:category];
    NSString* act = [NSString stringWithUTF8String:action];
    NSString* lab = [NSString stringWithUTF8String:label];
    NSNumber* val = [NSNumber numberWithInt:value];
    id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
    //[tracker sendEventWithCategory:cat withAction: act withLabel: lab withValue:val];
    [tracker send:[[GAIDictionaryBuilder createEventWithCategory:cat     // Event category (required)
                                                          action:act  // Event action (required)
                                                           label:lab          // Event label
                                                           value:val] build]];    // Event value
}




