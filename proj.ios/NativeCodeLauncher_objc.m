//
//  NativeCodeLauncher_objc.m
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

#import "NativeCodeLauncher_objc.h"

@implementation NativeCodeLauncher

// GameCenterへのログインチェック
+(bool)canUseGameCenter
{
    const float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    return version >= 4.1;
}


+(void)loginGameCenter
{
    if(![self canUseGameCenter]){
        return;
    }
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    [localPlayer authenticateWithCompletionHandler:^(NSError *error) {
        if(localPlayer.authenticated)
        {
            
        }
        else
        {
            
        }
    }];
}
// Leaderboardを開く
+(void)openRanking
{
    if(![self canUseGameCenter]){
        return;
    }
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if(localPlayer.authenticated)
    {
        AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
        
        GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc]init];
        leaderboardController.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardController.category  = Nil;
        leaderboardController.leaderboardDelegate = appController.viewController;
        
        [appController.viewController presentModalViewController:leaderboardController animated:YES];
    }
    else
    {
        NSString *alertTitle = @"";
        NSString *alertMessage = @"Game Centerへのログインが必要です。";
        UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:alertTitle message:alertMessage
                                                          delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
    }
}
// Leaderboardへの得点送信
+(void)postHighScore:(NSNumber *)kind score:(NSNumber *)score;
{
    if(![self canUseGameCenter]){
        return;
    }
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if([localPlayer isAuthenticated])
    {
        NSString *idName = @"";
        
        switch ([kind intValue]) {
            case 1:
                idName = @"Score";
                break;
            case 2:
                idName = @"Hit";
                break;
            default:
                break;
        }
        
        GKScore *gkScore = [[GKScore alloc]initWithCategory:idName];
        gkScore.value = [score longLongValue];
        gkScore.context = 1;
        gkScore.shouldSetDefaultLeaderboard = YES;
        [gkScore reportScoreWithCompletionHandler:^(NSError *error) {
            if(error)
            {
                NSLog(@"Error : %@",error);
            }
            else
            {
                NSLog(@"Sent highscore.");
            }
        }];
    }
    else
    {
        NSLog(@"Gamecenter not authenticated.");
    }
}

@end