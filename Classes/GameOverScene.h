#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "GameMainScene.h"

using namespace cocos2d;

class GameOver : public cocos2d::CCLayer
{
private:
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    void gameMainAction();
    void rankingAction();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameOver);
};

#endif // __GAMEOVER_SCENE_H__
