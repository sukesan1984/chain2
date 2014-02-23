//
//  FieldPanels.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#include "FieldPanels.h"

FieldPanels::FieldPanels(){
    groupManager = GroupManager::create();
    groupManager->retain();
    removedPanels = CCArray::create();
    removedPanels->retain();
}

FieldPanels::~FieldPanels(){
}

PanelSprite* FieldPanels::createPanel(int indexX, int indexY){
    int panelType = rand() % 6 + 1;
    PanelSprite* pSprite = PanelSprite::createWithPanelType(panelType);
    
    //float size = PANEL_SIZE * PANEL_SCALE;
    //float scale = PANEL_SCALE;
    float size = FIELD_SIZE / WIDTH;
    pSprite->setSize(size);
    pSprite->setAnchorPoint(CCPoint(0, 0));
    // position the sprite on the center of the screen
    pSprite->setPosition( CCPoint(size * indexX, size * indexY) );
    return pSprite;
}

void FieldPanels::initialize(CCNode* parentNode){
    this->parentNode = parentNode;
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            int panelType = rand() % 6 + 1;
            PanelSprite* panel = PanelSprite::createWithPanelType(panelType);
            int x = i * FIELD_SIZE / WIDTH;
            int y = j * FIELD_SIZE / HEIGHT;
            panel->setSize(FIELD_SIZE / WIDTH);
            panel->setPosition(CCPoint(x, y));
            panel->setAnchorPoint(CCPoint(0, 0));
            parentNode->addChild(panel);
            this->add(panel);
        }
    }
}

void FieldPanels::restockPanel(CCNode* parentNode){
    CCArray* removedPanels = this->getRemovedPanels();
    
    PanelSprite* removedPanel = NULL;
    CCObject* targetObject = NULL;
   
    CCDictionary* removedCount = CCDictionary::create();
    
    CCARRAY_FOREACH(removedPanels, targetObject){
        removedPanel = (PanelSprite*) targetObject;
        int y = HEIGHT;
        CCInteger* count = (CCInteger*) removedCount->objectForKey(removedPanel->getPosition().x);
        //既にその列が消えている場合は、追加する場所がn段上になる。
        if(count){
            y += count->getValue();
            removedCount->setObject(CCInteger::create(count->getValue()+1),removedPanel->getPosition().x);
            //その列がまだ消えていない場合は、dictionaryに追加
        } else {
            removedCount->setObject(CCInteger::create(1),removedPanel->getPosition().x);
        }
        
        PanelSprite* pSprite = this->createPanel(int(removedPanel->getPosition().x / (FIELD_SIZE / WIDTH)), y);
        this->add(pSprite);
        parentNode->addChild(pSprite);
    }
}

void FieldPanels::add(PanelSprite* panel){
    this->addObject((CCObject*) panel);
}

void FieldPanels::remove(int index){
    this->removeObjectAtIndex(index);
}

void FieldPanels::addRemoveflag(){
    CCArray* willBeRemovedPanels = this->groupManager->getRemovedPanels();
    PanelSprite* panel;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(willBeRemovedPanels, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->startToRemove();
    }
}

//消えたパネルの座標をセットする。
void FieldPanels::pushRemovedPanel(PanelSprite* panel){
    removedPanels->addObject(panel);
}

//消えたパネルを取得する。
CCArray* FieldPanels::getRemovedPanels(){
    return removedPanels;
}

FieldPanels* FieldPanels::create(){
    FieldPanels* pArray = new FieldPanels();
    if (pArray && pArray->init())
    {
        pArray->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pArray);
    }
    
    return pArray;
}

void FieldPanels::removePanels(){
    CCArray* removedIndexes = CCArray::create();
    
    PanelSprite *panel = NULL;
    CCObject* targetObject = NULL;
    
    int count = 0;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        
        //消えるパネルなら消す。
        if(panel->getWillRemoved()){
            panel->remove();
            this->pushRemovedPanel(panel);
            removedIndexes->addObject(CCInteger::create(count));
        }
        count++;
    }
    
    
    int maxIndex = removedIndexes->count();
    //上から順に消す
    for(int i = (maxIndex - 1); i >= 0; i--){
        CCInteger* index = (CCInteger*) removedIndexes->objectAtIndex(i);
        this->remove(index->getValue());
    }
}

void FieldPanels::movePanels(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    int movingPanelsNum = 0;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        if(panel->move()){
            movingPanelsNum++;
        }
    }
    if(movingPanelsNum == 0){
        moveState = false;
    }
}

void FieldPanels::makeRemovedGroups(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    this->groupManager->clearAll();
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite *) targetObject;
        CCAssert(panel != NULL, "cast failed");
        this->groupManager->addGroupToTable(panel);
    }
}



void FieldPanels::setMoves(){
    //if(moveState){
    //    return;
    //}
    CCArray* removedPanels = this->getRemovedPanels();
    PanelSprite* removedPanel = NULL;
    CCObject* targetObject1 = NULL;
    
    PanelSprite* panel = NULL;
    CCObject* targetObject2 = NULL;
    
    CCARRAY_FOREACH(this, targetObject1){
        panel = (PanelSprite*) targetObject1;
        CCARRAY_FOREACH(removedPanels, targetObject2){
            removedPanel = (PanelSprite*) targetObject2;
            
            if(removedPanel->getPosition().x == panel->getPosition().x && removedPanel->getPosition().y < panel->getPosition().y){
                moveState = true;
                panel->setDeltaY(FIELD_SIZE / WIDTH);
            }
        }
    }
}

void FieldPanels::update(){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    int movingPanelsNum = 0;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite*) targetObject;
        panel->update();
    }
    this->removePanels();
    this->restockPanel(this->parentNode);
    this->setMoves();
    this->movePanels();
    removedPanels->removeAllObjects();
}

bool FieldPanels::isMoving(){
    return this->moveState;
}