//
//  Field.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#ifndef __Chain__Field__
#define __Chain__Field__

#include <iostream>
#include "cocos2d.h"
#include "PanelSprite.h"
#include "FieldPanels.h"
using namespace cocos2d;


class Field : public CCNode
{
    CCNode* parentNode;
    FieldPanels* panels;
    PanelSprite* tapped;
public:
    void initialize();
    void onTouchBegan(const CCPoint &tap);
    void onTouchMove(const CCPoint &tap);
    void onTouchEnded(CCTouch* touch);
    void update();
    void test();
    int getHitNum();
    int getScore();
    Field();
    ~Field();
};

#endif /* defined(__Chain__PanelSprite__) */

