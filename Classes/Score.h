//
//  Score.h
//  chain
//
//  Created by Kosuke Takami on 2014/03/08.
//
//

#ifndef __chain__Score__
#define __chain__Score__

#include <iostream>

class Score {
    int hitNum;
    int maxHitNum;
    int score;
    Score();
    Score(const Score&);
public:
    static Score& instance();
    void setScore(int value);
    void increaseScore(int value);
    int getScore();
    void setHitNum(int value);
    void increaseHitNum();
    int getHitNum();
    
    int getMaxHitNum();
    
    void reset();
};

#endif /* defined(__chain__Score__) */
