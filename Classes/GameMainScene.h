#ifndef __GAMEMAIN_SCENE_H__
#define __GAMEMAIN_SCENE_H__

#include "cocos2d.h"
#include "Field.h"
#include "CoverSprite.h"
#include "Const.h"
#include "Gauge.h"
#include "GameOverScene.h"
#include "PanelTime.h"
// 美咲フォント（MISAKI_FONT）
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define MISAKI_FONT "misaki_gothic.ttf"
#else
#define MISAKI_FONT "MisakiGothic"
#endif

class GameMain : public cocos2d::CCLayer
{
private:
    Field* field;
    CCLabelTTF* hitNumLabel;
    CCLabelTTF* scoreLabel;
    CCLabelTTF* levelLabel;
    Gauge* gauge;
    bool goneToGameOver;
    int passedframe;
    int beforeTotalRemovedNum;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* event);
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
    
    void update(float dt);
    
    void test(CCObject* pSender);
    
    void gotoGameOverScene();
};

#endif // __GAMEMAIN_SCENE_H__
