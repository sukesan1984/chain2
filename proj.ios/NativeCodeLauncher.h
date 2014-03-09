//
//  NativeCodeLauncher.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/09.
//
//
#ifndef _NATIVE_CODE_LAUNCHER_H_
#define _NATIVE_CODE_LAUNCHER_H_

#include <stddef.h>

namespace Cocos2dExt {
    class NativeCodeLauncher
    {
    public:
        //GameCenter
        static void loginGameCenter();
        static void openRanking();
        static void postHighScore(int kind, int score);
    };
}

#endif // _NATIVE_CODE_LAUNCHER_H_