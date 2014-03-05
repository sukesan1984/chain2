//
//  Memori.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/05.
//
//

#ifndef __chain__Memori__
#define __chain__Memori__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class Memori : public CCSprite {
    Memori();
    ~Memori();
public:
    static Memori* createMemori();
};


#endif /* defined(__chain__Memori__) */
