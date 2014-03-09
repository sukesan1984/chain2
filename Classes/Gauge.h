//
//  Gauge.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/05.
//
//

#ifndef __chain__Gauge__
#define __chain__Gauge__

#include <iostream>
#include "cocos2d.h"
#include "Const.h"
#include "Memori.h"
using namespace cocos2d;

class Gauge : public CCSprite {
    Gauge();
    ~Gauge();
    Memori* memori;
    int value;
    int time;
    void setGaugeScale(float scale);
    int count;
public:
    static Gauge* createGauge();
    void reduce();
    void reduce(int value);
    void increase(int value);
    void increaseByPanelNum(int panelNum);
    bool isGameOver();
};

#endif /* defined(__chain__Gauge__) */
