#include "TitleScene.h"

USING_NS_CC;

CCScene* Title::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Title *layer = Title::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //CCLabelTTF* titleLabel  = CCLabelTTF::create("Hello", "arial", 20);
    //titleLabel->setPosition(CCPoint(visibleSize.width / 2, visibleSize.height / 2));
    //this->addChild(titleLabel);
    
    CCMenuItemLabel *gameMainButton = CCMenuItemFont::create("GameMain", this, menu_selector(Title::gameMainAction));
    CCMenuItemLabel *rankingButton  = CCMenuItemFont::create("Ranking", this, menu_selector(Title::rankingAction));
    
    //CCMenu *menu = CCMenu::createWithItems(gameMainButton, NULL);
    CCMenu *menu  = CCMenu::create(gameMainButton, rankingButton, NULL);
    menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    menu->alignItemsVertically();
    
    this->addChild(menu, 2);
    
    
    setTouchEnabled(true);
    
    this->schedule(schedule_selector(Title::update));
    return true;
}

void Title::gameMainAction(){
    //切り替え先のシーン
    CCScene *scene = GameMain::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}

void Title::rankingAction(){
    //切り替え先のシーン
    CCScene *scene = GameOver::scene();
    //0.5秒でクロスフェード
    CCTransitionCrossFade *crossFade = CCTransitionCrossFade::create(0.5f, scene);
    //切り替え
    CCDirector::sharedDirector()->replaceScene(crossFade);
}