//
//  CoverSprite.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#ifndef __Chain__CoverSprite__
#define __Chain__CoverSprite__

#include <iostream>
#include "cocos2d.h"
#include "Const.h"
#include "PanelTime.h"
using namespace cocos2d;

class CoverSprite : public CCSprite
{
    const int SIZE = 32;
    float scale = 0;
    float isMoving = false;
    float size;
    bool isFull = false;
public:
    CoverSprite();
    ~CoverSprite();
    static CoverSprite* createPanel();
    bool isFullCovered();
    void start();
    void reset();
    void update();
    void setTime(float time);
    
    CREATE_FUNC(CoverSprite);
};

#endif /* defined(__Chain__CoverSprite__) */