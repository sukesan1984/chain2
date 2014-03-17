#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "GameMainScene.h"
#include "GameOverScene.h"


// 美咲フォント（MISAKI_FONT）
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "misaki_gothic.ttf"
#else
#define MISAKI_FONT "MisakiGothic"
#endif
using namespace cocos2d;

class Tutorial : public cocos2d::CCLayer
{
private:
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void gameMainAction();
    CREATE_FUNC(Tutorial);
};

#endif // __TUTORIAL_SCENE_H__
