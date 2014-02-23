//
//  GroupAddressAddress.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/22.
//
//

#include "GroupAddress.h"

GroupAddress::GroupAddress(){
    group = NULL;
}

GroupAddress::~GroupAddress(){
}

GroupAddress * GroupAddress::create()
{
	GroupAddress * ret = new GroupAddress();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

//既に存在していた場合は、true
bool GroupAddress::setGroup(Group* group){
    bool ret = this->group != NULL;
    this->group = group;
    return ret;
}

Group* GroupAddress::getGroup(){
    return this->group;
}