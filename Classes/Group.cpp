//
//  Group.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#include "Group.h"
Group::Group(){
    addedNewone = false;
    this->groupPanels = CCArray::create();
    this->groupPanels->retain();
}

Group::~Group(){
}

Group * Group::create()
{
	Group * ret = new Group();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

CCArray* Group::getGroupPanels(){
    return groupPanels;
}

void Group::registerPanel(PanelSprite* panel){
    //無限に登録されないように
    PanelSprite* panelSprite = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->groupPanels, targetObject){
        panelSprite = (PanelSprite*) targetObject;
        if(panelSprite == panel){
            //既に登録されていたら何もしない。
            return;
        }
    }
    if(this->groupPanels->count() == 0){
        this->panelType = panel->getPanelType();
    }
    
    this->setAddedNewone(true);
    this->groupPanels->addObject((CCObject*) panel);
}

void Group::registerPanels(CCArray* gPanels){
    PanelSprite* panelSprite = NULL;
    CCObject* targetObject = NULL;
    if(gPanels->count() == 0){
        return;
    }
    CCARRAY_FOREACH(gPanels, targetObject){
        panelSprite = (PanelSprite*) targetObject;
        this->registerPanel(panelSprite);
    }
}

void Group::reset(){
    PanelSprite* panelSprite = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(groupPanels, targetObject){
        panelSprite = (PanelSprite*) targetObject;
        panelSprite->reset();
    }
}

int Group::getPanelType(){
    return panelType;
}

bool Group::willBeRemoved(){
    return groupPanels->count() >= 5;
}

bool Group::exist(PanelSprite *panel){
    PanelSprite* panelSprite = NULL;
    CCObject* targetObject = NULL;
    
    CCARRAY_FOREACH(groupPanels, targetObject){
        panelSprite = (PanelSprite*) targetObject;
        if(panelSprite == panel){
            return true;
        }
    }
    return false;
}

void Group::setAddedNewone(bool addedNewone){
    this->addedNewone = addedNewone;
}

bool Group::needToReset(){
    return this->addedNewone;
}

int Group::removePanel(PanelSprite* panel) {
    this->groupPanels->removeObject((CCObject*) panel);
    return this->groupPanels->count();
}

int Group::getGroupPanelsNum(){
    return this->groupPanels->count();
}