//
//  FieldPanelsArray.cpp
//  chain
//
//  Created by Kosuke Takami on 2014/02/26.
//
//

#include "FieldPanelsArray.h"

FieldPanelsArray::FieldPanelsArray(){
    //初期化
    for(int i = 0; i < FIELD_WIDTH_NUM; i++){
        for(int j = 0; j < FIELD_HEIGHT_NUM; j++){
            table[i][j] = NULL;
            checkTable[i][j] = false;
        }
    }
    groups = CCArray::create();
    groups->retain();
    //score = 0;
    //hitNum = 0;
}

FieldPanelsArray::~FieldPanelsArray(){
    this->removeAllPanels();
    this->gauge->release();
}

void FieldPanelsArray::removeAllPanels(){
    for(int i = 0; i < FIELD_WIDTH_NUM; i++){
        for(int j = 0; j < FIELD_HEIGHT_NUM; j++){
            PanelSprite* panel = this->getPanel(i, j);
            panel->release();
            table[i][j] = NULL;
        }
    }
}

void FieldPanelsArray::resetGroupCheckTable(){
    for(int i = 0; i < FIELD_WIDTH_NUM; i++){
        for(int j = 0; j < FIELD_HEIGHT_NUM; j++){
            checkTable[i][j] = false;
        }
    }
}

CCArray* FieldPanelsArray::getGroups(){
    return groups;
}

void FieldPanelsArray::registerPanel(int x, int y, PanelSprite *panel){
    CCAssert(x >= 0 && x < FIELD_WIDTH_NUM, "x must be in field size");
    CCAssert(y >= 0 && y < FIELD_HEIGHT_NUM, "y must be in field size");
    
    if(table[x][y] != NULL){
        table[x][y]->release();
        table[x][y] = panel;
        panel->retain();
    } else {
        table[x][y] = panel;
        panel->retain();
    }
}

void FieldPanelsArray::remove(int x, int y){
    CCAssert(x >= 0 && x < FIELD_WIDTH_NUM, "x must be in field size");
    CCAssert(y >= 0 && y < FIELD_HEIGHT_NUM, "y must be in field size");
    
    if(table[x][y] == NULL){
        return;
    }
    
    table[x][y]->release();
    table[x][y] = NULL;
}

PanelSprite* FieldPanelsArray::getPanel(int x, int y){
    CCAssert(x >= 0 && x < FIELD_WIDTH_NUM, "x must be in field size");
    CCAssert(y >= 0 && y < FIELD_HEIGHT_NUM, "y must be in field size");
    
    return table[x][y];
}

void FieldPanelsArray::group(){
    //一時的なgroup map;
    Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM] = {{NULL}};
    //前回分から登録する。
    this->groupFromCurrentGroups(map);
    for(int i = 0; i < FIELD_WIDTH_NUM; i++){
        for(int j = 0; j < FIELD_HEIGHT_NUM; j++){
            this->group(i, j, map);
        }
    }
}

void FieldPanelsArray::groupFromCurrentGroups(Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]){
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->getGroups(), targetObject){
        group = (Group*) targetObject;
        this->group(group, map);
    }
}

void FieldPanelsArray::group(Group* group, Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]){
    PanelSprite* panel = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(group->getGroupPanels(), targetObject){
        panel = (PanelSprite*) targetObject;
        CCPoint index = panel->getIndex();
        int x = (int) index.x;
        int y = (int) index.y;
        map[x][y] = group;
        this->group(x, y, map);
    }
}

