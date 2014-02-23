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
    PanelSprite* panel;
    CCObject* targetObject;
    CCARRAY_FOREACH(this->panels, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel && panel->boundingBox().containsPoint(tap)){
            panel->onTap();
        }
    }
}

void Field::onTouchMove(CCTouch* touch){
    if(this->panels->isMoving()){
        return;
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
    panels->makeRemovedGroups();
    panels->addRemoveflag();
    
    CCLog("test");
}