//
//  NativeCodeLauncher_objc.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

#import <Foundation/Foundation.h>
#import <GameKit/GKLocalPlayer.h>
#import <GameKit/GKScore.h>
#import <GameKit/GKLeaderboardViewController.h>
#include "AppController.h"

@interface NativeCodeLauncher : NSObject

// GameCenter
+(bool)canUseGameCenter;
+(void)loginGameCenter;
+(void)openRanking;
+(void)postHighScore:(NSNumber *)kind score:(NSNumber *)score;

@end
