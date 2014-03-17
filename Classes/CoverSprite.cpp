//
//  CoverSprite.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/16.
//
//

#include "CoverSprite.h"

CoverSprite::CoverSprite(){
    scale = 0;
    isMoving = false;
    isFull = false;
}

CoverSprite::~CoverSprite(){
}

CoverSprite* CoverSprite::createPanel(){
    CoverSprite* sprite = new CoverSprite();
    
    if(sprite && sprite->initWithSpriteFrameName("white.png")){
        sprite->autorelease();
        sprite->setVisible(false);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

bool CoverSprite::isFullCovered(){
    return isFull;
}

void CoverSprite::start(){
    this->isMoving = true;
    this->setVisible(true);
}

void CoverSprite::reset(){
    this->scale = 0;
}

void CoverSprite::update(){
    if(!this->isMoving){
        return;
    }
    if(scale >= 1.0){
        this->isMoving = false;
        this->setScaleY(1.0);
        this->isFull = true;
        return;
    }
    this->setScaleY(scale);
    scale += 1 / PanelTime::instance().getPanelRemoveTime() / 60;
}