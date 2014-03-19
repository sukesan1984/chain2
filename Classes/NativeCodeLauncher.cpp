//
//  NativeCodeLauncher.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/17.
//
//

#include "NativeCodeLauncher.h"
#include "NativeCodeLauncherJni.h"
namespace Cocos2dExt
{
	// Androidでは実装しない
	void NativeCodeLauncher::loginGameCenter()
    {
        
    }
    void NativeCodeLauncher::openRanking()
    {
        showRankingJNI();
    }
    void NativeCodeLauncher::postHighScore(int kind,int score)
    {
        postHighScoreJNI(kind, score);
        
    }
}
