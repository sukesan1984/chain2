//
//  GroupManagerManager.cpp
//  Chain
//
//  Created by Kosuke Takami on 2014/02/19.
//
//

#include "GroupManager.h"
#include "Const.h"

GroupManager::GroupManager(){
    table = CCDictionary::create();
    groups= CCArray::create();
    table->retain();
    groups->retain();
    groupNumber = 0;
}

GroupManager::~GroupManager(){
}

//パネルのグループを登録する。
GroupAddress* GroupManager::registerGroup(CCPoint &panelPos, Group* group){
    CCPoint pos = getIndex(panelPos);
    CCDictionary* tableY = (CCDictionary*) table->objectForKey(int(pos.x));
    if(!tableY){
        tableY = CCDictionary::create();
        table->setObject(tableY, int(pos.x));
    }
    //まだ、GroupAddressを持っていないときは、新規作成して、登録
    GroupAddress* groupAddress = (GroupAddress*) tableY->objectForKey(int(pos.y));
    if(!groupAddress){
        groupAddress = GroupAddress::create();
        tableY->setObject(groupAddress, int(pos.y));
    }
    //登録が無ければ、新しいグループだから、GroupAddressesに登録する。
    groupAddress->setGroup(group);
    return groupAddress;
}

GroupAddress* GroupManager::registerGroupAddress(CCPoint &panelPos, GroupAddress* groupAddress){
    CCPoint pos = getIndex(panelPos);
    CCDictionary* tableY = (CCDictionary*) table->objectForKey(int(pos.x));
    if(!tableY){
        tableY = CCDictionary::create();
        table->setObject(tableY, int(pos.x));
    }
    tableY->setObject(groupAddress, int(pos.y));
    return groupAddress;
}

//その位置のgroupを返す。
Group* GroupManager::searchGroup(CCPoint &panelPos){
    CCPoint pos = getIndex(panelPos);
    CCDictionary* tableY = (CCDictionary*) table->objectForKey(int(pos.x));
    if(!tableY){
        tableY = CCDictionary::create();
        table->setObject(tableY, int(pos.x));
        return NULL;
    }
    GroupAddress* groupAddress = (GroupAddress*) tableY->objectForKey(int(pos.y));
    if(!groupAddress){
        return NULL;
    }
    return groupAddress->getGroup();
}

GroupAddress* GroupManager::searchGroupAddress(CCPoint &panelPos){
    CCPoint pos = getIndex(panelPos);
    CCDictionary* tableY = (CCDictionary*) table->objectForKey(int(pos.x));
    if(!tableY){
        tableY = CCDictionary::create();
        table->setObject(tableY, int(pos.x));
        return NULL;
    }
    GroupAddress* groupAddress = (GroupAddress*) tableY->objectForKey(int(pos.y));
    if(!groupAddress){
        return NULL;
    }
    return groupAddress;
}

//2つのgroupをマージして、新たなgroupを作って返す。
//古いgroupは削除
GroupAddress* GroupManager::mergeGroups(GroupAddress* groupAddress1, GroupAddress* groupAddress2){
    Group* newGroup = this->createNewGroup();
    Group* group1 = groupAddress1->getGroup();
    Group* group2 = groupAddress2->getGroup();
    
    newGroup->registerPanels(group1->getGroupPanels());
    newGroup->registerPanels(group2->getGroupPanels());
    groups->removeObject(group1); //group1をgroupsから削除する。
    groups->removeObject(group2); //group1をgroups削除する。
    //group1->release();
    //group2->release();
    groupAddress1->setGroup(newGroup);
    groupAddress2->setGroup(newGroup);
    return groupAddress1;
}