Group* FieldPanelsArray::group(int x, int y, Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]){
    // 前回分を取得
    Group* selfGroup = this->getBelongingGroup(x, y);
    PanelSprite* selfPanel = this->getPanel(x, y);
    //再帰的に見るので、どこかにくっついているなら、selfGroupは既に何らかのグループに所属している
    if(selfGroup == NULL){
        selfGroup = Group::create();
        groups->addObject((CCObject*) selfGroup);
        selfGroup->registerPanel(selfPanel);
    }
    map[x][y] = selfGroup;
    
    //下とのグルーピングをチェック
    if(y > 0){
        //下が既にgroupingされていれば、何もしない。
        if(map[x][y-1] == NULL){
            //下のパネル
            PanelSprite* down = this->getPanel(x, y - 1);
            //同じ色なら
            if(selfPanel->getPanelType() == down->getPanelType()){
                selfGroup->registerPanel(down);
                map[x][y-1] = selfGroup;
                this->group(x, y - 1, map);
            }
        }
    }
    //上とのグルーピングをチェック
    if(y < FIELD_HEIGHT_NUM - 1){
        //下が既にgroupingされていれば、何もしない。
        if(map[x][y+1] == NULL){
            //下のパネル
            PanelSprite* up = this->getPanel(x, y + 1);
            //同じ色なら
            if(selfPanel->getPanelType() == up->getPanelType()){
                selfGroup->registerPanel(up);
                map[x][y+1] = selfGroup;
                this->group(x, y + 1, map);
            }
        }
    }
    //左とのグルーピングをチェック
    if(x > 0){
        //下が既にgroupingされていれば、何もしない。
        if(map[x - 1][y] == NULL){
            //下のパネル
            PanelSprite* left = this->getPanel(x - 1, y);
            //同じ色なら
            if(selfPanel->getPanelType() == left->getPanelType()){
                selfGroup->registerPanel(left);
                map[x - 1][y] = selfGroup;
                this->group(x - 1, y, map);
            }
        }
    }
    //右とのグルーピングをチェック
    if(x < FIELD_WIDTH_NUM - 1){
        //下が既にgroupingされていれば、何もしない。
        if(map[x + 1][y] == NULL){
            //下のパネル
            PanelSprite* right = this->getPanel(x + 1, y);
            //同じ色なら
            if(selfPanel->getPanelType() == right->getPanelType()){
                selfGroup->registerPanel(right);
                map[x + 1][y] = selfGroup;
                this->group(x + 1, y, map);
            }
        }
    }
}


CCArray* FieldPanelsArray::getRemovedPanels(){
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCArray* removedPanels = CCArray::create();
    removedPanels->retain();
    CCArray* removedIndex = CCArray::create();
    int index = 0;
    CCARRAY_FOREACH(this->getGroups(), targetObject){
        group = (Group*) targetObject;
        if(group->willBeRemoved()){
            group->setRemoving(true);
            removedPanels->addObjectsFromArray(group->getGroupPanels());
            //新たに消え始める時は、リセットする。
            // hitnumをの数を増やす。
            if(group->needToReset()){
                group->reset();
                Score &scoreInstance = Score::instance();
                //this->hitNum++;
                //score += this->calcScore();
                //scoreInstance.setScore(score);
                scoreInstance.increaseScore(this->calcScore());
                //scoreInstance.setHitNum(this->hitNum);
                scoreInstance.increaseHitNum();
                this->gauge->increaseByPanelNum(group->getGroupPanelsNum());
            }
           //削除される時に、フラグを落とす。
            group->setAddedNewone(false);
        } else {
            removedIndex->addObject(CCInteger::create(index));
        }
        index++;
    }
    
    int maxIndex = removedIndex->count();
    //上から順に消す
    for(int i = (maxIndex - 1); i >= 0; i--){
        CCInteger* index = (CCInteger*) removedIndex->objectAtIndex(i);
        this->groups->removeObjectAtIndex(index->getValue());
    }
    return removedPanels;
}

bool FieldPanelsArray::hasRemovingPanels(){
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->getGroups(), targetObject) {
        group = (Group*) targetObject;
        if(group->isRemoving()){
            return true;
        }
    }
    return false;
}

Group* FieldPanelsArray::getBelongingGroup(int x, int y){
    PanelSprite* panel = this->getPanel(x, y);
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->getGroups(), targetObject){
        group = (Group*) targetObject;
        if(group->exist(panel)){
            return group;
        }
    }
    return NULL;
}

void FieldPanelsArray::removePanel(PanelSprite *panel){
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->getGroups(), targetObject){
        group = (Group*) targetObject;
        if(group->exist(panel)){
            int remainings = group->removePanel(panel);
            //最後の一つを消去した場合
            if(remainings == 0){
                this->removeGroup(group);
            }
        }
    }
}

void FieldPanelsArray::removeGroup(Group *group){
    groups->removeObject((CCObject*) group);
    if(groups->count() == 0){
        Score::instance().setHitNum(0);
        //hitNum = 0;
    }
}

int FieldPanelsArray::getHitNum(){
    return Score::instance().getHitNum();
}

int FieldPanelsArray::getScore(){
    //Score &scoreInstance = Score::instance();
    return Score::instance().getScore();
}

int FieldPanelsArray::calcScore(){
    //scoreの計算は、現在のヒット数 x つながっているパネルの数。
    int panelNum = 0;
    Group* group = NULL;
    CCObject* targetObject = NULL;
    CCARRAY_FOREACH(this->getGroups(), targetObject){
        group = (Group*) targetObject;
        if(group->willBeRemoved()){
            panelNum += group->getGroupPanelsNum();
        }
    }
    return panelNum * ( Score::instance().getHitNum() / 5 + 1);
}

void FieldPanelsArray::setGauge(Gauge* gauge){
    this->gauge = gauge;
    this->gauge->retain();
}