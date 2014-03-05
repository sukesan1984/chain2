//
//  Gauge.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/05.
//
//

#include "Gauge.h"

Gauge::Gauge(){
    value = MAX_GAUGE_VALUE;
}

Gauge::~Gauge(){
}

Gauge* Gauge::createGauge(){
    Gauge* sprite = new Gauge();
    if(sprite && sprite->initWithSpriteFrameName("gauge.png")){
        Memori* memori = Memori::createMemori();
        memori->setAnchorPoint(CCPoint(0, 0));
        int baseZOrder = sprite->getZOrder();
        memori->setZOrder(baseZOrder - 1);
        sprite->addChild(memori);
        sprite->memori = memori;
        
        CCSprite* back = CCSprite::createWithSpriteFrameName("back_gauge.png");
        back->setAnchorPoint(CCPoint(0, 0));
        back->setZOrder(baseZOrder - 2);
        sprite->addChild(back);
        
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void Gauge::setGaugeScale(float scale){
    if(scale < 0){
        scale = 0;
    }
    if(scale > 1){
        scale = 1;
    }
    this->memori->setScaleX(scale);
}

void Gauge::reduce(int value){
    this->value -= value;
    if( this->value < 0 ){
        this->value = 0;
    }
    float scale = (float) this->value / MAX_GAUGE_VALUE;
    this->setGaugeScale(scale);
}

void Gauge::increase(int value) {
    this->value += value;
    if(this->value > MAX_GAUGE_VALUE){
        this->value = MAX_GAUGE_VALUE;
    }
    float scale = (float) this->value / MAX_GAUGE_VALUE;
    this->setGaugeScale(scale);
}