//
//  Field.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#include "Field.h"

Field::Field(){
}

Field::~Field(){
}

void Field::initialize(){
    panels = FieldPanels::create();
    panels->retain();
    panels->initialize(this);
}

void Field::onTouchBegan(const CCPoint &tap){
    //if(this->panels->isMoving()){
    //return;
    //}
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel && panel->boundingBox().containsPoint(tap)){
            panels->setTappedPanel(panel);
            //panel->onTap();
        }
    }
}

void Field::onTouchMove(const CCPoint &tap){
    //途中でパネルが消えても何もしない。
    if(this->panels->isMoving()){
        return;
    }
    if(tapped != NULL){
        CCLog("tapped is not NULL");
    }
    
    //tappedよりも20ピクセルか移動したときは、パネル交換
    PanelSprite* tapped = panels->getTappedPanel();
    if(tapped == NULL){
        return;
    }
    
    if(pow(tapped->getPositionX() - tap.x, 2)+ pow(tapped->getPositionY() - tap.y, 2) < 400){
        return;
    }
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(this->panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel && panel->boundingBox().containsPoint(tap)){
            panels->swap(tapped, panel);
            //this->test();
        }
    }
}

void Field::onTouchEnded(CCTouch* touch){
    if(this->panels->isMoving()){
        return;
    }
}

void Field::update(){
    panels->update();
}

void Field::test(){
    //panels->makeRemovedGroups();
    //panels->addRemoveflag();
    
    CCLog("test");
}