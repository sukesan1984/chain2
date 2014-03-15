#ifndef __CREDIT_SCENE_H__
#define __CREDIT_SCENE_H__

#include "cocos2d.h"
#include "TitleScene.h"


using namespace cocos2d;

class Credit : public cocos2d::CCLayer
{
private:
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    void titleAction();
    CREATE_FUNC(Credit);
};

#endif // __CREDIT_SCENE_H__
