//
//  PanelSprite.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/15.
//
//

#ifndef __Chain__PanelSprite__
#define __Chain__PanelSprite__

#include <iostream>
#include "cocos2d.h"
#include "CoverSprite.h"
#include "Const.h"
using namespace cocos2d;

class PanelSprite : public CCSprite
{
    const int SIZE = PANEL_SIZE;
    CoverSprite* cover;
    bool willRemoved = false;
    float deltaY = 0;
    float velocity = 0;
    int panelType;
    
public:
    PanelSprite();
    ~PanelSprite();
    static PanelSprite* createWithPanelType(int panelType);
    
    void setWillRemoved(bool willRemoved);
    bool getWillRemoved();
    void remove();
    
    void setSize(float size);
    void onTap();
    
    void startToRemove();
    void reset();
    
    bool move();
    void setDeltaY(float deltaY);
    void update();
    CCPoint getIndex();
    int getPanelType();
};

#endif /* defined(__Chain__PanelSprite__) */
