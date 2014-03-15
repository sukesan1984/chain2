//
//  FieldPanels.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#include "FieldPanels.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

FieldPanels::FieldPanels(){
    removedPanels = CCArray::create();
    removedPanels->retain();
    table = new FieldPanelsArray();
    totalRemovedPanelsNum = 0;
}

FieldPanels::~FieldPanels(){
    delete(table);
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

void FieldPanels::group(){
    if(this->isMoving()){
        return;
    }
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this, targetObject){
        panel = (PanelSprite *) targetObject;
        CCPoint index = panel->getIndex();
        table->registerPanel(index.x, index.y, panel);
    }
    table->group();
    this->addRemoveflag();
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
        
        CCPoint index = removedPanel->getIndex();
        
        CCInteger* count = (CCInteger*) removedCount->objectForKey(index.x);
        //既にその列が消えている場合は、追加する場所がn段上になる。
        if(count){
            y += count->getValue();
            removedCount->setObject(CCInteger::create(count->getValue()+1),index.x);
            //その列がまだ消えていない場合は、dictionaryに追加
        } else {
            removedCount->setObject(CCInteger::create(1),index.x);
        }
        
        PanelSprite* pSprite = this->createPanel(index.x, y);
        this->add(pSprite);
        parentNode->addChild(pSprite);
    }
}

void FieldPanels::add(PanelSprite* panel){
    this->addObject((CCObject*) panel);
}

void FieldPanels::remove(int index){
    PanelSprite* panel = (PanelSprite*) this->objectAtIndex(index);
    this->table->removePanel(panel);
    this->removeObjectAtIndex(index);
    totalRemovedPanelsNum++;
}

void FieldPanels::addRemoveflag(){
    CCArray* willBeRemovedPanels = this->table->getRemovedPanels();
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

PanelSprite* getPanelSprite(int x, int y){
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
            if(tapped == panel){
                this->tapped = NULL;
            }
                
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
    this->group();
}


void FieldPanels::setTappedPanel(PanelSprite *tapped){
    this->tapped = tapped;
}

PanelSprite* FieldPanels::getTappedPanel(){
    return this->tapped;
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
            
            //if(removedPanel->getPosition().x == panel->getPosition().x && removedPanel->getPosition().y < panel->getPosition().y){
            CCPoint indexRemoved = removedPanel->getIndex();
            CCPoint index = panel->getIndex();
            if(indexRemoved.x == index.x && indexRemoved.y < index.y){
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
    this->group();
    removedPanels->removeAllObjects();
}

bool FieldPanels::isMoving(){
    return this->moveState;
}

bool FieldPanels::hasRemovingPanels(){
    return this->table->hasRemovingPanels();
}

void FieldPanels::swap(PanelSprite *panel1, PanelSprite *panel2){
    if(panel1 == NULL || panel2 == NULL){
        return;
    }
    //後でリッチにしてもええかもな。
    CCPoint pos1 = panel1->getPosition();
    CCPoint pos2 = panel2->getPosition();
    
    panel1->setPosition(pos2);
    panel2->setPosition(pos1);
}

int FieldPanels::getHitNum(){
    return this->table->getHitNum();
}

int FieldPanels::getScore(){
    return this->table->getScore();
}

int FieldPanels::getTotalRemovedPanelsNum(){
    return this->totalRemovedPanelsNum;
}

void FieldPanels::setGauge(Gauge *gauge){
    this->table->setGauge(gauge);
}