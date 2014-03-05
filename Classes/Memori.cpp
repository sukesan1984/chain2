//
//  Memori.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/05.
//
//

#include "Memori.h"


Memori::Memori(){
}

Memori::~Memori(){
}

Memori* Memori::createMemori(){
    Memori* sprite = new Memori();
    if(sprite && sprite->initWithSpriteFrameName("memori.png")){
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}