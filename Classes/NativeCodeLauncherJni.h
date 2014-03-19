//
//  NativeCodeLauncherJni.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/19.
//
//

#ifndef __chain__NativeCodeLauncherJni__
#define __chain__NativeCodeLauncherJni__

#include <iostream>

#include <jni.h>

extern "C"
{
    extern void showRankingJNI();
    extern void postHighScoreJNI(int kind, int score);
}
#endif /* defined(__chain__NativeCodeLauncherJni__) */
