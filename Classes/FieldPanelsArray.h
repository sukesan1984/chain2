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
#include "Score.h"

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
    //int hitNum;
    
    //int score;
public:
    // tableにpanelを登録するやつ。
    void registerPanel(int x, int y, PanelSprite* panel);
    
    // x, yの位置のパネルを削除する。
    void remove(int x, int y);
    // indexで引くやつ
    PanelSprite* getPanel(int x, int y);
    
    void group();
    void groupFromCurrentGroups(Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]);
    void group(Group* group, Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]);
    Group* group(int x, int y, Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]);
    CCArray* getRemovedPanels();
    
    bool hasRemovingPanels();
    
    // x, yのパネルが属しているグループ
    Group* getBelongingGroup(int x, int y);
    
    void removePanel(PanelSprite* panel);
    // groupをGroupsから削除する。
    void removeGroup(Group* group);
    
    int getHitNum();
    int getScore();
    
    int calcScore();
    
    FieldPanelsArray();
    ~FieldPanelsArray();
};

#endif /* defined(__chain__FieldPanelsArray__) */
