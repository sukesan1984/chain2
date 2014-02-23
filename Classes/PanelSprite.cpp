//
//  PanelSprite.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/15.
//
//

#include "PanelSprite.h"

//PanelSprite::PanelSprite(Sprite* sprite){
//    this->sprite = sprite;
//    this->node->addChild(this->sprite);
//}

PanelSprite::PanelSprite(){
}

PanelSprite::~PanelSprite(){
}

PanelSprite* PanelSprite::createWithPanelType(int panelType){
    PanelSprite* sprite = new PanelSprite();
    sprite->panelType = panelType;
    std::string panelName;
    switch (panelType) {
        case 0:
            panelName = "black";
            break;
        case 1:
            panelName = "blue";
            break;
        case 2:
            panelName = "green";
            break;
        case 3:
            panelName = "purple";
            break;
        case 4:
            panelName = "red";
            break;
        case 5:
            panelName = "sky";
            break;
        case 6:
            panelName = "yellow";
            break;
        case 7:
            panelName = "white";
            break;
        default:
            break;
    }
    
    if(sprite && sprite->initWithSpriteFrameName((panelName + ".png").c_str())){
        sprite->cover = CoverSprite::createPanel();
        sprite->cover->setAnchorPoint(CCPoint(0, 0));
        sprite->addChild(sprite->cover);
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

//bool PanelSprite::initWithSpriteFrameName(const std::string &spriteFrameName){
//    return CCSprite::initWithSpriteFrameName(spriteFrameName);
//}

void PanelSprite::setSize(float size){
    this->setScale(size / SIZE);
}



void PanelSprite::setWillRemoved(bool willRemoved){
    this->willRemoved = willRemoved;
}

bool PanelSprite::getWillRemoved(){
    return this->willRemoved;
}

void PanelSprite::remove(){
    this->cover->removeFromParentAndCleanup(true);
    this->removeFromParentAndCleanup(true);
}

void PanelSprite::onTap(){
    CCLog("onTap");
    CCLog("x: %f, y: %f", this->getPosition().x, this->getPosition().y);
    this->startToRemove();
    CCPoint currentPos = this->getPosition();
    CCPoint pos = CCPoint(currentPos.x, currentPos.y);
    CCPoint pos2 = getIndex(pos);
    CCLog("x: %f, y: %f", pos2.x, pos2.y);
}

void PanelSprite::startToRemove(){
    this->cover->start();
}


//移動量に合わせて移動させて、deltaYを減らす。
bool PanelSprite::move(){
    if (deltaY >= -0.0001 && deltaY <= 0.0001 ){
        return false;
    }
    float currentY = this->getPositionY();
    this->setPositionY(currentY - velocity);
    deltaY -= velocity;
    return true;
}

void PanelSprite::setDeltaY(float deltaY){
    this->deltaY += deltaY;
    this->velocity = this->deltaY / 100 * 10;
}

void PanelSprite::update(){
    this->cover->update();
    if(this->cover->isFullCovered()){
        this->setWillRemoved(true);
    }
}

CCPoint PanelSprite::getIndex(CCPoint &panelPos){
    float posX = panelPos.x;
    float posY = panelPos.y;
    
    int x = int(posX) / int(FIELD_WIDTH_SIZE / FIELD_WIDTH_NUM);
    int y = int(posY) / int(FIELD_HEIGHT_SIZE / FIELD_HEIGHT_NUM);
    return CCPoint(x, y);
}

int PanelSprite::getPanelType(){
    return panelType;
}
