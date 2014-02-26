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
}

FieldPanelsArray::~FieldPanelsArray(){
    this->removeAllPanels();
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
    for(int i = 0; i < FIELD_WIDTH_NUM; i++){
        for(int j = 0; j < FIELD_HEIGHT_NUM; j++){
            this->group(i, j, map);
        }
    }
    
    /*
    for(int j = 0; j < FIELD_HEIGHT_NUM; j++){
        for(int i = 0; i < (FIELD_WIDTH_NUM - 1) + FIELD_WIDTH_NUM; i++){
                //横同士
                if(i < FIELD_WIDTH_NUM - 1){
                    PanelSprite* left = this->getPanel(i, j);
                    PanelSprite* right = this->getPanel(i + 1, j);
                    if(left->getPanelType() == right->getPanelType()){
                        if(map[i][j] != NULL ){
                            map[i][j]->registerPanel(right);
                            map[i+1][j] = map[i][j];
                        } else if(map[i+1][j] != NULL){
                            map[i+1][j]->registerPanel(left);
                            map[i][j] = map[i+1][j];
                        } else {
                            Group* newGroup = Group::create();
                            groups->addObject((CCObject*) newGroup);
                            newGroup->registerPanel(left);
                            newGroup->registerPanel(right);
                            map[i][j] = map[i+1][j] = newGroup;
                        }
                    }
                //縦同士
                } else {
                    //最上段は、上下のチェックはしない。
                    if(j < FIELD_HEIGHT_NUM - 1){
                        int startX = i - FIELD_WIDTH_NUM + 1;
                        PanelSprite* down = this->getPanel(startX, j);
                        PanelSprite* top = this->getPanel(startX, j + 1);
                        if(down->getPanelType() == top->getPanelType()){
                        //下あるいは上にgroupがあれば、それぞれを登録する。
                        //どちらもグループに属さないときは、新たにグループを作る
                        if(map[startX][j] != NULL){
                            map[startX][j]->registerPanel(top);
                            map[startX][j+1] = map[startX][j];
                        } else if(map[startX][j+1] != NULL){
                            map[startX][j+1]->registerPanel(down);
                            map[startX][j] = map[i][j+1];
                        } else {
                            Group* newGroup = Group::create();
                            groups->addObject((CCObject*) newGroup);
                            newGroup->registerPanel(down);
                            newGroup->registerPanel(top);
                            map[startX][j] = newGroup;
                            map[startX][j+1] = newGroup;
                        }
                    }
                }
            }
        }
    }
    */
}

Group* FieldPanelsArray::group(int x, int y, Group* map[FIELD_WIDTH_NUM][FIELD_HEIGHT_NUM]){
    //再帰的に見るので、どこかにくっついているなら、selfGroupは既に何らかのグループに所属している
    Group* selfGroup = map[x][y];
    PanelSprite* selfPanel = this->getPanel(x, y);
    if(selfGroup == NULL){
        selfGroup = Group::create();
        groups->addObject((CCObject*) selfGroup);
        selfGroup->registerPanel(selfPanel);
    }
    
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
    CCARRAY_FOREACH(this->getGroups(), targetObject){
        group = (Group*) targetObject;
        if(group->willBeRemoved()){
            removedPanels->addObjectsFromArray(group->getGroupPanels());
        }
    }
    return removedPanels;
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
}