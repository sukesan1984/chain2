//
//  FieldPanels.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#ifndef __Chain__FieldPanels__
#define __Chain__FieldPanels__

#include <iostream>
#include "PanelSprite.h"
#include "cocos2d.h"
#include "Const.h"
#include "GroupManager.h"
using namespace cocos2d;

class FieldPanels : public CCArray{
    const int WIDTH = FIELD_WIDTH_NUM;
    const int HEIGHT = FIELD_WIDTH_NUM;
    const int FIELD_SIZE = FIELD_WIDTH_SIZE;
    CCArray* removedPanels;
    bool moveState = false;
    PanelSprite* createPanel(int indexX, int indexY);
    CCNode* parentNode;
    GroupManager* groupManager;
    PanelSprite* tapped;
public:
    void initialize(CCNode* parentNode); //明示的に初期化処理を呼ぶ。
    void restockPanel(CCNode* parentNode);
    void add(PanelSprite* panel); //パネルを追加する。
    void remove(int index); //indexのパネルを消す。
    void addRemoveflag(); //消え得るパネルをフラグ立てる
    void pushRemovedPanel(PanelSprite* panel);
    CCArray* getRemovedPanels();
    void removePanels();
    void setMoves();
    void movePanels();
    
    void makeRemovedGroups();
    
    void setTappedPanel(PanelSprite* tapped);
    PanelSprite* getTappedPanel();
    
    static FieldPanels* create();
    bool isMoving();
    void swap(PanelSprite* panel1, PanelSprite* panel2);
    
    FieldPanels();
    ~FieldPanels();
    void update();
};


#endif /* defined(__Chain__FieldPanels__) */
