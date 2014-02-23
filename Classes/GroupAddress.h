//
//  GroupAddress.h
//  Chain
//
//  Created by Kosuke Takami on 2014/02/22.
//
//

#ifndef __Chain__GroupAddress__
#define __Chain__GroupAddress__

#include <iostream>
#include "cocos2d.h"
#include "Group.h"

using namespace cocos2d;


//Groupへのアドレスを持っているクラス
class  GroupAddress : public CCNode{
    Group* group;
    GroupAddress();
    ~GroupAddress();
public:
    static GroupAddress* create();
    bool setGroup(Group* group);
    Group* getGroup();
};

#endif /* defined(__Chain__GroupAddress__) */
