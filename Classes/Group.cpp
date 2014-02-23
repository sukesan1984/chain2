//
//  Group.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#include "Group.h"
Group::Group(int groupNumber){
    this->groupNumber = groupNumber;
    this->groupPanels = CCArray::create();
    this->groupPanels->retain();
}

Group::~Group(){
}

Group * Group::create(int groupNumber)
{
	Group * ret = new Group(groupNumber);
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
    int movingPanelsNum = 0;
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
    
    this->groupPanels->addObject((CCObject*) panel);
}

void Group::registerPanels(CCArray* groupPanels){
    PanelSprite* panelSprite = NULL;
    CCObject* targetObject = NULL;
    int movingPanelsNum = 0;
    if(groupPanels->count() == 0){
        return;
    }
    CCARRAY_FOREACH(groupPanels, targetObject){
        panelSprite = (PanelSprite*) targetObject;
        this->registerPanel(panelSprite);
    }
}

int Group::getGroupNumber(){
    return groupNumber;
}

int Group::getPanelType(){
    return panelType;
}

bool Group::willBeRemoved(){
    return groupPanels->count() >= 5;
}