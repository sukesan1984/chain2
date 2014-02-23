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
    int groupNumber;
    int panelType;
    CCArray* groupPanels;
    ~Group();
    Group(int groupNumber);
public:
    static Group* create(int groupNumber);
    CCArray* getGroupPanels();
    void registerPanel(PanelSprite* panel);
    void registerPanels(CCArray* groupPanels);
    int getGroupNumber();
    int getPanelType();
    bool willBeRemoved();
};

#endif /* defined(__Chain__Group__) */