GroupAddress* GroupManager::categorize(CCPoint &panelPos, PanelSprite* panelSprite, GroupAddress* selfGroupAddress){
    //Group* checkedGroup = this->searchGroup(panelPos);
    GroupAddress* checkedGroupAddress = this->searchGroupAddress(panelPos);
    Group* checkedGroup = NULL;
    Group* selfGroup = NULL;
    if(checkedGroupAddress){
        checkedGroup = checkedGroupAddress->getGroup();
    }
    if(selfGroupAddress){
        selfGroup = selfGroupAddress->getGroup();
    }
    CCPoint currentPos = panelSprite->getPosition();
    GroupAddress* retGroupAddress = selfGroupAddress;
    // 登録無し
    if(!checkedGroup){
        // 自分のgroupが無いときは、新しく作る。
        if(selfGroup == NULL){
            Group* newGroup = this->createNewGroup();
            newGroup->registerPanel(panelSprite);
            retGroupAddress = this->registerGroup(currentPos, newGroup);
        }
        //あるいは 登録あり、異なる色
    } else if(checkedGroup->getPanelType() != panelSprite->getPanelType()){
        // 自分のgroupが無いときは、新しく作る。
        if(selfGroup == NULL){
            Group* newGroup = this->createNewGroup();
            newGroup->registerPanel(panelSprite);
            retGroupAddress = this->registerGroup(currentPos, newGroup);
        }
    //　登録あり、同じ色
    } else {
        if(selfGroup == NULL){
            checkedGroup->registerPanel(panelSprite);
            this->registerGroupAddress(currentPos, checkedGroupAddress);
            retGroupAddress = checkedGroupAddress;
        //　自分のgroupがあるときは、そのポジションのgroupとmergeする。
        } else {
            checkedGroupAddress = this->mergeGroups(checkedGroupAddress, selfGroupAddress);
            retGroupAddress = this->registerGroupAddress(currentPos, checkedGroupAddress);
        }
    }
    return retGroupAddress;
}

Group* GroupManager::createNewGroup(){
    Group* newGroup = Group::create(groupNumber++);
    groups->addObject(newGroup);
    return newGroup;
}

GroupManager * GroupManager::create(void)
{
	GroupManager * ret = new GroupManager();
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

void GroupManager::addGroupToTable(PanelSprite* panel){
    //一番上じゃなければ、上をチェック
    CCPoint currentPos = panel->getPosition();
    GroupAddress* selfGroup = NULL;
    if(panel->getPositionY() < (FIELD_HEIGHT_SIZE / FIELD_HEIGHT_NUM) * (FIELD_HEIGHT_NUM - 1)){
        CCPoint pos = CCPoint(currentPos.x, currentPos.y + (FIELD_HEIGHT_SIZE / FIELD_HEIGHT_NUM));
        selfGroup = this->categorize(pos, panel, selfGroup);
    }
    //一番下じゃなければ、下をチェック
    if(panel->getPositionY() > 0){
        CCPoint pos = CCPoint(currentPos.x, currentPos.y - (FIELD_HEIGHT_SIZE / FIELD_HEIGHT_NUM));
        selfGroup = this->categorize(pos, panel, selfGroup);
    }
    
    //一番左じゃなければ、左をチェック
    if(panel->getPositionX() > 0){
        CCPoint pos = CCPoint(currentPos.x - (FIELD_WIDTH_SIZE / FIELD_WIDTH_NUM), currentPos.y);
        selfGroup = this->categorize(pos, panel, selfGroup);
    }
    
    if(panel->getPositionX() < (FIELD_WIDTH_SIZE / FIELD_WIDTH_NUM) * (FIELD_WIDTH_NUM -1 )){
        CCPoint pos = CCPoint(currentPos.x + (FIELD_WIDTH_SIZE / FIELD_WIDTH_NUM), currentPos.y);
        selfGroup = this->categorize(pos, panel, selfGroup);
    }
}

//削除され得るパネルを返す。
CCArray* GroupManager::getRemovedPanels(){
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCArray* retArray = CCArray::create();
    CCARRAY_FOREACH(groups, targetObject){
        group = (Group*) targetObject;
        if(group->willBeRemoved()){
            CCArray* panels = group->getGroupPanels();
            retArray->addObjectsFromArray(panels);
        }
    }
    return retArray;
}

CCPoint GroupManager::getIndex(CCPoint &panelPos){
    float posX = panelPos.x;
    float posY = panelPos.y;
    
    int x = int(posX) / int(FIELD_WIDTH_SIZE / FIELD_WIDTH_NUM);
    int y = int(posY) / int(FIELD_HEIGHT_SIZE / FIELD_HEIGHT_NUM);
    return CCPoint(x, y);
}

void GroupManager::clearAll(){
    this->table->removeAllObjects();
    this->groups->removeAllObjects();
}
