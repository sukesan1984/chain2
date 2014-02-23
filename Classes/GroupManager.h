//
//  GroupManager.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/19.
//
//

#ifndef __Chain__GroupManager__
#define __Chain__GroupManager__

#include <iostream>
#include "cocos2d.h"
#include "Group.h"
#include "GroupAddress.h"
#include "PanelSprite.h"

using namespace cocos2d;

class GroupManager : public CCNode{
    ~GroupManager();
    GroupManager();
    int groupNumber;
    //パネルのグループを登録する。
    GroupAddress* registerGroup(CCPoint &panelPos, Group* group);
    GroupAddress* registerGroupAddress(CCPoint &panelPos, GroupAddress* groupAddress);
    
    //その位置のgroupを返す。
    Group* searchGroup(CCPoint &panelPos);
    GroupAddress* searchGroupAddress(CCPoint &panelPos);
    
    //2つのgroupをマージして、新たなgroupを作って返す。
    GroupAddress* mergeGroups(GroupAddress* groupAddress1, GroupAddress* groupAddress2);
    
    // categorize
    GroupAddress* categorize(CCPoint &panelPos, PanelSprite* panelSprite, GroupAddress* selfGroupAddress);
    
    Group* createNewGroup();
    
    //table
    CCDictionary* table;
    
    //Groupsの参照
    CCArray* groups;
public:
    //PanelSpriteを登録する。
    void addGroupToTable(PanelSprite* panel);
    
    //削除され得るパネルを返す。
    CCArray* getRemovedPanels();
    
    
    CCPoint getIndex(CCPoint &panelPos);
    static GroupManager* create();
    void clearAll();
};

#endif /* defined(__Chain__GroupManager__) */
