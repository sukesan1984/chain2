//
//  Score.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/03/08.
//
//

#include "Score.h"

Score& Score::instance(){
    static Score instance;
    return instance;
}

Score::Score(){
    hitNum = 0;
    maxHitNum = 0;
    score = 0;
}

void Score::setScore(int value){
    this->score = value;
}

int Score::getScore(){
    return this->score;
}

void Score::setHitNum(int value){
    this->hitNum = value;
    if(this->maxHitNum < this->hitNum){
        this->maxHitNum = this->hitNum;
    }
}

int Score::getHitNum(){
    return this->hitNum;
}