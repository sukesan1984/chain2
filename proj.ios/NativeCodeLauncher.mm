//
//  NativeCodeLauncher.m
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//

#include "NativeCodeLauncher.h"
#include "NativeCodeLauncher_objc.h"

// GameCenterにログイン
static void static_loginGameCenter()
{
    [NativeCodeLauncher loginGameCenter];
}
// Leaderboard表示
static void static_openRanking()
{
    [NativeCodeLauncher openRanking];
}
// ハイスコアを送信
static void static_postHighScore(int kind,int score)
{
    [NativeCodeLauncher postHighScore:[NSNumber numberWithInt:kind]
                                score:[NSNumber numberWithInt:score]];
}

namespace Cocos2dExt
{
	// GameCenter
    void NativeCodeLauncher::loginGameCenter()
    {
        static_loginGameCenter();
    }
    void NativeCodeLauncher::openRanking()
    {
        static_openRanking();
    }
    void NativeCodeLauncher::postHighScore(int kind, int score)
    {
        static_postHighScore( kind, score);
    }
}