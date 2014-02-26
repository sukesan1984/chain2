//
//  FieldPanelsArray.h
//  chain
//
//  Created by Kosuke Takami on 2014/02/26.
//
//

#ifndef __chain__FieldPanelsArray__
#define __chain__FieldPanelsArray__

#include <iostream>
#include "PanelSprite.h"
#include "Group.h"
#include "cocos2d.h"

using namespace cocos2d;

class FieldPanelsArray {
    PanelSprite* table[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM];
    CCArray* groups;
    
    //既にgroup化したらflag立てる
    bool checkTable[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM];
    
    // tableを削除する
    void removeAllPanels();
    
    // checkTableをリセットする。
    void resetGroupCheckTable();
    CCArray* getGroups();
public:
    // tableにpanelを登録するやつ。
    void registerPanel(int x, int y, PanelSprite* panel);
    
    // x, yの位置のパネルを削除する。
    void remove(int x, int y);
    // indexで引くやつ
    PanelSprite* getPanel(int x, int y);
    
    void group();
    Group* group(int x, int y, Group* mapw[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]);
    CCArray* getRemovedPanels();
    
    //
    void removePanel(PanelSprite* panel);
    // groupをGroupsから削除する。
    void removeGroup(Group* group);
    
    FieldPanelsArray();
    ~FieldPanelsArray();
};

#endif /* defined(__chain__FieldPanelsArray__) */
