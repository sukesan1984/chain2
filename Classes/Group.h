//
//  Group.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#ifndef __Chain__Group__
#define __Chain__Group__

#include <iostream>
#include "cocos2d.h"
#include "PanelSprite.h"

using namespace cocos2d;
class Group : public CCNode{
    int panelType;
    CCArray* groupPanels;
    ~Group();
    Group();
public:
    static Group* create();
    CCArray* getGroupPanels();
    void registerPanel(PanelSprite* panel);
    void registerPanels(CCArray* groupPanels);
    void reset();
    int getGroupNumber();
    int getPanelType();
    bool willBeRemoved();
    bool exist(PanelSprite* panel);
    //残数を返す。
    int removePanel(PanelSprite* panel);
};

#endif /* defined(__Chain__Group__) */
