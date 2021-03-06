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
#include "FieldPanelsArray.h"
#include "Gauge.h"
using namespace cocos2d;

class FieldPanels : public CCArray{
    CCArray* removedPanels;
    bool moveState;
    PanelSprite* createPanel(int indexX, int indexY);
    CCNode* parentNode;
    PanelSprite* tapped;
    FieldPanelsArray* table;
    int totalRemovedPanelsNum;
    void group();
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
    bool hasRemovingPanels();
    void swap(PanelSprite* panel1, PanelSprite* panel2);
    
    int getHitNum();
    int getScore();
    int getTotalRemovedPanelsNum();
    
    FieldPanels();
    ~FieldPanels();
    void update();
    void setGauge(Gauge* gauge);
};


#endif /* defined(__Chain__FieldPanels__) */
